# Tasks

Task 1.1's suite closes `host-tests`' `Named` and `Not named`; 2.2 its `By that answer alone`; 2.3 `user-guide`'s `Content`;
3.1 `app-screen`'s `The long flash`, `The short flash`, `Only the half that acted flashes`, `Three seconds` and `Another action`,
with `Nothing clipped` for the labels; 3.2 `A series of arrow taps`; 3.3 `Voice`.
Standing as closed: `Acting again restarts it`, on the timer's documented restart (`design.md`, fact 3),
and, on lines this change leaves, `Voice takes over` and `Screenshots`.
Build, lint, clang-tidy and docs-build are `mise run build`, `mise exec -- ufbt lint`, `mise run clang-tidy` and `mise run docs-build`.
Task 2.1's walk and group 3 take the device, unlocked on the cable, with the paired Mac in range:
frames are read over RPC, kept beside the repository, and held against a board outside the battery's box (`design.md`, Goals).
The walk's only presses are Back's taps.
Group 3's are the owner's, on a scratch Claude Code session, and buzz, so it waits for the owner's word;
its log runs until the last frame awaited.

## 1. The time

- [x] 1.1 Note `mise run test`'s count of `ok` lines, 123 expected. Give `feedback_test.c` the design's two tests; then `feedback.c` its `feedback_sent_ms`. Check: `mise run test` fails on undeclared `feedback_sent_ms`, then prints 125 `ok` lines, expected; build, lint and clang-tidy exit 0.
  123 `ok`; red at `call to undeclared function 'feedback_sent_ms'`, `feedback_test.c:68` and `:80`; then 125 `ok`.

## 2. The label

- [x] 2.1 Give `ViewState` its `sent`, `view.c` the title, and `view_main.c` its constants and `view_main_draw_sent`, per the design. Check: build, lint and clang-tidy exit 0; launched, a frame is 0 cells from `D_Main`, and after Back's two taps 0 from `D_main_battery`.
  Launched 0 cells from `D_Main`; after Back's two taps 0 from `D_main_battery`. Frames: `sent-probe/frames/`.
- [x] 2.2 Give `screen` its second timer and `screen_confirm`, and `app.c` its call, with the architecture page's line, per the design. Check: `mise run test` prints 125 `ok` lines; build, lint, clang-tidy and docs-build exit 0; `By that answer alone` holds.
  125 `ok`; the grep prints `app.c:49` alone.
- [x] 2.3 Write the guide's sentences, per the design. Check: docs-build exits 0; the page holds what `user-guide`'s `Content` lists.
  Every item of `Content` found on the page, the two new at `:44-45` and `:47`.

## 3. With the owner

- [x] 3.1 With frames logged, the owner taps Up, Down within 3 s, waits, then taps Left, Right and OK and holds Up, Down, Left and Right. Observe: per press its board, then the same with the flash gone, 100 or 400 ms later; no `D_main_battery` between Up's board and Down's, and one 3 s after Down's.
  Every frame 0 cells from its board; flashes 81-85 ms for 100 and 378-384 for 400, the stream's lag; no `D_main_battery` between two boards under 3 s apart, and one 2984-2996 ms after the last. Logs: `sent-probe/log-3.1.txt`, `log-rest.txt`.
- [x] 3.2 The owner taps Up five times within a second. Observe: frames alternate `D_sent_up` with its flash and without it, once per tap; the owner sees each flash apart.
  Nine taps in 1.4 s: `D_sent_up` with and without its flash, alternating once per tap; the owner called it fine.
- [x] 3.3 The owner taps OK, then holds it for a second. Observe: `D_sent_enter`, the voice board, then a frame 0 cells from `D_main_battery`, under 3 s after `D_sent_enter`'s.
  `D_sent_enter`, `voice` 1188 ms later, `D_main_battery` 4582 ms after `D_sent_enter`: voice held 3.4 s, past the 3 s; that voice ends the label stands on `screen_confirm`'s time of none and the owner's word. Log: `sent-probe/log-3.3.txt`.

## 4. Close

- [x] 4.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
  None beyond 2.2's and 2.3's lines: `usb.md:21-23` and `architecture.md:63` hold, `screen.c` setting `sent` itself; `README.md:27` and `index.md:35` still true.
- [x] 4.2 Check: `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate sent-in-the-status-row --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
  All exit 0, 125 `ok`; the diff lists the Impact and `tasks.md`; words: proposal 583, design 853, tasks 589 as planned and one line of notes a task, specs 409, 142, 240.

## Workflow follow-up

- After `mise exec -- openspec archive sent-in-the-status-row -y`, `git diff --numstat -- openspec/specs` prints `20 3` for `app-screen`, `17 0` for `host-tests` and `3 2` for `user-guide`, and `mise exec -- openspec validate --specs --strict` prints `Totals: 30 passed, 0 failed (30 items)`, each expected.
