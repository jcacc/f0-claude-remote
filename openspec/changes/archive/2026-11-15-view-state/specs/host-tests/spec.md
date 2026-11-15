# Spec Delta

## MODIFIED Requirements

### Requirement: The core decides which link is in use
Which of the links of `bluetooth-link` and `usb-link` the remote is on SHALL be decided in `src/core/` by the keymap,
which answers it after every event, and SHALL be named there by no action and by no call on the transport.
The keymap's suite SHALL pin when the link moves and when it stays,
and the platform SHALL put the transport on that link, as it shows it on the screen,
at the opening as after an event.

#### Scenario: Moved
- **WHEN** Right's hold fires on the no-link screen, from a press made there
- **THEN** the core answers the other link, and no action

#### Scenario: Stayed
- **WHEN** any other event comes:
  another button's event on the no-link screen, Right tapped there,
  its hold fired there from no press or from one made on another screen,
  Right held on another screen, or a change of mode
- **THEN** the core answers the link it held

#### Scenario: Named by no action and no call
- **WHEN** `git grep -l -E 'Usb|Bluetooth' -- src/core` runs
- **THEN** it prints `src/core/keymap.c` and `src/core/link.h` alone

#### Scenario: The platform follows
- **WHEN** `git grep -n 'keymap_link' -- src/platform` runs
- **THEN** it prints three lines of `app.c`:
  the one that gives the screen's state the link, at the opening as after an event,
  and the two that open the transport and set it after an event

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
- **THEN** it prints one line of `app.c`, which gives the screen's state the legend, at the opening as after an event
