# Tasks

No design: text alone, no code. The Flipper Apps Catalog's steps follow `https://docs.flipper.net/zero/apps`.

## 1. Pages

- [ ] 1.1 In `docs/guide/installation.md`, add "From the Flipper Apps Catalog" before "From a Release": Install on the app's page, in Flipper Mobile App over Bluetooth or Flipper Lab in a Chromium browser over USB; Apps → Bluetooth; Installed → Update; Installed → 🗑, then `apps_data/f0_claude_remote/` if it is left. The front matter names the route. Check: the page against `Routes`.
- [ ] 1.2 In `docs/quick-start.md`, step 1 installs from the Flipper Apps Catalog as 1.1 does, and links Installation for the other routes. Check: the page against `Steps`.
- [ ] 1.3 In `docs/index.md`, link the app's page after Quick start's link. Check: `mise run docs-build` exits 0, and the built Home's first link is Quick start.
- [ ] 1.4 In `README.md`'s Installation, link the app's page before the commands, which follow as the source's, and name "the other routes" for "the Release build". Check: the README against `Links`.
- [ ] 1.5 In `docs/contributing/release.md`, after the pull request is opened by hand, say the Flipper Apps Catalog's merge brings the release to the app's page, linked. Check: the page against `App's page`.

## 2. Close

- [ ] 2.1 Check: `mise exec -- prek run --all-files`, `mise run docs-build` and `mise exec -- openspec validate flipper-apps-catalog-install --strict` exit 0; `wc -w` holds the budgets.

## Workflow follow-up

- After `mise exec -- openspec archive flipper-apps-catalog-install -y`, `git diff --numstat -- openspec/specs` prints `8 0` for `contributor-guide` and `14 2` for `user-guide`, and `mise exec -- openspec validate --specs --strict` prints `Totals: 30 passed, 0 failed (30 items)`, each expected.
