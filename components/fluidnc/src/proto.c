#include "proto.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- helpers ---------- */

static const char *skip_ws(const char *p)
{
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;
    return p;
}

static bool starts_with(const char *line, const char *prefix)
{
    return strncmp(line, prefix, strlen(prefix)) == 0;
}

/* Parse N comma-separated floats from `s` into `out[N]`. Returns count parsed. */
static int parse_floats(const char *s, float *out, int n)
{
    int got = 0;
    while (got < n && *s) {
        char *end = NULL;
        float v = strtof(s, &end);
        if (end == s) break;
        out[got++] = v;
        s = end;
        if (*s == ',') s++;
        else break;
    }
    return got;
}

/* Parse N comma-separated integers from `s` into `out[N]`. Returns count. */
static int parse_ints(const char *s, int *out, int n)
{
    int got = 0;
    while (got < n && *s) {
        char *end = NULL;
        long v = strtol(s, &end, 10);
        if (end == s) break;
        out[got++] = (int)v;
        s = end;
        if (*s == ',') s++;
        else break;
    }
    return got;
}

/* Find the next '|' or '>' delimiter in a status report; returns pointer to it
 * (or to the terminating NUL if neither found). */
static const char *find_delim(const char *s)
{
    while (*s && *s != '|' && *s != '>') s++;
    return s;
}

/* ---------- classifier ---------- */

fluidnc_rx_kind_t fluidnc_proto_classify(const char *line)
{
    if (!line) return FLUIDNC_RX_UNKNOWN;
    line = skip_ws(line);
    if (*line == '\0') return FLUIDNC_RX_UNKNOWN;

    if (line[0] == '<') return FLUIDNC_RX_STATUS;

    if (line[0] == '[') {
        if (starts_with(line, "[MSG"))  return FLUIDNC_RX_MSG;
        if (starts_with(line, "[FILE")) return FLUIDNC_RX_FILE_ENTRY;
        if (starts_with(line, "[DIR"))  return FLUIDNC_RX_DIR_ENTRY;
        return FLUIDNC_RX_INFO;
    }

    if (strncmp(line, "ok", 2) == 0
        && (line[2] == '\0' || line[2] == '\r' || line[2] == '\n' || line[2] == ' '))
        return FLUIDNC_RX_OK;

    if (starts_with(line, "error:")) return FLUIDNC_RX_ERROR;
    if (starts_with(line, "ALARM:")) return FLUIDNC_RX_ALARM;

    if (starts_with(line, "Grbl ") || starts_with(line, "GrblHAL")
        || strstr(line, "FluidNC") != NULL)
        return FLUIDNC_RX_WELCOME;

    return FLUIDNC_RX_UNKNOWN;
}

int fluidnc_proto_get_error_code(const char *line)
{
    if (!line) return -1;
    const char *p = strstr(line, "error:");
    if (!p) return -1;
    return (int)strtol(p + 6, NULL, 10);
}

int fluidnc_proto_get_alarm_code(const char *line)
{
    if (!line) return -1;
    const char *p = strstr(line, "ALARM:");
    if (!p) return -1;
    return (int)strtol(p + 6, NULL, 10);
}

bool fluidnc_proto_get_msg(const char *line, char *out, size_t out_max)
{
    if (!line || !out || out_max == 0) return false;
    /* "[MSG:..." or "[MSG, ..." — find first ':' then copy until ']' */
    const char *p = strchr(line, ':');
    if (!p) return false;
    p++;
    while (*p == ' ') p++;
    size_t i = 0;
    while (*p && *p != ']' && i + 1 < out_max) out[i++] = *p++;
    out[i] = '\0';
    return true;
}

bool fluidnc_proto_parse_file_entry(const char *line, char *name, size_t name_max,
                                    uint32_t *size_bytes)
{
    if (!line) return false;
    /* "[FILE: /path/to/x.nc|123456]" — path begins after the colon, before '|';
     * size between '|' and ']'. */
    const char *colon = strchr(line, ':');
    if (!colon) return false;
    colon++;
    while (*colon == ' ') colon++;
    const char *bar = strchr(colon, '|');
    const char *end = strchr(colon, ']');
    if (!end) return false;
    const char *path_end = (bar && bar < end) ? bar : end;

    /* Copy basename only — strip leading directory components so the UI sees
     * "bracket_v3.nc" not "/spiffs/bracket_v3.nc". */
    const char *slash = path_end;
    while (slash > colon && slash[-1] != '/') slash--;
    size_t len = (size_t)(path_end - slash);
    if (name && name_max > 0) {
        if (len >= name_max) len = name_max - 1;
        memcpy(name, slash, len);
        name[len] = '\0';
    }

    if (size_bytes) {
        *size_bytes = (bar && bar < end) ? (uint32_t)strtoul(bar + 1, NULL, 10) : 0;
    }
    return true;
}

/* Case-insensitive find of `needle` in `hay`. */
static const char *ci_strstr(const char *hay, const char *needle)
{
    size_t nl = strlen(needle);
    if (nl == 0) return hay;
    for (; *hay; hay++) {
        size_t i = 0;
        while (i < nl && tolower((unsigned char)hay[i])
                          == tolower((unsigned char)needle[i])) i++;
        if (i == nl) return hay;
    }
    return NULL;
}

/* Parse "<number>[<KMG>B]" starting at p, returning bytes. Recognises
 * raw byte counts and the suffixes B / KB / MB / GB (case-insensitive,
 * with optional whitespace). Returns 0 if nothing parses. */
static uint64_t parse_size_token(const char *p)
{
    while (*p == ' ' || *p == ':') p++;
    char *end = NULL;
    double v = strtod(p, &end);
    if (end == p) return 0;
    while (*end == ' ') end++;
    /* Detect units; default = bytes. */
    uint64_t mult = 1;
    if      (tolower((unsigned char)end[0]) == 'g') mult = 1024ULL*1024ULL*1024ULL;
    else if (tolower((unsigned char)end[0]) == 'm') mult = 1024ULL*1024ULL;
    else if (tolower((unsigned char)end[0]) == 'k') mult = 1024ULL;
    return (uint64_t)(v * (double)mult);
}

bool fluidnc_proto_parse_storage_info(const char *line,
                                       uint64_t *total_bytes,
                                       uint64_t *used_bytes)
{
    if (!line) return false;
    bool got = false;
    const char *p;

    if ((p = ci_strstr(line, "total:")) != NULL) {
        uint64_t v = parse_size_token(p + 6);
        if (v && total_bytes) { *total_bytes = v; got = true; }
    }
    /* "size:" is FluidNC's alternate spelling for total */
    if (!got && (p = ci_strstr(line, "size:")) != NULL) {
        uint64_t v = parse_size_token(p + 5);
        if (v && total_bytes) { *total_bytes = v; got = true; }
    }
    if ((p = ci_strstr(line, "used:")) != NULL) {
        uint64_t v = parse_size_token(p + 5);
        if (used_bytes) { *used_bytes = v; got = true; }
    }
    return got;
}

/* ---------- status report parser ---------- */

/* Map a grbl state token (e.g. "Run", "Hold:1") to our enum + sub-state. */
static void map_state(const char *tok, size_t len, fluidnc_state_t *st, int *sub)
{
    *sub = 0;
    /* sub-state after ':' */
    const char *colon = memchr(tok, ':', len);
    size_t name_len = colon ? (size_t)(colon - tok) : len;
    if (colon) *sub = (int)strtol(colon + 1, NULL, 10);

    if      (name_len == 4 && strncmp(tok, "Idle", 4) == 0) *st = FLUIDNC_STATE_IDLE;
    else if (name_len == 3 && strncmp(tok, "Run", 3)  == 0) *st = FLUIDNC_STATE_RUN;
    else if (name_len == 4 && strncmp(tok, "Hold", 4) == 0) *st = FLUIDNC_STATE_HOLD;
    else if (name_len == 3 && strncmp(tok, "Jog", 3)  == 0) *st = FLUIDNC_STATE_JOG;
    else if (name_len == 4 && strncmp(tok, "Home", 4) == 0) *st = FLUIDNC_STATE_HOMING;
    else if (name_len == 5 && strncmp(tok, "Alarm", 5)== 0) *st = FLUIDNC_STATE_ALARM;
    else if (name_len == 4 && strncmp(tok, "Door", 4) == 0) *st = FLUIDNC_STATE_HOLD;   /* close enough for the pill */
    else if (name_len == 5 && strncmp(tok, "Check", 5)== 0) *st = FLUIDNC_STATE_IDLE;
    else if (name_len == 5 && strncmp(tok, "Sleep", 5)== 0) *st = FLUIDNC_STATE_IDLE;
    else                                                     *st = FLUIDNC_STATE_IDLE;
}

bool fluidnc_proto_parse_status(const char *line, fluidnc_status_report_t *out)
{
    if (!line || !out) return false;
    line = skip_ws(line);
    if (line[0] != '<') return false;
    memset(out, 0, sizeof(*out));

    const char *p = line + 1;            /* past '<' */

    /* First field: state token, up to first '|' or '>'. */
    const char *delim = find_delim(p);
    map_state(p, (size_t)(delim - p), &out->state, &out->sub_state);
    if (*delim != '|') return true;      /* no more fields */
    p = delim + 1;

    /* Remaining fields are key:value pairs separated by '|'. */
    while (*p && *p != '>') {
        delim = find_delim(p);
        size_t field_len = (size_t)(delim - p);

        /* Walk the field for "key:value" form. */
        const char *colon = memchr(p, ':', field_len);
        if (colon) {
            size_t key_len = (size_t)(colon - p);
            const char *val = colon + 1;

            if (key_len == 4 && strncmp(p, "MPos", 4) == 0) {
                float v[3] = {0};
                int n = parse_floats(val, v, 3);
                if (n == 3) { out->has_mpos = true; out->mx = v[0]; out->my = v[1]; out->mz = v[2]; }
            } else if (key_len == 4 && strncmp(p, "WPos", 4) == 0) {
                float v[3] = {0};
                int n = parse_floats(val, v, 3);
                if (n == 3) { out->has_wpos = true; out->wx = v[0]; out->wy = v[1]; out->wz = v[2]; }
            } else if (key_len == 3 && strncmp(p, "WCO", 3) == 0) {
                float v[3] = {0};
                int n = parse_floats(val, v, 3);
                if (n == 3) { out->has_wco = true; out->ox = v[0]; out->oy = v[1]; out->oz = v[2]; }
            } else if (key_len == 2 && strncmp(p, "FS", 2) == 0) {
                int v[2] = {0};
                int n = parse_ints(val, v, 2);
                if (n >= 1) { out->has_fs = true; out->feed = v[0]; out->rpm = n >= 2 ? v[1] : 0; }
            } else if (key_len == 1 && p[0] == 'F') {
                int v[1] = {0};
                if (parse_ints(val, v, 1) == 1) { out->has_fs = true; out->feed = v[0]; }
            } else if (key_len == 2 && strncmp(p, "Ov", 2) == 0) {
                int v[3] = {0};
                int n = parse_ints(val, v, 3);
                if (n == 3) {
                    out->has_ov = true;
                    out->ov_feed = v[0]; out->ov_rapid = v[1]; out->ov_spindle = v[2];
                }
            } else if (key_len == 1 && p[0] == 'A') {
                out->has_acc = true;
                for (const char *q = val; q < delim; q++) {
                    switch (*q) {
                    case 'S': out->sp_cw  = true; break;
                    case 'C': out->sp_ccw = true; break;
                    case 'F': out->flood  = true; break;
                    case 'M': out->mist   = true; break;
                    default: break;
                    }
                }
            } else if (key_len == 2 && strncmp(p, "Pn", 2) == 0) {
                out->has_pn = true;
                for (const char *q = val; q < delim; q++) {
                    switch (*q) {
                    case 'P': out->pn_probe = true; break;
                    case 'X': out->pn_lim_x = true; break;
                    case 'Y': out->pn_lim_y = true; break;
                    case 'Z': out->pn_lim_z = true; break;
                    default: break;
                    }
                }
            }
            /* unknown keys silently ignored */
        }

        if (*delim != '|') break;
        p = delim + 1;
    }
    return true;
}
