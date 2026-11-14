# Spec Delta

## ADDED Requirements

### Requirement: The options have boards of their own
`D_Main` SHALL show a gear in a thin frame joined to Back's plate, for the tap that opens the options.
The options SHALL show the link's mark, `Options`,
and a plate of the Back mark and `EXIT`, white on black, joined to `BACK` in a thin frame,
above a line across the display, and below it a row for each option, its name left and its value right,
the cursor's row in a frame with its value between two arrows.
Until `Backlight` joins the options, its row SHALL stay empty.

#### Scenario: Vibration
- **WHEN** Back is tapped on `D_Main`, then Right
- **THEN** a frame equals `E_options_vibration_on`, then `E_options_vibration_off`, each but for its `Backlight` row

#### Scenario: No link
- **WHEN** the link drops on the options
- **THEN** a frame equals `E_options_no_link`, but for its `Backlight` row

## MODIFIED Requirements

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
