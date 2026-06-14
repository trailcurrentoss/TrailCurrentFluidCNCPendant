# Assets

Source artwork that feeds the EEZ Studio project in [../GUI/](../GUI/). EEZ Studio imports from here; **nothing in this folder is consumed at firmware build time** — it is design-time material only.

## Layout

```
assets/
├── fonts/
│   └── fontawesome/         # OTF (Solid, Regular, Brands) — for LVGL font subsetting
├── icons/
│   └── fontawesome/         # Font Awesome 7.2.0 Free icon raster + vector sets
│       ├── svg/{solid,regular,brands}/        # 2860 vector source SVGs
│       ├── png16/{solid,regular,brands}/      # 2860 PNGs rasterized at 16x16 px
│       ├── png32/{solid,regular,brands}/      # 2860 PNGs rasterized at 32x32 px
│       └── LICENSE.txt
├── images/                  # Project bitmap art (screen backgrounds, logos, etc.)
└── source/                  # Editable masters (SVG, AI, PSD, FreeCAD exports, …)
```

## Font Awesome

- Version: **7.2.0 Free** (CC BY 4.0 for icons, SIL OFL 1.1 for fonts, MIT for code — see `LICENSE.txt`).
- Family counts: solid (2000), regular (273), brands (587). Total: **2860 icons**.
- PNGs are black-on-transparent ARGB, centered, uniformly scaled to fit the canvas.
- Use the **SVG** when EEZ Studio is the consumer (vector → any size, recolorable).
- Use the **PNG** when you need a guaranteed pixel-aligned raster at the chosen size.
- Use the **OTF** when subsetting an LVGL icon font (typical for buttons that mix icon+text).

## Adding new assets

1. Drop the master file into `assets/source/`.
2. Export the production-format file (PNG / SVG) into `assets/images/` or `assets/icons/`.
3. Import into EEZ Studio from there.
