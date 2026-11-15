# Spec Delta

## MODIFIED Requirements

### Requirement: The core decides when the display is lit
Whether the backlight of `app-screen`'s `The backlight follows the offer` is held on, left to the device or off
SHALL be decided in `src/core/`,
which says it of each mode, in a `switch` over the modes, given `options`' Backlight.
A suite of its own SHALL pin that answer for every mode and either value,
and the platform SHALL light and darken the display by it alone, at the opening as after it,
naming no action for the light.

#### Scenario: Lit
- **WHEN** the mode holds the link or offers it: main, voice, no link, a voice cut by the link, or the options, with a link or with none,
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

### Requirement: The core says how many cells a charge fills
How many cells of `app-screen`'s battery a charge fills SHALL be decided in `src/core/`:
as many of the cells as the charge is of full, a part of a cell counting as one,
and every cell from a full charge on.
A suite of its own SHALL pin it, and the UI SHALL size the bar by that answer alone.

#### Scenario: Rounded up
- **WHEN** the core is asked how many of 20 cells a charge of 1, 5, 6, 94 or 95 % fills
- **THEN** it answers 1, 1, 2, 19 and 19

#### Scenario: Empty and full
- **WHEN** the charge is 0 %, 96 %, 100 %, or a reading past 100
- **THEN** it answers no cell for the first, and all 20 for each of the others

#### Scenario: By that answer alone
- **WHEN** `git grep -n 'charge_cells' -- src/ui src/platform` runs
- **THEN** it prints one line of `view_main.c`
