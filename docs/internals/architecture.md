---
description: The three layers of the source, each file's one task, and the files a press passes through.
---

# Architecture

## Layers

| Folder | Layer | Includes from |
|---|---|---|
| `src/core/` | The rules, with no Flipper header, tested on the Mac | Its own folder |
| `src/ui/` | Draws the state it is handed | Its own folder and the core |
| `src/platform/` | What exists only in the firmware | Every folder |

An include points down the layers only, relative to its file, as `"../core/action.h"`.
The core names what it needs, as the keys of `transport.h`,
and the platform supplies it, as `transport_hid.c` does.

## Files

| File | Its one task |
|---|---|
| `src/core/action.h` | Names the remote's actions |
| `src/core/mode.h` | Names the remote's modes |
| `src/core/link.h` | Names the remote's links |
| `src/core/option.h` | Names the remote's options |
| `src/core/keymap.h`, `src/core/keymap.c` | Maps a button event, a link change or the wait's end to an action, given the mode |
| `src/core/feedback.h`, `src/core/feedback.c` | Says how an action confirms itself |
| `src/core/deed.h`, `src/core/deed.c` | Says which deed an action earns |
| `src/core/display.h`, `src/core/display.c` | Says what light a mode gives the display, given Backlight |
| `src/core/charge.h`, `src/core/charge.c` | Says how many of the battery's cells a charge fills |
| `src/core/charging.h`, `src/core/charging.c` | Says whether the device charges, as the firmware's status bar counts it |
| `src/core/actions.h`, `src/core/actions.c` | Turns an action into calls on the transport |
| `src/core/transport.h` | Names what the core needs of a link |
| `src/ui/view_state.h` | Names what a frame shows |
| `src/ui/view.h`, `src/ui/view.c` | Draws a mode's board |
| `src/ui/view_main.h`, `src/ui/view_main.c` | Draws what only the main board shows |
| `src/ui/view_options.h`, `src/ui/view_options.c` | Draws the options board's controls |
| `src/ui/view_plate.h`, `src/ui/view_plate.c` | Draws the parts of a plate |
| `src/platform/main.c` | Hands the firmware's entry point to `app` |
| `src/platform/app.h`, `src/platform/app.c` | Runs the application's event loop |
| `src/platform/backlight.h`, `src/platform/backlight.c` | Gives the display the light asked for |
| `src/platform/battery.h`, `src/platform/battery.c` | Reports the battery as the firmware measures it |
| `src/platform/keymap_input.h`, `src/platform/keymap_input.c` | Translates a firmware event for the keymap |
| `src/platform/options_file.h`, `src/platform/options_file.c` | Keeps the options in a file on the SD card |
| `src/platform/screen.h`, `src/platform/screen.c` | Keeps what the display shows |
| `src/platform/transport_hid.h`, `src/platform/transport_hid.c` | Routes the core's keys to the link in use |
| `src/platform/transport_link.h` | Names what `transport_hid.c` needs of a link |
| `src/platform/transport_bluetooth.h`, `src/platform/transport_bluetooth.c` | Is the Mac's Bluetooth keyboard for its own life |
| `src/platform/transport_usb.h`, `src/platform/transport_usb.c` | Is the Mac's USB keyboard for its own life |

## A press's path

1. `screen.c`, on the GUI thread: the view port's input callback puts the `InputEvent` on the input queue.
2. `app.c`, on the event loop's thread: takes the event off the input queue.
3. `keymap_input.c`: translates the firmware's key and type into the keymap's own.
4. `keymap.c`: answers the action, given the mode, and moves the mode.
5. `actions.c`: presses and releases the action's keys through `transport.h`.
6. `transport_hid.c`: turns each key into its code, for the link in use.
7. `transport_bluetooth.c` or `transport_usb.c`: puts the code into the link's report.

Before step 5, `app.c` writes the mode, the link, the legend, each option and the cursor `keymap.c` holds
into the `ViewState` `screen.c` shows and sets it whole,
hands `options_file.c` each option, which writes the options to the SD card unless it is the one held,
then `transport_hid.c` that link, which switches to it unless it is the one in use.
After step 7, it hands the firmware's dolphin the deed `deed.c` names,
buzzes as `feedback.c` says of the action and Vibration,
and has `screen.c` flash the action and name it, each for `feedback.c`'s time.
Then, after every event, `backlight.c` takes the light `display.c` gives the mode and Backlight.

The link takes a second queue:
`transport_bluetooth.c`'s status callback, on the Bt thread,
or `transport_usb.c`'s, in the USB interrupt, puts `true` or `false` on the link queue,
and `app.c` hands it to `keymap.c`,
whose answer `actions.c` sends as a press's would be.

The charge takes a third queue, and the charging a fourth:
`battery.c` puts on each what the power service reads at the opening,
then each change its callback, on the power service's thread, is told of,
and `app.c` writes it into the `ViewState` `screen.c` shows and sets it whole.

The wait takes a timer in `app.c`, started and stopped as `keymap.c`'s `keymap_wait` answers after every event.
Its end goes to `keymap.c` too, whose answer `actions.c` turns into withdrawing the link,
and `backlight.c` goes dark, as `display.c` says of the new mode.

At the opening, `app.c` hands `options_file.c` each option `keymap.c` opens with,
and `keymap.c` the one `options_file.c` answers: read from the SD card, or the one handed where it reads none.

The queues exist because every function of an event loop must be called from the thread that made it
(documented: [`event_loop.h`](https://github.com/flipperdevices/flipperzero-firmware/blob/1.5.1/furi/core/event_loop.h#L15)).
`screen.c` keeps the `ViewState` behind a mutex, set whole on the event loop's thread and copied whole by the draw callback, on the GUI thread.
