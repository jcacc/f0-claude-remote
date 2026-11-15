# Design

## Context

See `proposal.md`, Why.
The core decides the legend's end (`keymap.c`), the bar's length (`charge.c`) and the opening's charging (`charging.c`, new);
the UI draws the battery;
platform-specific code carries the readings from the power service, which only the firmware has, to the GUI thread.

| Fact | Where, in firmware 1.5.1 |
|---|---|
| The SDK exports the power service's reading and events, the charger's `done` and the bitmap mode, but neither icon | `api_symbols.csv:42`, `:859`, `:1572`, `:3084-3085` |
| Each second the power service publishes a changed charge or state, on its 1 KiB thread, under the pubsub's lock | `power.c:88-112`, `:162-169`, `:253-264`, `pubsub.c:84-98`, `power/application.fam:15` |
| The Bt service follows that pubsub by a put on its own queue | `bt.c:123-137` |
| A loop serves its objects in the order they became ready | `event_loop.c:149`, `:552` |
| The battery: `Battery_26x8` at (99, 2), a box (101, 4, `(charge + 4) / 5`, 4); while charging, `Charging-lightning_mask_9x10` white, then `Charging-lightning_9x10`, at (107, 1), in bitmap mode | `power.c:17-48`, `assets/icons/StatusBar/`, the owner's shot `battery-probe/firmware-status-bar.png` |
| Charging: the charger charges, below 100, not done | `power.c:91-104` |
| u8g2 draws no box of zero width | `u8g2_box.c:40` |

## Goals / Non-Goals

**Goals:** the specs', each frame 0 cells from its reference, every other board as it was.

**Non-Goals:** the gauge's failure mark (`power.c:50-52`),
and the cross of a lowered charge limit (`:25-38`), which no setting or console command of 1.5.1 lowers.

## Decisions

- **The keymap holds the legend as a `bool`, answered by `keymap_legend`,**
  not a second idle mode, which every `switch` over the modes would name.
- **`charge_cells` and `charging_now` are units of the core with suites,**
  not arithmetic in `view_idle.c` and `battery.c`:
  no walk reaches 0, 1 or 100 %, nor the charger's `done`.
- **The icons are the firmware's PNGs, copied into `asset/image/`,**
  not drawn with lines:
  a copy is the firmware's to the cell, and the app shares its GPL-3.0.
- **The charge and the charging come with the power service's events, over a queue each,**
  not read on a timer, nor set from the service's callback:
  the service reads the gauge already, its callback on 1 KiB under a lock (fact 2).
- **The opening's readings take those queues too,** not `screen_alloc`:
  the walk's battery frame then proves the one way to the screen.
- **`view_draw` takes three more parameters,** not a struct of what the screen holds:
  replacing the list is a change of its own.

The parts:

- `charge.c`: `charge_cells(charge, cells)` answers `cells` from 100 on, otherwise the charge's share, rounded up.
- `charging.c`, new: `charging_now(charger, charge, done)` answers fact 6.
- `keymap.c`: `legend`, `true` at the opening, `false` from a press in `ModeIdle`.
- `asset/image/`: fact 5's icons, as `battery.png`, `charging_lightning.png` and `charging_lightning_mask.png`.
- `view_idle.c`: a component drawing fact 5, its bar `charge_cells` of 20 wide, left out at none (fact 7);
  `view_idle_draw` takes `legend`, `charge` and `charging` after `flash`, and draws the legend or the battery;
  `view_draw` takes the three after `cursor`.
- `screen.c`: an `_Atomic` word and a setter for each; `screen_alloc` takes the legend after the link.
- `battery.c` reports the battery as the firmware measures it:
  `battery_alloc(charge_queue, charging_queue)` subscribes to the power service's events,
  then puts `power_get_info`'s charge on the one,
  and `charging_now` of its charging, charge and `furi_hal_power_is_charging_done` on the other;
  its callback, a `switch` over the event's type, puts with no wait a changed level,
  `true` at `StartCharging`, `false` at `StopCharging` and `FullyCharged`;
  `battery_free` unsubscribes before `app.c` frees the queues.
- `app.c`: both queues, their callbacks handing the screen each reading;
  `battery_alloc` before `transport_hid_alloc`, so the first readings precede any link report (fact 4);
  `keymap_legend` in `screen_alloc`'s call and `app_settle`.

The tests: `keymap_test.c`'s four and `charge_test.c`'s three as landed, the latter on 20 cells;
`charging_test.c`, new: `test_charger_below_full_charges`, `test_full_charge_ends_it` and `test_no_charger_or_done_ends_it`.

The walks, over RPC and the console, by Back's taps alone:
the desktop's frame and `info power`'s `charge.level` (`furi_hal_power.c:528-529`);
launch: `D_Main`; Back, Back: the desktop's in x 99..124 of rows 1..10, `D_Main` elsewhere, at the same `charge.level`.
A, on the cable at 100: no lightning.
B, the owner's cable in below full: the lightning;
then the cable out and in, and a frame read with no launch equals the one before.

The pages: under the guide's `main.png`, the first press takes the legend away until the app is left,
and the device's own battery, its lightning included, takes its place.
The architecture page: `charging`'s row after `charge`'s; `battery`'s row and the third queue's paragraph take the charging, on a fourth.

Test seams:

- `keymap.c`, `charge.c`, `charging.c`: their suites; red is the build, at `keymap_legend` and each new unit.
- The UI, which only renders: the walks' frames.
- `screen.c`, `battery.c` and `app.c`: the build, the spec's greps, and walk B's frames, both queues crossed.

## Risks / Trade-offs

- No cell fills during a walk → a moved level still logs a frame no press caused (`rpc_gui.c:84-102`).
- A full queue drops a reading → each holds 8, and the service publishes one a second at most (fact 2).
- A new call overruns a stack → `battery.c`'s took 400 bytes at most against `app_alloc`'s 688 (`stack-probe/`, beside the repository); the probe measures `furi_hal_power_is_charging_done` before 2.3's code.
