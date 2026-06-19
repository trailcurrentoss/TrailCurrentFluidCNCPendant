#include "sdkconfig.h"

#if CONFIG_FLUIDNC_USE_MOCK

#include "fluidnc.h"

#include <math.h>
#include <string.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*
 * Mock implementation: drives a simulated machine state so the UI can be
 * exercised without a real FluidNC controller. Selected at build time via
 * `idf.py menuconfig` → "TrailCurrent FluidNC" → "Use mock backend".
 *
 * The real backend (src/fluidnc.c + src/transport_*.c + src/proto.c)
 * exposes the same public API; this file is excluded from the build when
 * CONFIG_FLUIDNC_USE_MOCK is unset.
 */

static const char *TAG = "fluidnc";

static fluidnc_status_t      s_status;
static fluidnc_status_cb_t   s_cb        = NULL;
static void                 *s_user_ctx  = NULL;
static TaskHandle_t          s_task      = NULL;
static volatile bool         s_run_task  = false;

static const fluidnc_file_t s_files[] = {
    { "bracket_v3.nc",         184  * 1024, "Today 09:42" },
    { "spoilboard_surface.gcode",  22 * 1024, "Yesterday" },
    { "nameplate_oak.nc",      512  * 1024, "Jun 09" },
    { "pcb_iso_mill.nc",       1200 * 1024, "Jun 07" },
    { "enclosure_lid.nc",       96  * 1024, "Jun 02" },
    { "circle_test.nc",          4  * 1024, "May 28" },
};

static void notify(void)
{
    if (s_cb) s_cb(&s_status, s_user_ctx);
}

static void protocol_task(void *arg)
{
    (void)arg;
    int64_t start_us = esp_timer_get_time();
    while (s_run_task) {
        /* Spindle ramp toward target when on. */
        int tgt = s_status.spindle_on
                      ? (s_status.spindle_target * s_status.spindle_ov) / 100
                      : 0;
        if (s_status.spindle_rpm < tgt) {
            int n = s_status.spindle_rpm + 900;
            s_status.spindle_rpm = n > tgt ? tgt : n;
        } else if (s_status.spindle_rpm > tgt) {
            int n = s_status.spindle_rpm - 1400;
            s_status.spindle_rpm = n < tgt ? tgt : n;
        }
        s_status.spindle_load = s_status.spindle_on
                                    ? 28 + (s_status.spindle_rpm * 44) / 24000
                                    : 0;

        /* Simulated motion when a job is running. */
        if (s_status.state == FLUIDNC_STATE_RUN && s_status.job_running) {
            float dt = (esp_timer_get_time() - start_us) / 1e6f;
            s_status.wpos.x = 60.0f + sinf(dt) * 52.0f;
            s_status.wpos.y = 42.0f + cosf(dt * 0.8f) * 30.0f;
            s_status.wpos.z = -1.5f - (sinf(dt * 2.3f) + 1.0f) * 1.4f;
            s_status.job_progress_pct += 0.16f * s_status.feed_ov / 100.0f;
            if (s_status.job_progress_pct >= 100.0f) {
                s_status.job_progress_pct = 100.0f;
                s_status.job_running      = false;
                s_status.state            = FLUIDNC_STATE_IDLE;
                s_status.spindle_on       = false;
            }
            s_status.job_line = (int)(s_status.job_progress_pct * s_status.job_total / 100.0f);
        }
        notify();
        vTaskDelay(pdMS_TO_TICKS(120));
    }
    s_task = NULL;
    vTaskDelete(NULL);
}

esp_err_t fluidnc_init(fluidnc_status_cb_t cb, void *user_ctx)
{
    memset(&s_status, 0, sizeof(s_status));
    s_status.state          = FLUIDNC_STATE_DISCONNECTED;
    strlcpy(s_status.wcs, "G54", sizeof(s_status.wcs));
    s_status.feed_ov        = 100;
    s_status.rapid_ov       = 100;
    s_status.spindle_ov     = 100;
    s_status.spindle_target = 12000;
    s_status.job_total      = 4820;
    strlcpy(s_status.job_file, "—", sizeof(s_status.job_file));

    s_cb       = cb;
    s_user_ctx = user_ctx;
    return ESP_OK;
}

esp_err_t fluidnc_connect(void)
{
    if (s_run_task) return ESP_OK;
    const pendant_config_t *cfg = pendant_config_get();
    const char *tport = "UART";
    switch (cfg->fluid_transport) {
        case PENDANT_TRANSPORT_WEBSOCKET: tport = "WebSocket"; break;
        case PENDANT_TRANSPORT_TELNET:    tport = "Telnet";    break;
        default: break;
    }
    ESP_LOGI(TAG, "connecting via %s host=%s (MOCK)", tport,
             cfg->fluid_host[0] ? cfg->fluid_host : "(local)");

    s_status.state = FLUIDNC_STATE_CONNECTING;
    notify();

    /* Mock: pretend the controller is ready almost immediately. */
    s_status.state = FLUIDNC_STATE_IDLE;
    s_run_task     = true;
    xTaskCreate(protocol_task, "fluidnc", 4096, NULL, 5, &s_task);
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_disconnect(void)
{
    s_run_task     = false;
    s_status.state = FLUIDNC_STATE_DISCONNECTED;
    notify();
    return ESP_OK;
}

fluidnc_state_t fluidnc_get_state(void) { return s_status.state; }
const fluidnc_status_t *fluidnc_get_status(void) { return &s_status; }

esp_err_t fluidnc_estop(void)
{
    s_status.state         = FLUIDNC_STATE_ALARM;
    s_status.spindle_on    = false;
    s_status.spindle_rpm   = 0;
    s_status.job_running   = false;
    strlcpy(s_status.alarm_text,
            "EMERGENCY STOP — PRESS RESET TO CLEAR",
            sizeof(s_status.alarm_text));
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_reset_alarm(void)
{
    s_status.state           = FLUIDNC_STATE_IDLE;
    s_status.alarm_text[0]   = '\0';
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_hold_resume(void)
{
    if (s_status.state == FLUIDNC_STATE_RUN) {
        s_status.state       = FLUIDNC_STATE_HOLD;
        s_status.job_running = false;
    } else if (s_status.state == FLUIDNC_STATE_HOLD) {
        s_status.state       = FLUIDNC_STATE_RUN;
        s_status.job_running = true;
    }
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_jog(int axis, int dir, float step_mm, float feed_mm_min)
{
    (void)feed_mm_min;
    if (s_status.state == FLUIDNC_STATE_ALARM ||
        s_status.state == FLUIDNC_STATE_RUN   ||
        s_status.state == FLUIDNC_STATE_HOMING) return ESP_OK;
    float d = dir * step_mm;
    if      (axis == 0) s_status.wpos.x += d;
    else if (axis == 1) s_status.wpos.y += d;
    else if (axis == 2) s_status.wpos.z += d;
    s_status.state = FLUIDNC_STATE_JOG;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_jog_xy(float dx_mm, float dy_mm, float feed_mm_min)
{
    return fluidnc_jog_axes(dx_mm, dy_mm, 0.0f, feed_mm_min);
}

esp_err_t fluidnc_jog_axes(float dx_mm, float dy_mm, float dz_mm,
                           float feed_mm_min)
{
    (void)feed_mm_min;
    if (s_status.state == FLUIDNC_STATE_ALARM ||
        s_status.state == FLUIDNC_STATE_RUN   ||
        s_status.state == FLUIDNC_STATE_HOMING) return ESP_OK;
    s_status.wpos.x += dx_mm;
    s_status.wpos.y += dy_mm;
    s_status.wpos.z += dz_mm;
    s_status.state = FLUIDNC_STATE_JOG;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_jog_cancel(void)
{
    if (s_status.state == FLUIDNC_STATE_JOG) {
        s_status.state = FLUIDNC_STATE_IDLE;
        notify();
    }
    return ESP_OK;
}

esp_err_t fluidnc_zero_axis(int axis)
{
    if (s_status.state == FLUIDNC_STATE_RUN) return ESP_OK;
    if (axis < 0) {
        s_status.wpos = (fluidnc_pos_t){0, 0, 0};
    } else if (axis == 0) s_status.wpos.x = 0;
    else if   (axis == 1) s_status.wpos.y = 0;
    else if   (axis == 2) s_status.wpos.z = 0;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_home_all(void)
{
    if (s_status.state == FLUIDNC_STATE_ALARM || s_status.state == FLUIDNC_STATE_RUN) return ESP_OK;
    s_status.state = FLUIDNC_STATE_HOMING;
    notify();
    /* Mock: snap to zero after a beat. */
    vTaskDelay(pdMS_TO_TICKS(1200));
    s_status.wpos  = (fluidnc_pos_t){0, 0, 0};
    s_status.state = FLUIDNC_STATE_IDLE;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_set_wcs(int wcs_index)
{
    if (wcs_index < 0 || wcs_index > 5) return ESP_ERR_INVALID_ARG;
    snprintf(s_status.wcs, sizeof(s_status.wcs), "G%02d", 54 + wcs_index);
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_set_units(pendant_units_t u)
{
    s_status.units_inch = (u == PENDANT_UNITS_INCH);
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_adjust_override(int channel, int delta)
{
    int *p = NULL;
    if      (channel == 0) p = &s_status.feed_ov;
    else if (channel == 1) p = &s_status.rapid_ov;
    else if (channel == 2) p = &s_status.spindle_ov;
    else return ESP_ERR_INVALID_ARG;
    int v = (delta == 0) ? 100 : (*p + delta);
    if (v < 10)  v = 10;
    if (v > 200) v = 200;
    *p = v;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_spindle_on(int rpm)
{
    if (s_status.state == FLUIDNC_STATE_ALARM) return ESP_OK;
    s_status.spindle_on     = true;
    if (rpm > 0) s_status.spindle_target = rpm;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_spindle_off(void)
{
    s_status.spindle_on = false;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_spindle_target_delta(int delta_rpm)
{
    int v = s_status.spindle_target + delta_rpm;
    if (v < 0)     v = 0;
    if (v > 24000) v = 24000;
    s_status.spindle_target = v;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_flood(bool on) { s_status.flood = on; notify(); return ESP_OK; }
esp_err_t fluidnc_mist (bool on) { s_status.mist  = on; notify(); return ESP_OK; }

esp_err_t fluidnc_job_start(const char *file_name)
{
    if (s_status.state == FLUIDNC_STATE_ALARM) return ESP_OK;
    if (file_name) strlcpy(s_status.job_file, file_name, sizeof(s_status.job_file));
    s_status.job_running      = true;
    s_status.job_progress_pct = 0;
    s_status.job_line         = 0;
    s_status.state            = FLUIDNC_STATE_RUN;
    s_status.spindle_on       = true;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_job_stop(void)
{
    s_status.job_running      = false;
    s_status.job_progress_pct = 0;
    s_status.state            = FLUIDNC_STATE_IDLE;
    s_status.spindle_on       = false;
    notify();
    return ESP_OK;
}

esp_err_t fluidnc_probe(int type, float plate_thickness_mm, float feed_mm_min, float max_travel_mm)
{
    (void)plate_thickness_mm; (void)feed_mm_min; (void)max_travel_mm;
    ESP_LOGI(TAG, "probe (mock) type=%d", type);
    return ESP_OK;
}

esp_err_t fluidnc_send_line(const char *line)
{
    ESP_LOGI(TAG, "send_line (mock): %s", line ? line : "(null)");
    return ESP_OK;
}

esp_err_t fluidnc_refresh_files(void)   { return ESP_OK; }
bool fluidnc_get_storage_info(uint64_t *total_bytes, uint64_t *used_bytes)
{
    /* Mock: pretend a 4 GB card with the demo gcode taking 12 MB. */
    if (total_bytes) *total_bytes = 4ULL * 1024ULL * 1024ULL * 1024ULL;
    if (used_bytes)  *used_bytes  = 12ULL * 1024ULL * 1024ULL;
    return true;
}
uint32_t fluidnc_get_files_seq(void) { return 0; }
int fluidnc_jog_outstanding(void) { return 0; }
size_t fluidnc_get_files(fluidnc_file_t *out, size_t out_cap)
{
    if (!out || out_cap == 0) return 0;
    size_t n = sizeof(s_files) / sizeof(s_files[0]);
    if (n > out_cap) n = out_cap;
    memcpy(out, s_files, n * sizeof(s_files[0]));
    return n;
}

#endif /* CONFIG_FLUIDNC_USE_MOCK */
