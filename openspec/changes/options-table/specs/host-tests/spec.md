# Spec Delta

## MODIFIED Requirements

### Requirement: The core holds the options' values
The value of each of `options`' options SHALL be held in `src/core/` by the keymap, which answers it after every event,
and whether an action vibrates the device SHALL be decided there from that value.
The keymap's suite SHALL pin when the value changes and when it stays,
the feedback's suite the buzz for either value,
and the platform SHALL show the value, keep it on the SD card and buzz by those answers alone, at the opening as after an event.
Every unit SHALL reach an option by its name among the options, and no function SHALL be named for one option.

#### Scenario: Changed
- **WHEN** Left or Right is tapped on the options, from a press made there
- **THEN** the core answers Vibration's other value, and no action

#### Scenario: Stayed
- **WHEN** any other event comes:
  another gesture on the options, a tap begun there before the link changed,
  a tap or hold on another screen, or a change of mode
- **THEN** the core answers the value it held

#### Scenario: The buzz
- **WHEN** the core is asked whether an action vibrates the device
- **THEN** it answers yes for each action of `button-actions`' `An action confirms itself with one buzz` with Vibration `On`,
  and no for every action with it `Off`

#### Scenario: The platform follows
- **WHEN** `git grep -n 'keymap_option' -- src/platform` runs
- **THEN** it prints three lines of `app.c`:
  the one that hands the card its fallback at the opening,
  the one that follows the options, at the opening as after an event,
  and the one that asks about the buzz

#### Scenario: No function of one option
- **WHEN** `git grep -n -E '_vibration\(' -- src` runs
- **THEN** it prints nothing

### Requirement: The core takes the options the card holds
The keymap SHALL open with each of `options`' options as it is by default,
and SHALL take from the platform, once, at the opening, the value read from the SD card, moving nothing else.
The keymap's suite SHALL pin both.

#### Scenario: Opened
- **WHEN** a keymap opens
- **THEN** it answers Vibration `On`

#### Scenario: Taken from the card
- **WHEN** a keymap just opened is handed a saved Vibration, `Off` and then `On`
- **THEN** it answers each in turn, and the mode, the link and the wait it opened with

#### Scenario: Handed once
- **WHEN** `git grep -n 'keymap_set_option' -- src/platform` runs
- **THEN** it prints one line of `app.c`
