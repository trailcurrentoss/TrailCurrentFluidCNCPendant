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
    FLOW_GLOBAL_VARIABLE_CLOCK_TEXT = 11,
    FLOW_GLOBAL_VARIABLE_HOLD_LABEL = 12,
    FLOW_GLOBAL_VARIABLE_ALARM_TEXT = 13,
    FLOW_GLOBAL_VARIABLE_WORK_DRO_X = 14,
    FLOW_GLOBAL_VARIABLE_WORK_DRO_Y = 15,
    FLOW_GLOBAL_VARIABLE_WORK_DRO_Z = 16,
    FLOW_GLOBAL_VARIABLE_MACHINE_DRO_X = 17,
    FLOW_GLOBAL_VARIABLE_MACHINE_DRO_Y = 18,
    FLOW_GLOBAL_VARIABLE_MACHINE_DRO_Z = 19,
    FLOW_GLOBAL_VARIABLE_UNITS_LABEL = 20,
    FLOW_GLOBAL_VARIABLE_FEED_OV_PCT = 21,
    FLOW_GLOBAL_VARIABLE_RAPID_OV_PCT = 22,
    FLOW_GLOBAL_VARIABLE_SPINDLE_OV_PCT = 23,
    FLOW_GLOBAL_VARIABLE_JOB_FILE = 24,
    FLOW_GLOBAL_VARIABLE_JOB_PCT = 25,
    FLOW_GLOBAL_VARIABLE_JOB_ELAPSED = 26,
    FLOW_GLOBAL_VARIABLE_JOB_ETA = 27,
    FLOW_GLOBAL_VARIABLE_JOB_LINE = 28,
    FLOW_GLOBAL_VARIABLE_JOB_TOTAL = 29,
    FLOW_GLOBAL_VARIABLE_SPINDLE_ON = 30,
    FLOW_GLOBAL_VARIABLE_SPINDLE_RPM = 31,
    FLOW_GLOBAL_VARIABLE_SPINDLE_TARGET = 32,
    FLOW_GLOBAL_VARIABLE_SPINDLE_LOAD = 33,
    FLOW_GLOBAL_VARIABLE_FLOOD_ON = 34,
    FLOW_GLOBAL_VARIABLE_MIST_ON = 35,
    FLOW_GLOBAL_VARIABLE_PROBE_PLATE_THICKNESS = 36,
    FLOW_GLOBAL_VARIABLE_PROBE_FEED = 37,
    FLOW_GLOBAL_VARIABLE_PROBE_MAX_TRAVEL = 38,
    FLOW_GLOBAL_VARIABLE_FW_VERSION = 39,
    FLOW_GLOBAL_VARIABLE_CONTROLLER_INFO = 40,
    FLOW_GLOBAL_VARIABLE_UI_INFO = 41,
    FLOW_GLOBAL_VARIABLE_NET_INFO = 42,
    FLOW_GLOBAL_VARIABLE_SCREEN_BRIGHTNESS = 43,
    FLOW_GLOBAL_VARIABLE_SCREEN_TIMEOUT_VALUE = 44,
    FLOW_GLOBAL_VARIABLE_DEFAULT_JOG_FEED = 45,
    FLOW_GLOBAL_VARIABLE_SELECTED_THEME = 46
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
extern const char *get_var_clock_text();
extern void set_var_clock_text(const char *value);
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
extern int32_t get_var_selected_theme();
extern void set_var_selected_theme(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/