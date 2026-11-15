# Tasks

Task 2.2 closes `host-tests`' `By that answer alone`.
Every other scenario of the deltas stands as closed: `app-screen`'s by the dump of 2.1 and 2.2,
which holds the package to the bytes that drew them, `host-tests`' by the 123 tests.
A rename changes no rule, so no task opens with a failing test.
Build, lint, clang-tidy and docs-build are `mise run build`, `mise exec -- ufbt lint`, `mise run clang-tidy` and `mise run docs-build`.
The dump is `.ufbt/toolchain/current/bin/arm-none-eabi-objdump -s dist/f0_claude_remote.fap`, after a build.
No task takes the device (`design.md`, Test seams).
Each count is `develop`'s at `3e2a7e1` plus `view-state`'s delta, none but the header's 38 bytes fewer, so each is marked expected.

## 1. The reference

- [ ] 1.1 Build; keep the dump and `mise run test`'s output in a `mktemp -d`. Check, each expected: 123 `ok` lines; `git grep -c ModeIdle -- src test` sums to 31 in six files; `git grep -c view_idle -- src` to 19 in three; `git grep -n -i idle -- ':!openspec'` prints 66 lines; `wc -c src/ui/view_idle.h` prints 125.

## 2. The names

- [ ] 2.1 Write `ModeMain` for `ModeIdle` wherever it stands. Check: `mise run test` prints 1.1's output; build, lint and clang-tidy exit 0; the dump differs from 1.1's in one line, `.gnu_debuglink`'s checksum; `git grep -n ModeIdle -- src test` prints nothing.
- [ ] 2.2 `git mv` the board's two files to `view_main.h` and `view_main.c`; write `view_main` for `view_idle` in `src/` and in the architecture page's row, per the design. Check: build, lint, clang-tidy and docs-build exit 0; the dump differs from 1.1's in that line alone; `git grep -n view_idle -- src docs` prints nothing; `By that answer alone` holds.
- [ ] 2.3 Rename the three tests and the local, and reword `app.c`'s comment, per the design. Check: `diff` of 1.1's output and `mise run test`'s shows three lines changed, `idle` to `main` in each; build and lint exit 0; `git grep -n -i idle -- ':!openspec'` prints the radio's two lines.

## 3. The proof of a rename

- [ ] 3.1 Read the tree against `HEAD`. Check: `git diff -M --name-status HEAD -- src` prints `R` for the board's two files, the header's score 51 expected; `git diff -M --numstat HEAD -- src test` prints nine files, each with as many lines added as removed, 63 in all, expected.

## 4. Close

- [ ] 4.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; docs-build exits 0.
- [ ] 4.2 Check: `mise run test`, build, lint, clang-tidy, docs-build, `mise exec -- prek run --all-files` and `mise exec -- openspec validate main-screen-name --strict` exit 0; `git status --short` lists the proposal's Impact and this change's files alone; `wc -w` holds the budgets.

## Workflow follow-up

- After the archive, `git grep -n -i idle -- openspec/specs` prints five lines, two of `app-screen` and three of `host-tests`: the ones `main-screen-in-the-specs` takes.
