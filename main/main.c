#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
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

#if __has_include("ui/ui.h")
#  include "ui/ui.h"
#  define HAVE_UI 1
#else
#  define HAVE_UI 0
#endif

static const char *TAG = "fluidcnc-pendant";

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

    /* --- Boot the state machine; this advances to WIFI_SETUP or WIFI_CONNECTING
     *     depending on whether NVS already has credentials. --- */
    ESP_ERROR_CHECK(app_state_init());

    /* --- LVGL tick driver runs in its own BSP task — nothing else for app_main. --- */
    ESP_LOGI(TAG, "boot complete");
}
