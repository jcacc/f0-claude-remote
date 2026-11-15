# app-screen Specification

## Purpose

Shows the remote's one screen: the link's status and every button's action, with boards of their own for voice, a voice cut by the link, a stopped offer and USB.

## Requirements

### Requirement: The application carries its name
The device SHALL list the application as `Claude Remote`.

#### Scenario: Apps menu
- **WHEN** Apps → Bluetooth opens on the device after `mise run launch`
- **THEN** it lists `Claude Remote`

### Requirement: The application opens on its one screen
Starting the application SHALL show its screen across the whole display,
with no menu first and no system status bar.

#### Scenario: Start
- **WHEN** `mise run launch` runs
- **THEN** the device shows the screen, with no status bar above it

### Requirement: The screen shows the status and every button's action
The main screen, with the link up, voice off and no flash running, SHALL show a status row above a ring of the device's buttons,
with a thin frame on every action taken by a press,
a black plate on every held one,
and, until a button is pressed on it, a legend saying so.
The ring and Back's plate SHALL stand in one outline, shaped as the recess the device's case has around its buttons.

#### Scenario: Status row
- **WHEN** the main screen shows with no flash running, before a press on it
- **THEN** the top row reads, left to right,
  a Bluetooth mark, `Connected`, and a legend of `HOLD` joined to `TAP`,
  above a line across the display

#### Scenario: Legend
- **WHEN** the main screen shows with no flash running
- **THEN** a ring holds an element split by a diagonal,
  a microphone at its upper left and an Enter arrow at its lower right,
  with `/effort high` and an up arrow at the ring's top,
  `/clear` and a left arrow on its left,
  a right arrow and `Esc` on its right,
  `/effort max` and a down arrow at its bottom,
  and a Back mark and `exit` under `Esc`

#### Scenario: The recess
- **WHEN** the main screen shows with no flash running
- **THEN** one outline holds the split element and Back's plate, and passes under the ring's four plates:
  round about the ring, then narrowing to a round end past Back's plate, with a level bottom,
  and no line of it inside a plate

#### Scenario: Hold and press read apart
- **WHEN** the main screen shows with no flash running, before a press on it
- **THEN** `HOLD`, `/effort high`, `/effort max`, the microphone, `/clear`, `Esc`, `exit` and the Back mark stand white on a black plate,
  and `TAP`, the four arrows and the Enter arrow stand black in a thin frame

#### Scenario: The board
- **WHEN** the link comes up with voice off and no flash running, before a press on the main screen
- **THEN** a frame read off the device equals board `D_Main`

#### Scenario: Nothing clipped
- **WHEN** the application is open, in any state
- **THEN** every label is whole and stands clear of its neighbors

### Requirement: Holding Back leaves the application
Holding Back for the device's long press SHALL end the application, from the options as from the main screen,
and a short press SHALL end nothing,
except on `D_stopped`, where Back's press ends it at once.

#### Scenario: Long press
- **WHEN** Back is held until the long press fires
- **THEN** the application ends and the device returns to the screen it was started from

#### Scenario: Short press
- **WHEN** Back is pressed and released before the long press fires, on any board but `D_stopped`
- **THEN** the application stays open, and its screen changes only as `options` says

#### Scenario: Stopped screen
- **WHEN** Back is pressed on `D_stopped`
- **THEN** the application ends at once, and the device returns to the screen it was started from

### Requirement: A new launch replaces the running application
`mise run launch` SHALL succeed while the application is open on Bluetooth.

#### Scenario: Launch over a running copy
- **WHEN** `mise run launch` runs while the application is open on Bluetooth
- **THEN** it exits 0, its log reads `App closed`, and the application opens again

### Requirement: Voice has a screen of its own
While voice is on, the screen SHALL show, white on black, the Bluetooth mark and `Connected` above a line across the display,
a microphone, `Listening` and `Release OK to stop`,
with no legend and no ring.

#### Scenario: Voice on
- **WHEN** voice starts
- **THEN** a frame read off the device equals board `D_voice`

#### Scenario: Voice off
- **WHEN** voice stops
- **THEN** a frame read off the device equals board `D_Main`

### Requirement: A sent action flashes its element
Effort high, effort max, clear, Esc and Enter SHALL each invert the inside of their part of their element for 400 ms,
and the four arrows theirs for 100 ms,
with the element's frame unchanged.

#### Scenario: The long flash
- **WHEN** one of the five acts
- **THEN** a frame read off the device equals its board,
  `D_sent_high`, `D_sent_max`, `D_sent_clear`, `D_sent_esc` or `D_sent_enter`,
  and 400 ms later one equals `D_Main`

#### Scenario: The short flash
- **WHEN** an arrow acts
- **THEN** a frame read off the device equals `D_sent_up`, `D_sent_down`, `D_sent_left` or `D_sent_right`,
  and 100 ms later one equals `D_Main`

#### Scenario: Only the half that acted flashes
- **WHEN** an action of Up, Down, Left, Right or OK flashes
- **THEN** the other half of its element does not change

#### Scenario: Acting again restarts it
- **WHEN** an action flashes while a flash runs
- **THEN** that action's flash shows and lasts its own duration from then on

#### Scenario: A series of arrow taps
- **WHEN** Up is tapped 5 times a second
- **THEN** frames read off the device alternate `D_sent_up` and `D_Main`, once per tap,
  and the owner sees each flash apart

#### Scenario: Voice takes over
- **WHEN** voice starts while a flash runs and stays on past its end
- **THEN** the voice screen shows throughout

### Requirement: The status follows the link
The screen SHALL read `Connected` only while the Mac holds the link, which over Bluetooth means paired.
While the link is offered with none up and the options are closed, it SHALL show `No link` and `Reconnecting...` with no ring,
and `Keys are not sent` unless a voice was cut;
`D_disconnected` alone SHALL also show Right's hold for USB, on a black plate reading `Switch to` and the USB mark,
and a legend of `HOLD` alone, white on a black plate, ending the status row where `D_Main`'s legend ends.
`D_disc_voice` SHALL show no legend.
Every no-link board SHALL keep its two lines on the rows of `D_stopped`.

#### Scenario: Opened with no link
- **WHEN** the application opens with no Mac connected
- **THEN** a frame read off the device equals board `D_disconnected`

#### Scenario: The link drops
- **WHEN** the link drops on the idle screen
- **THEN** a frame equals `D_disconnected`, with no press

#### Scenario: The link drops during a flash
- **WHEN** the link drops while a flash runs
- **THEN** a frame equals `D_disconnected`, and stays equal past the flash's end

#### Scenario: Nothing jumps
- **WHEN** OK is released on `D_disc_voice`, or the offer stops on `D_disconnected`
- **THEN** the two lines stay on their rows

#### Scenario: The legend
- **WHEN** the owner looks at `D_disconnected` on the device
- **THEN** the status row ends in `HOLD`, white on a black plate, with no `TAP`

### Requirement: A voice cut by the link has a screen of its own
While OK stays down after a link lost during voice,
the screen SHALL show `No link`, `Reconnecting...` and `Voice stopped: release OK`.

#### Scenario: The link drops during voice
- **WHEN** the link drops during voice
- **THEN** a frame equals `D_disc_voice`

#### Scenario: OK released
- **WHEN** OK is released on that screen
- **THEN** a frame equals `D_disconnected`

#### Scenario: The link returns with OK still down
- **WHEN** the link returns on that screen
- **THEN** a frame equals `D_Main`

### Requirement: A stopped offer has a screen of its own
Once the application stops offering the link, whatever is held,
the screen SHALL show board `D_stopped` until a button is pressed:
`D_disconnected`'s status row with no legend, `Reconnect stopped`, `Any button: retry`,
and the Back mark with `exit` in a thin frame, as a tap.

#### Scenario: Stopped
- **WHEN** the application stops offering the link
- **THEN** a frame equals `D_stopped`

#### Scenario: Stopped with OK still down
- **WHEN** OK stays down on `D_disc_voice` until the application stops offering the link
- **THEN** a frame equals `D_stopped`

#### Scenario: Started over
- **WHEN** a button but Back is pressed on `D_stopped`
- **THEN** a frame equals `D_disconnected`

### Requirement: The backlight follows the offer
While the application holds or offers the link, the backlight SHALL stay on,
whatever the device's Backlight Time,
unless `options`' Backlight is `Auto`:
then it SHALL go off once that time passes with no press, and come on again at a press.
Once the application stops offering the link, the backlight SHALL go off at once, whichever the option,
and the press that starts over SHALL bring it back.
Leaving the application SHALL hand the backlight back to the device's Backlight Time.

#### Scenario: Held on
- **WHEN** the link comes up after a press on `D_stopped`, with Backlight `On`,
  and twice the device's Backlight Time passes with no press
- **THEN** the backlight is on

#### Scenario: Off on stopping
- **WHEN** the application stops offering the link
- **THEN** the backlight goes off with no press

#### Scenario: Leaving after starting over
- **WHEN** the application ends after a press on `D_stopped`,
  and twice the Backlight Time passes on the desktop with no press
- **THEN** the backlight is off

#### Scenario: Left to the device
- **WHEN** Backlight is `Auto`, and the device's Backlight Time passes on `D_Main` with no press
- **THEN** the backlight is off, and a tap on Back lights it and opens the options

#### Scenario: Held again
- **WHEN** Backlight is turned `On` again, and the Backlight Time passes with no press
- **THEN** the backlight is on

#### Scenario: Leaving after a change
- **WHEN** the application ends after Backlight was turned `Auto` and `On` again,
  and the Backlight Time passes on the desktop with no press
- **THEN** the backlight is off

### Requirement: USB has boards of its own
Once USB is taken, the status row SHALL show a USB mark where Bluetooth's boards show theirs,
`Connect the cable` in place of `Reconnecting...`,
and, on `D_usb_disconnected` alone, Right's hold for Bluetooth on a black plate reading `Switch to` and the Bluetooth mark,
with the legend of `D_disconnected`.

#### Scenario: Boards
- **WHEN** the application is on USB
- **THEN** `D_usb_main`, `D_usb_voice`, `D_usb_disconnected`, `D_usb_disc_voice` and `D_usb_stopped`
  stand in for `D_Main`, `D_voice`, `D_disconnected`, `D_disc_voice` and `D_stopped`

#### Scenario: A flash
- **WHEN** an action flashes on USB
- **THEN** its element flashes as on Bluetooth, under the USB mark

#### Scenario: On Bluetooth
- **WHEN** the application is on Bluetooth
- **THEN** no status row shows a USB mark

#### Scenario: The legend on USB
- **WHEN** the owner looks at `D_usb_disconnected` on the device
- **THEN** the status row ends in `HOLD`, white on a black plate, with no `TAP`

### Requirement: The options have boards of their own
`D_Main` SHALL show a gear in a thin frame joined to Back's plate, for the tap that opens the options.
The options SHALL show the link's mark, `Options`,
and a plate of the Back mark and `EXIT`, white on black, joined to `BACK` in a thin frame,
above a line across the display, and below it a row for each option, its name left and its value right,
the cursor's row in a frame with its value between two arrows.

#### Scenario: Vibration
- **WHEN** Back is tapped on `D_Main` with both options `On` and the cursor on `Vibration`, then Right
- **THEN** a frame equals `E_options_vibration_on`, then `E_options_vibration_off`

#### Scenario: Backlight
- **WHEN** Down is tapped on `E_options_vibration_on`, then Right
- **THEN** a frame equals `E_options_backlight_on`, then `E_options_backlight_auto`

#### Scenario: No link
- **WHEN** the link drops on `E_options_vibration_on`
- **THEN** a frame equals `E_options_no_link`

### Requirement: The battery takes the legend's place
From the first press on the idle screen until the application ends,
its status row SHALL end in the battery the firmware's status bar draws, at the same place:
its bar as long as the charge, and its lightning while the device charges.
`D_Main`, `D_usb_main` and each `D_sent_*` SHALL then show it there.

#### Scenario: The first press
- **WHEN** Back is tapped on `D_Main`, then on the options
- **THEN** a frame equals, in x 99..124 of rows 1..10, the desktop's read before the launch at the same charge,
  elsewhere `D_Main` with the legend's place clear

#### Scenario: The charge
- **WHEN** the battery shows and the charge is read
- **THEN** the bar is as wide as it gives, changed since the press or not

#### Scenario: The lightning
- **WHEN** the device charges below full, plugged in before the launch or after it
- **THEN** the battery shows the lightning as the desktop does
