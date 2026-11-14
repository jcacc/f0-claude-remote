# Tasks

Task 1.1's suite closes `host-tests`' `Opened`, `Ended` and `Left`;
1.2 `The platform follows`, and `app-screen`'s `Status row`, `Hold and press read apart` and `The board`;
2.1 `Rounded up` and `Empty and full`;
2.2 `By that answer alone`, `The first press` and `Nothing clipped`;
2.3 `user-guide`'s `Content`; 3.2 `The charge`.
Standing as closed, on lines this change leaves: `Legend`, `The recess` and `Screenshots`;
`D_usb_main`'s mark and each flash's box, under the row 2.2 shows.
Build, lint, clang-tidy and docs-build are `mise run build`, `mise exec -- ufbt lint`, `mise run clang-tidy` and `mise run docs-build`.
Tasks 1.2, 2.2 and 3.2 take the device, unlocked on the cable, with the paired Mac in range, and no hand of the owner's:
frames are read over RPC against `D_Main` and the battery's board (`design.md`), kept beside the repository,
the charge over the console, and the only presses are Back's taps.
A frame that comes with no press as `charge.level` moves goes into 3.2's notes.

## 1. The legend

- [ ] 1.1 Note `mise run test`'s count of `ok` lines, 113 expected. Give `keymap_test.c` the design's four tests; then the keymap its `legend`. Check: `mise run test` fails on undeclared `keymap_legend`, then prints 117 `ok` lines, expected; build, lint and clang-tidy exit 0.
- [ ] 1.2 Give `view_draw` and `view_idle_draw` the legend, `screen` its word and `app.c` `keymap_legend`'s two lines, with the architecture page's lines on the legend, per the design. Check: build, lint, clang-tidy and docs-build exit 0; `The platform follows` holds; launched, a frame is 0 cells from `D_Main`, and after Back's two taps 0 cells outside the legend's place, which is clear.

## 2. The battery

- [ ] 2.1 Add `test/charge_test.c` with the design's three tests; then `charge.h` and `charge.c`, named on the architecture page. Check: `mise run test` fails on the missing `charge.h`, then prints 120 `ok` lines, expected; build, lint, clang-tidy and docs-build exit 0.
- [ ] 2.2 Give `view_idle.c` the battery, `view_draw` and `screen` the charge, and `app.c` the charge's queue; add `battery.h` and `battery.c`, with the architecture page's lines on them, per the design. Check: build, lint, clang-tidy and docs-build exit 0; `By that answer alone` holds; the design's walk ends on the battery's board, 0 cells apart.
- [ ] 2.3 Rewrite the guide's paragraph on the main screen, per the design. Check: docs-build exits 0; the paragraph holds what `user-guide`'s `Content` lists of the main screen.

## 3. Close

- [ ] 3.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
- [ ] 3.2 Check: the battery left showing since 2.2's walk, a frame's bar is as wide as the console's `charge.level` gives; `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate battery-in-the-status-row --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
