# Design

## Context

See `proposal.md`, Why.
The options' values stay in the core's keymap (`src/core/keymap.c:15`, `:92`).
Platform-specific code keeps what it carries today, each by `Option`:
the screen's words for the GUI thread, the file on the SD card, and `app.c` between them and the keymap,
since the view port and the storage exist only in the firmware.

| Fact | Where |
|---|---|
| `mise run test` builds each suite from its one core source, so the options stay in `keymap.c` | `.mise/tasks/test:13` |
| A key is sought forward from where the last read stopped | `flipper_format_stream.c:101-123`, firmware 1.5.1 |
| The walks of the options' file, with their frames and readings | `openspec/changes/archive/2026-11-14-options-across-launches/design.md:62-70` |

## Goals / Non-Goals

**Goals:** the spec's, with every frame and the file's lines as `develop` gives them,
and the test total standing at 108.

**Non-Goals:** `OptionBacklight`, the cursor and a table of the view's rows, which Backlight's change adds;
`feedback_vibrates` and `display_lit`, which stay as they are.

## Decisions

- **`Option` is an enum that ends in `OptionMAX` and indexes a table in the keymap and in the file,**
  not an enum under a `switch`:
  a new option then takes a row in each table, and no unit branches on it.
- **A value stays a `bool`, `true` its `On`,**
  not an enum of each option's words:
  `feedback_vibrates` and the file's format take it as it is.
- **The keymap answers one option by its name, `keymap_option(keymap, option)`,**
  not a pointer to its table:
  the table stays behind the header.
- **`options_file_read_option(file, option, fallback)` reads one option, from a file it opens itself,**
  not every option in `options_file_alloc`, handed the defaults as an array:
  `app.c` would build that array, and by the second fact one open for all would rewind for each key.
- **The options reach the screen and the file through `app_follow_options`, at the opening as after an event,**
  not through `screen_alloc`, which keeps the mode and the link:
  no board of the opening shows an option.

The parts:

- `option.h`, new, names the remote's options: `Option`, of `OptionVibration` and `OptionMAX`.
- `keymap.c`: `options[OptionMAX]` for `vibration`, each `true` at the opening.
  Left and Right on the options give `options[OptionVibration]` its other value.
  `keymap_option(keymap, option)` and `keymap_set_option(keymap, option, on)` replace `keymap_vibration` and `keymap_set_vibration`.
- `view.c`, `view_options.c`: `view_draw` and `view_options_draw` take `const bool options[OptionMAX]` for `vibration`;
  the board's three components stand, the row drawing `options[OptionVibration]`.
- `screen.c`: an `_Atomic` word for each option, `false` until handed, set by `screen_set_option(screen, option, on)`;
  the draw callback copies them for `view_draw`, and `screen_alloc` loses `vibration`.
- `options_file.c`: `options_file_keys[OptionMAX]` for the one key, and `options_file_alloc()`, which opens the storage alone.
  `options_file_read_option` holds `fallback`, then the card's value where the read answers true, and returns what it holds.
  `options_file_set_option(file, option, on)` returns on the value held; otherwise it holds `on` and writes the header and every option's line.
- `app.c`: at the opening each option goes from `options_file_read_option`, handed the keymap's, to `keymap_set_option`.
  `app_follow_options` hands each option to the screen, then to the file:
  it is called after `screen_alloc`, and in `app_settle` where the two lines on Vibration stand (`:72-73`).
  The buzz asks `keymap_option(…, OptionVibration)`.

The tests: `keymap_test.c` asks `keymap_option` and `keymap_set_option` with `OptionVibration`
wherever it asks `keymap_vibration` and `keymap_set_vibration`, its 83 tests and their names standing.

The walks are `options-across-launches`' three, by the third fact, run again as written, over RPC and the console,
each tap sent only on the frame it is for.
The device's `options.txt` is read first and planted back last.

The page, `docs/internals/architecture.md`: a row for `option.h` after `link.h`'s;
lines 57-58, 73-74 and 78 say each option where they say Vibration, and line 61's buzz keeps it.

Test seams:

- `keymap.c`: its suite; red is the build, at `keymap_option`.
- The UI, which only renders: frames over RPC, equal to `develop`'s.
- `screen.c`, `options_file.c` and `app.c`, with no host test:
  the build types the calls, the spec's greps count them, and the walks read the frames and the file.

## Risks / Trade-offs

- An arrow's tap that meets `D_Main` goes to the Mac → the walks send each tap only on the frame it is for.
- The walks overwrite the options the owner saved → the file is read first and planted back last.
- `options_file_set_option` asked before `options_file_read_option` compares with a value never read → `app.c` reads every option at the opening, ahead of the first event.
- clang-tidy takes a loop over `Option` for a too small variable → clang reads no short enums (`Clang.cpp:6815-6818`, LLVM 18.1.8), task 1.1's run shows it, and a `size_t` index is the fallback.
