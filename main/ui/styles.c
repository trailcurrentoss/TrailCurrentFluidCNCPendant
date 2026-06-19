#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: StyleScreenDefault
//

void init_style_style_screen_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_style_screen_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_screen_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_style_screen_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_screen_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_style_screen_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_screen_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: StylePanelDefault
//

void init_style_style_panel_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 12);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_style_panel_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_panel_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_style_panel_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_panel_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_style_panel_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_panel_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelTopBar
//

void init_style_panel_top_bar_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_TOP_LEFT);
    lv_style_set_min_width(style, 1024);
    lv_style_set_max_width(style, 1024);
    lv_style_set_min_height(style, 46);
    lv_style_set_max_height(style, 46);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_side(style, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_panel_top_bar_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_top_bar_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_top_bar(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_top_bar_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_top_bar(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_top_bar_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelBottomDock
//

void init_style_panel_bottom_dock_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_TOP_LEFT);
    lv_style_set_min_width(style, 1024);
    lv_style_set_max_width(style, 1024);
    lv_style_set_min_height(style, 66);
    lv_style_set_max_height(style, 66);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_side(style, LV_BORDER_SIDE_TOP);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_bottom_dock_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_bottom_dock_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_bottom_dock(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_bottom_dock_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_bottom_dock(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_bottom_dock_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelAlarm
//

void init_style_panel_alarm_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_align(style, LV_ALIGN_TOP_LEFT);
    lv_style_set_min_width(style, 1024);
    lv_style_set_max_width(style, 1024);
    lv_style_set_min_height(style, 38);
    lv_style_set_max_height(style, 38);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_alarm_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_alarm_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_alarm(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_alarm_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_alarm(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_alarm_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelTransparent
//

void init_style_panel_transparent_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 0);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_transparent_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_transparent_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_transparent(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_transparent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_transparent(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_transparent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: PanelDarkInset
//

void init_style_panel_dark_inset_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][12]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_panel_dark_inset_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_panel_dark_inset_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_panel_dark_inset(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_panel_dark_inset_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_panel_dark_inset(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_panel_dark_inset_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Card
//

void init_style_card_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_card_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_card_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_card(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_card_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_card(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_card_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelDefault
//

void init_style_label_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_label_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelCaption
//

void init_style_label_caption_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_text_font(style, &lv_font_montserrat_10);
    lv_style_set_text_letter_space(style, 1);
};

lv_style_t *get_style_label_caption_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_caption_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_caption(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_caption_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_caption(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_caption_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelSection
//

void init_style_label_section_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
};

lv_style_t *get_style_label_section_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_section_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_section(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_section_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_section(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_section_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelHeading
//

void init_style_label_heading_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
};

lv_style_t *get_style_label_heading_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_heading_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_heading(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_heading_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_heading(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_heading_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelBrand
//

void init_style_label_brand_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_text_letter_space(style, 2);
};

lv_style_t *get_style_label_brand_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_brand_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_brand(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_brand_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_brand(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_brand_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelAccent
//

void init_style_label_accent_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_font(style, &ui_font_mono_13);
    lv_style_set_text_letter_space(style, 1);
};

lv_style_t *get_style_label_accent_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_accent_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_accent(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_accent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_accent(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_accent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelMonoMini
//

void init_style_label_mono_mini_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &ui_font_mono_13);
};

lv_style_t *get_style_label_mono_mini_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_mono_mini_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_mono_mini(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_mono_mini_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_mono_mini(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_mono_mini_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelMonoJog
//

void init_style_label_mono_jog_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &ui_font_mono_30);
};

lv_style_t *get_style_label_mono_jog_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_mono_jog_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_mono_jog(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_mono_jog_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_mono_jog(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_mono_jog_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelMonoDro
//

void init_style_label_mono_dro_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &ui_font_mono_46);
};

lv_style_t *get_style_label_mono_dro_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_mono_dro_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_mono_dro(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_mono_dro_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_mono_dro(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_mono_dro_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelMonoSpindleVal
//

void init_style_label_mono_spindle_val_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &ui_font_mono_50);
};

lv_style_t *get_style_label_mono_spindle_val_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_mono_spindle_val_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_mono_spindle_val(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_mono_spindle_val_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_mono_spindle_val(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_mono_spindle_val_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelMonoMachine
//

void init_style_label_mono_machine_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_text_font(style, &ui_font_mono_13);
};

lv_style_t *get_style_label_mono_machine_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_mono_machine_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_mono_machine(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_mono_machine_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_mono_machine(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_mono_machine_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelMuted
//

void init_style_label_muted_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_label_muted_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_muted_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_muted(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_muted_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_muted(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_muted_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelDockTab
//

void init_style_label_dock_tab_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_text_font(style, &lv_font_montserrat_10);
};

lv_style_t *get_style_label_dock_tab_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_dock_tab_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_label_dock_tab_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_label_dock_tab_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_dock_tab_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_label_dock_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_dock_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_label_dock_tab_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_label_dock_tab(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_dock_tab_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_label_dock_tab_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: LabelSecondary
//

void init_style_label_secondary_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_label_secondary_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_secondary_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_secondary(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_secondary_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_secondary(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_secondary_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelSuccess
//

void init_style_label_success_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_label_success_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_success_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_success(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_success_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_success(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_success_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelInfo
//

void init_style_label_info_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][8]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_label_info_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_info_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_info(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_info_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_info(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_info_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelWarning
//

void init_style_label_warning_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][9]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_label_warning_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_warning_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_warning(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_warning_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_warning(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_warning_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LabelDanger
//

void init_style_label_danger_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_label_danger_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_label_danger_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_label_danger(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_label_danger_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_label_danger(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_label_danger_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: IconFa16
//

void init_style_icon_fa16_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_text_font(style, &ui_font_fa_16);
};

lv_style_t *get_style_icon_fa16_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_icon_fa16_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_icon_fa16(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_icon_fa16_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_icon_fa16(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_icon_fa16_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: IconFa22
//

void init_style_icon_fa22_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_text_font(style, &ui_font_fa_22);
};

lv_style_t *get_style_icon_fa22_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_icon_fa22_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_icon_fa22(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_icon_fa22_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_icon_fa22(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_icon_fa22_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: IconFa28
//

void init_style_icon_fa28_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_font(style, &ui_font_fa_28);
};

lv_style_t *get_style_icon_fa28_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_icon_fa28_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_icon_fa28(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_icon_fa28_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_icon_fa28(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_icon_fa28_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: IconFaAccent
//

void init_style_icon_fa_accent_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_font(style, &ui_font_fa_22);
};

lv_style_t *get_style_icon_fa_accent_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_icon_fa_accent_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_icon_fa_accent(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_icon_fa_accent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_icon_fa_accent(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_icon_fa_accent_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: IconFaAxisX
//

void init_style_icon_fa_axis_x_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][4]));
    lv_style_set_text_font(style, &ui_font_fa_22);
};

lv_style_t *get_style_icon_fa_axis_x_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_icon_fa_axis_x_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_icon_fa_axis_x(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_icon_fa_axis_x_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_icon_fa_axis_x(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_icon_fa_axis_x_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: AxisChipX
//

void init_style_axis_chip_x_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][4]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 7);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_axis_chip_x_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_axis_chip_x_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_axis_chip_x(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_axis_chip_x_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_axis_chip_x(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_axis_chip_x_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: AxisChipY
//

void init_style_axis_chip_y_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][5]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 7);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_axis_chip_y_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_axis_chip_y_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_axis_chip_y(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_axis_chip_y_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_axis_chip_y(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_axis_chip_y_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: AxisChipZ
//

void init_style_axis_chip_z_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][6]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 7);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_axis_chip_z_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_axis_chip_z_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_axis_chip_z(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_axis_chip_z_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_axis_chip_z(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_axis_chip_z_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: AxisChipLabel
//

void init_style_axis_chip_label_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
};

lv_style_t *get_style_axis_chip_label_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_axis_chip_label_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_axis_chip_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_axis_chip_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_axis_chip_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_axis_chip_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: StatusPill
//

void init_style_status_pill_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 0);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 6);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_status_pill_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_status_pill_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_status_pill_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][7]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_opa(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
};

lv_style_t *get_style_status_pill_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_status_pill_MAIN_CHECKED(style);
    }
    return style;
};

void init_style_status_pill_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][9]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_opa(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
};

lv_style_t *get_style_status_pill_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_status_pill_MAIN_FOCUSED(style);
    }
    return style;
};

void init_style_status_pill_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_opa(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
};

lv_style_t *get_style_status_pill_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_status_pill_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_status_pill(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_status_pill_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_status_pill_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_status_pill_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(obj, get_style_status_pill_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_status_pill(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_status_pill_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_status_pill_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_status_pill_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_remove_style(obj, get_style_status_pill_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: StatusPillDot
//

void init_style_status_pill_dot_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 1000);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_status_pill_dot_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_status_pill_dot_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_status_pill_dot_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_status_pill_dot_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_status_pill_dot_MAIN_CHECKED(style);
    }
    return style;
};

void init_style_status_pill_dot_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_status_pill_dot_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_status_pill_dot_MAIN_FOCUSED(style);
    }
    return style;
};

void init_style_status_pill_dot_MAIN_DISABLED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_status_pill_dot_MAIN_DISABLED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_status_pill_dot_MAIN_DISABLED(style);
    }
    return style;
};

void add_style_status_pill_dot(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_status_pill_dot_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_status_pill_dot_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_status_pill_dot_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(obj, get_style_status_pill_dot_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

void remove_style_status_pill_dot(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_status_pill_dot_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_status_pill_dot_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_status_pill_dot_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_remove_style(obj, get_style_status_pill_dot_MAIN_DISABLED(), LV_PART_MAIN | LV_STATE_DISABLED);
};

//
// Style: BrandDot
//

void init_style_brand_dot_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 1000);
    lv_style_set_shadow_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_shadow_opa(style, 200);
    lv_style_set_shadow_width(style, 12);
    lv_style_set_shadow_spread(style, 2);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_brand_dot_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_brand_dot_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_brand_dot(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_brand_dot_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_brand_dot(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_brand_dot_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: StyleButtonDefault
//

void init_style_style_button_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_style_button_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_button_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_style_button_default_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_style_button_default_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_button_default_MAIN_PRESSED(style);
    }
    return style;
};

void add_style_style_button_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_button_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_style_button_default_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

void remove_style_style_button_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_button_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_style_button_default_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

//
// Style: BtnDark
//

void init_style_btn_dark_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_dark_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_dark_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnAccentFill
//

void init_style_btn_accent_fill_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_shadow_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_shadow_opa(style, 100);
    lv_style_set_shadow_width(style, 18);
    lv_style_set_shadow_spread(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_accent_fill_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_accent_fill_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_accent_fill_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
};

lv_style_t *get_style_btn_accent_fill_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_accent_fill_MAIN_PRESSED(style);
    }
    return style;
};

void add_style_btn_accent_fill(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_accent_fill_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_accent_fill_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

void remove_style_btn_accent_fill(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_accent_fill_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_accent_fill_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

//
// Style: BtnAccentSoft
//

void init_style_btn_accent_soft_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_accent_soft_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_accent_soft_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_accent_soft(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_accent_soft_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_accent_soft(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_accent_soft_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnHold
//

void init_style_btn_hold_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][20]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][9]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 7);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][9]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_btn_hold_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_hold_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_hold(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_hold_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_hold(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_hold_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnEStop
//

void init_style_btn_estop_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 7);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_shadow_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_shadow_opa(style, 150);
    lv_style_set_shadow_width(style, 14);
    lv_style_set_shadow_spread(style, 0);
    lv_style_set_text_letter_space(style, 1);
};

lv_style_t *get_style_btn_estop_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_estop_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_estop(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_estop_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_estop(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_estop_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnDangerSoft
//

void init_style_btn_danger_soft_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][21]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 12);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][10]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_danger_soft_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_danger_soft_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_danger_soft(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_danger_soft_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_danger_soft(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_danger_soft_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnRound
//

void init_style_btn_round_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_border_width(style, 2);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 1000);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_shadow_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_shadow_opa(style, 80);
    lv_style_set_shadow_width(style, 24);
    lv_style_set_shadow_spread(style, 0);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_round_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_round_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_round(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_round_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_round(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_round_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnDockInactive
//

void init_style_btn_dock_inactive_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 0);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][18]));
    lv_style_set_text_font(style, &lv_font_montserrat_10);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_dock_inactive_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_dock_inactive_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_dock_inactive(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_dock_inactive_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_dock_inactive(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_dock_inactive_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnDockActive
//

void init_style_btn_dock_active_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_border_width(style, 2);
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_side(style, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_font(style, &lv_font_montserrat_10);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_dock_active_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_dock_active_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_btn_dock_active(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_dock_active_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_btn_dock_active(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_dock_active_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: BtnToggle
//

void init_style_btn_toggle_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 12);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_toggle_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_toggle_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_toggle_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_btn_toggle_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_toggle_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_btn_toggle(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_toggle_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_toggle_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_btn_toggle(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_toggle_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_toggle_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: BtnSelector
//

void init_style_btn_selector_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 7);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_selector_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_selector_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_selector_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_btn_selector_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_selector_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_btn_selector(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_selector_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_selector_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_btn_selector(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_selector_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_selector_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: BtnUnitsLeft
//

void init_style_btn_units_left_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 7);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_units_left_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_units_left_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_units_left_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
};

lv_style_t *get_style_btn_units_left_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_units_left_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_btn_units_left(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_units_left_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_units_left_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_btn_units_left(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_units_left_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_units_left_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: BtnJogPad
//

void init_style_btn_jog_pad_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 10);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_10);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_jog_pad_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_jog_pad_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_jog_pad_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_btn_jog_pad_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_jog_pad_MAIN_PRESSED(style);
    }
    return style;
};

void add_style_btn_jog_pad(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_jog_pad_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_jog_pad_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

void remove_style_btn_jog_pad(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_jog_pad_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_jog_pad_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

//
// Style: BtnSettingsNav
//

void init_style_btn_settings_nav_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 0);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_settings_nav_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_settings_nav_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_settings_nav_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_btn_settings_nav_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_settings_nav_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_btn_settings_nav(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_settings_nav_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_settings_nav_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_btn_settings_nav(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_settings_nav_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_settings_nav_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: BtnFileRow
//

void init_style_btn_file_row_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 9);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_file_row_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_file_row_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_file_row_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][19]));
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_btn_file_row_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_file_row_MAIN_CHECKED(style);
    }
    return style;
};

void add_style_btn_file_row(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_file_row_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_file_row_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

void remove_style_btn_file_row(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_file_row_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_file_row_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
};

//
// Style: BtnWifiRow
//

void init_style_btn_wifi_row_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 9);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
    lv_style_set_pad_top(style, 0);
    lv_style_set_pad_bottom(style, 0);
    lv_style_set_pad_left(style, 0);
    lv_style_set_pad_right(style, 0);
};

lv_style_t *get_style_btn_wifi_row_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_wifi_row_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_btn_wifi_row_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_btn_wifi_row_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_btn_wifi_row_MAIN_PRESSED(style);
    }
    return style;
};

void add_style_btn_wifi_row(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_btn_wifi_row_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_btn_wifi_row_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

void remove_style_btn_wifi_row(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_btn_wifi_row_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_btn_wifi_row_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

//
// Style: BarDefault
//

void init_style_bar_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 3);
};

lv_style_t *get_style_bar_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_bar_default_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 3);
};

lv_style_t *get_style_bar_default_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_default_INDICATOR_DEFAULT(style);
    }
    return style;
};

void add_style_bar_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_bar_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_bar_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

void remove_style_bar_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_bar_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_bar_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

//
// Style: BarProgress
//

void init_style_bar_progress_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 4);
};

lv_style_t *get_style_bar_progress_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_progress_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_bar_progress_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 4);
    lv_style_set_bg_grad_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_bg_grad_dir(style, LV_GRAD_DIR_HOR);
};

lv_style_t *get_style_bar_progress_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_bar_progress_INDICATOR_DEFAULT(style);
    }
    return style;
};

void add_style_bar_progress(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_bar_progress_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_bar_progress_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

void remove_style_bar_progress(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_bar_progress_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_bar_progress_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

//
// Style: ArcDefault
//

void init_style_arc_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_arc_width(style, 16);
    lv_style_set_arc_opa(style, 255);
};

lv_style_t *get_style_arc_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_arc_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_arc_default_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_arc_width(style, 16);
    lv_style_set_arc_opa(style, 255);
    lv_style_set_arc_rounded(style, true);
};

lv_style_t *get_style_arc_default_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_arc_default_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_arc_default_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 0);
};

lv_style_t *get_style_arc_default_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_arc_default_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_arc_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_arc_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_arc_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_arc_default_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_arc_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_arc_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_arc_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_arc_default_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
// Style: StyleDefaultSlider
//

void init_style_style_default_slider_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
    lv_style_set_radius(style, 3);
};

lv_style_t *get_style_style_default_slider_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_default_slider_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_style_default_slider_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 3);
};

lv_style_t *get_style_style_default_slider_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_default_slider_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_style_default_slider_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 1000);
};

lv_style_t *get_style_style_default_slider_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_style_default_slider_KNOB_DEFAULT(style);
    }
    return style;
};

void add_style_style_default_slider(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_style_default_slider_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_style_default_slider_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_style_default_slider_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

void remove_style_style_default_slider(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_style_default_slider_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_style_default_slider_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_style_default_slider_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
};

//
// Style: SwitchDefault
//

void init_style_switch_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 1000);
};

lv_style_t *get_style_switch_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_switch_default_MAIN_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_switch_default_MAIN_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_default_MAIN_CHECKED(style);
    }
    return style;
};

void init_style_switch_default_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][17]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 1000);
};

lv_style_t *get_style_switch_default_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_default_KNOB_DEFAULT(style);
    }
    return style;
};

void init_style_switch_default_KNOB_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_switch_default_KNOB_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_default_KNOB_CHECKED(style);
    }
    return style;
};

void init_style_switch_default_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_switch_default_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_default_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_switch_default_INDICATOR_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_switch_default_INDICATOR_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_switch_default_INDICATOR_CHECKED(style);
    }
    return style;
};

void add_style_switch_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_switch_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_switch_default_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_switch_default_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_switch_default_KNOB_CHECKED(), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_switch_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_switch_default_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
};

void remove_style_switch_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_switch_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_switch_default_MAIN_CHECKED(), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_switch_default_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_switch_default_KNOB_CHECKED(), LV_PART_KNOB | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_switch_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_switch_default_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
};

//
// Style: KeyboardDefault
//

void init_style_keyboard_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 12);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
};

lv_style_t *get_style_keyboard_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_keyboard_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_keyboard_default_ITEMS_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
};

lv_style_t *get_style_keyboard_default_ITEMS_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_keyboard_default_ITEMS_DEFAULT(style);
    }
    return style;
};

void init_style_keyboard_default_ITEMS_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
};

lv_style_t *get_style_keyboard_default_ITEMS_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_keyboard_default_ITEMS_CHECKED(style);
    }
    return style;
};

void add_style_keyboard_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_keyboard_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_keyboard_default_ITEMS_DEFAULT(), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_keyboard_default_ITEMS_CHECKED(), LV_PART_ITEMS | LV_STATE_CHECKED);
};

void remove_style_keyboard_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_keyboard_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_keyboard_default_ITEMS_DEFAULT(), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_keyboard_default_ITEMS_CHECKED(), LV_PART_ITEMS | LV_STATE_CHECKED);
};

//
// Style: TextareaDefault
//

void init_style_textarea_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
};

lv_style_t *get_style_textarea_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_textarea_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_textarea_default_MAIN_FOCUSED(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_textarea_default_MAIN_FOCUSED() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_textarea_default_MAIN_FOCUSED(style);
    }
    return style;
};

void add_style_textarea_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_textarea_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_textarea_default_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

void remove_style_textarea_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_textarea_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_textarea_default_MAIN_FOCUSED(), LV_PART_MAIN | LV_STATE_FOCUSED);
};

//
// Style: DropdownDefault
//

void init_style_dropdown_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][15]));
    lv_style_set_border_width(style, 1);
    lv_style_set_border_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_dropdown_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_dropdown_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_dropdown_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_dropdown_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_dropdown_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_dropdown_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: CheckboxDefault
//

void init_style_checkbox_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_checkbox_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_checkbox_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_checkbox_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_checkbox_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_checkbox_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_checkbox_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: LEDDefault
//

void init_style_led_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_led_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_led_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_led_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_led_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_led_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_led_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: ListDefault
//

void init_style_list_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_list_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_list_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_list_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_list_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_list_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_list_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: MessageBoxDefault
//

void init_style_message_box_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_message_box_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_message_box_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_message_box_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_message_box_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_message_box_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_message_box_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: RollerDefault
//

void init_style_roller_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_roller_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_roller_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_roller_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_roller_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_roller_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_roller_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: SpinnerDefault
//

void init_style_spinner_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_arc_width(style, 8);
};

lv_style_t *get_style_spinner_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_spinner_default_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_spinner_default_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_arc_width(style, 8);
};

lv_style_t *get_style_spinner_default_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_spinner_default_INDICATOR_DEFAULT(style);
    }
    return style;
};

void add_style_spinner_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_spinner_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_spinner_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

void remove_style_spinner_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_spinner_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_spinner_default_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

//
// Style: TabDefault
//

void init_style_tab_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 0);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_tab_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_tab_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_tab_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_tab_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_tab_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_tab_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: TabViewDefault
//

void init_style_tab_view_default_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][11]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_tab_view_default_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_tab_view_default_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_tab_view_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_tab_view_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_tab_view_default(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_tab_view_default_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: DefaultButtonMatrix
//

void init_style_default_button_matrix_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][13]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_width(style, 0);
};

lv_style_t *get_style_default_button_matrix_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_default_button_matrix_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_default_button_matrix_ITEMS_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][14]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_radius(style, 8);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][16]));
    lv_style_set_text_font(style, &lv_font_montserrat_12);
};

lv_style_t *get_style_default_button_matrix_ITEMS_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_default_button_matrix_ITEMS_DEFAULT(style);
    }
    return style;
};

void add_style_default_button_matrix(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_default_button_matrix_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_default_button_matrix_ITEMS_DEFAULT(), LV_PART_ITEMS | LV_STATE_DEFAULT);
};

void remove_style_default_button_matrix(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_default_button_matrix_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_default_button_matrix_ITEMS_DEFAULT(), LV_PART_ITEMS | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_style_screen_default,
        add_style_style_panel_default,
        add_style_panel_top_bar,
        add_style_panel_bottom_dock,
        add_style_panel_alarm,
        add_style_panel_transparent,
        add_style_panel_dark_inset,
        add_style_card,
        add_style_label_default,
        add_style_label_caption,
        add_style_label_section,
        add_style_label_heading,
        add_style_label_brand,
        add_style_label_accent,
        add_style_label_mono_mini,
        add_style_label_mono_jog,
        add_style_label_mono_dro,
        add_style_label_mono_spindle_val,
        add_style_label_mono_machine,
        add_style_label_muted,
        add_style_label_dock_tab,
        add_style_label_secondary,
        add_style_label_success,
        add_style_label_info,
        add_style_label_warning,
        add_style_label_danger,
        add_style_icon_fa16,
        add_style_icon_fa22,
        add_style_icon_fa28,
        add_style_icon_fa_accent,
        add_style_icon_fa_axis_x,
        add_style_axis_chip_x,
        add_style_axis_chip_y,
        add_style_axis_chip_z,
        add_style_axis_chip_label,
        add_style_status_pill,
        add_style_status_pill_dot,
        add_style_brand_dot,
        add_style_style_button_default,
        add_style_btn_dark,
        add_style_btn_accent_fill,
        add_style_btn_accent_soft,
        add_style_btn_hold,
        add_style_btn_estop,
        add_style_btn_danger_soft,
        add_style_btn_round,
        add_style_btn_dock_inactive,
        add_style_btn_dock_active,
        add_style_btn_toggle,
        add_style_btn_selector,
        add_style_btn_units_left,
        add_style_btn_jog_pad,
        add_style_btn_settings_nav,
        add_style_btn_file_row,
        add_style_btn_wifi_row,
        add_style_bar_default,
        add_style_bar_progress,
        add_style_arc_default,
        add_style_style_default_slider,
        add_style_switch_default,
        add_style_keyboard_default,
        add_style_textarea_default,
        add_style_dropdown_default,
        add_style_checkbox_default,
        add_style_led_default,
        add_style_list_default,
        add_style_message_box_default,
        add_style_roller_default,
        add_style_spinner_default,
        add_style_tab_default,
        add_style_tab_view_default,
        add_style_default_button_matrix,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_style_screen_default,
        remove_style_style_panel_default,
        remove_style_panel_top_bar,
        remove_style_panel_bottom_dock,
        remove_style_panel_alarm,
        remove_style_panel_transparent,
        remove_style_panel_dark_inset,
        remove_style_card,
        remove_style_label_default,
        remove_style_label_caption,
        remove_style_label_section,
        remove_style_label_heading,
        remove_style_label_brand,
        remove_style_label_accent,
        remove_style_label_mono_mini,
        remove_style_label_mono_jog,
        remove_style_label_mono_dro,
        remove_style_label_mono_spindle_val,
        remove_style_label_mono_machine,
        remove_style_label_muted,
        remove_style_label_dock_tab,
        remove_style_label_secondary,
        remove_style_label_success,
        remove_style_label_info,
        remove_style_label_warning,
        remove_style_label_danger,
        remove_style_icon_fa16,
        remove_style_icon_fa22,
        remove_style_icon_fa28,
        remove_style_icon_fa_accent,
        remove_style_icon_fa_axis_x,
        remove_style_axis_chip_x,
        remove_style_axis_chip_y,
        remove_style_axis_chip_z,
        remove_style_axis_chip_label,
        remove_style_status_pill,
        remove_style_status_pill_dot,
        remove_style_brand_dot,
        remove_style_style_button_default,
        remove_style_btn_dark,
        remove_style_btn_accent_fill,
        remove_style_btn_accent_soft,
        remove_style_btn_hold,
        remove_style_btn_estop,
        remove_style_btn_danger_soft,
        remove_style_btn_round,
        remove_style_btn_dock_inactive,
        remove_style_btn_dock_active,
        remove_style_btn_toggle,
        remove_style_btn_selector,
        remove_style_btn_units_left,
        remove_style_btn_jog_pad,
        remove_style_btn_settings_nav,
        remove_style_btn_file_row,
        remove_style_btn_wifi_row,
        remove_style_bar_default,
        remove_style_bar_progress,
        remove_style_arc_default,
        remove_style_style_default_slider,
        remove_style_switch_default,
        remove_style_keyboard_default,
        remove_style_textarea_default,
        remove_style_dropdown_default,
        remove_style_checkbox_default,
        remove_style_led_default,
        remove_style_list_default,
        remove_style_message_box_default,
        remove_style_roller_default,
        remove_style_spinner_default,
        remove_style_tab_default,
        remove_style_tab_view_default,
        remove_style_default_button_matrix,
    };
    remove_style_funcs[styleIndex](obj);
}

