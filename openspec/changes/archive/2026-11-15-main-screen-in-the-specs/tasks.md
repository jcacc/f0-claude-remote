# Tasks

Every scenario of the deltas stands as closed, none changing its meaning (`proposal.md`, Why):
no task changes code or takes the device.

## 1. The docs against the tree

- [x] 1.1 Read `README.md` and `docs/` against the tree for statements the change makes false; fix each. Check: the findings listed in this task's notes; `mise run docs-build` exits 0.
  - No finding: `git grep -n -i idle -- README.md docs/` prints `docs/internals/bluetooth.md:83` alone, the radio's idle, not the screen's.
  - `mise run docs-build` exits 0, "No issues found".

## 2. Close

- [x] 2.1 Check: `mise exec -- prek run --all-files` and `mise exec -- openspec validate main-screen-in-the-specs --strict` exit 0; `git status --short` lists this change's files alone; `wc -w` holds the budgets.
  - Both exit 0; `git status --short` lists `tasks.md` alone.
  - `wc -w`: proposal 436, design 199, app-screen 420, host-tests 235, tasks 176 before these notes.

## Workflow follow-up

- After `mise exec -- openspec archive main-screen-in-the-specs -y`, `git diff --numstat -- openspec/specs` prints two lines added and two removed in `app-screen`, three and three in `host-tests`, `idle` to `main` on each, and `git grep -n -i idle -- openspec/specs` prints nothing, each expected.
