#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_page_wifi_setup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_wifi_setup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // wifi_brand_dot
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_brand_dot = obj;
            lv_obj_set_pos(obj, 24, 20);
            lv_obj_set_size(obj, 8, 8);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_brand_dot(obj);
        }
        {
            // wifi_brand
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_brand = obj;
            lv_obj_set_pos(obj, 40, 17);
            lv_obj_set_size(obj, 160, 14);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_brand(obj);
            lv_label_set_text(obj, "FLUIDCNC");
        }
        {
            // wifi_brand_sub
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_brand_sub = obj;
            lv_obj_set_pos(obj, 124, 17);
            lv_obj_set_size(obj, 200, 14);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_muted(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "PENDANT SETUP");
        }
        {
            // wifi_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_title = obj;
            lv_obj_set_pos(obj, 24, 64);
            lv_obj_set_size(obj, 976, 28);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_heading(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Connect to WiFi");
        }
        {
            // wifi_sub
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_sub = obj;
            lv_obj_set_pos(obj, 24, 98);
            lv_obj_set_size(obj, 976, 18);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_secondary(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Choose a network and enter the password.");
        }
        {
            // wifi_btn_refresh
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.wifi_btn_refresh = obj;
            lv_obj_set_pos(obj, 860, 140);
            lv_obj_set_size(obj, 140, 36);
            lv_obj_add_event_cb(obj, action_wifi_scan, LV_EVENT_CLICKED, (void *)0);
            add_style_btn_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // wifi_btn_refresh_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_btn_refresh_icon = obj;
                    lv_obj_set_pos(obj, 8, 4);
                    lv_obj_set_size(obj, 26, 26);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_icon_fa22(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uf021");
                }
                {
                    // wifi_btn_refresh_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_btn_refresh_lbl = obj;
                    lv_obj_set_pos(obj, 36, 10);
                    lv_obj_set_size(obj, 92, 16);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Scan again");
                }
            }
        }
        {
            // wifi_scan_list
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_scan_list = obj;
            lv_obj_set_pos(obj, 24, 196);
            lv_obj_set_size(obj, 976, 324);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_dark_inset(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // wifi_net_0
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_net_0 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 944, 56);
                    lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_btn_wifi_row(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_0 = obj;
                            lv_obj_set_pos(obj, 12, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1eb");
                        }
                        {
                            // wifi_net_ssid_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_0 = obj;
                            lv_obj_set_pos(obj, 48, 19);
                            lv_obj_set_size(obj, 670, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_0
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_0 = obj;
                            lv_obj_set_pos(obj, 730, 0);
                            lv_obj_set_size(obj, 30, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_0
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_0 = obj;
                                    lv_obj_set_pos(obj, 0, 36);
                                    lv_obj_set_size(obj, 8, 8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar2_0
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_0 = obj;
                                    lv_obj_set_pos(obj, 11, 30);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar3_0
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_0 = obj;
                                    lv_obj_set_pos(obj, 22, 24);
                                    lv_obj_set_size(obj, 8, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_0 = obj;
                            lv_obj_set_pos(obj, 774, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // wifi_net_act_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_act_0 = obj;
                            lv_obj_set_pos(obj, 812, 19);
                            lv_obj_set_size(obj, 110, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
                {
                    // wifi_net_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_net_1 = obj;
                    lv_obj_set_pos(obj, 0, 64);
                    lv_obj_set_size(obj, 944, 56);
                    lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_btn_wifi_row(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_1 = obj;
                            lv_obj_set_pos(obj, 12, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1eb");
                        }
                        {
                            // wifi_net_ssid_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_1 = obj;
                            lv_obj_set_pos(obj, 48, 19);
                            lv_obj_set_size(obj, 670, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_1
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_1 = obj;
                            lv_obj_set_pos(obj, 730, 0);
                            lv_obj_set_size(obj, 30, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_1 = obj;
                                    lv_obj_set_pos(obj, 0, 36);
                                    lv_obj_set_size(obj, 8, 8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar2_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_1 = obj;
                                    lv_obj_set_pos(obj, 11, 30);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar3_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_1 = obj;
                                    lv_obj_set_pos(obj, 22, 24);
                                    lv_obj_set_size(obj, 8, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_1 = obj;
                            lv_obj_set_pos(obj, 774, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // wifi_net_act_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_act_1 = obj;
                            lv_obj_set_pos(obj, 812, 19);
                            lv_obj_set_size(obj, 110, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
                {
                    // wifi_net_2
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_net_2 = obj;
                    lv_obj_set_pos(obj, 0, 128);
                    lv_obj_set_size(obj, 944, 56);
                    lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)2);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_btn_wifi_row(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_2 = obj;
                            lv_obj_set_pos(obj, 12, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1eb");
                        }
                        {
                            // wifi_net_ssid_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_2 = obj;
                            lv_obj_set_pos(obj, 48, 19);
                            lv_obj_set_size(obj, 670, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_2
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_2 = obj;
                            lv_obj_set_pos(obj, 730, 0);
                            lv_obj_set_size(obj, 30, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_2
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_2 = obj;
                                    lv_obj_set_pos(obj, 0, 36);
                                    lv_obj_set_size(obj, 8, 8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar2_2
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_2 = obj;
                                    lv_obj_set_pos(obj, 11, 30);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar3_2
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_2 = obj;
                                    lv_obj_set_pos(obj, 22, 24);
                                    lv_obj_set_size(obj, 8, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_2 = obj;
                            lv_obj_set_pos(obj, 774, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // wifi_net_act_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_act_2 = obj;
                            lv_obj_set_pos(obj, 812, 19);
                            lv_obj_set_size(obj, 110, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
                {
                    // wifi_net_3
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_net_3 = obj;
                    lv_obj_set_pos(obj, 0, 192);
                    lv_obj_set_size(obj, 944, 56);
                    lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)3);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_btn_wifi_row(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_3 = obj;
                            lv_obj_set_pos(obj, 12, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1eb");
                        }
                        {
                            // wifi_net_ssid_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_3 = obj;
                            lv_obj_set_pos(obj, 48, 19);
                            lv_obj_set_size(obj, 670, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_3
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_3 = obj;
                            lv_obj_set_pos(obj, 730, 0);
                            lv_obj_set_size(obj, 30, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_3
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_3 = obj;
                                    lv_obj_set_pos(obj, 0, 36);
                                    lv_obj_set_size(obj, 8, 8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar2_3
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_3 = obj;
                                    lv_obj_set_pos(obj, 11, 30);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar3_3
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_3 = obj;
                                    lv_obj_set_pos(obj, 22, 24);
                                    lv_obj_set_size(obj, 8, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_3 = obj;
                            lv_obj_set_pos(obj, 774, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // wifi_net_act_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_act_3 = obj;
                            lv_obj_set_pos(obj, 812, 19);
                            lv_obj_set_size(obj, 110, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
                {
                    // wifi_net_4
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_net_4 = obj;
                    lv_obj_set_pos(obj, 0, 256);
                    lv_obj_set_size(obj, 944, 56);
                    lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)4);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_btn_wifi_row(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_4 = obj;
                            lv_obj_set_pos(obj, 12, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1eb");
                        }
                        {
                            // wifi_net_ssid_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_4 = obj;
                            lv_obj_set_pos(obj, 48, 19);
                            lv_obj_set_size(obj, 670, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_4
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_4 = obj;
                            lv_obj_set_pos(obj, 730, 0);
                            lv_obj_set_size(obj, 30, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_4
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_4 = obj;
                                    lv_obj_set_pos(obj, 0, 36);
                                    lv_obj_set_size(obj, 8, 8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar2_4
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_4 = obj;
                                    lv_obj_set_pos(obj, 11, 30);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar3_4
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_4 = obj;
                                    lv_obj_set_pos(obj, 22, 24);
                                    lv_obj_set_size(obj, 8, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_4 = obj;
                            lv_obj_set_pos(obj, 774, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // wifi_net_act_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_act_4 = obj;
                            lv_obj_set_pos(obj, 812, 19);
                            lv_obj_set_size(obj, 110, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
                {
                    // wifi_net_5
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_net_5 = obj;
                    lv_obj_set_pos(obj, 0, 320);
                    lv_obj_set_size(obj, 944, 56);
                    lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)5);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_btn_wifi_row(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_5 = obj;
                            lv_obj_set_pos(obj, 12, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1eb");
                        }
                        {
                            // wifi_net_ssid_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_5 = obj;
                            lv_obj_set_pos(obj, 48, 19);
                            lv_obj_set_size(obj, 670, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_5
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_5 = obj;
                            lv_obj_set_pos(obj, 730, 0);
                            lv_obj_set_size(obj, 30, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_5
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_5 = obj;
                                    lv_obj_set_pos(obj, 0, 36);
                                    lv_obj_set_size(obj, 8, 8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar2_5
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_5 = obj;
                                    lv_obj_set_pos(obj, 11, 30);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar3_5
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_5 = obj;
                                    lv_obj_set_pos(obj, 22, 24);
                                    lv_obj_set_size(obj, 8, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_5 = obj;
                            lv_obj_set_pos(obj, 774, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // wifi_net_act_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_act_5 = obj;
                            lv_obj_set_pos(obj, 812, 19);
                            lv_obj_set_size(obj, 110, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
                {
                    // wifi_net_6
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_net_6 = obj;
                    lv_obj_set_pos(obj, 0, 384);
                    lv_obj_set_size(obj, 944, 56);
                    lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)6);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_btn_wifi_row(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_6 = obj;
                            lv_obj_set_pos(obj, 12, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1eb");
                        }
                        {
                            // wifi_net_ssid_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_6 = obj;
                            lv_obj_set_pos(obj, 48, 19);
                            lv_obj_set_size(obj, 670, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_6
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_6 = obj;
                            lv_obj_set_pos(obj, 730, 0);
                            lv_obj_set_size(obj, 30, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_6
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_6 = obj;
                                    lv_obj_set_pos(obj, 0, 36);
                                    lv_obj_set_size(obj, 8, 8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar2_6
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_6 = obj;
                                    lv_obj_set_pos(obj, 11, 30);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar3_6
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_6 = obj;
                                    lv_obj_set_pos(obj, 22, 24);
                                    lv_obj_set_size(obj, 8, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_6 = obj;
                            lv_obj_set_pos(obj, 774, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // wifi_net_act_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_act_6 = obj;
                            lv_obj_set_pos(obj, 812, 19);
                            lv_obj_set_size(obj, 110, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
                {
                    // wifi_net_7
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_net_7 = obj;
                    lv_obj_set_pos(obj, 0, 448);
                    lv_obj_set_size(obj, 944, 56);
                    lv_obj_add_event_cb(obj, action_wifi_select_network, LV_EVENT_CLICKED, (void *)7);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_btn_wifi_row(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_net_icon_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_icon_7 = obj;
                            lv_obj_set_pos(obj, 12, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1eb");
                        }
                        {
                            // wifi_net_ssid_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_ssid_7 = obj;
                            lv_obj_set_pos(obj, 48, 19);
                            lv_obj_set_size(obj, 670, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "");
                        }
                        {
                            // wifi_net_signal_7
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.wifi_net_signal_7 = obj;
                            lv_obj_set_pos(obj, 730, 0);
                            lv_obj_set_size(obj, 30, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_style_panel_default(obj);
                            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // wifi_net_bar1_7
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar1_7 = obj;
                                    lv_obj_set_pos(obj, 0, 36);
                                    lv_obj_set_size(obj, 8, 8);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar2_7
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar2_7 = obj;
                                    lv_obj_set_pos(obj, 11, 30);
                                    lv_obj_set_size(obj, 8, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // wifi_net_bar3_7
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.wifi_net_bar3_7 = obj;
                                    lv_obj_set_pos(obj, 22, 24);
                                    lv_obj_set_size(obj, 8, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_style_panel_default(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 80, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                            }
                        }
                        {
                            // wifi_net_lock_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_lock_7 = obj;
                            lv_obj_set_pos(obj, 774, 15);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // wifi_net_act_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_net_act_7 = obj;
                            lv_obj_set_pos(obj, 812, 19);
                            lv_obj_set_size(obj, 110, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Connect");
                        }
                    }
                }
                {
                    // wifi_scan_spinner
                    lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
                    objects.wifi_scan_spinner = obj;
                    lv_obj_set_pos(obj, 458, 4);
                    lv_obj_set_size(obj, 28, 28);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                    add_style_spinner_default(obj);
                }
                {
                    // wifi_scan_status
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_scan_status = obj;
                    lv_obj_set_pos(obj, 0, 38);
                    lv_obj_set_size(obj, 944, 22);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Tap Scan again to search for WiFi networks.");
                }
            }
        }
        {
            // wifi_password_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_password_panel = obj;
            lv_obj_set_pos(obj, 24, 60);
            lv_obj_set_size(obj, 976, 470);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // wifi_pwd_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_pwd_caption = obj;
                    lv_obj_set_pos(obj, 20, 12);
                    lv_obj_set_size(obj, 240, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_caption(obj);
                    lv_label_set_text(obj, "ENTER PASSWORD");
                }
                {
                    // wifi_pwd_ssid
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_pwd_ssid = obj;
                    lv_obj_set_pos(obj, 20, 32);
                    lv_obj_set_size(obj, 936, 28);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_heading(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "(none)");
                }
                {
                    // wifi_pwd_input
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.wifi_pwd_input = obj;
                    lv_obj_set_pos(obj, 20, 72);
                    lv_obj_set_size(obj, 880, 56);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "Password");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, true);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_textarea_default(obj);
                }
                {
                    // wifi_pwd_reveal
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_pwd_reveal = obj;
                    lv_obj_set_pos(obj, 908, 72);
                    lv_obj_set_size(obj, 48, 56);
                    lv_obj_add_event_cb(obj, action_wifi_toggle_password_reveal, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_dark(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_pwd_reveal_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_pwd_reveal_icon = obj;
                            lv_obj_set_pos(obj, 0, 17);
                            lv_obj_set_size(obj, 48, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf06e");
                        }
                    }
                }
                {
                    // wifi_pwd_divider
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.wifi_pwd_divider = obj;
                    lv_obj_set_pos(obj, 20, 136);
                    lv_obj_set_size(obj, 936, 1);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_transparent(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // wifi_pwd_keyboard
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    objects.wifi_pwd_keyboard = obj;
                    lv_obj_set_pos(obj, 20, 144);
                    lv_obj_set_size(obj, 936, 260);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_keyboard_default(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // wifi_pwd_cancel
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_pwd_cancel = obj;
                    lv_obj_set_pos(obj, 20, 412);
                    lv_obj_set_size(obj, 160, 48);
                    lv_obj_add_event_cb(obj, action_wifi_back, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_dark(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_pwd_cancel_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_pwd_cancel_lbl = obj;
                            lv_obj_set_pos(obj, 0, 16);
                            lv_obj_set_size(obj, 160, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "CANCEL");
                        }
                    }
                }
                {
                    // wifi_pwd_connect
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.wifi_pwd_connect = obj;
                    lv_obj_set_pos(obj, 776, 412);
                    lv_obj_set_size(obj, 180, 48);
                    lv_obj_add_event_cb(obj, action_wifi_password_submit, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_accent_fill(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_pwd_connect_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_pwd_connect_lbl = obj;
                            lv_obj_set_pos(obj, 0, 16);
                            lv_obj_set_size(obj, 180, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "CONNECT");
                        }
                    }
                }
            }
        }
        {
            // wifi_btn_skip
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.wifi_btn_skip = obj;
            lv_obj_set_pos(obj, 780, 536);
            lv_obj_set_size(obj, 220, 40);
            lv_obj_add_event_cb(obj, action_wifi_skip_to_serial, LV_EVENT_CLICKED, (void *)0);
            add_style_btn_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // wifi_btn_skip_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_btn_skip_lbl = obj;
                    lv_obj_set_pos(obj, 0, 11);
                    lv_obj_set_size(obj, 220, 18);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Skip - Use Serial Only");
                }
            }
        }
        {
            // wifi_connecting_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wifi_connecting_panel = obj;
            lv_obj_set_pos(obj, 252, 190);
            lv_obj_set_size(obj, 520, 220);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // wifi_connecting_spinner
                    lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
                    objects.wifi_connecting_spinner = obj;
                    lv_obj_set_pos(obj, 232, 28);
                    lv_obj_set_size(obj, 56, 56);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                    add_style_spinner_default(obj);
                }
                {
                    // wifi_connecting_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_connecting_caption = obj;
                    lv_obj_set_pos(obj, 0, 104);
                    lv_obj_set_size(obj, 520, 18);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_caption(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "CONNECTING TO");
                }
                {
                    // wifi_connecting_ssid
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_connecting_ssid = obj;
                    lv_obj_set_pos(obj, 0, 128);
                    lv_obj_set_size(obj, 520, 28);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_heading(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
                {
                    // wifi_connecting_hint
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.wifi_connecting_hint = obj;
                    lv_obj_set_pos(obj, 0, 168);
                    lv_obj_set_size(obj, 520, 18);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Hold for ~10 seconds...");
                }
            }
        }
    }
    
    tick_screen_page_wifi_setup();
}

void tick_screen_page_wifi_setup() {
}

void create_screen_page_fluid_connect() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_fluid_connect = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // fluid_brand_dot
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fluid_brand_dot = obj;
            lv_obj_set_pos(obj, 24, 20);
            lv_obj_set_size(obj, 8, 8);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_brand_dot(obj);
        }
        {
            // fluid_brand
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fluid_brand = obj;
            lv_obj_set_pos(obj, 40, 17);
            lv_obj_set_size(obj, 160, 14);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_brand(obj);
            lv_label_set_text(obj, "FLUIDCNC");
        }
        {
            // fluid_brand_sub
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fluid_brand_sub = obj;
            lv_obj_set_pos(obj, 124, 17);
            lv_obj_set_size(obj, 280, 14);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_muted(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "CONNECTION");
        }
        {
            // fluid_wifi_dot
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fluid_wifi_dot = obj;
            lv_obj_set_pos(obj, 780, 21);
            lv_obj_set_size(obj, 8, 8);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_brand_dot(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fluid_wifi_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fluid_wifi_lbl = obj;
            lv_obj_set_pos(obj, 796, 17);
            lv_obj_set_size(obj, 200, 14);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_success(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "WiFi: TrailCurrent-IoT");
        }
        {
            // fluid_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fluid_title = obj;
            lv_obj_set_pos(obj, 24, 64);
            lv_obj_set_size(obj, 976, 28);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_heading(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Connect to FluidNC");
        }
        {
            // fluid_sub
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fluid_sub = obj;
            lv_obj_set_pos(obj, 24, 98);
            lv_obj_set_size(obj, 976, 18);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_secondary(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Choose how this pendant talks to the FluidNC controller.");
        }
        {
            // fluid_tport_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fluid_tport_card = obj;
            lv_obj_set_pos(obj, 24, 140);
            lv_obj_set_size(obj, 672, 180);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // fluid_tport_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fluid_tport_caption = obj;
                    lv_obj_set_pos(obj, 18, 14);
                    lv_obj_set_size(obj, 200, 12);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_caption(obj);
                    lv_label_set_text(obj, "TRANSPORT");
                }
                {
                    // fluid_tport_0
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.fluid_tport_0 = obj;
                    lv_obj_set_pos(obj, 18, 36);
                    lv_obj_set_size(obj, 204, 124);
                    lv_obj_add_event_cb(obj, action_set_fluid_transport, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                    add_style_btn_selector(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // fluid_tport_icon_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_icon_0 = obj;
                            lv_obj_set_pos(obj, 12, 12);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf120");
                        }
                        {
                            // fluid_tport_name_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_name_0 = obj;
                            lv_obj_set_pos(obj, 14, 56);
                            lv_obj_set_size(obj, 176, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Serial UART");
                        }
                        {
                            // fluid_tport_sub_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_sub_0 = obj;
                            lv_obj_set_pos(obj, 14, 80);
                            lv_obj_set_size(obj, 176, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Direct wired to board");
                        }
                    }
                }
                {
                    // fluid_tport_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.fluid_tport_1 = obj;
                    lv_obj_set_pos(obj, 234, 36);
                    lv_obj_set_size(obj, 204, 124);
                    lv_obj_add_event_cb(obj, action_set_fluid_transport, LV_EVENT_CLICKED, (void *)1);
                    add_style_btn_selector(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // fluid_tport_icon_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_icon_1 = obj;
                            lv_obj_set_pos(obj, 12, 12);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf6ff");
                        }
                        {
                            // fluid_tport_name_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_name_1 = obj;
                            lv_obj_set_pos(obj, 14, 56);
                            lv_obj_set_size(obj, 176, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "WebSocket");
                        }
                        {
                            // fluid_tport_sub_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_sub_1 = obj;
                            lv_obj_set_pos(obj, 14, 80);
                            lv_obj_set_size(obj, 176, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "ws://<host>:81");
                        }
                    }
                }
                {
                    // fluid_tport_2
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.fluid_tport_2 = obj;
                    lv_obj_set_pos(obj, 450, 36);
                    lv_obj_set_size(obj, 204, 124);
                    lv_obj_add_event_cb(obj, action_set_fluid_transport, LV_EVENT_CLICKED, (void *)2);
                    add_style_btn_selector(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // fluid_tport_icon_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_icon_2 = obj;
                            lv_obj_set_pos(obj, 12, 12);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf233");
                        }
                        {
                            // fluid_tport_name_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_name_2 = obj;
                            lv_obj_set_pos(obj, 14, 56);
                            lv_obj_set_size(obj, 176, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Telnet");
                        }
                        {
                            // fluid_tport_sub_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_tport_sub_2 = obj;
                            lv_obj_set_pos(obj, 14, 80);
                            lv_obj_set_size(obj, 176, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "telnet://<host>");
                        }
                    }
                }
            }
        }
        {
            // fluid_host_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fluid_host_card = obj;
            lv_obj_set_pos(obj, 24, 336);
            lv_obj_set_size(obj, 672, 130);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // fluid_host_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fluid_host_caption = obj;
                    lv_obj_set_pos(obj, 18, 14);
                    lv_obj_set_size(obj, 200, 12);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_caption(obj);
                    lv_label_set_text(obj, "FLUIDNC HOST");
                }
                {
                    // fluid_host_sub
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fluid_host_sub = obj;
                    lv_obj_set_pos(obj, 18, 30);
                    lv_obj_set_size(obj, 636, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_muted(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Hostname or IP address. Port 81 for FluidNC 3.x, 80 for 4.x.");
                }
                {
                    // fluid_host_input
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.fluid_host_input = obj;
                    lv_obj_set_pos(obj, 18, 56);
                    lv_obj_set_size(obj, 322, 44);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "fluidnc.local");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, action_fluid_edit_field, LV_EVENT_CLICKED, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_textarea_default(obj);
                }
                {
                    // fluid_port_input
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.fluid_port_input = obj;
                    lv_obj_set_pos(obj, 352, 56);
                    lv_obj_set_size(obj, 110, 44);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "81");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, action_fluid_edit_field, LV_EVENT_CLICKED, (void *)1);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_textarea_default(obj);
                }
                {
                    // fluid_btn_connect
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.fluid_btn_connect = obj;
                    lv_obj_set_pos(obj, 474, 56);
                    lv_obj_set_size(obj, 180, 44);
                    lv_obj_add_event_cb(obj, action_fluid_connect, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_accent_fill(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // fluid_btn_connect_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_btn_connect_icon = obj;
                            lv_obj_set_pos(obj, 14, 9);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf1d8");
                        }
                        {
                            // fluid_btn_connect_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_btn_connect_lbl = obj;
                            lv_obj_set_pos(obj, 44, 14);
                            lv_obj_set_size(obj, 130, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "CONNECT");
                        }
                    }
                }
            }
        }
        {
            // fluid_image_card
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fluid_image_card = obj;
            lv_obj_set_pos(obj, 712, 140);
            lv_obj_set_size(obj, 300, 326);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            add_style_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // fluid_image_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fluid_image_caption = obj;
                    lv_obj_set_pos(obj, 14, 12);
                    lv_obj_set_size(obj, 272, 14);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_caption(obj);
                    lv_label_set_text(obj, "TARGET MACHINE");
                }
                {
                    // fluid_image_machine
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.fluid_image_machine = obj;
                    lv_obj_set_pos(obj, 10, 36);
                    lv_obj_set_size(obj, 280, 280);
                    lv_img_set_src(obj, &img_cnc_machine);
                    lv_obj_set_style_radius(obj, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // fluid_status_dot
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fluid_status_dot = obj;
            lv_obj_set_pos(obj, 24, 490);
            lv_obj_set_size(obj, 8, 8);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_brand_dot(obj);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // fluid_status_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.fluid_status_lbl = obj;
            lv_obj_set_pos(obj, 38, 484);
            lv_obj_set_size(obj, 784, 16);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_label_secondary(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Disconnected");
        }
        {
            // fluid_btn_back
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.fluid_btn_back = obj;
            lv_obj_set_pos(obj, 800, 482);
            lv_obj_set_size(obj, 180, 36);
            lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)7);
            add_style_btn_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // fluid_btn_back_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fluid_btn_back_lbl = obj;
                    lv_obj_set_pos(obj, 0, 9);
                    lv_obj_set_size(obj, 180, 16);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back to Settings");
                }
            }
        }
        {
            // fluid_edit_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fluid_edit_panel = obj;
            lv_obj_set_pos(obj, 24, 60);
            lv_obj_set_size(obj, 976, 470);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // fluid_edit_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fluid_edit_caption = obj;
                    lv_obj_set_pos(obj, 20, 12);
                    lv_obj_set_size(obj, 240, 14);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_caption(obj);
                    lv_label_set_text(obj, "EDIT FIELD");
                }
                {
                    // fluid_edit_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.fluid_edit_label = obj;
                    lv_obj_set_pos(obj, 20, 32);
                    lv_obj_set_size(obj, 936, 28);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_heading(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Host or IP");
                }
                {
                    // fluid_edit_input
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.fluid_edit_input = obj;
                    lv_obj_set_pos(obj, 20, 72);
                    lv_obj_set_size(obj, 936, 56);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "fluidnc.local");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, action_fluid_edit_done, LV_EVENT_READY, (void *)0);
                    lv_obj_add_event_cb(obj, action_fluid_kb_hide, LV_EVENT_CANCEL, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_textarea_default(obj);
                }
                {
                    // fluid_edit_divider
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.fluid_edit_divider = obj;
                    lv_obj_set_pos(obj, 20, 136);
                    lv_obj_set_size(obj, 936, 1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_panel_transparent(obj);
                }
                {
                    // fluid_edit_keyboard
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    objects.fluid_edit_keyboard = obj;
                    lv_obj_set_pos(obj, 20, 144);
                    lv_obj_set_size(obj, 936, 260);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_keyboard_default(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // fluid_edit_cancel
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.fluid_edit_cancel = obj;
                    lv_obj_set_pos(obj, 20, 412);
                    lv_obj_set_size(obj, 160, 48);
                    lv_obj_add_event_cb(obj, action_fluid_kb_hide, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_dark(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // fluid_edit_cancel_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_edit_cancel_lbl = obj;
                            lv_obj_set_pos(obj, 0, 16);
                            lv_obj_set_size(obj, 160, 14);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "CANCEL");
                        }
                    }
                }
                {
                    // fluid_edit_done
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.fluid_edit_done = obj;
                    lv_obj_set_pos(obj, 776, 412);
                    lv_obj_set_size(obj, 180, 48);
                    lv_obj_add_event_cb(obj, action_fluid_edit_done, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_accent_fill(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // fluid_edit_done_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.fluid_edit_done_lbl = obj;
                            lv_obj_set_pos(obj, 0, 16);
                            lv_obj_set_size(obj, 180, 14);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "DONE");
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_page_fluid_connect();
}

void tick_screen_page_fluid_connect() {
}

void create_screen_page_dashboard() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_dashboard = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // PageDashboard_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_dashboard_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_status_bar(obj, 159);
        }
        {
            // PageDashboard_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_dashboard_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 488);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_transparent(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dash_dro_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_dro_card = obj;
                    lv_obj_set_pos(obj, 12, 0);
                    lv_obj_set_size(obj, 640, 312);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_dro_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_dro_caption = obj;
                            lv_obj_set_pos(obj, 16, 12);
                            lv_obj_set_size(obj, 240, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "WORK POSITION");
                        }
                        {
                            // dash_dro_unit
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_dro_unit = obj;
                            lv_obj_set_pos(obj, 590, 12);
                            lv_obj_set_size(obj, 30, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "mm");
                        }
                        {
                            // dash_dro_chip_x
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.dash_dro_chip_x = obj;
                            lv_obj_set_pos(obj, 16, 50);
                            lv_obj_set_size(obj, 36, 36);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_axis_chip_x(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_dro_chip_label_x
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_dro_chip_label_x = obj;
                                    lv_obj_set_pos(obj, 0, 9);
                                    lv_obj_set_size(obj, 36, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_axis_chip_label(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "X");
                                }
                            }
                        }
                        {
                            // dash_dro_x
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_dro_x = obj;
                            lv_obj_set_pos(obj, 64, 50);
                            lv_obj_set_size(obj, 486, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_dro(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                        {
                            // dash_dro_zero_x
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_dro_zero_x = obj;
                            lv_obj_set_pos(obj, 556, 56);
                            lv_obj_set_size(obj, 76, 26);
                            lv_obj_add_event_cb(obj, action_zero_axis, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_dro_zero_lbl_x
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_dro_zero_lbl_x = obj;
                                    lv_obj_set_pos(obj, 0, 7);
                                    lv_obj_set_size(obj, 76, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "ZERO");
                                }
                            }
                        }
                        {
                            // dash_dro_chip_y
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.dash_dro_chip_y = obj;
                            lv_obj_set_pos(obj, 16, 130);
                            lv_obj_set_size(obj, 36, 36);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_axis_chip_y(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_dro_chip_label_y
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_dro_chip_label_y = obj;
                                    lv_obj_set_pos(obj, 0, 9);
                                    lv_obj_set_size(obj, 36, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_axis_chip_label(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Y");
                                }
                            }
                        }
                        {
                            // dash_dro_y
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_dro_y = obj;
                            lv_obj_set_pos(obj, 64, 130);
                            lv_obj_set_size(obj, 486, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_dro(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                        {
                            // dash_dro_zero_y
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_dro_zero_y = obj;
                            lv_obj_set_pos(obj, 556, 136);
                            lv_obj_set_size(obj, 76, 26);
                            lv_obj_add_event_cb(obj, action_zero_axis, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_dro_zero_lbl_y
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_dro_zero_lbl_y = obj;
                                    lv_obj_set_pos(obj, 0, 7);
                                    lv_obj_set_size(obj, 76, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "ZERO");
                                }
                            }
                        }
                        {
                            // dash_dro_chip_z
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.dash_dro_chip_z = obj;
                            lv_obj_set_pos(obj, 16, 210);
                            lv_obj_set_size(obj, 36, 36);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_axis_chip_z(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_dro_chip_label_z
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_dro_chip_label_z = obj;
                                    lv_obj_set_pos(obj, 0, 9);
                                    lv_obj_set_size(obj, 36, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_axis_chip_label(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Z");
                                }
                            }
                        }
                        {
                            // dash_dro_z
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_dro_z = obj;
                            lv_obj_set_pos(obj, 64, 210);
                            lv_obj_set_size(obj, 486, 50);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_dro(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                        {
                            // dash_dro_zero_z
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_dro_zero_z = obj;
                            lv_obj_set_pos(obj, 556, 216);
                            lv_obj_set_size(obj, 76, 26);
                            lv_obj_add_event_cb(obj, action_zero_axis, LV_EVENT_CLICKED, (void *)2);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_dro_zero_lbl_z
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_dro_zero_lbl_z = obj;
                                    lv_obj_set_pos(obj, 0, 7);
                                    lv_obj_set_size(obj, 76, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "ZERO");
                                }
                            }
                        }
                    }
                }
                {
                    // dash_ov_card_feed
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_ov_card_feed = obj;
                    lv_obj_set_pos(obj, 12, 324);
                    lv_obj_set_size(obj, 205, 152);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_ov_lbl_feed
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_ov_lbl_feed = obj;
                            lv_obj_set_pos(obj, 10, 8);
                            lv_obj_set_size(obj, 145, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "FEED");
                        }
                        {
                            // dash_ov_val_feed
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_ov_val_feed = obj;
                            lv_obj_set_pos(obj, 145, 8);
                            lv_obj_set_size(obj, 50, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "100%");
                        }
                        {
                            // dash_ov_dec_feed
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_ov_dec_feed = obj;
                            lv_obj_set_pos(obj, 10, 32);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_add_event_cb(obj, action_adjust_override, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_ov_dec_lbl_feed
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_ov_dec_lbl_feed = obj;
                                    lv_obj_set_pos(obj, 0, 4);
                                    lv_obj_set_size(obj, 26, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "-");
                                }
                            }
                        }
                        {
                            // dash_ov_bar_feed
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.dash_ov_bar_feed = obj;
                            lv_obj_set_pos(obj, 42, 42);
                            lv_obj_set_size(obj, 125, 6);
                            lv_bar_set_value(obj, 100, LV_ANIM_OFF);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                            add_style_bar_default(obj);
                        }
                        {
                            // dash_ov_inc_feed
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_ov_inc_feed = obj;
                            lv_obj_set_pos(obj, 169, 32);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_add_event_cb(obj, action_adjust_override, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_ov_inc_lbl_feed
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_ov_inc_lbl_feed = obj;
                                    lv_obj_set_pos(obj, 0, 4);
                                    lv_obj_set_size(obj, 26, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "+");
                                }
                            }
                        }
                    }
                }
                {
                    // dash_ov_card_rapid
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_ov_card_rapid = obj;
                    lv_obj_set_pos(obj, 229, 324);
                    lv_obj_set_size(obj, 205, 152);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_ov_lbl_rapid
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_ov_lbl_rapid = obj;
                            lv_obj_set_pos(obj, 10, 8);
                            lv_obj_set_size(obj, 145, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "RAPID");
                        }
                        {
                            // dash_ov_val_rapid
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_ov_val_rapid = obj;
                            lv_obj_set_pos(obj, 145, 8);
                            lv_obj_set_size(obj, 50, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "100%");
                        }
                        {
                            // dash_ov_dec_rapid
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_ov_dec_rapid = obj;
                            lv_obj_set_pos(obj, 10, 32);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_add_event_cb(obj, action_adjust_override, LV_EVENT_CLICKED, (void *)2);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_ov_dec_lbl_rapid
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_ov_dec_lbl_rapid = obj;
                                    lv_obj_set_pos(obj, 0, 4);
                                    lv_obj_set_size(obj, 26, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "-");
                                }
                            }
                        }
                        {
                            // dash_ov_bar_rapid
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.dash_ov_bar_rapid = obj;
                            lv_obj_set_pos(obj, 42, 42);
                            lv_obj_set_size(obj, 125, 6);
                            lv_bar_set_value(obj, 100, LV_ANIM_OFF);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                            add_style_bar_default(obj);
                        }
                        {
                            // dash_ov_inc_rapid
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_ov_inc_rapid = obj;
                            lv_obj_set_pos(obj, 169, 32);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_add_event_cb(obj, action_adjust_override, LV_EVENT_CLICKED, (void *)3);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_ov_inc_lbl_rapid
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_ov_inc_lbl_rapid = obj;
                                    lv_obj_set_pos(obj, 0, 4);
                                    lv_obj_set_size(obj, 26, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "+");
                                }
                            }
                        }
                    }
                }
                {
                    // dash_ov_card_spindle
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_ov_card_spindle = obj;
                    lv_obj_set_pos(obj, 446, 324);
                    lv_obj_set_size(obj, 205, 152);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_ov_lbl_spindle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_ov_lbl_spindle = obj;
                            lv_obj_set_pos(obj, 10, 8);
                            lv_obj_set_size(obj, 145, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "SPINDLE");
                        }
                        {
                            // dash_ov_val_spindle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_ov_val_spindle = obj;
                            lv_obj_set_pos(obj, 145, 8);
                            lv_obj_set_size(obj, 50, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "100%");
                        }
                        {
                            // dash_ov_dec_spindle
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_ov_dec_spindle = obj;
                            lv_obj_set_pos(obj, 10, 32);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_add_event_cb(obj, action_adjust_override, LV_EVENT_CLICKED, (void *)4);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_ov_dec_lbl_spindle
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_ov_dec_lbl_spindle = obj;
                                    lv_obj_set_pos(obj, 0, 4);
                                    lv_obj_set_size(obj, 26, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "-");
                                }
                            }
                        }
                        {
                            // dash_ov_bar_spindle
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.dash_ov_bar_spindle = obj;
                            lv_obj_set_pos(obj, 42, 42);
                            lv_obj_set_size(obj, 125, 6);
                            lv_bar_set_value(obj, 100, LV_ANIM_OFF);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                            add_style_bar_default(obj);
                        }
                        {
                            // dash_ov_inc_spindle
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.dash_ov_inc_spindle = obj;
                            lv_obj_set_pos(obj, 169, 32);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_add_event_cb(obj, action_adjust_override, LV_EVENT_CLICKED, (void *)5);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // dash_ov_inc_lbl_spindle
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.dash_ov_inc_lbl_spindle = obj;
                                    lv_obj_set_pos(obj, 0, 4);
                                    lv_obj_set_size(obj, 26, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "+");
                                }
                            }
                        }
                    }
                }
                {
                    // dash_job_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.dash_job_card = obj;
                    lv_obj_set_pos(obj, 664, 0);
                    lv_obj_set_size(obj, 348, 130);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_job_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_job_caption = obj;
                            lv_obj_set_pos(obj, 14, 12);
                            lv_obj_set_size(obj, 200, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "CURRENT JOB");
                        }
                        {
                            // dash_job_pct
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_job_pct = obj;
                            lv_obj_set_pos(obj, 278, 12);
                            lv_obj_set_size(obj, 60, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0%");
                        }
                        {
                            // dash_job_file
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_job_file = obj;
                            lv_obj_set_pos(obj, 14, 32);
                            lv_obj_set_size(obj, 320, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_section(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "(no job loaded)");
                        }
                        {
                            // dash_job_bar
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.dash_job_bar = obj;
                            lv_obj_set_pos(obj, 14, 64);
                            lv_obj_set_size(obj, 320, 8);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                            add_style_bar_progress(obj);
                        }
                        {
                            // dash_job_elapsed
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_job_elapsed = obj;
                            lv_obj_set_pos(obj, 14, 84);
                            lv_obj_set_size(obj, 110, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "ELAPSED 00:00");
                        }
                        {
                            // dash_job_eta
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_job_eta = obj;
                            lv_obj_set_pos(obj, 133, 84);
                            lv_obj_set_size(obj, 110, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "ETA 00:00");
                        }
                        {
                            // dash_job_line
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_job_line = obj;
                            lv_obj_set_pos(obj, 260, 84);
                            lv_obj_set_size(obj, 74, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "L0");
                        }
                    }
                }
                {
                    // dash_tq_spindle
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.dash_tq_spindle = obj;
                    lv_obj_set_pos(obj, 664, 142);
                    lv_obj_set_size(obj, 168, 161);
                    lv_obj_add_event_cb(obj, action_toggle_spindle, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_tq_icon_spindle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_icon_spindle = obj;
                            lv_obj_set_pos(obj, 68, 54);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_label_set_text(obj, "\uf192");
                        }
                        {
                            // dash_tq_lbl_spindle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_lbl_spindle = obj;
                            lv_obj_set_pos(obj, 0, 92);
                            lv_obj_set_size(obj, 168, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SPINDLE");
                        }
                        {
                            // dash_tq_rpm_spindle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_rpm_spindle = obj;
                            lv_obj_set_pos(obj, 0, 110);
                            lv_obj_set_size(obj, 168, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 RPM");
                        }
                    }
                }
                {
                    // dash_tq_soft_reset
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.dash_tq_soft_reset = obj;
                    lv_obj_set_pos(obj, 844, 142);
                    lv_obj_set_size(obj, 168, 161);
                    lv_obj_add_event_cb(obj, action_estop, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_tq_icon_soft_reset
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_icon_soft_reset = obj;
                            lv_obj_set_pos(obj, 68, 54);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_label_set_text(obj, "\uf021");
                        }
                        {
                            // dash_tq_lbl_soft_reset
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_lbl_soft_reset = obj;
                            lv_obj_set_pos(obj, 0, 92);
                            lv_obj_set_size(obj, 168, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SOFT RESET");
                        }
                    }
                }
                {
                    // dash_tq_mist
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.dash_tq_mist = obj;
                    lv_obj_set_pos(obj, 664, 315);
                    lv_obj_set_size(obj, 168, 161);
                    lv_obj_add_event_cb(obj, action_toggle_mist, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_tq_icon_mist
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_icon_mist = obj;
                            lv_obj_set_pos(obj, 68, 54);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_label_set_text(obj, "\uf73d");
                        }
                        {
                            // dash_tq_lbl_mist
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_lbl_mist = obj;
                            lv_obj_set_pos(obj, 0, 92);
                            lv_obj_set_size(obj, 168, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "MIST");
                        }
                    }
                }
                {
                    // dash_tq_home
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.dash_tq_home = obj;
                    lv_obj_set_pos(obj, 844, 315);
                    lv_obj_set_size(obj, 168, 161);
                    lv_obj_add_event_cb(obj, action_home_all, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_toggle(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dash_tq_icon_home
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_icon_home = obj;
                            lv_obj_set_pos(obj, 68, 54);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_label_set_text(obj, "\uf015");
                        }
                        {
                            // dash_tq_lbl_home
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dash_tq_lbl_home = obj;
                            lv_obj_set_pos(obj, 0, 92);
                            lv_obj_set_size(obj, 168, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "HOME ALL");
                        }
                    }
                }
            }
        }
        {
            // PageDashboard_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_dashboard_dock = obj;
            lv_obj_set_pos(obj, 0, 534);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_dock(obj, 245);
        }
        {
            // PageDashboard_alarm
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_dashboard_alarm = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_alarm_ribbon(obj, 271);
        }
    }
    
    tick_screen_page_dashboard();
}

void tick_screen_page_dashboard() {
    tick_user_widget_status_bar(159);
    tick_user_widget_bottom_dock(245);
    tick_user_widget_alarm_ribbon(271);
}

void create_screen_page_jog() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_jog = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // PageJog_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_jog_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_status_bar(obj, 277);
        }
        {
            // PageJog_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_jog_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 488);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_transparent(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // jog_dro_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.jog_dro_card = obj;
                    lv_obj_set_pos(obj, 12, 0);
                    lv_obj_set_size(obj, 344, 260);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // jog_dro_work_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_dro_work_lbl = obj;
                            lv_obj_set_pos(obj, 14, 10);
                            lv_obj_set_size(obj, 80, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "WORK");
                        }
                        {
                            // jog_dro_machine_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_dro_machine_lbl = obj;
                            lv_obj_set_pos(obj, 234, 10);
                            lv_obj_set_size(obj, 90, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "MACHINE");
                        }
                        {
                            // jog_chip_x
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.jog_chip_x = obj;
                            lv_obj_set_pos(obj, 14, 30);
                            lv_obj_set_size(obj, 30, 30);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_axis_chip_x(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_chip_lbl_x
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_chip_lbl_x = obj;
                                    lv_obj_set_pos(obj, 0, 7);
                                    lv_obj_set_size(obj, 30, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_axis_chip_label(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "X");
                                }
                            }
                        }
                        {
                            // jog_work_x
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_work_x = obj;
                            lv_obj_set_pos(obj, 56, 26);
                            lv_obj_set_size(obj, 188, 38);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_jog(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                        {
                            // jog_machine_x
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_machine_x = obj;
                            lv_obj_set_pos(obj, 244, 36);
                            lv_obj_set_size(obj, 84, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_machine(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                        {
                            // jog_chip_y
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.jog_chip_y = obj;
                            lv_obj_set_pos(obj, 14, 100);
                            lv_obj_set_size(obj, 30, 30);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_axis_chip_y(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_chip_lbl_y
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_chip_lbl_y = obj;
                                    lv_obj_set_pos(obj, 0, 7);
                                    lv_obj_set_size(obj, 30, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_axis_chip_label(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Y");
                                }
                            }
                        }
                        {
                            // jog_work_y
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_work_y = obj;
                            lv_obj_set_pos(obj, 56, 96);
                            lv_obj_set_size(obj, 188, 38);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_jog(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                        {
                            // jog_machine_y
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_machine_y = obj;
                            lv_obj_set_pos(obj, 244, 106);
                            lv_obj_set_size(obj, 84, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_machine(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                        {
                            // jog_chip_z
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.jog_chip_z = obj;
                            lv_obj_set_pos(obj, 14, 170);
                            lv_obj_set_size(obj, 30, 30);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_axis_chip_z(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_chip_lbl_z
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_chip_lbl_z = obj;
                                    lv_obj_set_pos(obj, 0, 7);
                                    lv_obj_set_size(obj, 30, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_axis_chip_label(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Z");
                                }
                            }
                        }
                        {
                            // jog_work_z
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_work_z = obj;
                            lv_obj_set_pos(obj, 56, 166);
                            lv_obj_set_size(obj, 188, 38);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_jog(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                        {
                            // jog_machine_z
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_machine_z = obj;
                            lv_obj_set_pos(obj, 244, 176);
                            lv_obj_set_size(obj, 84, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_machine(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0.000");
                        }
                    }
                }
                {
                    // jog_wcs_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.jog_wcs_card = obj;
                    lv_obj_set_pos(obj, 12, 274);
                    lv_obj_set_size(obj, 344, 200);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // jog_wcs_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_wcs_caption = obj;
                            lv_obj_set_pos(obj, 12, 10);
                            lv_obj_set_size(obj, 240, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "WORK COORDINATE SYSTEM");
                        }
                        {
                            // jog_wcs_G54
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_wcs_g54 = obj;
                            lv_obj_set_pos(obj, 12, 28);
                            lv_obj_set_size(obj, 102, 32);
                            lv_obj_add_event_cb(obj, action_set_wcs, LV_EVENT_CLICKED, (void *)0);
                            lv_obj_add_state(obj, LV_STATE_CHECKED);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_wcs_lbl_G54
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_wcs_lbl_g54 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 102, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "G54");
                                }
                            }
                        }
                        {
                            // jog_wcs_G55
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_wcs_g55 = obj;
                            lv_obj_set_pos(obj, 120, 28);
                            lv_obj_set_size(obj, 102, 32);
                            lv_obj_add_event_cb(obj, action_set_wcs, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_wcs_lbl_G55
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_wcs_lbl_g55 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 102, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "G55");
                                }
                            }
                        }
                        {
                            // jog_wcs_G56
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_wcs_g56 = obj;
                            lv_obj_set_pos(obj, 228, 28);
                            lv_obj_set_size(obj, 102, 32);
                            lv_obj_add_event_cb(obj, action_set_wcs, LV_EVENT_CLICKED, (void *)2);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_wcs_lbl_G56
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_wcs_lbl_g56 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 102, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "G56");
                                }
                            }
                        }
                        {
                            // jog_wcs_G57
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_wcs_g57 = obj;
                            lv_obj_set_pos(obj, 12, 66);
                            lv_obj_set_size(obj, 102, 32);
                            lv_obj_add_event_cb(obj, action_set_wcs, LV_EVENT_CLICKED, (void *)3);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_wcs_lbl_G57
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_wcs_lbl_g57 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 102, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "G57");
                                }
                            }
                        }
                        {
                            // jog_wcs_G58
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_wcs_g58 = obj;
                            lv_obj_set_pos(obj, 120, 66);
                            lv_obj_set_size(obj, 102, 32);
                            lv_obj_add_event_cb(obj, action_set_wcs, LV_EVENT_CLICKED, (void *)4);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_wcs_lbl_G58
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_wcs_lbl_g58 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 102, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "G58");
                                }
                            }
                        }
                        {
                            // jog_wcs_G59
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_wcs_g59 = obj;
                            lv_obj_set_pos(obj, 228, 66);
                            lv_obj_set_size(obj, 102, 32);
                            lv_obj_add_event_cb(obj, action_set_wcs, LV_EVENT_CLICKED, (void *)5);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_wcs_lbl_G59
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_wcs_lbl_g59 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 102, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "G59");
                                }
                            }
                        }
                        {
                            // jog_units_mm
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_units_mm = obj;
                            lv_obj_set_pos(obj, 12, 112);
                            lv_obj_set_size(obj, 162, 34);
                            lv_obj_add_event_cb(obj, action_set_units, LV_EVENT_CLICKED, (void *)0);
                            lv_obj_add_state(obj, LV_STATE_CHECKED);
                            add_style_btn_units_left(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_units_mm_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_units_mm_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 9);
                                    lv_obj_set_size(obj, 162, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "MM");
                                }
                            }
                        }
                        {
                            // jog_units_in
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_units_in = obj;
                            lv_obj_set_pos(obj, 180, 112);
                            lv_obj_set_size(obj, 162, 34);
                            lv_obj_add_event_cb(obj, action_set_units, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_units_left(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_units_in_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_units_in_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 9);
                                    lv_obj_set_size(obj, 162, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "INCH");
                                }
                            }
                        }
                    }
                }
                {
                    // jog_step_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.jog_step_card = obj;
                    lv_obj_set_pos(obj, 370, 0);
                    lv_obj_set_size(obj, 642, 70);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // jog_step_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_step_caption = obj;
                            lv_obj_set_pos(obj, 14, 10);
                            lv_obj_set_size(obj, 200, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "JOG STEP . mm");
                        }
                        {
                            // jog_step_feed
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_step_feed = obj;
                            lv_obj_set_pos(obj, 468, 10);
                            lv_obj_set_size(obj, 160, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "FEED 1200 mm/min");
                        }
                        {
                            // jog_step_0
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_step_0 = obj;
                            lv_obj_set_pos(obj, 14, 28);
                            lv_obj_set_size(obj, 149, 34);
                            lv_obj_add_event_cb(obj, action_set_jog_step, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_step_lbl_0
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_step_lbl_0 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 149, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0.01");
                                }
                            }
                        }
                        {
                            // jog_step_1
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_step_1 = obj;
                            lv_obj_set_pos(obj, 169, 28);
                            lv_obj_set_size(obj, 149, 34);
                            lv_obj_add_event_cb(obj, action_set_jog_step, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_step_lbl_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_step_lbl_1 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 149, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0.1");
                                }
                            }
                        }
                        {
                            // jog_step_2
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_step_2 = obj;
                            lv_obj_set_pos(obj, 324, 28);
                            lv_obj_set_size(obj, 149, 34);
                            lv_obj_add_event_cb(obj, action_set_jog_step, LV_EVENT_CLICKED, (void *)2);
                            lv_obj_add_state(obj, LV_STATE_CHECKED);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_step_lbl_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_step_lbl_2 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 149, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "1");
                                }
                            }
                        }
                        {
                            // jog_step_3
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_step_3 = obj;
                            lv_obj_set_pos(obj, 479, 28);
                            lv_obj_set_size(obj, 149, 34);
                            lv_obj_add_event_cb(obj, action_set_jog_step, LV_EVENT_CLICKED, (void *)3);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_step_lbl_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_step_lbl_3 = obj;
                                    lv_obj_set_pos(obj, 0, 8);
                                    lv_obj_set_size(obj, 149, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "10");
                                }
                            }
                        }
                    }
                }
                {
                    // jog_pad_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.jog_pad_card = obj;
                    lv_obj_set_pos(obj, 370, 84);
                    lv_obj_set_size(obj, 512, 316);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // jog_yp
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_yp = obj;
                            lv_obj_set_pos(obj, 177, 12);
                            lv_obj_set_size(obj, 157, 92);
                            lv_obj_add_event_cb(obj, action_jog, LV_EVENT_CLICKED, (void *)2);
                            add_style_btn_jog_pad(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_yp_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_yp_icon = obj;
                                    lv_obj_set_pos(obj, 0, 18);
                                    lv_obj_set_size(obj, 157, 32);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa28(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf062");
                                }
                                {
                                    // jog_yp_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_yp_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 53);
                                    lv_obj_set_size(obj, 157, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Y+");
                                }
                            }
                        }
                        {
                            // jog_xm
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_xm = obj;
                            lv_obj_set_pos(obj, 12, 112);
                            lv_obj_set_size(obj, 157, 92);
                            lv_obj_add_event_cb(obj, action_jog, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_jog_pad(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_xm_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_xm_icon = obj;
                                    lv_obj_set_pos(obj, 0, 18);
                                    lv_obj_set_size(obj, 157, 32);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa28(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf060");
                                }
                                {
                                    // jog_xm_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_xm_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 53);
                                    lv_obj_set_size(obj, 157, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "X-");
                                }
                            }
                        }
                        {
                            // jog_home
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_home = obj;
                            lv_obj_set_pos(obj, 177, 112);
                            lv_obj_set_size(obj, 157, 92);
                            lv_obj_add_event_cb(obj, action_home_all, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_accent_soft(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_home_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_home_icon = obj;
                                    lv_obj_set_pos(obj, 0, 25);
                                    lv_obj_set_size(obj, 157, 26);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf015");
                                }
                                {
                                    // jog_home_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_home_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 50);
                                    lv_obj_set_size(obj, 157, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_accent(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "HOME");
                                }
                            }
                        }
                        {
                            // jog_xp
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_xp = obj;
                            lv_obj_set_pos(obj, 342, 112);
                            lv_obj_set_size(obj, 157, 92);
                            lv_obj_add_event_cb(obj, action_jog, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_jog_pad(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_xp_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_xp_icon = obj;
                                    lv_obj_set_pos(obj, 0, 18);
                                    lv_obj_set_size(obj, 157, 32);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa28(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf061");
                                }
                                {
                                    // jog_xp_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_xp_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 53);
                                    lv_obj_set_size(obj, 157, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "X+");
                                }
                            }
                        }
                        {
                            // jog_ym
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_ym = obj;
                            lv_obj_set_pos(obj, 177, 212);
                            lv_obj_set_size(obj, 157, 92);
                            lv_obj_add_event_cb(obj, action_jog, LV_EVENT_CLICKED, (void *)3);
                            add_style_btn_jog_pad(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_ym_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_ym_icon = obj;
                                    lv_obj_set_pos(obj, 0, 18);
                                    lv_obj_set_size(obj, 157, 32);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa28(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf063");
                                }
                                {
                                    // jog_ym_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_ym_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 53);
                                    lv_obj_set_size(obj, 157, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Y-");
                                }
                            }
                        }
                    }
                }
                {
                    // jog_z_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.jog_z_card = obj;
                    lv_obj_set_pos(obj, 894, 84);
                    lv_obj_set_size(obj, 118, 316);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // jog_zp
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_zp = obj;
                            lv_obj_set_pos(obj, 12, 12);
                            lv_obj_set_size(obj, 94, 126);
                            lv_obj_add_event_cb(obj, action_jog, LV_EVENT_CLICKED, (void *)4);
                            add_style_btn_jog_pad(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_zp_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_zp_icon = obj;
                                    lv_obj_set_pos(obj, 0, 7);
                                    lv_obj_set_size(obj, 94, 32);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa28(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf077");
                                }
                                {
                                    // jog_zp_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_zp_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 40);
                                    lv_obj_set_size(obj, 94, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_info(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Z+");
                                }
                            }
                        }
                        {
                            // jog_z_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.jog_z_caption = obj;
                            lv_obj_set_pos(obj, 0, 146);
                            lv_obj_set_size(obj, 118, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_info(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Z AXIS");
                        }
                        {
                            // jog_zm
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_zm = obj;
                            lv_obj_set_pos(obj, 12, 178);
                            lv_obj_set_size(obj, 94, 126);
                            lv_obj_add_event_cb(obj, action_jog, LV_EVENT_CLICKED, (void *)5);
                            add_style_btn_jog_pad(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_zm_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_zm_icon = obj;
                                    lv_obj_set_pos(obj, 0, 7);
                                    lv_obj_set_size(obj, 94, 32);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa28(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf078");
                                }
                                {
                                    // jog_zm_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_zm_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 40);
                                    lv_obj_set_size(obj, 94, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_info(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Z-");
                                }
                            }
                        }
                    }
                }
                {
                    // jog_zero_row
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.jog_zero_row = obj;
                    lv_obj_set_pos(obj, 370, 414);
                    lv_obj_set_size(obj, 642, 62);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_transparent(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // jog_zero_0
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_zero_0 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 154, 62);
                            lv_obj_add_event_cb(obj, action_zero_axis, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_zero_lbl_0
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_zero_lbl_0 = obj;
                                    lv_obj_set_pos(obj, 0, 24);
                                    lv_obj_set_size(obj, 154, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "ZERO X");
                                }
                            }
                        }
                        {
                            // jog_zero_1
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_zero_1 = obj;
                            lv_obj_set_pos(obj, 162, 0);
                            lv_obj_set_size(obj, 154, 62);
                            lv_obj_add_event_cb(obj, action_zero_axis, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_zero_lbl_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_zero_lbl_1 = obj;
                                    lv_obj_set_pos(obj, 0, 24);
                                    lv_obj_set_size(obj, 154, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "ZERO Y");
                                }
                            }
                        }
                        {
                            // jog_zero_2
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_zero_2 = obj;
                            lv_obj_set_pos(obj, 324, 0);
                            lv_obj_set_size(obj, 154, 62);
                            lv_obj_add_event_cb(obj, action_zero_axis, LV_EVENT_CLICKED, (void *)2);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_zero_lbl_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_zero_lbl_2 = obj;
                                    lv_obj_set_pos(obj, 0, 24);
                                    lv_obj_set_size(obj, 154, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "ZERO Z");
                                }
                            }
                        }
                        {
                            // jog_zero_3
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.jog_zero_3 = obj;
                            lv_obj_set_pos(obj, 486, 0);
                            lv_obj_set_size(obj, 154, 62);
                            lv_obj_add_event_cb(obj, action_zero_axis, LV_EVENT_CLICKED, (void *)3);
                            add_style_btn_accent_soft(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // jog_zero_lbl_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.jog_zero_lbl_3 = obj;
                                    lv_obj_set_pos(obj, 0, 24);
                                    lv_obj_set_size(obj, 154, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "ZERO ALL");
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // PageJog_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_jog_dock = obj;
            lv_obj_set_pos(obj, 0, 534);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_dock(obj, 377);
        }
        {
            // PageJog_alarm
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_jog_alarm = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_alarm_ribbon(obj, 403);
        }
    }
    
    tick_screen_page_jog();
}

void tick_screen_page_jog() {
    tick_user_widget_status_bar(277);
    tick_user_widget_bottom_dock(377);
    tick_user_widget_alarm_ribbon(403);
}

void create_screen_page_run() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_run = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // PageRun_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_run_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_status_bar(obj, 409);
        }
        {
            // PageRun_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_run_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 488);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_transparent(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // run_hdr_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.run_hdr_card = obj;
                    lv_obj_set_pos(obj, 12, 0);
                    lv_obj_set_size(obj, 1000, 110);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // run_hdr_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_hdr_caption = obj;
                            lv_obj_set_pos(obj, 14, 10);
                            lv_obj_set_size(obj, 200, 10);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "RUNNING FILE");
                        }
                        {
                            // run_hdr_file
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_hdr_file = obj;
                            lv_obj_set_pos(obj, 14, 26);
                            lv_obj_set_size(obj, 796, 22);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "(no job loaded)");
                        }
                        {
                            // run_hdr_pct
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_hdr_pct = obj;
                            lv_obj_set_pos(obj, 836, 8);
                            lv_obj_set_size(obj, 150, 48);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_46, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0%");
                        }
                        {
                            // run_hdr_bar
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.run_hdr_bar = obj;
                            lv_obj_set_pos(obj, 14, 64);
                            lv_obj_set_size(obj, 968, 10);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                            add_style_bar_progress(obj);
                        }
                        {
                            // run_hdr_elapsed
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_hdr_elapsed = obj;
                            lv_obj_set_pos(obj, 14, 84);
                            lv_obj_set_size(obj, 120, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "ELAPSED 00:00");
                        }
                        {
                            // run_hdr_remain
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_hdr_remain = obj;
                            lv_obj_set_pos(obj, 412, 84);
                            lv_obj_set_size(obj, 200, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "REMAINING 00:00");
                        }
                        {
                            // run_hdr_line
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_hdr_line = obj;
                            lv_obj_set_pos(obj, 786, 84);
                            lv_obj_set_size(obj, 200, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "LINE 0 / 0");
                        }
                    }
                }
                {
                    // run_gcode_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.run_gcode_card = obj;
                    lv_obj_set_pos(obj, 12, 122);
                    lv_obj_set_size(obj, 708, 354);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_dark_inset(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // run_gc_00
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_00 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_00_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_00_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_00_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_00_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_01
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_01 = obj;
                            lv_obj_set_pos(obj, 0, 22);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_01_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_01_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_01_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_01_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_02
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_02 = obj;
                            lv_obj_set_pos(obj, 0, 44);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_02_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_02_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_02_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_02_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_03
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_03 = obj;
                            lv_obj_set_pos(obj, 0, 66);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_03_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_03_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_03_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_03_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_04
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_04 = obj;
                            lv_obj_set_pos(obj, 0, 88);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_04_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_04_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_04_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_04_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_05
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_05 = obj;
                            lv_obj_set_pos(obj, 0, 110);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_05_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_05_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_05_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_05_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_06
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_06 = obj;
                            lv_obj_set_pos(obj, 0, 132);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_06_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_06_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_06_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_06_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_07
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_07 = obj;
                            lv_obj_set_pos(obj, 0, 154);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_07_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_07_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_07_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_07_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_08
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_08 = obj;
                            lv_obj_set_pos(obj, 0, 176);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_08_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_08_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_08_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_08_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_09
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_09 = obj;
                            lv_obj_set_pos(obj, 0, 198);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_09_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_09_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_09_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_09_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_10
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_10 = obj;
                            lv_obj_set_pos(obj, 0, 220);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_10_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_10_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_10_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_10_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_11
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_11 = obj;
                            lv_obj_set_pos(obj, 0, 242);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_11_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_11_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_11_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_11_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_12
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_12 = obj;
                            lv_obj_set_pos(obj, 0, 264);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_12_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_12_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_12_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_12_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_13
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_13 = obj;
                            lv_obj_set_pos(obj, 0, 286);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_13_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_13_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_13_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_13_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_14
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_14 = obj;
                            lv_obj_set_pos(obj, 0, 308);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_14_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_14_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_14_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_14_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_15
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_15 = obj;
                            lv_obj_set_pos(obj, 0, 330);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_15_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_15_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_15_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_15_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_16
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_16 = obj;
                            lv_obj_set_pos(obj, 0, 352);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_16_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_16_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_16_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_16_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_17
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_17 = obj;
                            lv_obj_set_pos(obj, 0, 374);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_17_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_17_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_17_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_17_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_18
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_18 = obj;
                            lv_obj_set_pos(obj, 0, 396);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_18_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_18_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_18_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_18_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            // run_gc_19
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.run_gc_19 = obj;
                            lv_obj_set_pos(obj, 0, 418);
                            lv_obj_set_size(obj, 692, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // run_gc_19_n
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_19_n = obj;
                                    lv_obj_set_pos(obj, 6, 3);
                                    lv_obj_set_size(obj, 32, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                                {
                                    // run_gc_19_t
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.run_gc_19_t = obj;
                                    lv_obj_set_pos(obj, 44, 3);
                                    lv_obj_set_size(obj, 648, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                    }
                }
                {
                    // run_btn_start
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.run_btn_start = obj;
                    lv_obj_set_pos(obj, 732, 122);
                    lv_obj_set_size(obj, 280, 52);
                    lv_obj_add_event_cb(obj, action_job_start, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_accent_fill(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // run_btn_start_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_btn_start_icon = obj;
                            lv_obj_set_pos(obj, 78, 13);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf04b");
                        }
                        {
                            // run_btn_start_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_btn_start_lbl = obj;
                            lv_obj_set_pos(obj, 110, 18);
                            lv_obj_set_size(obj, 90, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "START");
                        }
                    }
                }
                {
                    // run_btn_hold
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.run_btn_hold = obj;
                    lv_obj_set_pos(obj, 732, 184);
                    lv_obj_set_size(obj, 280, 52);
                    lv_obj_add_event_cb(obj, action_hold_resume, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_hold(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // run_btn_hold_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_btn_hold_icon = obj;
                            lv_obj_set_pos(obj, 76, 13);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf04c");
                        }
                        {
                            // run_btn_hold_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_btn_hold_lbl = obj;
                            lv_obj_set_pos(obj, 110, 18);
                            lv_obj_set_size(obj, 90, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_warning(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "HOLD");
                        }
                    }
                }
                {
                    // run_btn_stop
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.run_btn_stop = obj;
                    lv_obj_set_pos(obj, 732, 246);
                    lv_obj_set_size(obj, 280, 52);
                    lv_obj_add_event_cb(obj, action_job_stop, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_danger_soft(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // run_btn_stop_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_btn_stop_icon = obj;
                            lv_obj_set_pos(obj, 76, 13);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf04d");
                        }
                        {
                            // run_btn_stop_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_btn_stop_lbl = obj;
                            lv_obj_set_pos(obj, 110, 18);
                            lv_obj_set_size(obj, 90, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_danger(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "STOP");
                        }
                    }
                }
                {
                    // run_stat_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.run_stat_card = obj;
                    lv_obj_set_pos(obj, 732, 308);
                    lv_obj_set_size(obj, 280, 168);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // run_stat_spindle_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_stat_spindle_lbl = obj;
                            lv_obj_set_pos(obj, 12, 14);
                            lv_obj_set_size(obj, 120, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "SPINDLE");
                        }
                        {
                            // run_stat_spindle_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_stat_spindle_val = obj;
                            lv_obj_set_pos(obj, 158, 10);
                            lv_obj_set_size(obj, 100, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 RPM");
                        }
                        {
                            // run_stat_feed_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_stat_feed_lbl = obj;
                            lv_obj_set_pos(obj, 12, 50);
                            lv_obj_set_size(obj, 120, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "FEED OVR");
                        }
                        {
                            // run_stat_feed_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_stat_feed_val = obj;
                            lv_obj_set_pos(obj, 158, 46);
                            lv_obj_set_size(obj, 100, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "100%");
                        }
                        {
                            // run_stat_coolant_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_stat_coolant_lbl = obj;
                            lv_obj_set_pos(obj, 12, 86);
                            lv_obj_set_size(obj, 120, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "COOLANT");
                        }
                        {
                            // run_stat_coolant_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.run_stat_coolant_val = obj;
                            lv_obj_set_pos(obj, 158, 82);
                            lv_obj_set_size(obj, 100, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "OFF");
                        }
                    }
                }
            }
        }
        {
            // PageRun_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_run_dock = obj;
            lv_obj_set_pos(obj, 0, 534);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_dock(obj, 517);
        }
        {
            // PageRun_alarm
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_run_alarm = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_alarm_ribbon(obj, 543);
        }
    }
    
    tick_screen_page_run();
}

void tick_screen_page_run() {
    tick_user_widget_status_bar(409);
    tick_user_widget_bottom_dock(517);
    tick_user_widget_alarm_ribbon(543);
}

void create_screen_page_files() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_files = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // PageFiles_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_files_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_status_bar(obj, 549);
        }
        {
            // PageFiles_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_files_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 488);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_transparent(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // files_list_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.files_list_card = obj;
                    lv_obj_set_pos(obj, 12, 0);
                    lv_obj_set_size(obj, 706, 476);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_dark_inset(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // files_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_caption = obj;
                            lv_obj_set_pos(obj, 6, 8);
                            lv_obj_set_size(obj, 240, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "SD CARD . /GCODE");
                        }
                        {
                            // files_count
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_count = obj;
                            lv_obj_set_pos(obj, 606, 8);
                            lv_obj_set_size(obj, 80, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0 files");
                        }
                    }
                }
                {
                    // files_sel_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.files_sel_card = obj;
                    lv_obj_set_pos(obj, 730, 0);
                    lv_obj_set_size(obj, 282, 220);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // files_sel_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_sel_caption = obj;
                            lv_obj_set_pos(obj, 14, 12);
                            lv_obj_set_size(obj, 100, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "SELECTED");
                        }
                        {
                            // files_sel_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_sel_icon = obj;
                            lv_obj_set_pos(obj, 14, 40);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_fa_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf15c");
                        }
                        {
                            // files_sel_name
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_sel_name = obj;
                            lv_obj_set_pos(obj, 54, 46);
                            lv_obj_set_size(obj, 212, 18);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "(none selected)");
                        }
                        {
                            // files_det_rt_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_det_rt_lbl = obj;
                            lv_obj_set_pos(obj, 14, 96);
                            lv_obj_set_size(obj, 100, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_label_set_text(obj, "Est. runtime");
                        }
                        {
                            // files_det_rt_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_det_rt_val = obj;
                            lv_obj_set_pos(obj, 152, 96);
                            lv_obj_set_size(obj, 116, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                        {
                            // files_det_ln_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_det_ln_lbl = obj;
                            lv_obj_set_pos(obj, 14, 124);
                            lv_obj_set_size(obj, 100, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_label_set_text(obj, "Lines");
                        }
                        {
                            // files_det_ln_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_det_ln_val = obj;
                            lv_obj_set_pos(obj, 152, 124);
                            lv_obj_set_size(obj, 116, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                        {
                            // files_det_bd_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_det_bd_lbl = obj;
                            lv_obj_set_pos(obj, 14, 152);
                            lv_obj_set_size(obj, 100, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_label_set_text(obj, "Bounds");
                        }
                        {
                            // files_det_bd_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_det_bd_val = obj;
                            lv_obj_set_pos(obj, 122, 152);
                            lv_obj_set_size(obj, 146, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                    }
                }
                {
                    // files_btn_load
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.files_btn_load = obj;
                    lv_obj_set_pos(obj, 730, 230);
                    lv_obj_set_size(obj, 282, 52);
                    lv_obj_add_event_cb(obj, action_file_load_run, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_accent_fill(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // files_btn_load_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_btn_load_icon = obj;
                            lv_obj_set_pos(obj, 68, 14);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf04b");
                        }
                        {
                            // files_btn_load_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_btn_load_lbl = obj;
                            lv_obj_set_pos(obj, 99, 18);
                            lv_obj_set_size(obj, 130, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "LOAD & RUN");
                        }
                    }
                }
                {
                    // files_stg_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.files_stg_card = obj;
                    lv_obj_set_pos(obj, 730, 292);
                    lv_obj_set_size(obj, 282, 56);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // files_stg_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_stg_lbl = obj;
                            lv_obj_set_pos(obj, 12, 10);
                            lv_obj_set_size(obj, 120, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "SD STORAGE");
                        }
                        {
                            // files_stg_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.files_stg_val = obj;
                            lv_obj_set_pos(obj, 162, 10);
                            lv_obj_set_size(obj, 108, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_mini(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "(unknown)");
                        }
                        {
                            // files_stg_bar
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.files_stg_bar = obj;
                            lv_obj_set_pos(obj, 12, 30);
                            lv_obj_set_size(obj, 258, 6);
                            lv_bar_set_value(obj, 13, LV_ANIM_OFF);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                            add_style_bar_default(obj);
                        }
                    }
                }
            }
        }
        {
            // PageFiles_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_files_dock = obj;
            lv_obj_set_pos(obj, 0, 534);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_dock(obj, 592);
        }
        {
            // PageFiles_alarm
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_files_alarm = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_alarm_ribbon(obj, 618);
        }
    }
    
    tick_screen_page_files();
}

void tick_screen_page_files() {
    tick_user_widget_status_bar(549);
    tick_user_widget_bottom_dock(592);
    tick_user_widget_alarm_ribbon(618);
}

void create_screen_page_spindle() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_spindle = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // PageSpindle_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_spindle_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_status_bar(obj, 624);
        }
        {
            // PageSpindle_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_spindle_body = obj;
            lv_obj_set_pos(obj, 0, 50);
            lv_obj_set_size(obj, 1024, 488);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_transparent(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // spin_left_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.spin_left_card = obj;
                    lv_obj_set_pos(obj, 12, 0);
                    lv_obj_set_size(obj, 666, 476);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // spin_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.spin_caption = obj;
                            lv_obj_set_pos(obj, 0, 14);
                            lv_obj_set_size(obj, 666, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SPINDLE SPEED");
                        }
                        {
                            // spin_arc
                            lv_obj_t *obj = lv_arc_create(parent_obj);
                            objects.spin_arc = obj;
                            lv_obj_set_pos(obj, 215, 50);
                            lv_obj_set_size(obj, 236, 236);
                            lv_arc_set_range(obj, 0, 24000);
                            lv_arc_set_value(obj, 0);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_ADV_HITTEST|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                            add_style_arc_default(obj);
                        }
                        {
                            // spin_rpm_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.spin_rpm_val = obj;
                            lv_obj_set_pos(obj, 233, 133);
                            lv_obj_set_size(obj, 200, 56);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_mono_spindle_val(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0");
                        }
                        {
                            // spin_rpm_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.spin_rpm_lbl = obj;
                            lv_obj_set_pos(obj, 283, 194);
                            lv_obj_set_size(obj, 100, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "RPM");
                        }
                        {
                            // spin_btn_start
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.spin_btn_start = obj;
                            lv_obj_set_pos(obj, 40, 297);
                            lv_obj_set_size(obj, 280, 60);
                            lv_obj_add_event_cb(obj, action_spindle_start, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_accent_fill(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spin_btn_start_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_btn_start_icon = obj;
                                    lv_obj_set_pos(obj, 26, 17);
                                    lv_obj_set_size(obj, 26, 26);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_icon_fa22(obj);
                                    lv_label_set_text(obj, "\uf04b");
                                }
                                {
                                    // spin_btn_start_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_btn_start_lbl = obj;
                                    lv_obj_set_pos(obj, 58, 22);
                                    lv_obj_set_size(obj, 210, 16);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "START SPINDLE");
                                }
                            }
                        }
                        {
                            // spin_btn_stop
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.spin_btn_stop = obj;
                            lv_obj_set_pos(obj, 346, 297);
                            lv_obj_set_size(obj, 280, 60);
                            lv_obj_add_event_cb(obj, action_spindle_stop, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spin_btn_stop_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_btn_stop_icon = obj;
                                    lv_obj_set_pos(obj, 26, 17);
                                    lv_obj_set_size(obj, 26, 26);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_icon_fa22(obj);
                                    lv_label_set_text(obj, "\uf04d");
                                }
                                {
                                    // spin_btn_stop_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_btn_stop_lbl = obj;
                                    lv_obj_set_pos(obj, 58, 22);
                                    lv_obj_set_size(obj, 210, 16);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "STOP SPINDLE");
                                }
                            }
                        }
                    }
                }
                {
                    // spin_trgt_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.spin_trgt_card = obj;
                    lv_obj_set_pos(obj, 692, 0);
                    lv_obj_set_size(obj, 320, 110);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // spin_trgt_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.spin_trgt_caption = obj;
                            lv_obj_set_pos(obj, 14, 12);
                            lv_obj_set_size(obj, 200, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "TARGET RPM");
                        }
                        {
                            // spin_trgt_dec
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.spin_trgt_dec = obj;
                            lv_obj_set_pos(obj, 14, 38);
                            lv_obj_set_size(obj, 46, 46);
                            lv_obj_add_event_cb(obj, action_adjust_spindle_target, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spin_trgt_dec_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_trgt_dec_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 11);
                                    lv_obj_set_size(obj, 46, 24);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "-");
                                }
                            }
                        }
                        {
                            // spin_trgt_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.spin_trgt_val = obj;
                            lv_obj_set_pos(obj, 66, 48);
                            lv_obj_set_size(obj, 188, 30);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0");
                        }
                        {
                            // spin_trgt_inc
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.spin_trgt_inc = obj;
                            lv_obj_set_pos(obj, 260, 38);
                            lv_obj_set_size(obj, 46, 46);
                            lv_obj_add_event_cb(obj, action_adjust_spindle_target, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_dark(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spin_trgt_inc_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_trgt_inc_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 11);
                                    lv_obj_set_size(obj, 46, 24);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "+");
                                }
                            }
                        }
                    }
                }
                {
                    // spin_load_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.spin_load_card = obj;
                    lv_obj_set_pos(obj, 692, 122);
                    lv_obj_set_size(obj, 320, 70);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // spin_load_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.spin_load_lbl = obj;
                            lv_obj_set_pos(obj, 14, 12);
                            lv_obj_set_size(obj, 160, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "SPINDLE LOAD");
                        }
                        {
                            // spin_load_val
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.spin_load_val = obj;
                            lv_obj_set_pos(obj, 240, 10);
                            lv_obj_set_size(obj, 66, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_accent(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "0%");
                        }
                        {
                            // spin_load_bar
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.spin_load_bar = obj;
                            lv_obj_set_pos(obj, 14, 38);
                            lv_obj_set_size(obj, 292, 8);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK);
                            add_style_bar_default(obj);
                        }
                    }
                }
                {
                    // spin_cool_card
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.spin_cool_card = obj;
                    lv_obj_set_pos(obj, 692, 204);
                    lv_obj_set_size(obj, 320, 272);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_card(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // spin_cool_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.spin_cool_caption = obj;
                            lv_obj_set_pos(obj, 14, 12);
                            lv_obj_set_size(obj, 160, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "COOLANT");
                        }
                        {
                            // spin_cool_flood
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.spin_cool_flood = obj;
                            lv_obj_set_pos(obj, 14, 32);
                            lv_obj_set_size(obj, 141, 228);
                            lv_obj_add_event_cb(obj, action_toggle_flood, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_toggle(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spin_cool_flood_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_cool_flood_icon = obj;
                                    lv_obj_set_pos(obj, 0, 90);
                                    lv_obj_set_size(obj, 141, 32);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa28(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf043");
                                }
                                {
                                    // spin_cool_flood_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_cool_flood_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 128);
                                    lv_obj_set_size(obj, 141, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "FLOOD");
                                }
                            }
                        }
                        {
                            // spin_cool_mist
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.spin_cool_mist = obj;
                            lv_obj_set_pos(obj, 165, 32);
                            lv_obj_set_size(obj, 141, 228);
                            lv_obj_add_event_cb(obj, action_toggle_mist, LV_EVENT_CLICKED, (void *)0);
                            add_style_btn_toggle(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // spin_cool_mist_icon
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_cool_mist_icon = obj;
                                    lv_obj_set_pos(obj, 0, 90);
                                    lv_obj_set_size(obj, 141, 32);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa28(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf73d");
                                }
                                {
                                    // spin_cool_mist_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.spin_cool_mist_lbl = obj;
                                    lv_obj_set_pos(obj, 0, 128);
                                    lv_obj_set_size(obj, 141, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "MIST");
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // PageSpindle_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_spindle_dock = obj;
            lv_obj_set_pos(obj, 0, 534);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_dock(obj, 677);
        }
        {
            // PageSpindle_alarm
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_spindle_alarm = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_alarm_ribbon(obj, 703);
        }
    }
    
    tick_screen_page_spindle();
}

void tick_screen_page_spindle() {
    tick_user_widget_status_bar(624);
    tick_user_widget_bottom_dock(677);
    tick_user_widget_alarm_ribbon(703);
}

void create_screen_page_probe() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_probe = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // PageProbe_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_probe_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_status_bar(obj, 709);
        }
        {
            // PageProbe_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_probe_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 488);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_transparent(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // probe_left
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.probe_left = obj;
                    lv_obj_set_pos(obj, 12, 0);
                    lv_obj_set_size(obj, 300, 476);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_transparent(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // probe_cyc_caption
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.probe_cyc_caption = obj;
                            lv_obj_set_pos(obj, 4, 4);
                            lv_obj_set_size(obj, 200, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_caption(obj);
                            lv_label_set_text(obj, "PROBE CYCLE");
                        }
                        {
                            // probe_cyc_z
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.probe_cyc_z = obj;
                            lv_obj_set_pos(obj, 0, 24);
                            lv_obj_set_size(obj, 300, 60);
                            lv_obj_add_event_cb(obj, action_set_probe_type, LV_EVENT_CLICKED, (void *)0);
                            lv_obj_add_state(obj, LV_STATE_CHECKED);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // probe_cyc_icon_z
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_cyc_icon_z = obj;
                                    lv_obj_set_pos(obj, 12, 17);
                                    lv_obj_set_size(obj, 26, 26);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf063");
                                }
                                {
                                    // probe_cyc_lbl_z
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_cyc_lbl_z = obj;
                                    lv_obj_set_pos(obj, 44, 23);
                                    lv_obj_set_size(obj, 240, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Z Touch-Off");
                                }
                            }
                        }
                        {
                            // probe_cyc_corner
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.probe_cyc_corner = obj;
                            lv_obj_set_pos(obj, 0, 92);
                            lv_obj_set_size(obj, 300, 60);
                            lv_obj_add_event_cb(obj, action_set_probe_type, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // probe_cyc_icon_corner
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_cyc_icon_corner = obj;
                                    lv_obj_set_pos(obj, 12, 17);
                                    lv_obj_set_size(obj, 26, 26);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf126");
                                }
                                {
                                    // probe_cyc_lbl_corner
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_cyc_lbl_corner = obj;
                                    lv_obj_set_pos(obj, 44, 23);
                                    lv_obj_set_size(obj, 240, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Corner XYZ");
                                }
                            }
                        }
                        {
                            // probe_cyc_center
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.probe_cyc_center = obj;
                            lv_obj_set_pos(obj, 0, 160);
                            lv_obj_set_size(obj, 300, 60);
                            lv_obj_add_event_cb(obj, action_set_probe_type, LV_EVENT_CLICKED, (void *)2);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // probe_cyc_icon_center
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_cyc_icon_center = obj;
                                    lv_obj_set_pos(obj, 12, 17);
                                    lv_obj_set_size(obj, 26, 26);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf3c5");
                                }
                                {
                                    // probe_cyc_lbl_center
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_cyc_lbl_center = obj;
                                    lv_obj_set_pos(obj, 44, 23);
                                    lv_obj_set_size(obj, 240, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Center / Boss");
                                }
                            }
                        }
                        {
                            // probe_cyc_tool
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.probe_cyc_tool = obj;
                            lv_obj_set_pos(obj, 0, 228);
                            lv_obj_set_size(obj, 300, 60);
                            lv_obj_add_event_cb(obj, action_set_probe_type, LV_EVENT_CLICKED, (void *)3);
                            add_style_btn_selector(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // probe_cyc_icon_tool
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_cyc_icon_tool = obj;
                                    lv_obj_set_pos(obj, 12, 17);
                                    lv_obj_set_size(obj, 26, 26);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf545");
                                }
                                {
                                    // probe_cyc_lbl_tool
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_cyc_lbl_tool = obj;
                                    lv_obj_set_pos(obj, 44, 23);
                                    lv_obj_set_size(obj, 240, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_default(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Tool Length");
                                }
                            }
                        }
                    }
                }
                {
                    // probe_right
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.probe_right = obj;
                    lv_obj_set_pos(obj, 326, 0);
                    lv_obj_set_size(obj, 686, 476);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_transparent(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // probe_info_row
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.probe_info_row = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 686, 76);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // probe_info_plate
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.probe_info_plate = obj;
                                    lv_obj_set_pos(obj, 0, 0);
                                    lv_obj_set_size(obj, 222, 76);
                                    lv_obj_add_event_cb(obj, action_probe_edit_field, LV_EVENT_CLICKED, (void *)0);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_card(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // probe_info_plate_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_plate_lbl = obj;
                                            lv_obj_set_pos(obj, 12, 10);
                                            lv_obj_set_size(obj, 198, 10);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_caption(obj);
                                            lv_label_set_text(obj, "PLATE THICKNESS");
                                        }
                                        {
                                            // probe_info_plate_val
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_plate_val = obj;
                                            lv_obj_set_pos(obj, 12, 30);
                                            lv_obj_set_size(obj, 158, 30);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_mono_jog(obj);
                                            lv_obj_set_style_text_font(obj, &ui_font_mono_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "19.00");
                                        }
                                        {
                                            // probe_info_plate_unit
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_plate_unit = obj;
                                            lv_obj_set_pos(obj, 172, 40);
                                            lv_obj_set_size(obj, 36, 14);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_muted(obj);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "mm");
                                        }
                                    }
                                }
                                {
                                    // probe_info_feed
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.probe_info_feed = obj;
                                    lv_obj_set_pos(obj, 232, 0);
                                    lv_obj_set_size(obj, 222, 76);
                                    lv_obj_add_event_cb(obj, action_probe_edit_field, LV_EVENT_CLICKED, (void *)1);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_card(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // probe_info_feed_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_feed_lbl = obj;
                                            lv_obj_set_pos(obj, 12, 10);
                                            lv_obj_set_size(obj, 198, 10);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_caption(obj);
                                            lv_label_set_text(obj, "PROBE FEED");
                                        }
                                        {
                                            // probe_info_feed_val
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_feed_val = obj;
                                            lv_obj_set_pos(obj, 12, 30);
                                            lv_obj_set_size(obj, 158, 30);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_mono_jog(obj);
                                            lv_obj_set_style_text_font(obj, &ui_font_mono_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "100");
                                        }
                                        {
                                            // probe_info_feed_unit
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_feed_unit = obj;
                                            lv_obj_set_pos(obj, 172, 40);
                                            lv_obj_set_size(obj, 36, 14);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_muted(obj);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "mm/m");
                                        }
                                    }
                                }
                                {
                                    // probe_info_travel
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.probe_info_travel = obj;
                                    lv_obj_set_pos(obj, 464, 0);
                                    lv_obj_set_size(obj, 222, 76);
                                    lv_obj_add_event_cb(obj, action_probe_edit_field, LV_EVENT_CLICKED, (void *)2);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_card(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // probe_info_travel_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_travel_lbl = obj;
                                            lv_obj_set_pos(obj, 12, 10);
                                            lv_obj_set_size(obj, 198, 10);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_caption(obj);
                                            lv_label_set_text(obj, "MAX TRAVEL");
                                        }
                                        {
                                            // probe_info_travel_val
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_travel_val = obj;
                                            lv_obj_set_pos(obj, 12, 30);
                                            lv_obj_set_size(obj, 158, 30);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_mono_jog(obj);
                                            lv_obj_set_style_text_font(obj, &ui_font_mono_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "25");
                                        }
                                        {
                                            // probe_info_travel_unit
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_info_travel_unit = obj;
                                            lv_obj_set_pos(obj, 172, 40);
                                            lv_obj_set_size(obj, 36, 14);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_muted(obj);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "mm");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // probe_z_card
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.probe_z_card = obj;
                            lv_obj_set_pos(obj, 0, 88);
                            lv_obj_set_size(obj, 686, 376);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_card(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // probe_z_caption
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_z_caption = obj;
                                    lv_obj_set_pos(obj, 16, 16);
                                    lv_obj_set_size(obj, 220, 12);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_caption(obj);
                                    lv_label_set_text(obj, "CURRENT Z (WORK)");
                                }
                                {
                                    // probe_z_value
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_z_value = obj;
                                    lv_obj_set_pos(obj, 16, 36);
                                    lv_obj_set_size(obj, 486, 60);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_info(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_50, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "0.000");
                                }
                                {
                                    // probe_status_dot
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.probe_status_dot = obj;
                                    lv_obj_set_pos(obj, 16, 104);
                                    lv_obj_set_size(obj, 10, 10);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_status_pill_dot(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 1000, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_color(obj, lv_color_hex(theme_colors[active_theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_opa(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_width(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_shadow_spread(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // probe_status_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.probe_status_lbl = obj;
                                    lv_obj_set_pos(obj, 32, 102);
                                    lv_obj_set_size(obj, 280, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_secondary(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Probe inactive");
                                }
                                {
                                    // probe_btn_start
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.probe_btn_start = obj;
                                    lv_obj_set_pos(obj, 526, 118);
                                    lv_obj_set_size(obj, 140, 140);
                                    lv_obj_add_event_cb(obj, action_probe_start, LV_EVENT_CLICKED, (void *)0);
                                    add_style_btn_round(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // probe_btn_start_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_btn_start_icon = obj;
                                            lv_obj_set_pos(obj, 0, 32);
                                            lv_obj_set_size(obj, 140, 42);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_icon_fa28(obj);
                                            lv_obj_set_style_text_font(obj, &ui_font_fa_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "\uf3c5");
                                        }
                                        {
                                            // probe_btn_start_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.probe_btn_start_lbl = obj;
                                            lv_obj_set_pos(obj, 0, 84);
                                            lv_obj_set_size(obj, 140, 16);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_accent(obj);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "PROBE");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // PageProbe_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_probe_dock = obj;
            lv_obj_set_pos(obj, 0, 534);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_dock(obj, 768);
        }
        {
            // probe_edit_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.probe_edit_panel = obj;
            lv_obj_set_pos(obj, 24, 60);
            lv_obj_set_size(obj, 976, 470);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            add_style_card(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // probe_edit_caption
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.probe_edit_caption = obj;
                    lv_obj_set_pos(obj, 20, 12);
                    lv_obj_set_size(obj, 240, 14);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_caption(obj);
                    lv_label_set_text(obj, "EDIT VALUE");
                }
                {
                    // probe_edit_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.probe_edit_label = obj;
                    lv_obj_set_pos(obj, 20, 32);
                    lv_obj_set_size(obj, 936, 28);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_label_heading(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Plate thickness (mm)");
                }
                {
                    // probe_edit_input
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.probe_edit_input = obj;
                    lv_obj_set_pos(obj, 20, 72);
                    lv_obj_set_size(obj, 936, 56);
                    lv_textarea_set_max_length(obj, 16);
                    lv_textarea_set_placeholder_text(obj, "19.00");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_add_event_cb(obj, action_probe_edit_done, LV_EVENT_READY, (void *)0);
                    lv_obj_add_event_cb(obj, action_probe_kb_hide, LV_EVENT_CANCEL, (void *)0);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_textarea_default(obj);
                }
                {
                    // probe_edit_divider
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.probe_edit_divider = obj;
                    lv_obj_set_pos(obj, 20, 136);
                    lv_obj_set_size(obj, 936, 1);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_panel_transparent(obj);
                }
                {
                    // probe_edit_keyboard
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    objects.probe_edit_keyboard = obj;
                    lv_obj_set_pos(obj, 20, 144);
                    lv_obj_set_size(obj, 936, 260);
                    lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    add_style_keyboard_default(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // probe_edit_cancel
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.probe_edit_cancel = obj;
                    lv_obj_set_pos(obj, 20, 412);
                    lv_obj_set_size(obj, 160, 48);
                    lv_obj_add_event_cb(obj, action_probe_kb_hide, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_dark(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // probe_edit_cancel_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.probe_edit_cancel_lbl = obj;
                            lv_obj_set_pos(obj, 0, 16);
                            lv_obj_set_size(obj, 160, 14);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "CANCEL");
                        }
                    }
                }
                {
                    // probe_edit_done
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.probe_edit_done = obj;
                    lv_obj_set_pos(obj, 776, 412);
                    lv_obj_set_size(obj, 180, 48);
                    lv_obj_add_event_cb(obj, action_probe_edit_done, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_accent_fill(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // probe_edit_done_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.probe_edit_done_lbl = obj;
                            lv_obj_set_pos(obj, 0, 16);
                            lv_obj_set_size(obj, 180, 14);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "DONE");
                        }
                    }
                }
            }
        }
        {
            // PageProbe_alarm
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_probe_alarm = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_alarm_ribbon(obj, 804);
        }
    }
    
    tick_screen_page_probe();
}

void tick_screen_page_probe() {
    tick_user_widget_status_bar(709);
    tick_user_widget_bottom_dock(768);
    tick_user_widget_alarm_ribbon(804);
}

void create_screen_page_macros() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_macros = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // PageMacros_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_macros_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_status_bar(obj, 810);
        }
        {
            // PageMacros_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_macros_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 488);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_transparent(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // macros_0
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.macros_0 = obj;
                    lv_obj_set_pos(obj, 12, 12);
                    lv_obj_set_size(obj, 242, 227);
                    lv_obj_add_event_cb(obj, action_run_macro, LV_EVENT_CLICKED, (void *)0);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // macros_icon_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_icon_0 = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf063");
                        }
                        {
                            // macros_name_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_name_0 = obj;
                            lv_obj_set_pos(obj, 14, 179);
                            lv_obj_set_size(obj, 214, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Go To Front");
                        }
                        {
                            // macros_sub_0
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_sub_0 = obj;
                            lv_obj_set_pos(obj, 14, 201);
                            lv_obj_set_size(obj, 214, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "G53 Z0 . X0 Y0");
                        }
                    }
                }
                {
                    // macros_1
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.macros_1 = obj;
                    lv_obj_set_pos(obj, 264, 12);
                    lv_obj_set_size(obj, 242, 227);
                    lv_obj_add_event_cb(obj, action_run_macro, LV_EVENT_CLICKED, (void *)1);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // macros_icon_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_icon_1 = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf6e3");
                        }
                        {
                            // macros_name_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_name_1 = obj;
                            lv_obj_set_pos(obj, 14, 179);
                            lv_obj_set_size(obj, 214, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Tool Change");
                        }
                        {
                            // macros_sub_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_sub_1 = obj;
                            lv_obj_set_pos(obj, 14, 201);
                            lv_obj_set_size(obj, 214, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "M6 . Park rear");
                        }
                    }
                }
                {
                    // macros_2
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.macros_2 = obj;
                    lv_obj_set_pos(obj, 516, 12);
                    lv_obj_set_size(obj, 242, 227);
                    lv_obj_add_event_cb(obj, action_run_macro, LV_EVENT_CLICKED, (void *)2);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // macros_icon_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_icon_2 = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf3c5");
                        }
                        {
                            // macros_name_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_name_2 = obj;
                            lv_obj_set_pos(obj, 14, 179);
                            lv_obj_set_size(obj, 214, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Probe Z Plate");
                        }
                        {
                            // macros_sub_2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_sub_2 = obj;
                            lv_obj_set_pos(obj, 14, 201);
                            lv_obj_set_size(obj, 214, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "G38.2 Z-25");
                        }
                    }
                }
                {
                    // macros_3
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.macros_3 = obj;
                    lv_obj_set_pos(obj, 768, 12);
                    lv_obj_set_size(obj, 242, 227);
                    lv_obj_add_event_cb(obj, action_run_macro, LV_EVENT_CLICKED, (void *)3);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // macros_icon_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_icon_3 = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf5fd");
                        }
                        {
                            // macros_name_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_name_3 = obj;
                            lv_obj_set_pos(obj, 14, 179);
                            lv_obj_set_size(obj, 214, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Surface Spoilboard");
                        }
                        {
                            // macros_sub_3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_sub_3 = obj;
                            lv_obj_set_pos(obj, 14, 201);
                            lv_obj_set_size(obj, 214, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Facing cycle");
                        }
                    }
                }
                {
                    // macros_4
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.macros_4 = obj;
                    lv_obj_set_pos(obj, 12, 249);
                    lv_obj_set_size(obj, 242, 227);
                    lv_obj_add_event_cb(obj, action_run_macro, LV_EVENT_CLICKED, (void *)4);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // macros_icon_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_icon_4 = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf024");
                        }
                        {
                            // macros_name_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_name_4 = obj;
                            lv_obj_set_pos(obj, 14, 179);
                            lv_obj_set_size(obj, 214, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Set G54 Zero");
                        }
                        {
                            // macros_sub_4
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_sub_4 = obj;
                            lv_obj_set_pos(obj, 14, 201);
                            lv_obj_set_size(obj, 214, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "G10 L20 P1");
                        }
                    }
                }
                {
                    // macros_5
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.macros_5 = obj;
                    lv_obj_set_pos(obj, 264, 249);
                    lv_obj_set_size(obj, 242, 227);
                    lv_obj_add_event_cb(obj, action_run_macro, LV_EVENT_CLICKED, (void *)5);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // macros_icon_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_icon_5 = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf021");
                        }
                        {
                            // macros_name_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_name_5 = obj;
                            lv_obj_set_pos(obj, 14, 179);
                            lv_obj_set_size(obj, 214, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Spindle Warmup");
                        }
                        {
                            // macros_sub_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_sub_5 = obj;
                            lv_obj_set_pos(obj, 14, 201);
                            lv_obj_set_size(obj, 214, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "M3 S8000 . 60s");
                        }
                    }
                }
                {
                    // macros_6
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.macros_6 = obj;
                    lv_obj_set_pos(obj, 516, 249);
                    lv_obj_set_size(obj, 242, 227);
                    lv_obj_add_event_cb(obj, action_run_macro, LV_EVENT_CLICKED, (void *)6);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // macros_icon_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_icon_6 = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf124");
                        }
                        {
                            // macros_name_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_name_6 = obj;
                            lv_obj_set_pos(obj, 14, 179);
                            lv_obj_set_size(obj, 214, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Park Rear Right");
                        }
                        {
                            // macros_sub_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_sub_6 = obj;
                            lv_obj_set_pos(obj, 14, 201);
                            lv_obj_set_size(obj, 214, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "G53 X-10 Y-10");
                        }
                    }
                }
                {
                    // macros_7
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.macros_7 = obj;
                    lv_obj_set_pos(obj, 768, 249);
                    lv_obj_set_size(obj, 242, 227);
                    lv_obj_add_event_cb(obj, action_run_macro, LV_EVENT_CLICKED, (void *)7);
                    add_style_style_button_default(obj);
                    lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // macros_icon_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_icon_7 = obj;
                            lv_obj_set_pos(obj, 14, 14);
                            lv_obj_set_size(obj, 32, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa28(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf09c");
                        }
                        {
                            // macros_name_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_name_7 = obj;
                            lv_obj_set_pos(obj, 14, 179);
                            lv_obj_set_size(obj, 214, 16);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_heading(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Unlock");
                        }
                        {
                            // macros_sub_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.macros_sub_7 = obj;
                            lv_obj_set_pos(obj, 14, 201);
                            lv_obj_set_size(obj, 214, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_muted(obj);
                            lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "$X . Clear alarm");
                        }
                    }
                }
            }
        }
        {
            // PageMacros_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_macros_dock = obj;
            lv_obj_set_pos(obj, 0, 534);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_dock(obj, 865);
        }
        {
            // PageMacros_alarm
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_macros_alarm = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_alarm_ribbon(obj, 891);
        }
    }
    
    tick_screen_page_macros();
}

void tick_screen_page_macros() {
    tick_user_widget_status_bar(810);
    tick_user_widget_bottom_dock(865);
    tick_user_widget_alarm_ribbon(891);
}

void create_screen_page_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.page_settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    add_style_style_screen_default(obj);
    {
        lv_obj_t *parent_obj = obj;
        {
            // PageSettings_status_bar
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_settings_status_bar = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_status_bar(obj, 897);
        }
        {
            // PageSettings_body
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_settings_body = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 488);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_transparent(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // settings_nav
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.settings_nav = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 190, 488);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_transparent(obj);
                    lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // settings_nav_machine
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.settings_nav_machine = obj;
                            lv_obj_set_pos(obj, 8, 10);
                            lv_obj_set_size(obj, 174, 42);
                            lv_obj_add_event_cb(obj, action_open_settings_tab, LV_EVENT_CLICKED, (void *)0);
                            lv_obj_add_state(obj, LV_STATE_CHECKED);
                            add_style_btn_settings_nav(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_nav_icon_machine
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_icon_machine = obj;
                                    lv_obj_set_pos(obj, 11, 11);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_fa_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf013");
                                }
                                {
                                    // settings_nav_lbl_machine
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_lbl_machine = obj;
                                    lv_obj_set_pos(obj, 38, 12);
                                    lv_obj_set_size(obj, 130, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Machine");
                                }
                            }
                        }
                        {
                            // settings_nav_connection
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.settings_nav_connection = obj;
                            lv_obj_set_pos(obj, 8, 60);
                            lv_obj_set_size(obj, 174, 42);
                            lv_obj_add_event_cb(obj, action_open_settings_tab, LV_EVENT_CLICKED, (void *)1);
                            add_style_btn_settings_nav(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_nav_icon_connection
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_icon_connection = obj;
                                    lv_obj_set_pos(obj, 11, 11);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_fa_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf1eb");
                                }
                                {
                                    // settings_nav_lbl_connection
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_lbl_connection = obj;
                                    lv_obj_set_pos(obj, 38, 12);
                                    lv_obj_set_size(obj, 130, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Connection");
                                }
                            }
                        }
                        {
                            // settings_nav_motion
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.settings_nav_motion = obj;
                            lv_obj_set_pos(obj, 8, 110);
                            lv_obj_set_size(obj, 174, 42);
                            lv_obj_add_event_cb(obj, action_open_settings_tab, LV_EVENT_CLICKED, (void *)2);
                            add_style_btn_settings_nav(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_nav_icon_motion
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_icon_motion = obj;
                                    lv_obj_set_pos(obj, 11, 11);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_fa_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf124");
                                }
                                {
                                    // settings_nav_lbl_motion
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_lbl_motion = obj;
                                    lv_obj_set_pos(obj, 38, 12);
                                    lv_obj_set_size(obj, 130, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Motion");
                                }
                            }
                        }
                        {
                            // settings_nav_system
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.settings_nav_system = obj;
                            lv_obj_set_pos(obj, 8, 160);
                            lv_obj_set_size(obj, 174, 42);
                            lv_obj_add_event_cb(obj, action_open_settings_tab, LV_EVENT_CLICKED, (void *)3);
                            add_style_btn_settings_nav(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_nav_icon_system
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_icon_system = obj;
                                    lv_obj_set_pos(obj, 11, 11);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_fa_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf05a");
                                }
                                {
                                    // settings_nav_lbl_system
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_lbl_system = obj;
                                    lv_obj_set_pos(obj, 38, 12);
                                    lv_obj_set_size(obj, 130, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "System");
                                }
                            }
                        }
                        {
                            // settings_nav_display
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.settings_nav_display = obj;
                            lv_obj_set_pos(obj, 8, 210);
                            lv_obj_set_size(obj, 174, 42);
                            lv_obj_add_event_cb(obj, action_open_settings_tab, LV_EVENT_CLICKED, (void *)4);
                            add_style_btn_settings_nav(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_nav_icon_display
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_icon_display = obj;
                                    lv_obj_set_pos(obj, 11, 11);
                                    lv_obj_set_size(obj, 20, 20);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_icon_fa22(obj);
                                    lv_obj_set_style_text_font(obj, &ui_font_fa_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "\uf185");
                                }
                                {
                                    // settings_nav_lbl_display
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_nav_lbl_display = obj;
                                    lv_obj_set_pos(obj, 38, 12);
                                    lv_obj_set_size(obj, 130, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Display");
                                }
                            }
                        }
                    }
                }
                {
                    // settings_content
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.settings_content = obj;
                    lv_obj_set_pos(obj, 190, 0);
                    lv_obj_set_size(obj, 834, 488);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_panel_transparent(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // settings_panel_machine
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.settings_panel_machine = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 834, 488);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_machine_hdr
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_machine_hdr = obj;
                                    lv_obj_set_pos(obj, 18, 14);
                                    lv_obj_set_size(obj, 220, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Machine");
                                }
                                {
                                    // settings_units_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_units_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 52);
                                    lv_obj_set_size(obj, 200, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Display Units");
                                }
                                {
                                    // settings_units_sub
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_units_sub = obj;
                                    lv_obj_set_pos(obj, 18, 72);
                                    lv_obj_set_size(obj, 320, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Affects DRO, jog steps and probing");
                                }
                                {
                                    // settings_units_mm
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_units_mm = obj;
                                    lv_obj_set_pos(obj, 666, 56);
                                    lv_obj_set_size(obj, 70, 28);
                                    lv_obj_add_event_cb(obj, action_set_units, LV_EVENT_CLICKED, (void *)0);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                    add_style_btn_units_left(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_units_mm_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_units_mm_lbl = obj;
                                            lv_obj_set_pos(obj, 0, 7);
                                            lv_obj_set_size(obj, 70, 14);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_default(obj);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "MM");
                                        }
                                    }
                                }
                                {
                                    // settings_units_in
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_units_in = obj;
                                    lv_obj_set_pos(obj, 740, 56);
                                    lv_obj_set_size(obj, 70, 28);
                                    lv_obj_add_event_cb(obj, action_set_units, LV_EVENT_CLICKED, (void *)1);
                                    add_style_btn_units_left(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_units_in_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_units_in_lbl = obj;
                                            lv_obj_set_pos(obj, 0, 7);
                                            lv_obj_set_size(obj, 70, 14);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_default(obj);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "INCH");
                                        }
                                    }
                                }
                                {
                                    // settings_divider_1
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_divider_1 = obj;
                                    lv_obj_set_pos(obj, 18, 102);
                                    lv_obj_set_size(obj, 798, 1);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_panel_transparent(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // settings_home_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_home_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 116);
                                    lv_obj_set_size(obj, 200, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Home on Boot");
                                }
                                {
                                    // settings_home_sub
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_home_sub = obj;
                                    lv_obj_set_pos(obj, 18, 136);
                                    lv_obj_set_size(obj, 320, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Run homing cycle at power-on");
                                }
                                {
                                    // settings_home_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.settings_home_sw = obj;
                                    lv_obj_set_pos(obj, 740, 122);
                                    lv_obj_set_size(obj, 44, 25);
                                    lv_obj_add_event_cb(obj, action_toggle_home_on_boot, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // settings_machine_divider2
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_machine_divider2 = obj;
                                    lv_obj_set_pos(obj, 18, 170);
                                    lv_obj_set_size(obj, 798, 1);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    add_style_panel_transparent(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // settings_machine_ctrl_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_machine_ctrl_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 184);
                                    lv_obj_set_size(obj, 320, 16);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_heading(obj);
                                    lv_label_set_text(obj, "Controller");
                                }
                                {
                                    // settings_machine_ctrl_sub
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_machine_ctrl_sub = obj;
                                    lv_obj_set_pos(obj, 18, 204);
                                    lv_obj_set_size(obj, 480, 14);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_muted(obj);
                                    lv_label_set_text(obj, "Configure the FluidNC controller connection");
                                }
                                {
                                    // settings_btn_fluid_connect
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_btn_fluid_connect = obj;
                                    lv_obj_set_pos(obj, 18, 230);
                                    lv_obj_set_size(obj, 320, 44);
                                    lv_obj_add_event_cb(obj, action_open_fluid_connect, LV_EVENT_CLICKED, (void *)0);
                                    add_style_btn_dark(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_btn_fluid_connect_icon
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_btn_fluid_connect_icon = obj;
                                            lv_obj_set_pos(obj, 14, 9);
                                            lv_obj_set_size(obj, 26, 26);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_default(obj);
                                            lv_obj_set_style_text_font(obj, &ui_font_fa_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "\uf233");
                                        }
                                        {
                                            // settings_btn_fluid_connect_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_btn_fluid_connect_lbl = obj;
                                            lv_obj_set_pos(obj, 50, 14);
                                            lv_obj_set_size(obj, 260, 16);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_heading(obj);
                                            lv_label_set_text(obj, "Configure FluidNC Connection");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // settings_panel_connection
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.settings_panel_connection = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 834, 488);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_HIDDEN);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_conn_hdr
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_conn_hdr = obj;
                                    lv_obj_set_pos(obj, 18, 14);
                                    lv_obj_set_size(obj, 220, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Connection");
                                }
                                {
                                    // settings_conn_ssid_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_conn_ssid_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 52);
                                    lv_obj_set_size(obj, 200, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Saved Network");
                                }
                                {
                                    // settings_conn_ssid_val
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_conn_ssid_val = obj;
                                    lv_obj_set_pos(obj, 456, 52);
                                    lv_obj_set_size(obj, 360, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "(not connected)");
                                }
                                {
                                    // settings_conn_state_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_conn_state_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 78);
                                    lv_obj_set_size(obj, 200, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_label_set_text(obj, "Status");
                                }
                                {
                                    // settings_conn_state_val
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_conn_state_val = obj;
                                    lv_obj_set_pos(obj, 456, 78);
                                    lv_obj_set_size(obj, 360, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Disconnected");
                                }
                                {
                                    // settings_divider_conn
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_divider_conn = obj;
                                    lv_obj_set_pos(obj, 18, 108);
                                    lv_obj_set_size(obj, 798, 1);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_panel_transparent(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // settings_conn_change
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_conn_change = obj;
                                    lv_obj_set_pos(obj, 18, 122);
                                    lv_obj_set_size(obj, 200, 36);
                                    lv_obj_add_event_cb(obj, action_change_wifi, LV_EVENT_CLICKED, (void *)0);
                                    add_style_btn_dark(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_conn_change_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_conn_change_lbl = obj;
                                            lv_obj_set_pos(obj, 0, 11);
                                            lv_obj_set_size(obj, 200, 16);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_default(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "Change Network");
                                        }
                                    }
                                }
                                {
                                    // settings_conn_forget
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    objects.settings_conn_forget = obj;
                                    lv_obj_set_pos(obj, 234, 122);
                                    lv_obj_set_size(obj, 200, 36);
                                    lv_obj_add_event_cb(obj, action_wifi_forget, LV_EVENT_CLICKED, (void *)0);
                                    add_style_btn_danger_soft(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_conn_forget_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_conn_forget_lbl = obj;
                                            lv_obj_set_pos(obj, 0, 11);
                                            lv_obj_set_size(obj, 200, 16);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                            add_style_label_default(obj);
                                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "Forget Saved WiFi");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // settings_panel_motion
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.settings_panel_motion = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 834, 488);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_HIDDEN);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_motion_hdr
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_motion_hdr = obj;
                                    lv_obj_set_pos(obj, 18, 14);
                                    lv_obj_set_size(obj, 220, 18);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_heading(obj);
                                    lv_label_set_text(obj, "Motion");
                                }
                                {
                                    // settings_soft_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_soft_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 52);
                                    lv_obj_set_size(obj, 200, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Soft Limits");
                                }
                                {
                                    // settings_soft_sub
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_soft_sub = obj;
                                    lv_obj_set_pos(obj, 18, 72);
                                    lv_obj_set_size(obj, 320, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Block moves beyond travel envelope");
                                }
                                {
                                    // settings_soft_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.settings_soft_sw = obj;
                                    lv_obj_set_pos(obj, 740, 58);
                                    lv_obj_set_size(obj, 44, 25);
                                    lv_obj_add_event_cb(obj, action_toggle_soft_limits, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // settings_divider_2
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_divider_2 = obj;
                                    lv_obj_set_pos(obj, 18, 102);
                                    lv_obj_set_size(obj, 798, 1);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_panel_transparent(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // settings_hard_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_hard_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 116);
                                    lv_obj_set_size(obj, 200, 16);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Hard Limits");
                                }
                                {
                                    // settings_hard_sub
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_hard_sub = obj;
                                    lv_obj_set_pos(obj, 18, 136);
                                    lv_obj_set_size(obj, 320, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Endstop switches halt on contact");
                                }
                                {
                                    // settings_hard_sw
                                    lv_obj_t *obj = lv_switch_create(parent_obj);
                                    objects.settings_hard_sw = obj;
                                    lv_obj_set_pos(obj, 740, 122);
                                    lv_obj_set_size(obj, 44, 25);
                                    lv_obj_add_event_cb(obj, action_toggle_hard_limits, LV_EVENT_VALUE_CHANGED, (void *)0);
                                    lv_obj_add_state(obj, LV_STATE_CHECKED);
                                    add_style_switch_default(obj);
                                }
                                {
                                    // settings_divider_3
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_divider_3 = obj;
                                    lv_obj_set_pos(obj, 18, 168);
                                    lv_obj_set_size(obj, 798, 1);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_panel_transparent(obj);
                                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // settings_mot_jog_card
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_mot_jog_card = obj;
                                    lv_obj_set_pos(obj, 18, 184);
                                    lv_obj_set_size(obj, 798, 130);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    add_style_card(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_mot_jog_caption
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_mot_jog_caption = obj;
                                            lv_obj_set_pos(obj, 18, 12);
                                            lv_obj_set_size(obj, 200, 12);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_caption(obj);
                                            lv_label_set_text(obj, "DEFAULT JOG FEED");
                                        }
                                        {
                                            // settings_mot_jog_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_mot_jog_lbl = obj;
                                            lv_obj_set_pos(obj, 18, 30);
                                            lv_obj_set_size(obj, 320, 18);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_heading(obj);
                                            lv_label_set_text(obj, "Feed rate when jogging");
                                        }
                                        {
                                            // settings_mot_jog_sub
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_mot_jog_sub = obj;
                                            lv_obj_set_pos(obj, 18, 54);
                                            lv_obj_set_size(obj, 320, 14);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_muted(obj);
                                            lv_label_set_text(obj, "60 to 6000 mm/min");
                                        }
                                        {
                                            // settings_mot_jog_slider
                                            lv_obj_t *obj = lv_slider_create(parent_obj);
                                            objects.settings_mot_jog_slider = obj;
                                            lv_obj_set_pos(obj, 18, 88);
                                            lv_obj_set_size(obj, 580, 14);
                                            lv_slider_set_range(obj, 60, 6000);
                                            lv_slider_set_value(obj, 1200, LV_ANIM_ON);
                                            lv_obj_add_event_cb(obj, action_change_jog_feed_default, LV_EVENT_VALUE_CHANGED, (void *)0);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            add_style_style_default_slider(obj);
                                        }
                                        {
                                            // settings_mot_jog_val
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_mot_jog_val = obj;
                                            lv_obj_set_pos(obj, 620, 80);
                                            lv_obj_set_size(obj, 160, 22);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_heading(obj);
                                            lv_label_set_text(obj, "1200 mm/min");
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // settings_panel_system
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.settings_panel_system = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 834, 488);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_HIDDEN);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_system_hdr
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_system_hdr = obj;
                                    lv_obj_set_pos(obj, 18, 14);
                                    lv_obj_set_size(obj, 220, 18);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_heading(obj);
                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "System");
                                }
                                {
                                    // settings_sys_fw_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_sys_fw_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 52);
                                    lv_obj_set_size(obj, 200, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_label_set_text(obj, "Firmware");
                                }
                                {
                                    // settings_sys_fw_val
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_sys_fw_val = obj;
                                    lv_obj_set_pos(obj, 556, 52);
                                    lv_obj_set_size(obj, 260, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "(controller offline)");
                                }
                                {
                                    // settings_sys_ctl_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_sys_ctl_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 76);
                                    lv_obj_set_size(obj, 200, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_label_set_text(obj, "Controller");
                                }
                                {
                                    // settings_sys_ctl_val
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_sys_ctl_val = obj;
                                    lv_obj_set_pos(obj, 556, 76);
                                    lv_obj_set_size(obj, 260, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "(controller offline)");
                                }
                                {
                                    // settings_sys_ui_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_sys_ui_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 100);
                                    lv_obj_set_size(obj, 200, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_label_set_text(obj, "Interface");
                                }
                                {
                                    // settings_sys_ui_val
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_sys_ui_val = obj;
                                    lv_obj_set_pos(obj, 556, 100);
                                    lv_obj_set_size(obj, 260, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_mono_mini(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "LVGL 8.4 . 1024x600");
                                }
                                {
                                    // settings_sys_net_lbl
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_sys_net_lbl = obj;
                                    lv_obj_set_pos(obj, 18, 124);
                                    lv_obj_set_size(obj, 200, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_muted(obj);
                                    lv_label_set_text(obj, "Network");
                                }
                                {
                                    // settings_sys_net_val
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_sys_net_val = obj;
                                    lv_obj_set_pos(obj, 556, 124);
                                    lv_obj_set_size(obj, 260, 14);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                                    add_style_label_success(obj);
                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "Disconnected");
                                }
                            }
                        }
                        {
                            // settings_panel_display
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.settings_panel_display = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, 834, 488);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_HIDDEN);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            add_style_panel_transparent(obj);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // settings_display_hdr
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.settings_display_hdr = obj;
                                    lv_obj_set_pos(obj, 18, 14);
                                    lv_obj_set_size(obj, 220, 18);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    add_style_label_heading(obj);
                                    lv_label_set_text(obj, "Display");
                                }
                                {
                                    // settings_theme_card
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_theme_card = obj;
                                    lv_obj_set_pos(obj, 18, 52);
                                    lv_obj_set_size(obj, 798, 100);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    add_style_card(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_theme_caption
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_theme_caption = obj;
                                            lv_obj_set_pos(obj, 18, 12);
                                            lv_obj_set_size(obj, 200, 12);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_caption(obj);
                                            lv_label_set_text(obj, "THEME");
                                        }
                                        {
                                            // settings_theme_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_theme_lbl = obj;
                                            lv_obj_set_pos(obj, 18, 30);
                                            lv_obj_set_size(obj, 320, 18);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_heading(obj);
                                            lv_label_set_text(obj, "Color theme");
                                        }
                                        {
                                            // settings_theme_sub
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_theme_sub = obj;
                                            lv_obj_set_pos(obj, 18, 54);
                                            lv_obj_set_size(obj, 320, 14);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_muted(obj);
                                            lv_label_set_text(obj, "Light or dark interface");
                                        }
                                        {
                                            // settings_theme_light
                                            lv_obj_t *obj = lv_btn_create(parent_obj);
                                            objects.settings_theme_light = obj;
                                            lv_obj_set_pos(obj, 458, 28);
                                            lv_obj_set_size(obj, 160, 44);
                                            lv_obj_add_event_cb(obj, action_change_theme, LV_EVENT_CLICKED, (void *)0);
                                            add_style_btn_dark(obj);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // settings_theme_light_icon
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.settings_theme_light_icon = obj;
                                                    lv_obj_set_pos(obj, 16, 8);
                                                    lv_obj_set_size(obj, 28, 28);
                                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                                    add_style_label_default(obj);
                                                    lv_obj_set_style_text_font(obj, &ui_font_fa_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "\uf185");
                                                }
                                                {
                                                    // settings_theme_light_lbl
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.settings_theme_light_lbl = obj;
                                                    lv_obj_set_pos(obj, 52, 13);
                                                    lv_obj_set_size(obj, 100, 18);
                                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                                    add_style_label_heading(obj);
                                                    lv_label_set_text(obj, "Light");
                                                }
                                            }
                                        }
                                        {
                                            // settings_theme_dark
                                            lv_obj_t *obj = lv_btn_create(parent_obj);
                                            objects.settings_theme_dark = obj;
                                            lv_obj_set_pos(obj, 624, 28);
                                            lv_obj_set_size(obj, 160, 44);
                                            lv_obj_add_event_cb(obj, action_change_theme, LV_EVENT_CLICKED, (void *)1);
                                            lv_obj_add_state(obj, LV_STATE_CHECKED);
                                            add_style_btn_dark(obj);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // settings_theme_dark_icon
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.settings_theme_dark_icon = obj;
                                                    lv_obj_set_pos(obj, 16, 8);
                                                    lv_obj_set_size(obj, 28, 28);
                                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                                    add_style_label_default(obj);
                                                    lv_obj_set_style_text_font(obj, &ui_font_fa_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "\uf186");
                                                }
                                                {
                                                    // settings_theme_dark_lbl
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.settings_theme_dark_lbl = obj;
                                                    lv_obj_set_pos(obj, 52, 13);
                                                    lv_obj_set_size(obj, 100, 18);
                                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                                    add_style_label_heading(obj);
                                                    lv_label_set_text(obj, "Dark");
                                                }
                                            }
                                        }
                                    }
                                }
                                {
                                    // settings_disp_bright_card
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_disp_bright_card = obj;
                                    lv_obj_set_pos(obj, 18, 164);
                                    lv_obj_set_size(obj, 798, 130);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    add_style_card(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_disp_bright_caption
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_disp_bright_caption = obj;
                                            lv_obj_set_pos(obj, 18, 12);
                                            lv_obj_set_size(obj, 200, 12);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_caption(obj);
                                            lv_label_set_text(obj, "SCREEN BRIGHTNESS");
                                        }
                                        {
                                            // settings_disp_bright_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_disp_bright_lbl = obj;
                                            lv_obj_set_pos(obj, 18, 30);
                                            lv_obj_set_size(obj, 320, 18);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_heading(obj);
                                            lv_label_set_text(obj, "Backlight level");
                                        }
                                        {
                                            // settings_disp_bright_sub
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_disp_bright_sub = obj;
                                            lv_obj_set_pos(obj, 18, 54);
                                            lv_obj_set_size(obj, 320, 14);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_muted(obj);
                                            lv_label_set_text(obj, "10 to 255");
                                        }
                                        {
                                            // settings_disp_bright_slider
                                            lv_obj_t *obj = lv_slider_create(parent_obj);
                                            objects.settings_disp_bright_slider = obj;
                                            lv_obj_set_pos(obj, 18, 88);
                                            lv_obj_set_size(obj, 580, 14);
                                            lv_slider_set_range(obj, 10, 255);
                                            lv_slider_set_value(obj, 180, LV_ANIM_ON);
                                            lv_obj_add_event_cb(obj, action_change_screen_brightness, LV_EVENT_VALUE_CHANGED, (void *)0);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            add_style_style_default_slider(obj);
                                        }
                                        {
                                            // settings_disp_bright_val
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_disp_bright_val = obj;
                                            lv_obj_set_pos(obj, 620, 80);
                                            lv_obj_set_size(obj, 160, 22);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_heading(obj);
                                            lv_label_set_text(obj, "180");
                                        }
                                    }
                                }
                                {
                                    // settings_disp_to_card
                                    lv_obj_t *obj = lv_obj_create(parent_obj);
                                    objects.settings_disp_to_card = obj;
                                    lv_obj_set_pos(obj, 18, 306);
                                    lv_obj_set_size(obj, 798, 130);
                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                                    add_style_card(obj);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // settings_disp_to_caption
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_disp_to_caption = obj;
                                            lv_obj_set_pos(obj, 18, 12);
                                            lv_obj_set_size(obj, 200, 12);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_caption(obj);
                                            lv_label_set_text(obj, "SCREEN TIMEOUT");
                                        }
                                        {
                                            // settings_disp_to_lbl
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_disp_to_lbl = obj;
                                            lv_obj_set_pos(obj, 18, 30);
                                            lv_obj_set_size(obj, 320, 18);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_heading(obj);
                                            lv_label_set_text(obj, "Auto-blank after");
                                        }
                                        {
                                            // settings_disp_to_sub
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_disp_to_sub = obj;
                                            lv_obj_set_pos(obj, 18, 54);
                                            lv_obj_set_size(obj, 480, 14);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_muted(obj);
                                            lv_label_set_text(obj, "Minutes of inactivity (0 = never)");
                                        }
                                        {
                                            // settings_disp_to_dec
                                            lv_obj_t *obj = lv_btn_create(parent_obj);
                                            objects.settings_disp_to_dec = obj;
                                            lv_obj_set_pos(obj, 18, 80);
                                            lv_obj_set_size(obj, 60, 40);
                                            lv_obj_add_event_cb(obj, action_timeout_changed, LV_EVENT_CLICKED, (void *)0);
                                            add_style_btn_dark(obj);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // settings_disp_to_dec_lbl
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.settings_disp_to_dec_lbl = obj;
                                                    lv_obj_set_pos(obj, 0, 8);
                                                    lv_obj_set_size(obj, 60, 24);
                                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                                    add_style_label_heading(obj);
                                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "-");
                                                }
                                            }
                                        }
                                        {
                                            // settings_disp_to_val
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settings_disp_to_val = obj;
                                            lv_obj_set_pos(obj, 90, 86);
                                            lv_obj_set_size(obj, 200, 26);
                                            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                            add_style_label_heading(obj);
                                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                                            lv_label_set_text(obj, "5 min");
                                        }
                                        {
                                            // settings_disp_to_inc
                                            lv_obj_t *obj = lv_btn_create(parent_obj);
                                            objects.settings_disp_to_inc = obj;
                                            lv_obj_set_pos(obj, 298, 80);
                                            lv_obj_set_size(obj, 60, 40);
                                            lv_obj_add_event_cb(obj, action_timeout_changed, LV_EVENT_CLICKED, (void *)1);
                                            add_style_btn_dark(obj);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // settings_disp_to_inc_lbl
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.settings_disp_to_inc_lbl = obj;
                                                    lv_obj_set_pos(obj, 0, 8);
                                                    lv_obj_set_size(obj, 60, 24);
                                                    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
                                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                                    add_style_label_heading(obj);
                                                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "+");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            // PageSettings_dock
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_settings_dock = obj;
            lv_obj_set_pos(obj, 0, 534);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_bottom_dock(obj, 1019);
        }
        {
            // PageSettings_alarm
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.page_settings_alarm = obj;
            lv_obj_set_pos(obj, 0, 46);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_alarm_ribbon(obj, 1045);
        }
    }
    
    tick_screen_page_settings();
}

void tick_screen_page_settings() {
    tick_user_widget_status_bar(897);
    tick_user_widget_bottom_dock(1019);
    tick_user_widget_alarm_ribbon(1045);
}

void create_user_widget_status_bar(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // StatusBar_root
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 46);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_top_bar(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // status_brand_dot
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 12, 19);
                    lv_obj_set_size(obj, 8, 8);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_brand_dot(obj);
                }
                {
                    // status_brand
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 28, 16);
                    lv_obj_set_size(obj, 84, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_brand(obj);
                    lv_label_set_text(obj, "FLUIDCNC");
                }
                {
                    // status_pill
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 120, 12);
                    lv_obj_set_size(obj, 88, 22);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_status_pill(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // status_pill_dot
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                            lv_obj_set_pos(obj, 8, 8);
                            lv_obj_set_size(obj, 6, 6);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_status_pill_dot(obj);
                        }
                        {
                            // status_pill_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 20, 4);
                            lv_obj_set_size(obj, 60, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_secondary(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "IDLE");
                        }
                    }
                }
                {
                    // status_wcs
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                    lv_obj_set_pos(obj, 216, 16);
                    lv_obj_set_size(obj, 44, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_accent(obj);
                    lv_label_set_text(obj, "G54");
                }
                {
                    // status_wifi_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                    lv_obj_set_pos(obj, 686, 10);
                    lv_obj_set_size(obj, 26, 26);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_icon_fa22(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uf1eb");
                }
                {
                    // status_clock
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                    lv_obj_set_pos(obj, 688, 16);
                    lv_obj_set_size(obj, 56, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_secondary(obj);
                    lv_obj_set_style_text_font(obj, &ui_font_mono_13, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "14:32");
                }
                {
                    // status_btn_hold
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                    lv_obj_set_pos(obj, 752, 5);
                    lv_obj_set_size(obj, 92, 36);
                    lv_obj_add_event_cb(obj, action_hold_resume, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_hold(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // status_hold_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                            lv_obj_set_pos(obj, 5, 8);
                            lv_obj_set_size(obj, 20, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa16(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf04c");
                        }
                        {
                            // status_hold_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                            lv_obj_set_pos(obj, 29, 11);
                            lv_obj_set_size(obj, 50, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_warning(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "HOLD");
                        }
                    }
                }
                {
                    // status_btn_estop
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                    lv_obj_set_pos(obj, 852, 5);
                    lv_obj_set_size(obj, 124, 36);
                    lv_obj_add_event_cb(obj, action_estop, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_estop(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // status_estop_icon
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 13] = obj;
                            lv_obj_set_pos(obj, 22, 8);
                            lv_obj_set_size(obj, 20, 20);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa16(obj);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uf011");
                        }
                        {
                            // status_estop_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 14] = obj;
                            lv_obj_set_pos(obj, 48, 11);
                            lv_obj_set_size(obj, 54, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "E-STOP");
                        }
                    }
                }
                {
                    // status_axisX_letter
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 15] = obj;
                    lv_obj_set_pos(obj, 334, 16);
                    lv_obj_set_size(obj, 14, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_danger(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "X");
                }
                {
                    // status_mini_x
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 16] = obj;
                    lv_obj_set_pos(obj, 352, 16);
                    lv_obj_set_size(obj, 70, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_mono_mini(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "0.000");
                }
                {
                    // status_axisY_letter
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 17] = obj;
                    lv_obj_set_pos(obj, 430, 16);
                    lv_obj_set_size(obj, 14, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_success(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Y");
                }
                {
                    // status_mini_y
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 18] = obj;
                    lv_obj_set_pos(obj, 448, 16);
                    lv_obj_set_size(obj, 70, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_mono_mini(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "0.000");
                }
                {
                    // status_axisZ_letter
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 19] = obj;
                    lv_obj_set_pos(obj, 526, 16);
                    lv_obj_set_size(obj, 14, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_info(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Z");
                }
                {
                    // status_mini_z
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 20] = obj;
                    lv_obj_set_pos(obj, 544, 16);
                    lv_obj_set_size(obj, 70, 14);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_mono_mini(obj);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "0.000");
                }
            }
        }
    }
}

void tick_user_widget_status_bar(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void create_user_widget_bottom_dock(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // BottomDock_root
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 66);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_bottom_dock(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dock_btn_dash
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 8, 4);
                    lv_obj_set_size(obj, 122, 58);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_dock_inactive(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_icon_dash
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_label_set_text(obj, "\uf00a");
                        }
                        {
                            // dock_label_dash
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 122, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_dock_tab(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "DASHBOARD");
                        }
                    }
                }
                {
                    // dock_btn_jog
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                    lv_obj_set_pos(obj, 134, 4);
                    lv_obj_set_size(obj, 122, 58);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)1);
                    add_style_btn_dock_inactive(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_icon_jog
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 5] = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_label_set_text(obj, "\uf124");
                        }
                        {
                            // dock_label_jog
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 6] = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 122, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_dock_tab(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "JOG");
                        }
                    }
                }
                {
                    // dock_btn_run
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 7] = obj;
                    lv_obj_set_pos(obj, 260, 4);
                    lv_obj_set_size(obj, 122, 58);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)2);
                    add_style_btn_dock_inactive(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_icon_run
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 8] = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_label_set_text(obj, "\uf144");
                        }
                        {
                            // dock_label_run
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 9] = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 122, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_dock_tab(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "RUN");
                        }
                    }
                }
                {
                    // dock_btn_files
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 10] = obj;
                    lv_obj_set_pos(obj, 386, 4);
                    lv_obj_set_size(obj, 122, 58);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)3);
                    add_style_btn_dock_inactive(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_icon_files
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 11] = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_label_set_text(obj, "\uf07b");
                        }
                        {
                            // dock_label_files
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 12] = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 122, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_dock_tab(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "FILES");
                        }
                    }
                }
                {
                    // dock_btn_spindle
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 13] = obj;
                    lv_obj_set_pos(obj, 512, 4);
                    lv_obj_set_size(obj, 122, 58);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)4);
                    add_style_btn_dock_inactive(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_icon_spindle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 14] = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_label_set_text(obj, "\uf192");
                        }
                        {
                            // dock_label_spindle
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 15] = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 122, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_dock_tab(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SPINDLE");
                        }
                    }
                }
                {
                    // dock_btn_probe
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 16] = obj;
                    lv_obj_set_pos(obj, 638, 4);
                    lv_obj_set_size(obj, 122, 58);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)5);
                    add_style_btn_dock_inactive(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_icon_probe
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 17] = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_label_set_text(obj, "\uf3c5");
                        }
                        {
                            // dock_label_probe
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 18] = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 122, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_dock_tab(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "PROBE");
                        }
                    }
                }
                {
                    // dock_btn_macros
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 19] = obj;
                    lv_obj_set_pos(obj, 764, 4);
                    lv_obj_set_size(obj, 122, 58);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)6);
                    add_style_btn_dock_inactive(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_icon_macros
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 20] = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_label_set_text(obj, "\uf0e7");
                        }
                        {
                            // dock_label_macros
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 21] = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 122, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_dock_tab(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "MACROS");
                        }
                    }
                }
                {
                    // dock_btn_settings
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 22] = obj;
                    lv_obj_set_pos(obj, 890, 4);
                    lv_obj_set_size(obj, 122, 58);
                    lv_obj_add_event_cb(obj, action_change_screen, LV_EVENT_CLICKED, (void *)7);
                    add_style_btn_dock_inactive(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dock_icon_settings
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 23] = obj;
                            lv_obj_set_pos(obj, 48, 8);
                            lv_obj_set_size(obj, 26, 26);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_icon_fa22(obj);
                            lv_label_set_text(obj, "\uf013");
                        }
                        {
                            // dock_label_settings
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 24] = obj;
                            lv_obj_set_pos(obj, 0, 36);
                            lv_obj_set_size(obj, 122, 12);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_dock_tab(obj);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "SETTINGS");
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_bottom_dock(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void create_user_widget_alarm_ribbon(lv_obj_t *parent_obj, int startWidgetIndex) {
    (void)startWidgetIndex;
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            // AlarmRibbon_root
            lv_obj_t *obj = lv_obj_create(parent_obj);
            ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 1024, 38);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_panel_alarm(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // alarm_icon
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 1] = obj;
                    lv_obj_set_pos(obj, 12, 6);
                    lv_obj_set_size(obj, 26, 26);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_icon_fa22(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uf071");
                }
                {
                    // alarm_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 2] = obj;
                    lv_obj_set_pos(obj, 40, 10);
                    lv_obj_set_size(obj, 720, 18);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_label_default(obj);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "EMERGENCY STOP - PRESS RESET TO CLEAR");
                }
                {
                    // alarm_btn_reset
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 3] = obj;
                    lv_obj_set_pos(obj, 914, 6);
                    lv_obj_set_size(obj, 90, 28);
                    lv_obj_add_event_cb(obj, action_alarm_reset, LV_EVENT_CLICKED, (void *)0);
                    add_style_btn_dark(obj);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // alarm_reset_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            ((lv_obj_t **)&objects)[startWidgetIndex + 4] = obj;
                            lv_obj_set_pos(obj, 0, 6);
                            lv_obj_set_size(obj, 90, 14);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                            add_style_label_default(obj);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_letter_space(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "RESET");
                        }
                    }
                }
            }
        }
    }
}

void tick_user_widget_alarm_ribbon(int startWidgetIndex) {
    (void)startWidgetIndex;
}

void change_color_theme(uint32_t theme_index) {
    active_theme_index = theme_index;
    
    lv_style_set_bg_color(get_style_style_screen_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_text_color(get_style_style_screen_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_style_panel_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_border_color(get_style_style_panel_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_style_panel_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_panel_top_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_border_color(get_style_panel_top_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_panel_top_bar_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_panel_bottom_dock_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_border_color(get_style_panel_bottom_dock_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_bg_color(get_style_panel_alarm_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_text_color(get_style_panel_alarm_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_panel_dark_inset_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][12]));
    
    lv_style_set_border_color(get_style_panel_dark_inset_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_bg_color(get_style_card_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_border_color(get_style_card_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_label_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_label_caption_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    
    lv_style_set_text_color(get_style_label_section_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_label_heading_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_label_brand_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_label_accent_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_label_mono_mini_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_label_mono_jog_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_label_mono_dro_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_label_mono_spindle_val_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_label_mono_machine_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    
    lv_style_set_text_color(get_style_label_muted_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    
    lv_style_set_text_color(get_style_label_dock_tab_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    
    lv_style_set_text_color(get_style_label_dock_tab_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_label_secondary_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_text_color(get_style_label_success_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_text_color(get_style_label_info_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][8]));
    
    lv_style_set_text_color(get_style_label_warning_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_label_danger_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_text_color(get_style_icon_fa16_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_text_color(get_style_icon_fa22_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_text_color(get_style_icon_fa28_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_icon_fa_accent_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_icon_fa_axis_x_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_bg_color(get_style_axis_chip_x_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_style_set_text_color(get_style_axis_chip_x_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_axis_chip_y_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][5]));
    
    lv_style_set_text_color(get_style_axis_chip_y_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_axis_chip_z_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][6]));
    
    lv_style_set_text_color(get_style_axis_chip_z_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_text_color(get_style_axis_chip_label_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_border_color(get_style_status_pill_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_text_color(get_style_status_pill_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_bg_color(get_style_status_pill_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][7]));
    
    lv_style_set_text_color(get_style_status_pill_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_status_pill_MAIN_FOCUSED(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_status_pill_MAIN_FOCUSED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_status_pill_MAIN_DISABLED(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_text_color(get_style_status_pill_MAIN_DISABLED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_status_pill_dot_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_bg_color(get_style_status_pill_dot_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_status_pill_dot_MAIN_FOCUSED(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_bg_color(get_style_status_pill_dot_MAIN_DISABLED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_brand_dot_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_shadow_color(get_style_brand_dot_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_style_button_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_style_button_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_style_button_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_style_button_default_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_bg_color(get_style_btn_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_btn_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_btn_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_btn_accent_fill_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_accent_fill_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_shadow_color(get_style_btn_accent_fill_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_btn_accent_fill_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_btn_accent_soft_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    
    lv_style_set_border_color(get_style_btn_accent_soft_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_accent_soft_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_btn_hold_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][20]));
    
    lv_style_set_border_color(get_style_btn_hold_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_text_color(get_style_btn_hold_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][9]));
    
    lv_style_set_bg_color(get_style_btn_estop_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_border_color(get_style_btn_estop_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_text_color(get_style_btn_estop_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_shadow_color(get_style_btn_estop_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_bg_color(get_style_btn_danger_soft_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][21]));
    
    lv_style_set_border_color(get_style_btn_danger_soft_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_text_color(get_style_btn_danger_soft_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][10]));
    
    lv_style_set_bg_color(get_style_btn_round_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    
    lv_style_set_border_color(get_style_btn_round_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_round_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_shadow_color(get_style_btn_round_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_dock_inactive_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][18]));
    
    lv_style_set_bg_color(get_style_btn_dock_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][19]));
    
    lv_style_set_border_color(get_style_btn_dock_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_dock_active_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_btn_toggle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_border_color(get_style_btn_toggle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_btn_toggle_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_bg_color(get_style_btn_toggle_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][19]));
    
    lv_style_set_border_color(get_style_btn_toggle_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_toggle_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_btn_selector_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_border_color(get_style_btn_selector_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_btn_selector_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_bg_color(get_style_btn_selector_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][19]));
    
    lv_style_set_border_color(get_style_btn_selector_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_selector_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_btn_units_left_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_text_color(get_style_btn_units_left_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_bg_color(get_style_btn_units_left_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_units_left_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_btn_jog_pad_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_btn_jog_pad_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_btn_jog_pad_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_btn_jog_pad_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][19]));
    
    lv_style_set_border_color(get_style_btn_jog_pad_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_btn_settings_nav_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_bg_color(get_style_btn_settings_nav_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][19]));
    
    lv_style_set_text_color(get_style_btn_settings_nav_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_btn_file_row_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_border_color(get_style_btn_file_row_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_btn_file_row_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_btn_file_row_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][19]));
    
    lv_style_set_border_color(get_style_btn_file_row_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_btn_wifi_row_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_border_color(get_style_btn_wifi_row_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_btn_wifi_row_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_btn_wifi_row_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_btn_wifi_row_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_bar_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_bar_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_bar_progress_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_bar_progress_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_grad_color(get_style_bar_progress_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_arc_color(get_style_arc_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_arc_color(get_style_arc_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_style_default_slider_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_style_default_slider_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_style_default_slider_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_switch_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_bg_color(get_style_switch_default_MAIN_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_switch_default_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][17]));
    
    lv_style_set_bg_color(get_style_switch_default_KNOB_CHECKED(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_switch_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_bg_color(get_style_switch_default_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_keyboard_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_border_color(get_style_keyboard_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_keyboard_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_keyboard_default_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_border_color(get_style_keyboard_default_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_keyboard_default_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_keyboard_default_ITEMS_CHECKED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_keyboard_default_ITEMS_CHECKED(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_textarea_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_border_color(get_style_textarea_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_textarea_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_border_color(get_style_textarea_default_MAIN_FOCUSED(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_dropdown_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_border_color(get_style_dropdown_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][15]));
    
    lv_style_set_text_color(get_style_dropdown_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_text_color(get_style_checkbox_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_led_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_bg_color(get_style_list_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_bg_color(get_style_message_box_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_bg_color(get_style_roller_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_text_color(get_style_roller_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_arc_color(get_style_spinner_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_arc_color(get_style_spinner_default_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_text_color(get_style_tab_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_style_set_bg_color(get_style_tab_view_default_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][11]));
    
    lv_style_set_bg_color(get_style_default_button_matrix_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][13]));
    
    lv_style_set_bg_color(get_style_default_button_matrix_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][14]));
    
    lv_style_set_text_color(get_style_default_button_matrix_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][16]));
    
    lv_obj_set_style_text_color(objects.wifi_btn_refresh_icon, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_0, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_0, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_0, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_0, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_0, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_1, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_1, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_1, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_1, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_1, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_2, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_2, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_2, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_2, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_2, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_3, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_3, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_3, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_3, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_3, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_4, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_4, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_4, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_4, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_4, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_5, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_5, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_5, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_5, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_5, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_6, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_6, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_6, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_6, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_6, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_icon_7, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar1_7, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar2_7, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_net_bar3_7, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_net_lock_7, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.wifi_pwd_divider, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_pwd_connect_lbl, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.wifi_btn_skip_lbl, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.fluid_wifi_dot, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_shadow_color(objects.fluid_wifi_dot, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.fluid_tport_icon_0, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.fluid_tport_icon_1, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.fluid_tport_icon_2, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.fluid_btn_connect_icon, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.fluid_btn_connect_lbl, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.fluid_status_dot, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_shadow_color(objects.fluid_status_dot, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.fluid_btn_back_lbl, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_dro_zero_lbl_x, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_dro_zero_lbl_y, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_dro_zero_lbl_z, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_ov_val_feed, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_ov_val_rapid, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_ov_val_spindle, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_job_elapsed, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_job_eta, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_job_line, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.dash_tq_rpm_spindle, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_yp_icon, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_yp_lbl, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_xm_icon, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_xm_lbl, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_home_icon, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_xp_icon, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_xp_lbl, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_ym_icon, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_ym_lbl, lv_color_hex(theme_colors[theme_index][5]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_zp_icon, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.jog_zm_icon, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_hdr_pct, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_hdr_elapsed, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_hdr_remain, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_hdr_line, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_00_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_01_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_02_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_03_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_04_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_05_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_06_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_07_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_08_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_09_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_10_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_11_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_12_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_13_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_14_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_15_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_16_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_17_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_18_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_gc_19_t, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_btn_start_icon, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_btn_start_lbl, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_btn_hold_icon, lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_btn_stop_icon, lv_color_hex(theme_colors[theme_index][10]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.run_stat_spindle_val, lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.files_sel_icon, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.files_btn_load_icon, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.files_btn_load_lbl, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.files_stg_val, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.spin_trgt_val, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.spin_cool_flood_icon, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.spin_cool_flood_lbl, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.spin_cool_mist_icon, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.spin_cool_mist_lbl, lv_color_hex(theme_colors[theme_index][17]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.probe_cyc_icon_z, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.probe_cyc_icon_corner, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.probe_cyc_icon_center, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.probe_cyc_icon_tool, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.probe_z_value, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.probe_status_dot, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_shadow_color(objects.probe_status_dot, lv_color_hex(theme_colors[theme_index][7]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.probe_btn_start_icon, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.probe_btn_start_lbl, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.macros_0, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.macros_0, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_icon_0, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_sub_0, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.macros_1, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.macros_1, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_icon_1, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_sub_1, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.macros_2, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.macros_2, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_icon_2, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_sub_2, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.macros_3, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.macros_3, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_icon_3, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_sub_3, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.macros_4, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.macros_4, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_icon_4, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_sub_4, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.macros_5, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.macros_5, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_icon_5, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_sub_5, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.macros_6, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.macros_6, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_icon_6, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_sub_6, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.macros_7, lv_color_hex(theme_colors[theme_index][13]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.macros_7, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_icon_7, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.macros_sub_7, lv_color_hex(theme_colors[theme_index][18]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.settings_nav, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.settings_divider_1, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.settings_machine_divider2, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.settings_divider_conn, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.settings_divider_2, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.settings_divider_3, lv_color_hex(theme_colors[theme_index][15]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    {
        int startWidgetIndex = 159;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 271;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 277;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 403;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 409;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 543;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 549;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 618;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 624;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 703;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 709;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 804;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 810;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 891;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 897;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 7], lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 10], lv_color_hex(theme_colors[theme_index][9]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 13], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 14], lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    {
        int startWidgetIndex = 1045;
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 1], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 2], lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][11]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 3], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(((lv_obj_t **)&objects)[startWidgetIndex + 4], lv_color_hex(theme_colors[theme_index][16]), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    lv_obj_invalidate(objects.page_wifi_setup);
    lv_obj_invalidate(objects.page_fluid_connect);
    lv_obj_invalidate(objects.page_dashboard);
    lv_obj_invalidate(objects.page_jog);
    lv_obj_invalidate(objects.page_run);
    lv_obj_invalidate(objects.page_files);
    lv_obj_invalidate(objects.page_spindle);
    lv_obj_invalidate(objects.page_probe);
    lv_obj_invalidate(objects.page_macros);
    lv_obj_invalidate(objects.page_settings);
}

uint32_t theme_colors[2][22] = {
    { 0xffffffff, 0xff000000, 0xff52a441, 0xff469038, 0xffff5453, 0xff74fe00, 0xff48e6fe, 0xff388e3c, 0xff0288d1, 0xfff57c00, 0xffd32f2f, 0xffffffff, 0xfff5f5f5, 0xfff0f0f0, 0xffe0e0e0, 0xffdddddd, 0xff000000, 0xff555555, 0xff888888, 0xffe6f3dc, 0xfffff3e0, 0xffffebee },
    { 0xffffffff, 0xff000000, 0xff52a441, 0xff469038, 0xffff5453, 0xff74fe00, 0xff48e6fe, 0xff74fe00, 0xff48e6fe, 0xffffc107, 0xffff5453, 0xff000000, 0xff0a0a0a, 0xff1a1a1a, 0xff252525, 0xff333333, 0xffffffff, 0xffaaaaaa, 0xff666666, 0xff1a2c16, 0xff3a2a07, 0xff3a0f0f },
};


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_page_wifi_setup,
    tick_screen_page_fluid_connect,
    tick_screen_page_dashboard,
    tick_screen_page_jog,
    tick_screen_page_run,
    tick_screen_page_files,
    tick_screen_page_spindle,
    tick_screen_page_probe,
    tick_screen_page_macros,
    tick_screen_page_settings,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_page_wifi_setup();
    create_screen_page_fluid_connect();
    create_screen_page_dashboard();
    create_screen_page_jog();
    create_screen_page_run();
    create_screen_page_files();
    create_screen_page_spindle();
    create_screen_page_probe();
    create_screen_page_macros();
    create_screen_page_settings();
}
