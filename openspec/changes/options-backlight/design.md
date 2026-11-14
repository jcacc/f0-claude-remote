# Design

## Context

See `proposal.md`, Why.
The rules land in the core: the cursor in `keymap.c`, beside the values, and the display's light in `display.c`.
The UI draws both rows.
Platform-specific code carries the cursor to the GUI thread and sends the firmware the light:
the view port and the backlight's lock exist only in the firmware.

| Fact | Where |
|---|---|
| The firmware lights the display at every button event, RPC's included, and darkens it Backlight Time after the last | `notification_app.c:507-512`, `:129-134`, `:185-189`, `rpc_gui.c:238`, firmware 1.5.1 |
| The lock is a counter, and an unlock leaves a press's light on until that time runs out | `notification_app.c:229-249`, `:45-57`; the lock is documented, `notification_messages.h:91-94` |
| The rows: frames at y 16 and 31, text 9 px below a frame's top, arrows 2 px, a value centered on x 102 | the canvas, `1794678650-09f9`: `E_options_backlight_auto`, rows 10-16 |

## Goals / Non-Goals

**Goals:** the specs', the five boards 0 cells from the canvas's,
and with Backlight `On` the firmware's messages as `develop` sends them, in their order.

**Non-Goals:** a third option or a third value: the cursor's table and the `bool` hold two of each.

## Decisions

- **`display_light(mode, backlight)` gives one of three lights, `DisplayLightOn`, `DisplayLightAuto` or `DisplayLightOff`,**
  not `display_lit` beside a second question:
  held on, left to the device and off exclude each other.
- **`backlight_set` leaves the light it holds, then enters the one asked, a `switch` over `DisplayLight` each,**
  not a table of the firmware's sequences, nor an `if` on `DisplayLightOn` before one switch:
  a light left out stops the build at both, and the lock is given back where it is named.
- **`backlight_free` asks `backlight_set` for `DisplayLightAuto`, as `backlight_alloc` asks it,**
  not an `if` of its own: one line takes the lock and one releases it.
- **The cursor moves by `keymap_other_options[OptionMAX]`, as the link by its table (`src/core/keymap.c:27-30`),**
  not by arithmetic on the enumerator:
  of two rows each is the other's, whichever key.

The parts, on `options-table`'s names (its `design.md`):

- `option.h`: `OptionBacklight`, after `OptionVibration`.
- `keymap.c`: `cursor`, `OptionVibration` at the opening, answered by `keymap_cursor`.
  On the options Left and Right give `options[cursor]` its other value, Up and Down `cursor` the other row.
- `display.c` says what light a mode gives the display:
  `DisplayLightOff` for `ModeStopped`, otherwise `DisplayLightOn` or `DisplayLightAuto`, by `backlight`.
- `backlight.c` gives the display the light asked for, opening on `DisplayLightAuto`.
  `backlight_set` returns on the light it holds;
  leaving `DisplayLightOn` sends the unlock, entering it the lock,
  and entering `DisplayLightOff` `sequence_display_backlight_off`.
- `view_options.c`, its components the plate, a row and the cursor:
  `view_options_rows[OptionMAX]` holds a row's name, its value's other word, `Off` or `Auto`, and its frame's top;
  `view_options_draw` and `view_draw` take `cursor` after `options`.
- `screen.c`: an `_Atomic` word for the cursor, set by `screen_set_cursor`.
- `options_file.c`: `options_file_keys` gains `Backlight`.
- `app.c`: `app_follow_options` hands the screen the cursor too;
  the backlight takes `display_light` of the keymap's mode and `OptionBacklight` where it takes `display_lit`,
  the opening's below the card's reading (`src/platform/app.c:124-126`).

The tests.
`display_test.c`: the lit test asks its six modes with `true`,
`test_left_to_the_device_with_backlight_auto`, new, with `false`, and the dark test `ModeStopped` with both.
`keymap_test.c`: the five tests on Vibration ask every option, as
`test_fresh_keymap_has_every_option_on`, `test_keymap_takes_each_saved_option`,
`test_side_tap_on_the_options_switches_the_option_under_the_cursor`, `test_nothing_else_switches_an_option`
and `test_every_option_outlasts_the_options`;
four are new, `test_fresh_keymap_has_the_cursor_on_vibration`, `test_up_or_down_tap_on_the_options_moves_the_cursor`,
`test_nothing_else_moves_the_cursor` and `test_cursor_outlasts_the_options`;
`test_tap_through_a_drop_on_the_options_does_nothing` gains Down.

Walks 1 and 2 run over RPC and the console, each tap sent only on the frame it is for;
tasks 4.1 and 4.2 hold the owner's.
`v_on`, `v_off`, `b_on`, `b_auto` and `no_link` stand for `E_options_vibration_on`, `…_off`, `E_options_backlight_on`, `…_auto` and `E_options_no_link`:

1. No file: launch; Back: `v_on`; Up: `b_on`; Down: `v_on`; Back: still no file.
   Back, Right: `v_off`, the file's four lines, `Vibration: false`, `Backlight: true`; Left: `v_on`.
   Down: `b_on`; Right: `b_auto`, `Backlight: false`; Left: `b_on`, `Backlight: true`; Back, Back: `b_on`.
   Right, Back held at once: the application ends, the file whole, `Backlight: false`.
   Launch; Back, Down: `b_auto`.
2. Two plants, each before a launch.
   `Vibration: false` alone: Back: `v_off`.
   `Backlight: false` alone: Back, Down: `b_auto`; Left: `b_on`, the file's four lines, both `true`.

The pages: `docs/guide/using-the-remote.md`, under `options-bt.png`, says what `user-guide`'s `Content` lists,
both options `On` until changed, and that OK and every hold but Back's do nothing there;
`docs/internals/architecture.md` gives `display` and `backlight` the tasks above,
names the cursor wherever `screen.c` takes or reads the options,
and says the backlight takes its light after every event.

Test seams:

- `keymap.c`, `display.c`: their suites; red is the build, at `OptionBacklight` and `display_light`.
- The UI, which only renders: frames over RPC against the five boards.
- `screen.c`, `options_file.c`, `backlight.c` and `app.c`, with no host test:
  the build types the calls, the specs' greps count them, the walks read the file, and the owner sees the light.

## Risks / Trade-offs

- An arrow's tap that meets `D_Main` goes to the Mac → the walks send each only on an options frame.
- The device's Backlight Time is not 30 s → the owner reads it in Settings before task 4.2, which waits that time and 10 s.
- The stop stays unseen on the device, taking the Mac's Bluetooth off for a minute → `display_test.c` pins `ModeStopped` dark for either value, and `backlight.c` sends there no message `develop` does not (`src/platform/backlight.c:38-39`).
