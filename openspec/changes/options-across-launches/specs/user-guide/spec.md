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
  and the main screen, the options with what Left, Right and Back do there
  and that a change is saved on the SD card for the next launch,
  `Listening`, `No link` with `Keys are not sent` and Right's hold for USB and back,
  `Voice stopped: release OK`,
  and `Reconnect stopped` with what a press does there

#### Scenario: Screenshots
- **WHEN** the built page is read
- **THEN** its images are `main.png`, `options-bt.png`, `voice-bt.png`, `no-link-bt.png`, `no-link-usb.png`, `voice-cut-bt.png`
  and `stopped-bt.png` from `asset/screenshot/`, in that order,
  each directly above the paragraph of the screen it shows
