# Design

## Context

See `proposal.md`, Why.
No layer, source file or test is in play:
each delta carries its requirement whole from the text the queue leaves it in, and the archive writes it into `openspec/specs/`.

| Requirement | Carried from |
|---|---|
| `The status follows the link` | `openspec/specs/app-screen/spec.md:136-163` |
| `The battery takes the legend's place` | `openspec/specs/app-screen/spec.md:277-294` |
| `The core decides when the legend ends` | `openspec/changes/view-state/specs/host-tests/spec.md:33-57` |

`grep -rn` of the three names over both queued plans finds the third alone, in `view-state`;
`diff` of each block and its source prints the five lines alone, `idle` to `main` on each.

## Goals / Non-Goals

**Goals:** with the queue archived, `openspec/specs/` holds no `idle`.

**Non-Goals:** the archived changes, which keep `idle` as written, in 55 files on `develop`.

## Decisions

None beyond the proposal's: each line has one word to change, and nothing else is in play.

## Risks / Trade-offs

- A plan applied before this one rewords one of the three requirements → the archive would write this plan's older text over it; the diff in the tasks' follow-up shows a line besides the five, and the delta is carried anew.
