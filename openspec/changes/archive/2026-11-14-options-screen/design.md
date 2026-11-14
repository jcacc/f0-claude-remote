# Design

## Context

See `proposal.md`, Why.
The rules land in the core, the modes and Vibration in `keymap.c`, the buzz in `feedback.c`, the light in `display.c`,
and the boards in the UI.
Platform-specific code carries Vibration to the GUI thread,
an `_Atomic` word as the mode is (`src/platform/screen.c:11-14`), and sounds the buzz.

| Fact | Where |
|---|---|
| A tap's `Short` comes at the release, ahead of `Release`, and a hold sends none | `input.h:24`, documented; `input.c:146-155`, firmware 1.5.1 |
| `mise run test` builds each suite from its one core source | `.mise/tasks/test:13` |
| A status row's text starts 3 px past its mark: at 12 after 7 px, at 15 after 10 | `src/ui/view.c:32-34`, `:51-53`; the canvas's `noteD` |
| The calls below are rows 59-64 of `D_Main`'s table, and 1-11 and 14-16 of `E_options_vibration_on`'s | The canvas, `1794663074-5159` |

## Goals / Non-Goals

**Goals:** the specs', with `D_Main` 57 of 8,192 cells from today's, in Back's plate
(`canvas-check/apart.py`, beside the repository).

**Non-Goals:** a moving cursor, with one row.

## Decisions

- **Two modes, `ModeOptions` after `ModeVoice` and `ModeOptionsNoLink` after `ModeVoiceCut`,**
  not a flag beside the mode:
  a mode is a board (`src/ui/view.c:92-111`), every switch names both or stops the build,
  and voice under the options cannot be written.
- **Vibration is a `bool` of the keymap, read through `keymap_vibration`,**
  not a core file of its own, nor an action `app.c` applies:
  the taps that set it are button events on a screen, as the hold that moves the link is (`src/core/keymap.c:125-129`),
  and a second core source would not link into the keymap's suite, by the second fact.
- **`view_plate` takes `view_idle.c`'s four helpers (`:5-28`) as `view_plate_draw_*`,**
  not copies in `view_options.c`: the options' plate is one call of each.
- **`view_draw_title_row(canvas, mark, title)` draws every status row, its text at `icon_get_width(mark) + 5`,**
  not `x` passed beside the mark:
  the third fact is one rule, and `Options` stands after both marks.

`view_plate.c` draws the parts of a plate, and `view_options.c` the options board's controls.

- `mode.h`, `display.c`: both enumerators, lit.
- `keymap.c`: `vibration`, `true` at the opening.
  `ModeIdle` opens the options on Back's `Short`.
  Each options mode hands its `Short` to `keymap_tap_options(keymap, key, closed)`,
  which sets the mode `closed`, `ModeIdle` or `ModeNoLink`, on Back, and flips `vibration` on Left or Right:
  a value has two states, so both step it.
  A link change moves each options mode to the other, and `ModeOptionsNoLink` waits.
- `feedback.c`: `feedback_vibrates(action, vibration)` returns `vibration` where it returned `true`.
- `view.c`: `view_draw` takes `vibration` and draws both modes, under the link's mark and its no-link one.
- `view_idle.c`: Back's plate is outline `78, 46, 45`, fill `78, 46, 33`, its two white marks, and `I_options` at `113, 48`.
- `screen.c`: a fourth word, set at `screen_alloc` and by `screen_set_vibration`.
- `app.c`: `keymap_vibration` at the opening, in `app_settle` and for the buzz.

`view_options_draw(canvas, vibration)` is three components, in `FontSecondary`:
the plate, outline `63, 0, 64`, fill `63, 0, 36`, `I_back` white at `66, 2`, `EXIT` white at `77, 9`, `BACK` at `101, 9`;
the row, `Vibration` at `5, 26` and `On` or `Off` at `102, 26`, aligned as `view.c:59-60` aligns;
the cursor, `canvas_draw_rframe` at `1, 16, 125, 13, 2` with `I_left` at `80, 19` and `I_right` at `120, 19`.
`asset/image/options.png` is `noteE`'s grid, `D_Main`'s cells at (113, 48):

```text
..#.#..
.#####.
##...##
.#...#.
##...##
.#####.
..#.#..
```

The walk, over RPC, sends each tap only on the frame before it:
Back on `D_Main`, Right, Left, Back,
showing `E_options_vibration_on`, `E_options_vibration_off`, `E_options_vibration_on` and `D_Main`,
the options' boards less their cells in y 31-43.

New in `keymap_test.c`, the options' with a link and with none:
`test_tap_on_back_opens_the_options`, in place of `test_tap_on_back_does_nothing`,
`test_tap_on_back_closes_the_options`, `test_tap_on_back_opens_nothing_elsewhere`,
`test_back_tap_begun_elsewhere_opens_nothing`, `test_options_act_only_on_held_back`,
`test_fresh_keymap_vibrates`, `test_side_tap_on_the_options_switches_vibration`,
`test_nothing_else_switches_vibration`, `test_vibration_outlasts_the_options`,
`test_link_moves_the_options_between_their_modes`, `test_tap_through_a_drop_on_the_options_does_nothing`,
`test_wait_ends_the_options_with_give_up` and `test_options_keep_the_wait_but_for_the_link`.
`feedback_test.c` gains `test_nothing_vibrates_with_vibration_off`, its other asserts passing `true`,
and `display_test.c`'s lit test both modes.

The pages:

- `docs/guide/using-the-remote.md`: before `Back, hold`, a row `Back, tap`, `Nothing`, `Opens the options on the device`;
  line 29 goes; Confirmation, and a paragraph under `options-bt.png` after line 55, say what `user-guide`'s `Content` lists.
- `docs/guide/troubleshooting.md:16`: the cause opens with Vibration off, the fix with turning it on.
- `README.md:27`, `docs/index.md:34-36` and `catalog/description.md:10-11`, each in its voice:
  `every action buzzes and flashes; a tap on Back opens the options, where the buzz turns off`.
- `README.md:47`: a fourth row, `options-bt.png` alone, its alt `The options`.
- `catalog/description.md`, before line 24: `**Back, tap:** nothing; it opens the options`.
- `docs/internals/architecture.md`: a row for each new file; lines 54, 57 and 71 name Vibration.

Test seams:

- The core's three files: their suites; red is the build, at `ModeOptions` and at the second argument.
- The UI, which only renders: frames over RPC, equal across the plate's move, then to `D_Main`, through the walk and at a drop;
  `view_options.c` takes no link, so USB adds nothing.
- `screen.c`, `app.c`, with no host test: the build types the calls, `host-tests`' `git grep` counts them, and the owner feels the buzz.

## Risks / Trade-offs

- A tap of Left or Right that meets `D_Main` sends the Mac an arrow → the walk sends each only on the options' frame.
- The canvas moves the rows after this plan → the calls above stand, and the next change takes it.
