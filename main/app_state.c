#include "app_state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "esp_netif.h"
#include "esp_app_desc.h"
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

/* Defined further down, next to the PENDANT_TAB_* ids it indexes. Declared here
 * because app_state_set() lands on the Dashboard before that point. */
static void dock_highlight_active_tab(int tab_id);
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
        /* The Network row is owned by wifi_ui_refresh_connection_display_
         * locked(), invoked above for every state change — don't write it
         * here too. */
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
 * placeholder widgets that never carry real data, and means the row count is
 * bounded only by the listing itself: files_list_card scrolls vertically, so
 * there is no fixed maximum anywhere in the path.
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
/* No fixed row count — the card scrolls, so the list holds exactly as many
 * files as the controller reports. Row widgets are allocated on demand and
 * kept for the pendant's lifetime (a refresh reuses them; a longer listing
 * grows the array). */
typedef struct {
    lv_obj_t *row;
    lv_obj_t *icon;   /* glyph swaps between file / folder / up-one-level */
    lv_obj_t *name;
    lv_obj_t *size;
    lv_obj_t *date;
} file_row_t;

/* --- Files page directory navigation ---------------------------------------
 * The controller hands back one flat, recursive listing of the whole card;
 * the pendant turns it into something browsable. s_files_cwd is the folder
 * currently on screen, relative to the card root ("" = root), and the rows
 * are a VIEW over the dispatcher's cache: one row per immediate child of
 * s_files_cwd, folders first, plus a ".." row when we are below the root.
 *
 * Because of that, a row index is no longer an index into
 * fluidnc_get_file() - everything that resolves a tap goes through
 * app_state_files_tap() instead. */
typedef struct {
    app_files_tap_t kind;                /* NAV (folder / up) or FILE */
    bool            is_up;               /* the ".." row, not a real folder */
    char            path[FLUIDNC_PATH_MAX];  /* target dir, or the file path */
    char            name[FLUIDNC_NAME_MAX];  /* what the name column shows */
    uint32_t        size_bytes;
    char            date[20];
} files_view_t;

static files_view_t *s_view     = NULL;
static size_t        s_view_n   = 0;   /* rows the current folder needs */
static size_t        s_view_cap = 0;
static char          s_files_cwd[FLUIDNC_PATH_MAX];
/* Set when the folder changes so the repaint knows to jump back to the top. */
static bool          s_files_cwd_changed = false;

/* FontAwesome glyphs, all inside the fa_22 subset the .eez-project builds:
 * file (U+F15C), folder (U+F07B), arrow-up (U+F062). */
#define FILES_GLYPH_FILE   "\xEF\x85\x9C"
#define FILES_GLYPH_FOLDER "\xEF\x81\xBB"
#define FILES_GLYPH_UP     "\xEF\x81\xA2"

/* Is `path` an immediate child of the folder on screen? Returns the child's
 * own name (a pointer into `path`) if so, else NULL. "jobs" is a child of the
 * root; "jobs/part.nc" is not - it belongs to "jobs". */
static const char *cwd_child(const char *path)
{
    size_t cl = strlen(s_files_cwd);
    if (cl > 0) {
        if (strncmp(path, s_files_cwd, cl) != 0 || path[cl] != '/') return NULL;
        path += cl + 1;
    }
    if (path[0] == '\0' || strchr(path, '/') != NULL) return NULL;
    return path;
}

static bool files_view_reserve(size_t need)
{
    if (need <= s_view_cap) return true;
    size_t cap = s_view_cap ? s_view_cap * 2 : 16;
    while (cap < need) cap *= 2;
    files_view_t *p = realloc(s_view, cap * sizeof(*p));
    if (!p) return false;
    s_view     = p;
    s_view_cap = cap;
    return true;
}

static void files_view_push(const files_view_t *v)
{
    if (!files_view_reserve(s_view_n + 1)) {
        ESP_LOGE(TAG, "file view: out of memory at %u rows", (unsigned)s_view_n);
        return;
    }
    s_view[s_view_n++] = *v;
}

/* Rebuild s_view from the dispatcher's cache for the current folder. */
static void files_build_view(void)
{
    s_view_n = 0;

    /* ".." first, so leaving a folder is always the top row. */
    if (s_files_cwd[0]) {
        files_view_t up;
        memset(&up, 0, sizeof(up));
        up.kind  = APP_FILES_TAP_NAV;
        up.is_up = true;
        /* Parent of the current folder; empty string means the card root. */
        const char *slash = strrchr(s_files_cwd, '/');
        if (slash) {
            size_t len = (size_t)(slash - s_files_cwd);
            if (len >= sizeof(up.path)) len = sizeof(up.path) - 1;
            memcpy(up.path, s_files_cwd, len);
            up.path[len] = '\0';
        }
        strlcpy(up.name, "..", sizeof(up.name));
        strlcpy(up.date, "UP", sizeof(up.date));
        files_view_push(&up);
    }

    /* Two passes so folders group above files without needing a sort. */
    size_t n = fluidnc_get_file_count();
    for (int want_dir = 1; want_dir >= 0; want_dir--) {
        for (size_t i = 0; i < n; i++) {
            fluidnc_file_t f;
            if (!fluidnc_get_file(i, &f)) continue;
            if (f.is_dir != (want_dir == 1)) continue;
            const char *child = cwd_child(f.path);
            if (!child) continue;
            files_view_t v;
            memset(&v, 0, sizeof(v));
            v.kind       = f.is_dir ? APP_FILES_TAP_NAV : APP_FILES_TAP_FILE;
            v.size_bytes = f.is_dir ? 0 : f.size_bytes;
            strlcpy(v.path, f.path, sizeof(v.path));
            strlcpy(v.name, child,  sizeof(v.name));
            strlcpy(v.date, f.is_dir ? "FOLDER" : f.date, sizeof(v.date));
            files_view_push(&v);
        }
    }
}

static file_row_t *s_file_rows   = NULL;
static size_t      s_file_rows_n = 0;   /* widgets allocated, not files shown */

/* Grow the row array to hold at least `need` rows. New slots are zeroed so
 * create_file_row_locked() can tell "not built yet" from "already built". */
static bool file_rows_reserve(size_t need)
{
    if (need <= s_file_rows_n) return true;
    file_row_t *p = realloc(s_file_rows, need * sizeof(*p));
    if (!p) return false;
    memset(p + s_file_rows_n, 0, (need - s_file_rows_n) * sizeof(*p));
    s_file_rows   = p;
    s_file_rows_n = need;
    return true;
}

/* Build a single file row. Must be called while the LVGL lock is held
 * (refresh_files_display_locked is called from app_state_refresh_files_display
 * which takes the lock around it). */
static void create_file_row_locked(size_t idx)
{
    if (idx >= s_file_rows_n || s_file_rows[idx].row) return;
    if (!objects.files_list_card) return;

    /* One-time setup of the card as a vertical scroller. EEZ Studio already
     * leaves LV_OBJ_FLAG_SCROLLABLE set on files_list_card (it clears the
     * elastic/momentum/chain flags but not SCROLLABLE), so all that's needed
     * is to pin the header widgets — they're children of the card and would
     * otherwise scroll away with the rows — and lock scrolling to one axis. */
    static bool s_card_scroll_ready = false;
    if (!s_card_scroll_ready) {
        lv_obj_set_scroll_dir(objects.files_list_card, LV_DIR_VER);
        /* A drag only scrolls an ancestor if the press landed on something
         * LVGL hit-tested, and lv_obj_hit_test() rejects any object without
         * LV_OBJ_FLAG_CLICKABLE — which EEZ Studio clears on this card.
         * Rows are buttons so dragging one chains up here fine, but drags
         * starting in the gaps between rows (or below the last row) would
         * hit nothing and the list would feel stuck. The card has no event
         * handler, so making it clickable only affects hit-testing. */
        lv_obj_add_flag(objects.files_list_card, LV_OBJ_FLAG_CLICKABLE);
        if (objects.files_caption) {
            lv_obj_add_flag(objects.files_caption, LV_OBJ_FLAG_FLOATING);
        }
        if (objects.files_count) {
            lv_obj_add_flag(objects.files_count, LV_OBJ_FLAG_FLOATING);
        }
        if (objects.files_spinner) {
            lv_obj_add_flag(objects.files_spinner, LV_OBJ_FLAG_FLOATING);
        }
        s_card_scroll_ready = true;
    }

    /* Row geometry mirrors the .eez-project: rows are 678×44, first at y=28,
     * 50-px vertical pitch. Inset 6 px from card edge to leave room for the
     * card's own padding + the CHECKED-state outline. */
    lv_obj_t *row = lv_btn_create(objects.files_list_card);
    add_style_btn_file_row(row);
    lv_obj_set_pos(row, 6, (lv_coord_t)(28 + idx * 50));
    lv_obj_set_size(row, 678, 44);
    /* Tap routes through the same EEZ Studio FileSelect action that the
     * static rows used; userData carries the row index. */
    lv_obj_add_event_cb(row, action_file_select, LV_EVENT_CLICKED,
                        (void *)(intptr_t)idx);
    s_file_rows[idx].row = row;

    /* Row icon - same position the .eez-project placed it. */
    lv_obj_t *icon = lv_label_create(row);
    add_style_icon_fa22(icon);
    lv_obj_set_pos(icon, 10, 9);
    lv_obj_set_size(icon, 26, 26);
    /* Glyph is set per repaint now - a row can hold a file, a folder, or the
     * ".." entry depending on which folder is on screen. */
    lv_label_set_text(icon, FILES_GLYPH_FILE);
    s_file_rows[idx].icon = icon;

    /* Name — long label, Montserrat 14 (matches EEZ local_font override). */
    lv_obj_t *name = lv_label_create(row);
    add_style_label_default(name);
    lv_obj_set_pos(name, 44, 15);
    lv_obj_set_size(name, 464, 14);
    lv_obj_set_style_text_font(name, &lv_font_montserrat_14,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    /* Real CAM output runs to 80+ characters ("strut_plate_front-T2__6_35mm
     * __1_4__SpeTool_O-flute_-_Makita_dial_1__10k_rpm_-1.nc"), which is far
     * wider than the 464 px this label gets. Ellipsise rather than letting
     * the text run under the size and date columns. */
    lv_label_set_long_mode(name, LV_LABEL_LONG_DOT);
    lv_label_set_text(name, "");
    s_file_rows[idx].name = name;

    /* Size — mono-mini already configures the mono_13 font via its style. */
    lv_obj_t *size = lv_label_create(row);
    add_style_label_mono_mini(size);
    lv_obj_set_pos(size, 508, 15);
    lv_obj_set_size(size, 80, 14);
    lv_label_set_text(size, "");
    s_file_rows[idx].size = size;

    /* Date — Montserrat 12 (smaller than name on purpose, like EEZ shipped). */
    lv_obj_t *date = lv_label_create(row);
    add_style_label_default(date);
    lv_obj_set_pos(date, 588, 15);
    lv_obj_set_size(date, 80, 14);
    lv_obj_set_style_text_font(date, &lv_font_montserrat_12,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(date, "");
    s_file_rows[idx].date = date;

    /* Hidden until refresh decides whether to show it. */
    lv_obj_add_flag(row, LV_OBJ_FLAG_HIDDEN);
}

/* Walk every dynamically-created row and toggle CHECKED so the visual
 * "selected row" follows the user's tap. Called by action_file_select. */
void app_state_files_select_visual(int idx)
{
    for (size_t i = 0; i < s_file_rows_n; i++) {
        if (!s_file_rows[i].row) continue;
        if (i == (size_t)idx) lv_obj_add_state(s_file_rows[i].row,   LV_STATE_CHECKED);
        else                  lv_obj_clear_state(s_file_rows[i].row, LV_STATE_CHECKED);
    }
}

/* Paint one row per entry in the folder currently on screen - folders first,
 * then files, with a ".." row on top when we are below the card root. Rows are
 * created lazily and the card scrolls, so nothing here caps the count. */
static void refresh_files_display_locked(void)
{
    files_build_view();
    size_t n = s_view_n;

    /* The listing has arrived (or we're painting cached state) - the
     * loading spinner's job is done either way. */
    if (objects.files_spinner) {
        lv_obj_add_flag(objects.files_spinner, LV_OBJ_FLAG_HIDDEN);
    }

    /* Grow the row array to fit. On allocation failure, paint what we can
     * rather than dropping the whole list - and say so, because a silently
     * short list is exactly the failure that hides a file from the user. */
    size_t shown = n;
    if (!file_rows_reserve(n)) {
        shown = s_file_rows_n;
        ESP_LOGE(TAG, "file rows: out of memory - showing %u of %u entries",
                 (unsigned)shown, (unsigned)n);
    }

    size_t n_dirs = 0, n_files = 0;
    for (size_t i = 0; i < s_file_rows_n; i++) {
        if (i < shown) {
            const files_view_t *v = &s_view[i];
            bool is_up  = v->is_up;
            bool is_dir = (v->kind == APP_FILES_TAP_NAV);
            if (is_dir && !is_up) n_dirs++;
            else if (!is_dir)     n_files++;

            if (!s_file_rows[i].row) create_file_row_locked(i);
            if (s_file_rows[i].icon) {
                lv_label_set_text(s_file_rows[i].icon,
                                  is_up  ? FILES_GLYPH_UP :
                                  is_dir ? FILES_GLYPH_FOLDER : FILES_GLYPH_FILE);
            }
            if (s_file_rows[i].name) lv_label_set_text(s_file_rows[i].name, v->name);
            if (s_file_rows[i].size) {
                if (is_dir) {
                    /* A folder has no size to report and FluidNC doesn't count
                     * what is inside one, so the column stays blank rather
                     * than claiming "0 KB". */
                    lv_label_set_text(s_file_rows[i].size, "");
                } else {
                    char buf[16];
                    uint32_t kb = (v->size_bytes + 512) / 1024;
                    if (kb >= 1024) snprintf(buf, sizeof(buf), "%.1f MB", kb / 1024.0f);
                    else            snprintf(buf, sizeof(buf), "%u KB", (unsigned)kb);
                    lv_label_set_text(s_file_rows[i].size, buf);
                }
            }
            if (s_file_rows[i].date) {
                lv_label_set_text(s_file_rows[i].date, v->date);
            }
            if (s_file_rows[i].row) lv_obj_clear_flag(s_file_rows[i].row, LV_OBJ_FLAG_HIDDEN);
        } else if (s_file_rows[i].row) {
            lv_obj_add_flag(s_file_rows[i].row, LV_OBJ_FLAG_HIDDEN);
        }
    }

    /* Scroll back to the top when the listing itself changes, or when the user
     * opens a different folder, so neither leaves the view stranded partway
     * down a now-shorter list. Deliberately NOT on every repaint: files_seq
     * also bumps on the storage-capacity lines, and yanking the view to the
     * top while the user is scrolling would be maddening. */
    static size_t s_last_painted_n = (size_t)-1;
    if (objects.files_list_card && (n != s_last_painted_n || s_files_cwd_changed)) {
        lv_obj_scroll_to_y(objects.files_list_card, 0, LV_ANIM_OFF);
    }
    s_last_painted_n    = n;
    s_files_cwd_changed = false;

    if (objects.files_count) {
        char buf[40];
        /* Report what this folder holds. Folders are counted separately: "5
         * files" on a card whose jobs are all one level down was the reading
         * that made the subdirectories look like they didn't exist. */
        if (n_dirs > 0) {
            snprintf(buf, sizeof(buf), "%u folder%s, %u file%s",
                     (unsigned)n_dirs, n_dirs == 1 ? "" : "s",
                     (unsigned)n_files, n_files == 1 ? "" : "s");
        } else {
            snprintf(buf, sizeof(buf), "%u file%s",
                     (unsigned)n_files, n_files == 1 ? "" : "s");
        }
        lv_label_set_text(objects.files_count, buf);
    }

    /* Caption doubles as the breadcrumb so the user can tell which folder the
     * rows belong to. Trimmed from the left when it won't fit - the deepest
     * components are the informative ones. */
    if (objects.files_caption) {
        if (s_files_cwd[0] == '\0') {
            lv_label_set_text(objects.files_caption, "SD CARD");
        } else {
            char buf[32];
            const char *cwd = s_files_cwd;
            size_t room = sizeof(buf) - strlen("SD CARD / ") - 1;
            if (strlen(cwd) > room) cwd += strlen(cwd) - room;
            snprintf(buf, sizeof(buf), "SD CARD / %s", cwd);
            lv_label_set_text(objects.files_caption, buf);
        }
    }

    /* Storage tile — pull cached SD capacity from the dispatcher. The
     * controller emits this as `[MSG:Total: X Used: Y]` during the SD
     * list reply (FluidNC 3.5+); until that arrives we show a hyphen so
     * the user knows the link is up but the controller hasn't reported.
     * The bar always lives in [0..100] so the 0–100 range we set in the
     * .eez-project is the right fit. */
    uint64_t total = 0, used = 0;
    bool have_storage = fluidnc_get_storage_info(&total, &used);
    if (objects.files_stg_val) {
        if (have_storage && total > 0) {
            char buf[40];
            double used_mb  = (double)used  / (1024.0 * 1024.0);
            double total_mb = (double)total / (1024.0 * 1024.0);
            if (total_mb >= 1024.0) {
                snprintf(buf, sizeof(buf), "%.2f / %.2f GB",
                         used_mb / 1024.0, total_mb / 1024.0);
            } else {
                snprintf(buf, sizeof(buf), "%.1f / %.1f MB", used_mb, total_mb);
            }
            lv_label_set_text(objects.files_stg_val, buf);
        } else {
            /* ASCII hyphen — the em-dash isn't in Montserrat's subset and
             * rendered as an empty box. */
            lv_label_set_text(objects.files_stg_val, "-");
        }
    }
    if (objects.files_stg_bar) {
        int32_t pct = 0;
        if (have_storage && total > 0) {
            pct = (int32_t)((used * 100ULL) / total);
            if (pct < 0)   pct = 0;
            if (pct > 100) pct = 100;
        }
        lv_bar_set_value(objects.files_stg_bar, pct, LV_ANIM_OFF);
    }
}

void app_state_refresh_files_display(void)
{
    bsp_display_lock(0);
    refresh_files_display_locked();
    bsp_display_unlock();
}

app_files_tap_t app_state_files_tap(int idx, fluidnc_file_t *out)
{
    if (idx < 0 || (size_t)idx >= s_view_n) return APP_FILES_TAP_NONE;
    const files_view_t *v = &s_view[idx];

    if (v->kind == APP_FILES_TAP_FILE) {
        if (out) {
            memset(out, 0, sizeof(*out));
            strlcpy(out->path, v->path, sizeof(out->path));
            strlcpy(out->name, v->name, sizeof(out->name));
            strlcpy(out->date, v->date, sizeof(out->date));
            out->size_bytes = v->size_bytes;
        }
        return APP_FILES_TAP_FILE;
    }

    /* A folder (or "..") - move there and repaint. v->path is already the
     * destination: the folder itself, or the parent for the ".." row. */
    strlcpy(s_files_cwd, v->path, sizeof(s_files_cwd));
    s_files_cwd_changed = true;
    app_state_files_select_visual(-1);
    refresh_files_display_locked();

    return APP_FILES_TAP_NAV;
}

void app_state_files_show_loading(void)
{
    bsp_display_lock(0);
    if (objects.files_count) {
        /* ASCII dots — Montserrat's built-in subset has no U+2026. */
        lv_label_set_text(objects.files_count, "Loading...");
    }
    if (objects.files_spinner) {
        lv_obj_clear_flag(objects.files_spinner, LV_OBJ_FLAG_HIDDEN);
    }
    /* Hide any rows still left over from the previous list so the user
     * doesn't see stale filenames during the fetch. The next
     * refresh_files_display_locked() pass re-shows the rows that are
     * still in the freshly-arrived list. */
    for (size_t i = 0; i < s_file_rows_n; i++) {
        if (s_file_rows[i].row) lv_obj_add_flag(s_file_rows[i].row, LV_OBJ_FLAG_HIDDEN);
    }
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

    /* Jog page FEED readout — the .eez-project bakes in "FEED 1200 mm/min"
     * as design-time text and nothing else writes it, so push a real 0
     * (planner idle) over it before the first status report lands. */
    jog_feed_label_update(0);

    /* MDI console (Run page) — keymap + textarea wiring lives with the rest
     * of the MDI code in actions.c. */
    mdi_console_init();

    /* Override +/- buttons — press-and-hold repeat, wired in actions.c. */
    override_buttons_init();

    /* Settings → System rows — push the vars.c defaults over the authored
     * placeholder text so the page never shows stale .eez-project copy. */
    set_var_fw_version(get_var_fw_version());
    set_var_controller_info(get_var_controller_info());
    /* Interface row doubles as the OTA receipt: the build timestamp is the
     * only way to confirm on-device that a WiFi update actually took. */
    {
        const esp_app_desc_t *app = esp_app_get_description();
        char ui_buf[40];
        snprintf(ui_buf, sizeof(ui_buf), "Built %s %s", app->date, app->time);
        set_var_ui_info(ui_buf);
    }
    /* Network row: owned by wifi_ui_refresh_connection_display_locked(),
     * whose "Disconnected" idle wording matches the authored placeholder. */

    /* Empty file list (none refreshed from controller yet). */
    app_state_refresh_files_display();

    /* FluidConnect host/port textareas. These are NOT vars.c-bound — they're
     * plain LVGL textareas whose contents EEZ Studio bakes in as placeholder
     * text. Nothing else pushes the saved config into them, so without this
     * the page comes up showing the .eez-project placeholder after every
     * reboot and the saved host looks lost. It isn't — pendant_config_init()
     * has already read it out of NVS by the time we get here. */
    {
        const pendant_config_t *cfg = pendant_config_get();
        bsp_display_lock(0);
        if (objects.fluid_host_input && cfg->fluid_host[0]) {
            lv_textarea_set_text(objects.fluid_host_input, cfg->fluid_host);
        }
        if (objects.fluid_port_input) {
            char port_buf[8];
            snprintf(port_buf, sizeof(port_buf), "%u", (unsigned)cfg->fluid_port);
            lv_textarea_set_text(objects.fluid_port_input, port_buf);
        }

        /* Transport selector. Two buttons form a CHECKED-state radio group
         * driven entirely from C (EEZ Studio owns the CHECKED styling).
         * action_set_fluid_transport paints the selection when the user
         * taps; this paints it at boot from the saved config. WebSocket is
         * retired — pendant_config migrates any stored value to telnet
         * before we get here. */
        const int sel = (int)cfg->fluid_transport;
        lv_obj_t *want = (sel == PENDANT_TRANSPORT_UART) ? objects.fluid_tport_0
                                                         : objects.fluid_tport_2;
        lv_obj_t *const tports[] = { objects.fluid_tport_0, objects.fluid_tport_2 };
        for (int i = 0; i < (int)(sizeof(tports)/sizeof(*tports)); i++) {
            if (!tports[i]) continue;
            if (tports[i] == want) lv_obj_add_state(tports[i],   LV_STATE_CHECKED);
            else                   lv_obj_clear_state(tports[i], LV_STATE_CHECKED);
        }

        bsp_display_unlock();
        ESP_LOGI(TAG, "FluidConnect fields prefilled — host=%s port=%u transport=%d",
                 cfg->fluid_host[0] ? cfg->fluid_host : "(empty)",
                 (unsigned)cfg->fluid_port, sel);
    }
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

    /* Jog page FEED readout — live rate, override already applied by the
     * controller. Reads 0 whenever the planner is idle. */
    jog_feed_label_update(st->feed);

    /* Spindle + coolant — Spindle page + Dashboard tile. */
    set_var_spindle_rpm(st->spindle_rpm);
    set_var_spindle_target(st->spindle_target);
    set_var_spindle_load(st->spindle_load);
    set_var_spindle_on(st->spindle_on);
    set_var_flood_on(st->flood);
    set_var_mist_on(st->mist);

    /* Status bar — pill label, WCS, hold label, mini DRO (8 instances each).
     * The pill background colour change per state is a follow-up that needs
     * a .eez-project edit (see Piece E in the plan).
     *
     * OFFLINE latch: when the controller drops, the transport auto-reconnects
     * in <5 s and the pill would flick back to IDLE before the user notices.
     * Hold OFFLINE on screen for at least OFFLINE_MIN_DISPLAY_MS so any drop
     * is unmistakably visible. The DRO numbers behind it can update during
     * the latch — that's fine, the pill is the alert channel here. */
    const char *new_pill = machine_state_text(st->state);
    static int64_t  s_offline_hold_until_us = 0;
    static const char *s_last_pill = "OFFLINE";
    const int64_t now_us = esp_timer_get_time();
    const int64_t OFFLINE_MIN_DISPLAY_MS = 3000;
    if (!strcmp(new_pill, "OFFLINE")) {
        s_offline_hold_until_us = now_us + OFFLINE_MIN_DISPLAY_MS * 1000;
        set_var_machine_state(new_pill);
        s_last_pill = "OFFLINE";
    } else if (now_us < s_offline_hold_until_us) {
        /* In the OFFLINE latch window — leave the pill alone. */
    } else {
        set_var_machine_state(new_pill);
        s_last_pill = new_pill;
    }
    (void)s_last_pill;
    set_var_active_wcs(st->wcs);
    set_var_units_label(st->units_inch ? "in" : "mm");
    set_var_hold_label(st->state == FLUIDNC_STATE_HOLD ? "RESUME" : "HOLD");

    /* Settings → System rows. Firmware comes from the controller's banner /
     * $I reply once it has identified itself; the controller row tracks the
     * live transport state. */
    if (st->fw_version[0]) set_var_fw_version(st->fw_version);
    if (st->state == FLUIDNC_STATE_DISCONNECTED) {
        set_var_controller_info("(controller offline)");
    } else {
        const pendant_config_t *pc = pendant_config_get();
        char cbuf[40];
        if (pc->fluid_transport == PENDANT_TRANSPORT_UART) {
            snprintf(cbuf, sizeof(cbuf), "Serial UART");
        } else {
            snprintf(cbuf, sizeof(cbuf), "Telnet %s:%u",
                     pc->fluid_host, (unsigned)pc->fluid_port);
        }
        set_var_controller_info(cbuf);
    }

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

    /* Probe pin indicator — dot turns "live" via LV_STATE_CHECKED (the
     * shared status_pill_dot style flips to the accent colour in that
     * state). Label flips between "Probe inactive" / "Probe TRIGGERED"
     * so the user has unambiguous text feedback when the probe makes
     * contact. */
    if (objects.probe_status_dot) {
        if (st->probe_active) lv_obj_add_state(objects.probe_status_dot,   LV_STATE_CHECKED);
        else                  lv_obj_clear_state(objects.probe_status_dot, LV_STATE_CHECKED);
    }
    if (objects.probe_status_lbl) {
        lv_label_set_text(objects.probe_status_lbl,
                          st->probe_active ? "Probe TRIGGERED" : "Probe inactive");
    }

    /* Alarm ribbon — visibility is driven by whether the text is non-empty.
     * The controller can enter ALARM via two paths:
     *   (a) a discrete "ALARM:N" line, which fills s_status.alarm_text in
     *       the dispatcher with a specific message, OR
     *   (b) a `<Alarm|...>` status report alone — no specific text.
     * Path (b) used to leave alarm_text empty, which hid the ribbon and
     * left the user with no visible RESET button. Fall back to a generic
     * message so the ribbon (and its RESET button) always appears whenever
     * the controller is in ALARM. */
    const char *ribbon_text = "";
    if (st->state == FLUIDNC_STATE_ALARM) {
        ribbon_text = (st->alarm_text[0] != '\0')
                          ? st->alarm_text
                          : "ALARM - tap RESET to clear";
    }
    set_var_alarm_text(ribbon_text);

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

    /* Grey out Load & Run whenever a new job can't be started. The gate that
     * actually matters is in fluidnc_job_start() - this is so the user can SEE
     * that the button is spent, instead of tapping it again and queueing a
     * duplicate pass. Appearance of the DISABLED state belongs to EEZ Studio;
     * C only sets the state. */
    if (objects.files_btn_load) {
        bool busy = st->job_running
                    || st->state == FLUIDNC_STATE_RUN
                    || st->state == FLUIDNC_STATE_HOLD
                    || st->state == FLUIDNC_STATE_HOMING;
        if (busy) lv_obj_add_state(objects.files_btn_load, LV_STATE_DISABLED);
        else      lv_obj_clear_state(objects.files_btn_load, LV_STATE_DISABLED);
    }

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

    /* First successful connect — kick off a controller-side $SD/List so
     * the dispatcher starts populating fresh file rows + storage info.
     * fluidnc_refresh_files() is a no-op in the mock backend. */
    if (just_connected) {
        fluidnc_refresh_files();
    }

    /* Repaint Files whenever the dispatcher signals fresh data — file list
     * completed, or a `[MSG: Total/Used]` line just landed. The dispatcher
     * bumps fluidnc_get_files_seq() on either event; we mirror its value
     * and only call into LVGL when it changes. Cheap, no callbacks. */
    static uint32_t s_last_files_seq = 0;
    uint32_t cur_seq = fluidnc_get_files_seq();
    if (cur_seq != s_last_files_seq) {
        s_last_files_seq = cur_seq;
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
        /* Dashboard is tab 0 - light its dock button so the very first screen
         * the user sees already shows which tab is active. */
        dock_highlight_active_tab(0);
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
#define PENDANT_TAB_COUNT     8

/* Highlight the active tab in the bottom dock.
 *
 * The dock is a user widget instanced on all 8 pendant screens, so each screen
 * carries its OWN 8 dock buttons and they are addressed per instance
 * (page_<screen>_dock__dock_btn_<tab>) - there is no single objects.dock_btn_x.
 * Every instance gets the same tab checked so whichever screen the user lands
 * on already shows the right highlight.
 *
 * C only sets the state; BtnDockInactive's MAIN/CHECKED in the .eez-project
 * supplies the look, and the button's checked text_color is inherited by the
 * dock label and icon (neither declares its own), so all three change together.
 */
static void dock_highlight_active_tab(int tab_id)
{
    lv_obj_t *const docks[][PENDANT_TAB_COUNT] = {
        { objects.page_dashboard_dock__dock_btn_dash, objects.page_dashboard_dock__dock_btn_jog, objects.page_dashboard_dock__dock_btn_run, objects.page_dashboard_dock__dock_btn_files, objects.page_dashboard_dock__dock_btn_spindle, objects.page_dashboard_dock__dock_btn_probe, objects.page_dashboard_dock__dock_btn_macros, objects.page_dashboard_dock__dock_btn_settings },
        { objects.page_jog_dock__dock_btn_dash, objects.page_jog_dock__dock_btn_jog, objects.page_jog_dock__dock_btn_run, objects.page_jog_dock__dock_btn_files, objects.page_jog_dock__dock_btn_spindle, objects.page_jog_dock__dock_btn_probe, objects.page_jog_dock__dock_btn_macros, objects.page_jog_dock__dock_btn_settings },
        { objects.page_run_dock__dock_btn_dash, objects.page_run_dock__dock_btn_jog, objects.page_run_dock__dock_btn_run, objects.page_run_dock__dock_btn_files, objects.page_run_dock__dock_btn_spindle, objects.page_run_dock__dock_btn_probe, objects.page_run_dock__dock_btn_macros, objects.page_run_dock__dock_btn_settings },
        { objects.page_files_dock__dock_btn_dash, objects.page_files_dock__dock_btn_jog, objects.page_files_dock__dock_btn_run, objects.page_files_dock__dock_btn_files, objects.page_files_dock__dock_btn_spindle, objects.page_files_dock__dock_btn_probe, objects.page_files_dock__dock_btn_macros, objects.page_files_dock__dock_btn_settings },
        { objects.page_spindle_dock__dock_btn_dash, objects.page_spindle_dock__dock_btn_jog, objects.page_spindle_dock__dock_btn_run, objects.page_spindle_dock__dock_btn_files, objects.page_spindle_dock__dock_btn_spindle, objects.page_spindle_dock__dock_btn_probe, objects.page_spindle_dock__dock_btn_macros, objects.page_spindle_dock__dock_btn_settings },
        { objects.page_probe_dock__dock_btn_dash, objects.page_probe_dock__dock_btn_jog, objects.page_probe_dock__dock_btn_run, objects.page_probe_dock__dock_btn_files, objects.page_probe_dock__dock_btn_spindle, objects.page_probe_dock__dock_btn_probe, objects.page_probe_dock__dock_btn_macros, objects.page_probe_dock__dock_btn_settings },
        { objects.page_macros_dock__dock_btn_dash, objects.page_macros_dock__dock_btn_jog, objects.page_macros_dock__dock_btn_run, objects.page_macros_dock__dock_btn_files, objects.page_macros_dock__dock_btn_spindle, objects.page_macros_dock__dock_btn_probe, objects.page_macros_dock__dock_btn_macros, objects.page_macros_dock__dock_btn_settings },
        { objects.page_settings_dock__dock_btn_dash, objects.page_settings_dock__dock_btn_jog, objects.page_settings_dock__dock_btn_run, objects.page_settings_dock__dock_btn_files, objects.page_settings_dock__dock_btn_spindle, objects.page_settings_dock__dock_btn_probe, objects.page_settings_dock__dock_btn_macros, objects.page_settings_dock__dock_btn_settings },
    };
    const size_t n_docks = sizeof(docks) / sizeof(docks[0]);
    for (size_t d = 0; d < n_docks; d++) {
        for (int t = 0; t < PENDANT_TAB_COUNT; t++) {
            lv_obj_t *btn = docks[d][t];
            if (!btn) continue;
            if (t == tab_id) lv_obj_add_state(btn,   LV_STATE_CHECKED);
            else             lv_obj_clear_state(btn, LV_STATE_CHECKED);
        }
    }
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
    dock_highlight_active_tab(tab_id);

    /* Opening the Files tab triggers a fresh listing from the controller so
     * the user sees current SD contents, not whatever was cached from the
     * boot-time refresh. The display repaint happens when the dispatcher
     * finishes collecting entries (it fires a status callback on the "ok"
     * that closes the listing reply). Show "Loading…" in the meantime so
     * the user knows the page is alive while the round-trip completes. */
    if (tab_id == PENDANT_TAB_FILES) {
        fluidnc_refresh_files();
        app_state_files_show_loading();
    }
#else
    (void)tab_id;
#endif
}
