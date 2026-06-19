#include "app_state.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "esp_timer.h"
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
#  include "ui/vars.h"
#  include "ui/styles.h"
#  include "ui/actions.h"
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
    /* Plain ASCII — LVGL's built-in Montserrat subset doesn't include U+2026 ellipsis. */
    if (objects.wifi_scan_status)  lv_label_set_text(objects.wifi_scan_status, "Scanning...");
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
    /* Plain ASCII placeholder — Montserrat built-in doesn't have U+2014 em-dash. */
    const char *ssid = (cfg && cfg->wifi_ssid[0]) ? cfg->wifi_ssid : "(none)";

    char state_buf[40];
    switch (wifi_setup_get_state()) {
    case WIFI_SETUP_STATE_CONNECTED: {
        char ip_buf[20];
        wifi_setup_format_ip(ip_buf, sizeof(ip_buf));
        /* "Connected | IP" — pipe instead of U+00B7 middle dot (missing from Montserrat). */
        snprintf(state_buf, sizeof(state_buf), "Connected | %s", ip_buf);
        break;
    }
    case WIFI_SETUP_STATE_CONNECTING: strcpy(state_buf, "Connecting..."); break;
    case WIFI_SETUP_STATE_SCANNING:   strcpy(state_buf, "Scanning..."); break;
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
        /* WiFi just came up. Skip the FluidConnect onboarding screen — the
         * user reaches it via Settings → Machine → "Configure FluidNC
         * Connection" when they want to set it up. When a controller config
         * is already saved, kick off the connection in the background so the
         * controller is ready by the time the user starts using the dock.
         * on_fluid_status() is a no-op while s_state == PENDANT, so the
         * connection completes silently. */
        if (s_state == APP_STATE_WIFI_CONNECTING) {
            app_state_set(APP_STATE_PENDANT);
            if (pendant_config_has_fluid()) fluidnc_connect();
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

#if HAVE_UI
/* Format an axis position into "0.000" (mm) / "0.0000" (inch). 4 dp for inch
 * matches the FluidNC default $13 reporting precision, 3 dp for mm matches
 * the grbl realtime status report. */
static void format_axis(char *buf, size_t n, float v, bool inch)
{
    snprintf(buf, n, inch ? "%.4f" : "%.3f", v);
}

/* Format an mm/sec elapsed/eta value into MM:SS or HH:MM:SS. */
static void format_hms(char *buf, size_t n, uint32_t seconds)
{
    uint32_t h = seconds / 3600;
    uint32_t m = (seconds % 3600) / 60;
    uint32_t s = seconds % 60;
    if (h > 0) snprintf(buf, n, "%02u:%02u:%02u", (unsigned)h, (unsigned)m, (unsigned)s);
    else       snprintf(buf, n, "%02u:%02u",                 (unsigned)m, (unsigned)s);
}

/* Map fluidnc_state_t to the pill text the UI shows. */
static const char *machine_state_text(fluidnc_state_t s)
{
    switch (s) {
    case FLUIDNC_STATE_IDLE:         return "IDLE";
    case FLUIDNC_STATE_RUN:          return "RUN";
    case FLUIDNC_STATE_HOLD:         return "HOLD";
    case FLUIDNC_STATE_JOG:          return "JOG";
    case FLUIDNC_STATE_HOMING:       return "HOMING";
    case FLUIDNC_STATE_ALARM:        return "ALARM";
    case FLUIDNC_STATE_CONNECTING:   return "CONN...";
    case FLUIDNC_STATE_DISCONNECTED:
    default:                          return "OFFLINE";
    }
}

/* --- Dynamic file rows ----------------------------------------------------
 *
 * Rows on PageFiles aren't authored in EEZ Studio — they're built here in C,
 * one per file the controller reports. This keeps the .eez-project free of
 * placeholder widgets that never carry real data, and means MAX_FILES (and
 * scrolling, eventually) can change without an .eez-project edit.
 *
 * Geometry, styles, and per-label font overrides match what the EEZ Studio
 * source used to ship. Styles are applied through the add_style_*() helpers
 * EEZ Studio exports into ui/styles.h, so any theme / palette / radius /
 * border change made in EEZ Studio still flows through.
 *
 * Built lazily inside files_list_card on the first refresh that finds the
 * parent populated (i.e. once ui_init has run). Rows persist for the
 * pendant's lifetime; refresh just shows/hides them and updates the label
 * text per the current fluidnc_get_files() result. */
#define MAX_FILES 8

static lv_obj_t *s_file_row[MAX_FILES];
static lv_obj_t *s_file_row_name[MAX_FILES];
static lv_obj_t *s_file_row_size[MAX_FILES];
static lv_obj_t *s_file_row_date[MAX_FILES];

/* Build a single file row. Must be called while the LVGL lock is held
 * (refresh_files_display_locked is called from app_state_refresh_files_display
 * which takes the lock around it). */
static void create_file_row_locked(int idx)
{
    if (idx < 0 || idx >= MAX_FILES || s_file_row[idx]) return;
    if (!objects.files_list_card) return;

    /* Row geometry mirrors the .eez-project: rows are 678×44, first at y=28,
     * 50-px vertical pitch. Inset 6 px from card edge to leave room for the
     * card's own padding + the CHECKED-state outline. */
    lv_obj_t *row = lv_btn_create(objects.files_list_card);
    add_style_btn_file_row(row);
    lv_obj_set_pos(row, 6, 28 + idx * 50);
    lv_obj_set_size(row, 678, 44);
    /* Tap routes through the same EEZ Studio FileSelect action that the
     * static rows used; userData carries the row index. */
    lv_obj_add_event_cb(row, action_file_select, LV_EVENT_CLICKED,
                        (void *)(intptr_t)idx);
    s_file_row[idx] = row;

    /* File-type icon (FA "file" glyph U+F15C) — same position the .eez-project
     * placed it. */
    lv_obj_t *icon = lv_label_create(row);
    add_style_icon_fa22(icon);
    lv_obj_set_pos(icon, 10, 9);
    lv_obj_set_size(icon, 26, 26);
    lv_label_set_text(icon, "\xEF\x85\x9C");

    /* Name — long label, Montserrat 14 (matches EEZ local_font override). */
    lv_obj_t *name = lv_label_create(row);
    add_style_label_default(name);
    lv_obj_set_pos(name, 44, 15);
    lv_obj_set_size(name, 464, 14);
    lv_obj_set_style_text_font(name, &lv_font_montserrat_14,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(name, "");
    s_file_row_name[idx] = name;

    /* Size — mono-mini already configures the mono_13 font via its style. */
    lv_obj_t *size = lv_label_create(row);
    add_style_label_mono_mini(size);
    lv_obj_set_pos(size, 508, 15);
    lv_obj_set_size(size, 80, 14);
    lv_label_set_text(size, "");
    s_file_row_size[idx] = size;

    /* Date — Montserrat 12 (smaller than name on purpose, like EEZ shipped). */
    lv_obj_t *date = lv_label_create(row);
    add_style_label_default(date);
    lv_obj_set_pos(date, 588, 15);
    lv_obj_set_size(date, 80, 14);
    lv_obj_set_style_text_font(date, &lv_font_montserrat_12,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(date, "");
    s_file_row_date[idx] = date;

    /* Hidden until refresh decides whether to show it. */
    lv_obj_add_flag(row, LV_OBJ_FLAG_HIDDEN);
}

/* Walk every dynamically-created row and toggle CHECKED so the visual
 * "selected row" follows the user's tap. Called by action_file_select. */
void app_state_files_select_visual(int idx)
{
    for (int i = 0; i < MAX_FILES; i++) {
        if (!s_file_row[i]) continue;
        if (i == idx) lv_obj_add_state(s_file_row[i],   LV_STATE_CHECKED);
        else          lv_obj_clear_state(s_file_row[i], LV_STATE_CHECKED);
    }
}

/* Show up to MAX_FILES rows populated from the controller's cached file
 * listing; hide the rest. Creates rows lazily on first call so the panel
 * never holds widgets it doesn't need. */
static void refresh_files_display_locked(void)
{
    fluidnc_file_t files[MAX_FILES];
    size_t n = fluidnc_get_files(files, sizeof(files) / sizeof(*files));

    for (size_t i = 0; i < MAX_FILES; i++) {
        if (i < n) {
            if (!s_file_row[i]) create_file_row_locked((int)i);
            if (s_file_row_name[i]) lv_label_set_text(s_file_row_name[i], files[i].name);
            if (s_file_row_size[i]) {
                char buf[16];
                uint32_t kb = (files[i].size_bytes + 512) / 1024;
                if (kb >= 1024) snprintf(buf, sizeof(buf), "%.1f MB", kb / 1024.0f);
                else            snprintf(buf, sizeof(buf), "%u KB", (unsigned)kb);
                lv_label_set_text(s_file_row_size[i], buf);
            }
            if (s_file_row_date[i]) {
                lv_label_set_text(s_file_row_date[i],
                                  files[i].date[0] ? files[i].date : "");
            }
            if (s_file_row[i]) lv_obj_clear_flag(s_file_row[i], LV_OBJ_FLAG_HIDDEN);
        } else if (s_file_row[i]) {
            lv_obj_add_flag(s_file_row[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
    if (objects.files_count) {
        char buf[24];
        snprintf(buf, sizeof(buf), "%u file%s", (unsigned)n, n == 1 ? "" : "s");
        lv_label_set_text(objects.files_count, buf);
    }
}

void app_state_refresh_files_display(void)
{
    bsp_display_lock(0);
    refresh_files_display_locked();
    bsp_display_unlock();
}

/* Push the vars.c "no controller yet" defaults into every UI-bound widget.
 * Called once at boot, immediately after ui_init() — overwrites the
 * placeholder text baked into the .eez-project file so the user sees a
 * coherent "not connected" UI from the moment the screen lights up,
 * instead of stale demo data ("12000" target RPM, "bracket_v3.nc" file
 * name) that would mislead them about controller state. As soon as the
 * dispatcher delivers its first status report, every value gets
 * overwritten with live data. */
void app_state_paint_initial_state(void)
{
    /* Status bar — the most visible "I have / haven't talked to a
     * controller" signal. set_var_machine_state also fans the OFFLINE
     * pill colour out to all 8 instances. */
    set_var_machine_state(get_var_machine_state());
    set_var_active_wcs(get_var_active_wcs());
    set_var_units_label(get_var_units_label());
    set_var_hold_label(get_var_hold_label());
    set_var_clock_text(get_var_clock_text());

    /* DRO labels (work + machine + mini, all 0.000 by default). */
    set_var_work_dro_x(get_var_work_dro_x());
    set_var_work_dro_y(get_var_work_dro_y());
    set_var_work_dro_z(get_var_work_dro_z());
    set_var_machine_dro_x(get_var_machine_dro_x());
    set_var_machine_dro_y(get_var_machine_dro_y());
    set_var_machine_dro_z(get_var_machine_dro_z());
    set_var_mini_dro_x(get_var_mini_dro_x());
    set_var_mini_dro_y(get_var_mini_dro_y());
    set_var_mini_dro_z(get_var_mini_dro_z());

    /* Job card — "(no job loaded)" + 0% / --:-- defaults. */
    set_var_job_file(get_var_job_file());
    set_var_job_pct(get_var_job_pct());
    set_var_job_elapsed(get_var_job_elapsed());
    set_var_job_eta(get_var_job_eta());
    set_var_job_line(get_var_job_line());

    /* Spindle / coolant — target 0, RPM 0, load 0, all off. */
    set_var_spindle_target(get_var_spindle_target());
    set_var_spindle_rpm(get_var_spindle_rpm());
    set_var_spindle_load(get_var_spindle_load());
    set_var_spindle_on(get_var_spindle_on());
    set_var_flood_on(get_var_flood_on());
    set_var_mist_on(get_var_mist_on());

    /* Overrides — 100% on every channel. */
    set_var_feed_ov_pct(get_var_feed_ov_pct());
    set_var_rapid_ov_pct(get_var_rapid_ov_pct());
    set_var_spindle_ov_pct(get_var_spindle_ov_pct());

    /* Empty file list (none refreshed from controller yet). */
    app_state_refresh_files_display();
}
#endif /* HAVE_UI */

/* --- FluidConnect live status feedback ---------------------------------
 *
 * fluid_status_lbl and fluid_status_dot live on PageFluidConnect, just
 * above the BACK button. They surface "what is happening right now" so the
 * user gets confirmation after tapping CONNECT instead of staring at a
 * static label wondering whether anything is going on.
 *
 * Color tokens come from the Dark theme palette (the production look) —
 * StatusWarning yellow for "connecting", StatusSuccess green for
 * "connected", StatusDanger red for "failed", TextSecondary gray for the
 * idle / disconnected baseline. Setting the bg_color from C technically
 * crosses the "EEZ owns appearance" line, but the precedent is already
 * here (see wifi_ui_paint_bars) — dot/bar status indicators are state,
 * not chrome.
 *
 * A 10 s esp_timer guards against the case where the controller is
 * unreachable: if we're still in FLUID_CONNECTING when it fires we paint
 * "Connection failed" so the user can adjust host/port and retry. */
#define FLUID_DOT_CONNECTING 0xFFC107   /* yellow  — StatusWarning */
#define FLUID_DOT_CONNECTED  0x74FE00   /* green   — StatusSuccess */
#define FLUID_DOT_FAILED     0xFF5453   /* red     — StatusDanger  */
#define FLUID_DOT_IDLE       0xAAAAAA   /* gray    — TextSecondary */

static esp_timer_handle_t s_fluid_connect_timer = NULL;

static void fluid_status_paint_locked(const char *text, uint32_t dot_hex)
{
    if (objects.fluid_status_lbl) lv_label_set_text(objects.fluid_status_lbl, text);
    if (objects.fluid_status_dot) {
        lv_obj_set_style_bg_color(objects.fluid_status_dot, lv_color_hex(dot_hex),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(objects.fluid_status_dot, 255,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}

static void fluid_status_paint(const char *text, uint32_t dot_hex)
{
    bsp_display_lock(0);
    fluid_status_paint_locked(text, dot_hex);
    bsp_display_unlock();
}

static void fluid_connect_timeout_cb(void *arg)
{
    (void)arg;
    /* Only paint failure if we're still in the connecting state. If we've
     * already made it to PENDANT (or the user navigated away) the timer
     * firing is a stale callback — ignore. */
    if (s_state == APP_STATE_FLUID_CONNECTING) {
        ESP_LOGW(TAG, "fluidnc connect attempt timed out");
        fluid_status_paint("Connection failed - check host and port",
                           FLUID_DOT_FAILED);
    }
}

static void fluid_connect_timer_arm(void)
{
    if (!s_fluid_connect_timer) {
        esp_timer_create_args_t args = {
            .callback = fluid_connect_timeout_cb,
            .name     = "fluid_connect_to",
        };
        esp_timer_create(&args, &s_fluid_connect_timer);
    }
    esp_timer_stop(s_fluid_connect_timer);
    esp_timer_start_once(s_fluid_connect_timer, 10ULL * 1000 * 1000);   /* 10 s */
}

static void fluid_connect_timer_disarm(void)
{
    if (s_fluid_connect_timer) esp_timer_stop(s_fluid_connect_timer);
}

static void on_fluid_status(const fluidnc_status_t *st, void *ctx)
{
    (void)ctx;
    /* Connect → pendant gate. Fires once on the first IDLE/RUN reply. */
    bool just_connected = false;
    if (s_state == APP_STATE_FLUID_CONNECTING && st->state != FLUIDNC_STATE_DISCONNECTED
                                              && st->state != FLUIDNC_STATE_CONNECTING) {
        /* Brief "Connected" flash before the screen switches — the user
         * sees green confirmation, then lands on the Dashboard. */
        fluid_status_paint("Connected", FLUID_DOT_CONNECTED);
        fluid_connect_timer_disarm();
        app_state_set(APP_STATE_PENDANT);
        just_connected = true;
    } else if (s_state == APP_STATE_FLUID_CONNECTING
               && st->state == FLUIDNC_STATE_DISCONNECTED) {
        /* WebSocket failed to open (wrong host, unreachable, etc.) —
         * surface immediately; don't wait for the 10 s timer. */
        ESP_LOGW(TAG, "fluidnc transport reported DISCONNECTED during connect");
        fluid_status_paint("Connection failed - check host and port",
                           FLUID_DOT_FAILED);
        fluid_connect_timer_disarm();
    }

    /* Reconnect watch — when the controller drops while the user is on the
     * pendant pages, the WebSocket / UART transport already retries on its
     * own internal schedule (5 s default for esp_websocket_client). Our job
     * is just to log the drop and NOT layer extra reconnects on top —
     * earlier versions did, which produced a tight log-spam loop when the
     * controller was unreachable. fluidnc_connect() on an already-running
     * dispatcher is a no-op for the transport but spams two log lines per
     * tick, so we let the transport handle re-establishment. */
    static fluidnc_state_t s_last_state = FLUIDNC_STATE_DISCONNECTED;
    if (s_state == APP_STATE_PENDANT
        && st->state == FLUIDNC_STATE_DISCONNECTED
        && s_last_state != FLUIDNC_STATE_DISCONNECTED) {
        ESP_LOGW(TAG, "controller dropped — transport will retry on its own");
    }
    s_last_state = st->state;

#if HAVE_UI
    /* Overrides — the +/- buttons read these back to render the bars. */
    set_var_feed_ov_pct(st->feed_ov);
    set_var_rapid_ov_pct(st->rapid_ov);
    set_var_spindle_ov_pct(st->spindle_ov);

    /* Spindle + coolant — Spindle page + Dashboard tile. */
    set_var_spindle_rpm(st->spindle_rpm);
    set_var_spindle_target(st->spindle_target);
    set_var_spindle_load(st->spindle_load);
    set_var_spindle_on(st->spindle_on);
    set_var_flood_on(st->flood);
    set_var_mist_on(st->mist);

    /* Status bar — pill label, WCS, hold label, mini DRO (8 instances each).
     * The pill background colour change per state is a follow-up that needs
     * a .eez-project edit (see Piece E in the plan). */
    set_var_machine_state(machine_state_text(st->state));
    set_var_active_wcs(st->wcs);
    set_var_units_label(st->units_inch ? "in" : "mm");
    set_var_hold_label(st->state == FLUIDNC_STATE_HOLD ? "RESUME" : "HOLD");

    /* DRO labels — work + machine + mini all driven from the same values. */
    char buf[16];
    format_axis(buf, sizeof(buf), st->wpos.x, st->units_inch);
    set_var_work_dro_x(buf); set_var_mini_dro_x(buf);
    format_axis(buf, sizeof(buf), st->wpos.y, st->units_inch);
    set_var_work_dro_y(buf); set_var_mini_dro_y(buf);
    format_axis(buf, sizeof(buf), st->wpos.z, st->units_inch);
    set_var_work_dro_z(buf); set_var_mini_dro_z(buf);
    format_axis(buf, sizeof(buf), st->mpos.x, st->units_inch); set_var_machine_dro_x(buf);
    format_axis(buf, sizeof(buf), st->mpos.y, st->units_inch); set_var_machine_dro_y(buf);
    format_axis(buf, sizeof(buf), st->mpos.z, st->units_inch); set_var_machine_dro_z(buf);

    /* Alarm ribbon — visibility is driven by whether the text is non-empty. */
    set_var_alarm_text(st->state == FLUIDNC_STATE_ALARM ? st->alarm_text : "");

    /* Job — Dashboard job card + Run header. Elapsed / ETA are derived from
     * a job-start timestamp captured here (the backend doesn't track them
     * yet; the real protocol can plumb them through when available). */
    static int64_t s_job_start_us = 0;
    static bool    s_job_was_running = false;
    if (st->job_running && !s_job_was_running) {
        s_job_start_us = esp_timer_get_time();
    }
    if (!st->job_running && s_job_was_running) {
        s_job_start_us = 0;
    }
    s_job_was_running = st->job_running;

    set_var_job_file(st->job_file);
    set_var_job_pct((int32_t)st->job_progress_pct);
    set_var_job_line(st->job_line);
    set_var_job_total(st->job_total);

    if (s_job_start_us > 0) {
        uint32_t elapsed_s = (uint32_t)((esp_timer_get_time() - s_job_start_us) / 1000000);
        format_hms(buf, sizeof(buf), elapsed_s);
        set_var_job_elapsed(buf);
        if (st->job_progress_pct > 1.0f) {
            uint32_t total_s = (uint32_t)((float)elapsed_s * 100.0f / st->job_progress_pct);
            uint32_t eta_s   = total_s > elapsed_s ? total_s - elapsed_s : 0;
            format_hms(buf, sizeof(buf), eta_s);
            set_var_job_eta(buf);
        } else {
            set_var_job_eta("--:--");
        }
    } else if (!st->job_running) {
        set_var_job_elapsed("00:00");
        set_var_job_eta("--:--");
    }

    /* First successful connect — populate the Files page once so the user
     * sees real listings instead of the placeholder rows baked in by the
     * .eez-project. fluidnc_refresh_files() is a no-op in the mock; the
     * real backend will (re)scan the controller's SD listing. */
    if (just_connected) {
        fluidnc_refresh_files();
        app_state_refresh_files_display();
    }
#else
    (void)just_connected;
#endif
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
    case APP_STATE_FLUID_CONNECTING: {
        load_screen(objects.page_fluid_connect);
        /* Paint immediate feedback so the user knows their CONNECT tap was
         * received and we're trying. The label updates again to "Connected"
         * (green) or "Connection failed" (red) once on_fluid_status hears
         * back from the dispatcher — or after the 10 s timeout fires. */
        const pendant_config_t *cfg = pendant_config_get();
        char buf[64];
        const char *where = (cfg && cfg->fluid_host[0]) ? cfg->fluid_host
                                                        : "controller";
        snprintf(buf, sizeof(buf), "Connecting to %s...", where);
        fluid_status_paint_locked(buf, FLUID_DOT_CONNECTING);
        fluid_connect_timer_arm();
        fluidnc_connect();
        break;
    }
    case APP_STATE_PENDANT:
        load_screen(objects.page_dashboard);
        fluid_connect_timer_disarm();
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

/* Dock tab indices into screens[] (and the userData on each dock button). */
#define PENDANT_TAB_DASHBOARD 0
#define PENDANT_TAB_JOG       1
#define PENDANT_TAB_RUN       2
#define PENDANT_TAB_FILES     3
#define PENDANT_TAB_SPINDLE   4
#define PENDANT_TAB_PROBE     5
#define PENDANT_TAB_MACROS    6
#define PENDANT_TAB_SETTINGS  7

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

    /* Opening the Files tab triggers a fresh listing from the controller so
     * the user sees current SD contents, not whatever was cached from the
     * boot-time refresh. The display repaint happens when the dispatcher
     * finishes collecting entries (it fires a status callback on the "ok"
     * that closes the listing reply). */
    if (tab_id == PENDANT_TAB_FILES) {
        fluidnc_refresh_files();
        app_state_refresh_files_display();
    }
#else
    (void)tab_id;
#endif
}
