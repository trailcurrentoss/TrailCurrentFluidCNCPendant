/*
 * Native global variable bridge.
 *
 * EEZ Studio declares one `set_var_<name>` / `get_var_<name>` pair per global
 * variable in main/ui/vars.h. The implementations live here. They are called
 * from C code (status callbacks, action handlers, …) any time the UI needs to
 * be refreshed.
 *
 * Threading: setters take bsp_display_lock so they're safe to call from the
 * WiFi / FluidNC tasks. Getters return cached values without locking.
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
} s_v = {
    .machine_state = "IDLE",
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
    .job_file      = "—",
    .job_elapsed   = "00:00",
    .job_eta       = "00:00",
    .hold_label    = "HOLD",
    .clock_text    = "--:--",
    .spindle_target= 12000,
    .probe_plate_thickness = "19.00",
    .probe_feed            = "100",
    .probe_max_travel      = "25",
    .fw_version            = "FluidNC 3.7.16",
    .controller_info       = "ESP32-P4 @ 360 MHz",
    .ui_info               = "LVGL 8.4 . 1024x600",
    .net_info              = "Disconnected",
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

/* --- Top status bar ----------------------------------------------------- */
VAR_STRING(machine_state, machine_state)
VAR_STRING(active_wcs,    active_wcs)
VAR_STRING(mini_dro_x,    mini_dro_x)
VAR_STRING(mini_dro_y,    mini_dro_y)
VAR_STRING(mini_dro_z,    mini_dro_z)
VAR_STRING(clock_text,    clock_text)
VAR_STRING(hold_label,    hold_label)

VAR_STRING(alarm_text, alarm_text)

/* --- Dashboard / Jog DRO ------------------------------------------------ */
VAR_STRING(work_dro_x,    work_dro_x)
VAR_STRING(work_dro_y,    work_dro_y)
VAR_STRING(work_dro_z,    work_dro_z)
VAR_STRING(machine_dro_x, machine_dro_x)
VAR_STRING(machine_dro_y, machine_dro_y)
VAR_STRING(machine_dro_z, machine_dro_z)
VAR_STRING(units_label,   units_label)

/* --- Overrides ---------------------------------------------------------- */
VAR_INT(feed_ov_pct,    feed_ov_pct)
VAR_INT(rapid_ov_pct,   rapid_ov_pct)
VAR_INT(spindle_ov_pct, spindle_ov_pct)

/* --- Job ---------------------------------------------------------------- */
VAR_STRING(job_file,    job_file)
VAR_INT   (job_pct,     job_pct)
VAR_STRING(job_elapsed, job_elapsed)
VAR_STRING(job_eta,     job_eta)
VAR_INT   (job_line,    job_line)
VAR_INT   (job_total,   job_total)

/* --- Spindle ------------------------------------------------------------ */
VAR_BOOL(spindle_on,     spindle_on)
VAR_INT (spindle_rpm,    spindle_rpm)
VAR_INT (spindle_target, spindle_target)
VAR_INT (spindle_load,   spindle_load)
VAR_BOOL(flood_on,       flood_on)
VAR_BOOL(mist_on,        mist_on)

/* --- Probe -------------------------------------------------------------- */
VAR_STRING(probe_plate_thickness, probe_plate_thickness)
VAR_STRING(probe_feed,            probe_feed)
VAR_STRING(probe_max_travel,      probe_max_travel)

/* --- System info -------------------------------------------------------- */
VAR_STRING(fw_version,      fw_version)
VAR_STRING(controller_info, controller_info)
VAR_STRING(ui_info,         ui_info)
VAR_STRING(net_info,        net_info)

#endif /* __has_include("ui/vars.h") */
