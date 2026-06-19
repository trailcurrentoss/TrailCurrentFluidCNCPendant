#include "thumbstick_monitor.h"

#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_timer.h"

#include "fluidnc.h"
#include "ui/vars.h"

static const char *TAG = "thumbstick";

/* --- Jog control tuning ------------------------------------------------------
 *
 * Sampling at 10 Hz keeps the FluidNC planner buffer comfortably full (16-deep
 * by default) while still feeling responsive. Each $J= covers slightly more
 * than one sample period so the buffer never starves between sends.
 *
 * Curve is quadratic (x²) for "gentle progressive" — half-deflection only
 * produces 25 % of the max feed, and the snap to full speed happens in the
 * outer third of the travel.
 *
 * X/Y feed cap is the user's `default_jog_feed` slider, hard-capped at
 * 1500 mm/min so a sloppy bump on a slider set to 6000 can't fling the
 * spindle across the table.
 *
 * Z feed cap is HALF of the X/Y cap — Z mistakes break tools and cut into
 * spoilboards, and the spindle weight makes Z always feel "fast." Slower
 * default is safer; the user can re-bump it later if they want.
 *
 * Deadzone is generous because each stick rests around 1730–1760 raw on
 * either axis and we want zero motion when the user lets go.
 */
#define SAMPLE_PERIOD_MS    100
#define DEADZONE_FRAC       0.12f
#define MAX_FEED_XY_CEILING 1500.0f /* mm/min — slider clamp for X/Y */
#define MAX_FEED_Z_CEILING   750.0f /* mm/min — half of XY ceiling */
#define CALIBRATION_SAMPLES 24      /* averaged at startup */

/* --- $J= emit throttling ----------------------------------------------------
 *
 * Earlier versions emitted a fresh $J= every sample tick (10 Hz). That
 * floods FluidNC's planner and starves its main loop — the symptom is the
 * dashboard not updating while jogging because the `?` status reply is
 * stuck behind a queue of jog parses. FluidNC's documented best practice
 * for joystick control is *one* longer $J=, only resent when the user's
 * intent meaningfully changes, with 0x85 to interrupt on stops or
 * direction reversals.
 *
 * Tunings:
 *   JOG_SEGMENT_MS       — how much motion each $J= queues. 400 ms is
 *                          enough to coast across an intent-refresh gap
 *                          and short enough that a 0x85 cancel decelerates
 *                          quickly.
 *   INTENT_REFRESH_MS    — resend even when nothing changed, so the
 *                          planner never empties mid-deflection.
 *   INTENT_DIR_DEG       — direction-change angle that triggers a resend.
 *                          15° is well past stick noise, well under a real
 *                          directional intent change.
 *   INTENT_MAG_REL       — relative magnitude change that triggers a
 *                          resend (12 % = noticeable speed change).
 */
#define JOG_SEGMENT_MS      400
#define INTENT_REFRESH_MS   300
#define INTENT_DIR_DEG      15.0f
#define INTENT_MAG_REL      0.12f

/* Grace period before firing 0x85 jog-cancel after the stick falls into
 * the deadzone. Without this, a fast direction change (X+ → through center
 * → X-) causes a stutter because we cancel + re-engage on the single tick
 * the stick is centered. 200 ms of slack is short enough that a real
 * release still feels instant, and long enough to absorb a directional
 * swing across the rest position. */
#define CANCEL_GRACE_TICKS  2

/* Wiring (change here only).
 *
 * ADC2 channels broken out on the P1 header (GPIO49-52) hold the four
 * analog rails. Buttons go on P3 digital pins.
 *
 *   Stick 1 (XY jog):
 *     VRX1 → GPIO49  (ADC2_CH0)
 *     VRY1 → GPIO50  (ADC2_CH1)
 *     SW1  → GPIO2   (digital, pull-up)
 *
 *   Stick 2 (Z jog on Y axis; X reserved for a future function):
 *     VRX2 → GPIO51  (ADC2_CH2 — read but not used yet)
 *     VRY2 → GPIO52  (ADC2_CH3 → Z+/Z-)
 *     SW2  → GPIO3   (digital, pull-up)
 *
 * Why GPIO51 for SW1 was wrong: GPIO51 is an ADC pin. A button doesn't
 * need analog, but a second stick does — so SW1 moved to GPIO2 to free
 * GPIO51 for VRX2. */
#define PIN_VRX1 GPIO_NUM_49
#define PIN_VRY1 GPIO_NUM_50
#define PIN_SW1  GPIO_NUM_2
#define PIN_VRX2 GPIO_NUM_51
#define PIN_VRY2 GPIO_NUM_52
#define PIN_SW2  GPIO_NUM_3

static float s_center_x1 = 1750.0f, s_center_y1 = 1750.0f;
static float s_center_x2 = 1750.0f, s_center_y2 = 1750.0f;
static bool  s_jog_active = false;       /* true while we have $J=‘s in flight */
static int   s_idle_ticks = 0;           /* consecutive ticks below deadzone */
/* Last-emitted velocity vector and emit timestamp — used to decide whether
 * the next sample's intent is meaningfully different from what's already
 * queued at the controller. Zero magnitude = nothing in flight. */
static float    s_emit_vx = 0, s_emit_vy = 0, s_emit_vz = 0;
static int64_t  s_emit_us = 0;

/* The ESP-IDF oneshot driver allows ONE handle per ADC unit. Two channels on
 * the same unit (e.g. VRX=GPIO49 / VRY=GPIO50 both on ADC2) must share that
 * handle, otherwise the second adc_oneshot_new_unit() call returns
 * ESP_ERR_INVALID_STATE and reads silently fail. s_unit_handle[unit] keeps a
 * lazy per-unit cache. */
static adc_oneshot_unit_handle_t s_unit_handle[SOC_ADC_PERIPH_NUM] = {0};

typedef struct {
    adc_oneshot_unit_handle_t handle;
    adc_channel_t             chan;
    adc_unit_t                unit;
    bool                      ok;
} adc_chan_t;

static adc_chan_t s_x1, s_y1, s_x2, s_y2;

/* Bring up ADC oneshot on a digital pin. The unit handle is cached in
 * s_unit_handle so multiple channels on the same SAR unit share one handle —
 * the IDF driver returns ESP_ERR_INVALID_STATE if you try to create two. */
static bool try_init_adc(gpio_num_t gpio, adc_chan_t *out)
{
    esp_err_t err = adc_oneshot_io_to_channel(gpio, &out->unit, &out->chan);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "GPIO%d has no ADC channel on this chip (%s)",
                 (int)gpio, esp_err_to_name(err));
        return false;
    }

    if (s_unit_handle[out->unit] == NULL) {
        adc_oneshot_unit_init_cfg_t init_cfg = {
            .unit_id  = out->unit,
            .ulp_mode = ADC_ULP_MODE_DISABLE,
        };
        err = adc_oneshot_new_unit(&init_cfg, &s_unit_handle[out->unit]);
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "adc_oneshot_new_unit(unit=%d) for GPIO%d failed: %s",
                     (int)out->unit, (int)gpio, esp_err_to_name(err));
            return false;
        }
    }
    out->handle = s_unit_handle[out->unit];

    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten    = ADC_ATTEN_DB_12,   /* full 0–~3.1 V range */
    };
    err = adc_oneshot_config_channel(out->handle, out->chan, &chan_cfg);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "adc_oneshot_config_channel(GPIO%d, ch=%d) failed: %s",
                 (int)gpio, (int)out->chan, esp_err_to_name(err));
        return false;
    }

    out->ok = true;
    ESP_LOGI(TAG, "ADC ready on GPIO%d (unit=%d ch=%d)",
             (int)gpio, (int)out->unit, (int)out->chan);
    return true;
}

static int read_chan(const adc_chan_t *c)
{
    int raw = 0;
    if (c->ok) (void)adc_oneshot_read(c->handle, c->chan, &raw);
    return raw;
}

/* Configure a digital fallback for any pin. SW gets a pull-up because the
 * common Keyes-style thumbstick wires its push-switch from SW to GND when
 * pressed. VRX/VRY get NO pull because the thumbstick already drives those
 * pins with its 10 kΩ potentiometer dividers — adding the ~45 kΩ internal
 * pull would skew the reading. */
static void init_digital(gpio_num_t gpio, bool pullup)
{
    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << gpio,
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = pullup ? GPIO_PULLUP_ENABLE  : GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&cfg));
}

/* Average a handful of samples to learn each stick's at-rest raw value.
 * Sticks MUST be centered while this runs (true at boot, well before user
 * touch). */
static void calibrate_centers(void)
{
    long sx1 = 0, sy1 = 0, sx2 = 0, sy2 = 0;
    int  nx1 = 0, ny1 = 0, nx2 = 0, ny2 = 0;
    for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
        int r;
        if (s_x1.ok && adc_oneshot_read(s_x1.handle, s_x1.chan, &r) == ESP_OK) { sx1 += r; nx1++; }
        if (s_y1.ok && adc_oneshot_read(s_y1.handle, s_y1.chan, &r) == ESP_OK) { sy1 += r; ny1++; }
        if (s_x2.ok && adc_oneshot_read(s_x2.handle, s_x2.chan, &r) == ESP_OK) { sx2 += r; nx2++; }
        if (s_y2.ok && adc_oneshot_read(s_y2.handle, s_y2.chan, &r) == ESP_OK) { sy2 += r; ny2++; }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    if (nx1) s_center_x1 = (float)sx1 / nx1;
    if (ny1) s_center_y1 = (float)sy1 / ny1;
    if (nx2) s_center_x2 = (float)sx2 / nx2;
    if (ny2) s_center_y2 = (float)sy2 / ny2;
    ESP_LOGI(TAG, "centers: stick1 VRX=%.0f VRY=%.0f | stick2 VRX=%.0f VRY=%.0f",
             s_center_x1, s_center_y1, s_center_x2, s_center_y2);
}

/* Map a raw reading to deflection in [-1, +1] around the calibrated center.
 * Use the larger of (center) and (4095 - center) as the full-scale half so
 * a pot trimmed slightly off-center still gives a usable full swing. */
static float deflection(int raw, float center)
{
    float half = fmaxf(center, 4095.0f - center);
    float d = ((float)raw - center) / half;
    if (d >  1.0f) d =  1.0f;
    if (d < -1.0f) d = -1.0f;
    return d;
}

/* Quadratic gentle curve: sign-preserving x². Half-stick = 25 % of max,
 * three-quarter = ~56 %, full = 100 %. */
static float gentle_curve(float d)
{
    return (d >= 0.0f) ? d * d : -(d * d);
}

/* Active feed cap: user's slider, hard-clamped per axis-group. */
static float max_feed_xy(void)
{
    float f = (float)get_var_default_jog_feed();
    if (f < 60.0f)                  f = 60.0f;
    if (f > MAX_FEED_XY_CEILING)    f = MAX_FEED_XY_CEILING;
    return f;
}
static float max_feed_z(void)
{
    float f = (float)get_var_default_jog_feed() * 0.5f;
    if (f < 30.0f)                  f = 30.0f;
    if (f > MAX_FEED_Z_CEILING)     f = MAX_FEED_Z_CEILING;
    return f;
}

/* Apply deadzone-rescale + gentle curve to a 1-D deflection magnitude. */
static float curved_throttle(float mag)
{
    if (mag < DEADZONE_FRAC) return 0.0f;
    float scaled = (mag - DEADZONE_FRAC) / (1.0f - DEADZONE_FRAC);
    if (scaled > 1.0f) scaled = 1.0f;
    return gentle_curve(scaled);     /* 0..1 */
}

/* Has the user's intent changed enough since the last $J= to justify
 * cancelling the queued motion and queuing a fresh one? Returns true on
 * meaningful direction change, meaningful speed change, or refresh
 * timeout — false if the previous emit is still close enough that the
 * existing motion will track the stick correctly. */
static bool intent_changed(float vx, float vy, float vz)
{
    float old_mag = sqrtf(s_emit_vx * s_emit_vx +
                          s_emit_vy * s_emit_vy +
                          s_emit_vz * s_emit_vz);
    float new_mag = sqrtf(vx * vx + vy * vy + vz * vz);

    if (old_mag < 1e-3f) return true;   /* nothing in flight — must send */
    if (new_mag < 1e-3f) return true;   /* (shouldn't reach here, but safe) */

    /* Magnitude change */
    if (fabsf(new_mag - old_mag) / old_mag > INTENT_MAG_REL) return true;

    /* Direction change (cosine similarity) */
    float dot = (s_emit_vx * vx + s_emit_vy * vy + s_emit_vz * vz)
                / (old_mag * new_mag);
    float cos_thresh = cosf(INTENT_DIR_DEG * (float)M_PI / 180.0f);
    if (dot < cos_thresh) return true;

    /* Periodic refresh so the planner never runs dry mid-motion */
    int64_t age_ms = (esp_timer_get_time() - s_emit_us) / 1000;
    if (age_ms > INTENT_REFRESH_MS) return true;

    return false;
}

static void clear_emit_state(void)
{
    s_emit_vx = s_emit_vy = s_emit_vz = 0.0f;
    s_emit_us = 0;
}

static void jog_tick(int x1, int y1, int x2, int y2)
{
    fluidnc_state_t st = fluidnc_get_state();
    bool jog_ok = (st == FLUIDNC_STATE_IDLE) || (st == FLUIDNC_STATE_JOG);
    if (!jog_ok) {
        if (s_jog_active) {
            fluidnc_jog_cancel();
            s_jog_active = false;
            clear_emit_state();
        }
        s_idle_ticks = 0;
        return;
    }

    /* Stick 1 (X+Y plane). */
    float dx1 = deflection(x1, s_center_x1);
    float dy1 = deflection(y1, s_center_y1);
    float mag1 = sqrtf(dx1 * dx1 + dy1 * dy1);
    float t1   = curved_throttle(mag1);
    float vx = 0.0f, vy = 0.0f;
    if (t1 > 0.0f) {
        float feed1 = t1 * max_feed_xy();
        vx = (dx1 / mag1) * feed1;
        vy = (dy1 / mag1) * feed1;
    }

    /* Stick 2: Y axis only → Z jog. (VRX2 read but ignored for now.) */
    float dy2 = deflection(y2, s_center_y2);
    float mag2 = fabsf(dy2);
    float t2   = curved_throttle(mag2);
    float vz = 0.0f;
    if (t2 > 0.0f) {
        float feed2 = t2 * max_feed_z();
        vz = (dy2 >= 0.0f ? 1.0f : -1.0f) * feed2;
    }

    bool any_motion = (vx != 0.0f) || (vy != 0.0f) || (vz != 0.0f);

    if (!any_motion) {
        /* In the deadzone. Only fire 0x85 after a grace period so a fast
         * direction reversal through center doesn't cancel + re-engage. */
        if (s_jog_active && ++s_idle_ticks >= CANCEL_GRACE_TICKS) {
            fluidnc_jog_cancel();
            s_jog_active = false;
            clear_emit_state();
            s_idle_ticks = 0;
        }
        return;
    }
    s_idle_ticks = 0;

    /* The motion already queued at the controller is good enough — let it
     * keep running, don't touch the WS. This is the critical throttle
     * that keeps FluidNC's main loop free to send `?` status replies. */
    if (!intent_changed(vx, vy, vz)) return;

    /* Intent changed meaningfully (direction, speed, or refresh). Cancel
     * any in-flight motion so the controller decelerates from the OLD
     * motion before starting the new one — otherwise the controller
     * queues the new segment behind the old, and the stick feels laggy. */
    if (s_jog_active) {
        fluidnc_jog_cancel();
    }

    float vec_feed = sqrtf(vx * vx + vy * vy + vz * vz);
    if (vec_feed < 30.0f) return;

    float dt_min = (JOG_SEGMENT_MS / 1000.0f) / 60.0f;
    float step_x = vx * dt_min;
    float step_y = vy * dt_min;
    float step_z = vz * dt_min;

    fluidnc_jog_axes(step_x, step_y, step_z, vec_feed);
    s_emit_vx = vx;
    s_emit_vy = vy;
    s_emit_vz = vz;
    s_emit_us = esp_timer_get_time();
    s_jog_active = true;
}

static void monitor_task(void *arg)
{
    (void)arg;
    calibrate_centers();

    int log_div = 0;
    while (1) {
        int x1 = read_chan(&s_x1);
        int y1 = read_chan(&s_y1);
        int x2 = read_chan(&s_x2);
        int y2 = read_chan(&s_y2);
        int sw1 = gpio_get_level(PIN_SW1);
        int sw2 = gpio_get_level(PIN_SW2);

        jog_tick(x1, y1, x2, y2);

        if (++log_div >= (1000 / SAMPLE_PERIOD_MS)) {
            log_div = 0;
            ESP_LOGI(TAG,
                     "s1: X=%4d Y=%4d SW=%d | s2: X=%4d Y=%4d SW=%d | jog=%s",
                     x1, y1, sw1, x2, y2, sw2,
                     s_jog_active ? "active" : "idle");
        }

        vTaskDelay(pdMS_TO_TICKS(SAMPLE_PERIOD_MS));
    }
}

void thumbstick_monitor_start(void)
{
    ESP_LOGI(TAG,
             "starting thumbstick monitor (s1 VRX/VRY/SW=GPIO%d/%d/%d, "
             "s2 VRX/VRY/SW=GPIO%d/%d/%d)",
             (int)PIN_VRX1, (int)PIN_VRY1, (int)PIN_SW1,
             (int)PIN_VRX2, (int)PIN_VRY2, (int)PIN_SW2);

    try_init_adc(PIN_VRX1, &s_x1);
    try_init_adc(PIN_VRY1, &s_y1);
    try_init_adc(PIN_VRX2, &s_x2);
    try_init_adc(PIN_VRY2, &s_y2);

    /* SW gets a pull-up (active-low). Analog rails get no pull — the stick's
     * 10 kΩ divider already drives them, and the internal ~45 kΩ pull would
     * skew the reading. */
    init_digital(PIN_SW1, true);
    init_digital(PIN_SW2, true);

    xTaskCreatePinnedToCore(monitor_task, "thumbstick", 3584,
                            NULL, 4, NULL, 0);
}
