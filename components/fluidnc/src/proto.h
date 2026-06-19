#pragma once

/*
 * FluidNC / grbl line-level wire protocol parsers.
 *
 * Pure C string parsing — no IDF or LVGL dependencies — so this is unit-test
 * friendly and reusable across transports.
 *
 * Status report format (grbl realtime, returned in reply to "?"):
 *   <State|MPos:x,y,z|FS:feed,rpm|Ov:f,r,s|WCO:x,y,z|Pn:PSXYZ|A:SFM>
 *
 *   State    Idle | Run | Hold:N | Jog | Home | Alarm | Door:N | Check | Sleep
 *   MPos     machine coordinates (always reported)
 *   WPos     work coordinates (alternative to MPos; pendant prefers MPos+WCO)
 *   WCO      work coordinate offset; WPos = MPos - WCO
 *   FS       current feed rate and spindle rpm
 *   Ov       feed / rapid / spindle override percentages
 *   A        spindle / coolant accessory state: S=cw, C=ccw, F=flood, M=mist
 *   Pn       triggered pin flags: P=probe, X|Y|Z=limit, D=door, …
 *
 * File listing reply ($LocalFS/List or $SD/List):
 *   [FILE: /spiffs/<name>|<size_bytes>]
 *   [DIR:  /spiffs/<subdir>]
 *   ok
 *
 * Generic responses:
 *   ok
 *   error:<N>          (gcode parser error)
 *   ALARM:<N>          (motion fault)
 *   [MSG:<text>]
 *   [VER:<text>]       [OPT:<text>]   [GC:<gcode>]
 *
 * Welcome banner on connect:
 *   "Grbl 1.1f ['$' for help]" (legacy form)
 *   "[MSG:INFO: ...]" (FluidNC startup)
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "fluidnc.h"      /* fluidnc_state_t */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    fluidnc_state_t state;        /* always populated */
    int    sub_state;             /* 0 unless e.g. Hold:1 or Door:2 */

    bool   has_mpos; float mx, my, mz;
    bool   has_wpos; float wx, wy, wz;
    bool   has_wco;  float ox, oy, oz;

    bool   has_fs;   int feed, rpm;

    bool   has_ov;   int ov_feed, ov_rapid, ov_spindle;

    bool   has_acc;
    bool   sp_cw, sp_ccw;
    bool   flood, mist;

    bool   has_pn;
    bool   pn_probe;
    bool   pn_lim_x, pn_lim_y, pn_lim_z;
} fluidnc_status_report_t;

/* Parse a status report line (must begin with '<' and end with '>') into out.
 * Returns true on success. Leaves fields not present in the report at their
 * zero-initialized defaults. */
bool fluidnc_proto_parse_status(const char *line, fluidnc_status_report_t *out);

typedef enum {
    FLUIDNC_RX_UNKNOWN = 0,
    FLUIDNC_RX_STATUS,            /* "<...>" — call parse_status to decode */
    FLUIDNC_RX_OK,                /* "ok" */
    FLUIDNC_RX_ERROR,             /* "error:N" */
    FLUIDNC_RX_ALARM,             /* "ALARM:N" */
    FLUIDNC_RX_MSG,               /* "[MSG: ...]" */
    FLUIDNC_RX_INFO,              /* "[VER: ...]" / "[OPT: ...]" / "[GC: ...]" / "[<...>]" */
    FLUIDNC_RX_FILE_ENTRY,        /* "[FILE: /path|size]" */
    FLUIDNC_RX_DIR_ENTRY,         /* "[DIR: /path]" */
    FLUIDNC_RX_WELCOME,           /* "Grbl 1.1f [...]" or FluidNC banner */
} fluidnc_rx_kind_t;

/* Classify a single received line (no trailing newline). Whitespace-only
 * lines and empty strings return UNKNOWN. */
fluidnc_rx_kind_t fluidnc_proto_classify(const char *line);

/* Decoders for the kinds above. Return false if the line doesn't match the
 * expected shape (caller already classified, so this is mostly defensive). */
int  fluidnc_proto_get_error_code(const char *line);
int  fluidnc_proto_get_alarm_code(const char *line);
bool fluidnc_proto_get_msg(const char *line, char *out, size_t out_max);
bool fluidnc_proto_parse_file_entry(const char *line, char *name, size_t name_max,
                                    uint32_t *size_bytes);

#ifdef __cplusplus
}
#endif
