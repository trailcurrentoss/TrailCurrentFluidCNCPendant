/*
 * Battery monitor — see battery_monitor.h for the divider math.
 *
 * Sampling loop lives in its own FreeRTOS task. Each iteration:
 *   1. Averages 16 raw ADC counts on GPIO20.
 *   2. Converts to mV via the calibration handle (falls back to a raw-count
 *      ratio if calibration isn't available on this chip).
 *   3. Multiplies by 3 (the R92+R93 / R93 divider ratio) to recover V_bat.
 *   4. Maps V_bat -> percent state-of-charge via a Li-Ion 1S discharge LUT
 *      (piecewise linear from 3.00 V = 0% to 4.20 V = 100%).
 *   5. Detects charging from a rolling voltage trend PLUS the near-full
 *      threshold (V_bat > 4.15 V is either charge-in-progress or
 *      charge-complete-with-USB — both display as "charging").
 *   6. Pushes the new percent + charging flag into vars.c so the status bar
 *      updates on every page instance.
 *
 * If GPIO20 has no ADC channel on this chip (should never happen on ESP32-P4
 * but the code stays defensive), we log and exit so the rest of the firmware
 * still boots cleanly.
 */

#include "battery_monitor.h"

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdbool.h>
#include <stdint.h>

#if __has_include("ui/vars.h")
#include "ui/vars.h"
#define HAVE_UI_VARS 1
#else
#define HAVE_UI_VARS 0
#endif

static const char *TAG = "battery_monitor";

/* Wiring — the board's on-board divider is fixed to GPIO20. */
#define BAT_ADC_GPIO         20
#define DIVIDER_NUM          3      /* (R92 + R93) / R93 = 3 */
#define DIVIDER_DEN          1

/* Sampling cadence: one reading per second is plenty for a battery gauge,
 * and lets the trend detector see meaningful voltage change over its window. */
#define SAMPLE_PERIOD_MS     1000
#define AVG_SAMPLES          16

/* Charge-detection tuning. A 30-entry ring buffer at 1 Hz = 30 seconds of
 * history. Delta between "now" and "30 s ago" > 10 mV -> charging.
 * Delta < -5 mV -> not charging. In between, latch previous state. */
#define TREND_WINDOW         30
#define TREND_UP_MV          10
#define TREND_DOWN_MV        (-5)

/* Voltage thresholds (millivolts at the battery, after multiplying V_adc). */
#define V_BAT_MV_FULL        4200   /* charge complete */
#define V_BAT_MV_CHARGING    4150   /* USB present / charging-in-progress */
#define V_BAT_MV_EMPTY       3000   /* below this we clamp SOC to 0 */
#define V_BAT_MV_VISIBLE_MIN 2500   /* below this, no battery present */

/* Li-Ion 1S discharge curve — piecewise linear.
 * From typical 18650 / LiPo discharge data at moderate load. */
typedef struct { int mv; int pct; } soc_point_t;
static const soc_point_t s_soc_lut[] = {
    { 4200, 100 },
    { 4100,  90 },
    { 4000,  80 },
    { 3900,  65 },
    { 3800,  50 },
    { 3700,  35 },
    { 3600,  20 },
    { 3500,  10 },
    { 3300,   5 },
    { 3000,   0 },
};
#define SOC_LUT_LEN (sizeof(s_soc_lut) / sizeof(s_soc_lut[0]))

/* --- Charge detection state (all touched only from the sampling task). --- */
static int  s_trend[TREND_WINDOW];
static int  s_trend_head    = 0;
static int  s_trend_count   = 0;
static bool s_charging      = false;

static int mv_to_soc(int mv_bat)
{
    if (mv_bat >= s_soc_lut[0].mv)               return 100;
    if (mv_bat <= s_soc_lut[SOC_LUT_LEN - 1].mv) return 0;
    for (size_t i = 0; i + 1 < SOC_LUT_LEN; i++) {
        int hi_mv = s_soc_lut[i].mv,      lo_mv = s_soc_lut[i + 1].mv;
        int hi_pc = s_soc_lut[i].pct,     lo_pc = s_soc_lut[i + 1].pct;
        if (mv_bat <= hi_mv && mv_bat >= lo_mv) {
            int span_mv = hi_mv - lo_mv;
            int span_pc = hi_pc - lo_pc;
            return lo_pc + (mv_bat - lo_mv) * span_pc / span_mv;
        }
    }
    return 0;
}

static bool detect_charging(int mv_bat)
{
    /* Above the charge-complete / USB-present threshold: latch charging on
     * regardless of trend — this covers the "USB connected, battery topped
     * off, no current flowing but voltage stays high" case. */
    if (mv_bat >= V_BAT_MV_CHARGING) {
        s_charging = true;
        return true;
    }

    /* Compare current reading to oldest in the trend window. */
    if (s_trend_count >= TREND_WINDOW) {
        int oldest = s_trend[(s_trend_head) % TREND_WINDOW];   /* about to be overwritten */
        int delta  = mv_bat - oldest;
        if      (delta >= TREND_UP_MV)   s_charging = true;
        else if (delta <= TREND_DOWN_MV) s_charging = false;
        /* else: keep last state — hysteresis */
    }
    return s_charging;
}

static void push_trend_sample(int mv_bat)
{
    s_trend[s_trend_head] = mv_bat;
    s_trend_head = (s_trend_head + 1) % TREND_WINDOW;
    if (s_trend_count < TREND_WINDOW) s_trend_count++;
}

static void battery_task(void *arg)
{
    (void)arg;

    adc_unit_t    unit;
    adc_channel_t chan;
    esp_err_t err = adc_oneshot_io_to_channel(BAT_ADC_GPIO, &unit, &chan);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "GPIO%d has no ADC channel on this chip (%s) — battery monitor disabled",
                 BAT_ADC_GPIO, esp_err_to_name(err));
        vTaskDelete(NULL);
        return;
    }

    adc_oneshot_unit_handle_t handle;
    adc_oneshot_unit_init_cfg_t init_cfg = {
        .unit_id  = unit,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    if (adc_oneshot_new_unit(&init_cfg, &handle) != ESP_OK) {
        ESP_LOGE(TAG, "adc_oneshot_new_unit(unit=%d) failed", unit);
        vTaskDelete(NULL);
        return;
    }

    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten    = ADC_ATTEN_DB_12,   /* full 0–~3.1 V range at the ADC pin */
    };
    if (adc_oneshot_config_channel(handle, chan, &chan_cfg) != ESP_OK) {
        ESP_LOGE(TAG, "adc_oneshot_config_channel(GPIO%d) failed", BAT_ADC_GPIO);
        vTaskDelete(NULL);
        return;
    }

    /* Try to set up curve-fitting calibration. If the chip / eFuse doesn't
     * support it we still measure — just via a fixed 3.1 V / 4095 raw ratio,
     * which drifts a bit but is fine for a coarse SOC indicator. */
    adc_cali_handle_t cali = NULL;
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    adc_cali_curve_fitting_config_t cali_cfg = {
        .unit_id  = unit,
        .chan     = chan,
        .atten    = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    if (adc_cali_create_scheme_curve_fitting(&cali_cfg, &cali) != ESP_OK) {
        cali = NULL;
    }
#endif
    if (cali) {
        ESP_LOGI(TAG, "battery ADC ready on GPIO%d (unit=%d ch=%d, calibrated)",
                 BAT_ADC_GPIO, unit, chan);
    } else {
        ESP_LOGW(TAG, "battery ADC ready on GPIO%d (unit=%d ch=%d, UNCALIBRATED)",
                 BAT_ADC_GPIO, unit, chan);
    }

    int last_pct = -1;
    bool last_charging = false;
    bool last_visible  = false;

    for (;;) {
        int sum_raw = 0, n = 0;
        for (int i = 0; i < AVG_SAMPLES; i++) {
            int raw = 0;
            if (adc_oneshot_read(handle, chan, &raw) == ESP_OK) {
                sum_raw += raw;
                n++;
            }
            vTaskDelay(pdMS_TO_TICKS(2));
        }
        if (n == 0) {
            vTaskDelay(pdMS_TO_TICKS(SAMPLE_PERIOD_MS));
            continue;
        }
        int raw_avg = sum_raw / n;

        int mv_adc = 0;
        if (cali) {
            /* Calibrated path — mV at the ADC pin. */
            if (adc_cali_raw_to_voltage(cali, raw_avg, &mv_adc) != ESP_OK) {
                mv_adc = raw_avg * 3100 / 4095;
            }
        } else {
            mv_adc = raw_avg * 3100 / 4095;
        }

        int mv_bat = mv_adc * DIVIDER_NUM / DIVIDER_DEN;

        bool visible = mv_bat >= V_BAT_MV_VISIBLE_MIN;
        int  pct     = mv_to_soc(mv_bat);
        push_trend_sample(mv_bat);
        bool charging = detect_charging(mv_bat);

        /* Full-charge cosmetic: if the battery is at or above the charge-
         * complete voltage, report 100 % even if the LUT rounds down. */
        if (mv_bat >= V_BAT_MV_FULL) pct = 100;
        if (pct > 100) pct = 100;
        if (pct < 0)   pct = 0;

#if HAVE_UI_VARS
        if (visible != last_visible) {
            set_var_battery_visible(visible);
            last_visible = visible;
        }
        if (pct != last_pct) {
            set_var_battery_pct(pct);
            last_pct = pct;
        }
        if (charging != last_charging) {
            set_var_battery_charging(charging);
            last_charging = charging;
        }
#else
        (void)last_pct; (void)last_charging; (void)last_visible;
        (void)visible;  (void)pct;           (void)charging;
#endif

        ESP_LOGD(TAG, "raw=%d V_adc=%d mV V_bat=%d mV pct=%d chg=%d vis=%d",
                 raw_avg, mv_adc, mv_bat, pct, (int)charging, (int)visible);

        vTaskDelay(pdMS_TO_TICKS(SAMPLE_PERIOD_MS));
    }
}

void battery_monitor_start(void)
{
    xTaskCreatePinnedToCore(battery_task, "battery", 4096, NULL, 3, NULL, 0);
}
