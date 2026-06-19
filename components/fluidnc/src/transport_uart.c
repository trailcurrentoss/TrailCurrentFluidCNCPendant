/*
 * UART transport for FluidNC.
 *
 * The pendant exposes the ESP32-P4's UART0 on the USB-C bridge that's used
 * for flashing + console (/dev/ttyACM0). Wiring the FluidNC controller to
 * that same UART means the console logs would interleave with grbl traffic,
 * so the real pendant build needs to either:
 *   (a) move ESP-IDF console to a different UART (esp_console + UART1), or
 *   (b) wire FluidNC to a free UART (UART1, GPIO5 = TX, GPIO4 = RX is a
 *       common choice on the Waveshare board).
 *
 * The transport here uses UART1 at 115200 8N1 by default — match this to
 * the FluidNC controller's $0/$1 config when wiring. Pins are fixed in
 * code; revisit once we have a definitive wiring decision.
 *
 * Bytes received on UART1 are pushed into the dispatcher one line buffer
 * at a time. The rx task does a blocking read with a short timeout so we
 * don't burn CPU when the controller is idle.
 */

#include "transport.h"

#include <string.h>

#include "driver/uart.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define FLUIDNC_UART_NUM    UART_NUM_1
#define FLUIDNC_UART_TX_PIN 5
#define FLUIDNC_UART_RX_PIN 4
#define FLUIDNC_UART_BAUD   115200
#define FLUIDNC_UART_BUF    1024

static const char *TAG = "fluidnc_uart";

static TaskHandle_t      s_rx_task = NULL;
static volatile bool     s_run     = false;
static volatile bool     s_open    = false;

static void rx_task(void *arg)
{
    (void)arg;
    uint8_t buf[256];
    while (s_run) {
        int n = uart_read_bytes(FLUIDNC_UART_NUM, buf, sizeof(buf),
                                pdMS_TO_TICKS(100));
        if (n > 0) fluidnc_dispatcher_feed_rx((const char *)buf, (size_t)n);
    }
    s_rx_task = NULL;
    vTaskDelete(NULL);
}

static esp_err_t uart_open(const pendant_config_t *cfg)
{
    (void)cfg;          /* baud / pins are fixed for now */
    if (s_open) return ESP_OK;

    const uart_config_t uart_cfg = {
        .baud_rate  = FLUIDNC_UART_BAUD,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    esp_err_t err;
    err = uart_driver_install(FLUIDNC_UART_NUM, FLUIDNC_UART_BUF * 2,
                              FLUIDNC_UART_BUF * 2, 0, NULL, 0);
    if (err != ESP_OK) { ESP_LOGE(TAG, "driver_install: %s", esp_err_to_name(err)); return err; }
    err = uart_param_config(FLUIDNC_UART_NUM, &uart_cfg);
    if (err != ESP_OK) { ESP_LOGE(TAG, "param_config: %s",   esp_err_to_name(err)); return err; }
    err = uart_set_pin(FLUIDNC_UART_NUM, FLUIDNC_UART_TX_PIN, FLUIDNC_UART_RX_PIN,
                       UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    if (err != ESP_OK) { ESP_LOGE(TAG, "set_pin: %s",        esp_err_to_name(err)); return err; }

    s_run = true;
    if (xTaskCreatePinnedToCore(rx_task, "fluidnc_uart_rx", 3072, NULL, 5,
                                &s_rx_task, 0) != pdPASS) {
        uart_driver_delete(FLUIDNC_UART_NUM);
        s_run = false;
        return ESP_FAIL;
    }
    s_open = true;
    fluidnc_dispatcher_set_link_open(true);
    ESP_LOGI(TAG, "opened UART%d at %d baud (TX=%d RX=%d)",
             FLUIDNC_UART_NUM, FLUIDNC_UART_BAUD,
             FLUIDNC_UART_TX_PIN, FLUIDNC_UART_RX_PIN);
    return ESP_OK;
}

static void uart_close(void)
{
    if (!s_open) return;
    s_run = false;
    /* Let the rx task notice and exit. uart_driver_delete then unblocks
     * any pending read. */
    vTaskDelay(pdMS_TO_TICKS(150));
    uart_driver_delete(FLUIDNC_UART_NUM);
    s_open = false;
    fluidnc_dispatcher_set_link_open(false);
}

static esp_err_t uart_write(const void *data, size_t n)
{
    if (!s_open) return ESP_ERR_INVALID_STATE;
    int sent = uart_write_bytes(FLUIDNC_UART_NUM, (const char *)data, n);
    return sent == (int)n ? ESP_OK : ESP_FAIL;
}

static bool uart_is_open(void)
{
    return s_open;
}

const fluid_transport_t g_transport_uart = {
    .open    = uart_open,
    .close   = uart_close,
    .write   = uart_write,
    .is_open = uart_is_open,
};
