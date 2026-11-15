# Proposal

## Why

`app-screen`'s `The status follows the link` runs to 610 characters of requirement text
(`openspec show app-screen --type spec --json`) against OpenSpec 2.0.0's 500
(`MAX_REQUIREMENT_TEXT_LENGTH`, `dist/core/validation/constants.js:9` in the pinned package),
so `openspec validate --specs --strict` fails `app-screen` on `develop`, its one failure of 30,
and every plan's third check carries it as noise.
OpenSpec splits such a requirement only in a change made for it, when the owner asks (`schemas/spec-driven/schema.yaml:109`);
the owner asked on 2026-11-15.
It comes now, before `Sent:` in the status row, which rewrites this requirement.

Decisions:

- **Right's hold for USB leaves, with its legend,** not the plate alone:
  without the plate the text stays at 529 characters; without the plate, the legend and `D_disc_voice`'s line, at 351,
  leaving the requirement one behavior, what the status reads per link, and room for `Sent:`.
- **MODIFIED keeps its header and all five scenarios, `The legend` included,**
  not REMOVED and ADDED under new names:
  `schema.yaml:109` prescribes it, and `openspec validate` refuses a MODIFIED block that omits a scenario
  (`dist/core/validation/validator.js:684`).
- **The ADDED requirement's scenario stands as closed,** not checked anew on the device:
  it says what `Opened with no link` already proves, a frame equal to `D_disconnected`,
  whose plate `usb-transport` read off the canvas and saw on the device (its `tasks.md:13`, `:29`).
- **Relatively simple, so implemented on `develop`:** one requirement of one spec, no code, no test, no behavior.
- **It builds on `develop` alone:** `openspec list` shows no queued plan.
- **It lands as `docs(openspec): split the status requirement`,**
  in the type and scope of `4eb4b85`, `docs(openspec): rename the idle screen to main`.

## What Changes

- `The status follows the link` keeps what the status reads per link and the no-link boards' rows, at 351 characters.
- `No link shows Right's hold for USB` takes the plate, the `HOLD` legend and `D_disc_voice`'s none, at 253, its words but `also`.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `app-screen`: `The status follows the link` split in two.

## Impact

`openspec/specs/app-screen/spec.md`, written by the archive.
`src/`, `test/`, `README.md`, `docs/` and `catalog/` stay as they are: no requirement's meaning changes.
