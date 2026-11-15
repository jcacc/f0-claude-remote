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
The owner asked for the plan on 2026-11-15, and, with it implemented to `D_idea_status`,
for the firmware's own battery the same day: «1-в-1 такую же и на том же месте», «с молнией».

Decisions:

- **The legend ends when a button goes down on the main screen,**
  not at any press since the launch, as item 2 names no screen:
  a press on `D_stopped`, which starts over, would take the legend before the main screen showed it once.
- **The battery stands on the main screen alone,**
  not on every board:
  `D_idea_status` gives it the legend's place, and no other board has one,
  voice ending its row in nothing, the options in their plate, a no-link board in `HOLD` or in nothing
  (`openspec/specs/app-screen/spec.md:91-93`, `:140-142`, `:184`, `:245-246`).
- **The battery is the firmware's, to the cell and at its place,** its lightning included,
  not `D_idea_status`'s 8 cells at (114, 2):
  the owner's call; it fits the legend's place, x 74..126 of rows 0..10
  (`power.c:17-48`, the owner's shot `battery-probe/firmware-status-bar.png`, beside the repository).
- **Neither the gauge's failure mark nor the cross of a lowered charge limit** (`power.c:25-38`, `:50-52`),
  not every state the firmware draws:
  real use reaches neither, as no setting or console command of 1.5.1 lowers the limit.
- **A frame after the press is held against the desktop's, read off the device at the same charge, in the battery's box,
  and against `D_Main` elsewhere,** not against `D_idea_status`:
  the device draws the reference itself.
  The canvas's `D_Main`, `D_usb_main` and nine `D_sent_*` keep the legend.
- **`main.png` and `main-usb.png` stay,** the look of a launch,
  not retaken with the battery:
  the guide says in words what the first press changes.
- **Frames are read over RPC through Back's taps, which send no key and do not buzz**
  (`openspec/specs/options/spec.md:9-11`), and the charge over the console;
  the owner's hand only plugs the cable in below a full charge, for the lightning.
- **Complex, so implemented on `feature/battery-in-the-status-row`:**
  rules and two units new to the core, readings that cross from the power service's thread,
  three layers and three spec documents.
- **It builds on `develop`, where `options-table` and `options-backlight` have landed.**
- **It lands as `feat(view): show the battery after the first press`.**

## What Changes

- The main screen shows its legend from the launch until a button is pressed on it.
- From that press on the firmware's battery stands in the legend's place until the application ends,
  where its status bar draws it, its lightning included.
- Every other board stays as it is.
- The guide and the architecture page follow.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `app-screen`: the legend shows until the first press on the main screen, and the firmware's battery takes its place.
- `host-tests`: the core decides when the legend ends, how many cells a charge fills, and whether the battery opens with its lightning.
- `user-guide`: the guide says what the first press changes in the top row.

## Impact

`src/core/charge.h` and `charge.c`, new, with `test/charge_test.c`;
`src/core/charging.h` and `charging.c`, new, with `test/charging_test.c`;
`asset/image/battery.png`, `charging_lightning.png` and `charging_lightning_mask.png`, new;
`src/core/keymap.h` and `keymap.c`, with `test/keymap_test.c`;
`src/ui/view.h`, `view.c`, `view_idle.h` and `view_idle.c`;
`src/platform/battery.h` and `battery.c`, new;
`src/platform/app.c`, `screen.h` and `screen.c`;
`docs/guide/using-the-remote.md` and `docs/internals/architecture.md`.
The transport, `view_options.c`, `options_file.c`, `backlight.c`, `display.c`, `README.md`, `catalog/`
and every screenshot stay as they are.
