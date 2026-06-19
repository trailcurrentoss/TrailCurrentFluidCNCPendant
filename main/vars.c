/*
 * Native global variable bridge.
 *
 * EEZ Studio declares one `set_var_<name>` / `get_var_<name>` pair per global
 * variable in main/ui/vars.h. The implementations live here. They are called
 * from C code (status callbacks, action handlers, …) any time the UI needs to
 * be refreshed.
 *
 * Two flavors of setter:
 *   - VAR_STRING / VAR_INT / VAR_BOOL — just cache the value. Used for vars
 *     that no LVGL widget binds to directly (or that are fanned out to many
 *     widgets via on_fluid_status's helpers).
 *   - Hand-written overlays — cache AND push the value into one or more
 *     LVGL widgets. Used wherever there's a clean 1:1 var-to-widget binding
 *     so the var setter is the single point that keeps the UI in sync.
 *
 * Per-instance fan-out (user-widget children like the status bar / alarm
 * ribbon, where one logical value drives 8 widget copies) is also handled
 * here in the appropriate setter — the alternative was to bounce through
 * app_state.c, but that just spreads the widget knowledge across two files.
 *
 * Threading: every setter takes bsp_display_lock so it's safe to call from
 * the WiFi / FluidNC tasks. Getters return cached values without locking.
 */

#if __has_include("ui/vars.h")

#include "ui/vars.h"
#include "ui/screens.h"
#include "lvgl.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bsp/display.h"

/* --- Cache. Keep small — only mirrors the values C originated. ---------- */
static struct {
    int32_t  wifi_state;
    char     wifi_ssid[33];
    char     wifi_ip[24];

    int32_t  fluid_state;
    char     fluid_host[65];
    int32_t  fluid_transport_index;

    char     machine_state[12];
    char     active_wcs[8];
    char     mini_dro_x[16], mini_dro_y[16], mini_dro_z[16];
    char     clock_text[12];
    char     hold_label[12];

    char     alarm_text[96];

    char     work_dro_x[16],    work_dro_y[16],    work_dro_z[16];
    char     machine_dro_x[16], machine_dro_y[16], machine_dro_z[16];
    char     units_label[6];

    int32_t  feed_ov_pct, rapid_ov_pct, spindle_ov_pct;

    char     job_file[64];
    int32_t  job_pct;
    char     job_elapsed[12], job_eta[12];
    int32_t  job_line, job_total;

    bool     spindle_on;
    int32_t  spindle_rpm, spindle_target, spindle_load;
    bool     flood_on, mist_on;

    char     probe_plate_thickness[12], probe_feed[12], probe_max_travel[12];

    char     fw_version[24], controller_info[40], ui_info[40], net_info[40];

    int32_t  screen_brightness;
    int32_t  screen_timeout_value;
    int32_t  default_jog_feed;
    int32_t  selected_theme;
} s_v = {
    /* Defaults are "pre-connect" values — they're what the UI shows before
     * any FluidNC status report has arrived. Anything that's normally
     * populated from controller telemetry starts as a no-data placeholder
     * (e.g. job_file "(no job loaded)") so the user can tell at a glance
     * that no real data is in play yet. As soon as the dispatcher delivers
     * a status report, set_var_* overwrites these with live values.
     *
     * IMPORTANT: every placeholder string must be renderable with the
     * built-in LVGL Montserrat subset (basic ASCII 0x20-0x7F). Avoid
     * "—" (em-dash, U+2014) and other Unicode punctuation — they show as
     * empty boxes. Use plain hyphen or parenthesised text instead. */
    .machine_state = "OFFLINE",
    .active_wcs    = "G54",
    .mini_dro_x    = "0.000",
    .mini_dro_y    = "0.000",
    .mini_dro_z    = "0.000",
    .work_dro_x    = "0.000",
    .work_dro_y    = "0.000",
    .work_dro_z    = "0.000",
    .machine_dro_x = "0.000",
    .machine_dro_y = "0.000",
    .machine_dro_z = "0.000",
    .units_label   = "mm",
    .feed_ov_pct   = 100,
    .rapid_ov_pct  = 100,
    .spindle_ov_pct= 100,
    .job_file      = "(no job loaded)",
    .job_elapsed   = "--:--",
    .job_eta       = "--:--",
    .hold_label    = "HOLD",
    .clock_text    = "--:--",
    .spindle_target= 0,                 /* user can dial this up in the Spindle page */
    .probe_plate_thickness = "19.00",
    .probe_feed            = "100",
    .probe_max_travel      = "25",
    .fw_version            = "(controller offline)",
    .controller_info       = "(controller offline)",
    .ui_info               = "LVGL 8.4 . 1024x600",
    .net_info              = "Not connected",
    .screen_brightness     = 180,
    .screen_timeout_value  = 5,
    .default_jog_feed      = 1200,
    .selected_theme        = 1,     /* 0 = Light (Default), 1 = Dark */
};

/* Macro generator for the four common variable kinds EEZ Studio emits.
 * Each macro defines get_var_<name> / set_var_<name>. */
#define VAR_STRING(NAME, FIELD)                                                  \
    const char *get_var_##NAME(void)            { return s_v.FIELD; }            \
    void        set_var_##NAME(const char *v)   {                                \
        bsp_display_lock(0);                                                     \
        strlcpy(s_v.FIELD, v ? v : "", sizeof(s_v.FIELD));                       \
        bsp_display_unlock();                                                    \
    }

#define VAR_INT(NAME, FIELD)                                                     \
    int32_t get_var_##NAME(void)              { return s_v.FIELD; }              \
    void    set_var_##NAME(int32_t v)         {                                  \
        bsp_display_lock(0);                                                     \
        s_v.FIELD = v;                                                           \
        bsp_display_unlock();                                                    \
    }

#define VAR_BOOL(NAME, FIELD)                                                    \
    bool get_var_##NAME(void)                 { return s_v.FIELD; }              \
    void set_var_##NAME(bool v)               {                                  \
        bsp_display_lock(0);                                                     \
        s_v.FIELD = v;                                                           \
        bsp_display_unlock();                                                    \
    }

/* --- WiFi gating -------------------------------------------------------- */
VAR_INT   (wifi_state,            wifi_state)
VAR_STRING(wifi_ssid,             wifi_ssid)
VAR_STRING(wifi_ip,               wifi_ip)

/* --- FluidNC connection ------------------------------------------------- */
VAR_INT   (fluid_state,           fluid_state)
VAR_STRING(fluid_host,            fluid_host)
VAR_INT   (fluid_transport_index, fluid_transport_index)

/* --- Status bar fan-out helpers ----------------------------------------- *
 * Eight pendant pages each instance the StatusBar / AlarmRibbon user widget,
 * so a single logical value (machine_state, mini_dro_x, …) drives eight
 * widget copies. The fan-out arrays below are the static lookup tables —
 * one per user-widget child — used by the setters that need them.
 *
 * Members are stable lv_obj_t* pointers exported by EEZ Studio; any null
 * entry (page export missing) is silently skipped by the setter loops. */

#define STATUS_BAR_FIELD(suffix)                                                  \
    {                                                                             \
        objects.page_dashboard_status_bar__##suffix,                              \
        objects.page_jog_status_bar__##suffix,                                    \
        objects.page_run_status_bar__##suffix,                                    \
        objects.page_files_status_bar__##suffix,                                  \
        objects.page_spindle_status_bar__##suffix,                                \
        objects.page_probe_status_bar__##suffix,                                  \
        objects.page_macros_status_bar__##suffix,                                 \
        objects.page_settings_status_bar__##suffix,                               \
    }
#define ALARM_FIELD(suffix)                                                       \
    {                                                                             \
        objects.page_dashboard_alarm__##suffix,                                   \
        objects.page_jog_alarm__##suffix,                                         \
        objects.page_run_alarm__##suffix,                                         \
        objects.page_files_alarm__##suffix,                                       \
        objects.page_spindle_alarm__##suffix,                                     \
        objects.page_probe_alarm__##suffix,                                       \
        objects.page_macros_alarm__##suffix,                                      \
        objects.page_settings_alarm__##suffix,                                    \
    }
#define STATUSBAR_FANOUT_TEXT(suffix, text)                                       \
    do {                                                                          \
        lv_obj_t *const _arr[] = STATUS_BAR_FIELD(suffix);                        \
        for (size_t _i = 0; _i < sizeof(_arr)/sizeof(*_arr); _i++) {              \
            if (_arr[_i]) lv_label_set_text(_arr[_i], (text) ? (text) : "");      \
        }                                                                         \
    } while (0)

/* --- Top status bar ----------------------------------------------------- */

/* machine_state — pill label text across all 8 instances. Also drives the
 * LV_STATE_* bits on the pill panel + the inner dot so the StatusPill /
 * StatusPillDot styles can colour-code the pill per state. State mapping
 * (must match the patch_status_pill_states() block in the Phase-2 .eez
 * patch — see tmp/patch_fluid_keyboard_and_pill.py):
 *     DEFAULT  = IDLE / CONNECTING / OFFLINE  (neutral text + transparent bg)
 *     CHECKED  = RUN / JOG                    (StatusSuccess, green)
 *     FOCUSED  = HOLD / HOMING                (StatusWarning, orange)
 *     DISABLED = ALARM                        (StatusDanger,  red) */
const char *get_var_machine_state(void) { return s_v.machine_state; }
void        set_var_machine_state(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.machine_state, v ? v : "", sizeof(s_v.machine_state));
    STATUSBAR_FANOUT_TEXT(status_pill_label, s_v.machine_state);

    /* Pick the right state bit. strcmp on the same strings the pump in
     * app_state.c's machine_state_text() emits — fragile if those strings
     * change, but they're co-located in the file so it's caught immediately. */
    lv_state_t st_bit = 0;
    if      (!strcmp(s_v.machine_state, "RUN")    || !strcmp(s_v.machine_state, "JOG"))    st_bit = LV_STATE_CHECKED;
    else if (!strcmp(s_v.machine_state, "HOLD")   || !strcmp(s_v.machine_state, "HOMING")) st_bit = LV_STATE_FOCUSED;
    else if (!strcmp(s_v.machine_state, "ALARM"))                                          st_bit = LV_STATE_DISABLED;
    const lv_state_t mask = LV_STATE_CHECKED | LV_STATE_FOCUSED | LV_STATE_DISABLED;

    lv_obj_t *const pills[] = STATUS_BAR_FIELD(status_pill);
    lv_obj_t *const dots[]  = STATUS_BAR_FIELD(status_pill_dot);
    for (size_t i = 0; i < sizeof(pills)/sizeof(*pills); i++) {
        if (pills[i]) { lv_obj_clear_state(pills[i], mask); if (st_bit) lv_obj_add_state(pills[i], st_bit); }
        if (dots[i])  { lv_obj_clear_state(dots[i],  mask); if (st_bit) lv_obj_add_state(dots[i],  st_bit); }
    }
    bsp_display_unlock();
}

const char *get_var_active_wcs(void) { return s_v.active_wcs; }
void        set_var_active_wcs(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.active_wcs, v ? v : "", sizeof(s_v.active_wcs));
    STATUSBAR_FANOUT_TEXT(status_wcs, s_v.active_wcs);
    bsp_display_unlock();
}

const char *get_var_mini_dro_x(void) { return s_v.mini_dro_x; }
void        set_var_mini_dro_x(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.mini_dro_x, v ? v : "", sizeof(s_v.mini_dro_x));
    STATUSBAR_FANOUT_TEXT(status_mini_x, s_v.mini_dro_x);
    bsp_display_unlock();
}
const char *get_var_mini_dro_y(void) { return s_v.mini_dro_y; }
void        set_var_mini_dro_y(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.mini_dro_y, v ? v : "", sizeof(s_v.mini_dro_y));
    STATUSBAR_FANOUT_TEXT(status_mini_y, s_v.mini_dro_y);
    bsp_display_unlock();
}
const char *get_var_mini_dro_z(void) { return s_v.mini_dro_z; }
void        set_var_mini_dro_z(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.mini_dro_z, v ? v : "", sizeof(s_v.mini_dro_z));
    STATUSBAR_FANOUT_TEXT(status_mini_z, s_v.mini_dro_z);
    bsp_display_unlock();
}

const char *get_var_clock_text(void) { return s_v.clock_text; }
void        set_var_clock_text(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.clock_text, v ? v : "", sizeof(s_v.clock_text));
    STATUSBAR_FANOUT_TEXT(status_clock, s_v.clock_text);
    bsp_display_unlock();
}

const char *get_var_hold_label(void) { return s_v.hold_label; }
void        set_var_hold_label(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.hold_label, v ? v : "", sizeof(s_v.hold_label));
    STATUSBAR_FANOUT_TEXT(status_hold_label, s_v.hold_label);
    bsp_display_unlock();
}

/* alarm_text — fans out to all 8 alarm text labels AND drives the ribbon's
 * hidden flag. Empty string hides the ribbon on every page; non-empty shows
 * it. The ribbon is layered at the top of each page, above the status bar. */
const char *get_var_alarm_text(void) { return s_v.alarm_text; }
void        set_var_alarm_text(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.alarm_text, v ? v : "", sizeof(s_v.alarm_text));
    bool show = s_v.alarm_text[0] != '\0';

    lv_obj_t *const texts[]   = ALARM_FIELD(alarm_text);
    lv_obj_t *const ribbons[] = ALARM_FIELD(alarm_ribbon_root);
    for (size_t i = 0; i < sizeof(texts)/sizeof(*texts); i++) {
        if (texts[i]) lv_label_set_text(texts[i], s_v.alarm_text);
        if (ribbons[i]) {
            if (show) lv_obj_clear_flag(ribbons[i], LV_OBJ_FLAG_HIDDEN);
            else      lv_obj_add_flag(ribbons[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
    bsp_display_unlock();
}

/* --- Dashboard / Jog DRO ------------------------------------------------ *
 * work_dro_* lives on the Dashboard (dash_dro_*) AND the Jog page
 * (jog_work_*). machine_dro_* only on the Jog page (Dashboard shows work
 * coords only). Each setter pushes to every widget bound to it. */
const char *get_var_work_dro_x(void) { return s_v.work_dro_x; }
void        set_var_work_dro_x(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.work_dro_x, v ? v : "", sizeof(s_v.work_dro_x));
    if (objects.dash_dro_x) lv_label_set_text(objects.dash_dro_x, s_v.work_dro_x);
    if (objects.jog_work_x) lv_label_set_text(objects.jog_work_x, s_v.work_dro_x);
    bsp_display_unlock();
}
const char *get_var_work_dro_y(void) { return s_v.work_dro_y; }
void        set_var_work_dro_y(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.work_dro_y, v ? v : "", sizeof(s_v.work_dro_y));
    if (objects.dash_dro_y) lv_label_set_text(objects.dash_dro_y, s_v.work_dro_y);
    if (objects.jog_work_y) lv_label_set_text(objects.jog_work_y, s_v.work_dro_y);
    bsp_display_unlock();
}
const char *get_var_work_dro_z(void) { return s_v.work_dro_z; }
void        set_var_work_dro_z(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.work_dro_z, v ? v : "", sizeof(s_v.work_dro_z));
    if (objects.dash_dro_z) lv_label_set_text(objects.dash_dro_z, s_v.work_dro_z);
    if (objects.jog_work_z) lv_label_set_text(objects.jog_work_z, s_v.work_dro_z);
    bsp_display_unlock();
}

const char *get_var_machine_dro_x(void) { return s_v.machine_dro_x; }
void        set_var_machine_dro_x(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.machine_dro_x, v ? v : "", sizeof(s_v.machine_dro_x));
    if (objects.jog_machine_x) lv_label_set_text(objects.jog_machine_x, s_v.machine_dro_x);
    bsp_display_unlock();
}
const char *get_var_machine_dro_y(void) { return s_v.machine_dro_y; }
void        set_var_machine_dro_y(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.machine_dro_y, v ? v : "", sizeof(s_v.machine_dro_y));
    if (objects.jog_machine_y) lv_label_set_text(objects.jog_machine_y, s_v.machine_dro_y);
    bsp_display_unlock();
}
const char *get_var_machine_dro_z(void) { return s_v.machine_dro_z; }
void        set_var_machine_dro_z(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.machine_dro_z, v ? v : "", sizeof(s_v.machine_dro_z));
    if (objects.jog_machine_z) lv_label_set_text(objects.jog_machine_z, s_v.machine_dro_z);
    bsp_display_unlock();
}

/* units_label — Dashboard caption ("mm" / "in"). The Jog DRO unit lives in
 * the chip styling, not a label. */
const char *get_var_units_label(void) { return s_v.units_label; }
void        set_var_units_label(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.units_label, v ? v : "", sizeof(s_v.units_label));
    if (objects.dash_dro_unit) lv_label_set_text(objects.dash_dro_unit, s_v.units_label);
    bsp_display_unlock();
}

/* --- Overrides ---------------------------------------------------------- *
 * Each setter also writes the new value into the percent label and updates
 * the bar widget — the dashboard override cards have no other code path
 * driving them. The bars are LVGLBar (not Slider) so they're display-only;
 * the +/- buttons fire action_adjust_override, which calls fluidnc, which
 * calls back through on_fluid_status -> set_var_<ov>_pct(). */
/* Bars are authored in EEZ Studio with range 0–100 (matches the on-screen
 * "100 %" expectation: full bar = 100 %). For overrides above 100 % the
 * numeric label still shows the true percentage; we just clamp the bar's
 * visual to its max so values above 100 stay pinned to "full". */
#define OV_PCT_VAR(NAME, LABEL_FIELD, BAR_FIELD)                              \
    int32_t get_var_##NAME(void) { return s_v.NAME; }                         \
    void    set_var_##NAME(int32_t v) {                                       \
        bsp_display_lock(0);                                                  \
        s_v.NAME = v;                                                         \
        if (objects.LABEL_FIELD) {                                            \
            char buf[8];                                                      \
            snprintf(buf, sizeof(buf), "%d%%", (int)v);                       \
            lv_label_set_text(objects.LABEL_FIELD, buf);                      \
        }                                                                     \
        if (objects.BAR_FIELD) {                                              \
            int32_t bar_v = v;                                                \
            if (bar_v < 0)   bar_v = 0;                                       \
            if (bar_v > 100) bar_v = 100;                                     \
            lv_bar_set_value(objects.BAR_FIELD, bar_v, LV_ANIM_OFF);          \
        }                                                                     \
        bsp_display_unlock();                                                 \
    }
OV_PCT_VAR(feed_ov_pct,    dash_ov_val_feed,    dash_ov_bar_feed)
OV_PCT_VAR(rapid_ov_pct,   dash_ov_val_rapid,   dash_ov_bar_rapid)
OV_PCT_VAR(spindle_ov_pct, dash_ov_val_spindle, dash_ov_bar_spindle)
#undef OV_PCT_VAR


/* --- Job ---------------------------------------------------------------- *
 * Run header (run_hdr_*) and Dashboard job card (dash_job_*) both show the
 * same set of fields. Setters fan to both. */

const char *get_var_job_file(void) { return s_v.job_file; }
void        set_var_job_file(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.job_file, v ? v : "", sizeof(s_v.job_file));
    if (objects.dash_job_file) lv_label_set_text(objects.dash_job_file, s_v.job_file);
    if (objects.run_hdr_file)  lv_label_set_text(objects.run_hdr_file,  s_v.job_file);
    bsp_display_unlock();
}

int32_t get_var_job_pct(void) { return s_v.job_pct; }
void    set_var_job_pct(int32_t v)
{
    bsp_display_lock(0);
    if (v < 0)   v = 0;
    if (v > 100) v = 100;
    s_v.job_pct = v;
    char buf[8];
    snprintf(buf, sizeof(buf), "%d%%", (int)v);
    if (objects.dash_job_pct) lv_label_set_text(objects.dash_job_pct, buf);
    if (objects.run_hdr_pct)  lv_label_set_text(objects.run_hdr_pct,  buf);
    if (objects.dash_job_bar) lv_bar_set_value(objects.dash_job_bar, v, LV_ANIM_OFF);
    if (objects.run_hdr_bar)  lv_bar_set_value(objects.run_hdr_bar,  v, LV_ANIM_OFF);
    bsp_display_unlock();
}

const char *get_var_job_elapsed(void) { return s_v.job_elapsed; }
void        set_var_job_elapsed(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.job_elapsed, v ? v : "", sizeof(s_v.job_elapsed));
    if (objects.dash_job_elapsed) lv_label_set_text(objects.dash_job_elapsed, s_v.job_elapsed);
    if (objects.run_hdr_elapsed)  lv_label_set_text(objects.run_hdr_elapsed,  s_v.job_elapsed);
    bsp_display_unlock();
}
const char *get_var_job_eta(void) { return s_v.job_eta; }
void        set_var_job_eta(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.job_eta, v ? v : "", sizeof(s_v.job_eta));
    if (objects.dash_job_eta) lv_label_set_text(objects.dash_job_eta, s_v.job_eta);
    if (objects.run_hdr_remain) lv_label_set_text(objects.run_hdr_remain, s_v.job_eta);
    bsp_display_unlock();
}

int32_t get_var_job_line(void)  { return s_v.job_line;  }
int32_t get_var_job_total(void) { return s_v.job_total; }

static void job_line_widgets_update_locked(void)
{
    char buf[24];
    if (s_v.job_total > 0) {
        snprintf(buf, sizeof(buf), "Line %d / %d", (int)s_v.job_line, (int)s_v.job_total);
    } else {
        snprintf(buf, sizeof(buf), "Line %d", (int)s_v.job_line);
    }
    if (objects.dash_job_line) lv_label_set_text(objects.dash_job_line, buf);
    if (objects.run_hdr_line)  lv_label_set_text(objects.run_hdr_line,  buf);
}
void set_var_job_line(int32_t v)
{
    bsp_display_lock(0);
    s_v.job_line = v;
    job_line_widgets_update_locked();
    bsp_display_unlock();
}
void set_var_job_total(int32_t v)
{
    bsp_display_lock(0);
    s_v.job_total = v;
    job_line_widgets_update_locked();
    bsp_display_unlock();
}

/* --- Spindle ------------------------------------------------------------ *
 * spindle_on drives the Dashboard SPINDLE tile's CHECKED state. The
 * dedicated START / STOP buttons on PageSpindle don't consult this var —
 * they always do their one action — so this setter no longer touches
 * anything on the Spindle page. */
bool get_var_spindle_on(void) { return s_v.spindle_on; }
void set_var_spindle_on(bool v)
{
    bsp_display_lock(0);
    s_v.spindle_on = v;
    if (objects.dash_tq_spindle) {
        if (v) lv_obj_add_state(objects.dash_tq_spindle,   LV_STATE_CHECKED);
        else   lv_obj_clear_state(objects.dash_tq_spindle, LV_STATE_CHECKED);
    }
    bsp_display_unlock();
}

int32_t get_var_spindle_rpm(void) { return s_v.spindle_rpm; }
void    set_var_spindle_rpm(int32_t v)
{
    bsp_display_lock(0);
    s_v.spindle_rpm = v;
    char buf[12];
    snprintf(buf, sizeof(buf), "%d", (int)v);
    if (objects.spin_rpm_val) lv_label_set_text(objects.spin_rpm_val, buf);
    if (objects.dash_tq_rpm_spindle) lv_label_set_text(objects.dash_tq_rpm_spindle, buf);
    if (objects.spin_arc) {
        int arc_v = v;
        if (arc_v < 0)     arc_v = 0;
        if (arc_v > 24000) arc_v = 24000;
        lv_arc_set_value(objects.spin_arc, arc_v);
    }
    bsp_display_unlock();
}

int32_t get_var_spindle_target(void) { return s_v.spindle_target; }
void    set_var_spindle_target(int32_t v)
{
    bsp_display_lock(0);
    s_v.spindle_target = v;
    if (objects.spin_trgt_val) {
        char buf[12];
        snprintf(buf, sizeof(buf), "%d", (int)v);
        lv_label_set_text(objects.spin_trgt_val, buf);
    }
    bsp_display_unlock();
}

int32_t get_var_spindle_load(void) { return s_v.spindle_load; }
void    set_var_spindle_load(int32_t v)
{
    bsp_display_lock(0);
    s_v.spindle_load = v;
    char buf[8];
    snprintf(buf, sizeof(buf), "%d%%", (int)v);
    if (objects.spin_load_val) lv_label_set_text(objects.spin_load_val, buf);
    if (objects.spin_load_bar) lv_bar_set_value(objects.spin_load_bar, v, LV_ANIM_OFF);
    bsp_display_unlock();
}

bool get_var_flood_on(void) { return s_v.flood_on; }
void set_var_flood_on(bool v)
{
    bsp_display_lock(0);
    s_v.flood_on = v;
    /* The dashboard "FLOOD" button became Soft Reset in the .eez-project
     * (see dash_tq_soft_reset) — flood state only mirrors on the Spindle
     * page now. */
    if (objects.spin_cool_flood) {
        if (v) lv_obj_add_state(objects.spin_cool_flood,   LV_STATE_CHECKED);
        else   lv_obj_clear_state(objects.spin_cool_flood, LV_STATE_CHECKED);
    }
    bsp_display_unlock();
}
bool get_var_mist_on(void) { return s_v.mist_on; }
void set_var_mist_on(bool v)
{
    bsp_display_lock(0);
    s_v.mist_on = v;
    if (objects.dash_tq_mist) {
        if (v) lv_obj_add_state(objects.dash_tq_mist,   LV_STATE_CHECKED);
        else   lv_obj_clear_state(objects.dash_tq_mist, LV_STATE_CHECKED);
    }
    if (objects.spin_cool_mist) {
        if (v) lv_obj_add_state(objects.spin_cool_mist,   LV_STATE_CHECKED);
        else   lv_obj_clear_state(objects.spin_cool_mist, LV_STATE_CHECKED);
    }
    bsp_display_unlock();
}

/* --- Probe --------------------------------------------------------------
 *
 * Each probe parameter has both a cached string (used by action_probe_start
 * to build the gcode) AND a visible label on the Probe screen. The bare
 * VAR_STRING macro only writes the cache, so the on-screen tile would
 * keep showing its initial text after an edit. These setters fan the new
 * value out to the label as well — same pattern as set_var_machine_state. */
const char *get_var_probe_plate_thickness(void) { return s_v.probe_plate_thickness; }
void        set_var_probe_plate_thickness(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.probe_plate_thickness, v ? v : "",
            sizeof(s_v.probe_plate_thickness));
    if (objects.probe_info_plate_val) {
        lv_label_set_text(objects.probe_info_plate_val,
                          s_v.probe_plate_thickness);
    }
    bsp_display_unlock();
}

const char *get_var_probe_feed(void) { return s_v.probe_feed; }
void        set_var_probe_feed(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.probe_feed, v ? v : "", sizeof(s_v.probe_feed));
    if (objects.probe_info_feed_val) {
        lv_label_set_text(objects.probe_info_feed_val, s_v.probe_feed);
    }
    bsp_display_unlock();
}

const char *get_var_probe_max_travel(void) { return s_v.probe_max_travel; }
void        set_var_probe_max_travel(const char *v)
{
    bsp_display_lock(0);
    strlcpy(s_v.probe_max_travel, v ? v : "", sizeof(s_v.probe_max_travel));
    if (objects.probe_info_travel_val) {
        lv_label_set_text(objects.probe_info_travel_val, s_v.probe_max_travel);
    }
    bsp_display_unlock();
}

/* --- System info -------------------------------------------------------- */
VAR_STRING(fw_version,      fw_version)
VAR_STRING(controller_info, controller_info)
VAR_STRING(ui_info,         ui_info)
VAR_STRING(net_info,        net_info)

/* --- Display / motion preferences (persisted in NVS by actions.c) ------ */
/* These overlay the macro-generated bodies because each setter also writes
 * back into a label widget so the value stays in sync without an extra
 * callback round-trip. */

int32_t get_var_screen_brightness(void) { return s_v.screen_brightness; }
void    set_var_screen_brightness(int32_t v)
{
    bsp_display_lock(0);
    s_v.screen_brightness = v;
    if (objects.settings_disp_bright_val) {
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", (int)v);
        lv_label_set_text(objects.settings_disp_bright_val, buf);
    }
    if (objects.settings_disp_bright_slider) {
        lv_slider_set_value(objects.settings_disp_bright_slider, v, LV_ANIM_OFF);
    }
    bsp_display_unlock();
}

int32_t get_var_screen_timeout_value(void) { return s_v.screen_timeout_value; }
void    set_var_screen_timeout_value(int32_t v)
{
    bsp_display_lock(0);
    s_v.screen_timeout_value = v;
    if (objects.settings_disp_to_val) {
        char buf[16];
        if (v <= 0) {
            /* "Never" — the screen never times out. Previously this label
             * said "Off" which users read as "the screen will turn off",
             * the opposite of what it means. */
            snprintf(buf, sizeof(buf), "Never");
        } else {
            snprintf(buf, sizeof(buf), "%d min", (int)v);
        }
        lv_label_set_text(objects.settings_disp_to_val, buf);
    }
    bsp_display_unlock();
}

int32_t get_var_default_jog_feed(void) { return s_v.default_jog_feed; }
void    set_var_default_jog_feed(int32_t v)
{
    bsp_display_lock(0);
    s_v.default_jog_feed = v;
    if (objects.settings_mot_jog_val) {
        char buf[16];
        snprintf(buf, sizeof(buf), "%d mm/min", (int)v);
        lv_label_set_text(objects.settings_mot_jog_val, buf);
    }
    if (objects.settings_mot_jog_slider) {
        lv_slider_set_value(objects.settings_mot_jog_slider, v, LV_ANIM_OFF);
    }
    bsp_display_unlock();
}

int32_t get_var_selected_theme(void) { return s_v.selected_theme; }
void    set_var_selected_theme(int32_t v)
{
    /* 0 = Light (THEME_ID_DEFAULT), 1 = Dark (THEME_ID_DARK). Picks the
     * matching color palette and toggles the CHECKED state on the two
     * Light/Dark buttons on the Display tab. */
    bsp_display_lock(0);
    s_v.selected_theme = v;
    if (v == 0)      change_color_theme(THEME_ID_DEFAULT);
    else if (v == 1) change_color_theme(THEME_ID_DARK);
    if (objects.settings_theme_light) {
        if (v == 0) lv_obj_add_state(objects.settings_theme_light,   LV_STATE_CHECKED);
        else        lv_obj_clear_state(objects.settings_theme_light, LV_STATE_CHECKED);
    }
    if (objects.settings_theme_dark) {
        if (v == 1) lv_obj_add_state(objects.settings_theme_dark,    LV_STATE_CHECKED);
        else        lv_obj_clear_state(objects.settings_theme_dark,  LV_STATE_CHECKED);
    }
    bsp_display_unlock();
}

#endif /* __has_include("ui/vars.h") */
