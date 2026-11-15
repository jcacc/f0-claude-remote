# Proposal

## Why

An action confirms itself on the screen for 100 or 400 ms (`src/core/feedback.c:27-49`),
and then the main screen reads `Connected` (`src/ui/view.c:89`), as before the press:
a glance that comes later learns nothing of what was sent,
and with Vibration `Off` the flash is all there was (`docs/guide/using-the-remote.md:45`).
The canvas's backlog puts it to plan first (`backlogMain`, item 1):
`Sent:` and the pressed button's label in place of `Connected` for 2-3 s.
It waited for the battery to take the legend's place,
as `Sent: /effort max` ends at x 87 and the legend starts at x 74 (`src/ui/view_main.c:11`),
and for a frame's state to cross as one value; both landed (`fbf98ca`, `fed95bd`).
The owner had the boards drawn on 2026-11-15, at the canvas's `1794763775-4775`:
`D_main_battery`, the main screen after the first press, and the nine `D_sent_*` with the label and the battery.

Decisions:

- **The label holds 3 s,** not 2, the backlog's other end:
  it is for the late glance, and hides nothing meanwhile, as the link's mark stays beside it (`backlogMain`, item 1).
- **It ends with its time or with the next action sent, the start of voice included, which names nothing,**
  not with the main screen's leaving:
  only a dictation makes a label stale,
  and after the options or a returned link it still names the last action sent.
- **`D_sent_long`, a label cut to fit, is left to layouts,** not drawn here:
  the backlog leaves the labels' length to them (`backlogMain`, item 5),
  and the longest of the nine ends 11 px before the battery (`canvas-check/sent.py`, beside the repository).
- **No board and no check on USB,** not a copy of the nine:
  `usb.png` is 7 × 9 as `bluetooth.png`, so the title and the label keep their x (the canvas's `sent` note),
  and on USB the device has no console (`openspec/specs/user-guide/spec.md:135`).
- **A frame with a label comes from the owner's press on a scratch Claude Code session,**
  not from a tap sent over RPC:
  an action sends its keys to the Mac's focused window, and buzzes.
  The frames before it are read over RPC through Back's taps, which send no key and do not buzz
  (`openspec/specs/options/spec.md:9-11`).
- **Complex, so implemented on `feature/sent-in-the-status-row`:**
  a rule new to the core, a second timer beside the flash's, three layers and three spec documents.
- **It builds on `develop` alone:** no plan is queued.
- **It lands as `feat(view): name the sent action in the status row`.**

## What Changes

- On the main screen an action that flashes takes the status row:
  `Sent:` and its button's label, as the ring draws it, stand in place of `Connected` for 3 s.
- Another such action takes the row for 3 s of its own, and the start of voice gives it back to `Connected`.
- The flash, the battery, the buzz and every other board stay as they are.
- The guide and the architecture page follow.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `app-screen`: the main screen's status row names the action sent for 3 s, so the frame after a flash keeps the label.
- `host-tests`: the core says how long a sent action stays named.
- `user-guide`: the guide says what the top row reads after an action.

## Impact

`src/core/feedback.h` and `feedback.c`, with `test/feedback_test.c`;
`src/ui/view_state.h`, `view.c` and `view_main.c`;
`src/platform/screen.h`, `screen.c` and `app.c`;
`docs/guide/using-the-remote.md` and `docs/internals/architecture.md`.
The keymap, the transport, `view_options.c`, `battery.c`, `README.md`, `catalog/` and every screenshot stay as they are.
