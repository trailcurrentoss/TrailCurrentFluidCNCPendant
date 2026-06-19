# TrailCurrent FluidCNC Pendant — Documentation

Welcome. This folder is the full documentation for the pendant — written so
someone who's never touched the project (and doesn't have a CNC background)
can read it cover to cover and end up knowing what the device does, how to
use it, and how it's built.

## Reading order

If you're new, read in order. If you already know what a CNC is and just
want to set the pendant up, skip to [02 — Getting started](02-getting-started.md).
If you're a developer who wants to modify the code, [05 — Architecture](05-architecture.md)
is the starting point.

| # | Topic | What's in it |
|--:|---|---|
| 01 | [Overview](01-overview.md) | What the pendant is, who it's for, the hardware |
| 02 | [Getting started](02-getting-started.md) | First boot — WiFi setup, connecting to a CNC |
| 03 | [Screen tour](03-screen-tour.md) | Every screen, every button, what it does |
| 04 | [How it talks to FluidNC](04-how-it-talks-to-fluidnc.md) | The protocol in plain English |
| 05 | [Architecture](05-architecture.md) | Code organisation — where things live and why |
| 06 | [Building and flashing](06-building-and-flashing.md) | Compiling and getting firmware on the device |
| 07 | [Customizing](07-customizing.md) | Changing screens, themes, actions |
| 08 | [Troubleshooting](08-troubleshooting.md) | Common problems and how to fix them |

## Glossary

Terms used throughout the docs. Skim once, refer back as needed.

- **CNC** — Computer Numerical Control. A milling machine, lathe, plasma cutter,
  laser, etc. that moves automatically under software control.
- **FluidNC** — open-source CNC controller firmware that runs on an ESP32 board
  connected to the stepper drivers. The pendant talks to it as a remote.
- **g-code** — the text language CNC machines speak. Commands look like
  `G1 X100 Y50 F1500` (move to X=100, Y=50 at 1500 mm/min). The pendant sends
  these to FluidNC behind the scenes when you tap a button.
- **grbl** — an older CNC firmware FluidNC inherits its wire protocol from. The
  status reports and realtime control bytes the pendant uses come from grbl.
- **Jog** — small, manually-commanded movement (used to position the spindle
  before running a job).
- **Home** — automatic move to the machine's reference position, used so the
  controller knows where the spindle physically is.
- **WCS** — Work Coordinate System. Lets you set "this corner of my material
  is zero" without moving the machine. FluidNC supports 6: `G54`–`G59`.
- **DRO** — Digital ReadOut. The big numbers on the screen showing where the
  spindle currently is.
- **LVGL** — the C library that draws everything on the screen.
- **EEZ Studio** — the visual designer used to lay out the pendant's screens.
  Saves to a `.eez-project` JSON file, which the build process turns into C code.
- **ESP-IDF** — Espressif's development framework for the ESP32 family of chips.
  Provides the compiler, flashing tool, and system libraries.
- **NVS** — Non-Volatile Storage. A small flash partition where the pendant
  remembers your WiFi password, controller address, and preferences.

If a term shows up in the docs that isn't here, let us know — we'll add it.
