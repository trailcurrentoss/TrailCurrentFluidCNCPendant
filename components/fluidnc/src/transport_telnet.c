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
 * Reconnect: this transport does NOT auto-reconnect on a dropped socket —
 * the dispatcher's reconnect-watch (in main/app_state.c) used to layer
 * one on, but the loop was noisy and was removed. Telnet drops should be
 * rare on a wired LAN; if it becomes a problem we can add a backoff retry
 * inside the rx task.
 */

#include "transport.h"

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
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

static TaskHandle_t  s_rx_task = NULL;
static volatile bool s_run     = false;
static volatile int  s_sock    = -1;
static volatile bool s_open    = false;

static void rx_task(void *arg)
{
    (void)arg;
    char buf[RX_BUF_BYTES];
    while (s_run) {
        int sock = s_sock;
        if (sock < 0) { vTaskDelay(pdMS_TO_TICKS(100)); continue; }
        int n = recv(sock, buf, sizeof(buf), 0);
        if (n > 0) {
            fluidnc_dispatcher_feed_rx(buf, (size_t)n);
        } else if (n == 0) {
            ESP_LOGW(TAG, "remote closed connection");
            s_open = false;
            fluidnc_dispatcher_set_link_open(false);
            break;
        } else {
            /* recv error — log + bail. errno EAGAIN is unlikely since the
             * socket is blocking. ECONNRESET / ENOTCONN / etc. all imply
             * the connection is gone. */
            ESP_LOGW(TAG, "recv error: errno=%d", errno);
            s_open = false;
            fluidnc_dispatcher_set_link_open(false);
            break;
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
    uint16_t port = cfg->fluid_port ? cfg->fluid_port : DEFAULT_TELNET_PORT;

    /* Resolve the hostname — supports both literal IPv4 and mDNS names like
     * "fluidnc.local" if the network supports it. */
    struct addrinfo hints = {
        .ai_family   = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    char port_str[8];
    snprintf(port_str, sizeof(port_str), "%u", (unsigned)port);
    struct addrinfo *res = NULL;
    int err = getaddrinfo(cfg->fluid_host, port_str, &hints, &res);
    if (err != 0 || res == NULL) {
        ESP_LOGE(TAG, "getaddrinfo(%s:%u) failed: %d", cfg->fluid_host,
                 (unsigned)port, err);
        if (res) freeaddrinfo(res);
        return ESP_FAIL;
    }

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        ESP_LOGE(TAG, "socket() failed: errno=%d", errno);
        freeaddrinfo(res);
        return ESP_FAIL;
    }

    /* 5 s connect timeout — long enough for slow networks, short enough that
     * the user gets the "Connection failed" feedback before they give up. */
    struct timeval tv = { .tv_sec = 5, .tv_usec = 0 };
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    ESP_LOGI(TAG, "connecting %s:%u ...", cfg->fluid_host, (unsigned)port);
    if (connect(sock, res->ai_addr, res->ai_addrlen) != 0) {
        ESP_LOGE(TAG, "connect() failed: errno=%d (%s)", errno, strerror(errno));
        close(sock);
        freeaddrinfo(res);
        return ESP_FAIL;
    }
    freeaddrinfo(res);

    /* Switch RCVTIMEO back to blocking so the rx task isn't churning. */
    tv.tv_sec = 0; tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

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
