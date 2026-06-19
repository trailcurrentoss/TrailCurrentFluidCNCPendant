# 05 — Architecture

A developer-oriented map of the codebase: what files exist, what
responsibilities each one has, and how they wire up.

If you've never read an ESP-IDF project before, the [README's project
layout table](../README.md#project-layout) and this chapter together
should be enough to find your way around.

## The 30-second summary

```
                       ┌──────────────────────────────────┐
                       │  EEZ Studio (.eez-project JSON)  │
                       │  ─ designed in the GUI app       │
                       │  ─ defines every screen, style,  │
                       │    action declaration, font      │
                       └──────────────┬───────────────────┘
                                      │  Build (Ctrl+B in EEZ Studio)
                                      ▼
                       ┌──────────────────────────────────┐
                       │  main/ui/*.c|*.h  (GENERATED)    │
                       │  ─ screens.c: every widget       │
                       │  ─ actions.h: action prototypes  │
                       │  ─ vars.h:    get/set prototypes │
                       └──────────────┬───────────────────┘
                                      │  linked with
                                      ▼
                       ┌──────────────────────────────────┐
                       │  main/  (HAND-WRITTEN C)         │
                       │  ─ main.c:      boot + LVGL init │
                       │  ─ app_state.c: state machine    │
                       │  ─ actions.c:   button handlers  │
                       │  ─ vars.c:      widget updaters  │
                       └──────────────┬───────────────────┘
                                      │  uses
                                      ▼
                       ┌──────────────────────────────────┐
                       │  components/  (LIBRARIES)        │
                       │  ─ fluidnc/  CNC protocol        │
                       │  ─ wifi_setup/  WiFi scan+join   │
                       │  ─ pendant_config/  NVS storage  │
                       └──────────────────────────────────┘
```

## Two halves: appearance vs state

The pendant's code follows one rule above all others:

> **EEZ Studio owns appearance. C owns state.**

- Colors, fonts, layouts, padding, borders, icons — all in the EEZ Studio
  `.eez-project` file. Edit them in EEZ Studio's GUI; never set them from C.
- Which widget is highlighted, which screen is showing, what text the
  DRO labels display, whether the alarm ribbon is visible — all in C.
  Code calls `lv_label_set_text(…)`, `lv_obj_add_state(…)`, etc.

If you want to change what something looks like, open EEZ Studio. If you
want to change what something does, open a `.c` file.

## File by file

### Root

- **[README.md](../README.md)** — Top-level intro, project layout, status.
- **[CLAUDE.md](../CLAUDE.md)** — Agent instructions (workflow rules,
  source-of-truth, build pattern). Read if you're contributing.
- **[sdkconfig.defaults](../sdkconfig.defaults)** — ESP-IDF config. Always
  edit this file; never `sdkconfig` (which is regenerated on every build).
- **[partitions.csv](../partitions.csv)** — Flash partition layout (32 MB
  flash: bootloader, partition table, 26 MB app, 5 MB SPIFFS for assets).
- **[CMakeLists.txt](../CMakeLists.txt)** — Top-level project file ESP-IDF
  expects.

### `main/` — application code

This is where the project-specific firmware lives. Everything else is a
library.

- **[main/main.c](../main/main.c)** — Boots NVS, the display via the
  Waveshare BSP, LVGL, then calls `ui_init()` (which builds every screen)
  and hands off to the state machine. Also owns the inactivity-blanking
  task that dims the screen after the configured timeout.

- **[main/app_state.h](../main/app_state.h)** — defines the top-level
  state machine: `BOOT → WIFI_SETUP → WIFI_CONNECTING → FLUID_CONNECT →
  FLUID_CONNECTING → PENDANT`. The state transitions decide which screen
  is showing.

- **[main/app_state.c](../main/app_state.c)** — implementation of the
  state machine. The `on_fluid_status` callback is the heart of the
  app — every status report from the controller flows through here and
  is fanned out into the UI variables.

- **[main/actions.c](../main/actions.c)** — one function per UI action.
  When you tap a button, EEZ Studio's generated `screens.c` registers a
  `LV_EVENT_CLICKED` handler that calls one of these. Conventions:
  - `evt_user_data(e)` returns the `userData` byte set in EEZ Studio,
    used to distinguish variants of one action (e.g. `ChangeScreen` with
    userData 0–7 for the 8 tabs).
  - `selector_swap(target, group, n)` is the helper used for any
    mutually-exclusive selector group (WCS chips, units, jog step,
    transport cards, etc.).

- **[main/vars.c](../main/vars.c)** — the **bridge** between the
  controller's status and the LVGL widgets. EEZ Studio's generated
  `vars.h` declares `set_var_<name>()` / `get_var_<name>()` for every
  global variable in the project; `vars.c` implements each one. Two flavours:
  - **Cache-only** setters (`VAR_STRING`, `VAR_INT`, `VAR_BOOL` macros) — just
    store the value, nothing else.
  - **Cache + widget-update** setters — hand-written to also push the new
    value into one or more widgets. Most of vars.c is this kind.

  Setters that fan out to many widgets (status bar lives on all 8 screens,
  so the WCS label / mini DRO / status pill is duplicated 8 times) loop
  over a static array of widget pointers.

- **[main/ui/](../main/ui/)** — **generated** by EEZ Studio's Build
  (Ctrl+B). Don't hand-edit; changes get clobbered on next export.
  - `screens.c` / `screens.h` — every widget object and the
    `create_screen_<name>()` constructors.
  - `actions.h` — `extern void action_<Name>(lv_event_t *e);` prototypes.
  - `vars.h` — `extern <type> get_var_<name>()` / `set_var_<name>()`
    prototypes for every global.
  - `styles.c` / `styles.h` — every named style.
  - `images.c` / `images.h` / `ui_image_*.c` — bitmap data.
  - `fonts.h` / `ui_font_*.c` — converted glyph data.
  - `ui.c` / `ui.h` — `ui_init()` that calls every screen's create function.

- **[main/CMakeLists.txt](../main/CMakeLists.txt)** — lists every source
  file in the `main` component, including every `ui/ui_font_*.c` and
  `ui/ui_image_*.c` from EEZ Studio. Add a new bitmap or font here when
  EEZ Studio emits one.

### `components/fluidnc/` — the CNC protocol

The most complex component. Three sub-systems:

- **Dispatcher** ([src/fluidnc.c](../components/fluidnc/src/fluidnc.c)):
  picks a transport at connect time, runs the status-poll task, runs the
  RX-parse task, exposes the high-level command API (`fluidnc_jog`,
  `fluidnc_spindle_on`, etc.).

- **Parsers** ([src/proto.c](../components/fluidnc/src/proto.c)): pure C
  string parsing for the grbl status report, classification of incoming
  lines (`ok`, `error:N`, `[FILE:…]`, etc.), and helpers to extract codes
  and file metadata.

- **Transports** — three implementations of one vtable
  ([src/transport.h](../components/fluidnc/src/transport.h)):
  - **[transport_ws.c](../components/fluidnc/src/transport_ws.c)** —
    WebSocket via `esp_websocket_client`. Used for wireless.
  - **[transport_uart.c](../components/fluidnc/src/transport_uart.c)** —
    UART1 at 115200 8N1 (GPIO 5 TX, 4 RX). Used for wired.
  - **[fluidnc_mock.c](../components/fluidnc/src/fluidnc_mock.c)** —
    bench testing without a real controller. Selected via Kconfig.

The mock and the real backend are mutually exclusive — only one is
compiled in (controlled by `CONFIG_FLUIDNC_USE_MOCK`). Both expose the
same public API in
[include/fluidnc.h](../components/fluidnc/include/fluidnc.h), so the rest
of the project doesn't know or care which one is active.

### `components/wifi_setup/` — joining WiFi networks

- **[include/wifi_setup.h](../components/wifi_setup/include/wifi_setup.h)** —
  public API: `wifi_setup_init`, `wifi_setup_scan_start`, `wifi_setup_connect`,
  `wifi_setup_disconnect`, plus state and result-readout helpers.

- **[src/wifi_setup.c](../components/wifi_setup/src/wifi_setup.c)** —
  brings up the ESP-Hosted bridge to the ESP32-C6 (where the WiFi radio
  lives), starts a STA-mode driver, scans, connects, classifies disconnect
  reasons into the buckets the UI surfaces ("Bad password" / "Network not
  in range" / "Timed out").

### `components/pendant_config/` — persistent storage

- **[include/pendant_config.h](../components/pendant_config/include/pendant_config.h)** —
  the `pendant_config_t` struct (WiFi creds, FluidNC host/port/transport,
  units, limit prefs, home-on-boot) plus init / getter / setters.

- **[src/pendant_config.c](../components/pendant_config/src/pendant_config.c)** —
  reads / writes the NVS namespace `pendant`. Setters update the cache
  AND commit to flash atomically.

### `GUI/` — the EEZ Studio project

- **[GUI/TrailCurrentFluidCNCPendant.eez-project](../GUI/TrailCurrentFluidCNCPendant.eez-project)** —
  the source of truth for the UI. JSON. Edit in EEZ Studio's GUI; build
  with Ctrl+B to regenerate `main/ui/`.

### `assets/` — source images and fonts

The TTF / OTF source files for fonts used in the project, and source PNG
/ SVG / JPG images for any bitmaps. These get embedded into the
generated UI code at EEZ Studio build time — they're not flashed
separately.

## The boot sequence (step by step)

When you power on the pendant:

1. **ESP32-P4 ROM bootloader** runs from on-chip ROM (about 50 ms).
2. **Second-stage bootloader** from the `bootloader` partition (about
   500 ms — sets up flash, PSRAM, clocks).
3. **`app_main()` in [main.c](../main/main.c)** starts:
   1. `nvs_flash_init()` — opens the settings storage.
   2. `esp_event_loop_create_default()` — needed by WiFi later.
   3. `pendant_config_init()` — loads WiFi creds + FluidNC config from NVS.
   4. `bsp_display_start_with_config(...)` — brings up the panel and
      LVGL (this takes about 2 s).
   5. `ui_init()` — builds every screen in memory.
   6. `restore_user_settings_from_nvs()` — restores brightness, timeout,
      jog feed, theme.
   7. `app_state_init()` — initialises WiFi + FluidNC components and
      decides whether to show WifiSetup or auto-reconnect.
4. **Inactivity-blanking task** is spawned to handle screen dimming.
5. **WiFi auto-connect** (if creds are saved) — takes 3–5 s on a typical
   network.
6. **FluidNC auto-connect** (if a controller is configured) — happens in
   the background; the pendant lands on the Dashboard regardless.

The whole thing from power-on to a usable Dashboard is **about 15
seconds** on a typical setup.

## Threading model

The pendant runs FreeRTOS with these tasks:

| Task | Purpose | Stack |
|---|---|---|
| `main_task` | Runs `app_main()` then exits | — |
| `LVGL` task (pinned to core 1) | Owns all LVGL state, draws everything, dispatches touch events | 7 KB |
| `wifi_setup` event handler | Runs on the default event loop task | — |
| `fluidnc_rx` | Parses incoming grbl lines | 4 KB |
| `fluidnc_pol` | Sends `?` every 250 ms | 3 KB |
| `fluidnc_uart_rx` | Reads bytes from UART1 (only in UART mode) | 3 KB |
| `WS-client task` | esp_websocket_client's own RX loop (only in WebSocket mode) | 6 KB |
| `blank` | Watches for inactivity, dims/wakes the screen | 3 KB |

The rule for safe LVGL access is: **always wrap LVGL calls with
`bsp_display_lock()` / `bsp_display_unlock()` if you're not on the LVGL
task**. The variable setters in `vars.c` and the helpers in `app_state.c`
do this for you.

## Where to look when you want to…

| Goal | File(s) |
|---|---|
| Add or change a button's behaviour | [main/actions.c](../main/actions.c) |
| Change what a status field shows | [main/vars.c](../main/vars.c) (setter for that field) |
| Add a new top-level state | [main/app_state.h](../main/app_state.h) + [main/app_state.c](../main/app_state.c) |
| Send a new kind of command to FluidNC | [include/fluidnc.h](../components/fluidnc/include/fluidnc.h) + [src/fluidnc.c](../components/fluidnc/src/fluidnc.c) |
| Add a new field to the grbl status report | [src/proto.c](../components/fluidnc/src/proto.c) + [src/fluidnc.c](../components/fluidnc/src/fluidnc.c) |
| Add a new bitmap | EEZ Studio (add to bitmaps), then `main/CMakeLists.txt` (add `ui/ui_image_<name>.c`) |
| Add a new font | EEZ Studio (add to fonts) + `sdkconfig.defaults` if it's a Montserrat size |
| Change colour palette | EEZ Studio → Themes |
| Change persisted settings shape | [pendant_config.h](../components/pendant_config/include/pendant_config.h) + [pendant_config.c](../components/pendant_config/src/pendant_config.c) |
