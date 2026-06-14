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
#include <string.h>
#include "esp_log.h"
#include "esp_event.h"
#include "bsp/display.h"

#include "app_state.h"
#include "fluidnc.h"
#include "pendant_config.h"
#include "wifi_setup.h"

static const char *TAG = "actions";

/* Read the integer userData attached to the originating widget. */
static int evt_user_data(lv_event_t *e)
{
    return (int)(intptr_t)lv_event_get_user_data(e);
}

/* ---------- Navigation ---------- */
void action_change_screen(lv_event_t *e)
{
    app_state_set_pendant_tab(evt_user_data(e));
}

void action_open_settings_tab(lv_event_t *e)
{
    /* TODO: swap the Settings sub-tab view (Machine/Connection/Motion/System). */
    ESP_LOGI(TAG, "settings sub-tab -> %d", evt_user_data(e));
}

/* ---------- Global chrome ---------- */
void action_hold_resume(lv_event_t *e) { (void)e; fluidnc_hold_resume(); }
void action_estop(lv_event_t *e)       { (void)e; fluidnc_estop(); }
void action_alarm_reset(lv_event_t *e) { (void)e; fluidnc_reset_alarm(); }

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
void action_set_wcs(lv_event_t *e)      { fluidnc_set_wcs(evt_user_data(e)); }
void action_set_units(lv_event_t *e)
{
    int ud = evt_user_data(e);
    pendant_units_t u = ud == 1 ? PENDANT_UNITS_INCH : PENDANT_UNITS_MM;
    pendant_config_set_units(u);
    fluidnc_set_units(u);
}
void action_set_jog_step(lv_event_t *e)
{
    /* TODO: track jog step index in a shared variable so action_jog can read it. */
    ESP_LOGI(TAG, "jog step idx -> %d", evt_user_data(e));
}
void action_jog(lv_event_t *e)
{
    int ud   = evt_user_data(e);
    int axis = ud / 2;              /* 0=X 1=Y 2=Z */
    int dir  = (ud & 1) ? -1 : +1;
    /* TODO: read current jog step + feed from config / UI state. */
    fluidnc_jog(axis, dir, 1.0f /* mm */, 1200.0f /* mm/min */);
}

/* ---------- Run ---------- */
void action_job_start(lv_event_t *e)   { (void)e; fluidnc_job_start(NULL); }
void action_job_stop(lv_event_t *e)    { (void)e; fluidnc_job_stop();      }

/* ---------- Files ---------- */
void action_file_select(lv_event_t *e)
{
    ESP_LOGI(TAG, "file selected idx=%d", evt_user_data(e));
    /* TODO: highlight the selected row in the file list and update the
     *       SELECTED card with the file's metadata. */
}
void action_file_load_run(lv_event_t *e) { (void)e; fluidnc_job_start(NULL); }
void action_file_refresh(lv_event_t *e)  { (void)e; fluidnc_refresh_files(); }

/* ---------- Spindle ---------- */
void action_toggle_spindle(lv_event_t *e)
{
    (void)e;
    const fluidnc_status_t *st = fluidnc_get_status();
    if (st->spindle_on) fluidnc_spindle_off();
    else                fluidnc_spindle_on(st->spindle_target);
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
    ESP_LOGI(TAG, "probe type -> %d", evt_user_data(e));
}
void action_probe_start(lv_event_t *e)
{
    (void)e;
    /* TODO: read probe-type and parameter cards from variables. */
    fluidnc_probe(0, 19.0f, 100.0f, 25.0f);
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

/* ---------- Settings toggles ---------- */
void action_toggle_soft_limits(lv_event_t *e)
{
    (void)e;
    pendant_config_set_soft_limits(!pendant_config_get()->soft_limits);
}
void action_toggle_hard_limits(lv_event_t *e)
{
    (void)e;
    pendant_config_set_hard_limits(!pendant_config_get()->hard_limits);
}
void action_toggle_home_on_boot(lv_event_t *e)
{
    (void)e;
    pendant_config_set_home_on_boot(!pendant_config_get()->home_on_boot);
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
    pendant_transport_t t = (pendant_transport_t)evt_user_data(e);
    pendant_config_set_fluid_transport(t);
}
void action_fluid_connect(lv_event_t *e)
{
    (void)e;
    /* TODO: read host textarea, persist, then advance the state machine. */
    app_state_set(APP_STATE_FLUID_CONNECTING);
}
void action_fluid_disconnect(lv_event_t *e)  { (void)e; fluidnc_disconnect(); }

#else /* !__has_include("ui/actions.h") */

/* EEZ Studio hasn't exported yet — empty translation unit. */
typedef int actions_placeholder;

#endif
