#ifndef EEZ_LVGL_UI_FONTS_H
#define EEZ_LVGL_UI_FONTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_font_t ui_font_mono_13;
extern const lv_font_t ui_font_mono_22;
extern const lv_font_t ui_font_mono_30;
extern const lv_font_t ui_font_mono_46;
extern const lv_font_t ui_font_mono_50;
extern const lv_font_t ui_font_fa_16;
extern const lv_font_t ui_font_fa_22;
extern const lv_font_t ui_font_fa_28;

#ifndef EXT_FONT_DESC_T
#define EXT_FONT_DESC_T
typedef struct _ext_font_desc_t {
    const char *name;
    const void *font_ptr;
} ext_font_desc_t;
#endif

extern ext_font_desc_t fonts[];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_FONTS_H*/