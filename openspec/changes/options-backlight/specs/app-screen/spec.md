# Spec Delta

## MODIFIED Requirements

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
