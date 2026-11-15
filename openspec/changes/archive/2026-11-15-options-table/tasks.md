# Tasks

The keymap's suite, on the new names, closes `host-tests`' `Changed`, `Stayed`, `Opened` and `Taken from the card`,
and the feedback's `The buzz`, as it stands;
task 2.2's greps close `The platform follows`, `No function of one option` and `Handed once`.
Build, lint, clang-tidy and docs-build are `mise run build`, `mise exec -- ufbt lint`, `mise run clang-tidy` and `mise run docs-build`.
Group 3 takes the device, unlocked on the cable, with the paired Mac in range, and no hand of the owner's:
frames are read over RPC against the ones `develop` draws, kept beside the repository,
the file is read and planted over the console, and the only presses are the walks' (`design.md`),
run as `options-across-launches`' tasks 2.2, 3.1 and 3.2 ran them.

## 1. The core

- [x] 1.1 Note `mise run test`'s count of `ok` lines, 108 expected. Give `keymap_test.c` the new names; then add `option.h`, named on the architecture page, the keymap's table and `app.c`'s six lines, per the design. Check: `mise run test` fails on undeclared `keymap_option`, then prints 108 `ok` lines; build, lint, clang-tidy and docs-build exit 0.
  108 `ok` lines before and after; red at `keymap_test.c:848`, undeclared `keymap_option` and `OptionVibration`.
  clang-tidy passes the keymap's loop over `Option`, so no `size_t` index.

## 2. The followers

- [x] 2.1 Give `options_file` its keys, `options_file_read_option` and `options_file_set_option`, and `app.c` the opening's loop, per the design. Check: build, lint and clang-tidy exit 0; `git grep -n -E 'options_file_(set_)?vibration' -- src` prints nothing.
  The header and every option's line go out through `options_file_write`, a static helper the design leaves unnamed.
- [x] 2.2 Give `view_draw`, `view_options_draw` and `screen` the options by `Option`, `app.c` `app_follow_options`, and the architecture page its lines on the options, per the design. Check: build, lint, clang-tidy and docs-build exit 0; the spec's three greps hold; the page names every file of `git ls-files src` once.
  `keymap_option` at `app.c:42`, `:70` and `:133`; `keymap_set_option` at `app.c:134`.

## 3. The walks

- [x] 3.1 Read the device's `options.txt` and keep it; run the design's three walks; plant the file back. Check: each frame 0 cells from `develop`'s, and each reading of the file as the walks give it; the file planted back reads as it was kept.
  The device held no `options.txt`, so none was planted back; frames against `usb-probe/boards/1794663074-5159-options/`, drawn by `cf1818e`.
  Every frame named, 0 cells apart, but the desktop after each Back held; walk 1 read `false`, `true`, `false`, then `off` on relaunch.
  Walk 2 ran again after a first plant appended to the old file: `write_chunk` appends, so each plant now follows `storage remove`.

## 4. Close

- [x] 4.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
  No finding beyond the architecture page: the guide speaks of Vibration as a user meets it, which stays, and `docs/development/host-tests.md:37-39` names no function.
- [x] 4.2 Check: `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate options-table --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
  108 `ok` lines; words: proposal 438, design 772, spec 433, tasks 534 as planned.
  OpenSpec 2.0.0 failed the archived `The core holds the options' values`, 560 characters: cut to 498 in wording alone;
  `validate --specs --strict` then flags `app-screen` alone, as on `develop`, the queued plans archived after it or not.
