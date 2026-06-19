/*
 * FluidNC dispatcher — real backend.
 *
 * Owns:
 *   - The cached fluidnc_status_t (mirror of the controller's most recent
 *     status report). Updated by the rx-parser task.
 *   - The selected transport vtable (WebSocket / UART, picked at connect
 *     time from pendant_config_t.fluid_transport).
 *   - A small line buffer for reassembling incoming chunks into complete
 *     lines before classifying them.
 *   - Two FreeRTOS tasks:
 *       * status_poll_task — sends "?" at 4 Hz when the link is open.
 *       * rx_parse_task    — drains the line queue, calls proto.c.
 *
 * Threading:
 *   - Public fluidnc_* calls may come from any task (LVGL, app_state, …).
 *     Writes use the transport directly (transports serialise internally).
 *   - Status callback fires from rx_parse_task; consumers must bsp_display_lock
 *     for any LVGL access (already the convention in app_state.c / vars.c).
 *
 * Skipped when CONFIG_FLUIDNC_USE_MOCK=y — fluidnc_mock.c provides the
 * legacy mock backend in that configuration.
 */

#include "sdkconfig.h"

#if !CONFIG_FLUIDNC_USE_MOCK

#include "fluidnc.h"
#include "proto.h"
#include "transport.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

static const char *TAG = "fluidnc";

#define FLUIDNC_LINE_MAX        256
#define RX_QUEUE_DEPTH  16
#define POLL_PERIOD_MS  250
/* If no RX activity for this long while we're polling `?` at 4 Hz, the
 * link is half-broken (TCP open, controller stuck) — tear it down so the
 * transport's own auto-reconnect re-establishes a working link. 4 seconds
 * is well past worst-case round-trip on a healthy network (typical is
 * <20 ms) so we won't false-trigger during a momentary stall. */
#define RX_STALE_THRESHOLD_MS  4000

/* --- State ---------------------------------------------------------------- */

static fluidnc_status_t      s_status;
static fluidnc_status_cb_t   s_cb         = NULL;
static void                 *s_user_ctx   = NULL;
static SemaphoreHandle_t     s_state_mtx  = NULL;

static const fluid_transport_t *s_transport = NULL;
static volatile bool         s_link_open    = false;

/* Wall-clock ms timestamp of the most recent RX byte. Used by the poll
 * task to detect half-broken links (TCP open, controller silent) and
 * trigger an explicit reconnect. */
static volatile int64_t      s_last_rx_us   = 0;

static TaskHandle_t          s_poll_task = NULL;
static TaskHandle_t          s_rx_task   = NULL;
static volatile bool         s_run_tasks = false;

/* Inbound line queue — rx callback splits chunks at '\n' and pushes each
 * line (NUL-terminated) here for the parser task. */
typedef struct { char buf[FLUIDNC_LINE_MAX]; } rx_line_t;
static QueueHandle_t s_rx_q = NULL;

/* Inbound chunk reassembly buffer — bytes accumulate here until '\n' is
 * seen, then a rx_line_t is pushed. Owned by the dispatcher (writes come
 * from the transport rx task / event task). */
static char    s_partial[FLUIDNC_LINE_MAX];
static size_t  s_partial_len = 0;
static SemaphoreHandle_t s_partial_mtx = NULL;

/* File listing — collected between "$LocalFS/List" send and the following
 * "ok". The pendant only displays a few rows so this is small. */
#define FILES_MAX 24
static fluidnc_file_t s_files[FILES_MAX];
static size_t         s_files_n = 0;
static SemaphoreHandle_t s_files_mtx = NULL;
static volatile bool  s_collecting_files = false;

/* --- Helpers -------------------------------------------------------------- */

static void notify(void)
{
    if (s_cb) s_cb(&s_status, s_user_ctx);
}

static void status_lock(void)
{
    if (s_state_mtx) xSemaphoreTake(s_state_mtx, portMAX_DELAY);
}
static void status_unlock(void)
{
    if (s_state_mtx) xSemaphoreGive(s_state_mtx);
}

static esp_err_t write_line(const char *line)
{
    if (!s_transport || !s_transport->is_open()) {
        ESP_LOGW(TAG, "TX line FAIL (link not open): %s", line);
        return ESP_ERR_INVALID_STATE;
    }
    size_t n = strlen(line);
    esp_err_t err = s_transport->write(line, n);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "TX line OK: %.*s", (int)n, line);
    } else {
        ESP_LOGW(TAG, "TX line FAIL (%s): %.*s", esp_err_to_name(err), (int)n, line);
    }
    return err;
}

static esp_err_t write_rt(uint8_t byte)
{
    if (!s_transport || !s_transport->is_open()) {
        if (byte != '?') ESP_LOGW(TAG, "TX rt FAIL (link not open): 0x%02x", byte);
        return ESP_ERR_INVALID_STATE;
    }
    esp_err_t err = s_transport->write(&byte, 1);
    if (byte != '?') {
        if (err == ESP_OK) ESP_LOGI(TAG, "TX rt OK: 0x%02x", byte);
        else               ESP_LOGW(TAG, "TX rt FAIL (%s): 0x%02x", esp_err_to_name(err), byte);
    }
    return err;
}

/* Apply a parsed status report into s_status under the state mutex. */
static void apply_status_report(const fluidnc_status_report_t *r)
{
    status_lock();
    s_status.state = r->state;

    if (r->has_mpos) {
        s_status.mpos.x = r->mx; s_status.mpos.y = r->my; s_status.mpos.z = r->mz;
    }
    if (r->has_wpos) {
        s_status.wpos.x = r->wx; s_status.wpos.y = r->wy; s_status.wpos.z = r->wz;
    } else if (r->has_mpos && r->has_wco) {
        s_status.wpos.x = r->mx - r->ox;
        s_status.wpos.y = r->my - r->oy;
        s_status.wpos.z = r->mz - r->oz;
    }

    if (r->has_fs) {
        s_status.spindle_rpm = r->rpm;
    }
    if (r->has_ov) {
        s_status.feed_ov    = r->ov_feed;
        s_status.rapid_ov   = r->ov_rapid;
        s_status.spindle_ov = r->ov_spindle;
    }
    /* Accessory state derivation, with FS-rpm as fallback for spindle.
     *
     * grbl 1.1 spec: A field is OMITTED when all accessories are off, but
     * FluidNC ALSO rotates which optional fields appear in successive
     * status reports — so a status with FS:0,12000 may have A:S one tick
     * and omit A the next, even though the spindle is still spinning.
     * Trusting A-absence as "all off" made the Dashboard tile flicker
     * (and confused the previous toggle button) every other tick.
     *
     * The FS field IS always present in FluidNC's status reports, and its
     * second value is the current spindle RPM. So when A is missing we
     * fall back to "FS rpm > 0 => spindle on", which matches the
     * controller's actual state deterministically.
     *
     * Coolant (flood/mist) has no equivalent fallback field, so when A is
     * omitted we mirror the spec ("all off"); the Dashboard's coolant
     * tile will flicker if the user has flood/mist active, but that's
     * far less common than spindle use during testing. */
    if (r->has_acc) {
        s_status.spindle_on = r->sp_cw || r->sp_ccw;
        s_status.flood      = r->flood;
        s_status.mist       = r->mist;
    } else {
        s_status.spindle_on = r->has_fs && r->rpm > 0;
        s_status.flood      = false;
        s_status.mist       = false;
    }
    status_unlock();
    notify();
}

/* Dispatch a single classified line. */
static void handle_line(const char *line)
{
    fluidnc_rx_kind_t kind = fluidnc_proto_classify(line);
    switch (kind) {
    case FLUIDNC_RX_STATUS: {
        fluidnc_status_report_t r;
        if (fluidnc_proto_parse_status(line, &r)) apply_status_report(&r);
        break;
    }
    case FLUIDNC_RX_OK:
        if (s_collecting_files) {
            s_collecting_files = false;
            ESP_LOGI(TAG, "file listing complete (%u entries)", (unsigned)s_files_n);
            notify();
        }
        break;
    case FLUIDNC_RX_ERROR: {
        int code = fluidnc_proto_get_error_code(line);
        ESP_LOGW(TAG, "error:%d", code);
        if (s_collecting_files) s_collecting_files = false;
        break;
    }
    case FLUIDNC_RX_ALARM: {
        int code = fluidnc_proto_get_alarm_code(line);
        status_lock();
        s_status.state = FLUIDNC_STATE_ALARM;
        snprintf(s_status.alarm_text, sizeof(s_status.alarm_text),
                 "ALARM %d - see FluidNC docs", code);
        status_unlock();
        notify();
        ESP_LOGW(TAG, "ALARM:%d", code);
        break;
    }
    case FLUIDNC_RX_MSG: {
        char msg[96];
        if (fluidnc_proto_get_msg(line, msg, sizeof(msg))) {
            ESP_LOGI(TAG, "MSG: %s", msg);
        }
        break;
    }
    case FLUIDNC_RX_FILE_ENTRY: {
        if (s_collecting_files && s_files_n < FILES_MAX) {
            fluidnc_file_t *f = &s_files[s_files_n];
            memset(f, 0, sizeof(*f));
            if (fluidnc_proto_parse_file_entry(line, f->name, sizeof(f->name),
                                               &f->size_bytes)) {
                f->date[0] = '\0';      /* FluidNC doesn't report mtime */
                s_files_n++;
            }
        }
        break;
    }
    case FLUIDNC_RX_DIR_ENTRY:
        /* Subdirectories not exposed by the pendant UI yet — log and skip. */
        ESP_LOGD(TAG, "DIR: %s", line);
        break;
    case FLUIDNC_RX_WELCOME:
        ESP_LOGI(TAG, "controller: %s", line);
        /* Some welcome banners imply the link is alive even before a status
         * reply lands; treat as a hint that the controller is ready. */
        break;
    default:
        if (line[0]) ESP_LOGD(TAG, "RX: %s", line);
        break;
    }
}

static void rx_parse_task(void *arg)
{
    (void)arg;
    rx_line_t line;
    while (s_run_tasks) {
        if (xQueueReceive(s_rx_q, &line, pdMS_TO_TICKS(200)) == pdTRUE) {
            handle_line(line.buf);
        }
    }
    s_rx_task = NULL;
    vTaskDelete(NULL);
}

static void status_poll_task(void *arg)
{
    (void)arg;
    while (s_run_tasks) {
        if (s_link_open) {
            write_rt('?');

            /* Staleness watchdog: at 4 Hz polling, we should be getting at
             * least one status report back per ~250 ms. If we haven't seen
             * any RX activity for RX_STALE_THRESHOLD_MS while the link is
             * "open", the controller has gone unresponsive (its message
             * loop hung, or the WebSocket got into a half-broken state
             * that esp_websocket_client's ping/pong didn't catch). Close
             * the transport so the client's auto-reconnect re-establishes. */
            int64_t now_us  = esp_timer_get_time();
            int64_t age_ms  = (now_us - s_last_rx_us) / 1000;
            if (s_last_rx_us > 0 && age_ms > RX_STALE_THRESHOLD_MS) {
                ESP_LOGW(TAG, "RX stale for %lld ms — forcing transport reconnect",
                         age_ms);
                s_last_rx_us = now_us;          /* prevent immediate retrigger */
                if (s_transport) {
                    s_transport->close();
                    /* Small delay so the close completes before the
                     * transport's own auto-reconnect kicks in. */
                    vTaskDelay(pdMS_TO_TICKS(200));
                    s_transport->open(pendant_config_get());
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(POLL_PERIOD_MS));
    }
    s_poll_task = NULL;
    vTaskDelete(NULL);
}

/* --- Public: rx feed (called by transports) ------------------------------- */

void fluidnc_dispatcher_feed_rx(const char *data, size_t n)
{
    if (!s_partial_mtx || n == 0) return;
    /* Stamp any incoming activity — used by status_poll_task to detect a
     * half-broken link (TCP open, no responses). */
    s_last_rx_us = esp_timer_get_time();
    xSemaphoreTake(s_partial_mtx, portMAX_DELAY);
    for (size_t i = 0; i < n; i++) {
        char c = data[i];
        if (c == '\r') continue;
        if (c == '\n') {
            if (s_partial_len > 0) {
                rx_line_t line;
                size_t copy = s_partial_len < sizeof(line.buf) - 1
                                  ? s_partial_len : sizeof(line.buf) - 1;
                memcpy(line.buf, s_partial, copy);
                line.buf[copy] = '\0';
                /* Non-blocking; drop if queue is full. */
                if (s_rx_q) xQueueSend(s_rx_q, &line, 0);
            }
            s_partial_len = 0;
        } else if (s_partial_len + 1 < sizeof(s_partial)) {
            s_partial[s_partial_len++] = c;
        } else {
            /* Overflow — discard this line and resync at the next '\n'. */
            s_partial_len = 0;
        }
    }
    xSemaphoreGive(s_partial_mtx);
}

void fluidnc_dispatcher_set_link_open(bool open)
{
    s_link_open = open;
    if (open) {
        /* Probe the controller right away so the pendant has firmware info
         * before the user reaches the Pendant pages. */
        write_line("$I\n");
    } else {
        status_lock();
        s_status.state = FLUIDNC_STATE_DISCONNECTED;
        status_unlock();
        notify();
    }
}

/* --- Public API ----------------------------------------------------------- */

esp_err_t fluidnc_init(fluidnc_status_cb_t cb, void *user_ctx)
{
    memset(&s_status, 0, sizeof(s_status));
    s_status.state          = FLUIDNC_STATE_DISCONNECTED;
    strlcpy(s_status.wcs, "G54", sizeof(s_status.wcs));
    s_status.feed_ov        = 100;
    s_status.rapid_ov       = 100;
    s_status.spindle_ov     = 100;
    s_status.spindle_target = 12000;
    strlcpy(s_status.job_file, "(no job loaded)", sizeof(s_status.job_file));

    s_cb       = cb;
    s_user_ctx = user_ctx;

    if (!s_state_mtx)   s_state_mtx   = xSemaphoreCreateMutex();
    if (!s_partial_mtx) s_partial_mtx = xSemaphoreCreateMutex();
    if (!s_files_mtx)   s_files_mtx   = xSemaphoreCreateMutex();
    if (!s_rx_q)        s_rx_q        = xQueueCreate(RX_QUEUE_DEPTH, sizeof(rx_line_t));

    return ESP_OK;
}

esp_err_t fluidnc_connect(void)
{
    const pendant_config_t *cfg = pendant_config_get();

    switch (cfg->fluid_transport) {
    case PENDANT_TRANSPORT_WEBSOCKET: s_transport = &g_transport_ws;     break;
    case PENDANT_TRANSPORT_UART:      s_transport = &g_transport_uart;   break;
    case PENDANT_TRANSPORT_TELNET:    s_transport = &g_transport_telnet; break;
    default:
        return ESP_ERR_INVALID_ARG;
    }

    status_lock();
    s_status.state = FLUIDNC_STATE_CONNECTING;
    status_unlock();
    notify();

    if (!s_run_tasks) {
        s_run_tasks = true;
        xTaskCreatePinnedToCore(rx_parse_task,    "fluidnc_rx",  4096, NULL, 5, &s_rx_task,   0);
        xTaskCreatePinnedToCore(status_poll_task, "fluidnc_pol", 3072, NULL, 5, &s_poll_task, 0);
    }
    return s_transport->open(cfg);
}

esp_err_t fluidnc_disconnect(void)
{
    s_run_tasks = false;
    if (s_transport) {
        s_transport->close();
        s_transport = NULL;
    }
    status_lock();
    s_status.state = FLUIDNC_STATE_DISCONNECTED;
    status_unlock();
    notify();
    return ESP_OK;
}

fluidnc_state_t fluidnc_get_state(void) { return s_status.state; }
const fluidnc_status_t *fluidnc_get_status(void) { return &s_status; }

/* --- Realtime + line commands -------------------------------------------- */

esp_err_t fluidnc_estop(void)
{
    /* Soft reset — same byte FluidTouch / grbl-Web use; the controller
     * clears motion and enters Alarm state on its own. */
    status_lock();
    s_status.spindle_on  = false;
    s_status.spindle_rpm = 0;
    s_status.job_running = false;
    strlcpy(s_status.alarm_text, "EMERGENCY STOP - PRESS RESET TO CLEAR",
            sizeof(s_status.alarm_text));
    status_unlock();
    notify();
    return write_rt(0x18);
}

esp_err_t fluidnc_reset_alarm(void)
{
    status_lock();
    s_status.alarm_text[0] = '\0';
    status_unlock();
    notify();
    return write_line("$X\n");
}

esp_err_t fluidnc_hold_resume(void)
{
    /* Send the realtime byte unconditionally. Previously this only sent
     * when state was RUN (->!)  or HOLD (->~) and silently returned OK
     * otherwise, so the user saw nothing happen if they tapped HOLD while
     * idle. FluidNC ignores ! / ~ in states where they don't apply, so
     * always sending the toggle is safe and produces visible feedback in
     * the relevant states. Send '~' (resume) when in HOLD, else '!' (hold). */
    if (s_status.state == FLUIDNC_STATE_HOLD) return write_rt('~');
    return write_rt('!');
}

esp_err_t fluidnc_jog(int axis, int dir, float step_mm, float feed_mm_min)
{
    if (axis < 0 || axis > 2) return ESP_ERR_INVALID_ARG;
    if (s_status.state == FLUIDNC_STATE_ALARM ||
        s_status.state == FLUIDNC_STATE_HOMING) return ESP_OK;

    /* "$J=G91 G21 <axis><±step> F<feed>\n" — G91 incremental, G21 mm. The
     * controller's current G20/G21 mode is honoured if we omit the modal,
     * but specifying it here makes the math match the on-screen step. */
    char buf[64];
    const char letter = "XYZ"[axis];
    float d = dir * step_mm;
    int len = snprintf(buf, sizeof(buf), "$J=G91 G21 %c%.4f F%.1f\n",
                       letter, d, feed_mm_min);
    if (len < 0 || len >= (int)sizeof(buf)) return ESP_FAIL;
    return write_line(buf);
}

esp_err_t fluidnc_zero_axis(int axis)
{
    char buf[48];
    if (axis < 0)      snprintf(buf, sizeof(buf), "G10 L20 P0 X0 Y0 Z0\n");
    else if (axis == 0) snprintf(buf, sizeof(buf), "G10 L20 P0 X0\n");
    else if (axis == 1) snprintf(buf, sizeof(buf), "G10 L20 P0 Y0\n");
    else if (axis == 2) snprintf(buf, sizeof(buf), "G10 L20 P0 Z0\n");
    else return ESP_ERR_INVALID_ARG;
    return write_line(buf);
}

esp_err_t fluidnc_home_all(void)             { return write_line("$H\n"); }

esp_err_t fluidnc_set_wcs(int wcs_index)
{
    if (wcs_index < 0 || wcs_index > 5) return ESP_ERR_INVALID_ARG;
    char buf[8];
    snprintf(buf, sizeof(buf), "G%02d\n", 54 + wcs_index);
    snprintf(s_status.wcs, sizeof(s_status.wcs), "G%02d", 54 + wcs_index);
    notify();
    return write_line(buf);
}

esp_err_t fluidnc_set_units(pendant_units_t u)
{
    s_status.units_inch = (u == PENDANT_UNITS_INCH);
    notify();
    return write_line(u == PENDANT_UNITS_INCH ? "G20\n" : "G21\n");
}

esp_err_t fluidnc_adjust_override(int channel, int delta)
{
    /* grbl realtime override bytes.
     *   feed:    0x90 reset100, 0x91 +10, 0x92 -10, 0x93 +1, 0x94 -1
     *   rapid:   0x95 100%,    0x96 50%,           0x97 25%
     *   spindle: 0x99 reset100, 0x9A +10, 0x9B -10, 0x9C +1, 0x9D -1
     *
     * The UI only emits delta = ±10 or 0 today. Rapid only has 3 discrete
     * settings, so ±10 there maps to "step toward the next preset". */
    if (channel == 0) {       /* feed */
        if (delta == 0)    return write_rt(0x90);
        if (delta >= 10)   return write_rt(0x91);
        if (delta <= -10)  return write_rt(0x92);
        return delta > 0 ? write_rt(0x93) : write_rt(0x94);
    }
    if (channel == 1) {       /* rapid — cycle: 25 -> 50 -> 100 */
        int cur = s_status.rapid_ov;
        if (delta == 0)   return write_rt(0x95);
        if (delta < 0)    return write_rt(cur > 50 ? 0x96 : 0x97);   /* down */
        return                    write_rt(cur < 50 ? 0x96 : 0x95);  /* up   */
    }
    if (channel == 2) {       /* spindle */
        if (delta == 0)   return write_rt(0x99);
        if (delta >= 10)  return write_rt(0x9A);
        if (delta <= -10) return write_rt(0x9B);
        return delta > 0 ? write_rt(0x9C) : write_rt(0x9D);
    }
    return ESP_ERR_INVALID_ARG;
}

esp_err_t fluidnc_spindle_on(int rpm)
{
    if (rpm > 0) s_status.spindle_target = rpm;
    char buf[24];
    /* Use the two-digit M-code form (M03 not M3) — both are valid g-code
     * per ISO 6983, but the leading-zero form is what FluidNC's
     * documentation + web UI examples consistently use. Matching that
     * avoids any parser surprises. */
    snprintf(buf, sizeof(buf), "M03 S%d\n", rpm > 0 ? rpm : s_status.spindle_target);
    return write_line(buf);
}

esp_err_t fluidnc_spindle_off(void)            { return write_line("M05\n"); }

esp_err_t fluidnc_spindle_target_delta(int delta_rpm)
{
    int v = s_status.spindle_target + delta_rpm;
    if (v < 0)     v = 0;
    if (v > 24000) v = 24000;
    s_status.spindle_target = v;
    notify();
    /* If currently spinning, re-issue M3 with the new target so the
     * controller updates without waiting for the next on/off cycle. */
    if (s_status.spindle_on) {
        char buf[24];
        snprintf(buf, sizeof(buf), "M3 S%d\n", v);
        return write_line(buf);
    }
    return ESP_OK;
}

esp_err_t fluidnc_flood(bool on) { return write_line(on ? "M08\n" : "M09\n"); }
esp_err_t fluidnc_mist (bool on)
{
    /* M09 turns BOTH coolant outputs off. To toggle mist independently from
     * flood we re-issue the flood state after M09 + M07. */
    if (on) return write_line("M07\n");
    bool flood = s_status.flood;
    esp_err_t err = write_line("M09\n");
    if (err == ESP_OK && flood) err = write_line("M08\n");
    return err;
}

esp_err_t fluidnc_job_start(const char *file_name)
{
    if (s_status.state == FLUIDNC_STATE_ALARM) return ESP_OK;
    char buf[96];
    if (file_name && file_name[0]) {
        strlcpy(s_status.job_file, file_name, sizeof(s_status.job_file));
        /* Try LocalFS first (FluidNC 3.x default). The controller will
         * respond with error:8 if the path is wrong, which we surface as
         * an alarm-banner on the next status update. */
        snprintf(buf, sizeof(buf), "$LocalFS/Run=/spiffs/%s\n", file_name);
    } else if (s_status.job_file[0] && s_status.job_file[0] != '-') {
        snprintf(buf, sizeof(buf), "$LocalFS/Run=/spiffs/%s\n", s_status.job_file);
    } else {
        return ESP_ERR_INVALID_ARG;
    }
    s_status.job_running      = true;
    s_status.job_progress_pct = 0.0f;
    s_status.job_line         = 0;
    notify();
    return write_line(buf);
}

esp_err_t fluidnc_job_stop(void)
{
    s_status.job_running = false;
    notify();
    /* Soft-reset stops the running program; $X clears the resulting alarm
     * so the user lands back on Idle without needing a second tap. */
    esp_err_t e = write_rt(0x18);
    if (e == ESP_OK) e = write_line("$X\n");
    return e;
}

esp_err_t fluidnc_probe(int type, float plate_thickness_mm, float feed_mm_min, float max_travel_mm)
{
    /* Type 0 = Z touch-off: probe down, set Z to plate thickness, lift.
     * Types 1/2/3 (corner / center / tool) are full macros and will land in
     * Piece D's "real macro library" once the cycle UI is fleshed out. */
    char buf[160];
    int len = 0;
    switch (type) {
    case 0: {
        /* "G38.2 Z-<travel> F<feed>" → "G10 L20 P0 Z<plate>" → "G0 Z<plate+5>" */
        char a[64], b[48], c[48];
        snprintf(a, sizeof(a), "G38.2 Z-%.3f F%.1f\n", max_travel_mm, feed_mm_min);
        snprintf(b, sizeof(b), "G10 L20 P0 Z%.3f\n",   plate_thickness_mm);
        snprintf(c, sizeof(c), "G0 Z%.3f\n",           plate_thickness_mm + 5.0f);
        len = snprintf(buf, sizeof(buf), "%s%s%s", a, b, c);
        break;
    }
    default:
        ESP_LOGW(TAG, "probe type %d not implemented", type);
        return ESP_ERR_NOT_SUPPORTED;
    }
    if (len <= 0 || len >= (int)sizeof(buf)) return ESP_FAIL;
    return write_line(buf);
}

esp_err_t fluidnc_send_line(const char *line)
{
    if (!line) return ESP_ERR_INVALID_ARG;
    /* If caller forgot the newline, append one. */
    size_t n = strlen(line);
    bool nl  = n > 0 && line[n-1] == '\n';
    if (nl) return write_line(line);
    char buf[160];
    if (n + 2 > sizeof(buf)) return ESP_ERR_INVALID_SIZE;
    memcpy(buf, line, n);
    buf[n]   = '\n';
    buf[n+1] = '\0';
    return write_line(buf);
}

/* --- File listing --------------------------------------------------------- */

esp_err_t fluidnc_refresh_files(void)
{
    xSemaphoreTake(s_files_mtx, portMAX_DELAY);
    s_files_n = 0;
    xSemaphoreGive(s_files_mtx);
    s_collecting_files = true;
    return write_line("$LocalFS/List\n");
}

size_t fluidnc_get_files(fluidnc_file_t *out, size_t out_cap)
{
    if (!out || out_cap == 0) return 0;
    /* Callable before fluidnc_init() — e.g. from app_state_paint_initial_state()
     * which runs right after ui_init() and wants to repaint Files with whatever
     * the controller has cached (always zero at this point). Skip the lock
     * dance if the dispatcher hasn't created its mutexes yet. */
    if (!s_files_mtx) return 0;
    xSemaphoreTake(s_files_mtx, portMAX_DELAY);
    size_t n = s_files_n;
    if (n > out_cap) n = out_cap;
    memcpy(out, s_files, n * sizeof(s_files[0]));
    xSemaphoreGive(s_files_mtx);
    return n;
}

#endif /* !CONFIG_FLUIDNC_USE_MOCK */
