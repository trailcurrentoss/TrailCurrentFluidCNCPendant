/*
 * WebSocket transport for FluidNC.
 *
 * FluidNC's wireless port speaks plain text grbl over a WebSocket on
 *   ws://<host>:<port>/
 * Port defaults: 81 (FluidNC 3.x) / 80 (4.x). The pendant stores both host
 * and port in pendant_config; if port is 0 we fall back to 81.
 *
 * Threading:
 *   - esp_websocket_client runs its own RX task; we receive WS_EVENT_DATA
 *     events from there and bounce bytes into the dispatcher's line buffer.
 *   - Writes are synchronous from whatever task called us (action handler,
 *     status poller, …). esp_websocket_client serialises writes internally.
 */

#include "transport.h"

#include <string.h>

#include "esp_err.h"
#include "esp_log.h"
#include "esp_websocket_client.h"

static const char *TAG = "fluidnc_ws";

static esp_websocket_client_handle_t s_ws  = NULL;
static volatile bool                 s_open = false;

static void ws_event_cb(void *handler_args, esp_event_base_t base,
                        int32_t event_id, void *event_data)
{
    (void)handler_args; (void)base;
    esp_websocket_event_data_t *d = (esp_websocket_event_data_t *)event_data;
    switch ((esp_websocket_event_id_t)event_id) {
    case WEBSOCKET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "connected");
        s_open = true;
        fluidnc_dispatcher_set_link_open(true);
        break;
    case WEBSOCKET_EVENT_DISCONNECTED:
        ESP_LOGW(TAG, "disconnected");
        s_open = false;
        fluidnc_dispatcher_set_link_open(false);
        break;
    case WEBSOCKET_EVENT_DATA:
        /* FluidNC 4.x sends grbl traffic as BINARY frames (op_code 0x02).
         * Accept text + continuation + binary; skip control frames. */
        if (d && d->data_ptr && d->data_len > 0
            && (d->op_code == 0x00 || d->op_code == 0x01 || d->op_code == 0x02)) {
            fluidnc_dispatcher_feed_rx((const char *)d->data_ptr, d->data_len);
        }
        break;
    case WEBSOCKET_EVENT_ERROR:
        ESP_LOGW(TAG, "error event");
        break;
    default:
        break;
    }
}

static esp_err_t ws_open(const pendant_config_t *cfg)
{
    if (s_ws) return ESP_OK;             /* already initialised */

    char uri[128];
    uint16_t port = cfg->fluid_port ? cfg->fluid_port : 81;
    if (cfg->fluid_host[0] == '\0') {
        ESP_LOGE(TAG, "open requested but no host configured");
        return ESP_ERR_INVALID_ARG;
    }
    snprintf(uri, sizeof(uri), "ws://%s:%u/", cfg->fluid_host, (unsigned)port);
    ESP_LOGI(TAG, "open %s", uri);

    esp_websocket_client_config_t wcfg = {
        .uri                  = uri,
        .reconnect_timeout_ms = 5000,
        .network_timeout_ms   = 10000,
        .buffer_size          = 1024,
        .task_stack           = 6144,
        .task_prio            = 5,
        /* FluidNC and other grbl-over-WS servers (FluidTouch, ESP3D) use the
         * "arduino" subprotocol marker on the WebSocket handshake. Without
         * it, FluidNC's HTTP server accepts the upgrade but doesn't route
         * the connection into its grbl reader — the TCP link stays open
         * but no status reports come back. */
        .subprotocol          = "arduino",
        /* Detect dead-remote scenarios: when FluidNC's main loop hangs but
         * the TCP socket stays open, the client used to silently sit on a
         * "connected" link forever — no status reports, no rejected writes,
         * no auto-reconnect. Sending a WebSocket ping every 10 s and
         * requiring a pong within 5 s tears the link down so the client's
         * own 5 s reconnect_timeout_ms kicks in and re-establishes. The
         * pendant surfaces this as OFFLINE on the status pill, which is
         * exactly what the user needs to know when the controller hangs. */
        .ping_interval_sec    = 10,
        .pingpong_timeout_sec = 5,
    };
    s_ws = esp_websocket_client_init(&wcfg);
    if (!s_ws) return ESP_FAIL;

    esp_websocket_register_events(s_ws, WEBSOCKET_EVENT_ANY, ws_event_cb, NULL);
    return esp_websocket_client_start(s_ws);
}

static void ws_close(void)
{
    if (!s_ws) return;
    esp_websocket_client_close(s_ws, pdMS_TO_TICKS(1000));
    esp_websocket_client_destroy(s_ws);
    s_ws   = NULL;
    s_open = false;
}

static esp_err_t ws_write(const void *data, size_t n)
{
    if (!s_ws || !s_open) return ESP_ERR_INVALID_STATE;
    /* esp_websocket_client_send_text expects a length argument that is the
     * payload bytes; it builds the WS frame around it. timeout 0 = non-block
     * if internal queue is empty, but pumps if it isn't. We pass a small
     * timeout so the realtime bytes don't get dropped on a short stall. */
    int sent = esp_websocket_client_send_text(s_ws, (const char *)data, n,
                                              pdMS_TO_TICKS(200));
    return sent == (int)n ? ESP_OK : ESP_FAIL;
}

static bool ws_is_open(void)
{
    return s_open;
}

const fluid_transport_t g_transport_ws = {
    .open    = ws_open,
    .close   = ws_close,
    .write   = ws_write,
    .is_open = ws_is_open,
};
