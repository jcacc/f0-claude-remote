# Spec Delta

## MODIFIED Requirements

### Requirement: The core decides when the legend ends
Whether the main screen's status row ends in the legend or in the battery of `app-screen`
SHALL be decided in `src/core/` by the keymap, which answers it after every event.
The keymap's suite SHALL pin what ends the legend and what leaves it,
and the platform SHALL show the row's end by that answer alone, at the opening as after an event.

#### Scenario: Opened
- **WHEN** a keymap opens, and when its link comes up
- **THEN** the core answers the legend

#### Scenario: Ended
- **WHEN** a button goes down on the main screen, on either link
- **THEN** the core answers the battery,
  and still does once voice, the options, a lost link or a stopped offer has come and gone

#### Scenario: Left
- **WHEN** any other event comes before that press:
  a press, tap or hold on a no-link board or on the stopped screen,
  the release or the tap, on the main screen, of a button that went down before the link came up,
  a link report, or the wait's end
- **THEN** the core answers the legend

#### Scenario: The platform follows
- **WHEN** `git grep -n 'keymap_legend' -- src/platform` runs
- **THEN** it prints one line of `app.c`, which gives the screen's state the legend, at the opening as after an event
