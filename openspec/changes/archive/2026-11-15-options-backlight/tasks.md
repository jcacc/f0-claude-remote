# Tasks

Task 1.1's suite closes `options-state`'s `Changed`, `The cursor`, `Stayed`, `Opened` and `Taken from the card`, and `options`' `Every other gesture`;
2.2's walks the rest of `options` and of `options-file`, and `app-screen`'s `Vibration` and `Backlight`;
3.1 `host-tests`' `Lit`, `Left to the device` and `Dark`, with every grep of the deltas; 3.2 `user-guide`'s;
4.1 `app-screen`'s `No link`; 4.2 its `Left to the device`, `Held again` and `Leaving after a change`.
Standing as closed, on lines this change leaves: `The buzz`; both `A mode not asked`;
`Another file`'s other type and version, and `Not written`, by `options-table`'s walks;
`Held on`, `Off on stopping` and `Leaving after starting over`, as Backlight `On` sends `develop`'s messages (`design.md`, Goals).
Build, lint, clang-tidy and docs-build are `mise run build`, `mise exec -- ufbt lint`, `mise run clang-tidy` and `mise run docs-build`.
Groups 2 and 4 take the device, unlocked on the cable, with the paired Mac in range:
frames are read over RPC against the boards at `1794678650-09f9`, kept beside the repository,
the file is read and planted over the console, and the only presses are the walks' and these tasks'.
Group 4 waits for the owner's word.

## 1. The core

- [x] 1.1 Note `mise run test`'s count of `ok` lines, 108 expected. Give `keymap_test.c` the design's tests; then add `OptionBacklight`, the keymap's cursor and `options_file_keys`' row. Check: `mise run test` fails on undeclared `OptionBacklight`, then prints 112 `ok` lines, expected; build, lint and clang-tidy exit 0.
  108 `ok` lines before, 112 after; red at `keymap_test.c:856`, undeclared `keymap_cursor`, and `:917`, `OptionBacklight`.

## 2. The rows

- [x] 2.1 Give `screen` the cursor's word, `view_draw` and `view_options_draw` the cursor, `view_options.c` its rows' table and `app_follow_options` the cursor, naming the cursor on the architecture page, per the design. Check: build, lint, clang-tidy and docs-build exit 0; `options-state`'s `By its name alone` holds.
  `By its name alone` prints nothing; `keymap_cursor` at `app.c:74`.
- [x] 2.2 Keep the device's `options.txt`; run walks 1 and 2. Check: each frame 0 cells from its board, and each reading of the file as the walk gives it.
  The device held no `options.txt`, so 4.3 removes it; boards from `usb-probe/boards/1794678650-09f9-options/`, `D_Main` from `1794663074-5159-options/`.
  Every named frame 0 cells apart; the desktop and the options opened on Backlight `Auto`, which the walks leave unnamed, match no board.
  Each reading as the walks give it: 76, 76, 75 and 76 bytes in walk 1, 75 in walk 2.

## 3. The light

- [x] 3.1 Give `display_test.c` its three tests; then `DisplayLight` and `display_light`, `backlight.c`'s lights and `app.c`'s two calls, with the architecture page's lines on them, per the design. Check: `mise run test` fails on undeclared `display_light`, then prints 113 `ok` lines, expected; build, lint, clang-tidy and docs-build exit 0; the deltas' five greps hold.
  113 `ok` lines; red at `display_test.c:15`, undeclared `display_light`. The greps print none, two, six, none and one line.
  `backlight_set` leaves and enters through two static helpers, a switch each.
- [x] 3.2 Rewrite the guide's paragraph on the options, per the design. Check: docs-build exits 0; the paragraph holds what `user-guide`'s `Content` lists of the options.
  `docs/guide/using-the-remote.md:60-71`; Vibration `Off`'s flash stays at `:44`.

## 4. With the owner

- [x] 4.1 With frames logged and `v_on` showing, the owner clicks Disconnect on `Claude Remote` in the Mac's Bluetooth settings. Observe, with no press: `no_link`, then `v_on`, each 0 cells from its board.
  `no_link` 75.4 s into the log, `v_on` 1.5 s later as the Mac reconnected by itself, each 0 cells apart.
  The first Disconnect went unlogged: the walk's output was lost in its pipe, so the owner clicked again.
- [x] 4.2 From a launch, tap Back, Down, Right, Back over RPC; 40 s later the owner says whether the display is dark. Tap Back: `b_auto`, and whether it lit. Tap Left, Back; 40 s: whether it is lit. Hold Back; 40 s: whether the desktop is dark. Observe: dark, lit, lit, dark.
  Backlight Time 30 s, by the owner; every frame named 0 cells apart. The owner saw dark, lit, lit and dark.
- [x] 4.3 On `v_on` the owner saves qFlipper's screenshot as `asset/screenshot/options-bt.png`; put the device's `options.txt` back. Check: the image is 512×256 in black and `(254, 138, 44)` alone, its cells `E_options_vibration_on`'s; the file reads as it was kept.
  512×256, black and `(254, 138, 44)` alone, 0 cells apart; the device held no file, so it was removed, and `storage stat` finds none.

## 5. Close

- [x] 5.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
  No finding beyond the guide and the architecture page: `README.md:27` and `docs/index.md:36` stay, by the proposal;
  `docs/guide/usb.md:41` and `using-the-remote.md:99` hold, as `D_stopped` goes dark whichever the option.
- [x] 5.2 Check: `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate options-backlight --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
  113 `ok` lines; words: proposal 658, design 878, tasks 628 as planned, specs up to 545, each within a tenth over.
