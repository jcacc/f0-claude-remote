## MODIFIED Requirements

### Requirement: Quick start reaches a dictated prompt
`docs/quick-start.md` SHALL take a reader to a prompt dictated and sent from the device,
each step linking its Guide page.

#### Scenario: Steps
- **WHEN** the page is read
- **THEN** it holds, in order, the install from the Flipper Apps Catalog, pairing, the `keybindings.json` block with `/voice hold`,
  and a try: hold OK, speak, release, wait out `Voice: processing…`, tap OK

### Requirement: Installation offers each route
`docs/guide/installation.md` SHALL name what the app needs,
then offer the Flipper Apps Catalog, the latest Release's `.fap` and the source, in that order,
each with its update and removal.

#### Scenario: Routes
- **WHEN** the page is read
- **THEN** it names firmware 1.5.1, a computer taking a Bluetooth keyboard or, over a cable, a USB one,
  Claude Code 2.1.311 as tried,
  and for the source an Apple Silicon Mac with mise;
  the Flipper Apps Catalog installs from `https://lab.flipper.net/apps/f0_claude_remote`
  through Flipper Mobile App or Flipper Lab, and updates and removes under Installed;
  the `.fap` goes into the SD card's `apps/Bluetooth/` through qFlipper,
  and the source runs `mise trust`, `mise install`, `mise run setup` and `mise run launch`

## ADDED Requirements

### Requirement: The README and Home link the Flipper Apps Catalog
`README.md`'s Installation SHALL open with a link to `https://lab.flipper.net/apps/f0_claude_remote`,
and `docs/index.md` SHALL link it after Quick start.

#### Scenario: Links
- **WHEN** `README.md` and the built Home page are read
- **THEN** the README's Installation links the page before its first command,
  and Home links it while its first link stays Quick start
