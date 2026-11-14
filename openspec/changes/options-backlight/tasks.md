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

- [ ] 1.1 Note `mise run test`'s count of `ok` lines, 108 expected. Give `keymap_test.c` the design's tests; then add `OptionBacklight`, the keymap's cursor and `options_file_keys`' row. Check: `mise run test` fails on undeclared `OptionBacklight`, then prints 112 `ok` lines, expected; build, lint and clang-tidy exit 0.

## 2. The rows

- [ ] 2.1 Give `screen` the cursor's word, `view_draw` and `view_options_draw` the cursor, `view_options.c` its rows' table and `app_follow_options` the cursor, naming the cursor on the architecture page, per the design. Check: build, lint, clang-tidy and docs-build exit 0; `options-state`'s `By its name alone` holds.
- [ ] 2.2 Keep the device's `options.txt`; run walks 1 and 2. Check: each frame 0 cells from its board, and each reading of the file as the walk gives it.

## 3. The light

- [ ] 3.1 Give `display_test.c` its three tests; then `DisplayLight` and `display_light`, `backlight.c`'s lights and `app.c`'s two calls, with the architecture page's lines on them, per the design. Check: `mise run test` fails on undeclared `display_light`, then prints 113 `ok` lines, expected; build, lint, clang-tidy and docs-build exit 0; the deltas' five greps hold.
- [ ] 3.2 Rewrite the guide's paragraph on the options, per the design. Check: docs-build exits 0; the paragraph holds what `user-guide`'s `Content` lists of the options.

## 4. With the owner

- [ ] 4.1 With frames logged and `v_on` showing, the owner clicks Disconnect on `Claude Remote` in the Mac's Bluetooth settings. Observe, with no press: `no_link`, then `v_on`, each 0 cells from its board.
- [ ] 4.2 From a launch, tap Back, Down, Right, Back over RPC; 40 s later the owner says whether the display is dark. Tap Back: `b_auto`, and whether it lit. Tap Left, Back; 40 s: whether it is lit. Hold Back; 40 s: whether the desktop is dark. Observe: dark, lit, lit, dark.
- [ ] 4.3 On `v_on` the owner saves qFlipper's screenshot as `asset/screenshot/options-bt.png`; put the device's `options.txt` back. Check: the image is 512×256 in black and `(254, 138, 44)` alone, its cells `E_options_vibration_on`'s; the file reads as it was kept.

## 5. Close

- [ ] 5.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
- [ ] 5.2 Check: `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate options-backlight --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
