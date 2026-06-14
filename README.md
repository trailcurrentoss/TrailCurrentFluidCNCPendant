# TrailCurrent FluidCNC Pendant

Touch screen pendant for FluidNC / FluidCNC controllers.

Hardware: Waveshare ESP32-P4 WiFi6 Touch LCD 7B (1024x600 capacitive touch).
Framework: ESP-IDF 5.5.x + LVGL 8.4 via the Waveshare BSP component.
UI authored in [EEZ Studio](https://www.envox.eu/studio/) — project file lives in [GUI/](GUI/).

## Layout

| Path | Purpose |
|---|---|
| [main/](main/) | Application entry point and (future) UI export from EEZ Studio |
| [GUI/](GUI/) | EEZ Studio `.eez-project` (LVGL UI source of truth) |
| [assets/](assets/) | Source images, fonts, icons that feed the EEZ Studio project |
| [components/](components/) | Project-local ESP-IDF components |
| `partitions.csv` | Flash partition table (32 MB flash, 26 MB app + 5 MB SPIFFS) |
| `sdkconfig.defaults` | Pinned project sdkconfig — edit here, not `sdkconfig` |

## Build

```bash
. ~/esp/v5.5.2/esp-idf/export.sh
idf.py set-target esp32p4
idf.py build
```
