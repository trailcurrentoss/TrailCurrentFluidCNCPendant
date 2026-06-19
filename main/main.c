#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_heap_caps.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "lvgl.h"
#include "bsp/display.h"
#include "bsp/esp-bsp.h"

#include "app_state.h"
#include "pendant_config.h"
#include "thumbstick_monitor.h"

#if __has_include("ui/ui.h")
#  include "ui/ui.h"
#  include "ui/vars.h"
#  include "ui/screens.h"
#  define HAVE_UI 1
#else
#  define HAVE_UI 0
#endif

static const char *TAG = "fluidcnc-pendant";

#define USER_SETTINGS_NVS_NAMESPACE "user_settings"

#if HAVE_UI
/* Restore brightness / timeout / jog-feed from NVS after ui_init() exposes the
 * value labels. Falls back to the defaults baked into vars.c when an entry is
 * missing — the first boot after flashing always uses the defaults. */
static void restore_user_settings_from_nvs(void)
{
    nvs_handle_t nvs;
    if (nvs_open(USER_SETTINGS_NVS_NAMESPACE, NVS_READONLY, &nvs) != ESP_OK) {
        ESP_LOGI(TAG, "user_settings NVS namespace not present — using defaults");
        bsp_display_lock(0);
        bsp_display_brightness_set((int)get_var_screen_brightness());
        bsp_display_unlock();
        return;
    }

    uint8_t theme = 0;
    if (nvs_get_u8(nvs, "theme", &theme) == ESP_OK) {
        if (theme > 1) theme = 1;
        set_var_selected_theme(theme);
        ESP_LOGI(TAG, "restored theme=%d", (int)theme);
    } else {
        set_var_selected_theme(get_var_selected_theme());
    }

    uint8_t brightness = 0;
    if (nvs_get_u8(nvs, "brightness", &brightness) == ESP_OK) {
        if (brightness < 10) brightness = 10;   /* keep screen actually visible */
        set_var_screen_brightness(brightness);
        bsp_display_brightness_set(brightness);
        ESP_LOGI(TAG, "restored brightness=%d", (int)brightness);
    } else {
        bsp_display_brightness_set((int)get_var_screen_brightness());
    }

    int8_t timeout = 0;
    if (nvs_get_i8(nvs, "timeout", &timeout) == ESP_OK) {
        if (timeout < 0)  timeout = 0;
        if (timeout > 60) timeout = 60;
        set_var_screen_timeout_value(timeout);
        ESP_LOGI(TAG, "restored timeout=%d min", (int)timeout);
    } else {
        /* Force the default into the value label so it isn't stuck at "5". */
        set_var_screen_timeout_value(get_var_screen_timeout_value());
    }

    int16_t jog_feed = 0;
    if (nvs_get_i16(nvs, "jog_feed", &jog_feed) == ESP_OK) {
        if (jog_feed < 60)   jog_feed = 60;
        if (jog_feed > 6000) jog_feed = 6000;
        set_var_default_jog_feed(jog_feed);
        ESP_LOGI(TAG, "restored jog_feed=%d mm/min", (int)jog_feed);
    } else {
        set_var_default_jog_feed(get_var_default_jog_feed());
    }

    nvs_close(nvs);
}

/* Inactivity blanking — when no touch has fired for `screen_timeout_value`
 * minutes, dim the backlight to the minimum-visible floor and overlay a
 * full-screen invisible touch absorber. The next touch restores brightness.
 *
 * Floor is BLANK_BRIGHTNESS_FLOOR — 10/255 keeps the panel safely visible
 * (so the user can tell the device is alive and find where to touch),
 * doesn't burn power, and avoids the brownout-on-wake we saw at 0. The
 * EK79007 panel's LED driver spikes inrush current re-enabling from full
 * off; keeping the LED warm at 10 sidesteps that entirely. */
#define BLANK_BRIGHTNESS_FLOOR 10

static lv_obj_t *s_wake_overlay = NULL;
static int32_t   s_brightness_before_blank = 180;

static void wake_touch_cb(lv_event_t *e)
{
    (void)e;
    /* Defensive floor — if the saved brightness is below visible (user
     * had dragged the slider to near-zero before the screen blanked),
     * restore to the same floor we use for blanking. Otherwise the screen
     * stays apparently off after wake and the user can't recover. */
    int restore = (int)s_brightness_before_blank;
    if (restore < BLANK_BRIGHTNESS_FLOOR) restore = BLANK_BRIGHTNESS_FLOOR;
    bsp_display_brightness_set(restore);
    if (s_wake_overlay) {
        lv_obj_del(s_wake_overlay);
        s_wake_overlay = NULL;
    }
    ESP_LOGI(TAG, "screen wake — restored brightness %d", restore);
}

static void inactivity_blank_task(void *arg)
{
    (void)arg;
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        int32_t timeout_min = get_var_screen_timeout_value();
        if (timeout_min <= 0) continue;  /* 0 = disabled */

        bsp_display_lock(0);
        uint32_t idle_ms = lv_disp_get_inactive_time(NULL);
        bool already_blanked = (s_wake_overlay != NULL);
        if (!already_blanked && idle_ms >= (uint32_t)timeout_min * 60u * 1000u) {
            s_brightness_before_blank = get_var_screen_brightness();
            bsp_display_brightness_set(BLANK_BRIGHTNESS_FLOOR);
            s_wake_overlay = lv_obj_create(lv_layer_top());
            lv_obj_remove_style_all(s_wake_overlay);
            lv_obj_set_size(s_wake_overlay, LV_PCT(100), LV_PCT(100));
            lv_obj_add_flag(s_wake_overlay, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_clear_flag(s_wake_overlay, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_add_event_cb(s_wake_overlay, wake_touch_cb,
                                LV_EVENT_CLICKED, NULL);
            ESP_LOGI(TAG, "screen blanked after %d min inactivity",
                     (int)timeout_min);
        }
        bsp_display_unlock();
    }
}
#endif /* HAVE_UI */

void app_main(void)
{
    ESP_LOGI(TAG, "TrailCurrent FluidCNC Pendant booting");

    /* --- NVS (must come before WiFi or persistent config). --- */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* --- Default event loop (WiFi needs it, the BSP doesn't create one). --- */
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* --- Persistent pendant config from NVS. --- */
    ESP_ERROR_CHECK(pendant_config_init());

    /* --- Display + LVGL via the Waveshare ESP32-P4 BSP. --- */
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = {
            .task_priority      = 5,
            .task_stack         = 7168,
            .task_affinity      = 1,                 /* Core 1 — keep core 0 free for app/WiFi */
            .task_max_sleep_ms  = 500,
            .task_stack_caps    = MALLOC_CAP_INTERNAL | MALLOC_CAP_DEFAULT,
            .timer_period_ms    = 5,
        },
        .buffer_size   = BSP_LCD_H_RES * 100,        /* Larger draw buffer = fewer flushes */
        .double_buffer = 1,
        .flags = {
            .buff_dma    = false,
            .buff_spiram = true,                     /* Use PSRAM for draw buffers */
            .sw_rotate   = true,                     /* Match Fireside — required for 180° rotation */
        },
    };
    lv_display_t *disp = bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();
    if (disp == NULL) {
        ESP_LOGE(TAG, "Display init failed");
        return;
    }
    /* Match Fireside: panel mounted upside-down in the case, rotate 180°. */
    bsp_display_rotate(disp, LV_DISPLAY_ROTATION_180);

    /* --- Initialize the EEZ Studio-generated UI tree. --- */
#if HAVE_UI
    bsp_display_lock(0);
    ui_init();
    bsp_display_unlock();
    ESP_LOGI(TAG, "UI initialized");

    /* Restore persisted Display / Motion preferences and apply brightness
     * to the panel. Must come AFTER ui_init() because set_var_*() pokes the
     * value labels (and slider knobs) created during init. */
    restore_user_settings_from_nvs();

    /* Push "not yet connected" defaults into every widget — overwrites the
     * demo text the .eez-project ships with (bracket_v3.nc, 12000 RPM, etc.)
     * so the user never sees stale mock data before the dispatcher delivers
     * real status. Must come AFTER ui_init() too. */
    app_state_paint_initial_state();

    xTaskCreatePinnedToCore(inactivity_blank_task, "blank", 3072,
                            NULL, 4, NULL, 0);
#else
    /* UI hasn't been exported from EEZ Studio yet — show a placeholder so the
     * device at least boots cleanly. Open the .eez-project and Build (Ctrl+B)
     * to populate main/ui/. */
    bsp_display_lock(0);
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label,
        "FluidCNC Pendant\n"
        "Run EEZ Studio Build to populate the UI.");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    bsp_display_unlock();
    ESP_LOGW(TAG, "ui.h not found — EEZ Studio export needed");
#endif

    /* --- Diagnostic: thumbstick wiring monitor (logs ADC + digital state). --- */
    thumbstick_monitor_start();

    /* --- Boot the state machine; this advances to WIFI_SETUP or WIFI_CONNECTING
     *     depending on whether NVS already has credentials. --- */
    ESP_ERROR_CHECK(app_state_init());

    /* --- LVGL tick driver runs in its own BSP task — nothing else for app_main. --- */
    ESP_LOGI(TAG, "boot complete");
}
