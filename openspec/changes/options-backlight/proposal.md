# Proposal

## Why

The application holds the backlight on while it holds or offers the link,
whatever the device's Backlight Time
(`openspec/specs/app-screen/spec.md:199-204`, `src/core/display.c:3-16`),
and nothing on the device lets the screen go dark.
The owner put the options first on 2026-11-14, Vibration and Backlight, `On | Auto` (`noteE`).
Vibration landed in `cf1818e`, its file in `b6a2c2d`,
and `options-table`, queued, leaves Backlight's rows and the cursor to this change (its `proposal.md:19-24`):
the options' second row stays empty (`openspec/specs/app-screen/spec.md:249`).
Claude Design drew both rows at canvas version `1794678650-09f9`,
1 px above the code's (`noteE`).

Decisions:

- **`Auto` is the firmware's own: the lock released, the device's Backlight Time darkens the screen, and a press lights it and acts,**
  not the canvas's press that only lights a dark screen (`noteE`; `risksE`, item 8):
  SDK 1.5.1 lets an application send to the backlight and read nothing back
  (`notification.h:12`, `:89-108`; `furi_hal_light.h:25`),
  so that press would take the application's own timer in place of the device's.
  The owner's call of 2026-11-14; `button-actions`' `A press acts with the backlight off` stands.
- **`D_stopped` goes dark at once under `Auto` too,**
  not when Backlight Time runs out:
  a press in the wait's last seconds would leave the stopped screen lit.
- **Up and Down each move the cursor to the other row,**
  not stopping at the ends:
  the firmware's lists wrap (`variable_item_list.c:185-226`, firmware 1.5.1),
  and a value already takes either of its keys (`risksE`, item 4).
- **The cursor stays where it was left until the application ends, and is not saved,**
  not back on `Vibration` each time the options open:
  it then moves on Up and Down alone.
- **The file gains the line `Backlight`, `true` for `On`, under version 1,**
  not a version 2:
  a file with no such line already opens with the option as it is by default
  (`openspec/specs/options/spec.md:80-81`).
- **`options-file` and `options-state` take three requirements from `options` and `host-tests`,**
  not changed where they stand:
  in place, the two deltas count 664 and 824 words against the 550 `openspec/config.yaml` allows.
- **The README, Home and the Flipper Apps Catalog's description stay:**
  their line on the options names the buzz
  (`README.md:27`, `docs/index.md:34-36`, `catalog/description.md:10-11`).
- **Frames and the file are read over RPC and the console, by taps that send no key and do not buzz;**
  the owner gives four glances at the light, one Disconnect in the Mac's Bluetooth settings
  and one screenshot in qFlipper.
- **Complex, so implemented on `feature/options-backlight`:**
  the display's rule gains a third answer across three layers,
  six spec documents change, and no frame shows the light.
- **It builds on `options-table`, queued.**
- **It lands as `feat(options): add a backlight option`.**

## What Changes

- The options gain `Backlight`, `On` or `Auto`, on their second row,
  kept in `options.txt` beside Vibration's; `On` is today's backlight.
- With `Auto` the screen goes dark by the device's Backlight Time, and a press lights it and acts.
- A tap on Up or Down moves the cursor between the rows, and Left and Right change the row under it.
- Both rows stand 1 px higher, as on the canvas.
- The guide, the architecture page and the options' screenshot follow.

## Capabilities

### New Capabilities

- `options-file`: how the options are kept on the SD card, taken from `options`.
- `options-state`: the options' values and cursor in the core, taken from `host-tests`.

### Modified Capabilities

- `options`: Backlight joins the options, and Up and Down move the cursor.
- `app-screen`: the backlight follows Backlight's value, and the options' boards show both rows.
- `host-tests`: the core gives the display one of three lights.
- `user-guide`: the guide says what Up, Down and Backlight do on the options.

## Impact

`src/core/option.h`, `keymap.h`, `keymap.c`, `display.h` and `display.c`,
with `test/keymap_test.c` and `test/display_test.c`;
`src/ui/view.h`, `view.c`, `view_options.h` and `view_options.c`;
`src/platform/app.c`, `backlight.h`, `backlight.c`, `options_file.c`, `screen.h` and `screen.c`;
`asset/screenshot/options-bt.png`;
`docs/guide/using-the-remote.md` and `docs/internals/architecture.md`.
The transport, `feedback.c`, `view_idle.c`, `README.md`, `catalog/` and every other screenshot stay as they are.
