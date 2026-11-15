# Proposal

## Why

Once `main-screen-name` is archived, the code and three requirements name the screen `main` (its `proposal.md:47-52`),
and three other requirements still point at it as `the idle screen`, on five lines:
two of `app-screen` (`openspec/specs/app-screen/spec.md:150`, `:278`)
and three of `host-tests` (`openspec/specs/host-tests/spec.md:138`, `:148`, `:155`).
With `view-state` and `main-screen-name` archived in a copy,
`grep -n -i idle` over `openspec/specs/` prints these five lines alone.
The owner's call of 2026-11-15 has the specs take the name with the code, not after it
(`main-screen-name`'s `proposal.md:26-27`),
so this change follows that one in the queue.

Decisions:

- **Two changes, this one second,** not one:
  `main-screen-name`'s proposal gives the word counts (its `proposal.md:28-32`).
- **Each requirement is MODIFIED and carried whole,**
  not edited by hand under `skip_specs: true`, as `spec-purposes`' Purposes were:
  the archive ignores a delta's Purpose (`schemas/spec-driven/schema.yaml:116-117` in the pinned package),
  which sent that change by hand (its `proposal.md:16-20`), but applies a MODIFIED requirement.
- **`The status follows the link` is carried at its 610 characters** (`openspec show app-screen --type spec --json`),
  not trimmed or split to OpenSpec 2.0.0's 500:
  OpenSpec keeps a MODIFIED block whole, and splits a long requirement only in a change of its own, when the owner asks
  (`schema.yaml:109`).
  `openspec validate --specs --strict` already fails `app-screen` for it on `develop`, and the three archives flag no spec anew.
- **Each reworded scenario stands as closed,** not closed anew by a task:
  the idle and the main screen are one (`main-screen-name`'s `proposal.md:5`),
  so no scenario changes its meaning, and no line outside `openspec/` changes.
- **Relatively simple, so implemented on `develop`:** five lines of two specs, no code, no test, no behavior.
- **It builds on `view-state`, then `main-screen-name`, and comes last:**
  `main-screen-name` builds on `view-state` and has this change follow it (its `proposal.md:31-32`, `:40-42`),
  and `host-tests`' delta carries `view-state`'s text of the requirement both change (`openspec/config.yaml:180`).
- **It lands as `docs(openspec): rename the idle screen to main`,**
  in the type and scope of `5a92901`, `docs(openspec): fill out two spec purposes`,
  the one other `docs(openspec)` subject in `git log`.

## What Changes

- Five lines say `main screen` where they said `idle screen`; no other word changes.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `app-screen`: `The status follows the link` and `The battery takes the legend's place` name the main screen.
- `host-tests`: `The core decides when the legend ends` names it, on `view-state`'s text.

## Impact

`openspec/specs/app-screen/spec.md` and `openspec/specs/host-tests/spec.md`, five lines, written by the archive.
`src/`, `test/`, `README.md`, `docs/` and `catalog/` stay as they are:
with `main-screen-name` applied, `idle` stands outside `openspec/` in the radio's two lines alone (its `tasks.md:20`).
