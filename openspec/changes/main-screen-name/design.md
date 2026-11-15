# Design

## Context

See `proposal.md`, Why.
No behavior moves and no layer gains a rule: each name changes where it stands,
in the core, in the UI, in one comment of platform-specific code, in both suites, on the architecture page and in three requirements.

| Fact | Where |
|---|---|
| The SDK holds no word `ModeMain`, and no name with `view_main` or `ViewMain` in it | `grep -rnw` and `grep -rn -E` over `.ufbt/current/sdk_headers` print nothing, SDK 1.5.1 |
| `main` is each suite's entry point | `test/keymap_test.c:1199` |
| Flipper's format wraps a line past 99 columns | `.clang-format:95` |
| Git shows a delete and an add as a rename from 50 % of the file kept, counted in the bytes of the lines kept | `git help diff`, `-M`, documented; `e4e6396`'s five scores, 98, 79, 98, 91 and 78, are that count |
| The build links the sources sorted by path, and their sections in that order | `SCons/Node/FS.py:2247`, in the toolchain; `application_ext.ld:4-34`, with no `SORT` |
| The package holds one of the names, `view_idle_draw`, in its string table, and a checksum of the debug file, which holds them all | `strings` over both files under `dist/`; `fbt_extapps.py:400` |
| `objdump -s` prints the package's `.text`, `.rodata`, `.data`, `.fapmeta`, `.gnu_debuglink` and three `.fast.rel.*`, and no table of names | the toolchain's, over `dist/f0_claude_remote.fap` |

## Goals / Non-Goals

**Goals:** the proposal's, with every old name gone from `src/`, `test/` and `docs/` but the radio's two lines
(`src/core/keymap.c:185`, `docs/internals/bluetooth.md:83`).

**Non-Goals:** the three requirements `main-screen-in-the-specs` takes; `view.c`'s name; a rule or a scenario that holds names.

## Decisions

- **The three tests take `main` for `idle`, word for word,**
  not `the_main_screen`, the fourth test's wording (`test/keymap_test.c:1128`):
  each stands beside a sibling that names its mode in one word (`:169`, `:287`, `:358`).
- **The local becomes `main_screen`,** not `main`: fact 2.
- **`the screen is idle` becomes `the main screen shows with no flash running`,** not `the main screen is idle`:
  the requirement said what idle was only where it named the screen (`openspec/specs/app-screen/spec.md:25`),
  so each scenario now says it itself.
- **No scenario holds the names,** not a grep for `idle` in a spec:
  the word is English as well, as the radio's two lines show, so the scenario would fail at its next honest use.
- **The package's dump proves the UI and the platform,** not its `sha256`, `asset-folder`'s proof, nor a frame:
  the string table and the checksum differ where no code does (fact 6),
  and the dump leaves the first out and holds the second in one line (fact 7).

The names, counted on `develop` at `3e2a7e1`; `view-state` adds and drops none of these lines (its `design.md:49-52`):

| From | To | Lines | In |
|---|---|---|---|
| `ModeIdle` | `ModeMain` | 31 | `mode.h`, `keymap.c`, `display.c`, `view.c`, both suites |
| `view_idle`, in the two files' names and in every name they prefix | `view_main` | 19 | `view.c`, the board's two files |
| `idle` in `test_link_down_ends_idle`, `test_right_pressed_on_usb_idle_returns_nothing` and `test_right_pressed_on_idle_takes_no_usb` | `main` | 6 | `keymap_test.c` |
| `idle`, the local of `test_right_held_elsewhere_on_usb_keeps_usb` | `main_screen` | 6 | `keymap_test.c` |
| `the idle screen`, in the comment over `battery_alloc` | `the main screen` | 1 | `app.c` |
| `view_idle.h`, `view_idle.c` and `the idle board`, in the board's row | `view_main.h`, `view_main.c` and `the main board` | 1 | `architecture.md` |

`view_main.h` and `view_main.c` keep the board's one task: they draw what only the main board shows.
Each new name is as long as the one it takes over, but the local's,
whose longest line reaches 85 columns (`test/keymap_test.c:312`): the formatter wraps no line anew (fact 3).

Test seams:

- The core: `mise run test`, whose output stands but for three names, and every suite's count with it.
- The UI and the platform, with no host test: the build types every renamed call,
  and the dump holds the package's code and data to the bytes built before;
  `view_main.c` is linked where `view_idle.c` was, between `view.c` and `view_options.c` (fact 5).
- The device: none. Equal bytes draw and send what they did.
- The specs: no line that draws or decides changes, so each scenario the deltas reword stands as closed,
  `app-screen`'s by the dump and `host-tests`' by the suites.

## Risks / Trade-offs

- `view_main.h`, as `view-state`'s design words the header, keeps six of its seven lines, 64 of its 125 bytes: a score of 51 against git's 50 → 1.1 counts the header's bytes before the move and 3.1 reads the score; under 50 is a stop.
- `view-state` lands other lines than its design words → each count is marked expected, and 1.1 takes it anew.
- The dump differs past the checksum's line → the objects are compared section by section, as `src-layers`' 2.3 did (`openspec/changes/archive/2026-11-04-src-layers/tasks.md:16`); code or data that differs is a stop.
