#pragma once

/*
 * Transport vtable for the FluidNC dispatcher. Each backend (WebSocket,
 * UART, …) exposes a const fluid_transport_t with these four entry points.
 * The dispatcher picks one at fluidnc_connect() time based on the
 * pendant_config_t.fluid_transport setting.
 *
 * Bytes received on the wire are pushed back into the dispatcher via
 * fluidnc_dispatcher_feed_rx() — the transport doesn't need to know about
 * line buffering or the proto parser.
 *
 * Link state changes (websocket connected / disconnected, UART driver
 * reset) are reported via fluidnc_dispatcher_set_link_open(). The
 * dispatcher uses this to gate the status poller and surface OFFLINE on
 * the status pill.
 */

#include <stdbool.h>
#include <stddef.h>

#include "esp_err.h"
#include "pendant_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* Open the link. Reads cfg->fluid_host / fluid_port / etc. as needed.
     * Returns ESP_OK on accepted-connection-attempt (the actual open may
     * happen asynchronously — link readiness is signalled via
     * fluidnc_dispatcher_set_link_open()). */
    esp_err_t (*open)(const pendant_config_t *cfg);

    /* Tear down the link. Synchronous; safe to call when already closed. */
    void (*close)(void);

    /* Write raw bytes. For text commands the caller passes the trailing '\n'.
     * For realtime bytes (?, !, ~, 0x18, …) the caller passes a single byte. */
    esp_err_t (*write)(const void *data, size_t n);

    /* Is the link currently usable? Polled by the status-poller before each
     * "?" so we don't pile up writes against a broken link. */
    bool (*is_open)(void);
} fluid_transport_t;

extern const fluid_transport_t g_transport_ws;
extern const fluid_transport_t g_transport_uart;
extern const fluid_transport_t g_transport_telnet;

/* Push received bytes into the dispatcher's line buffer. Called from each
 * transport's rx callback. Safe from any task. */
void fluidnc_dispatcher_feed_rx(const char *data, size_t n);

/* Report a link-readiness transition. open=true means the transport is now
 * ready to write (e.g. WebSocket handshake completed); open=false means it
 * has gone down. */
void fluidnc_dispatcher_set_link_open(bool open);

#ifdef __cplusplus
}
#endif
