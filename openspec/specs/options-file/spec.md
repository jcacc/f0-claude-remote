# options-file Specification

## Purpose
Keeps the options' values in a file on the SD card,
so the application opens with them at the next launch.

## Requirements

### Requirement: The options are kept on the SD card
A change of an option SHALL be written at once to `apps_data/f0_claude_remote/options.txt` on the SD card,
as text: the file's type, its version and a line for each option.
No other event SHALL write the file.
The application SHALL open with the options a file of this type and version gives,
and with every other option as it is by default.
A file that cannot be written SHALL change nothing else.

#### Scenario: Written
- **WHEN** Backlight is turned `Auto` on the options, then `On`
- **THEN** the file reads `Filetype: Claude Remote Options`, `Version: 1`, `Vibration: true` and `Backlight: false`, a line each,
  then the same with `Backlight: true`

#### Scenario: Left at once
- **WHEN** an option is changed, and Back is held at once until the application ends
- **THEN** the file holds the new value, whole

#### Scenario: Nothing to write
- **WHEN** the application opens with no file, and the options are opened, the cursor moved, and the options closed
- **THEN** they show Vibration `On` and Backlight `On`, and there is still no file

#### Scenario: Another file
- **WHEN** the application opens on a file of another type or version, or on one with a line for one option alone
- **THEN** the options show every option `On` but the one such a line gives, and the next change writes the file whole

#### Scenario: Not written
- **WHEN** a folder stands in the file's place, and Vibration is changed
- **THEN** the options show the new value, and the next launch opens with Vibration `On`
