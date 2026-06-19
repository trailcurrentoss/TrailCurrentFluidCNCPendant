# 06 — Building and flashing

How to compile the firmware and get it onto the pendant. If you only
want to *use* the pendant, you can skip this chapter — flashed firmware
should be self-contained.

## Prerequisites

| Tool | Version | Purpose |
|---|---|---|
| [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32p4/get-started/) | 5.5.2+ | Compiler, build system, flash tool |
| [EEZ Studio](https://www.envox.eu/studio/) | latest | UI designer (only needed if you'll edit screens) |
| Linux / macOS / Windows | any recent | Host machine for the build |
| USB-C cable | any data-capable cable | Power + flashing |

Install ESP-IDF following the [official guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32p4/get-started/index.html) for your OS. The pendant targets the **ESP32-P4** chip; make sure your IDF install includes support for it.

## One-time setup

```bash
# Clone or copy the project
cd /path/to/TrailCurrentFluidCNCPendant

# Source the ESP-IDF environment (do this in every new terminal)
. ~/esp/v5.5.2/esp-idf/export.sh

# Tell IDF the target chip (only required once per checkout)
idf.py set-target esp32p4

# Pull managed component dependencies (esp_websocket_client etc.)
idf.py reconfigure
```

## Build

```bash
idf.py build
```

A clean build takes about 30 seconds on a modern laptop, 90 seconds on a
slow one. Subsequent rebuilds are incremental.

Output goes to `build/trailcurrent_fluidcnc_pendant.bin` (about 1.9 MB).

## Flash

Plug the pendant into your computer via USB-C. The board enumerates as
`/dev/ttyACM0` on Linux, `/dev/cu.usbmodem*` on macOS, `COM*` on Windows.

```bash
idf.py -p /dev/ttyACM0 flash
```

Flashing takes about 20 seconds. The board auto-resets after flashing
and starts running the new firmware.

## Monitor the serial console

To watch boot messages and log output:

```bash
idf.py -p /dev/ttyACM0 monitor
```

Exit with `Ctrl-]`. To flash and monitor in one go:

```bash
idf.py -p /dev/ttyACM0 flash monitor
```

## Configuring the build (menuconfig)

The most common reason to use `menuconfig` is to switch between the
real FluidNC backend and the bench-testing mock:

```bash
idf.py menuconfig
# → TrailCurrent FluidNC → [ ] Use mock backend (no real controller)
# Tap space to toggle, "S" to save, "Q" to quit
idf.py build flash
```

Other useful menus:

- **Component config → ESP-Hosted** — WiFi co-processor settings (don't
  change unless you know what you're doing; defaults work).
- **Component config → LVGL → Font** — additional Montserrat font sizes
  if you reference one in EEZ Studio that isn't currently enabled.

> ⚠️ **Don't edit `sdkconfig` directly.** It's regenerated on every
> build. Put changes in [`sdkconfig.defaults`](../sdkconfig.defaults).

## When something doesn't compile

| Error | Cause | Fix |
|---|---|---|
| `undefined reference to objects.<name>` | EEZ Studio Build hasn't run since the `.eez-project` changed | Open EEZ Studio, press Ctrl+B, retry `idf.py build` |
| `undefined reference to action_<Name>` | New action declared in EEZ Studio but no C handler in [actions.c](../main/actions.c) | Add `void action_<Name>(lv_event_t *e) { … }` to actions.c |
| `'ui_font_<name>' undeclared` | Custom font added but its `.c` file isn't in main/CMakeLists.txt | Add `"ui/ui_font_<name>.c"` to the `SRCS` list |
| `undefined reference to img_<name>` | New bitmap added but its `.c` file isn't in CMakeLists | Add `"ui/ui_image_<name>.c"` to `SRCS` |

More in [08 — Troubleshooting](08-troubleshooting.md).

## Releasing a binary

If you want a flashable image to share with someone who doesn't have
ESP-IDF installed, after a successful build you can produce a single
combined binary:

```bash
cd build
esptool.py --chip esp32p4 merge_bin \
    -o trailcurrent_pendant_full.bin \
    --flash_mode dio --flash_size 32MB --flash_freq 80m \
    0x2000 bootloader/bootloader.bin \
    0x8000 partition_table/partition-table.bin \
    0x10000 trailcurrent_fluidcnc_pendant.bin
```

The resulting `trailcurrent_pendant_full.bin` can be flashed with any
ESP-IDF or esptool installation:

```bash
esptool.py --chip esp32p4 -p /dev/ttyACM0 write_flash 0x0 trailcurrent_pendant_full.bin
```
