/*
 * Browser-push OTA — see ota_update.h.
 *
 * Design notes:
 *  - Push model, no external server: the laptop (or phone) opens
 *    http://<pendant-ip>/ and uploads the .bin from the build directory.
 *  - The upload handler streams straight into esp_ota_write() in 4 KB
 *    chunks; nothing is buffered whole (a 1.7 MB image would not fit in
 *    internal RAM anyway).
 *  - Progress is reported through the status callback roughly every 5 %
 *    so the pendant's own screen shows what's happening.
 *  - On success: mark the new slot bootable, report, reboot after a short
 *    delay so the HTTP response reaches the browser first.
 */

#include "ota_update.h"

#include <string.h>
#include <stdio.h>

#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "ota_update";

static httpd_handle_t  s_server = NULL;
static ota_status_cb_t s_cb     = NULL;

static void report(const char *msg)
{
    ESP_LOGI(TAG, "%s", msg);
    if (s_cb) s_cb(msg);
}

/* Minimal self-contained upload page. Kept ASCII-only and dependency-free —
 * the pendant serves this to whatever browser connects. */
static const char k_index_html[] =
    "<!DOCTYPE html><html><head><meta name=viewport content='width=device-width'>"
    "<title>Pendant Firmware Update</title><style>"
    "body{font-family:sans-serif;max-width:480px;margin:40px auto;padding:0 16px}"
    "progress{width:100%;height:24px}button{padding:10px 24px;font-size:16px}"
    "</style></head><body>"
    "<h2>FluidCNC Pendant &mdash; Firmware Update</h2>"
    "<p>Select <code>trailcurrent_fluidcnc_pendant.bin</code> from the build "
    "directory, then press Upload. The pendant reboots automatically when "
    "flashing completes.</p>"
    "<input type=file id=f accept='.bin'><br><br>"
    "<button onclick='up()'>Upload</button><br><br>"
    "<progress id=p max=100 value=0></progress><div id=s></div>"
    "<script>function up(){var f=document.getElementById('f').files[0];"
    "if(!f){s.textContent='Pick a .bin first';return;}"
    "var x=new XMLHttpRequest();x.open('POST','/update');"
    "x.upload.onprogress=function(e){p.value=e.loaded/e.total*100};"
    "x.onload=function(){s.textContent=x.responseText};"
    "x.onerror=function(){s.textContent='Upload failed'};x.send(f);}"
    "</script></body></html>";

static esp_err_t index_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, k_index_html, HTTPD_RESP_USE_STRLEN);
}

static esp_err_t update_post_handler(httpd_req_t *req)
{
    const esp_partition_t *dest = esp_ota_get_next_update_partition(NULL);
    if (!dest) {
        report("OTA failed: no OTA partition (old partition table?)");
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                            "No OTA partition — device needs the OTA "
                            "partition table (one USB flash)");
        return ESP_FAIL;
    }

    int total = req->content_len;
    if (total <= 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Empty upload");
        return ESP_FAIL;
    }
    if ((uint32_t)total > dest->size) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Image too large");
        return ESP_FAIL;
    }

    esp_ota_handle_t ota = 0;
    esp_err_t err = esp_ota_begin(dest, total, &ota);
    if (err != ESP_OK) {
        report("OTA failed: esp_ota_begin");
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "ota_begin failed");
        return ESP_FAIL;
    }

    char msg[64];
    snprintf(msg, sizeof(msg), "Receiving firmware (%d KB)...", total / 1024);
    report(msg);

    char buf[4096];
    int  received = 0, last_pct = -5;
    while (received < total) {
        int n = httpd_req_recv(req, buf, sizeof(buf));
        if (n <= 0) {
            if (n == HTTPD_SOCK_ERR_TIMEOUT) continue;
            esp_ota_abort(ota);
            report("OTA failed: connection lost during upload");
            return ESP_FAIL;
        }
        err = esp_ota_write(ota, buf, n);
        if (err != ESP_OK) {
            esp_ota_abort(ota);
            report("OTA failed: flash write error");
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "flash write failed");
            return ESP_FAIL;
        }
        received += n;
        int pct = (int)((int64_t)received * 100 / total);
        if (pct >= last_pct + 5) {
            last_pct = pct;
            snprintf(msg, sizeof(msg), "Receiving firmware... %d%%", pct);
            report(msg);
        }
    }

    err = esp_ota_end(ota);
    if (err != ESP_OK) {
        /* Covers truncated images and failed validation. */
        report("OTA failed: image invalid");
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                            "Image validation failed — wrong or corrupt .bin?");
        return ESP_FAIL;
    }
    err = esp_ota_set_boot_partition(dest);
    if (err != ESP_OK) {
        report("OTA failed: could not set boot partition");
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "set_boot failed");
        return ESP_FAIL;
    }

    report("Update complete - rebooting...");
    httpd_resp_sendstr(req, "Update complete. Pendant is rebooting.");
    /* Give the response a moment to flush before the socket dies. */
    vTaskDelay(pdMS_TO_TICKS(1500));
    esp_restart();
    return ESP_OK;   /* unreached */
}

esp_err_t ota_update_start(ota_status_cb_t cb)
{
    if (s_server) return ESP_OK;
    s_cb = cb;

    httpd_config_t cfg = HTTPD_DEFAULT_CONFIG();
    cfg.server_port      = 80;
    cfg.lru_purge_enable = true;
    cfg.stack_size       = 8192;   /* esp_ota_* + TLS-free HTTP fits comfortably */

    esp_err_t err = httpd_start(&s_server, &cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "httpd_start failed: %s", esp_err_to_name(err));
        s_server = NULL;
        return err;
    }

    const httpd_uri_t index_uri  = { .uri = "/",       .method = HTTP_GET,
                                     .handler = index_get_handler };
    const httpd_uri_t update_uri = { .uri = "/update", .method = HTTP_POST,
                                     .handler = update_post_handler };
    httpd_register_uri_handler(s_server, &index_uri);
    httpd_register_uri_handler(s_server, &update_uri);
    ESP_LOGI(TAG, "OTA server listening on :80");
    return ESP_OK;
}

void ota_update_stop(void)
{
    if (!s_server) return;
    httpd_stop(s_server);
    s_server = NULL;
    s_cb     = NULL;
    ESP_LOGI(TAG, "OTA server stopped");
}

bool ota_update_active(void)
{
    return s_server != NULL;
}
