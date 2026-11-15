# Proposal

## Why

One screen bears two names.
A user meets the main screen:
the guide and the README call it so (`docs/guide/using-the-remote.md:53`, `README.md:3`),
its screenshot is `asset/screenshot/main.png`, and its board on the canvas `D_Main` (`openspec/specs/app-screen/spec.md:60`).
The code calls it idle:
`git grep -n -i idle -- ':!openspec'` prints 66 lines of 11 files, 64 of them this screen's.
Its mode is `ModeIdle`, on 31 lines, alone of seven modes to bear none of the screenshots' names
(`src/core/mode.h:4-10`, `asset/screenshot/`);
its board is `view_idle`, on 19;
three tests, a local, a comment and the architecture page hold the other 14,
beside one comment and one test that say main already (`src/core/keymap.c:128`, `test/keymap_test.c:1128`).
The specs say both: `main screen` on four lines of three specs,
`idle` on 12 lines of five requirements in `app-screen` and `host-tests`.
The owner asked for a `view_main` on 2026-11-15,
and `view-state` left the names to a plan of their own, on it (`openspec/changes/view-state/proposal.md:31-35`).

Decisions:

- **The code takes the user's word, `main`,** not the guide the code's `idle`:
  `main` stands in the guide, the README and the manifest each release hands the Flipper Apps Catalog
  (`.github/workflows/release.yml:101-102`).
- **The specs take the word with the code,** not after it:
  the owner's call of 2026-11-15, a spec leading its code.
- **Two changes, this one first,** not one:
  the five requirements, with the one that names the board's file, run to 789 words in `app-screen` and 701 in `host-tests`,
  against one delta's 550.
  This one carries the screen's own requirement and what the code names, the list of modes and the board's file;
  `main-screen-in-the-specs` follows with the three requirements that point at the screen by its name.
- **`src/ui/view.c` keeps its name,** not `view_main.c`, the owner's first ask:
  `view_draw` draws every mode's board, four of them whole (`src/ui/view.c:96-123`), so the name would cover them all.
- **No task takes the device,** not a walk of frames as `view-state`'s:
  the package's code and data are held to the bytes built before, as `asset-folder` proved its move
  (`openspec/changes/archive/2026-11-09-asset-folder/design.md:28-30`), and equal bytes draw what they drew.
- **Relatively simple, so implemented on `develop`:**
  one word for another on 63 lines of nine files under `src/` and `test/`, two of the files moved, and no behavior.
- **It builds on `view-state`,** the one plan queued:
  that plan rewrites the board's draw call and names `view_idle` in its own artifacts (its `design.md:31`, `:49-50`),
  so it lands first.
- **It lands as `refactor: rename the idle screen to main`.**

## What Changes

- `ModeIdle` becomes `ModeMain`.
- `src/ui/view_idle.h` and `view_idle.c` become `view_main.h` and `view_main.c`, with every name they prefix.
- Three tests, a local and `app.c`'s one comment say `main`.
- The architecture page's row names the board's files as they are.
- `app-screen`'s requirement of the screen and `host-tests`' list of modes say `main`,
  and `host-tests`' one scenario names `view_main.c`.
- Every board, every key and every suite's count stay as they are.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `app-screen`: the requirement of the screen that shows the status and every button's action names the main screen,
  and says that no flash runs where it said idle.
- `host-tests`: the modes that light the display are listed with `main`,
  and the scenario that names the file sizing the battery's bar names `view_main.c`.

## Impact

`src/core/mode.h`, `keymap.c` and `display.c`;
`src/ui/view.c`, and `view_idle.h` and `view_idle.c` under their new names;
`src/platform/app.c`, one comment;
`test/display_test.c` and `test/keymap_test.c`;
`docs/internals/architecture.md`.
The three requirements `main-screen-in-the-specs` takes, every other header, the rest of `src/platform/`,
`README.md`, the rest of `docs/` and `catalog/` stay as they are.
