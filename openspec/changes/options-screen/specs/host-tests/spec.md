# Spec Delta

## ADDED Requirements

### Requirement: The core holds the options' values
The value of each of `options`' options SHALL be held in `src/core/` by the keymap, which answers it after every event,
and whether an action vibrates the device SHALL be decided there from that value.
The keymap's suite SHALL pin when the value changes and when it stays,
the feedback's suite the buzz for either value,
and the platform SHALL show the value and buzz by those answers alone, at the opening as after an event.

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
- **WHEN** `git grep -n 'keymap_vibration' -- src/platform` runs
- **THEN** it prints three lines of `app.c`:
  the one that opens the screen, the one that sets it after an event, and the one that asks about the buzz

## MODIFIED Requirements

### Requirement: The core decides when the display is lit
Whether the backlight of `app-screen`'s `The backlight follows the offer` is on SHALL be decided in `src/core/`,
which says of each mode, in a `switch` over the modes, whether it keeps the display lit.
A suite of its own SHALL pin that answer for every mode,
and the platform SHALL light and darken the display by it alone, at the opening as after it,
naming no action for the light.

#### Scenario: Lit
- **WHEN** the mode holds the link or offers it: idle, voice, no link, a voice cut by the link, or the options, with a link or with none
- **THEN** the core answers that the display is lit

#### Scenario: Dark
- **WHEN** the mode is the one of a stopped offer
- **THEN** the core answers that the display is dark

#### Scenario: No action named for the light
- **WHEN** `git grep -n -E 'ActionGiveUp|ActionStartOver' -- src/platform` runs
- **THEN** it prints nothing

#### Scenario: The opening
- **WHEN** `git grep -n 'display_lit' -- src/platform` runs
- **THEN** it prints two lines of `app.c`: the one that opens the backlight, and the one that sets it after an event

#### Scenario: A mode not asked
- **WHEN** an enumerator is added to the enum in `src/core/mode.h`, and to no switch, and `mise run test` runs
- **THEN** it exits non-zero and names that enumerator at the switch that says whether a mode keeps the display lit
