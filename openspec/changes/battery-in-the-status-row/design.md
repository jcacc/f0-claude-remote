# Design

## Context

See `proposal.md`, Why.
The rules land in the core: the legend's end in `keymap.c`, the bar's length in `charge.c`, new.
The UI draws the battery.
Platform-specific code carries the charge from the power service to the GUI thread:
both exist only in the firmware.

| Fact | Where, in firmware 1.5.1 but for the canvas |
|---|---|
| SDK 1.5.1 exports the power service's reading and its events | `api_symbols.csv:42`, `:3084-3085` |
| Each second the power service publishes a changed charge, on its own 1 KiB thread, under the pubsub's lock | `power.c:162-169`, `:253-264`, `:312`, `pubsub.c:84-98`, `power/application.fam:15` |
| The firmware's Bt service follows that pubsub by a put on its own queue | `bt.c:123-137` |
| A loop serves its objects in the order they became ready | `event_loop.c:149`, `:552` |
| The battery: frame (114, 2, 12, 7), contact box (126, 4, 1, 3), bar box (116, 4, w, 3) of 8 cells | the canvas, `1794678650-09f9`: `D_idea_status`, rows 3-5 |
| u8g2 notes it draws no box of zero width | `u8g2_box.c:40` |

## Goals / Non-Goals

**Goals:** the specs', each frame 0 cells from its board,
every board but the idle one as `options-backlight` leaves it.

**Non-Goals:** a mark for a gauge that fails, as the firmware's bar has (`power.c:50-52`).

## Decisions

- **The keymap holds the legend as a `bool`, answered by `keymap_legend`,**
  not a second idle mode:
  every `switch` over the modes would name it, and the keymap would still keep which idle a link's return opens.
- **`charge_cells(charge, cells)` is a unit of the core with a suite,**
  not arithmetic in `view_idle.c`:
  the device shows one charge at a time, so no walk reaches 0, 1 or 100 %.
- **The charge comes with the power service's events, over a queue of its own,**
  not read on a timer, nor set from the service's callback:
  the service reads the gauge already,
  and its callback runs on 1 KiB under a lock (fact 2).
- **The opening's reading takes that queue too,**
  not `screen_alloc`:
  the walk's battery frame then proves the one way to the screen.
- **`view_draw` takes two more parameters,**
  not a struct of what the screen holds:
  replacing the list, six after `options-backlight`, is a change of its own.

The parts, on `options-backlight`'s names (its `design.md`):

- `charge.c`, new, says how many cells a charge fills:
  `charge_cells` answers `cells` from a charge of 100 on, otherwise the charge's share of them, rounded up.
- `keymap.c`: `legend`, `true` at the opening, `false` from a press in `ModeIdle`'s case.
- `view_idle.c`: a component for the battery, its bar `charge_cells` wide, of 8 cells, and left out at none (fact 6);
  `view_idle_draw` takes `legend` and `charge` after `flash`, and draws the legend or the battery.
  `view_draw` takes both after `cursor`.
- `screen.c`: an `_Atomic` word for each, set by `screen_set_legend` and `screen_set_charge`;
  `screen_alloc` takes the legend after the link.
- `battery.c`, new, reports the battery's charge as the firmware measures it:
  `battery_alloc(charge_queue)` subscribes to the power service's events,
  then puts `power_get_info`'s charge on the queue;
  its callback, a `switch` over the event's type, puts a changed level there with no wait;
  `battery_free` unsubscribes, before `app.c` frees the queue.
- `app.c`: `charge_queue`, whose callback hands the screen each reading;
  `battery_alloc` ahead of `transport_hid_alloc`, so the first reading is served before any link report (fact 4),
  hence before the idle screen;
  `keymap_legend` in `screen_alloc`'s call and, after the link, in `app_settle`.

The tests.
`keymap_test.c`, four new: `test_fresh_keymap_shows_the_legend`, `test_press_on_the_main_screen_ends_the_legend`,
`test_nothing_else_ends_the_legend` and `test_legend_stays_away`.
`charge_test.c`, new, three: `test_no_charge_fills_no_cell`, `test_part_of_a_cell_fills_it`
and `test_full_charge_or_more_fills_every_cell`.

The walk, over RPC and the console, by Back's taps alone:
launch: `D_Main`; the console's `info power` gives `charge.level` (`furi_hal_power.c:528-529`);
Back: the options; Back: the battery's board,
`D_idea_status` above the line and `D_Main` from it down, its bar `charge_cells` of that level wide.

The pages.
`docs/guide/using-the-remote.md`, under `main.png`:
the first press on the main screen takes the legend away until the app is left,
and a battery takes its place, its bar as long as the charge.
`docs/internals/architecture.md`: rows for `charge` after `display`'s and `battery` after `backlight`'s;
`view_idle` draws what only the idle board shows;
the legend goes where the mode and the link do, the charge over a third queue from the power service's thread,
and the draw callback reads both.

Test seams:

- `keymap.c`, `charge.c`: their suites; red is the build, at `keymap_legend` and at `charge.h`.
- The UI, which only renders: frames over RPC against `D_Main` and the battery's board.
- `screen.c`, `battery.c` and `app.c`, with no host test:
  the build types the calls, the spec's greps count them,
  and the walk's battery frame shows a reading that crossed the queue.

## Risks / Trade-offs

- No cell fills during the walk → a moved level still redraws, and the stream logs a frame no press caused (`rpc_gui.c:84-102`); the opening's reading crosses the same queue, the callback follows the Bt service's (fact 3).
- A full queue drops a reading → it holds 8, and the service publishes one a second at most (fact 2).
- A new call overruns a stack → `battery.c`'s take 400 bytes at most, where `app_alloc` goes to 688, and its callback makes the put the Bt service's makes (`stack-probe/probe.sh`, beside the repository).
