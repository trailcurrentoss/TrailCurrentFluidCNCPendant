# GUI

The EEZ Studio LVGL project that drives the pendant UI lives here. The exported C output is committed to [`../main/ui/`](../main/) (when populated) — never edit those files by hand.

## Workflow

1. Open the `.eez-project` in this folder with [EEZ Studio](https://www.envox.eu/studio/).
2. Build / Export → C files land in `../main/ui/`.
3. Run `idf.py build` from the project root to compile firmware against the new UI.

## Source assets

Drop any new icons, images, or fonts into [`../assets/`](../assets/) first, then reference them from EEZ Studio. The full Font Awesome 7.2.0 Free icon set (SVG + 16/32 px PNG) is already staged in `../assets/icons/fontawesome/`.
