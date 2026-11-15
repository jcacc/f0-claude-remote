# Tasks

Task 2.1 closes `source-layers`' `Drawn from one state`;
2.2 its `Set whole` and `No word of its own`, `host-tests`' two `The platform follows` and `options-state`'s.
The walk, in 2.1 and 2.2, shows `develop`'s frame at every step, and 3.1 the flash,
so `app-screen`'s and `options`' scenarios stand as closed;
so does every other scenario of the deltas, on lines this change leaves.
Build, lint, clang-tidy and docs-build are `mise run build`, `mise exec -- ufbt lint`, `mise run clang-tidy` and `mise run docs-build`.
Groups 1 and 2 take the device, unlocked on the cable, with the paired Mac in range, and no hand of the owner's:
frames are read over RPC and kept beside the repository, the file over the console,
and the only presses are the walk's (`design.md`).
Group 3 buzzes, so it waits for the owner's word.

## 1. The reference

- [ ] 1.1 Note `mise run test`'s count of `ok` lines, 123 expected. On `develop`'s build, keep the device's `options.txt`, the desktop's frame and its `charge.level`; run the walk and keep each step's frame. Check: the launch's frame 0 cells from `D_Main`; the last one's battery 0 cells from the desktop's.

## 2. The state

- [ ] 2.1 Add `view_state.h`, named on the architecture page; give `view_draw` and both boards the state, `screen.c`'s draw callback filling one from its words, per the design. Check: build, lint, clang-tidy and docs-build exit 0; `Drawn from one state` holds; the walk's frames 0 cells from 1.1's.
- [ ] 2.2 Give `screen` its mutex, its one copy, `screen_state` and `screen_set_state`, and `app.c` `app_follow_keymap`, with the architecture page's three lines, per the design. Check: `mise run test` prints 123 `ok` lines; build, lint, clang-tidy and docs-build exit 0; every grep of the deltas holds; the walk's frames 0 cells from 1.1's; `options.txt` reads as kept.

## 3. With the owner

- [ ] 3.1 With frames logged, the owner taps Up on a scratch Claude Code session. Observe: a frame apart from the one before in x 56..66 of rows 15..23 alone, then one equal to it again, 100 ms later.

## 4. Close

- [ ] 4.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
- [ ] 4.2 Check: `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate view-state --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
