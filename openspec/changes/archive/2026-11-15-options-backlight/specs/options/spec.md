# Spec Delta

## ADDED Requirements

### Requirement: On the options the arrows and Back act
On the options a tap on Up or Down SHALL move the cursor to the other row,
a tap on Left or Right SHALL give the option under the cursor its other value,
holding Back SHALL end the application,
and no gesture but these and Back's tap SHALL do anything.
None SHALL send a key, vibrate the device or flash.
The cursor SHALL stand on `Vibration` when the application opens,
and SHALL move on a tap of Up or Down on the options alone.

#### Scenario: The cursor
- **WHEN** the options open for the first time since the launch, and Up is tapped, then Down
- **THEN** the cursor's frame stands on `Vibration`, on `Backlight`, then on `Vibration`

#### Scenario: A value
- **WHEN** Left or Right is tapped on the options
- **THEN** the row under the cursor shows its other value, and the other row the value it had

#### Scenario: Every other gesture
- **WHEN** OK is tapped and held on the options, and Up, Down, Left and Right are held
- **THEN** the options do not change, voice does not start, and no key is sent

#### Scenario: Exit
- **WHEN** Back is held on the options until the long press fires
- **THEN** the application ends

#### Scenario: The cursor stays
- **WHEN** the cursor stands on `Backlight`, and the options are closed and opened again
- **THEN** the cursor's frame stands on `Backlight`

### Requirement: Backlight can be left to the device
The options SHALL hold Backlight, `On` or `Auto`, and it SHALL be `On` until it is changed.
`On` SHALL keep the backlight on and `Auto` leave it to the device's Backlight Time,
each as `app-screen`'s `The backlight follows the offer` says.
A change SHALL hold at once, and across launches, until the next change.

#### Scenario: Opened again
- **WHEN** the application ends with Backlight `Auto` and opens again
- **THEN** the options show Backlight `Auto`

## REMOVED Requirements

### Requirement: On the options only Left, Right and Back act
**Reason**: Up and Down act there now, moving the cursor between the two rows.
**Migration**: `On the options the arrows and Back act` replaces it, with Left, Right and Back as they were.

### Requirement: The options are kept on the SD card
**Reason**: How the options are kept, the path, the format and a file the application cannot use, is a capability apart from what they do.
**Migration**: `options-file` holds the requirement, with a line for each option.
