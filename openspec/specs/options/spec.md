# options Specification

## Purpose
Lets the owner change how the remote behaves from the device itself,
on a screen of options that a tap on Back opens from the main screen.

## Requirements

### Requirement: A tap on Back opens and closes the options
A tap on Back on `D_Main` SHALL open the options, and a tap on Back on the options SHALL close them,
each with no buzz, no flash and no key sent.
On any other board a tap on Back SHALL open nothing.

#### Scenario: Opened
- **WHEN** Back is tapped on `D_Main`
- **THEN** the options show, the device does not vibrate, and no key is sent

#### Scenario: Closed
- **WHEN** Back is tapped on the options with the link up
- **THEN** `D_Main` shows

### Requirement: On the options only Left, Right and Back act
On the options a tap on Left or Right SHALL give the option under the cursor its other value,
holding Back SHALL end the application,
and no gesture but these and Back's tap SHALL do anything.
None SHALL send a key, vibrate the device or flash.

#### Scenario: A value
- **WHEN** Left or Right is tapped on the options
- **THEN** the row under the cursor shows its other value

#### Scenario: Every other gesture
- **WHEN** Up, Down and OK are tapped and held on the options, and Left and Right are held
- **THEN** the options do not change, voice does not start, and no key is sent

#### Scenario: Exit
- **WHEN** Back is held on the options until the long press fires
- **THEN** the application ends

### Requirement: Vibration can be turned off
The options SHALL hold Vibration, `On` or `Off`, and it SHALL be `On` when the application opens.
While it is `Off` no action SHALL vibrate the device, and each SHALL act and flash as with it `On`.
A change SHALL hold from the next action until the application ends.

#### Scenario: Off
- **WHEN** Vibration is `Off`, and Up is tapped on `D_Main`
- **THEN** the up arrow acts, a frame equals `D_sent_up`, and the device does not vibrate

#### Scenario: On again
- **WHEN** Vibration is `On` again, and Up is tapped on `D_Main`
- **THEN** the device vibrates once

#### Scenario: Opened again
- **WHEN** the application opens
- **THEN** Vibration is `On`

### Requirement: The options outlast a lost link
A link lost on the options SHALL leave them open under the no-link mark,
and its return SHALL bring the link's mark back.
With no link a tap on Back SHALL show `D_disconnected`,
and 60 s after the drop `D_stopped` SHALL take the options' place.
Vibration SHALL keep its value throughout.

#### Scenario: Dropped and back
- **WHEN** the Mac's settings disconnect the device on the options, and the Mac connects again by itself
- **THEN** the options show the no-link mark, then the link's, with no press

#### Scenario: Closed with no link
- **WHEN** the link drops on the options, and Back is tapped
- **THEN** `D_disconnected` shows, and `D_stopped` 60 s after the drop

#### Scenario: Stopped
- **WHEN** 60 s pass with no link from a drop on the options
- **THEN** `D_stopped` shows, and Vibration keeps its value
