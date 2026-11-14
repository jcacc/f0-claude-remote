# Spec Delta

## ADDED Requirements

### Requirement: The core decides when the legend ends
Whether the idle screen's status row ends in the legend or in the battery of `app-screen`
SHALL be decided in `src/core/` by the keymap, which answers it after every event.
The keymap's suite SHALL pin what ends the legend and what leaves it,
and the platform SHALL show the row's end by that answer alone, at the opening as after an event.

#### Scenario: Opened
- **WHEN** a keymap opens, and when its link comes up
- **THEN** the core answers the legend

#### Scenario: Ended
- **WHEN** a button goes down on the idle screen, on either link
- **THEN** the core answers the battery,
  and still does once voice, the options, a lost link or a stopped offer has come and gone

#### Scenario: Left
- **WHEN** any other event comes before that press:
  a press, tap or hold on a no-link board or on the stopped screen,
  the release or the tap, on the idle screen, of a button that went down before the link came up,
  a link report, or the wait's end
- **THEN** the core answers the legend

#### Scenario: The platform follows
- **WHEN** `git grep -n 'keymap_legend' -- src/platform` runs
- **THEN** it prints two lines of `app.c`: the one that opens the screen, and the one that sets it after an event

### Requirement: The core says how many cells a charge fills
How many cells of `app-screen`'s battery a charge fills SHALL be decided in `src/core/`:
as many of the cells as the charge is of full, a part of a cell counting as one,
and every cell from a full charge on.
A suite of its own SHALL pin it, and the UI SHALL size the bar by that answer alone.

#### Scenario: Rounded up
- **WHEN** the core is asked how many of 8 cells a charge of 1, 12, 13, 75, 76 or 87 % fills
- **THEN** it answers 1, 1, 2, 6, 7 and 7

#### Scenario: Empty and full
- **WHEN** the charge is 0 %, 88 %, 100 %, or a reading past 100
- **THEN** it answers no cell for the first, and all 8 for each of the others

#### Scenario: By that answer alone
- **WHEN** `git grep -n 'charge_cells' -- src/ui src/platform` runs
- **THEN** it prints one line of `view_idle.c`
