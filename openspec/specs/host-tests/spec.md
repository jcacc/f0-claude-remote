# host-tests Specification

## Purpose

Proves the remote's logic on the Mac, with no device and no Flipper SDK,
so a failure names the broken rule before anything reaches the hardware.

## Requirements

### Requirement: A task runs the tests on the host
`mise run test` SHALL build every suite under `test/` with the system `cc`,
Flipper's warnings as errors and the address and undefined-behavior sanitizers,
and run it. It is the one task that needs a compiler from outside the project.

#### Scenario: Green
- **WHEN** `mise run test` runs with no device attached
- **THEN** it exits 0 and prints one `ok <name>` line per test

#### Scenario: A failing test
- **WHEN** an assertion fails and the output is piped
- **THEN** the task exits non-zero, names the assertion's file and line,
  and the `ok` lines before it are all there

### Requirement: The logic needs no SDK
The sources under test, all of `src/core/`, SHALL include no Flipper header.

#### Scenario: Includes
- **WHEN** `git grep -E '#include <(furi|gui|input|notification)' -- src/core` runs
- **THEN** it prints nothing

### Requirement: Tests stay out of the package
`test/` SHALL build into no package, and SHALL stay under the linter.

#### Scenario: Package
- **WHEN** `mise run build` runs
- **THEN** `compile_commands.json` lists no path under `test/`

#### Scenario: Lint
- **WHEN** a `.c` file under `test/` breaks Flipper's format and `mise exec -- ufbt lint` runs
- **THEN** it exits non-zero and names that file

### Requirement: The core decides when the wait is counted
What the 60 s of `bluetooth-link` and `usb-link` are counted from, and what ends the count,
SHALL be decided in `src/core/`, which answers every event with what the count does:
it starts, it stops, or it stays as it is.
The keymap's suite SHALL pin that answer,
and the platform SHALL start and stop its timer by it alone, keeping no count of its own.

#### Scenario: Started
- **WHEN** the application opens, the link drops, a press starts over on the stopped screen, or Right's hold switches the link
- **THEN** the core answers that the count starts

#### Scenario: Stopped
- **WHEN** the link comes up, or the 60 s end
- **THEN** the core answers that the count stops

#### Scenario: Left as it is
- **WHEN** any other event comes:
  a button event with no link, a drop reported again, OK released after a cut,
  or an event with the link up or on the stopped screen that starts nothing over
- **THEN** the core answers that the count stays as it is

#### Scenario: Nothing counted in the platform
- **WHEN** `git grep -n 'wait_ms[^(]' -- src/platform` runs
- **THEN** it prints nothing

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

### Requirement: The core decides when the lightning shows at the opening
Whether `app-screen`'s battery opens with its lightning SHALL be decided in `src/core/`:
while the device charges, below a full charge, before the charger is done.
A suite of its own SHALL pin it, and the platform SHALL open the battery by that answer alone.

#### Scenario: Charging
- **WHEN** the device charges at 0 or 99 %, the charger not done
- **THEN** the core answers the lightning

#### Scenario: Not charging
- **WHEN** the device does not charge, charges at 100 %, or the charger is done
- **THEN** the core answers none

#### Scenario: By the opening's answer alone
- **WHEN** `git grep -n 'charging_now' -- src/ui src/platform` runs
- **THEN** it prints one line of `battery.c`
