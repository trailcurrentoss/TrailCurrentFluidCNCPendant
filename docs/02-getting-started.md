# 02 — Getting started

This chapter walks through the very first time you power the pendant on.
It assumes the firmware is already flashed — if it isn't, do that first
([06 — Building and flashing](06-building-and-flashing.md)) and come back.

## What you need

- The Waveshare ESP32-P4 WiFi6 Touch LCD 7B board with firmware flashed.
- A USB-C cable to power it (any phone charger works — 5 V, 1 A is plenty).
- A WiFi network you can join. The pendant supports 2.4 GHz, WPA/WPA2/WPA3.
  5 GHz only networks won't work (the ESP32-C6 inside doesn't have a 5 GHz radio).
- Your FluidNC controller already configured and reachable on the same WiFi network
  (or wired to the pendant's UART pins — see *Wired connection* below).

## First boot

Plug in USB power. The screen will go through these stages:

1. **Black screen** for about 1 second while the ESP32 boots.
2. **Backlight comes on** and you see the LVGL UI initialise.
3. **WiFi Setup screen appears** — the pendant has scanned for networks and lists them.
4. (After WiFi connects) the pendant either skips straight to the **Dashboard**
   if you've used it before, or asks you to **Configure FluidNC Connection**.

That's it for a first-time happy-path boot. If the screen stays black for
more than 30 seconds, see [08 — Troubleshooting](08-troubleshooting.md).

## Connecting to WiFi

The WiFi Setup screen shows up to 8 nearby networks, sorted by signal strength.
Each row shows the network name (SSID), a signal-strength meter (0–3 bars),
and a padlock icon (locked = password required, unlocked = open).

```
┌────────────────────────────────────────────────┐
│  Connect to WiFi                               │
│  Pick a network to continue · or skip if you   │
│  prefer to wire the controller over serial     │
│                                                │
│  ┌──────────────────────────────────────────┐  │
│  │ ▮▮▮  HomeWiFi              🔒   →        │  │
│  │ ▮▮▯  Workshop              🔒   →        │  │
│  │ ▮▯▯  ShopGuest             🔓   →        │  │
│  │  ...                                     │  │
│  └──────────────────────────────────────────┘  │
│                                                │
│  [ Skip — Use Serial Only ]    [ ⟳ Rescan ]    │
└────────────────────────────────────────────────┘
```

### To join a network

1. Tap the row for the network you want.
2. If it's **open** (unlocked icon), the pendant connects immediately.
3. If it's **locked**, a password panel slides up with an on-screen keyboard.
   Type the password — you can tap the eye icon to show/hide it as you type.
4. Tap **Connect**. The pendant shows "Connecting to *YourNetwork*…" then
   either advances to the next screen or shows an error and goes back to
   the network list.

### Common errors

- **"Incorrect password."** — Re-tap the network and try again. The
  pendant doesn't save bad passwords, so you can keep trying.
- **"Network not in range."** — The signal dropped between scanning and
  connecting. Tap Rescan and try again.
- **"Timed out joining."** — The router took too long to respond. Rescan,
  or move closer.

The pendant **saves the credentials** to flash on the first successful
connect, so future boots auto-reconnect silently — you'll only see the WiFi
Setup screen again if you tap **Forget** in Settings → Connection, or if
the saved network disappears.

### Skipping WiFi

The **Skip — Use Serial Only** button is for setups where you'll wire the
pendant directly to the FluidNC controller's UART pins (see *Wired
connection* below). After tapping skip, the pendant goes straight to the
Dashboard and the FluidNC backend is set to UART.

## Connecting to FluidNC (the first time)

After WiFi joins, the pendant checks whether you've configured a FluidNC
controller before. If not, it shows the **FluidConnect** screen:

```
┌────────────────────────────────────────────────────────────┐
│  ●  TrailCurrent                              ●  WiFi 🟢   │
│                                                            │
│  Connect your FluidNC controller                           │
│  Pick a transport and tell us where to find it             │
│                                                            │
│  ┌────────── Transport ──────────┐                         │
│  │ ▣  ⟨⟩  WebSocket    Wireless  │  ← (pick one)           │
│  │ ▢  ⥨  UART          Wired     │                         │
│  │ ▢  ▦  Telnet        Wireless  │                         │
│  └───────────────────────────────┘                         │
│  ┌────────── Host & Port ────────────────────┐             │
│  │ [ 192.168.1.42      ] [ 81 ] [ CONNECT ]  │             │
│  └───────────────────────────────────────────┘             │
│  ●  Disconnected                       [ Back to WiFi ]    │
└────────────────────────────────────────────────────────────┘
```

### Wireless connection (WebSocket — recommended for most setups)

1. Tap the **WebSocket** card. It'll show a green checkmark.
2. Tap the host field. A keyboard slides up.
3. Type your controller's address. This can be:
   - An **IP address** (`192.168.1.42`) — look it up on your router's admin page,
     or in FluidNC's web UI under the System tab.
   - A **hostname** (`fluidnc.local`) — works on most home networks that support
     mDNS / Bonjour.
4. Tap the port field. The keyboard switches to numeric mode.
5. Type the port. Defaults:
   - **`81`** for FluidNC 3.x (the current 2026 release line)
   - **`80`** for FluidNC 4.x and later
   - If unsure, try 81 first.
6. Tap **CONNECT**. The status dot at the bottom turns green when the
   pendant successfully reaches the controller.
7. The pendant transitions to the Dashboard with live machine readouts.

### Wired connection (UART)

Use this if you want a wired link with no WiFi involvement — slightly more
reliable for permanent installs but requires a physical connection.

1. Wire the pendant's UART pins to the FluidNC controller's UART:
   - Pendant GPIO 5 (TX) → Controller RX
   - Pendant GPIO 4 (RX) → Controller TX
   - Pendant GND → Controller GND
2. On the FluidConnect screen, tap the **UART** card.
3. Tap **CONNECT** (host/port fields are ignored for UART).

The default baud rate is 115200 8N1; match this in your FluidNC YAML config.

## After you're connected

You land on the Dashboard. From here you can:

- Tap any axis chip (X / Y / Z) to **zero** that axis in the current work coordinate system.
- Drag the override sliders (Feed, Rapid, Spindle) to scale FluidNC's motion in real time.
- Tap any of the eight tabs in the bottom dock to switch screens.
- Tap the red **E-STOP** in the top-right to soft-reset the controller (panic button).

What every screen actually does is documented in [03 — Screen tour](03-screen-tour.md).

## Subsequent boots

After the first successful setup:
- WiFi auto-connects from saved credentials in about 4 seconds.
- The FluidNC connection is re-established to your saved host/port.
- The pendant lands directly on the **Dashboard** — no setup screens shown.

If the FluidNC controller is offline when the pendant boots, the status
pill in the top bar shows **OFFLINE** and the pendant retries automatically
every few seconds. As soon as the controller comes online the pill flips
to **IDLE** and live data starts flowing.

## Changing the connection later

- **Different WiFi network:** Settings → Connection → **Change Network**.
  This takes you back to the WiFi setup screen so you can pick a different SSID.
- **Different FluidNC controller:** Settings → Machine → **Configure FluidNC Connection**.
  Same FluidConnect screen as first boot, but reachable without re-doing WiFi.
- **Forget WiFi entirely:** Settings → Connection → **Forget**. The pendant
  drops the saved credentials and shows the WiFi setup screen on the next boot.
