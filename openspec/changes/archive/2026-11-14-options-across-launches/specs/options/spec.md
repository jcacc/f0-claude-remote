# Spec Delta

## MODIFIED Requirements

### Requirement: Vibration can be turned off
The options SHALL hold Vibration, `On` or `Off`, and it SHALL be `On` until it is changed.
While it is `Off` no action SHALL vibrate the device, and each SHALL act and flash as with it `On`.
A change SHALL hold from the next action, and across launches, until the next change.

#### Scenario: Off
- **WHEN** Vibration is `Off`, and Up is tapped on `D_Main`
- **THEN** the up arrow acts, a frame equals `D_sent_up`, and the device does not vibrate

#### Scenario: On again
- **WHEN** Vibration is `On` again, and Up is tapped on `D_Main`
- **THEN** the device vibrates once

#### Scenario: Opened again
- **WHEN** the application ends with Vibration `Off` and opens again
- **THEN** the options show Vibration `Off`

## ADDED Requirements

### Requirement: The options are kept on the SD card
A change of an option SHALL be written at once to `apps_data/f0_claude_remote/options.txt` on the SD card,
as text: the file's type, its version and a line for each option.
No other event SHALL write the file.
The application SHALL open with the options a file of this type and version gives,
and with every other option as it is by default.
A file that cannot be written SHALL change nothing else.

#### Scenario: Written
- **WHEN** Vibration is turned `Off` on the options, then `On`
- **THEN** the file reads `Filetype: Claude Remote Options`, `Version: 1` and `Vibration: false`, a line each,
  then the same with `Vibration: true`

#### Scenario: Left at once
- **WHEN** Vibration is changed, and Back is held at once until the application ends
- **THEN** the file holds the new value, whole

#### Scenario: Nothing to write
- **WHEN** the application opens with no file, and the options are opened and closed
- **THEN** they show Vibration `On`, and there is still no file

#### Scenario: Another file
- **WHEN** the application opens on a file of another type, of another version, or with no line for Vibration
- **THEN** the options show Vibration `On`, and the next change writes the file whole

#### Scenario: Not written
- **WHEN** a folder stands in the file's place, and Vibration is changed
- **THEN** the options show the new value, and the next launch opens with Vibration `On`
