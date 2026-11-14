# Proposal

## Why

Vibration crosses the application as a `bool` of its own:
five functions carry its name
(`keymap_vibration`, `keymap_set_vibration`, `screen_set_vibration`, `options_file_vibration`, `options_file_set_vibration`),
and 49 lines of eleven files outside `feedback` spell it (`git grep -c -i vibration -- src`).
Backlight, the options' second row (`openspec/specs/app-screen/spec.md:249`), would add a second set of each,
and its cursor a branch on the option in the keymap and in the view.
The owner asked on 2026-11-14 for Backlight as two changes, this one first:
planned as one, its design ran to 1094 words against the 880 `openspec/config.yaml` allows.

Decisions:

- **An option becomes an enumerator of `Option`, and every unit reaches it by that name,**
  not a second set of functions written beside Vibration's once Backlight comes:
  that set is what the cursor would branch over.
- **The table holds Vibration alone, a single row,**
  not Backlight with it:
  Backlight's change adds its enumerator and its rows.
- **The cursor and a table of the view's rows stay with Backlight,**
  not built ahead:
  with one option nothing would read them.
- **Nothing a user meets changes:**
  every board, the file's three lines and the buzz stay,
  so no requirement of `options` or `app-screen` does,
  and `host-tests` alone names the functions that go.
- **The device checks take no hand of the owner's:**
  the walks of `options-across-launches` run again, over RPC and the console,
  through taps that send no key and do not buzz (`openspec/specs/options/spec.md:9-11`, `:22-26`),
  the owner's `options.txt` read first and planted back last.
- **Complex, so implemented on `feature/options-table`:**
  every hand-off of the options changes at once, across three layers,
  and `options_file.c`, which no suite builds, reads and writes anew.
- **It builds on `develop` alone:** no plan is queued.
- **It lands as `refactor(options): hold the options in a table`.**

## What Changes

- `Option` names the options, Vibration alone for now.
- The keymap holds the options' values in a table and answers each by its name.
- The screen, the options' file and the view take the options by `Option`.
- `app.c` follows every option in one place, at the opening as after an event.
- The architecture page follows; every board, the file and the buzz stay as they are.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `host-tests`: the platform reaches the options through `keymap_option` and `keymap_set_option`,
  and no function is named for one option.

## Impact

`src/core/option.h`, new; `src/core/keymap.h`, `keymap.c` and `test/keymap_test.c`;
`src/ui/view.h`, `view.c`, `view_options.h` and `view_options.c`;
`src/platform/app.c`, `options_file.h`, `options_file.c`, `screen.h` and `screen.c`;
`docs/internals/architecture.md`.
`feedback.c`, `display.c`, `backlight.c`, the transport, `view_idle.c`, `README.md`, the rest of `docs/`
and `catalog/` stay as they are.
