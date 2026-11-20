## ADDED Requirements

### Requirement: The release page names where a release ends up
`docs/contributing/release.md` SHALL say that a release reaches `https://lab.flipper.net/apps/f0_claude_remote`
once the Flipper Apps Catalog merges its pull request, and link that page.

#### Scenario: App's page
- **WHEN** the release page is read
- **THEN** after the `flipper-apps-catalog` job's pull request it links `https://lab.flipper.net/apps/f0_claude_remote`
