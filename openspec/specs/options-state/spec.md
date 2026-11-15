# options-state Specification

## Purpose
Holds the options' values and their cursor in the core,
where the host suites pin them, with the platform only following.

## Requirements

### Requirement: The core holds the options' values
The value of each of `options`' options, and the row their cursor stands on,
SHALL be held in `src/core/` by the keymap, which answers them after every event,
and whether an action vibrates the device SHALL be decided there from Vibration's value.
The keymap's suite SHALL pin when a value or the cursor changes and when each stays,
and the feedback's suite the buzz for either value.

#### Scenario: Changed
- **WHEN** Left or Right is tapped on the options, from a press made there
- **THEN** the core answers the other value of the option under the cursor,
  the other option and the cursor as they were, and no action

#### Scenario: The cursor
- **WHEN** Up or Down is tapped on the options, from a press made there
- **THEN** the core answers the other row, every value as it was, and no action

#### Scenario: Stayed
- **WHEN** any other event comes:
  another gesture on the options, a tap begun there before the link changed,
  a tap or hold on another screen, or a change of mode
- **THEN** the core answers the values and the row it held

#### Scenario: The buzz
- **WHEN** the core is asked whether an action vibrates the device
- **THEN** it answers yes for each action of `button-actions`' `An action confirms itself with one buzz` with Vibration `On`,
  and no for every action with it `Off`

### Requirement: The platform follows the options
The platform SHALL show the options and their cursor, keep the values on the SD card and buzz
by the core's answers alone, at the opening as after an event.
Every unit SHALL reach an option by its name among the options,
through no function named for one option and no comparison with an enumerator.

#### Scenario: The platform follows
- **WHEN** `git grep -n -E 'keymap_(option|cursor)' -- src/platform` runs
- **THEN** it prints six lines of `app.c`:
  one hands the card its fallback, two give the backlight its light,
  two follow the cursor and the options, and one asks about the buzz

#### Scenario: By its name alone
- **WHEN** `git grep -n -E '_(vibration|backlight)\(|(==|!=) Option' -- src` runs
- **THEN** it prints nothing

### Requirement: The core takes the options the card holds
The keymap SHALL open with each of `options`' options as it is by default,
and SHALL take from the platform, once, at the opening, the value read from the SD card, moving nothing else.
The keymap's suite SHALL pin both.

#### Scenario: Opened
- **WHEN** a keymap opens
- **THEN** it answers every option `On`, and the cursor on `Vibration`

#### Scenario: Taken from the card
- **WHEN** a keymap just opened is handed a saved value of each option, its other one and then `On`
- **THEN** it answers each in turn, and the other option, the cursor, the mode, the link and the wait it opened with

#### Scenario: Handed once
- **WHEN** `git grep -n 'keymap_set_option' -- src/platform` runs
- **THEN** it prints one line of `app.c`
