#pragma once

/*
 * FluidNC controller interface.
 *
 * Abstraction over UART / WebSocket / Telnet so the pendant talks to a real
 * FluidNC controller the same way regardless of physical link. The current
 * implementation ships a MOCK backend that simulates motion / spindle / job
 * progress so the UI can be exercised on the bench without a CNC connected.
 *
 * The real link layers (UART, WebSocket, Telnet) are stubbed out — to be filled
 * in once the on-screen UI flow is verified.
 *
 * Threading: all `fluidnc_*` calls are safe from any task. State callbacks fire
 * from the protocol task; consumers must bounce LVGL updates onto the LVGL
 * thread via bsp_display_lock().
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "esp_err.h"
#include "pendant_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FLUIDNC_STATE_DISCONNECTED = 0,
    FLUIDNC_STATE_CONNECTING,
    FLUIDNC_STATE_IDLE,
    FLUIDNC_STATE_RUN,
    FLUIDNC_STATE_HOLD,
    FLUIDNC_STATE_JOG,
    FLUIDNC_STATE_HOMING,
    FLUIDNC_STATE_ALARM,
} fluidnc_state_t;

typedef struct {
    float x, y, z;
} fluidnc_pos_t;

typedef struct {
    fluidnc_state_t state;
    fluidnc_pos_t   wpos;        /* work coordinates */
    fluidnc_pos_t   mpos;        /* machine coordinates */
    char            wcs[8];      /* "G54".."G59" */
    bool            units_inch;
    int             feed_ov;     /* % */
    int             rapid_ov;    /* % */
    int             spindle_ov;  /* % */
    bool            spindle_on;
    int             spindle_rpm;
    int             spindle_target;
    int             spindle_load;
    bool            flood;
    bool            mist;
    char            alarm_text[96];
    /* Current job */
    char            job_file[64];
    bool            job_running;
    float           job_progress_pct;
    int             job_line;
    int             job_total;
} fluidnc_status_t;

typedef void (*fluidnc_status_cb_t)(const fluidnc_status_t *st, void *user_ctx);

esp_err_t fluidnc_init(fluidnc_status_cb_t cb, void *user_ctx);

/* Connect via the configured transport in pendant_config. */
esp_err_t fluidnc_connect(void);
esp_err_t fluidnc_disconnect(void);

fluidnc_state_t       fluidnc_get_state(void);
const fluidnc_status_t *fluidnc_get_status(void);

/* --- High-level commands (translate to grbl-realtime / g-code under the hood). --- */
esp_err_t fluidnc_estop(void);
esp_err_t fluidnc_reset_alarm(void);
esp_err_t fluidnc_hold_resume(void);

/* axis: 0=X 1=Y 2=Z; dir: +1 or -1; step in mm (or inch, controller respects current G20/21). */
esp_err_t fluidnc_jog(int axis, int dir, float step_mm, float feed_mm_min);

/* Combined X+Y incremental jog. Used by the thumbstick: a small step is
 * emitted every sample period so the controller's planner has continuous
 * motion to chew on. feed_mm_min is the vector feedrate along the diagonal. */
esp_err_t fluidnc_jog_xy(float dx_mm, float dy_mm, float feed_mm_min);

/* Three-axis combined incremental jog. Any axis whose delta is ~0 is omitted
 * from the resulting $J= line, so single-axis moves still look clean on the
 * controller. feed_mm_min is the path/vector feedrate. */
esp_err_t fluidnc_jog_axes(float dx_mm, float dy_mm, float dz_mm, float feed_mm_min);

/* Realtime jog cancel (0x85). Stops the current $J= motion at the
 * configured deceleration without dropping into HOLD or ALARM. */
esp_err_t fluidnc_jog_cancel(void);

/* axis: 0=X 1=Y 2=Z; -1 = zero all. */
esp_err_t fluidnc_zero_axis(int axis);

esp_err_t fluidnc_home_all(void);
esp_err_t fluidnc_set_wcs(int wcs_index);            /* 0..5 = G54..G59 */
esp_err_t fluidnc_set_units(pendant_units_t u);

/* channel: 0=feed 1=rapid 2=spindle; delta: -10, +10, or 0 for 100%. */
esp_err_t fluidnc_adjust_override(int channel, int delta);

esp_err_t fluidnc_spindle_on(int rpm);
esp_err_t fluidnc_spindle_off(void);
esp_err_t fluidnc_spindle_target_delta(int delta_rpm);

esp_err_t fluidnc_flood(bool on);
esp_err_t fluidnc_mist(bool on);

/* Job control. file_name selected from the SD listing on the controller. */
esp_err_t fluidnc_job_start(const char *file_name);
esp_err_t fluidnc_job_stop(void);

/* Probe cycles. type 0=Z touch-off, 1=corner, 2=center, 3=tool length. */
esp_err_t fluidnc_probe(int type, float plate_thickness_mm, float feed_mm_min, float max_travel_mm);

/* Send a raw line of g-code (used by macros). */
esp_err_t fluidnc_send_line(const char *line);

/* --- SD file listing on the FluidNC controller. --- */
typedef struct {
    char     name[64];
    uint32_t size_bytes;
    char     date[20];
} fluidnc_file_t;

esp_err_t fluidnc_refresh_files(void);
size_t    fluidnc_get_files(fluidnc_file_t *out, size_t out_cap);

#ifdef __cplusplus
}
#endif
