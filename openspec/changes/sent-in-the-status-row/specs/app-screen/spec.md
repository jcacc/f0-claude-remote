# Spec Delta

## MODIFIED Requirements

### Requirement: A sent action flashes its element
Effort high, effort max, clear, Esc and Enter SHALL each invert the inside of their part of their element for 400 ms,
and the four arrows theirs for 100 ms,
with the element's frame unchanged.

#### Scenario: The long flash
- **WHEN** one of the five acts
- **THEN** a frame read off the device equals its board,
  `D_sent_high`, `D_sent_max`, `D_sent_clear`, `D_sent_esc` or `D_sent_enter`,
  and 400 ms later one equals it with the flash gone

#### Scenario: The short flash
- **WHEN** an arrow acts
- **THEN** a frame read off the device equals `D_sent_up`, `D_sent_down`, `D_sent_left` or `D_sent_right`,
  and 100 ms later one equals it with the flash gone

#### Scenario: Only the half that acted flashes
- **WHEN** an action of Up, Down, Left, Right or OK flashes
- **THEN** the other half of its element does not change

#### Scenario: Acting again restarts it
- **WHEN** an action flashes while a flash runs
- **THEN** that action's flash shows and lasts its own duration from then on

#### Scenario: A series of arrow taps
- **WHEN** Up is tapped 5 times a second
- **THEN** frames read off the device alternate `D_sent_up` with its flash and without it, once per tap,
  and the owner sees each flash apart

#### Scenario: Voice takes over
- **WHEN** voice starts while a flash runs and stays on past its end
- **THEN** the voice screen shows throughout

## ADDED Requirements

### Requirement: The status row names the action sent
From an action's flash on, the main screen's status row SHALL read `Sent:` and the action's label, as the ring draws it,
in place of `Connected`, for 3 s or until another action is sent:
one that flashes takes the row for 3 s of its own, and the start of voice leaves it to `Connected`.

#### Scenario: Three seconds
- **WHEN** an action flashes, and no other is sent
- **THEN** the row names it for 3 s from the flash's start, and a frame then equals `D_Main`

#### Scenario: Another action
- **WHEN** Down is tapped while the row names Up's tap
- **THEN** a frame equals `D_sent_down`, and none equals `D_Main` until 3 s after Down's tap

#### Scenario: Voice
- **WHEN** voice starts while the row names an action, and stops before its 3 s pass
- **THEN** a frame equals `D_Main`
