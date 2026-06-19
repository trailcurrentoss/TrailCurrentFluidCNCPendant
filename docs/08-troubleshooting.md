# 08 — Troubleshooting

Things that go wrong, and what to do about them.

## Boot / display

### Screen stays black after powering on

- **Wait 30 seconds.** First boot after a fresh flash takes about 12 s
  before the backlight comes on; nothing's wrong if the screen is still
  off at 10 s.
- **Check the USB cable.** Some USB cables only carry power, not data.
  Use a known-good one.
- **Try a different USB port or power source.** The pendant draws up to
  500 mA in inrush; some PC USB ports can't deliver that cleanly.
- **Look at the serial console.** Connect `idf.py monitor` and watch for
  errors during boot. Typical successful boot starts with
  `ESP-ROM:esp32p4-eco2-…` and ends with `fluidcnc-pendant: boot complete`.

### Screen is on but shows a placeholder ("Run EEZ Studio Build…")

The firmware was built before the EEZ Studio export ran, so it has no
UI compiled in. Open the .eez-project in EEZ Studio, press **Ctrl+B**,
then `idf.py build flash`.

## WiFi

### "Incorrect password"

You typed the wrong password. Pick the network again and try.

### "Network not in range"

The signal dropped or the SSID isn't visible. Tap **Rescan** and retry.
If your network is 5 GHz-only, the pendant can't see it — you need a
2.4 GHz band on the same router.

### WiFi auto-reconnect doesn't happen on boot

Saved credentials may have failed validation. Go to Settings →
Connection → **Forget** and re-do the WiFi setup from scratch.

### WiFi connected but FluidNC says OFFLINE

The pendant has joined WiFi but can't reach the controller. Check:

- Is the controller powered on and on the same WiFi network?
- Is the host / IP correct? Open FluidNC's web UI in a browser from your
  laptop to confirm reachability.
- Is the port correct? FluidNC 3.x defaults to 81; FluidNC 4.x to 80.

## FluidNC connection

### Status pill always shows OFFLINE

The transport opened but no status reports are coming back. Possible
causes:

- **Wrong host/port.** Re-enter in Settings → Machine → Configure FluidNC.
- **FluidNC firewalled or disabled WebSockets.** Check the controller's
  YAML config — `websocket: enable: true` should be set.
- **UART wiring wrong.** Verify TX/RX swap (pendant TX → controller RX,
  pendant RX → controller TX). Common mistake.
- **UART baud mismatch.** The pendant uses 115200 8N1; the controller
  must match.

### Buttons don't do anything

Tap a button and nothing happens? Possibilities:

- **Controller in alarm.** Tap the alarm reset (the **R** on the red
  alarm ribbon, or the alarm-state pill) to send `$X`.
- **Controller running a job.** Some commands queue, some are ignored
  during a run. Stop the job first if needed.
- **Link is down.** Check the status pill — if it's red OFFLINE the
  command isn't going anywhere.

### Alarm shows "ALARM N" with no explanation

The pendant currently surfaces the alarm code but doesn't decode it.
Reference: [grbl alarm codes](https://github.com/gnea/grbl/wiki/Grbl-v1.1-Interface#alarm-codes-via-error-messages-when-using-grbl-controller-software).

Common ones:
- **Alarm 1** — Hard limit triggered.
- **Alarm 2** — Soft limit alarm (motion target outside soft limits).
- **Alarm 9** — Reset while in motion (the soft reset from E-STOP).
- **Alarm 10** — Homing required.

## Build / flash

### `idf.py: command not found`

You haven't sourced the ESP-IDF environment in this terminal. Run:

```bash
. ~/esp/v5.5.2/esp-idf/export.sh
```

(Adjust path to wherever you installed IDF.)

### `Permission denied: '/dev/ttyACM0'`

On Linux, your user isn't in the `dialout` group:

```bash
sudo usermod -a -G dialout $USER
# Then log out + back in for the group change to take effect
```

### `undefined reference to objects.<widget>`

EEZ Studio Build hasn't run since the .eez-project changed. Open the
project in EEZ Studio, press **Ctrl+B**, retry `idf.py build`.

### `undefined reference to action_<Name>`

EEZ Studio knows about an action that has no C implementation. Either:

- Add the implementation in [main/actions.c](../main/actions.c), or
- Remove the action from the .eez-project if it's not actually needed.

### `'ui_font_<name>' undeclared`

The font is referenced from `styles.c` but the corresponding `.c` file
isn't in the build. Add it to [main/CMakeLists.txt](../main/CMakeLists.txt)
`SRCS`:

```cmake
"ui/ui_font_<name>.c"
```

### `undefined reference to img_<name>` at link time

Same problem as missing font, for bitmaps. Add `"ui/ui_image_<name>.c"`
to [main/CMakeLists.txt](../main/CMakeLists.txt) `SRCS`.

### Empty squares `[]` appear in label text

The character you're trying to render isn't in the font's subset. Either:

- Use a different character (often the case for em-dash `—` vs hyphen
  `-`), or
- Add the codepoint to the font's `lvglRanges` in EEZ Studio
  (see [07 — Customizing](07-customizing.md), "Adding a Font Awesome icon").

## UI / interaction

### Touch is unresponsive in one area of the screen

The touch controller (GT911) maps to a fixed 1024×600 grid. If you see
dead zones, it's probably a hardware issue with the panel ribbon
connector — re-seat it.

### A label is cut off / overflows its container

EEZ Studio doesn't auto-size labels to fit text. Two fixes:
- Make the label widget wider, OR
- Use a smaller font in its style.

Both done in EEZ Studio + Build + flash.

### The keyboard on PageFluidConnect won't go away

Tap the **Connect** button (it dismisses the keyboard automatically), or
press Enter on the keyboard. If those don't work, navigate away via the
Back button.

## Settings persist across reboots in unexpected ways

The pendant stores in NVS (flash):

- WiFi SSID + password
- FluidNC host, port, transport
- Units (mm/in)
- Soft / hard limits switches
- Home on boot switch
- Screen brightness
- Screen timeout (minutes)
- Default jog feed (mm/min)
- Theme (light/dark)

To wipe everything and start fresh:

```bash
idf.py -p /dev/ttyACM0 erase-flash
idf.py -p /dev/ttyACM0 flash
```

This wipes ALL of flash — code AND NVS — so the next boot is a true
factory-fresh experience.

## Performance

### UI feels sluggish during a long g-code run

The status poller runs at 250 ms (4 Hz). On a complex job you may see
the pendant updating one beat behind reality. This is a deliberate
trade-off — polling faster would consume more bandwidth and CPU. If
you need higher rates, edit `POLL_PERIOD_MS` near the top of
[components/fluidnc/src/fluidnc.c](../components/fluidnc/src/fluidnc.c).

### The screen looks dim

Settings → Display → Brightness. Saved to flash on each change.

## Getting more help

If you hit something that isn't in this list, the serial console
(`idf.py monitor`) is your best friend — most issues show up as
`E (…)` (error) or `W (…)` (warning) log lines with a tag indicating
which subsystem is unhappy.

The project's tag list (handy for filtering):

- `fluidcnc-pendant` — top-level init in `main.c`
- `app_state` — state-machine transitions
- `actions` — UI button handlers
- `fluidnc` — protocol dispatcher (real backend)
- `fluidnc_ws` — WebSocket transport
- `fluidnc_uart` — UART transport
- `wifi_setup` — WiFi scan + connect
- `pendant_cfg` — NVS load/save
