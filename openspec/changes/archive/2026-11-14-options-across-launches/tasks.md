# Tasks

Task 1.1's suite closes `host-tests`' `Opened` and `Taken from the card`, with `Changed`, `Stayed` and `The buzz` as they stand;
2.1's greps `The platform follows` and `Handed once`;
2.2's walk `options`' `Opened again`, `Written`, `Left at once` and `Nothing to write`;
3.1 `Another file`; 3.2 `Not written`; 2.4 `user-guide`'s `Content`, with `Screenshots` as it stands.
`options`' `Off` and `On again` stand as `options-screen`'s task 4.1 closed them: the buzz's lines stay (`src/platform/app.c:40-42`).
Groups 2 and 3 take the device, unlocked on the cable, with the paired Mac in range:
frames are read over RPC against the boards at `1794663074-5159`, less their cells in y 31-43,
the file is read and planted over the console, and the only presses are the walks' (`design.md`).

## 1. The core

- [x] 1.1 Add `test_keymap_takes_the_saved_vibration`; then `keymap_set_vibration`. Check: `mise run test` fails on the undeclared function, then prints 108 `ok` lines; `mise exec -- ufbt lint` exits 0.

## 2. The file

- [x] 2.1 Add `options_file` and its lines of `app.c` per the design, naming the file in `docs/internals/architecture.md`. Check: `mise run build`, lint, `mise run clang-tidy` and `mise run docs-build` exit 0; `git grep -n 'keymap_vibration' -- src/platform` prints five lines of `app.c`, and `keymap_set_vibration` one; the architecture page names every file of `git ls-files src` once.
- [x] 2.2 Run the first walk. Check: each frame and each reading of the file is as the walk gives it.
  Every frame 0 cells apart outside y 31-43; no file after the first open and close; then `false`, `true`, and `false` after the exit.
  Back's hold went out the moment `E_options_vibration_off` showed, 22 ms after Right; `loader info` then found no application running.
- [x] 2.3 After that walk, with the application open, read the console's `top`. Check: the application's thread shows 512 or more under `Stack Min`; the notes give that number and, from the walk's log, the milliseconds from each change's tap to its frame.
  `Stack Min` 1480 of 2044 after the walk; read also mid-walk, after both writes in one launch: 1400.
  From the short press to the frame: Right 22 ms, Left 24 ms, Right 22 ms.
- [x] 2.4 Edit the four other pages per the design. Check: docs-build exits 0; `git grep -n -i -E 'each launch|nothing is saved' -- README.md docs catalog` prints nothing.

## 3. The files it cannot use

- [x] 3.1 Run the second walk. Check: `E_options_vibration_on` after each of the three launches, and the file whole after the change.
  Each file planted with `storage write_chunk` after `loader close`, each launch by `loader open`; every frame 0 cells apart outside y 31-43.
- [x] 3.2 Run the third walk. Check: its four frames; then the console's `storage stat` finds no `options.txt`, file or folder.
  `E_options_vibration_on`, `_off`, the desktop after the hold, then `_on`; `storage stat` read `Directory` after the change.

## 4. Close

- [x] 4.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
  No finding beyond the design's five pages: `docs/internals/bluetooth.md:35` names the keys' file alone, which stays true.
- [x] 4.2 Check: `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate options-across-launches --strict` exit 0; `git diff --name-only develop` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.
  108 `ok` lines; words: proposal 585, design 870, specs 176-393, tasks 573 as planned.
