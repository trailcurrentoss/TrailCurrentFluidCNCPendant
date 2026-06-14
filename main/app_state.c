#include "app_state.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "lvgl.h"

#include "bsp/display.h"
#include "bsp/esp-bsp.h"
#include "fluidnc.h"
#include "pendant_config.h"
#include "wifi_setup.h"

/* EEZ Studio export — after the user runs Build (Ctrl+B) in EEZ Studio these
 * become populated; until then the file may be absent.  Using __has_include
 * keeps the project buildable through the bootstrap phase. */
#if __has_include("ui/screens.h")
#  include "ui/screens.h"
#  define HAVE_UI 1
#else
#  define HAVE_UI 0
#endif

static const char *TAG = "app_state";
static app_state_t s_state = APP_STATE_BOOT;

#if HAVE_UI
/* Screen objects come from `objects.page_<name>` in EEZ Studio's export. */
static void load_screen(lv_obj_t *scr)
{
    if (!scr) return;
    bsp_display_lock(0);
    lv_scr_load(scr);
    bsp_display_unlock();
}
#else
static inline void load_screen(void *scr) { (void)scr; }
#endif

#if HAVE_UI
/* Active vs inactive bar colors — TrailCurrent palette tokens via lv_color_hex. */
#define WIFI_BAR_ACTIVE_COLOR   0x52A441   /* AccentPrimary */
#define WIFI_BAR_INACTIVE_COLOR 0x6F7780   /* TextSecondary */

static void wifi_ui_paint_bars(int row_idx, uint8_t bars)
{
    lv_obj_t *b1, *b2, *b3;
    switch (row_idx) {
    case 0: b1 = objects.wifi_net_bar1_0; b2 = objects.wifi_net_bar2_0; b3 = objects.wifi_net_bar3_0; break;
    case 1: b1 = objects.wifi_net_bar1_1; b2 = objects.wifi_net_bar2_1; b3 = objects.wifi_net_bar3_1; break;
    case 2: b1 = objects.wifi_net_bar1_2; b2 = objects.wifi_net_bar2_2; b3 = objects.wifi_net_bar3_2; break;
    case 3: b1 = objects.wifi_net_bar1_3; b2 = objects.wifi_net_bar2_3; b3 = objects.wifi_net_bar3_3; break;
    case 4: b1 = objects.wifi_net_bar1_4; b2 = objects.wifi_net_bar2_4; b3 = objects.wifi_net_bar3_4; break;
    case 5: b1 = objects.wifi_net_bar1_5; b2 = objects.wifi_net_bar2_5; b3 = objects.wifi_net_bar3_5; break;
    case 6: b1 = objects.wifi_net_bar1_6; b2 = objects.wifi_net_bar2_6; b3 = objects.wifi_net_bar3_6; break;
    case 7: b1 = objects.wifi_net_bar1_7; b2 = objects.wifi_net_bar2_7; b3 = objects.wifi_net_bar3_7; break;
    default: return;
    }
    lv_obj_t *const bs[3] = { b1, b2, b3 };
    for (int b = 0; b < 3; b++) {
        bool active = (b < bars);
        lv_obj_set_style_bg_color(bs[b],
            lv_color_hex(active ? WIFI_BAR_ACTIVE_COLOR : WIFI_BAR_INACTIVE_COLOR),
            LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(bs[b], active ? 255 : 80,
            LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

/* Push the latest scan results into the wifi_net_<i> row widgets. Hides any
 * row beyond the result count; shows "No networks found" in the status label
 * when the scan returned 0. Called from the WiFi event task → bracket with
 * the display lock. */
static void wifi_ui_refresh_scan_list(void)
{
    wifi_setup_network_t nets[WIFI_SETUP_MAX_SCAN_RESULTS];
    size_t n = wifi_setup_get_scan_results(nets, WIFI_SETUP_MAX_SCAN_RESULTS);

    lv_obj_t *const rows[]  = {
        objects.wifi_net_0, objects.wifi_net_1, objects.wifi_net_2, objects.wifi_net_3,
        objects.wifi_net_4, objects.wifi_net_5, objects.wifi_net_6, objects.wifi_net_7,
    };
    lv_obj_t *const ssids[] = {
        objects.wifi_net_ssid_0, objects.wifi_net_ssid_1, objects.wifi_net_ssid_2, objects.wifi_net_ssid_3,
        objects.wifi_net_ssid_4, objects.wifi_net_ssid_5, objects.wifi_net_ssid_6, objects.wifi_net_ssid_7,
    };
    lv_obj_t *const locks[] = {
        objects.wifi_net_lock_0, objects.wifi_net_lock_1, objects.wifi_net_lock_2, objects.wifi_net_lock_3,
        objects.wifi_net_lock_4, objects.wifi_net_lock_5, objects.wifi_net_lock_6, objects.wifi_net_lock_7,
    };
    const int row_cap = sizeof(rows) / sizeof(rows[0]);

    bsp_display_lock(0);
    for (int i = 0; i < row_cap; i++) {
        if (i < (int)n) {
            lv_label_set_text(ssids[i], nets[i].ssid);
            wifi_ui_paint_bars(i, nets[i].bars);
            /* fa-lock = U+F023, fa-lock-open = U+F09C (UTF-8). */
            lv_label_set_text(locks[i], nets[i].locked ? "\xEF\x80\xA3" : "\xEF\x82\x9C");
            lv_obj_clear_flag(rows[i], LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(rows[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
    if (objects.wifi_scan_spinner) lv_obj_add_flag(objects.wifi_scan_spinner, LV_OBJ_FLAG_HIDDEN);
    if (objects.wifi_scan_status) {
        lv_label_set_text(objects.wifi_scan_status,
                          n == 0 ? "No networks found. Tap Scan again." : "");
    }
    bsp_display_unlock();
}

static void wifi_ui_show_scanning(void)
{
    bsp_display_lock(0);
    if (objects.wifi_scan_spinner) lv_obj_clear_flag(objects.wifi_scan_spinner, LV_OBJ_FLAG_HIDDEN);
    if (objects.wifi_scan_status)  lv_label_set_text(objects.wifi_scan_status, "Scanning\xE2\x80\xA6");
    bsp_display_unlock();
}

static void wifi_ui_set_status(const char *msg)
{
    if (!objects.wifi_scan_status) return;
    bsp_display_lock(0);
    if (objects.wifi_scan_spinner) lv_obj_add_flag(objects.wifi_scan_spinner, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text(objects.wifi_scan_status, msg);
    bsp_display_unlock();
}

/* Show / hide the "Connecting to <SSID>…" overlay used during the silent
 * auto-reconnect path. */
static void wifi_ui_show_connecting_overlay(const char *ssid)
{
    if (!objects.wifi_connecting_panel) return;
    bsp_display_lock(0);
    if (objects.wifi_connecting_ssid) lv_label_set_text(objects.wifi_connecting_ssid, ssid ? ssid : "");
    lv_obj_clear_flag(objects.wifi_connecting_panel, LV_OBJ_FLAG_HIDDEN);
    bsp_display_unlock();
}

static void wifi_ui_hide_connecting_overlay(void)
{
    if (!objects.wifi_connecting_panel) return;
    bsp_display_lock(0);
    lv_obj_add_flag(objects.wifi_connecting_panel, LV_OBJ_FLAG_HIDDEN);
    bsp_display_unlock();
}

/* Status-bar WiFi icon visibility. Shown when an IP is held (CONNECTED state),
 * hidden in every other state. Called from the WiFi event task.
 *
 * StatusBar is an EEZ Studio user widget instantiated on every pendant page,
 * so there are 8 separate icon objects to keep in sync. */
static void wifi_ui_set_status_icon(bool connected)
{
    lv_obj_t *const icons[] = {
        objects.page_dashboard_status_bar__status_wifi_icon,
        objects.page_jog_status_bar__status_wifi_icon,
        objects.page_run_status_bar__status_wifi_icon,
        objects.page_files_status_bar__status_wifi_icon,
        objects.page_spindle_status_bar__status_wifi_icon,
        objects.page_probe_status_bar__status_wifi_icon,
        objects.page_macros_status_bar__status_wifi_icon,
        objects.page_settings_status_bar__status_wifi_icon,
    };
    bsp_display_lock(0);
    for (size_t i = 0; i < sizeof(icons) / sizeof(icons[0]); i++) {
        if (!icons[i]) continue;
        if (connected) lv_obj_clear_flag(icons[i], LV_OBJ_FLAG_HIDDEN);
        else           lv_obj_add_flag(icons[i], LV_OBJ_FLAG_HIDDEN);
    }
    bsp_display_unlock();
}

/* Settings → Connection: saved SSID + state. Also drives the "Network" row
 * in the System section. */
static void wifi_ui_refresh_connection_display_locked(void)
{
    const pendant_config_t *cfg = pendant_config_get();
    const char *ssid = (cfg && cfg->wifi_ssid[0]) ? cfg->wifi_ssid : "—";

    char state_buf[40];
    switch (wifi_setup_get_state()) {
    case WIFI_SETUP_STATE_CONNECTED: {
        char ip_buf[20];
        wifi_setup_format_ip(ip_buf, sizeof(ip_buf));
        snprintf(state_buf, sizeof(state_buf), "Connected · %s", ip_buf);
        break;
    }
    case WIFI_SETUP_STATE_CONNECTING: strcpy(state_buf, "Connecting…"); break;
    case WIFI_SETUP_STATE_SCANNING:   strcpy(state_buf, "Scanning…"); break;
    case WIFI_SETUP_STATE_FAILED:     strcpy(state_buf, "Failed"); break;
    case WIFI_SETUP_STATE_IDLE:
    default:                           strcpy(state_buf, "Disconnected"); break;
    }

    if (objects.settings_conn_ssid_val) lv_label_set_text(objects.settings_conn_ssid_val, ssid);
    if (objects.settings_conn_state_val) lv_label_set_text(objects.settings_conn_state_val, state_buf);
    if (objects.settings_sys_net_val)   lv_label_set_text(objects.settings_sys_net_val, state_buf);
}
#endif

static void on_wifi_state(wifi_setup_state_t st, void *ctx)
{
    (void)ctx;
    ESP_LOGI(TAG, "wifi state -> %d", (int)st);
#if HAVE_UI
    /* Settings → Connection labels track the live WiFi state, not just the
     * app_state machine transitions. */
    app_state_refresh_connection_display();
#endif
    switch (st) {
    case WIFI_SETUP_STATE_IDLE:
        /* Scan finished (or driver settled) — refresh the row widgets. */
#if HAVE_UI
        wifi_ui_set_status_icon(false);
        if (s_state == APP_STATE_WIFI_SETUP) wifi_ui_refresh_scan_list();
#endif
        break;
    case WIFI_SETUP_STATE_SCANNING:
#if HAVE_UI
        wifi_ui_set_status_icon(false);
        if (s_state == APP_STATE_WIFI_SETUP) wifi_ui_show_scanning();
#endif
        break;
    case WIFI_SETUP_STATE_CONNECTED:
#if HAVE_UI
        wifi_ui_set_status_icon(true);
#endif
        /* Persist creds (in case the user just entered them) then advance. */
        if (s_state == APP_STATE_WIFI_CONNECTING) {
            app_state_set(APP_STATE_FLUID_CONNECT);
        }
        break;
    case WIFI_SETUP_STATE_FAILED:
#if HAVE_UI
        wifi_ui_set_status_icon(false);
#endif
        if (s_state == APP_STATE_WIFI_CONNECTING) {
#if HAVE_UI
            const char *msg;
            switch (wifi_setup_get_last_failure_reason()) {
            case WIFI_SETUP_FAIL_BAD_PASSWORD:
                msg = "Incorrect password. Try again or pick another network."; break;
            case WIFI_SETUP_FAIL_AP_NOT_FOUND:
                msg = "Network not in range. Rescan or pick another network."; break;
            case WIFI_SETUP_FAIL_TIMEOUT:
                msg = "Timed out joining. Check signal and try again."; break;
            default:
                msg = "Connection failed. Pick a network and try again."; break;
            }
            wifi_ui_set_status(msg);
#endif
            app_state_set(APP_STATE_WIFI_SETUP);
        }
        break;
    default:
        break;
    }
}

static void on_fluid_status(const fluidnc_status_t *st, void *ctx)
{
    (void)ctx;
    if (s_state == APP_STATE_FLUID_CONNECTING && st->state != FLUIDNC_STATE_DISCONNECTED
                                              && st->state != FLUIDNC_STATE_CONNECTING) {
        app_state_set(APP_STATE_PENDANT);
    }
}

esp_err_t app_state_init(void)
{
    /* Drivers up first. */
    wifi_setup_init(on_wifi_state, NULL);
    fluidnc_init(on_fluid_status, NULL);

    /* Initial branch: do we have saved WiFi? */
    if (pendant_config_has_wifi()) {
        const pendant_config_t *cfg = pendant_config_get();
        app_state_set(APP_STATE_WIFI_CONNECTING);
        return wifi_setup_connect(cfg->wifi_ssid, cfg->wifi_pass);
    }
    app_state_set(APP_STATE_WIFI_SETUP);
    return ESP_OK;
}

void app_state_set(app_state_t next)
{
    if (s_state == next) return;
    ESP_LOGI(TAG, "%d -> %d", (int)s_state, (int)next);
    s_state = next;

#if HAVE_UI
    switch (next) {
    case APP_STATE_BOOT:
        break;
    case APP_STATE_WIFI_SETUP:
        load_screen(objects.page_wifi_setup);
        wifi_ui_hide_connecting_overlay();
        if (objects.wifi_scan_list) {
            lv_obj_clear_flag(objects.wifi_scan_list, LV_OBJ_FLAG_HIDDEN);
        }
        if (objects.wifi_password_panel) {
            lv_obj_add_flag(objects.wifi_password_panel, LV_OBJ_FLAG_HIDDEN);
        }
        wifi_setup_scan_start();
        break;
    case APP_STATE_WIFI_CONNECTING: {
        load_screen(objects.page_wifi_setup);
        /* Hide any leftover entry surfaces so the overlay is the only thing
         * the user sees while we wait for the join. */
        if (objects.wifi_password_panel) {
            lv_obj_add_flag(objects.wifi_password_panel, LV_OBJ_FLAG_HIDDEN);
        }
        if (objects.wifi_scan_list) {
            lv_obj_add_flag(objects.wifi_scan_list, LV_OBJ_FLAG_HIDDEN);
        }
        /* Auto-reconnect path: show centered "Connecting to <SSID>…" overlay.
         * The manual path (user submitted password) also goes through here;
         * the overlay is fine either way. */
        const pendant_config_t *cfg = pendant_config_get();
        wifi_ui_show_connecting_overlay(cfg ? cfg->wifi_ssid : "");
        break;
    }
    case APP_STATE_FLUID_CONNECT:
        /* Auto-skip when we already have a working configuration. */
        if (pendant_config_has_fluid()) {
            app_state_set(APP_STATE_FLUID_CONNECTING);
            fluidnc_connect();
            return;
        }
        load_screen(objects.page_fluid_connect);
        break;
    case APP_STATE_FLUID_CONNECTING:
        load_screen(objects.page_fluid_connect);
        fluidnc_connect();
        break;
    case APP_STATE_PENDANT:
        load_screen(objects.page_dashboard);
        break;
    }
    app_state_refresh_connection_display();
#endif
}

app_state_t app_state_get(void) { return s_state; }

void app_state_refresh_connection_display(void)
{
#if HAVE_UI
    bsp_display_lock(0);
    wifi_ui_refresh_connection_display_locked();
    bsp_display_unlock();
#endif
}

void app_state_set_pendant_tab(int tab_id)
{
#if HAVE_UI
    if (s_state != APP_STATE_PENDANT) return;
    lv_obj_t *const screens[] = {
        objects.page_dashboard, objects.page_jog,    objects.page_run,    objects.page_files,
        objects.page_spindle,   objects.page_probe,  objects.page_macros, objects.page_settings,
    };
    if (tab_id < 0 || tab_id >= (int)(sizeof(screens) / sizeof(screens[0]))) return;
    load_screen(screens[tab_id]);
#else
    (void)tab_id;
#endif
}
