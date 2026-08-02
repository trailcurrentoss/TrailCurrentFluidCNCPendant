#pragma once
/*
 * Over-the-air firmware update via a browser upload.
 *
 * ota_update_start() launches a small HTTP server on port 80:
 *   GET  /        — upload page (file picker + progress bar)
 *   POST /update  — receives the .bin, writes it to the inactive OTA slot,
 *                   sets it as boot partition, reboots on success.
 *
 * Requires the OTA partition table (ota_0/ota_1/otadata) — see
 * partitions.csv. The status callback fires from the HTTP server task;
 * implementations must take the display lock before touching LVGL.
 */

#include <stdbool.h>
#include "esp_err.h"

typedef void (*ota_status_cb_t)(const char *msg);

esp_err_t ota_update_start(ota_status_cb_t cb);
void      ota_update_stop(void);
bool      ota_update_active(void);
