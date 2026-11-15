# Design

## Context

See `proposal.md`, Why.
The core says how long an action stays named (`feedback.c`);
the UI draws the title and the label from the state it is handed;
platform-specific code times both and hands the screen each action,
as the timers are the event loop's, which only the firmware has.

| Fact | Where |
|---|---|
| `D_main_battery` is `D_Main` but for the legend's place, which holds `battery.png` at (99, 2) over a bar of 15; each `D_sent_*` is it with the title and `view_main.c`'s flash | `canvas-check/sent.py`, beside the repository: 0 cells apart each |
| The title: `str (12, 9, "Sent:")` in Primary; then, from x 41 in Secondary, `I_slash` at (41, 2) with a command's text at (45, 9), `Esc` at (41, 9), `I_enter`, `I_left` or `I_right` at (41, 2), `I_up` or `I_down` at (41, 4) | the boards' draw lists; each icon the repository's and each text the ring's, by the same script |
| A timer started again restarts with its new interval; a stopped one fires no callback; an interval of no ticks is not documented | `event_loop_timer.h:69-74`, `:84-90`, SDK 1.5.1 |
| Each set of the state asks for a frame | `screen.c:78-83` |
| An action comes from a tap or hold whose press the main screen saw, and that press ends the legend | `keymap.c:71-78`, `:130-138` |
| The title starts at its mark's width plus 5, so at x 12 after either mark, 7 px wide | `view.c:36`, `asset/image/bluetooth.png`, `usb.png` |

## Goals / Non-Goals

**Goals:** the specs', each frame 0 cells from its board outside the battery's box, x 99..124 of rows 1..10.

**Non-Goals:** a label cut to fit, and a rule for the main screen's leaving (`proposal.md`).

## Decisions

- **One call, `screen_confirm`, sets the flash and the label and starts both timers,**
  not a setter beside `screen_flash`:
  two sets ask for two frames (fact 4), the first flashing under `Connected`.
- **It takes every action `app.c` performs, with the core's two times,**
  not only one that flashes (`app.c:49-52`):
  a time of none shows nothing and stops that timer (fact 3),
  so the start of voice ends the label with no branch in `app.c`.
- **`feedback_sent_ms` answers 3000 where `feedback_flash_ms` answers a time,**
  not a `switch` of its own:
  the label names what flashed, and one list holds the nine.
- **`view.c` picks the title and `view_main.c` draws the label after it,**
  not a title row of the main board's own:
  the mark, the title and the line are `view.c`'s for every mode (`view.c:33-38`).
- **The ring's four texts become constants of `view_main.c`, which the label draws too,**
  not a second literal of each:
  the label is the button's own.

The parts, each file keeping its task (`docs/internals/architecture.md:23-50`):

- `feedback.c`: `feedback_sent_ms(action)`, by the third decision.
- `view_state.h`: `sent`, an `Action` after `flash`.
- `view.c`: `ModeMain`'s title is `Sent:` while `state->sent` is an action, and `Connected` otherwise.
- `view_main.c`: the constants, read by the ring (`:41`, `:46`, `:64`, `:69`);
  a component `view_main_draw_sent(canvas, sent)`, a `switch` naming every action,
  with fact 2's calls for the nine and nothing for the six, called once the font is set.
  The legend is gone by then (fact 5).
- `screen.c`: `sent_timer` beside `flash_timer`, each callback setting its own field to `ActionNone`;
  `screen_confirm(screen, action, flash_ms, sent_ms)` reads the state,
  gives `flash` and `sent` the action for a time above none and `ActionNone` otherwise,
  sets the state once, and starts each timer for its time or stops it at none.
  `screen_flash` and `screen_show_flash` go.
- `app.c`: `app_perform` calls `screen_confirm` with the action's `feedback_flash_ms` and `feedback_sent_ms`
  where `:49-52` stand; the opening's state names `.sent = ActionNone`.

The tests, in `feedback_test.c`: `test_what_flashes_stays_named_for_3_s` and `test_the_rest_are_not_named`.

The walk, over RPC by Back's taps alone: launched, `D_Main`;
Back, Back: `D_main_battery`, the spec's `D_Main` once the battery shows.

The trial: the owner's presses on a scratch Claude Code session, logged until the last frame awaited (`tasks.md`, group 3).

The pages: the guide's Confirmation says, after the flash,
that the top row then reads `Sent:` and the button's label in place of `Connected` for 3 s or until the next action,
and that with Vibration `Off` the screen alone confirms (`:45`);
the architecture page's `:67`, that `screen.c` flashes the action and names it, each for `feedback.c`'s time.

Test seams:

- `feedback.c`: its suite; red is the build, at `feedback_sent_ms`.
- The UI, which only renders: the walk's and the trial's frames.
- `screen.c` and `app.c`, with no host test: the build types the calls, `host-tests`' grep counts them,
  and the trial crosses both timers, the one set and a time of none.

## Risks / Trade-offs

- A changed charge draws a frame among the trial's → each is held outside the battery's box, and one equal to the frame before is skipped.
- The stream's lag moves a time read off the log, 94 ms for 100 in `view-state`'s 3.1 → a time holds within 50 ms.
- After the options or a returned link a label under 3 s old shows again → it names the last action sent (`proposal.md`).
