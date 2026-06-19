# 04 — How it talks to FluidNC

This chapter explains the conversation between the pendant and the
FluidNC controller. You don't need to read it to use the pendant — it's
here for the curious, and for anyone debugging a connection that's not
behaving.

## The big picture

The FluidNC controller speaks an old, simple, text-based protocol it
inherited from a project called grbl. Lines of text go in either
direction over the link (WiFi or wired serial). The pendant is just a
client that:

1. **Polls** the controller four times a second for its current state
   ("where's the spindle? what's running? any alarms?"), and
2. **Sends commands** when you tap buttons ("move +1 mm in X", "start
   spinning at 12000 rpm", "stop everything").

```
   ┌─────────────────┐                   ┌─────────────────┐
   │  PENDANT        │                   │  FluidNC        │
   │  (ESP32-P4)     │ ── "?" ─────────▶ │  controller     │
   │                 │                   │  (ESP32 board   │
   │                 │ ◀── "<Idle|...>" ─│  + stepper      │
   │                 │                   │   drivers)      │
   │                 │ ── "G0 X10" ────▶ │                 │
   │                 │ ◀── "ok" ─────────│                 │
   └─────────────────┘                   └─────────────────┘
```

## What goes over the wire

### Status reports (the most common message)

Four times a second the pendant sends a single byte: `?` (question mark).
FluidNC responds with one line in angle brackets, packed with comma-
separated key-value fields:

```
<Run|MPos:12.345,67.890,-1.230|FS:1500,12000|Ov:100,100,100|Pn:|A:SF>
```

Decoded:

- `Run` — current state (Idle / Run / Hold / Jog / Home / Alarm / Door / Check / Sleep)
- `MPos:12.345,67.890,-1.230` — machine position (X, Y, Z), in mm by default
- `FS:1500,12000` — current feed rate (mm/min) and spindle speed (rpm)
- `Ov:100,100,100` — feed / rapid / spindle override percentages
- `Pn:` — triggered pin flags (probe, limits) — empty here means none
- `A:SF` — accessory state: `S` = spindle clockwise, `F` = flood on

The pendant parses this in [src/proto.c](../components/fluidnc/src/proto.c)
and updates every widget that displays one of these values — DRO numbers,
status pill text and colour, override bars, spindle dial, coolant tile
states.

### Realtime control bytes (single byte, no newline)

Some controls bypass the line-by-line command queue because they need to
take effect immediately:

| Byte | Hex  | Meaning |
|---|---|---|
| `?` | `0x3F` | Status report request |
| `!` | `0x21` | Feed hold (pause motion mid-move) |
| `~` | `0x7E` | Cycle start / resume |
| `\x18` | `0x18` | Soft reset (used as E-STOP) |
| `\x85` | `0x85` | Jog cancel |
| `\x90`–`\x9D` | | Feed / rapid / spindle override step commands |
| `\xA0` | `0xA0` | Toggle flood coolant |
| `\xA1` | `0xA1` | Toggle mist coolant |

The pendant uses these for the E-STOP button, the HOLD / RESUME button,
and the override − / + buttons. They go out instantly without queueing.

### G-code lines (everything else)

Anything that takes a `\n` to terminate is g-code. The pendant
constructs and sends:

| Pendant action | What the pendant sends |
|---|---|
| Tap Jog X+ at 1 mm, 1200 mm/min | `$J=G91 G21 X1.0000 F1200.0\n` |
| Zero X in current WCS | `G10 L20 P0 X0\n` |
| Switch to G55 | `G55\n` |
| Switch to inch | `G20\n` |
| Home all | `$H\n` |
| Start spindle at 12000 | `M3 S12000\n` |
| Stop spindle | `M5\n` |
| Flood on / off | `M8\n` / `M9\n` |
| Reset alarm | `$X\n` |
| Start a job | `$LocalFS/Run=/spiffs/bracket_v3.nc\n` |
| Get file listing | `$LocalFS/List\n` |
| Z probe | `G38.2 Z-25 F100\n` then `G10 L20 P0 Z19.00\n` then `G0 Z24.00\n` |

The controller responds to each line with `ok` (accepted) or `error:N`
(rejected, where N is the grbl error code). The pendant doesn't surface
every error today — that's a future enhancement.

## Transports

The pendant supports three ways to physically reach the controller. You
pick one on the FluidConnect screen.

### WebSocket (wireless — recommended)

FluidNC exposes the grbl protocol over a WebSocket on
`ws://<controller-ip>:81/` (FluidNC 3.x) or `ws://<controller-ip>:80/`
(FluidNC 4.x). The pendant connects via the
[`esp_websocket_client`](https://components.espressif.com/components/espressif/esp_websocket_client)
library and treats each WebSocket text frame as one or more newline-
separated grbl lines.

Source: [src/transport_ws.c](../components/fluidnc/src/transport_ws.c).

### UART (wired)

If WiFi isn't reliable in your shop, or you just prefer wires, the
pendant can talk grbl over a UART pair instead. Wiring:

- Pendant GPIO 5 (TX) → Controller RX
- Pendant GPIO 4 (RX) → Controller TX
- Pendant GND → Controller GND
- 115200 8N1, no flow control

Match this baud rate in your FluidNC YAML config (usually under
`uart1:` or similar). Source:
[src/transport_uart.c](../components/fluidnc/src/transport_uart.c).

### Telnet (stub)

The pendant config knows about Telnet because FluidNC exposes one, but
the transport isn't implemented yet. Picking it returns a "not supported"
error. WebSocket is functionally equivalent for almost every use case.

## Inside the pendant — the dispatcher

When the pendant talks to FluidNC, three things happen on three different
FreeRTOS tasks:

1. **Status-poll task** — sends a `?` byte every 250 ms when the link is up.
2. **RX-parse task** — reads incoming bytes one chunk at a time, splits
   them at newlines, classifies each line (`<Status>`, `ok`, `error:N`,
   `[FILE:…]`, etc.), and updates the cached status struct.
3. **The widget refresh** — after every parsed status report, a callback
   fires that pushes the new values into the UI variables, which in
   turn update every relevant LVGL widget across all 8 screens.

The dispatcher (the brains tying these together) is in
[src/fluidnc.c](../components/fluidnc/src/fluidnc.c). The public API
(`fluidnc_jog`, `fluidnc_spindle_on`, etc.) is in
[include/fluidnc.h](../components/fluidnc/include/fluidnc.h).

## When things go wrong

### Connection drops mid-use

If the WebSocket disconnects, the pendant detects it and tries to
reconnect automatically. The status pill flips to **OFFLINE** while
disconnected and back to **IDLE** (or whatever state) when the link
recovers. UART links don't auto-detect drop the same way; you have to
pull power and reconnect.

### Controller alarms

When FluidNC enters alarm state, its next status report includes an
`Alarm` state token and the pendant:

1. Flips the status pill to red.
2. Shows the red **Alarm ribbon** across the top of every screen.
3. Refuses to send motion commands (e.g. jog) until alarm is cleared.

Tap **Reset** on the alarm ribbon (or the alarm-state pill) to send
`$X` and clear it.

### Commands that don't take effect

If you tap a button and nothing happens, possibilities are:

- The controller is in alarm (motion blocked until cleared).
- The controller is running a job (some commands queue, some are ignored).
- The link is down (status pill shows OFFLINE).
- The command was sent but FluidNC rejected it with `error:N` — these
  are logged on the pendant's serial console (USB-C) but not currently
  shown on screen.

For more on debugging, see [08 — Troubleshooting](08-troubleshooting.md).

## Mock backend (for bench testing without a real controller)

If you want to develop or demo the pendant without hooking it up to a
real CNC, the project ships a mock backend that simulates motion,
spindle ramp, file listings, and job progress. Enable it via:

```bash
idf.py menuconfig
# → TrailCurrent FluidNC → Use mock backend → Y
idf.py build flash
```

The mock lives in
[src/fluidnc_mock.c](../components/fluidnc/src/fluidnc_mock.c). It's
useful when:

- You want to test UI changes without standing next to a CNC.
- You want to record demo video of the pendant.
- The real controller isn't built/wired yet.

To go back to the real backend, set the option to N and rebuild.

## Useful FluidNC documentation

- [FluidNC wiki](https://github.com/bdring/FluidNC/wiki) — official docs
- [grbl realtime commands](https://github.com/gnea/grbl/wiki/Grbl-v1.1-Commands#real-time-commands) — full byte list
- [grbl status report format](https://github.com/gnea/grbl/blob/master/doc/markdown/interface.md#status-reporting) — field reference
