# Tasks

Task 3.1's walk closes `options`' `Opened`, `Closed` and `A value`, `app-screen`'s `Vibration` and `Short press`,
and `button-actions`' `A tap with no action`;
4.1 `Off`, `On again` and `An action`; 4.2 `Dropped and back` and `No link`; 3.3 and 4.3 `user-guide`'s;
the suites of 3.1 and 3.2 every other scenario of the deltas, by the mode each board is drawn for.
Groups 1 to 4 take the device, unlocked on the cable, with the paired Mac in range:
frames are read over RPC and compared with the boards at `1794663074-5159`.
The only presses over RPC are the walk's (`design.md`), and group 4 waits for the owner's word.

## 1. The plate and the title row

- [ ] 1.1 Keep a frame of `D_Main` from `mise run launch`. Move the plate's parts to `view_plate` and every status row to `view_draw_title_row`, naming `view_plate` in `docs/internals/architecture.md`. Check: `mise run build`, `mise exec -- ufbt lint`, `mise run clang-tidy` and `mise run docs-build` exit 0; the frame, kept again, equals the first; `git grep -n -E 'view_idle_draw_(outline|fill|white)' -- src` prints nothing.

## 2. The gear

- [ ] 2.1 Write `asset/image/options.png` from the design's grid, mode `1`, through the toolchain's Pillow, with the script outside the repository; draw Back's plate per the design. Check: the PNG read back holds 24 black cells of 49; build, lint and clang-tidy exit 0; launched, a frame equals `D_Main`, 0 of 8,192 cells apart.

## 3. The options

- [ ] 3.1 Add the design's keymap tests and the display's two asserts; then both modes in every switch, Vibration in the keymap, `view_options`, and the screen's fourth word. Check: `mise run test` fails on undeclared `ModeOptions`, then prints 106 `ok` lines, expected; build, lint and clang-tidy exit 0; the design's walk shows its four frames.
- [ ] 3.2 Add `test_nothing_vibrates_with_vibration_off`, and pass `true` in the feedback's other asserts; then give `feedback_vibrates` Vibration, the keymap's in `app.c`. Check: `mise run test` fails on the call's arguments, then prints 107 `ok` lines, expected; build, lint and clang-tidy exit 0; `git grep -c keymap_vibration -- src/platform/app.c` ends in `:3`.
- [ ] 3.3 Edit the pages per the design, but for the options' paragraph and the README's row. Check: docs-build and `mise exec -- prek run --files catalog/description.md` exit 0; `git grep -n -i 'no buzz' -- README.md docs catalog` prints three lines, the guide's two and troubleshooting's row; the architecture page names every file of `git ls-files src` once.

## 4. With the owner

- [ ] 4.1 With frames logged, the owner sets Vibration `Off`, closes the options and taps Up on a scratch Claude Code session, then sets it `On` and taps Up. Observe: `Off`, the arrow acts with no buzz, a frame `D_sent_up`, then `D_Main`; `On`, a buzz.
- [ ] 4.2 With frames logged, the owner clicks Disconnect on `Claude Remote` in the Mac's Bluetooth settings, on `D_Main` and again on the options. Observe, with no press on the device: `D_disconnected`, then `D_Main`; `E_options_no_link`, then `E_options_vibration_on`, each less its cells in y 31-43.
- [ ] 4.3 The owner saves qFlipper's screenshots of `D_Main`, `D_usb_main` and the options as `main.png`, `main-usb.png` and `options-bt.png` in `asset/screenshot/`; link the third under `docs/assets/screenshot/`, and add the options' paragraph and the README's row. Check: each is 512×256 in black and `(254, 138, 44)` alone; `main.png`'s cells equal task 2.1's frame; docs-build exits 0.

## 5. Close

- [ ] 5.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
- [ ] 5.2 Check: `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate options-screen --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
