#pragma once

/*
 * WiFi setup — STA mode scan + connect.
 *
 * The ESP32-P4 has no native WiFi radio. ESP-Hosted bridges to an ESP32-C6
 * slave over SDIO (Waveshare ESP32-P4 WiFi6 Touch LCD 7B board layout); the
 * standard esp_wifi_* APIs work as soon as ESP-Hosted is up.
 *
 * Credentials live in NVS via pendant_config — this module never touches NVS
 * directly. The pendant UI calls:
 *
 *   1. wifi_setup_init()              once, after NVS + netif + event loop
 *   2. wifi_setup_scan_start(cb)      to populate the network list
 *   3. wifi_setup_connect(ssid, pwd)  when the user submits the password panel
 *   4. wifi_setup_disconnect()        to drop the link (used when changing WiFi)
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_SETUP_MAX_SCAN_RESULTS 12
#define WIFI_SETUP_SSID_MAX         33
#define WIFI_SETUP_BSSID_LEN        6

typedef enum {
    WIFI_SETUP_STATE_IDLE = 0,
    WIFI_SETUP_STATE_SCANNING,
    WIFI_SETUP_STATE_CONNECTING,
    WIFI_SETUP_STATE_CONNECTED,
    WIFI_SETUP_STATE_FAILED,
} wifi_setup_state_t;

/* Bucketed reason for the last STATE_FAILED transition. The UI uses this to
 * tell the user *why* the connection failed without exposing every raw
 * ESP-IDF wifi_err_reason_t code. */
typedef enum {
    WIFI_SETUP_FAIL_NONE = 0,
    WIFI_SETUP_FAIL_BAD_PASSWORD,   /* auth failed / 4-way handshake / cipher mismatch */
    WIFI_SETUP_FAIL_AP_NOT_FOUND,   /* SSID not in range / beacon timeout */
    WIFI_SETUP_FAIL_TIMEOUT,        /* assoc / auth timeout */
    WIFI_SETUP_FAIL_UNKNOWN,        /* anything else (still actionable: "try again") */
} wifi_setup_fail_reason_t;

typedef struct {
    char     ssid[WIFI_SETUP_SSID_MAX];
    uint8_t  bssid[WIFI_SETUP_BSSID_LEN];
    int8_t   rssi;          /* dBm, negative */
    uint8_t  bars;          /* 0..3 derived bucket for UI */
    bool     locked;        /* true when the AP uses any auth */
} wifi_setup_network_t;

/* Callback when the state changes. Runs on the WiFi event task — keep it short
 * and bounce LVGL updates onto the LVGL thread with bsp_display_lock(). */
typedef void (*wifi_setup_state_cb_t)(wifi_setup_state_t state, void *user_ctx);

/* Initialize WiFi (netif, default event loop, STA mode, start driver).
 * Idempotent — safe to call multiple times. */
esp_err_t wifi_setup_init(wifi_setup_state_cb_t state_cb, void *user_ctx);

/* Start an async scan. The callback fires with STATE_IDLE once results are
 * available; read them with wifi_setup_get_scan_results(). */
esp_err_t wifi_setup_scan_start(void);

/* Fill out an array of recently-scanned networks. Returns the number written
 * (at most WIFI_SETUP_MAX_SCAN_RESULTS). Sorted by RSSI descending. */
size_t wifi_setup_get_scan_results(wifi_setup_network_t *out, size_t out_cap);

/* Connect to the named network using the given password.
 * Password may be empty for open networks. */
esp_err_t wifi_setup_connect(const char *ssid, const char *password);

/* Disconnect and stop any reconnect attempts. */
esp_err_t wifi_setup_disconnect(void);

wifi_setup_state_t wifi_setup_get_state(void);

/* Reason for the most recent transition into STATE_FAILED.
 * Returns WIFI_SETUP_FAIL_NONE if no failure has occurred yet, or if the
 * connection succeeded since the last failure. */
wifi_setup_fail_reason_t wifi_setup_get_last_failure_reason(void);

/* Last-known IPv4 address, or 0.0.0.0 if not connected. */
uint32_t wifi_setup_get_ip(void);

/* Print "192.168.4.1" form into buf. */
void wifi_setup_format_ip(char *buf, size_t buf_sz);

#ifdef __cplusplus
}
#endif
