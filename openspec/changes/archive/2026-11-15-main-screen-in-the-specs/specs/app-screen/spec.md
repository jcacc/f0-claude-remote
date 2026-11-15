# Spec Delta

## MODIFIED Requirements

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
- **WHEN** the link drops on the main screen
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

### Requirement: The battery takes the legend's place
From the first press on the main screen until the application ends,
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
