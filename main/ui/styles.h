#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: StyleScreenDefault
lv_style_t *get_style_style_screen_default_MAIN_DEFAULT();
void add_style_style_screen_default(lv_obj_t *obj);
void remove_style_style_screen_default(lv_obj_t *obj);

// Style: StylePanelDefault
lv_style_t *get_style_style_panel_default_MAIN_DEFAULT();
void add_style_style_panel_default(lv_obj_t *obj);
void remove_style_style_panel_default(lv_obj_t *obj);

// Style: PanelTopBar
lv_style_t *get_style_panel_top_bar_MAIN_DEFAULT();
void add_style_panel_top_bar(lv_obj_t *obj);
void remove_style_panel_top_bar(lv_obj_t *obj);

// Style: PanelBottomDock
lv_style_t *get_style_panel_bottom_dock_MAIN_DEFAULT();
void add_style_panel_bottom_dock(lv_obj_t *obj);
void remove_style_panel_bottom_dock(lv_obj_t *obj);

// Style: PanelAlarm
lv_style_t *get_style_panel_alarm_MAIN_DEFAULT();
void add_style_panel_alarm(lv_obj_t *obj);
void remove_style_panel_alarm(lv_obj_t *obj);

// Style: PanelTransparent
lv_style_t *get_style_panel_transparent_MAIN_DEFAULT();
void add_style_panel_transparent(lv_obj_t *obj);
void remove_style_panel_transparent(lv_obj_t *obj);

// Style: PanelDarkInset
lv_style_t *get_style_panel_dark_inset_MAIN_DEFAULT();
void add_style_panel_dark_inset(lv_obj_t *obj);
void remove_style_panel_dark_inset(lv_obj_t *obj);

// Style: Card
lv_style_t *get_style_card_MAIN_DEFAULT();
void add_style_card(lv_obj_t *obj);
void remove_style_card(lv_obj_t *obj);

// Style: LabelDefault
lv_style_t *get_style_label_default_MAIN_DEFAULT();
void add_style_label_default(lv_obj_t *obj);
void remove_style_label_default(lv_obj_t *obj);

// Style: LabelCaption
lv_style_t *get_style_label_caption_MAIN_DEFAULT();
void add_style_label_caption(lv_obj_t *obj);
void remove_style_label_caption(lv_obj_t *obj);

// Style: LabelSection
lv_style_t *get_style_label_section_MAIN_DEFAULT();
void add_style_label_section(lv_obj_t *obj);
void remove_style_label_section(lv_obj_t *obj);

// Style: LabelHeading
lv_style_t *get_style_label_heading_MAIN_DEFAULT();
void add_style_label_heading(lv_obj_t *obj);
void remove_style_label_heading(lv_obj_t *obj);

// Style: LabelBrand
lv_style_t *get_style_label_brand_MAIN_DEFAULT();
void add_style_label_brand(lv_obj_t *obj);
void remove_style_label_brand(lv_obj_t *obj);

// Style: LabelAccent
lv_style_t *get_style_label_accent_MAIN_DEFAULT();
void add_style_label_accent(lv_obj_t *obj);
void remove_style_label_accent(lv_obj_t *obj);

// Style: LabelMonoMini
lv_style_t *get_style_label_mono_mini_MAIN_DEFAULT();
void add_style_label_mono_mini(lv_obj_t *obj);
void remove_style_label_mono_mini(lv_obj_t *obj);

// Style: LabelMonoJog
lv_style_t *get_style_label_mono_jog_MAIN_DEFAULT();
void add_style_label_mono_jog(lv_obj_t *obj);
void remove_style_label_mono_jog(lv_obj_t *obj);

// Style: LabelMonoDro
lv_style_t *get_style_label_mono_dro_MAIN_DEFAULT();
void add_style_label_mono_dro(lv_obj_t *obj);
void remove_style_label_mono_dro(lv_obj_t *obj);

// Style: LabelMonoSpindleVal
lv_style_t *get_style_label_mono_spindle_val_MAIN_DEFAULT();
void add_style_label_mono_spindle_val(lv_obj_t *obj);
void remove_style_label_mono_spindle_val(lv_obj_t *obj);

// Style: LabelMonoMachine
lv_style_t *get_style_label_mono_machine_MAIN_DEFAULT();
void add_style_label_mono_machine(lv_obj_t *obj);
void remove_style_label_mono_machine(lv_obj_t *obj);

// Style: LabelMuted
lv_style_t *get_style_label_muted_MAIN_DEFAULT();
void add_style_label_muted(lv_obj_t *obj);
void remove_style_label_muted(lv_obj_t *obj);

// Style: LabelDockTab
lv_style_t *get_style_label_dock_tab_MAIN_DEFAULT();
lv_style_t *get_style_label_dock_tab_MAIN_CHECKED();
void add_style_label_dock_tab(lv_obj_t *obj);
void remove_style_label_dock_tab(lv_obj_t *obj);

// Style: LabelSecondary
lv_style_t *get_style_label_secondary_MAIN_DEFAULT();
void add_style_label_secondary(lv_obj_t *obj);
void remove_style_label_secondary(lv_obj_t *obj);

// Style: LabelSuccess
lv_style_t *get_style_label_success_MAIN_DEFAULT();
void add_style_label_success(lv_obj_t *obj);
void remove_style_label_success(lv_obj_t *obj);

// Style: LabelInfo
lv_style_t *get_style_label_info_MAIN_DEFAULT();
void add_style_label_info(lv_obj_t *obj);
void remove_style_label_info(lv_obj_t *obj);

// Style: LabelWarning
lv_style_t *get_style_label_warning_MAIN_DEFAULT();
void add_style_label_warning(lv_obj_t *obj);
void remove_style_label_warning(lv_obj_t *obj);

// Style: LabelDanger
lv_style_t *get_style_label_danger_MAIN_DEFAULT();
void add_style_label_danger(lv_obj_t *obj);
void remove_style_label_danger(lv_obj_t *obj);

// Style: IconFa16
lv_style_t *get_style_icon_fa16_MAIN_DEFAULT();
void add_style_icon_fa16(lv_obj_t *obj);
void remove_style_icon_fa16(lv_obj_t *obj);

// Style: IconFa22
lv_style_t *get_style_icon_fa22_MAIN_DEFAULT();
void add_style_icon_fa22(lv_obj_t *obj);
void remove_style_icon_fa22(lv_obj_t *obj);

// Style: IconFa28
lv_style_t *get_style_icon_fa28_MAIN_DEFAULT();
void add_style_icon_fa28(lv_obj_t *obj);
void remove_style_icon_fa28(lv_obj_t *obj);

// Style: IconFaAccent
lv_style_t *get_style_icon_fa_accent_MAIN_DEFAULT();
void add_style_icon_fa_accent(lv_obj_t *obj);
void remove_style_icon_fa_accent(lv_obj_t *obj);

// Style: IconFaAxisX
lv_style_t *get_style_icon_fa_axis_x_MAIN_DEFAULT();
void add_style_icon_fa_axis_x(lv_obj_t *obj);
void remove_style_icon_fa_axis_x(lv_obj_t *obj);

// Style: AxisChipX
lv_style_t *get_style_axis_chip_x_MAIN_DEFAULT();
void add_style_axis_chip_x(lv_obj_t *obj);
void remove_style_axis_chip_x(lv_obj_t *obj);

// Style: AxisChipY
lv_style_t *get_style_axis_chip_y_MAIN_DEFAULT();
void add_style_axis_chip_y(lv_obj_t *obj);
void remove_style_axis_chip_y(lv_obj_t *obj);

// Style: AxisChipZ
lv_style_t *get_style_axis_chip_z_MAIN_DEFAULT();
void add_style_axis_chip_z(lv_obj_t *obj);
void remove_style_axis_chip_z(lv_obj_t *obj);

// Style: AxisChipLabel
lv_style_t *get_style_axis_chip_label_MAIN_DEFAULT();
void add_style_axis_chip_label(lv_obj_t *obj);
void remove_style_axis_chip_label(lv_obj_t *obj);

// Style: StatusPill
lv_style_t *get_style_status_pill_MAIN_DEFAULT();
void add_style_status_pill(lv_obj_t *obj);
void remove_style_status_pill(lv_obj_t *obj);

// Style: StatusPillDot
lv_style_t *get_style_status_pill_dot_MAIN_DEFAULT();
void add_style_status_pill_dot(lv_obj_t *obj);
void remove_style_status_pill_dot(lv_obj_t *obj);

// Style: BrandDot
lv_style_t *get_style_brand_dot_MAIN_DEFAULT();
void add_style_brand_dot(lv_obj_t *obj);
void remove_style_brand_dot(lv_obj_t *obj);

// Style: StyleButtonDefault
lv_style_t *get_style_style_button_default_MAIN_DEFAULT();
lv_style_t *get_style_style_button_default_MAIN_PRESSED();
void add_style_style_button_default(lv_obj_t *obj);
void remove_style_style_button_default(lv_obj_t *obj);

// Style: BtnDark
lv_style_t *get_style_btn_dark_MAIN_DEFAULT();
void add_style_btn_dark(lv_obj_t *obj);
void remove_style_btn_dark(lv_obj_t *obj);

// Style: BtnAccentFill
lv_style_t *get_style_btn_accent_fill_MAIN_DEFAULT();
lv_style_t *get_style_btn_accent_fill_MAIN_PRESSED();
void add_style_btn_accent_fill(lv_obj_t *obj);
void remove_style_btn_accent_fill(lv_obj_t *obj);

// Style: BtnAccentSoft
lv_style_t *get_style_btn_accent_soft_MAIN_DEFAULT();
void add_style_btn_accent_soft(lv_obj_t *obj);
void remove_style_btn_accent_soft(lv_obj_t *obj);

// Style: BtnHold
lv_style_t *get_style_btn_hold_MAIN_DEFAULT();
void add_style_btn_hold(lv_obj_t *obj);
void remove_style_btn_hold(lv_obj_t *obj);

// Style: BtnEStop
lv_style_t *get_style_btn_estop_MAIN_DEFAULT();
void add_style_btn_estop(lv_obj_t *obj);
void remove_style_btn_estop(lv_obj_t *obj);

// Style: BtnDangerSoft
lv_style_t *get_style_btn_danger_soft_MAIN_DEFAULT();
void add_style_btn_danger_soft(lv_obj_t *obj);
void remove_style_btn_danger_soft(lv_obj_t *obj);

// Style: BtnRound
lv_style_t *get_style_btn_round_MAIN_DEFAULT();
void add_style_btn_round(lv_obj_t *obj);
void remove_style_btn_round(lv_obj_t *obj);

// Style: BtnDockInactive
lv_style_t *get_style_btn_dock_inactive_MAIN_DEFAULT();
void add_style_btn_dock_inactive(lv_obj_t *obj);
void remove_style_btn_dock_inactive(lv_obj_t *obj);

// Style: BtnDockActive
lv_style_t *get_style_btn_dock_active_MAIN_DEFAULT();
void add_style_btn_dock_active(lv_obj_t *obj);
void remove_style_btn_dock_active(lv_obj_t *obj);

// Style: BtnToggle
lv_style_t *get_style_btn_toggle_MAIN_DEFAULT();
lv_style_t *get_style_btn_toggle_MAIN_CHECKED();
void add_style_btn_toggle(lv_obj_t *obj);
void remove_style_btn_toggle(lv_obj_t *obj);

// Style: BtnSelector
lv_style_t *get_style_btn_selector_MAIN_DEFAULT();
lv_style_t *get_style_btn_selector_MAIN_CHECKED();
void add_style_btn_selector(lv_obj_t *obj);
void remove_style_btn_selector(lv_obj_t *obj);

// Style: BtnUnitsLeft
lv_style_t *get_style_btn_units_left_MAIN_DEFAULT();
lv_style_t *get_style_btn_units_left_MAIN_CHECKED();
void add_style_btn_units_left(lv_obj_t *obj);
void remove_style_btn_units_left(lv_obj_t *obj);

// Style: BtnJogPad
lv_style_t *get_style_btn_jog_pad_MAIN_DEFAULT();
lv_style_t *get_style_btn_jog_pad_MAIN_PRESSED();
void add_style_btn_jog_pad(lv_obj_t *obj);
void remove_style_btn_jog_pad(lv_obj_t *obj);

// Style: BtnSettingsNav
lv_style_t *get_style_btn_settings_nav_MAIN_DEFAULT();
lv_style_t *get_style_btn_settings_nav_MAIN_CHECKED();
void add_style_btn_settings_nav(lv_obj_t *obj);
void remove_style_btn_settings_nav(lv_obj_t *obj);

// Style: BtnFileRow
lv_style_t *get_style_btn_file_row_MAIN_DEFAULT();
lv_style_t *get_style_btn_file_row_MAIN_CHECKED();
void add_style_btn_file_row(lv_obj_t *obj);
void remove_style_btn_file_row(lv_obj_t *obj);

// Style: BtnWifiRow
lv_style_t *get_style_btn_wifi_row_MAIN_DEFAULT();
lv_style_t *get_style_btn_wifi_row_MAIN_PRESSED();
void add_style_btn_wifi_row(lv_obj_t *obj);
void remove_style_btn_wifi_row(lv_obj_t *obj);

// Style: BarDefault
lv_style_t *get_style_bar_default_MAIN_DEFAULT();
lv_style_t *get_style_bar_default_INDICATOR_DEFAULT();
void add_style_bar_default(lv_obj_t *obj);
void remove_style_bar_default(lv_obj_t *obj);

// Style: BarProgress
lv_style_t *get_style_bar_progress_MAIN_DEFAULT();
lv_style_t *get_style_bar_progress_INDICATOR_DEFAULT();
void add_style_bar_progress(lv_obj_t *obj);
void remove_style_bar_progress(lv_obj_t *obj);

// Style: ArcDefault
lv_style_t *get_style_arc_default_MAIN_DEFAULT();
lv_style_t *get_style_arc_default_INDICATOR_DEFAULT();
lv_style_t *get_style_arc_default_KNOB_DEFAULT();
void add_style_arc_default(lv_obj_t *obj);
void remove_style_arc_default(lv_obj_t *obj);

// Style: StyleDefaultSlider
lv_style_t *get_style_style_default_slider_MAIN_DEFAULT();
lv_style_t *get_style_style_default_slider_INDICATOR_DEFAULT();
lv_style_t *get_style_style_default_slider_KNOB_DEFAULT();
void add_style_style_default_slider(lv_obj_t *obj);
void remove_style_style_default_slider(lv_obj_t *obj);

// Style: SwitchDefault
lv_style_t *get_style_switch_default_MAIN_DEFAULT();
lv_style_t *get_style_switch_default_MAIN_CHECKED();
lv_style_t *get_style_switch_default_KNOB_DEFAULT();
lv_style_t *get_style_switch_default_KNOB_CHECKED();
lv_style_t *get_style_switch_default_INDICATOR_DEFAULT();
lv_style_t *get_style_switch_default_INDICATOR_CHECKED();
void add_style_switch_default(lv_obj_t *obj);
void remove_style_switch_default(lv_obj_t *obj);

// Style: KeyboardDefault
lv_style_t *get_style_keyboard_default_MAIN_DEFAULT();
lv_style_t *get_style_keyboard_default_ITEMS_DEFAULT();
lv_style_t *get_style_keyboard_default_ITEMS_CHECKED();
void add_style_keyboard_default(lv_obj_t *obj);
void remove_style_keyboard_default(lv_obj_t *obj);

// Style: TextareaDefault
lv_style_t *get_style_textarea_default_MAIN_DEFAULT();
lv_style_t *get_style_textarea_default_MAIN_FOCUSED();
void add_style_textarea_default(lv_obj_t *obj);
void remove_style_textarea_default(lv_obj_t *obj);

// Style: DropdownDefault
lv_style_t *get_style_dropdown_default_MAIN_DEFAULT();
void add_style_dropdown_default(lv_obj_t *obj);
void remove_style_dropdown_default(lv_obj_t *obj);

// Style: CheckboxDefault
lv_style_t *get_style_checkbox_default_MAIN_DEFAULT();
void add_style_checkbox_default(lv_obj_t *obj);
void remove_style_checkbox_default(lv_obj_t *obj);

// Style: LEDDefault
lv_style_t *get_style_led_default_MAIN_DEFAULT();
void add_style_led_default(lv_obj_t *obj);
void remove_style_led_default(lv_obj_t *obj);

// Style: ListDefault
lv_style_t *get_style_list_default_MAIN_DEFAULT();
void add_style_list_default(lv_obj_t *obj);
void remove_style_list_default(lv_obj_t *obj);

// Style: MessageBoxDefault
lv_style_t *get_style_message_box_default_MAIN_DEFAULT();
void add_style_message_box_default(lv_obj_t *obj);
void remove_style_message_box_default(lv_obj_t *obj);

// Style: RollerDefault
lv_style_t *get_style_roller_default_MAIN_DEFAULT();
void add_style_roller_default(lv_obj_t *obj);
void remove_style_roller_default(lv_obj_t *obj);

// Style: SpinnerDefault
lv_style_t *get_style_spinner_default_MAIN_DEFAULT();
lv_style_t *get_style_spinner_default_INDICATOR_DEFAULT();
void add_style_spinner_default(lv_obj_t *obj);
void remove_style_spinner_default(lv_obj_t *obj);

// Style: TabDefault
lv_style_t *get_style_tab_default_MAIN_DEFAULT();
void add_style_tab_default(lv_obj_t *obj);
void remove_style_tab_default(lv_obj_t *obj);

// Style: TabViewDefault
lv_style_t *get_style_tab_view_default_MAIN_DEFAULT();
void add_style_tab_view_default(lv_obj_t *obj);
void remove_style_tab_view_default(lv_obj_t *obj);

// Style: DefaultButtonMatrix
lv_style_t *get_style_default_button_matrix_MAIN_DEFAULT();
lv_style_t *get_style_default_button_matrix_ITEMS_DEFAULT();
void add_style_default_button_matrix(lv_obj_t *obj);
void remove_style_default_button_matrix(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/