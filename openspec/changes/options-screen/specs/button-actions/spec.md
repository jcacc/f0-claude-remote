# Spec Delta

## MODIFIED Requirements

### Requirement: An action confirms itself with one buzz
Enter, the four arrows, Esc, effort high, effort max, clear and the start of voice
SHALL each vibrate the device once, for 100 ms, unless `options`' Vibration is `Off`.

#### Scenario: An action
- **WHEN** one of them acts with Vibration `On`
- **THEN** the device vibrates once

#### Scenario: The silent rest
- **WHEN** voice stops, exit acts, or Back is tapped
- **THEN** the device does not vibrate

### Requirement: With no link only holding Back or Right acts
With no link and the options closed, holding Back SHALL exit,
holding Right on `D_disconnected` or `D_usb_disconnected` SHALL switch the link, as `usb-link` and `bluetooth-link` say,
and no other press SHALL act, vibrate or flash,
so, with Vibration `On`, a press with no buzz was not sent;
`D_stopped` alone answers a press otherwise, as its requirements say.

#### Scenario: Every other press
- **WHEN** the link is offered with none up and the options are closed, every button but Back and Right is tapped and held, and Back and Right are tapped
- **THEN** nothing acts, the device does not vibrate and the screen does not change

#### Scenario: Exit
- **WHEN** there is no link and Back is held until the long press fires
- **THEN** the application ends

#### Scenario: The link returns
- **WHEN** the link returns and Up is tapped
- **THEN** the up arrow acts

### Requirement: Each button acts on a tap or a hold
With the link up and the options closed, a tap, released before the device's long press fires, and a hold, kept until it fires,
SHALL take the actions in the scenarios below, once each, as far as `A tap or hold acts on the screen it began on` allows,
and nothing else SHALL act.

#### Scenario: Tap
- **WHEN** Up, Down, Left, Right or OK is tapped
- **THEN** the up, down, left or right arrow, or Enter, acts, on the release

#### Scenario: Hold
- **WHEN** Up, Down, Left, Right or Back is held
- **THEN** effort high, effort max, clear, Esc or exit acts when the long press fires

#### Scenario: A hold does not repeat
- **WHEN** Up stays down for 2 seconds after its long press fired
- **THEN** effort high has acted once

#### Scenario: Nothing acts on the press
- **WHEN** a button goes down
- **THEN** nothing acts before its release or its long press

#### Scenario: A tap with no action
- **WHEN** Back is tapped
- **THEN** nothing acts, and the options open, as `options` says
