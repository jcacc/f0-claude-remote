# Proposal

## Why

What a frame shows crosses the application as loose words.
`view_draw` takes nine parameters (`src/ui/view.h:10-19`);
`Screen` keeps a word for each value, eight `_Atomic` fields, with a setter for seven
(`src/platform/screen.c:12-19`, `screen.h:21-33`);
and `app.c` calls them one by one (`:75-85`, `:118`, `:126`), each asking for a frame of its own:
nine `view_port_update` in `screen.c`, six of them per event.
`charging`, the last value added (`fbf98ca`), stands on 13 lines of seven files
between the queue's callback and the component that draws it.
The canvas's backlog still holds `Sent:` in the status row (`backlogMain`, item 1), one more value on every list,
and `battery-in-the-status-row` left the list as "a change of its own"
(`openspec/changes/archive/2026-11-15-battery-in-the-status-row/design.md:42-43`).

Decisions:

- **What a frame shows becomes one state, `ViewState`, which the UI names and every board draws from,**
  not a shorter list of parameters:
  a value added to a board then stands in the type, in that board and where it is set, alone.
- **`screen` keeps one copy of it behind a mutex, set whole and copied whole,**
  not an `_Atomic` word for each value, `app-keymap`'s choice for two words with no invariant between them
  (`openspec/changes/archive/2026-11-04-app-keymap/design.md:63-66`):
  nine words cross now, read one by one between an event's six updates, and a state set whole is read whole.
- **`app.c` reads what the screen shows, changes its part and sets it whole,**
  not a setter for each value, which is the list again.
- **Nothing a user meets changes:**
  every board, the flash, the file and the buzz stay, so `app-screen` and `options` stand,
  and the specs change by what `git grep` shows of the sources alone.
- **No file of the UI is renamed here,** though the owner asked on 2026-11-15 for a `view_main`:
  a rename is proved by version control showing each moved file as one (`openspec/config.yaml`, Housekeeping),
  and this change rewrites the one declaration `view_idle.h` holds;
  with the requirement that names `view_idle.c`, `host-tests`' delta would run to 650 words against 550.
  The names get a plan of their own, on this one.
- **The owner's hand taps Up once, on a scratch Claude Code session, for the flash,**
  not a tap sent over RPC:
  a tap that acts sends its key to the Mac's focused window.
  Every other frame is read over RPC through taps that send no key and do not buzz
  (`openspec/specs/options/spec.md:11`, `:63`).
- **Complex, so implemented on `feature/view-state`:**
  the hand-over between two threads changes its mechanism, across the UI and the platform, under three spec documents.
- **It builds on `develop` alone:** no plan is queued.
- **It lands as `refactor(view): draw a frame from one state`.**

## What Changes

- The UI names what a frame shows as one state, and its draw calls take it whole.
- The screen keeps one copy of that state for both threads, with one setter in its header.
- `app.c` gives the state the keymap's answers in one place, at the opening as after an event.
- The architecture page follows; every board, the flash, the file and the buzz stay as they are.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `source-layers`: what a frame shows crosses from the platform to the UI as one state, kept as one copy.
- `host-tests`: the screen takes the link and the legend within its state, so `app.c` names each on fewer lines.
- `options-state`: the screen takes the options and the cursor within its state, apart from the card.

## Impact

`src/ui/view_state.h`, new; `src/ui/view.h`, `view.c`, `view_idle.h`, `view_idle.c`, `view_options.h` and `view_options.c`;
`src/platform/screen.h`, `screen.c` and `app.c`;
`docs/internals/architecture.md`.
The core and its suites, `view_plate.c`, the transport, `battery.c`, `backlight.c`, `options_file.c`, `README.md`,
the rest of `docs/` and `catalog/` stay as they are.
