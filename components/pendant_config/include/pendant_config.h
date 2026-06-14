#pragma once

/*
 * Pendant persistent configuration (NVS-backed).
 *
 * Single source of truth for all user-entered settings the pendant remembers
 * across reboots: WiFi credentials, FluidNC transport, units preference,
 * limits toggles, etc. No SD-card / external-file path — the touchscreen UI is
 * the only configuration surface.
 *
 * NVS namespace: "pendant".
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PENDANT_CFG_SSID_MAX    33      /* 32 + NUL */
#define PENDANT_CFG_PASS_MAX    65      /* 64 + NUL */
#define PENDANT_CFG_HOST_MAX    65      /* hostname/IP + NUL */

typedef enum {
    PENDANT_TRANSPORT_UART      = 0,
    PENDANT_TRANSPORT_WEBSOCKET = 1,
    PENDANT_TRANSPORT_TELNET    = 2,
} pendant_transport_t;

typedef enum {
    PENDANT_UNITS_MM   = 0,
    PENDANT_UNITS_INCH = 1,
} pendant_units_t;

typedef struct {
    /* WiFi */
    char     wifi_ssid[PENDANT_CFG_SSID_MAX];
    char     wifi_pass[PENDANT_CFG_PASS_MAX];

    /* FluidNC connection
     *   transport      — UART (wired) / WebSocket (wireless) / Telnet (rare)
     *   host           — hostname/IP for WS/Telnet; ignored for UART
     *   port           — WebSocket: 81 (FluidNC 3.x, default) or 80 (4.x);
     *                    Telnet: 23. Ignored for UART.
     */
    pendant_transport_t fluid_transport;
    char     fluid_host[PENDANT_CFG_HOST_MAX];
    uint16_t fluid_port;

    /* User preferences */
    pendant_units_t units;
    bool     soft_limits;
    bool     hard_limits;
    bool     home_on_boot;
} pendant_config_t;

/* Initialize NVS namespace and load config into the global cache.
 * If no config has been saved yet, fills the cache with defaults
 * (empty creds, transport=UART, units=mm, soft+hard limits on, home_on_boot off).
 */
esp_err_t pendant_config_init(void);

/* Pointer to the in-memory cached config. Read-only access is fine without a
 * lock; mutating fields directly is NOT safe — use the setters below so the
 * NVS write happens atomically.
 */
const pendant_config_t *pendant_config_get(void);

/* True when WiFi SSID is non-empty (i.e. user has saved credentials before). */
bool pendant_config_has_wifi(void);

/* True when FluidNC host or transport has been configured (UART transport
 * needs no host, so transport != default is enough). */
bool pendant_config_has_fluid(void);

/* --- Setters: each writes the field to NVS and updates the cache. --- */
esp_err_t pendant_config_set_wifi(const char *ssid, const char *pass);
esp_err_t pendant_config_clear_wifi(void);

esp_err_t pendant_config_set_fluid_transport(pendant_transport_t t);
esp_err_t pendant_config_set_fluid_host(const char *host);
esp_err_t pendant_config_set_fluid_port(uint16_t port);

esp_err_t pendant_config_set_units(pendant_units_t u);
esp_err_t pendant_config_set_soft_limits(bool on);
esp_err_t pendant_config_set_hard_limits(bool on);
esp_err_t pendant_config_set_home_on_boot(bool on);

#ifdef __cplusplus
}
#endif
