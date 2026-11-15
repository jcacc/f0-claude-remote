# Tasks

Every scenario of the delta stands as closed (`design.md`): no task changes code or takes the device.

## 1. Close

- [x] 1.1 Check: `mise exec -- prek run --all-files` and `mise exec -- openspec validate split-the-status-requirement --strict` exit 0; `git status --short` lists this change's files alone; `wc -w` holds the budgets.
  Both exit 0; `git status --short` empty before this tick.
  Words: proposal 356, design 77, tasks 95, spec 295.

## Workflow follow-up

- After `mise exec -- openspec archive split-the-status-requirement -y`, `git diff --numstat -- openspec/specs` prints `10 4 openspec/specs/app-screen/spec.md`, and `mise exec -- openspec validate --specs --strict` prints `Totals: 30 passed, 0 failed (30 items)`, each expected.
