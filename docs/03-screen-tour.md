# 03 — Screen tour

This chapter walks through every screen and every button. If you're trying
to figure out "what does this do?" while looking at the pendant, this is
the chapter to keep open.

## Things common to every screen

### Top status bar

Always visible at the top of every operating screen.

```
●  TrailCurrent  ●  IDLE   G54   13:42   📶   ‖ HOLD  ⏹ E-STOP   X 12.345  Y 67.890  Z  -1.230
```

- **● TrailCurrent** — brand mark on the left.
- **● Status pill** — a coloured chip showing the controller's state:
  - **IDLE** (neutral) — the controller is on but not moving.
  - **RUN** (green) — running a job or jogging.
  - **JOG** (green) — actively jogging in response to your taps.
  - **HOLD** (orange) — feed hold is engaged (paused mid-motion).
  - **HOMING** (orange) — running a homing cycle.
  - **ALARM** (red) — something tripped; the controller will refuse to move
    until you reset the alarm.
  - **OFFLINE** (red) — the pendant can't reach the controller.
- **G54** — the active work coordinate system.
- **13:42** — the on-board clock (not yet wired to network time; static for now).
- **📶 WiFi icon** — shown when the pendant is connected to WiFi.
- **‖ HOLD button** — same as the realtime feed hold: tap to pause motion.
  When already held, the label changes to **▶ RESUME**.
- **⏹ E-STOP button** — soft reset; stops motion and puts the controller in
  alarm state. For real emergencies you should still have a hardware
  e-stop wired to the controller.
- **X / Y / Z mini-DRO** — current position, condensed. Same as the big
  DRO on Dashboard / Jog but always visible no matter what screen you're on.

### Alarm ribbon

Appears as a red band below the status bar **only when the machine is in
alarm**. Shows the alarm code and a description; tap **RESET** on the
right side to clear it (sends `$X` to FluidNC).

### Bottom dock

Always visible at the bottom. Eight icon-and-label buttons that switch
between operating screens. The active one is highlighted.

```
▥ Dash   ✥ Jog   ▶ Run   🗎 Files   𝍝 Spindle   ✚ Probe   ⚡ Macros   ⚙ Settings
```

---

## Dashboard (▥ Dash)

The home screen. Everything you need to see at a glance during a job.

```
┌──────────────── Top status bar ────────────────┐
├────────────────────────────────────────────────┤
│  POSITION                          mm          │
│  X  [+12.345]   ▣Zero                          │
│  Y  [+67.890]   ▣Zero                          │
│  Z  [ -1.230]   ▣Zero                          │
├────────────────────────────────────────────────┤
│  FEED 100%   ─◖████████◗────  − +              │
│  RAPID 100%  ─◖████████◗────  − +              │
│  SPINDLE 100%─◖████████◗────  − +              │
├────────────────────────────────────────────────┤
│  JOB · bracket_v3.nc · 23%                     │
│  ████████░░░░░░░░░░░░░░░ Line 142 / 612        │
│  Elapsed 02:45    ETA 09:12                    │
├────────────────────────────────────────────────┤
│  𝍝 Spindle 12000 rpm   ⛆ Flood   ☷ Mist   ⌂ Home│
└─────────────────── Bottom dock ────────────────┘
```

- **POSITION card** — work-coordinate position, big. Tapping the **Zero**
  button next to an axis zeros that axis in the active WCS (sends
  `G10 L20 P0 X0`). The unit (mm or in) sits at the top right and reflects
  whatever you've picked in Settings.
- **Override card (Feed / Rapid / Spindle)** — three rows showing each
  override percentage. Tap **−** to drop by 10, **+** to bump by 10, and
  tap the percentage value itself to reset to 100. The bars fill to
  visualise the current value. *Note:* Rapid only has three legal grbl
  values (25 %, 50 %, 100 %) so taps cycle between those.
- **JOB card** — only meaningful during a run. Shows file name, percent,
  current line / total lines, elapsed time, ETA. When no job is running
  it shows placeholders.
- **Tile row** — four quick-access tiles:
  - **𝍝 Spindle** — tap to start/stop the spindle at the current target RPM.
  - **⛆ Flood** — toggle coolant flood (`M8` / `M9`).
  - **☷ Mist** — toggle coolant mist (`M7` / `M9`).
  - **⌂ Home** — run `$H` (homing cycle). The pendant will refuse if the
    controller is in alarm or already running.

## Jog (✥ Jog)

For manually moving the spindle around. Two DROs (work + machine
coordinates), a WCS picker, units, step-size buttons, and the directional pad.

- **Work / Machine DRO** — two columns, X/Y/Z each. Work is in the active
  WCS; machine is from the homed reference. Both update live.
- **WCS chips (G54–G59)** — tap any to switch active WCS (sends the
  matching g-code). The currently active one stays highlighted.
- **Units chips (mm / in)** — switch the controller's units (`G21` / `G20`)
  and the on-screen formatting. Saved to flash so it survives reboot.
- **Step size buttons (0.01 / 0.1 / 1.0 / 10)** — picks how far each tap
  of a direction button moves the spindle. Distance is in the current units.
- **Directional pad** — X+/−, Y+/−, Z+/−, with a Home button in the centre.
  Each tap fires a `$J=…` jog command at the current step size and the
  feed rate from Settings → Motion → Default Jog Feed.
- **Zero row (X 0 · Y 0 · Z 0 · All 0)** — instant zero buttons for each
  axis or all three at once.

## Run (▶ Run)

The job runner. Open this screen when you're about to start cutting.

- **Header card** — current file name, percent complete, progress bar,
  elapsed time, time remaining, current line.
- **G-code preview** — scrolling window of 20 lines of the program around
  the line currently executing. Line numbers on the left, g-code text on
  the right. (Static placeholder text today; live preview to come.)
- **Status card** — quick read of spindle RPM, feed rate, coolant state.
- **Start / Hold / Stop buttons**:
  - **▶ Start** — begins running the file currently loaded
    (`$LocalFS/Run=/spiffs/<name>` to FluidNC).
  - **‖ Hold** — feed hold (`!` realtime byte).
  - **⏹ Stop** — soft-reset then `$X` — stops motion and clears the alarm
    state so you can immediately run again or jog.

## Files (🗎 Files)

Browser for the g-code files stored on the FluidNC controller's local
filesystem (or SD card, depending on your FluidNC config).

- **Left side — file list** — up to 6 rows showing file name, size, date.
  Tap a row to select it (highlights green). The file count is shown above.
- **Refresh button** — re-queries the controller's file listing
  (`$LocalFS/List`). Useful after you've uploaded a new file via FluidNC's
  web UI.
- **Right side — Selected card** — shows the currently selected file's
  name and metadata (size, line count, runtime estimate).
- **Load & Run button** — equivalent to tapping the file then going to Run
  and tapping Start; one-tap shortcut.
- **Staging card** — placeholder for upload progress when streaming files
  from the pendant (not yet implemented; SD-on-controller is the current path).

> The pendant doesn't store g-code files itself — it always reads them
> from the controller. To get a new file onto the controller, use FluidNC's
> web UI (browse to its IP address in any browser) and upload there, then
> tap Refresh on the pendant.

## Spindle (𝍝 Spindle)

Dedicated spindle control screen, more detailed than the Dashboard tile.

- **Left card — RPM dial** — a big arc showing current RPM vs the target.
  Below it a Start/Stop button (label changes based on state).
- **Target card** — current target RPM with **−** / **+** buttons that
  step by 500 RPM. The displayed target is the value sent to FluidNC the
  next time the spindle is started (or, if already spinning, sent
  immediately as a new `M3 S…` line).
- **Load card** — spindle load (% of max). FluidNC reports this if the
  spindle driver supports load reporting; otherwise it stays at 0.
- **Coolant card** — Flood and Mist toggles. Same actions as the
  Dashboard tile row.

## Probe (✚ Probe)

Touch-off cycles for finding the surface of your material (so the
controller knows where Z=0 is) and similar reference operations.

- **Probe cycle picker (left)** — four cycle types:
  - **Z touch-off** — basic Z probe down + back off + set Z. *Implemented.*
  - **Corner** — find an outside corner of the stock. *Not yet implemented.*
  - **Center** — find the centre of a circular pocket / boss. *Not yet implemented.*
  - **Tool length** — measure tool length offset. *Not yet implemented.*
- **Parameters (right)** — three values:
  - **Plate thickness** — thickness of your probing plate in mm.
  - **Feed** — probe approach speed in mm/min.
  - **Travel** — maximum distance the probe will try before giving up.
- **Probe Z indicator** — last measured Z value. Shows "—" before a probe runs.
- **Start Probe button** — sends the probe sequence based on the selected cycle.

## Macros (⚡ Macros)

Eight tiles, each running a preset multi-line g-code snippet. Defaults
shipped:

| Tile | Macro |
|---|---|
| Go To Front | `G53 G90 G0 Z0` then `G53 G0 X0 Y0` |
| Tool Change | `M6` |
| Probe Z | `G38.2 Z-25 F100` |
| Spindle Warm | `M3 S8000` · `G4 P60` · `M5` |
| Set G54 Zero | `G10 L20 P1 X0 Y0 Z0` |
| Spindle Warmup | (duplicate of Spindle Warm) |
| Park Rear Right | `G53 G0 X-10 Y-10` |
| Unlock | `$X` |

To change what a macro does, edit the `k_macros[]` array in
[main/actions.c](../main/actions.c) and rebuild.

## Settings (⚙ Settings)

Tabbed settings page with five sub-tabs along the left.

### Settings → Machine

- **Units** — mm / inch. Sends `G21` / `G20` to the controller and saves
  the preference to flash.
- **Home on boot** — switch. If on, the pendant tells the controller to
  home immediately on connect. *Stored as a preference; behaviour wiring
  is a follow-up.*
- **Configure FluidNC Connection** — opens the FluidConnect screen so you
  can change the controller host / port / transport without re-doing WiFi.

### Settings → Connection

- **SSID** — the WiFi network the pendant is currently connected to.
- **State** — `Connected · 192.168.x.y` / `Disconnected` / `Failed`.
- **Change Network** — kicks the pendant back to the WiFi setup screen
  so you can pick a different network.
- **Forget** — drops the saved credentials and disconnects. Next boot
  will show the WiFi setup screen.

### Settings → Motion

- **Soft limits** — switch (preference only; FluidNC's `$20=1` is set in
  its own YAML).
- **Hard limits** — switch (preference only).
- **Default jog feed** — slider, 60–6000 mm/min. The Jog page uses this
  whenever you tap a directional button.

### Settings → System

Read-only info:

- **Firmware** — what FluidNC version the controller reported (parsed
  from the `[VER:…]` line FluidNC sends on `$I`).
- **Controller** — the chip identifier the controller reported.
- **UI** — `LVGL 8.4 · 1024x600`.
- **Network** — same string as the Connection tab's State field.

### Settings → Display

- **Brightness** — slider 0–255 with live preview. Saved to flash.
- **Screen timeout** — minutes until the screen blanks for inactivity
  (0 = never). Tapping the dark screen wakes it.
- **Theme** — Light / Dark. The Dark theme is the production look;
  Light is currently a near-mirror (placeholder for a real light palette).
