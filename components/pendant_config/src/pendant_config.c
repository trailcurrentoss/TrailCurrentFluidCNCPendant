#include "pendant_config.h"

#include <string.h>

#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

static const char *TAG = "pendant_cfg";

#define NS              "pendant"
#define KEY_SSID        "wifi_ssid"
#define KEY_PASS        "wifi_pass"
#define KEY_TRANSPORT   "fluid_tport"
#define KEY_HOST        "fluid_host"
#define KEY_PORT        "fluid_port"
#define KEY_UNITS       "units"
#define KEY_SOFT        "soft_lim"
#define KEY_HARD        "hard_lim"
#define KEY_HOME        "home_boot"

static pendant_config_t s_cfg;

static void apply_defaults(void)
{
    memset(&s_cfg, 0, sizeof(s_cfg));
    s_cfg.fluid_transport = PENDANT_TRANSPORT_UART;
    s_cfg.fluid_port      = 81;                  /* FluidNC 3.x default */
    s_cfg.units           = PENDANT_UNITS_MM;
    s_cfg.soft_limits     = true;
    s_cfg.hard_limits     = true;
    s_cfg.home_on_boot    = false;
}

static esp_err_t read_str(nvs_handle_t h, const char *key, char *buf, size_t buf_sz)
{
    size_t len = buf_sz;
    esp_err_t err = nvs_get_str(h, key, buf, &len);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        buf[0] = '\0';
        return ESP_OK;
    }
    return err;
}

esp_err_t pendant_config_init(void)
{
    apply_defaults();

    nvs_handle_t h;
    esp_err_t err = nvs_open(NS, NVS_READONLY, &h);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGI(TAG, "first boot — no saved config, using defaults");
        return ESP_OK;
    }
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "nvs_open: %s — using defaults", esp_err_to_name(err));
        return err;
    }

    read_str(h, KEY_SSID, s_cfg.wifi_ssid, sizeof(s_cfg.wifi_ssid));
    read_str(h, KEY_PASS, s_cfg.wifi_pass, sizeof(s_cfg.wifi_pass));
    read_str(h, KEY_HOST, s_cfg.fluid_host, sizeof(s_cfg.fluid_host));

    uint8_t  u8;
    uint16_t u16;
    if (nvs_get_u8(h,  KEY_TRANSPORT, &u8)  == ESP_OK) s_cfg.fluid_transport = (pendant_transport_t)u8;
    if (nvs_get_u16(h, KEY_PORT,      &u16) == ESP_OK) s_cfg.fluid_port      = u16;
    if (nvs_get_u8(h,  KEY_UNITS,     &u8)  == ESP_OK) s_cfg.units           = (pendant_units_t)u8;
    if (nvs_get_u8(h,  KEY_SOFT,      &u8)  == ESP_OK) s_cfg.soft_limits     = (bool)u8;
    if (nvs_get_u8(h,  KEY_HARD,      &u8)  == ESP_OK) s_cfg.hard_limits     = (bool)u8;
    if (nvs_get_u8(h,  KEY_HOME,      &u8)  == ESP_OK) s_cfg.home_on_boot    = (bool)u8;

    nvs_close(h);
    ESP_LOGI(TAG, "loaded — ssid=%s host=%s transport=%d units=%d",
             s_cfg.wifi_ssid[0] ? s_cfg.wifi_ssid : "(empty)",
             s_cfg.fluid_host[0] ? s_cfg.fluid_host : "(empty)",
             (int)s_cfg.fluid_transport, (int)s_cfg.units);
    return ESP_OK;
}

const pendant_config_t *pendant_config_get(void)
{
    return &s_cfg;
}

bool pendant_config_has_wifi(void)
{
    return s_cfg.wifi_ssid[0] != '\0';
}

bool pendant_config_has_fluid(void)
{
    /* UART needs no host; WS / Telnet do. */
    if (s_cfg.fluid_transport == PENDANT_TRANSPORT_UART) {
        return true;
    }
    return s_cfg.fluid_host[0] != '\0';
}

/* ---- Shared NVS write helpers ---- */
static esp_err_t write_str(const char *key, const char *value)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(NS, NVS_READWRITE, &h);
    if (err != ESP_OK) return err;

    err = nvs_set_str(h, key, value);
    if (err == ESP_OK) err = nvs_commit(h);
    nvs_close(h);
    return err;
}

static esp_err_t write_u8(const char *key, uint8_t value)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(NS, NVS_READWRITE, &h);
    if (err != ESP_OK) return err;

    err = nvs_set_u8(h, key, value);
    if (err == ESP_OK) err = nvs_commit(h);
    nvs_close(h);
    return err;
}

static esp_err_t erase_key(const char *key)
{
    nvs_handle_t h;
    esp_err_t err = nvs_open(NS, NVS_READWRITE, &h);
    if (err != ESP_OK) return err;
    err = nvs_erase_key(h, key);
    if (err == ESP_ERR_NVS_NOT_FOUND) err = ESP_OK;
    if (err == ESP_OK) err = nvs_commit(h);
    nvs_close(h);
    return err;
}

/* ---- Setters ---- */
esp_err_t pendant_config_set_wifi(const char *ssid, const char *pass)
{
    if (!ssid || !pass) return ESP_ERR_INVALID_ARG;
    strlcpy(s_cfg.wifi_ssid, ssid, sizeof(s_cfg.wifi_ssid));
    strlcpy(s_cfg.wifi_pass, pass, sizeof(s_cfg.wifi_pass));
    esp_err_t e1 = write_str(KEY_SSID, s_cfg.wifi_ssid);
    esp_err_t e2 = write_str(KEY_PASS, s_cfg.wifi_pass);
    ESP_LOGI(TAG, "saved WiFi creds for SSID=%s", s_cfg.wifi_ssid);
    return e1 ? e1 : e2;
}

esp_err_t pendant_config_clear_wifi(void)
{
    s_cfg.wifi_ssid[0] = '\0';
    s_cfg.wifi_pass[0] = '\0';
    esp_err_t e1 = erase_key(KEY_SSID);
    esp_err_t e2 = erase_key(KEY_PASS);
    return e1 ? e1 : e2;
}

esp_err_t pendant_config_set_fluid_transport(pendant_transport_t t)
{
    s_cfg.fluid_transport = t;
    return write_u8(KEY_TRANSPORT, (uint8_t)t);
}

esp_err_t pendant_config_set_fluid_host(const char *host)
{
    if (!host) return ESP_ERR_INVALID_ARG;
    strlcpy(s_cfg.fluid_host, host, sizeof(s_cfg.fluid_host));
    return write_str(KEY_HOST, s_cfg.fluid_host);
}

esp_err_t pendant_config_set_fluid_port(uint16_t port)
{
    s_cfg.fluid_port = port ? port : 81;
    nvs_handle_t h;
    esp_err_t err = nvs_open(NS, NVS_READWRITE, &h);
    if (err != ESP_OK) return err;
    err = nvs_set_u16(h, KEY_PORT, s_cfg.fluid_port);
    if (err == ESP_OK) err = nvs_commit(h);
    nvs_close(h);
    return err;
}

esp_err_t pendant_config_set_units(pendant_units_t u)
{
    s_cfg.units = u;
    return write_u8(KEY_UNITS, (uint8_t)u);
}

esp_err_t pendant_config_set_soft_limits(bool on) { s_cfg.soft_limits  = on; return write_u8(KEY_SOFT, on); }
esp_err_t pendant_config_set_hard_limits(bool on) { s_cfg.hard_limits  = on; return write_u8(KEY_HARD, on); }
esp_err_t pendant_config_set_home_on_boot(bool on){ s_cfg.home_on_boot = on; return write_u8(KEY_HOME, on); }
