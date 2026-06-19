# 01 — Overview

## What is the pendant?

It's a 7-inch touchscreen that sits next to your CNC machine and acts as
the everyday control surface for it. You touch the screen to jog the
spindle, start a job, set zero positions, adjust feed and spindle speed,
and watch what the machine is doing.

Today most people running [FluidNC](https://github.com/bdring/FluidNC) (the
controller firmware this pendant talks to) reach the controller through a
web browser on a laptop or phone — point it at the controller's IP address
and you get the FluidNC web UI. That works, but it means a laptop on the
shop bench, an open browser tab, and your attention split between the
screen and the machine.

The pendant replaces that web UI with a purpose-built, always-on,
single-purpose touch panel. It mounts on the side of the machine. You walk
up, tap, and it does the thing.

```
┌─────────────────────────────────────────────────────────┐
│  ●  TrailCurrent              ●  IDLE   G54   --:--     │  ← Status bar
├─────────────────────────────────────────────────────────┤
│  ALARM RIBBON (hidden unless the machine alarms)        │
├─────────────────────────────────────────────────────────┤
│                                                         │
│            Whatever the active screen is                │
│            (Dashboard, Jog, Files, …)                   │
│                                                         │
├─────────────────────────────────────────────────────────┤
│  ▥ Dash · ✥ Jog · ▶ Run · 🗎 Files · 𝍝 Spindle · …      │  ← Bottom dock
└─────────────────────────────────────────────────────────┘
```

## Who is it for?

- **Hobbyists** running a small CNC mill, router, plasma cutter, or laser
  with a FluidNC controller, who want a tidy permanent control surface
  instead of a laptop on the bench.
- **Small shops** that want a consistent, fast UI for operators who
  shouldn't need to learn the browser-based FluidNC web UI.
- **Makers building their own CNC** who already have FluidNC on the
  controller side and want a matching front panel.

You **do not** need this pendant if FluidNC's built-in web UI on your phone
or laptop is meeting your needs — this is a hardware-and-software project
that involves buying a specific touchscreen and flashing firmware to it.

## What runs on it?

| Component | What it is |
|---|---|
| **Hardware** | Waveshare ESP32-P4 WiFi6 Touch LCD 7B board — a 7-inch 1024×600 capacitive touch panel with an ESP32-P4 main chip (no WiFi of its own) and a small ESP32-C6 co-processor that handles WiFi. |
| **Firmware framework** | [ESP-IDF 5.5](https://docs.espressif.com/projects/esp-idf/) — Espressif's official development framework. Provides the compiler, FreeRTOS, drivers, and flash tools. |
| **Graphics library** | [LVGL 8.4](https://lvgl.io/) — a lightweight C library that draws all the widgets (buttons, sliders, labels) and handles touch input. |
| **UI design tool** | [EEZ Studio](https://www.envox.eu/studio/) — a free visual editor for LVGL screens. The pendant's layout is designed in EEZ Studio and saved as a JSON file under [GUI/](../GUI/). |
| **CNC protocol** | The pendant speaks the same wire protocol FluidNC inherited from [grbl](https://github.com/grbl/grbl) — short g-code lines (`G0 X10`) and single "realtime" control bytes (`?` for status, `!` for hold, etc.). |

## What does it *not* do?

- It does **not** generate g-code. You create g-code somewhere else (CAM
  software like Fusion 360, Carbide Create, Kiri:Moto, etc.) and put the
  files onto FluidNC's SD card or local filesystem. The pendant browses
  and runs those files; it doesn't author them.
- It does **not** control stepper motors or relays directly. The CNC
  controller (an ESP32 board running FluidNC firmware) does all the
  motion. The pendant just talks to it.
- It does **not** include an emergency stop hardware button. The
  on-screen E-STOP sends a soft-reset command to FluidNC, which stops
  motion — but for real safety you should still have a physical
  emergency stop wired directly to the controller's input.
- It does **not** record video, host a camera, or stream the workshop
  anywhere. It's a control panel, not a monitor.

## How is it organised?

The pendant has **10 screens**, grouped in two phases:

**Setup screens** (shown only when there's something to set up):

- **WifiSetup** — scan and join a WiFi network
- **FluidConnect** — tell the pendant your controller's address and connect

**Operating screens** (the eight tabs in the bottom dock):

- **Dashboard** — the home screen; big position display, job progress, override sliders
- **Jog** — manually move each axis, zero coordinates, switch units
- **Run** — start/stop the current job, see g-code preview, monitor progress
- **Files** — browse the controller's SD card, pick a file to load
- **Spindle** — RPM dial, target speed, coolant on/off
- **Probe** — touch-off cycles for finding work zero or tool length
- **Macros** — eight one-tap shortcuts for things like "park", "tool change", "warm up spindle"
- **Settings** — preferences (units, brightness, theme), system info, WiFi management

[Chapter 03 — Screen tour](03-screen-tour.md) walks through each screen in detail.

## Where to next?

- If you have the hardware and want to use it: **[02 — Getting started](02-getting-started.md)**.
- If you just want to know what each screen does: **[03 — Screen tour](03-screen-tour.md)**.
- If you're a developer wanting to read the code: **[05 — Architecture](05-architecture.md)**.
