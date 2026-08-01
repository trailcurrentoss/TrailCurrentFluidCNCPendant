/*
 * Telnet transport for FluidNC.
 *
 * Plain line-based grbl protocol over a raw TCP socket. FluidNC's telnet
 * port is 23 by default but the user can configure any port via the
 * pendant's Settings → Machine → Configure FluidNC Connection screen.
 *
 * Threading:
 *   - One rx task does blocking recv() in a loop and forwards bytes to the
 *     dispatcher's line buffer.
 *   - Writes are synchronous send() calls from whatever task invoked them
 *     (status poller, action handler). socket I/O is serialised by the
 *     kernel; we don't add extra locking around send().
 *
 * Reconnect: the rx task owns it. The first connect happens synchronously
 * in telnet_open() so the UI still gets immediate "connection failed"
 * feedback; after that, any dropped socket is retried by the rx task at
 * 1 s intervals until telnet_close() — matching the WS transport's 1 s
 * auto-reconnect behaviour so the two are interchangeable in the field.
 */

#include "transport.h"

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "fluidnc_telnet";

#define DEFAULT_TELNET_PORT 23
#define RX_BUF_BYTES        512

#define RECONNECT_BACKOFF_MS 1000

static TaskHandle_t  s_rx_task = NULL;
static volatile bool s_run     = false;
static volatile int  s_sock    = -1;
static volatile bool s_open    = false;

/* Snapshot of the target taken in telnet_open() so the rx task can
 * re-dial without touching the live config from another task. */
static char     s_host[64];
static uint16_t s_port = DEFAULT_TELNET_PORT;

/* Resolve + connect. Returns the connected socket or -1. Shared by the
 * synchronous first connect and the rx task's reconnect loop. */
static int try_connect(const char *host, uint16_t port)
{
    struct addrinfo hints = {
        .ai_family   = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    char port_str[8];
    snprintf(port_str, sizeof(port_str), "%u", (unsigned)port);
    struct addrinfo *res = NULL;
    int err = getaddrinfo(host, port_str, &hints, &res);
    if (err != 0 || res == NULL) {
        ESP_LOGW(TAG, "getaddrinfo(%s:%u) failed: %d", host, (unsigned)port, err);
        if (res) freeaddrinfo(res);
        return -1;
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        ESP_LOGW(TAG, "socket() failed: errno=%d", errno);
        freeaddrinfo(res);
        return -1;
    }

    /* 5 s connect timeout — long enough for slow networks, short enough that
     * the user gets the "Connection failed" feedback before they give up. */
    struct timeval tv = { .tv_sec = 5, .tv_usec = 0 };
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
        ESP_LOGW(TAG, "connect(%s:%u) failed: errno=%d (%s)", host,
                 (unsigned)port, errno, strerror(errno));
        close(sock);
        freeaddrinfo(res);
        return -1;
    }
    freeaddrinfo(res);

    /* Switch RCVTIMEO back to blocking so the rx task isn't churning. */
    tv.tv_sec = 0; tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    /* Realtime control stream — never let Nagle hold a write. A queued
     * 0x85 jog-cancel or E-STOP byte sitting in the TCP send buffer
     * waiting for an ACK is exactly the latency this pendant exists to
     * avoid; the payloads are tiny, so the extra packets are irrelevant. */
    int nodelay = 1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &nodelay, sizeof(nodelay));
    return sock;
}

static void rx_task(void *arg)
{
    (void)arg;
    char buf[RX_BUF_BYTES];
    while (s_run) {
        int sock = s_sock;
        if (sock < 0) {
            /* Dropped — re-dial with backoff until closed or connected. */
            vTaskDelay(pdMS_TO_TICKS(RECONNECT_BACKOFF_MS));
            if (!s_run) break;
            sock = try_connect(s_host, s_port);
            if (sock < 0) continue;
            s_sock = sock;
            s_open = true;
            fluidnc_dispatcher_set_link_open(true);
            ESP_LOGI(TAG, "reconnected");
            continue;
        }
        int n = recv(sock, buf, sizeof(buf), 0);
        if (n > 0) {
            fluidnc_dispatcher_feed_rx(buf, (size_t)n);
        } else {
            /* n == 0: orderly close. n < 0: ECONNRESET / ENOTCONN / etc. —
             * either way the connection is gone; drop it and let the loop
             * above re-dial. */
            if (n == 0) ESP_LOGW(TAG, "remote closed connection");
            else        ESP_LOGW(TAG, "recv error: errno=%d", errno);
            s_open = false;
            fluidnc_dispatcher_set_link_open(false);
            if (s_sock >= 0) { close(s_sock); s_sock = -1; }
        }
    }
    if (s_sock >= 0) { close(s_sock); s_sock = -1; }
    s_open    = false;
    s_rx_task = NULL;
    vTaskDelete(NULL);
}

static esp_err_t telnet_open(const pendant_config_t *cfg)
{
    if (s_open) return ESP_OK;
    if (cfg->fluid_host[0] == '\0') {
        ESP_LOGE(TAG, "open requested but no host configured");
        return ESP_ERR_INVALID_ARG;
    }
    /* Snapshot the target for the rx task's reconnect loop. */
    strlcpy(s_host, cfg->fluid_host, sizeof(s_host));
    s_port = cfg->fluid_port ? cfg->fluid_port : DEFAULT_TELNET_PORT;

    ESP_LOGI(TAG, "connecting %s:%u ...", s_host, (unsigned)s_port);
    int sock = try_connect(s_host, s_port);
    if (sock < 0) return ESP_FAIL;

    s_sock = sock;
    s_open = true;
    s_run  = true;
    if (xTaskCreatePinnedToCore(rx_task, "fluidnc_tn_rx", 4096, NULL, 5,
                                &s_rx_task, 0) != pdPASS) {
        close(sock);
        s_sock = -1;
        s_open = false;
        s_run  = false;
        return ESP_FAIL;
    }

    fluidnc_dispatcher_set_link_open(true);
    ESP_LOGI(TAG, "connected");
    return ESP_OK;
}

static void telnet_close(void)
{
    if (!s_open && s_sock < 0) return;
    s_run = false;
    if (s_sock >= 0) {
        /* Shutdown unblocks the rx task's recv() call. */
        shutdown(s_sock, SHUT_RDWR);
        close(s_sock);
        s_sock = -1;
    }
    s_open = false;
    fluidnc_dispatcher_set_link_open(false);
    /* Give the rx task ~150 ms to exit cleanly. */
    vTaskDelay(pdMS_TO_TICKS(150));
}

static esp_err_t telnet_write(const void *data, size_t n)
{
    if (!s_open || s_sock < 0) return ESP_ERR_INVALID_STATE;
    int sent = send(s_sock, data, n, 0);
    return sent == (int)n ? ESP_OK : ESP_FAIL;
}

static bool telnet_is_open(void) { return s_open; }

const fluid_transport_t g_transport_telnet = {
    .open    = telnet_open,
    .close   = telnet_close,
    .write   = telnet_write,
    .is_open = telnet_is_open,
};
