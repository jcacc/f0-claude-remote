# Proposal

## Why

The Flipper Apps Catalog took Claude Remote 0.4:
its record at `catalog.flipperzero.one/api/v0/0/application/f0_claude_remote` reads `"status":"READY"`, `"version":"0.4"`,
and its page is `https://lab.flipper.net/apps/f0_claude_remote`.
Nothing in the repository names it:
Quick start installs by building the source, which needs an Apple Silicon Mac, mise and a clone (`docs/quick-start.md:9-17`),
Installation offers a Release and the source (`docs/guide/installation.md:17,27`),
and the README's Installation holds the build's commands alone (`README.md:53-67`).
A reader with no Mac to build on, the catalog's own audience, finds no route that needs no build.

Decisions:

- **The Flipper Apps Catalog is the first route everywhere a route is offered,**
  not added after the Release:
  it needs a phone or a Chromium browser and no file handling,
  and it updates from the same place (`https://docs.flipper.net/zero/apps`).
- **Quick start installs from the Flipper Apps Catalog,**
  not from the source:
  the page is for a user, and the build moves to Installation's routes, linked from step 1.
- **Removal from the Flipper Apps Catalog names `apps_data/f0_claude_remote/` "if it is left",**
  not as left or as gone:
  Flipper's docs say only that the 🗑 icon deletes the app, not what becomes of its data.
- **The release page says where a release ends up,**
  the app's page once the owner's pull request is merged,
  as the 0.4 record shows.
- **The GitHub Release's notes and the repository's homepage stay as they are:**
  the notes are git-cliff's section alone (`docs/contributing/release.md:65-70`),
  and the homepage is the site, which now leads to the Flipper Apps Catalog.
- **Relatively simple, so implemented on `develop`:** text in four site pages and the README, no code.
- **It builds on `develop` alone:** no plan is queued.
- **It lands as `docs: install from the Flipper Apps Catalog`.**

## What Changes

- `README.md`'s Installation opens with the app's page in the Flipper Apps Catalog, the build's commands after it.
- Installation gains the route "From the Flipper Apps Catalog", first, with its update and removal.
- Quick start's step 1 installs from the Flipper Apps Catalog.
- Home names the Flipper Apps Catalog after its link to Quick start.
- The release page links the app's page as where a merged submission ends up.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `user-guide`: Quick start and Installation install from the Flipper Apps Catalog first; Home and the README link its page.
- `contributor-guide`: the release page names the app's page in the Flipper Apps Catalog.

## Impact

`README.md`, `docs/index.md`, `docs/quick-start.md`, `docs/guide/installation.md` and `docs/contributing/release.md`.
`application.fam`'s `fap_weburl`, `catalog/`, `.github/workflows/release.yml` and every screenshot stay as they are.
