# Spec Delta

## MODIFIED Requirements

### Requirement: The screen shows the status and every button's action
The idle screen, with the link up, voice off and no flash running, SHALL show a status row above a ring of the device's buttons,
with a thin frame on every action taken by a press,
a black plate on every held one,
and, until a button is pressed on it, a legend saying so.
The ring and Back's plate SHALL stand in one outline, shaped as the recess the device's case has around its buttons.

#### Scenario: Status row
- **WHEN** the screen is idle, before a press on it
- **THEN** the top row reads, left to right,
  a Bluetooth mark, `Connected`, and a legend of `HOLD` joined to `TAP`,
  above a line across the display

#### Scenario: Legend
- **WHEN** the screen is idle
- **THEN** a ring holds an element split by a diagonal,
  a microphone at its upper left and an Enter arrow at its lower right,
  with `/effort high` and an up arrow at the ring's top,
  `/clear` and a left arrow on its left,
  a right arrow and `Esc` on its right,
  `/effort max` and a down arrow at its bottom,
  and a Back mark and `exit` under `Esc`

#### Scenario: The recess
- **WHEN** the screen is idle
- **THEN** one outline holds the split element and Back's plate, and passes under the ring's four plates:
  round about the ring, then narrowing to a round end past Back's plate, with a level bottom,
  and no line of it inside a plate

#### Scenario: Hold and press read apart
- **WHEN** the screen is idle, before a press on it
- **THEN** `HOLD`, `/effort high`, `/effort max`, the microphone, `/clear`, `Esc`, `exit` and the Back mark stand white on a black plate,
  and `TAP`, the four arrows and the Enter arrow stand black in a thin frame

#### Scenario: The board
- **WHEN** the link comes up with voice off and no flash running, before a press on the idle screen
- **THEN** a frame read off the device equals board `D_Main`

#### Scenario: Nothing clipped
- **WHEN** the application is open, in any state
- **THEN** every label is whole and stands clear of its neighbors

## ADDED Requirements

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
