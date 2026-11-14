# Spec Delta

## MODIFIED Requirements

### Requirement: Using the remote covers every button and screen
`docs/guide/using-the-remote.md` SHALL give each button's tap and hold, what it sends and does in Claude Code,
the buzz and flash confirming it, and each screen, below its screenshot.

#### Scenario: Content
- **WHEN** the page is read
- **THEN** it holds the twelve rows of the keys table,
  what the left arrow does on an empty prompt,
  that Vibration `Off` leaves the flash alone to confirm,
  and the main screen, the options with what Left, Right and Back do there, `Listening`, `No link` with `Keys are not sent` and Right's hold for USB and back,
  `Voice stopped: release OK`,
  and `Reconnect stopped` with what a press does there

#### Scenario: Screenshots
- **WHEN** the built page is read
- **THEN** its images are `main.png`, `options-bt.png`, `voice-bt.png`, `no-link-bt.png`, `no-link-usb.png`, `voice-cut-bt.png`
  and `stopped-bt.png` from `asset/screenshot/`, in that order,
  each directly above the paragraph of the screen it shows

### Requirement: The README shows every screen
`README.md` SHALL show `asset/screenshot/main.png` on top
and, in `## Screens` after `## Features`, the other seven screenshots, two to a row and the last alone, each 256 px wide.

#### Scenario: Screens
- **WHEN** `README.md` is read
- **THEN** `## Screens` follows `## Features` and shows, row by row,
  `main-usb.png` and `voice-bt.png`, `no-link-bt.png` and `no-link-usb.png`, `voice-cut-bt.png` and `stopped-bt.png`, then `options-bt.png`,
  each `width="256"` with alt text naming its screen
