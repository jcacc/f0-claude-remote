# contributor-guide Specification

## Purpose

Says how a change is planned, checked and released, on the site rather than in `CONTRIBUTING.md`,
which only points there.

## Requirements

### Requirement: CONTRIBUTING.md points to the site
`CONTRIBUTING.md` SHALL hold only a pointer to the site's Contributing pages, as `claude-shim`'s does.

#### Scenario: Pointer
- **WHEN** `CONTRIBUTING.md` is read
- **THEN** it links `https://petr-korobeinikov.github.io/f0-claude-remote/contributing/workflow/` and holds no command

### Requirement: The release page names where a release ends up
`docs/contributing/release.md` SHALL say that a release reaches `https://lab.flipper.net/apps/f0_claude_remote`
once the Flipper Apps Catalog merges its pull request, and link that page.

#### Scenario: App's page
- **WHEN** the release page is read
- **THEN** after the `flipper-apps-catalog` job's pull request it links `https://lab.flipper.net/apps/f0_claude_remote`
