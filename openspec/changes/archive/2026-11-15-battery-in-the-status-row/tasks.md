# Tasks

Task 1.1's suite closes `host-tests`' `Opened`, `Ended` and `Left`;
1.2 `The platform follows`, and `app-screen`'s `Status row`, `Hold and press read apart` and `The board`;
2.1 `Rounded up` and `Empty and full`; 2.2 `Charging` and `Not charging`;
2.3 `By that answer alone`, `By the opening's answer alone`, `The first press` and `Nothing clipped`;
2.4 `user-guide`'s `Content`; 3.2 `The charge` and `The lightning`.
Standing as closed, on lines this change leaves: `Legend`, `The recess` and `Screenshots`;
`D_usb_main`'s mark and each flash's box, under the row 2.3 shows.
Build, lint, clang-tidy and docs-build are `mise run build`, `mise exec -- ufbt lint`, `mise run clang-tidy` and `mise run docs-build`.
Tasks 1.2, 2.3 and 3.2 take the device, unlocked on the cable, with the paired Mac in range:
frames are read over RPC, kept beside the repository, the charge over the console, and the only presses are Back's taps;
the owner's hand only moves the cable, in 3.2.
The first plan's 2.1-3.2 landed `D_idea_status`'s battery as `166dae1` and `33b1006`; the tasks below replace it.

## 1. The legend

- [x] 1.1 Note `mise run test`'s count of `ok` lines, 113 expected. Give `keymap_test.c` the design's four tests; then the keymap its `legend`. Check: `mise run test` fails on undeclared `keymap_legend`, then prints 117 `ok` lines, expected; build, lint and clang-tidy exit 0.
  113 `ok` lines before; red at `keymap_legend`, undeclared; 117 after.
- [x] 1.2 Give `view_draw` and `view_idle_draw` the legend, `screen` its word and `app.c` `keymap_legend`'s two lines, with the architecture page's lines on the legend, per the design. Check: build, lint, clang-tidy and docs-build exit 0; `The platform follows` holds; launched, a frame is 0 cells from `D_Main`, and after Back's two taps 0 cells outside the legend's place, which is clear.
  `D_Main` taken from the canvas at `1794663074-5159`: the probe's `boards/D_Main.txt` predates the ⚙. Launched, 0 cells; after the taps 363, all in x 74..126 of rows 0..10, none black.
  `view_idle_draw` sets the font now: the ring took it from the legend. Frames and `walk.py` in `battery-probe/`, beside the repository.

## 2. The battery

- [x] 2.1 Set `charge_test.c`'s three tests on 20 cells, per `host-tests`. Check: `mise run test` prints 120 `ok` lines, expected; build, lint and clang-tidy exit 0.
  120 `ok` lines. `charge.c`'s comment rests on 1 %, as 6 % rounds to a cell of 20.
- [x] 2.2 Add `test/charging_test.c` with the design's three tests; then `charging.h` and `charging.c`, named on the architecture page. Check: `mise run test` fails on the missing unit, then prints 123 `ok` lines, expected; build, lint, clang-tidy and docs-build exit 0.
  Red: `no such file or directory: 'src/core/lightning.c'`; 123 `ok` lines after.
  Landed as `lightning`, `lightning_shows`; renamed to `charging`, `charging_now` by the owner's call: the state, not its picture.
- [x] 2.3 Measure `furi_hal_power_is_charging_done` with the stack probe; copy the icons, draw them in `view_idle.c`, give `view_draw` and `screen` the charging, `battery.c` and `app.c` its queue, with the architecture page's lines, per the design. Check: build, lint, clang-tidy and docs-build exit 0; both greps hold; walk A ends 0 cells apart.
  `furi_hal_power_is_charging_done`: 256 bytes. Icons from the firmware's 1.5.1 tag; the charging comes from `PowerInfo`'s `is_charging`.
  Walk A at `charge.level` 100, `charged`: launched 0 cells from `D_Main`, after the taps 0 from the desktop's battery. `walk.py desktop|firmware|again`.
- [x] 2.4 Rewrite the guide's sentence on the battery, per the design. Check: docs-build exits 0; the paragraph holds what `user-guide`'s `Content` lists of the main screen.

## 3. Close

- [x] 3.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
  One: `architecture.md:68`, «The link takes the other queue», of two; now «a second», of four.
- [x] 3.2 Check: walk B ends 0 cells apart, and so does its frame after the cable's way out and in; `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate battery-in-the-status-row --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
  Walk B at `charge.level` 99, `charging`, the desktop's lightning shown: launched 0 cells from `D_Main`, after the taps 0 from the desktop's; after the cable's way out and in, 0 from that frame.
  123 `ok` lines; words: design 878 of 880, `app-screen` 549 of 550.
