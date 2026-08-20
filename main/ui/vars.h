#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp/esp-bsp.h"
#include "bsp/display.h"

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_WIFI_STATE = 0,
    FLOW_GLOBAL_VARIABLE_WIFI_SSID = 1,
    FLOW_GLOBAL_VARIABLE_WIFI_IP = 2,
    FLOW_GLOBAL_VARIABLE_FLUID_STATE = 3,
    FLOW_GLOBAL_VARIABLE_FLUID_HOST = 4,
    FLOW_GLOBAL_VARIABLE_FLUID_TRANSPORT_INDEX = 5,
    FLOW_GLOBAL_VARIABLE_MACHINE_STATE = 6,
    FLOW_GLOBAL_VARIABLE_ACTIVE_WCS = 7,
    FLOW_GLOBAL_VARIABLE_MINI_DRO_X = 8,
    FLOW_GLOBAL_VARIABLE_MINI_DRO_Y = 9,
    FLOW_GLOBAL_VARIABLE_MINI_DRO_Z = 10,
    FLOW_GLOBAL_VARIABLE_HOLD_LABEL = 11,
    FLOW_GLOBAL_VARIABLE_ALARM_TEXT = 12,
    FLOW_GLOBAL_VARIABLE_WORK_DRO_X = 13,
    FLOW_GLOBAL_VARIABLE_WORK_DRO_Y = 14,
    FLOW_GLOBAL_VARIABLE_WORK_DRO_Z = 15,
    FLOW_GLOBAL_VARIABLE_MACHINE_DRO_X = 16,
    FLOW_GLOBAL_VARIABLE_MACHINE_DRO_Y = 17,
    FLOW_GLOBAL_VARIABLE_MACHINE_DRO_Z = 18,
    FLOW_GLOBAL_VARIABLE_UNITS_LABEL = 19,
    FLOW_GLOBAL_VARIABLE_FEED_OV_PCT = 20,
    FLOW_GLOBAL_VARIABLE_RAPID_OV_PCT = 21,
    FLOW_GLOBAL_VARIABLE_SPINDLE_OV_PCT = 22,
    FLOW_GLOBAL_VARIABLE_JOB_FILE = 23,
    FLOW_GLOBAL_VARIABLE_JOB_PCT = 24,
    FLOW_GLOBAL_VARIABLE_JOB_ELAPSED = 25,
    FLOW_GLOBAL_VARIABLE_JOB_ETA = 26,
    FLOW_GLOBAL_VARIABLE_JOB_LINE = 27,
    FLOW_GLOBAL_VARIABLE_JOB_TOTAL = 28,
    FLOW_GLOBAL_VARIABLE_SPINDLE_ON = 29,
    FLOW_GLOBAL_VARIABLE_SPINDLE_RPM = 30,
    FLOW_GLOBAL_VARIABLE_SPINDLE_TARGET = 31,
    FLOW_GLOBAL_VARIABLE_SPINDLE_LOAD = 32,
    FLOW_GLOBAL_VARIABLE_FLOOD_ON = 33,
    FLOW_GLOBAL_VARIABLE_MIST_ON = 34,
    FLOW_GLOBAL_VARIABLE_PROBE_PLATE_THICKNESS = 35,
    FLOW_GLOBAL_VARIABLE_PROBE_FEED = 36,
    FLOW_GLOBAL_VARIABLE_PROBE_MAX_TRAVEL = 37,
    FLOW_GLOBAL_VARIABLE_FW_VERSION = 38,
    FLOW_GLOBAL_VARIABLE_CONTROLLER_INFO = 39,
    FLOW_GLOBAL_VARIABLE_UI_INFO = 40,
    FLOW_GLOBAL_VARIABLE_NET_INFO = 41,
    FLOW_GLOBAL_VARIABLE_SCREEN_BRIGHTNESS = 42,
    FLOW_GLOBAL_VARIABLE_SCREEN_TIMEOUT_VALUE = 43,
    FLOW_GLOBAL_VARIABLE_DEFAULT_JOG_FEED = 44,
    FLOW_GLOBAL_VARIABLE_STICK_JOG_FEED = 45,
    FLOW_GLOBAL_VARIABLE_SELECTED_THEME = 46,
    FLOW_GLOBAL_VARIABLE_BATTERY_PCT = 47,
    FLOW_GLOBAL_VARIABLE_BATTERY_CHARGING = 48,
    FLOW_GLOBAL_VARIABLE_BATTERY_VISIBLE = 49,
    FLOW_GLOBAL_VARIABLE_PROBE_XY_TRAVEL = 50,
    FLOW_GLOBAL_VARIABLE_PROBE_EDGE_DEPTH = 51,
    FLOW_GLOBAL_VARIABLE_PROBE_TOOL_DIA = 52,
    FLOW_GLOBAL_VARIABLE_PROBE_EDGE_THICK = 53
};

// Native global variables

extern int32_t get_var_wifi_state();
extern void set_var_wifi_state(int32_t value);
extern const char *get_var_wifi_ssid();
extern void set_var_wifi_ssid(const char *value);
extern const char *get_var_wifi_ip();
extern void set_var_wifi_ip(const char *value);
extern int32_t get_var_fluid_state();
extern void set_var_fluid_state(int32_t value);
extern const char *get_var_fluid_host();
extern void set_var_fluid_host(const char *value);
extern int32_t get_var_fluid_transport_index();
extern void set_var_fluid_transport_index(int32_t value);
extern const char *get_var_machine_state();
extern void set_var_machine_state(const char *value);
extern const char *get_var_active_wcs();
extern void set_var_active_wcs(const char *value);
extern const char *get_var_mini_dro_x();
extern void set_var_mini_dro_x(const char *value);
extern const char *get_var_mini_dro_y();
extern void set_var_mini_dro_y(const char *value);
extern const char *get_var_mini_dro_z();
extern void set_var_mini_dro_z(const char *value);
extern const char *get_var_hold_label();
extern void set_var_hold_label(const char *value);
extern const char *get_var_alarm_text();
extern void set_var_alarm_text(const char *value);
extern const char *get_var_work_dro_x();
extern void set_var_work_dro_x(const char *value);
extern const char *get_var_work_dro_y();
extern void set_var_work_dro_y(const char *value);
extern const char *get_var_work_dro_z();
extern void set_var_work_dro_z(const char *value);
extern const char *get_var_machine_dro_x();
extern void set_var_machine_dro_x(const char *value);
extern const char *get_var_machine_dro_y();
extern void set_var_machine_dro_y(const char *value);
extern const char *get_var_machine_dro_z();
extern void set_var_machine_dro_z(const char *value);
extern const char *get_var_units_label();
extern void set_var_units_label(const char *value);
extern int32_t get_var_feed_ov_pct();
extern void set_var_feed_ov_pct(int32_t value);
extern int32_t get_var_rapid_ov_pct();
extern void set_var_rapid_ov_pct(int32_t value);
extern int32_t get_var_spindle_ov_pct();
extern void set_var_spindle_ov_pct(int32_t value);
extern const char *get_var_job_file();
extern void set_var_job_file(const char *value);
extern int32_t get_var_job_pct();
extern void set_var_job_pct(int32_t value);
extern const char *get_var_job_elapsed();
extern void set_var_job_elapsed(const char *value);
extern const char *get_var_job_eta();
extern void set_var_job_eta(const char *value);
extern int32_t get_var_job_line();
extern void set_var_job_line(int32_t value);
extern int32_t get_var_job_total();
extern void set_var_job_total(int32_t value);
extern bool get_var_spindle_on();
extern void set_var_spindle_on(bool value);
extern int32_t get_var_spindle_rpm();
extern void set_var_spindle_rpm(int32_t value);
extern int32_t get_var_spindle_target();
extern void set_var_spindle_target(int32_t value);
extern int32_t get_var_spindle_load();
extern void set_var_spindle_load(int32_t value);
extern bool get_var_flood_on();
extern void set_var_flood_on(bool value);
extern bool get_var_mist_on();
extern void set_var_mist_on(bool value);
extern const char *get_var_probe_plate_thickness();
extern void set_var_probe_plate_thickness(const char *value);
extern const char *get_var_probe_feed();
extern void set_var_probe_feed(const char *value);
extern const char *get_var_probe_max_travel();
extern void set_var_probe_max_travel(const char *value);
extern const char *get_var_fw_version();
extern void set_var_fw_version(const char *value);
extern const char *get_var_controller_info();
extern void set_var_controller_info(const char *value);
extern const char *get_var_ui_info();
extern void set_var_ui_info(const char *value);
extern const char *get_var_net_info();
extern void set_var_net_info(const char *value);
extern int32_t get_var_screen_brightness();
extern void set_var_screen_brightness(int32_t value);
extern int32_t get_var_screen_timeout_value();
extern void set_var_screen_timeout_value(int32_t value);
extern int32_t get_var_default_jog_feed();
extern void set_var_default_jog_feed(int32_t value);
extern int32_t get_var_stick_jog_feed();
extern void set_var_stick_jog_feed(int32_t value);
extern int32_t get_var_selected_theme();
extern void set_var_selected_theme(int32_t value);
extern int32_t get_var_battery_pct();
extern void set_var_battery_pct(int32_t value);
extern bool get_var_battery_charging();
extern void set_var_battery_charging(bool value);
extern bool get_var_battery_visible();
extern void set_var_battery_visible(bool value);
extern const char *get_var_probe_xy_travel();
extern void set_var_probe_xy_travel(const char *value);
extern const char *get_var_probe_edge_depth();
extern void set_var_probe_edge_depth(const char *value);
extern const char *get_var_probe_tool_dia();
extern void set_var_probe_tool_dia(const char *value);
extern const char *get_var_probe_edge_thick();
extern void set_var_probe_edge_thick(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/