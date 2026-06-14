#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_change_screen(lv_event_t * e);
extern void action_open_settings_tab(lv_event_t * e);
extern void action_hold_resume(lv_event_t * e);
extern void action_estop(lv_event_t * e);
extern void action_alarm_reset(lv_event_t * e);
extern void action_zero_axis(lv_event_t * e);
extern void action_home_all(lv_event_t * e);
extern void action_adjust_override(lv_event_t * e);
extern void action_reset_override(lv_event_t * e);
extern void action_set_wcs(lv_event_t * e);
extern void action_set_units(lv_event_t * e);
extern void action_set_jog_step(lv_event_t * e);
extern void action_jog(lv_event_t * e);
extern void action_job_start(lv_event_t * e);
extern void action_job_stop(lv_event_t * e);
extern void action_file_select(lv_event_t * e);
extern void action_file_load_run(lv_event_t * e);
extern void action_file_refresh(lv_event_t * e);
extern void action_toggle_spindle(lv_event_t * e);
extern void action_adjust_spindle_target(lv_event_t * e);
extern void action_toggle_flood(lv_event_t * e);
extern void action_toggle_mist(lv_event_t * e);
extern void action_set_probe_type(lv_event_t * e);
extern void action_probe_start(lv_event_t * e);
extern void action_run_macro(lv_event_t * e);
extern void action_toggle_soft_limits(lv_event_t * e);
extern void action_toggle_hard_limits(lv_event_t * e);
extern void action_toggle_home_on_boot(lv_event_t * e);
extern void action_wifi_scan(lv_event_t * e);
extern void action_wifi_select_network(lv_event_t * e);
extern void action_wifi_password_submit(lv_event_t * e);
extern void action_wifi_forget(lv_event_t * e);
extern void action_wifi_back(lv_event_t * e);
extern void action_wifi_skip_to_serial(lv_event_t * e);
extern void action_wifi_toggle_password_reveal(lv_event_t * e);
extern void action_set_fluid_transport(lv_event_t * e);
extern void action_fluid_connect(lv_event_t * e);
extern void action_fluid_disconnect(lv_event_t * e);
extern void action_change_wifi(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/