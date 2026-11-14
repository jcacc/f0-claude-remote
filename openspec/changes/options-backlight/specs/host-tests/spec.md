# Spec Delta

## MODIFIED Requirements

### Requirement: Every mode is asked how long it waits
The core SHALL say how long each mode waits for a link in a `switch` over the modes,
so `mise run test` fails at a mode nobody has asked.

#### Scenario: A mode not asked
- **WHEN** an enumerator is added to the enum in `src/core/mode.h`,
  and to no switch but the one that says what light a mode gives the display,
  and `mise run test` runs
- **THEN** it exits non-zero and names that enumerator at the switch that says how long a mode waits

### Requirement: The core decides when the display is lit
Whether the backlight of `app-screen`'s `The backlight follows the offer` is held on, left to the device or off
SHALL be decided in `src/core/`,
which says it of each mode, in a `switch` over the modes, given `options`' Backlight.
A suite of its own SHALL pin that answer for every mode and either value,
and the platform SHALL light and darken the display by it alone, at the opening as after it,
naming no action for the light.

#### Scenario: Lit
- **WHEN** the mode holds the link or offers it: idle, voice, no link, a voice cut by the link, or the options, with a link or with none,
  and Backlight is `On`
- **THEN** the core answers that the display is held lit

#### Scenario: Left to the device
- **WHEN** the mode is one of those six, and Backlight is `Auto`
- **THEN** the core answers that the display is left to the device

#### Scenario: Dark
- **WHEN** the mode is the one of a stopped offer, with Backlight `On` or `Auto`
- **THEN** the core answers that the display is dark

#### Scenario: No action named for the light
- **WHEN** `git grep -n -E 'ActionGiveUp|ActionStartOver' -- src/platform` runs
- **THEN** it prints nothing

#### Scenario: The opening
- **WHEN** `git grep -n 'display_light' -- src/platform` runs
- **THEN** it prints two lines of `app.c`: the one that opens the backlight, and the one that sets it after an event

#### Scenario: A mode not asked
- **WHEN** an enumerator is added to the enum in `src/core/mode.h`, and to no switch, and `mise run test` runs
- **THEN** it exits non-zero and names that enumerator at the switch that says what light a mode gives the display

## REMOVED Requirements

### Requirement: The core holds the options' values
**Reason**: With the cursor and a second option, what the core holds of the options is a capability of its own.
**Migration**: `options-state` holds the requirement, with the cursor's row beside the values.

### Requirement: The core takes the options the card holds
**Reason**: It goes with the values it hands the core.
**Migration**: `options-state` holds the requirement, for every option.
