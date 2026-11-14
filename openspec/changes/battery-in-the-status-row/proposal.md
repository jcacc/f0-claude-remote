# Proposal

## Why

The main screen's legend `HOLD | TAP` takes 53 of its status row's 128 px (`src/ui/view_idle.c:9`)
for as long as the application runs, and says the same at every glance.
The application covers the whole display, the firmware's status bar with it
(`openspec/specs/app-screen/spec.md:17-18`), where the battery stands (`power.c:300-301`, firmware 1.5.1),
while it holds the backlight on (`openspec/specs/app-screen/spec.md:199-201`):
nothing on the device shows the charge that light spends.
The canvas's backlog puts both to plan (`backlogMain`, items 2 and 3):
the legend until the first press, then the battery in its place (`D_idea_status`).
The owner asked for the plan on 2026-11-15.

Decisions:

- **The legend ends when a button goes down on the main screen,**
  not at any press since the launch, as item 2 names no screen:
  a press on `D_stopped`, which starts over, would take the legend before the main screen showed it once.
- **The battery stands on the main screen alone,**
  not on every board:
  `D_idea_status` gives it the legend's place, and no other board has one,
  voice ending its row in nothing, the options in their plate, a no-link board in `HOLD` or in nothing
  (`openspec/specs/app-screen/spec.md:91-93`, `:140-142`, `:184`, `:245-246`).
- **A part of a cell counts as a cell,**
  not rounded to the nearest:
  the firmware's own bar rounds up (`power.c:23`), and at 6 % the nearest would draw an empty battery.
- **The battery shows the charge alone,**
  not the firmware's mark of charging beside it (`power.c:40-48`):
  `D_idea_status` draws none.
- **A frame after the press is held against `D_idea_status` above the line and `D_Main` from it down,**
  not against boards drawn anew:
  the idea board draws the ring where it stood before the recess,
  but above the line the two differ in the legend's place alone
  (376 cells, all in x 74..126 of rows 0..10: `canvas-check/status_row.py`, beside the repository).
  The canvas's `D_Main`, `D_usb_main` and nine `D_sent_*` keep the legend.
- **`main.png` and `main-usb.png` stay,** the look of a launch,
  not retaken with the battery:
  the guide says in words what the first press changes.
- **Frames are read over RPC through Back's taps, which send no key and do not buzz**
  (`openspec/specs/options/spec.md:9-11`), and the charge over the console;
  the checks take no hand of the owner's.
- **Complex, so implemented on `feature/battery-in-the-status-row`:**
  a rule and a unit new to the core, a reading that crosses from the power service's thread,
  three layers and three spec documents, on two queued plans.
- **It builds on `options-table`, then `options-backlight`, both queued.**
- **It lands as `feat(view): show the battery after the first press`.**

## What Changes

- The main screen shows its legend from the launch until a button is pressed on it.
- From that press on a battery stands in the legend's place until the application ends,
  its bar as long as the device's charge.
- Every other board stays as it is.
- The guide and the architecture page follow.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `app-screen`: the legend shows until the first press on the main screen, and the battery takes its place.
- `host-tests`: the core decides when the legend ends, and how many cells a charge fills.
- `user-guide`: the guide says what the first press changes in the top row.

## Impact

`src/core/charge.h` and `charge.c`, new, with `test/charge_test.c`;
`src/core/keymap.h` and `keymap.c`, with `test/keymap_test.c`;
`src/ui/view.h`, `view.c`, `view_idle.h` and `view_idle.c`;
`src/platform/battery.h` and `battery.c`, new;
`src/platform/app.c`, `screen.h` and `screen.c`;
`docs/guide/using-the-remote.md` and `docs/internals/architecture.md`.
The transport, `view_options.c`, `options_file.c`, `backlight.c`, `display.c`, `README.md`, `catalog/`
and every screenshot stay as they are.
