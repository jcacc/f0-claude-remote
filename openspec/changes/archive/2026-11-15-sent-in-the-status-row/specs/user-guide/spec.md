# Spec Delta

## MODIFIED Requirements

### Requirement: Using the remote covers every button and screen
`docs/guide/using-the-remote.md` SHALL give each button's tap and hold, what it sends and does in Claude Code,
the buzz, the flash and the top row's `Sent:` confirming it, and each screen, below its screenshot.

#### Scenario: Content
- **WHEN** the page is read
- **THEN** it holds the twelve rows of the keys table,
  what the left arrow does on an empty prompt,
  that the top row reads `Sent:` and the button's label for 3 s after an action,
  that Vibration `Off` leaves the screen alone to confirm,
  and the main screen, whose legend gives its place at the first press there to the battery as the device's status bar draws it, the lightning included,
  the options with what Up, Down, Left, Right and Back do there,
  that Backlight `Auto` leaves the screen to the device's Backlight Time, where a press lights it and acts,
  and that a change is saved on the SD card for the next launch,
  `Listening`, `No link` with `Keys are not sent` and Right's hold for USB and back,
  `Voice stopped: release OK`,
  and `Reconnect stopped` with what a press does there

#### Scenario: Screenshots
- **WHEN** the built page is read
- **THEN** its images are `main.png`, `options-bt.png`, `voice-bt.png`, `no-link-bt.png`, `no-link-usb.png`, `voice-cut-bt.png`
  and `stopped-bt.png` from `asset/screenshot/`, in that order,
  each directly above the paragraph of the screen it shows
