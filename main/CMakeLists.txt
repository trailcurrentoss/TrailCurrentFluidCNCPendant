idf_component_register(
    SRCS
        "main.c"
        "app_state.c"
        "actions.c"
        "vars.c"
        "ui/screens.c"
        "ui/styles.c"
        "ui/images.c"
        "ui/ui.c"
        "ui/ui_font_mono_13.c"
        "ui/ui_font_mono_22.c"
        "ui/ui_font_mono_30.c"
        "ui/ui_font_mono_46.c"
        "ui/ui_font_mono_50.c"
        "ui/ui_font_fa_16.c"
        "ui/ui_font_fa_22.c"
        "ui/ui_font_fa_28.c"
    INCLUDE_DIRS "." "ui"
    REQUIRES
        nvs_flash
        esp_event
        esp_netif
        esp_timer
        esp_wifi
        pendant_config
        wifi_setup
        fluidnc
        waveshare__esp32_p4_wifi6_touch_lcd_7b
)

target_compile_definitions(${COMPONENT_LIB} PRIVATE MODULE_TYPE="fluidcnc_pendant")

idf_component_get_property(LVGL_LIB lvgl__lvgl COMPONENT_LIB)
target_compile_options(
    ${LVGL_LIB}
    PRIVATE
        -DLV_LVGL_H_INCLUDE_SIMPLE
)
