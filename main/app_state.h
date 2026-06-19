#pragma once

/*
 * Top-level pendant state machine.
 *
 *      ┌─── BOOT ────────────────────────────────┐
 *      │ NVS, BSP, LVGL init                     │
 *      └─────────────────────────────────────────┘
 *                  │
 *                  ▼  no saved SSID
 *      ┌─── WIFI_SETUP ──────────────────────────┐
 *      │ PageWifiSetup — scan + password panel   │
 *      └─────────────────────────────────────────┘
 *                  │  user submits credentials
 *                  ▼
 *      ┌─── WIFI_CONNECTING ─────────────────────┐
 *      │ esp_wifi_connect, await IP_EVENT        │
 *      └─────────────────────────────────────────┘
 *                  │  IP_EVENT_STA_GOT_IP
 *                  ▼
 *      ┌─── FLUID_CONNECT ───────────────────────┐
 *      │ PageFluidConnect — host/transport prompt│
 *      │   skipped automatically when both have  │
 *      │   been saved before                     │
 *      └─────────────────────────────────────────┘
 *                  │  user submits / saved config valid
 *                  ▼
 *      ┌─── FLUID_CONNECTING ────────────────────┐
 *      └─────────────────────────────────────────┘
 *                  │  fluidnc_status == IDLE
 *                  ▼
 *      ┌─── PENDANT (Dashboard, Jog, Run, …) ────┐
 *      └─────────────────────────────────────────┘
 *
 * Failures: any connection error returns to the corresponding *_SETUP /
 * *_CONNECT screen with the alarm ribbon shown.
 *
 * All transitions go through app_state_set() so the screen swap and side
 * effects (wifi_setup_init, fluidnc_connect, lv_scr_load, …) happen in one
 * place. The state machine runs on the LVGL task — bsp_display_lock is
 * already held by the caller.
 */

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    APP_STATE_BOOT = 0,
    APP_STATE_WIFI_SETUP,
    APP_STATE_WIFI_CONNECTING,
    APP_STATE_FLUID_CONNECT,
    APP_STATE_FLUID_CONNECTING,
    APP_STATE_PENDANT,
} app_state_t;

/* Initialize: starts in BOOT, drives the first transition based on saved cfg. */
esp_err_t app_state_init(void);

/* Force a transition. Called from the WiFi event handler, FluidNC status
 * callback, or directly by UI actions (e.g., user taps "Back to WiFi"). */
void app_state_set(app_state_t next);

app_state_t app_state_get(void);

/* Switch which pendant page is active (Dashboard, Jog, Run, …).
 * No-op when current state != APP_STATE_PENDANT. */
void app_state_set_pendant_tab(int tab_id);

/* Refresh the Settings → Connection labels (saved SSID + connection state)
 * and the System "Network" row from pendant_config + wifi_setup. Safe from
 * any task — brackets LVGL access with bsp_display_lock(). */
void app_state_refresh_connection_display(void);

/* Repaint the 6 Files page rows from fluidnc_get_files(). Called after
 * fluidnc_refresh_files() returns and from action_file_refresh when the
 * user taps the refresh button. Safe from any task. */
void app_state_refresh_files_display(void);

/* Push the vars.c "pre-connect" defaults into every UI-bound widget so
 * the screen lights up showing OFFLINE / 0.000 / (no job loaded) / etc.
 * instead of the demo text baked into the .eez-project. Call once after
 * ui_init() and after restore_user_settings_from_nvs(). Safe from any
 * task. */
void app_state_paint_initial_state(void);

/* Toggle the CHECKED state across every dynamically-created file row so
 * the visual "selected row" follows the user's tap. Called from
 * action_file_select. idx is the row index (0-based, MAX_FILES exclusive);
 * passing -1 (or out-of-range) clears every row. Must be called from a
 * context where the LVGL lock is held — i.e. inside an event handler. */
void app_state_files_select_visual(int idx);

#ifdef __cplusplus
}
#endif
