/*
 * Action handlers — implementations for every action declared in the
 * GUI/TrailCurrentFluidCNCPendant.eez-project file.
 *
 * EEZ Studio exports `extern void action_<Name>(lv_event_t *e)` declarations
 * to main/ui/actions.h on Build (Ctrl+B); the symbols are resolved here at
 * link time. Until the EEZ Studio export has been run, main/ui/actions.h
 * doesn't exist and this file does nothing. The build still succeeds because
 * nothing calls the handlers yet.
 *
 * userData (set on each widget's eventHandler in EEZ Studio) carries the
 * variant for actions that map many widgets to one handler — for example
 * ChangeScreen(userData=N) where N is the tab index.
 */

#if __has_include("ui/actions.h")

#include "ui/actions.h"
#include "ui/screens.h"
#include "ui/vars.h"
#include "lvgl.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "esp_event.h"
#include "nvs.h"
#include "bsp/display.h"
#include "bsp/esp-bsp.h"

#include "app_state.h"
#include "fluidnc.h"
#include "pendant_config.h"
#include "wifi_setup.h"

/* Jog step sizes (mm), indexed by the four jog_step_* buttons on the Jog
 * page. action_set_jog_step records the user's choice into s_jog_step_idx;
 * action_jog reads it. Default 1.0 mm (index 2) — the "RUN" middle preset
 * the .eez-project ships with the CHECKED state set. */
static const float JOG_STEPS_MM[4] = { 0.01f, 0.1f, 1.0f, 10.0f };
static int s_jog_step_idx = 2;

/* Probe type chosen via the probe_cyc_* selector. Default 0 = Z touch-off. */
static int s_probe_type_idx = 0;

/* Index into the controller's file listing the user most recently tapped.
 * -1 = no selection yet — action_file_load_run uses this to pass the right
 * file name to fluidnc_job_start. */
static int s_selected_file_idx = -1;

static const char *TAG = "actions";

#define USER_SETTINGS_NVS_NAMESPACE "user_settings"

/* Read the integer userData attached to the originating widget. */
static int evt_user_data(lv_event_t *e)
{
    return (int)(intptr_t)lv_event_get_user_data(e);
}

/* Move the LV_STATE_CHECKED highlight from whatever sibling currently has it
 * to `target`. Used by every mutually-exclusive selector group on the UI —
 * WCS, units, jog step, transport, probe cycle, file row, … — so a tap
 * visually moves the highlight and clears the previously-checked button.
 * Pass NULL to clear every button in the group (none selected). */
static void selector_swap(lv_obj_t *target, lv_obj_t *const *group, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if (!group[i]) continue;
        if (group[i] == target) lv_obj_add_state(group[i],   LV_STATE_CHECKED);
        else                    lv_obj_clear_state(group[i], LV_STATE_CHECKED);
    }
}

/* ---------- Navigation ---------- */
void action_change_screen(lv_event_t *e)
{
    app_state_set_pendant_tab(evt_user_data(e));
}

void action_open_settings_tab(lv_event_t *e)
{
    /* The 5 settings tabs in order, matched to the userData on each nav button:
     *   0 = Machine   1 = Connection   2 = Motion   3 = System   4 = Display
     *
     * Each tab has a content Panel (only one visible at a time) and a nav
     * Button (highlighted via LV_STATE_CHECKED for the active tab). */
    lv_obj_t *const panels[] = {
        objects.settings_panel_machine,
        objects.settings_panel_connection,
        objects.settings_panel_motion,
        objects.settings_panel_system,
        objects.settings_panel_display,
    };
    lv_obj_t *const buttons[] = {
        objects.settings_nav_machine,
        objects.settings_nav_connection,
        objects.settings_nav_motion,
        objects.settings_nav_system,
        objects.settings_nav_display,
    };
    const int idx = evt_user_data(e);
    if (idx < 0 || idx >= (int)(sizeof(panels)/sizeof(*panels))) return;
    for (size_t i = 0; i < sizeof(panels)/sizeof(*panels); i++) {
        if ((int)i == idx) {
            if (panels[i])  lv_obj_clear_flag(panels[i], LV_OBJ_FLAG_HIDDEN);
            if (buttons[i]) lv_obj_add_state(buttons[i], LV_STATE_CHECKED);
        } else {
            if (panels[i])  lv_obj_add_flag(panels[i], LV_OBJ_FLAG_HIDDEN);
            if (buttons[i]) lv_obj_clear_state(buttons[i], LV_STATE_CHECKED);
        }
    }
    ESP_LOGI(TAG, "settings sub-tab -> %d", idx);
}

/* ---------- Global chrome ---------- */
void action_hold_resume(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "[BTN] HOLD/RESUME tapped");
    fluidnc_hold_resume();
}
void action_estop(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "[BTN] E-STOP tapped");
    fluidnc_estop();
}
void action_alarm_reset(lv_event_t *e)
{
    (void)e;
    ESP_LOGI(TAG, "[BTN] alarm reset tapped");
    fluidnc_reset_alarm();
}

/* ---------- Dashboard ---------- */
void action_zero_axis(lv_event_t *e)
{
    int ud = evt_user_data(e);
    fluidnc_zero_axis(ud == 3 ? -1 : ud);
}

void action_home_all(lv_event_t *e) { (void)e; fluidnc_home_all(); }

void action_adjust_override(lv_event_t *e)
{
    int ud      = evt_user_data(e);
    int channel = ud >> 1;          /* 0=feed 1=rapid 2=spindle */
    int dir     = (ud & 1) ? +10 : -10;
    fluidnc_adjust_override(channel, dir);
}

void action_reset_override(lv_event_t *e)
{
    fluidnc_adjust_override(evt_user_data(e), 0);
}

/* ---------- Jog ---------- */
void action_set_wcs(lv_event_t *e)
{
    int ud = evt_user_data(e);
    lv_obj_t *const wcs[] = {
        objects.jog_wcs_g54, objects.jog_wcs_g55, objects.jog_wcs_g56,
        objects.jog_wcs_g57, objects.jog_wcs_g58, objects.jog_wcs_g59,
    };
    if (ud >= 0 && ud < (int)(sizeof(wcs)/sizeof(*wcs))) {
        selector_swap(wcs[ud], wcs, sizeof(wcs)/sizeof(*wcs));
    }
    fluidnc_set_wcs(ud);
}
void action_set_units(lv_event_t *e)
{
    int ud = evt_user_data(e);
    pendant_units_t u = ud == 1 ? PENDANT_UNITS_INCH : PENDANT_UNITS_MM;

    /* Units are surfaced in two places (Jog page + Settings → Machine).
     * Both pairs must end up CHECKED on the same side — so clear all four
     * first, then set the two targets directly. Using selector_swap in a
     * loop here would un-check the first target on the second iteration. */
    lv_obj_clear_state(objects.jog_units_mm,      LV_STATE_CHECKED);
    lv_obj_clear_state(objects.jog_units_in,      LV_STATE_CHECKED);
    lv_obj_clear_state(objects.settings_units_mm, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.settings_units_in, LV_STATE_CHECKED);
    if (u == PENDANT_UNITS_MM) {
        lv_obj_add_state(objects.jog_units_mm,      LV_STATE_CHECKED);
        lv_obj_add_state(objects.settings_units_mm, LV_STATE_CHECKED);
    } else {
        lv_obj_add_state(objects.jog_units_in,      LV_STATE_CHECKED);
        lv_obj_add_state(objects.settings_units_in, LV_STATE_CHECKED);
    }

    pendant_config_set_units(u);
    fluidnc_set_units(u);
}
void action_set_jog_step(lv_event_t *e)
{
    int ud = evt_user_data(e);
    lv_obj_t *const steps[] = {
        objects.jog_step_0, objects.jog_step_1, objects.jog_step_2, objects.jog_step_3,
    };
    if (ud >= 0 && ud < (int)(sizeof(steps)/sizeof(*steps))) {
        selector_swap(steps[ud], steps, sizeof(steps)/sizeof(*steps));
        s_jog_step_idx = ud;
        ESP_LOGI(TAG, "jog step idx -> %d (%.2f mm)", ud, JOG_STEPS_MM[ud]);
    }
}
void action_jog(lv_event_t *e)
{
    int ud   = evt_user_data(e);
    int axis = ud / 2;              /* 0=X 1=Y 2=Z */
    int dir  = (ud & 1) ? -1 : +1;
    float step = JOG_STEPS_MM[s_jog_step_idx];
    float feed = (float)get_var_default_jog_feed();
    if (feed < 1.0f) feed = 1200.0f;     /* sanity floor — never send F0 */
    fluidnc_jog(axis, dir, step, feed);
}

/* ---------- Run ---------- */
void action_job_start(lv_event_t *e)   { (void)e; fluidnc_job_start(NULL); }
void action_job_stop(lv_event_t *e)    { (void)e; fluidnc_job_stop();      }

/* ---------- Files ---------- */
/* File rows on PageFiles are now created dynamically in app_state.c — see
 * MAX_FILES + create_file_row_locked(). action_file_select reads the
 * controller's cached listing and updates the right-hand SELECTED card;
 * the visual "highlight one row" swap is delegated to app_state since it
 * owns the row pointer array. */
#define ACTIONS_MAX_FILES 8

void action_file_select(lv_event_t *e)
{
    int ud = evt_user_data(e);
    app_state_files_select_visual(ud);

    fluidnc_file_t files[ACTIONS_MAX_FILES];
    size_t n = fluidnc_get_files(files, sizeof(files) / sizeof(*files));
    if (ud < 0 || (size_t)ud >= n) {
        ESP_LOGW(TAG, "file_select idx=%d out of range (n=%u)", ud, (unsigned)n);
        return;
    }
    s_selected_file_idx = ud;

    /* Update the SELECTED card on the right side of the Files page. fluidnc
     * only exposes name+size+date today; runtime and line count stay "-"
     * until the real backend inspects the file or parses its header. */
    if (objects.files_sel_name) {
        lv_label_set_text(objects.files_sel_name, files[ud].name);
    }
    if (objects.files_det_bd_val) {
        char buf[16];
        uint32_t kb = (files[ud].size_bytes + 512) / 1024;
        if (kb >= 1024) snprintf(buf, sizeof(buf), "%.1f MB", kb / 1024.0f);
        else            snprintf(buf, sizeof(buf), "%u KB", (unsigned)kb);
        lv_label_set_text(objects.files_det_bd_val, buf);
    }
    if (objects.files_det_rt_val) lv_label_set_text(objects.files_det_rt_val, "-");
    if (objects.files_det_ln_val) lv_label_set_text(objects.files_det_ln_val, "-");
    ESP_LOGI(TAG, "file selected idx=%d name=%s", ud, files[ud].name);
}
void action_file_load_run(lv_event_t *e)
{
    (void)e;
    /* Pass the selected file name; backend resolves SD path. NULL means
     * "resume the currently loaded job" — fine when nothing is selected. */
    const char *name = NULL;
    if (s_selected_file_idx >= 0) {
        fluidnc_file_t files[ACTIONS_MAX_FILES];
        size_t n = fluidnc_get_files(files, sizeof(files) / sizeof(*files));
        if ((size_t)s_selected_file_idx < n) name = files[s_selected_file_idx].name;
    }
    fluidnc_job_start(name);
}
void action_file_refresh(lv_event_t *e)
{
    (void)e;
    fluidnc_refresh_files();
    app_state_refresh_files_display();
}

/* ---------- Spindle ---------- *
 * action_toggle_spindle is kept for the Dashboard's combined SPINDLE tile
 * (small icon button — toggles based on the cached spindle_on). The
 * Spindle page now uses two dedicated buttons (SpindleStart / SpindleStop)
 * so it never has to consult the cache — fixes the rapid START/STOP label
 * flip the user reported when FluidNC's status-report rotation alternates
 * presence of the A: accessory field. */
void action_toggle_spindle(lv_event_t *e)
{
    (void)e;
    const fluidnc_status_t *st = fluidnc_get_status();
    if (st->spindle_on) fluidnc_spindle_off();
    else                fluidnc_spindle_on(st->spindle_target);
}

void action_spindle_start(lv_event_t *e)
{
    (void)e;
    /* rpm=0 means "use current spindle_target" — set in the Spindle page
     * via the +/- buttons. fluidnc_spindle_on() expands rpm=0 to the
     * cached target. */
    fluidnc_spindle_on(0);
}

void action_spindle_stop(lv_event_t *e)
{
    (void)e;
    fluidnc_spindle_off();
}
void action_adjust_spindle_target(lv_event_t *e)
{
    fluidnc_spindle_target_delta(evt_user_data(e) == 1 ? +500 : -500);
}
void action_toggle_flood(lv_event_t *e) { (void)e; fluidnc_flood(!fluidnc_get_status()->flood); }
void action_toggle_mist(lv_event_t *e)  { (void)e; fluidnc_mist(!fluidnc_get_status()->mist);  }

/* ---------- Probe ---------- */
void action_set_probe_type(lv_event_t *e)
{
    int ud = evt_user_data(e);
    lv_obj_t *const types[] = {
        objects.probe_cyc_z, objects.probe_cyc_corner,
        objects.probe_cyc_center, objects.probe_cyc_tool,
    };
    if (ud >= 0 && ud < (int)(sizeof(types)/sizeof(*types))) {
        selector_swap(types[ud], types, sizeof(types)/sizeof(*types));
        s_probe_type_idx = ud;
        ESP_LOGI(TAG, "probe type -> %d", ud);
    }
}
void action_probe_start(lv_event_t *e)
{
    (void)e;
    /* Parameters live in the three info cards as text labels. atof() copes
     * with the "19.00" / "100" / "25" placeholders the .eez-project ships
     * with, and with anything the user later sets via a numeric keypad. */
    float plate  = atof(get_var_probe_plate_thickness());
    float feed   = atof(get_var_probe_feed());
    float travel = atof(get_var_probe_max_travel());
    if (plate  <= 0.0f) plate  = 19.0f;
    if (feed   <= 0.0f) feed   = 100.0f;
    if (travel <= 0.0f) travel = 25.0f;
    fluidnc_probe(s_probe_type_idx, plate, feed, travel);
}

/* ---------- Macros ---------- */
static const char *const k_macros[] = {
    "G53 G90 G0 Z0\nG53 G0 X0 Y0",         /* Go To Front  */
    "M6",                                   /* Tool Change  */
    "G38.2 Z-25 F100",                      /* Probe Z      */
    "M3 S8000\nG4 P60\nM5",                 /* Spindle Warm */
    "G10 L20 P1 X0 Y0 Z0",                  /* Set G54 Zero */
    "M3 S8000\nG4 P60\nM5",                 /* Spindle Warmup duplicate */
    "G53 G0 X-10 Y-10",                     /* Park Rear Right */
    "$X",                                   /* Unlock       */
};
void action_run_macro(lv_event_t *e)
{
    int ud = evt_user_data(e);
    if (ud < 0 || ud >= (int)(sizeof(k_macros) / sizeof(k_macros[0]))) return;
    fluidnc_send_line(k_macros[ud]);
}

/* ---------- Settings toggles ---------- *
 * LVGL flips the switch's LV_STATE_CHECKED automatically on touch and then
 * fires VALUE_CHANGED, so reading the state from the event target after the
 * flip is the source of truth — never invert pendant_config (it might be
 * stale relative to the displayed value, e.g. between boot and the first
 * config_init). */
static bool switch_state(lv_event_t *e)
{
    lv_obj_t *sw = lv_event_get_target(e);
    return sw && lv_obj_has_state(sw, LV_STATE_CHECKED);
}
void action_toggle_soft_limits(lv_event_t *e)
{
    pendant_config_set_soft_limits(switch_state(e));
}
void action_toggle_hard_limits(lv_event_t *e)
{
    pendant_config_set_hard_limits(switch_state(e));
}
void action_toggle_home_on_boot(lv_event_t *e)
{
    pendant_config_set_home_on_boot(switch_state(e));
}

/* ---------- WiFi flow ---------- */
/* SSID the user tapped — shared between select / submit handlers. */
static char s_selected_ssid[WIFI_SETUP_SSID_MAX] = {0};
static bool s_selected_locked = false;
static bool s_kb_events_bound = false;

/* The LVGL keyboard's special keys also raise events on the textarea:
 *   - LV_SYMBOL_OK (Enter) → LV_EVENT_READY → treat as Connect.
 *   - LV_SYMBOL_CLOSE      → LV_EVENT_CANCEL → treat as Cancel.
 * This lets the user dismiss or submit without reaching past the keyboard. */
static void wifi_pwd_textarea_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_READY)       action_wifi_password_submit(e);
    else if (code == LV_EVENT_CANCEL) action_wifi_back(e);
}

void action_wifi_scan(lv_event_t *e)         { (void)e; wifi_setup_scan_start(); }

void action_wifi_select_network(lv_event_t *e)
{
    int idx = evt_user_data(e);
    wifi_setup_network_t nets[WIFI_SETUP_MAX_SCAN_RESULTS];
    size_t n = wifi_setup_get_scan_results(nets, WIFI_SETUP_MAX_SCAN_RESULTS);
    if (idx < 0 || (size_t)idx >= n) return;

    strncpy(s_selected_ssid, nets[idx].ssid, sizeof(s_selected_ssid) - 1);
    s_selected_ssid[sizeof(s_selected_ssid) - 1] = '\0';
    s_selected_locked = nets[idx].locked;
    ESP_LOGI(TAG, "WiFi: user picked SSID=%s (locked=%d)", s_selected_ssid, (int)s_selected_locked);

    /* Open network → connect immediately, no password panel. */
    if (!s_selected_locked) {
        app_state_set(APP_STATE_WIFI_CONNECTING);
        wifi_setup_connect(s_selected_ssid, "");
        return;
    }

    /* Locked → swap scan list for password panel; show chosen SSID. */
    lv_label_set_text(objects.wifi_pwd_ssid, s_selected_ssid);
    lv_textarea_set_text(objects.wifi_pwd_input, "");
    lv_obj_add_flag(objects.wifi_scan_list, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(objects.wifi_password_panel, LV_OBJ_FLAG_HIDDEN);
    /* LVGL keyboards don't auto-bind — link it to the password textarea so
     * key taps land somewhere. Also focus the textarea so the cursor shows.
     * Keyboard alignment override (LV_ALIGN_DEFAULT) is set in the .eez-project
     * itself — see the keyboard() helper in tmp/gen_eez_project.py. */
    lv_keyboard_set_textarea(objects.wifi_pwd_keyboard, objects.wifi_pwd_input);
    lv_obj_add_state(objects.wifi_pwd_input, LV_STATE_FOCUSED);
    /* One-time binding: keyboard's Enter / OK fires LV_EVENT_READY on the
     * textarea, and the keyboard's Close key fires LV_EVENT_CANCEL — route
     * both to the same submit/back handlers we wire to the buttons below. */
    if (!s_kb_events_bound) {
        lv_obj_add_event_cb(objects.wifi_pwd_input, wifi_pwd_textarea_event_cb,
                            LV_EVENT_READY, NULL);
        lv_obj_add_event_cb(objects.wifi_pwd_input, wifi_pwd_textarea_event_cb,
                            LV_EVENT_CANCEL, NULL);
        s_kb_events_bound = true;
    }
}

void action_wifi_password_submit(lv_event_t *e)
{
    (void)e;
    if (s_selected_ssid[0] == '\0') {
        ESP_LOGW(TAG, "WiFi submit with no selected SSID");
        return;
    }
    const char *pwd = lv_textarea_get_text(objects.wifi_pwd_input);
    ESP_LOGI(TAG, "WiFi: connecting to %s", s_selected_ssid);

    /* Persist now; app_state's on_wifi_state() callback will clear creds on
     * failure if desired. */
    pendant_config_set_wifi(s_selected_ssid, pwd ? pwd : "");
    app_state_set(APP_STATE_WIFI_CONNECTING);
    wifi_setup_connect(s_selected_ssid, pwd ? pwd : "");
}

void action_wifi_forget(lv_event_t *e)
{
    (void)e;
    pendant_config_clear_wifi();
    wifi_setup_disconnect();
    /* Refresh the saved-network display so the user sees "—" + "Disconnected"
     * immediately, not a stale SSID until the next state transition. */
    app_state_refresh_connection_display();
}

void action_change_wifi(lv_event_t *e)
{
    (void)e;
    /* Drop the current link (if any) and bounce back to the WiFi setup screen
     * so the user can pick a new SSID. */
    wifi_setup_disconnect();
    app_state_set(APP_STATE_WIFI_SETUP);
}

void action_wifi_toggle_password_reveal(lv_event_t *e)
{
    (void)e;
    /* Flip the textarea's password mode and swap the eye / eye-slash icon. */
    bool now_password = lv_textarea_get_password_mode(objects.wifi_pwd_input);
    bool reveal = now_password;          /* if we were masking, now we reveal */
    lv_textarea_set_password_mode(objects.wifi_pwd_input, !reveal);
    /* fa-eye = U+F06E, fa-eye-slash = U+F070 (UTF-8). When revealed, show the
     * "eye-slash" icon (tap again to hide); when masked, show plain "eye". */
    lv_label_set_text(objects.wifi_pwd_reveal_icon,
                      reveal ? "\xEF\x81\xB0" : "\xEF\x81\xAE");
}

void action_wifi_back(lv_event_t *e)
{
    (void)e;
    /* Reverse of select: hide password panel, return to scan list. */
    lv_keyboard_set_textarea(objects.wifi_pwd_keyboard, NULL);
    lv_obj_clear_state(objects.wifi_pwd_input, LV_STATE_FOCUSED);
    lv_obj_add_flag(objects.wifi_password_panel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(objects.wifi_scan_list, LV_OBJ_FLAG_HIDDEN);
    s_selected_ssid[0] = '\0';
}
void action_wifi_skip_to_serial(lv_event_t *e)
{
    (void)e;
    /* User opted out of WiFi entirely. Skip past WIFI_SETUP and FLUID_CONNECT,
     * land on the pendant. They'll be using UART/USB serial transport. */
    ESP_LOGI(TAG, "WiFi setup skipped — serial-only mode");
    pendant_config_set_fluid_transport(PENDANT_TRANSPORT_UART);
    app_state_set(APP_STATE_PENDANT);
}

/* ---------- FluidNC connection ---------- */
void action_set_fluid_transport(lv_event_t *e)
{
    int ud = evt_user_data(e);
    lv_obj_t *const tports[] = {
        objects.fluid_tport_0, objects.fluid_tport_1, objects.fluid_tport_2,
    };
    if (ud >= 0 && ud < (int)(sizeof(tports)/sizeof(*tports))) {
        selector_swap(tports[ud], tports, sizeof(tports)/sizeof(*tports));
    }
    pendant_config_set_fluid_transport((pendant_transport_t)ud);
}
/* FluidConnect edit panel — fluid_edit_panel is a hidden overlay that
 * matches the WifiPassword layout: caption + heading + visible textarea +
 * slim keyboard + CANCEL/DONE buttons. The user taps either of the main-
 * page textareas (fluid_host_input / fluid_port_input) to bring it up;
 * on DONE the panel's input is copied back to the originating field.
 *
 * s_fluid_edit_field tracks which main-page field the panel is editing
 * (0 = host, 1 = port) so DONE knows where to write back. */
static int s_fluid_edit_field = -1;

static void fluid_edit_hide_locked(void)
{
    if (objects.fluid_edit_keyboard) {
        lv_keyboard_set_textarea(objects.fluid_edit_keyboard, NULL);
    }
    if (objects.fluid_edit_panel) {
        lv_obj_add_flag(objects.fluid_edit_panel, LV_OBJ_FLAG_HIDDEN);
    }
    s_fluid_edit_field = -1;
}

void action_fluid_connect(lv_event_t *e)
{
    (void)e;
    /* Read the two textareas on the FluidConnect page and persist them so the
     * state machine has a host/port to dial in APP_STATE_FLUID_CONNECTING.
     * Empty host is allowed (UART transport uses no host); empty port falls
     * back to the FluidNC default by transport (81 for WS 3.x, 23 telnet). */
    if (objects.fluid_host_input) {
        const char *host = lv_textarea_get_text(objects.fluid_host_input);
        if (host) pendant_config_set_fluid_host(host);
    }
    if (objects.fluid_port_input) {
        const char *port_s = lv_textarea_get_text(objects.fluid_port_input);
        if (port_s && port_s[0]) {
            long p = strtol(port_s, NULL, 10);
            if (p > 0 && p <= 65535) pendant_config_set_fluid_port((uint16_t)p);
        }
    }
    /* Hide the edit panel in case it's still up. */
    fluid_edit_hide_locked();
    app_state_set(APP_STATE_FLUID_CONNECTING);
}

/* User tapped the host or port input on the main FluidConnect view.
 * userData 0 = host (TEXT_LOWER keyboard), 1 = port (NUMBER keyboard).
 *
 * Opens the edit panel, populates its caption/label, pre-fills the panel
 * input with the current value of the tapped field, points the panel
 * keyboard at the panel's own textarea, and remembers which field is
 * being edited so DONE knows where to write back. */
void action_fluid_edit_field(lv_event_t *e)
{
    int ud = evt_user_data(e);
    if (!objects.fluid_edit_panel || !objects.fluid_edit_input
        || !objects.fluid_edit_keyboard) return;

    lv_obj_t *src = (ud == 1) ? objects.fluid_port_input
                              : objects.fluid_host_input;
    const char *label_text = (ud == 1) ? "Port" : "Host or IP";
    lv_keyboard_mode_t mode = (ud == 1) ? LV_KEYBOARD_MODE_NUMBER
                                        : LV_KEYBOARD_MODE_TEXT_LOWER;

    if (objects.fluid_edit_label) lv_label_set_text(objects.fluid_edit_label, label_text);
    lv_textarea_set_text(objects.fluid_edit_input,
                         src ? lv_textarea_get_text(src) : "");
    lv_keyboard_set_mode(objects.fluid_edit_keyboard, mode);
    lv_keyboard_set_textarea(objects.fluid_edit_keyboard, objects.fluid_edit_input);
    lv_obj_clear_flag(objects.fluid_edit_panel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_state(objects.fluid_edit_input, LV_STATE_FOCUSED);
    s_fluid_edit_field = ud;
}

/* DONE pressed (or Enter on the keyboard). Copy the panel input's text
 * back to whichever main-page field we were editing, then hide. */
void action_fluid_edit_done(lv_event_t *e)
{
    (void)e;
    if (!objects.fluid_edit_input) { fluid_edit_hide_locked(); return; }
    const char *val = lv_textarea_get_text(objects.fluid_edit_input);
    if (!val) val = "";

    if (s_fluid_edit_field == 0 && objects.fluid_host_input) {
        lv_textarea_set_text(objects.fluid_host_input, val);
    } else if (s_fluid_edit_field == 1 && objects.fluid_port_input) {
        lv_textarea_set_text(objects.fluid_port_input, val);
    }
    fluid_edit_hide_locked();
}

void action_fluid_kb_hide(lv_event_t *e) { (void)e; fluid_edit_hide_locked(); }
void action_fluid_disconnect(lv_event_t *e)  { (void)e; fluidnc_disconnect(); }

/* ---------- Display (Settings -> Display tab) ---------- */

/* Slider value drag generates many events — dedup the NVS write so we don't
 * commit on every pixel of movement. (Fireside pattern.) */
static int32_t last_persisted_brightness = -1;

void action_change_screen_brightness(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    /* Defensive floor: never accept a brightness so low that the screen
     * becomes invisible — the user would have no way to drag the slider
     * back up. 10/255 is comfortably dim but still readable. */
    if (value < 10) value = 10;
    bsp_display_brightness_set((int)value);
    set_var_screen_brightness(value);    /* updates the value label */

    if (value != last_persisted_brightness) {
        last_persisted_brightness = value;
        nvs_handle_t nvs;
        if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
            nvs_set_u8(nvs, "brightness", (uint8_t)value);
            nvs_commit(nvs);
            nvs_close(nvs);
        }
    }
}

void action_timeout_changed(lv_event_t *e)
{
    /* userData 0 = decrement, 1 = increment. Range 0..60 minutes
     * (0 means never blank). */
    int32_t v = get_var_screen_timeout_value();
    v += (evt_user_data(e) == 0) ? -1 : +1;
    if (v < 0)  v = 0;
    if (v > 60) v = 60;
    set_var_screen_timeout_value(v);

    nvs_handle_t nvs;
    if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
        nvs_set_i8(nvs, "timeout", (int8_t)v);
        nvs_commit(nvs);
        nvs_close(nvs);
    }
}

/* Slider value drag generates many events — dedup similarly. */
static int32_t last_persisted_jog_feed = -1;

void action_change_jog_feed_default(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(slider);
    set_var_default_jog_feed(value);    /* updates "1200 mm/min" label */

    if (value != last_persisted_jog_feed) {
        last_persisted_jog_feed = value;
        nvs_handle_t nvs;
        if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
            nvs_set_i16(nvs, "jog_feed", (int16_t)value);
            nvs_commit(nvs);
            nvs_close(nvs);
        }
    }
}

void action_change_theme(lv_event_t *e)
{
    int theme_index = evt_user_data(e);     /* 0 = Light, 1 = Dark */
    set_var_selected_theme(theme_index);    /* calls change_color_theme() + updates CHECKED */

    nvs_handle_t nvs;
    if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READWRITE, &nvs) == ESP_OK) {
        nvs_set_u8(nvs, "theme", (uint8_t)theme_index);
        nvs_commit(nvs);
        nvs_close(nvs);
    }
    ESP_LOGI(TAG, "theme -> %d", theme_index);
}

/* Settings -> Machine -> "Configure FluidNC Connection".
 * Loads PageFluidConnect without changing app_state — the pendant is still
 * running. The back button on PageFluidConnect returns to PageSettings
 * (ChangeScreen userData=7), and tapping CONNECT fires action_fluid_connect
 * which advances the state machine into FLUID_CONNECTING as before. */
void action_open_fluid_connect(lv_event_t *e)
{
    (void)e;
    if (objects.page_fluid_connect) {
        lv_scr_load(objects.page_fluid_connect);
    }
}

#else /* !__has_include("ui/actions.h") */

/* EEZ Studio hasn't exported yet — empty translation unit. */
typedef int actions_placeholder;

#endif
