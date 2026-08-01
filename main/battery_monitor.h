#pragma once

/*
 * Battery monitor — samples the on-board voltage divider on GPIO20 and pushes
 * state-of-charge + charging status into the UI via set_var_battery_pct() /
 * set_var_battery_charging() / set_var_battery_visible() in vars.c.
 *
 * The Waveshare ESP32-P4 WiFi6 Touch LCD 7B has a 200k / 100k divider from
 * V_BAT to GPIO20:
 *
 *     V_bat = V_adc * (R92 + R93) / R93
 *           = V_adc * (200 + 100) / 100
 *           = V_adc * 3.0
 *
 * There is no dedicated STAT pin on this board, so charging is detected from
 * V_bat trend + the near-full voltage threshold. See battery_monitor.c for
 * details.
 */

void battery_monitor_start(void);
