#pragma once

/*
 * Diagnostic monitor for a 3-pin analog thumbstick (VRX / VRY / SW). Logs
 * ADC + digital state every ~250 ms so you can confirm in `idf.py monitor`
 * that the stick is wired up correctly before any UI work depends on it.
 *
 * Pins are set with PIN_VRX / PIN_VRY / PIN_SW at the top of
 * thumbstick_monitor.c. Default wiring uses ADC2 on the P1 expansion
 * header — see the comment block there for the pin map and why those
 * specific pins are required on the ESP32-P4.
 */
void thumbstick_monitor_start(void);
