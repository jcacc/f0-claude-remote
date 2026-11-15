# Design

## Context

See `proposal.md`, Why.
The state is the UI's to name: it says what it draws, and the platform supplies it.
`screen`'s copy, its mutex and `app.c`'s hand-over stay platform-specific code:
the display's thread, the view port and the event loop exist only in the firmware.

| Fact | Where |
|---|---|
| The draw callback runs on the GUI thread, an event loop's callbacks on its own | `view_port.h:25-28`, `event_loop.h:15-16`, `event_loop_timer.h:5-6`, SDK 1.5.1, documented |
| `view_port_update` takes the lock the draw callback runs under, waits 2 ticks for it, then logs a lockup | `view_port.c:182-193`, `:202-220`, firmware 1.5.1's sources |
| The SDK exports the mutex and no `__atomic_*` | `api_symbols.csv:1817-1821`; `grep -c atomic` prints 0 |
| `gui_add_view_port` asks for a frame; `gui_remove_view_port` waits for one being drawn | `gui.c:245-270`, `:351-406`, the same sources |

## Goals / Non-Goals

**Goals:** the specs', with every frame 0 cells from `develop`'s.

**Non-Goals:** the UI's file names, the next plan's;
the flash's timer and the battery's two queues.

## Decisions

- **`ViewState` lives in `src/ui/view_state.h`,** not in `view.h`, nor in the core:
  `screen.h` and the boards need the type without `view_draw`, and no core unit reads it.
- **It is flat, a field for each value,** not nested by board or by source:
  the keymap, the battery and the flash cut the values one way, the boards another.
- **Every board takes the state,** not its own values:
  `view_idle_draw` takes four today, each passed through `view.c`.
- **One copy behind a `FuriMutex`, held for a copy alone,** the firmware's own guard for such a model
  (`gui/view.h:79-91`, documented), not `_Atomic` fields, nor its `View` in a `ViewHolder`:
  a struct wider than a word is atomic only through `__atomic_*` (fact 3);
  a `View` keeps its lock through the whole draw (`gui/view.c:135-142`),
  and a `ViewHolder` drops a tap or hold whose press it did not see (`view_holder.c:146-161`).
- **`app.c` reads the state back and sets it whole,** as `with_view_model` does a model (`gui/view.h:225-238`),
  not `screen` reading the keymap, nor a copy in `App`:
  `screen` would be the keymap's third reader (`git grep -l keymap -- src/platform`),
  and a copy set whole would end a flash still running.
- **`screen_alloc` takes the opening's state,** not a first `screen_set_state` after it:
  by fact 4 a frame could be drawn between the two.

The parts:

- `view_state.h`, new, names what a frame shows:
  `ViewState`, of `mode`, `link`, `legend`, `charge`, `charging`, `flash`, `options[OptionMAX]` and `cursor`,
  typed as `view_draw` takes them today.
- `view.h`, `view_idle.h`, `view_options.h`:
  `view_draw`, `view_idle_draw` and `view_options_draw` take `(Canvas* canvas, const ViewState* state)`,
  each header including `view_state.h` for the core's it names today.
  Their components keep their parameters.
- `screen.c`: a `mutex` and a `state` for the eight words.
  `screen_state(screen)` returns a copy taken under the mutex.
  `screen_set_state(screen, state)` copies in under it, releases it, then calls `view_port_update`, the file's one call (fact 2).
  The draw callback draws from `screen_state`'s copy.
  A static `screen_show_flash(screen, flash)` reads the state, changes `flash` and sets it:
  `screen_flash` calls it before starting its timer, and the timer's callback with `ActionNone`.
  `screen_alloc(event_loop, input_queue, state)` allocates the mutex and copies the state before the view port joins the GUI;
  `screen_free` frees the mutex once it has left (fact 4).
  The seven setters go.
- `app.c`: `app_follow_keymap(app, state)` writes the keymap's mode, link, legend, options and cursor into a state.
  `app_alloc` builds the opening's from `{.flash = ActionNone}`, the charge empty as today (`screen.c:62-64`), for `screen_alloc`.
  `app_settle` reads the screen's, has it follow the keymap and sets it, where its three setters stand (`:83-85`).
  Each battery callback reads its queue into the screen's state and sets it.
  `app_follow_options` keeps the card alone, and leaves `app_alloc`, where it writes nothing (`options_file.c:70-72`, `app.c:162-166`).

The walk, over RPC, each tap sent only on the frame it is for:
launch: `D_Main`; Back: the options; Right, Left: Vibration's other value and back; Down: the cursor on `Backlight`; Back: `D_Main` with the battery.
Each frame is held against `develop`'s at the same step, read before the code changes;
where the charge has moved, the last frame's battery is held against the desktop's at that charge
(`battery-probe/walk.py`, beside the repository).
The device's `options.txt` is read before and after: Right and Left write it and leave it as it was.

The page, `docs/internals/architecture.md`: a row for `view_state.h` above `view.h`'s;
lines 61 and 77 say `app.c` writes the keymap's values and each reading into the `ViewState` `screen.c` shows and sets it whole;
line 88, that `screen.c` keeps it behind a mutex, set whole by the event loop's thread and copied whole by the draw callback.

Test seams:

- The core: untouched; `mise run test` prints 123 `ok` lines before and after.
- The UI, which only renders: the walk's frames, and the owner's tap for the flash.
- `screen.c` and `app.c`, with no host test: the build types the calls, the specs' greps count them,
  and every step of the walk crosses both threads.

## Risks / Trade-offs

- `view_port_update` called under the mutex waits 2 ticks on a frame being drawn → `screen_set_state` releases first (fact 2).
- A second thread reading and setting would lose a change → every caller is a callback of the loop (fact 1), and a comment at `screen_set_state` says so.
