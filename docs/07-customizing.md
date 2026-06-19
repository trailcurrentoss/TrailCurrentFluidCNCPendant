# 07 — Customizing

How to change what the pendant looks like and what it does.

## The two workflows

There are two completely separate workflows depending on what you want
to change:

| To change… | Use |
|---|---|
| Colors, fonts, layout, icons, themes | **EEZ Studio** (visual editor) |
| What happens when a button is tapped, what data updates a label | **A `.c` file** in `main/` |

Both end in `idf.py build flash`, but the editing surface is different.

## Changing what something looks like (EEZ Studio)

1. Install [EEZ Studio](https://www.envox.eu/studio/).
2. Open `GUI/TrailCurrentFluidCNCPendant.eez-project`.
3. Make your edits in the GUI (drag widgets, change colors, edit styles).
4. Save (`Ctrl+S`).
5. **Build** (`Ctrl+B`). This regenerates everything under `main/ui/`.
6. From your terminal: `idf.py build flash` to rebuild and flash.

> ⚠️ **Never edit files inside `main/ui/`.** They're overwritten on every
> Build. Your edits will disappear.

### Common edits

- **Change a colour** — Themes panel (left sidebar). Two themes ship:
  `Default` (light) and `Dark` (production). Click a colour token and
  edit the hex value. The change applies wherever that token is used.
- **Change a font size** — Open the style on the widget, change
  `text_font` to a different value. Use `MONTSERRAT_<n>` (e.g.
  `MONTSERRAT_16`) for sizes that LVGL has built-in; the names
  in lowercase (`mono_13`, `fa_22`) are custom fonts embedded by the
  project.
- **Move a button** — Click it, drag, or edit `left` / `top` / `width` /
  `height` in the properties panel.
- **Change a label's initial text** — Click the label, edit the `text`
  property. (At runtime, code in `vars.c` may overwrite this — see
  *Default vs runtime values* below.)
- **Add a new screen** — Right-click `userPages` → New. Place an
  `LVGLScreenWidget` as the root, then add child widgets inside.

### Default vs runtime values

Many widgets have an *initial* text or value set in EEZ Studio, but get
overwritten the moment data starts flowing. The DRO labels are an
example — they start at `0.000` per the EEZ Studio source, but the moment
the pendant connects to FluidNC, `set_var_work_dro_x()` in
[main/vars.c](../main/vars.c) starts pushing real values into them.

If you want a different default *before* data arrives, change the value
in **both** EEZ Studio (the initial text) and `vars.c` (the cache
default in the `s_v` struct initialiser). Both should agree.

## Changing what a button does (C)

Every interactive button in EEZ Studio has an `eventHandlers` entry
naming an action like `Jog`, `HoldResume`, `JobStart`. EEZ Studio's
Build (Ctrl+B) emits an `extern void action_<Name>(lv_event_t *e);`
prototype into `main/ui/actions.h`. You write the implementation in
[main/actions.c](../main/actions.c).

### Adding a new action

1. **In EEZ Studio**: open the Actions panel, add a new action (e.g.
   `MyNewAction`). Don't add anything inside the action's components
   list — actions are just named declarations when `flowSupport` is
   off (and it is for this project).
2. Wire the action to a button: open the button, click `eventHandlers`,
   add a new entry with `eventName=CLICKED`, `handlerType=action`,
   `action=MyNewAction`, `userData=0`.
3. **Build** (Ctrl+B). EEZ Studio emits the new `action_my_new_action`
   prototype into `main/ui/actions.h`.
4. **In actions.c**, add the implementation:

   ```c
   void action_my_new_action(lv_event_t *e)
   {
       (void)e;
       /* whatever you want this to do */
       fluidnc_send_line("G53 G0 X-100 Y0\n");
   }
   ```

5. `idf.py build flash` and you're done.

### Using userData to disambiguate

Many actions in the project use a single C function for many buttons,
distinguished by `userData`. E.g. `ChangeScreen` has userData 0–7 for
the 8 dock tabs; one handler does the dispatch:

```c
void action_change_screen(lv_event_t *e)
{
    int tab = (int)(intptr_t)lv_event_get_user_data(e);
    app_state_set_pendant_tab(tab);
}
```

Use this pattern when you have many similar buttons (a number pad, a
grid of macros).

### Changing what a macro does

Edit `k_macros[]` in [main/actions.c](../main/actions.c). Eight strings,
each a g-code program (multi-line OK, separate lines with `\n`).

```c
static const char *const k_macros[] = {
    "G53 G90 G0 Z0\nG53 G0 X0 Y0",         /* Go To Front  */
    "M6",                                   /* Tool Change  */
    /* …add yours here… */
};
```

The labels in EEZ Studio (`macros_name_0` etc.) stay where they are —
update them in EEZ Studio if you want the tile to say something
different.

### Changing the jog step sizes or feed default

Edit the `JOG_STEPS_MM` array near the top of
[main/actions.c](../main/actions.c). Four values, in millimetres. The
default feed rate is in NVS under "user_settings/jog_feed" and shown on
the Settings → Motion → Default Jog Feed slider.

## Changing what data updates a widget

When the controller's state changes, the flow is:

1. The dispatcher in [components/fluidnc/src/fluidnc.c](../components/fluidnc/src/fluidnc.c)
   parses the incoming grbl status report and calls the registered
   status callback.
2. `on_fluid_status()` in [main/app_state.c](../main/app_state.c) is the
   callback — it pulls fields out of the status struct and calls the
   appropriate `set_var_<name>()` functions.
3. The setter in [main/vars.c](../main/vars.c) caches the value and
   pushes it into the relevant LVGL widget(s).

If you want a new field to update a widget:

1. **Add the field to the status struct** in
   [include/fluidnc.h](../components/fluidnc/include/fluidnc.h) — e.g.
   `int probe_z_pos;`.
2. **Populate it in proto.c / fluidnc.c** — parse it from the grbl
   status report or wherever it comes from.
3. **Add a global variable in EEZ Studio** (Variables panel) — type
   matches what the widget needs. Build (Ctrl+B) emits the
   `set_var_<name>` prototype.
4. **Implement the setter in vars.c** — at minimum cache the value;
   ideally also push it into the widget (see existing overlays for the
   pattern).
5. **Call the setter from `on_fluid_status`** — `set_var_<name>(st->probe_z_pos);`.

## Changing colours / themes

The project uses **named colour tokens** (e.g. `AccentPrimary`,
`StatusDanger`, `BgCard`) defined once in the `colors` array, then bound
to hex values per theme in the `themes` array. To change a colour:

1. Open the .eez-project in EEZ Studio.
2. Themes panel → click the token you want to change.
3. Edit its hex value for both `Default` and `Dark` themes (or only
   one if the design intentionally differs per theme).
4. Save + Build.

If you want to add a *new* token, add it to `colors`, then add a hex
value at the same index in both themes' `colors` arrays.

> Some tokens are intentionally **theme-invariant** (same colour in both
> themes): `AccentPrimary`, `AxisX/Y/Z`, `StatusSuccess`,
> `StatusWarning`, `StatusDanger`, `ForegroundWhite`, `ForegroundBlack`.
> Don't change those per-theme — they represent semantic colour the
> rest of the design depends on.

## Adding a Font Awesome icon

The project embeds three Font Awesome subsets (`fa_16`, `fa_22`, `fa_28`)
with only the icons currently used. Adding a new icon means:

1. Look up the Unicode codepoint at <https://fontawesome.com/v6/icons>
   (it's in the "Unicode" field, e.g. `f04b` for fa-play).
2. In EEZ Studio, open the font (`fa_16`, `fa_22`, or `fa_28`) in the
   Fonts panel.
3. Add the codepoint to its `lvglRanges` list (comma-separated hex,
   e.g. `0xF04B`).
4. Save the project, close + reopen it so EEZ Studio re-embeds the font.
   (This is one of EEZ Studio's quirks — font re-embedding only fires
   when you edit a font through the GUI.)
5. Set the label's `text` to the UTF-8 encoding of the codepoint. For
   `f04b` this is `""` in EEZ Studio's text field (`"\xEF\x81\x8B"`
   if you're writing it in C).
6. Build (Ctrl+B) + `idf.py build flash`.

## Adding a custom bitmap

1. Drop the source image (PNG / JPG / BMP) into `assets/images/`.
2. In EEZ Studio, Bitmaps panel → Add. Point it at the file.
3. Place an `LVGLImageWidget` on a screen, set `image` to the bitmap's name.
4. Save + Build.
5. **Add the new generated file to the build**: open
   [main/CMakeLists.txt](../main/CMakeLists.txt) and add
   `"ui/ui_image_<bitmap_name>.c"` to the `SRCS` list. (EEZ Studio
   exports the bitmap data as a new `.c` file but doesn't auto-register
   it in CMakeLists.)
6. `idf.py build flash`.

## Adding a custom font

1. Drop the source TTF / OTF into `assets/fonts/`.
2. In EEZ Studio, Fonts panel → Add. Point it at the file. Set the size,
   choose the codepoint range, save.
3. Reference the font in any style as `text_font: <font_name>`.
4. Save + Build.
5. Add the generated file to the build:
   `"ui/ui_font_<font_name>.c"` in [main/CMakeLists.txt](../main/CMakeLists.txt).
6. `idf.py build flash`.

If you used a font size that's available as an LVGL built-in (any
Montserrat 8–48), reference it in UPPERCASE (`MONTSERRAT_14`) instead —
no font file needed, just enable `CONFIG_LV_FONT_MONTSERRAT_14=y` in
[sdkconfig.defaults](../sdkconfig.defaults).
