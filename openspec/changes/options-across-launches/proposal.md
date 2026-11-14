# Proposal

## Why

Vibration turned `Off` is `On` again at the next launch (`src/core/keymap.c:92`),
as `options` has it (`openspec/specs/options/spec.md:41`, `:53-55`)
and the guide says (`docs/guide/using-the-remote.md:61`),
so it is turned `Off` again at every launch.
`options-screen` left keeping the options as a change of its own,
for the decisions a file on the SD card brings: the path, the format and a card left out
(`openspec/changes/archive/2026-11-14-options-screen/proposal.md:25-28`).
The canvas has the options saved at once, a write for each change
(`noteE`, and `risksE`, item 6, at version `1794663074-5159`).
It comes now, as `options-screen` landed in `cf1818e`,
and ahead of Backlight, by the owner's call of 2026-11-14.

Decisions, the firmware's files being 1.5.1's:

- **The file is `options.txt` in the application's data folder, `apps_data/f0_claude_remote/`,**
  not beside the firmware's own settings in `/int` (`bt_settings.c:11`):
  the documentation gives that folder to what an application generates, configuration included,
  and names its example `config.txt` (Apps Data folder Example),
  the pairing's keys are there (`src/platform/transport_bluetooth.c:43`),
  and removing the application takes the one folder (`docs/guide/installation.md:26-27`).
- **It is FlipperFormat's text, a type, a version and a line for each option,**
  not `saved_struct`'s checksummed binary, which those settings use (`bt_settings.c:18-33`):
  that refuses a file of another size or version (`saved_struct.c:94-110`),
  so Backlight would be a second version to read, as the desktop's is (`desktop_settings.c:27-52`),
  where here it is one more line.
  The stock BadUSB keeps its settings so (`bad_usb_app.c:31-95`).
- **A change is written at once (`noteE`),**
  not on leaving, as BadUSB writes (`bad_usb_app.c:203`):
  a reboot or an empty battery then loses nothing.
- **A file the application cannot read is no file, so Vibration is `On`;
  one it cannot write changes nothing else, and no board says so:**
  the canvas draws none,
  and the application is on that card itself (`docs/guide/installation.md:21`),
  so it never opens with the card out.
- **The link is not kept:**
  `usb-link`'s `Opened again` stands (`openspec/specs/usb-link/spec.md:27-29`).
- **The device checks take no hand of the owner's:**
  taps of Back, Left and Right around the options send no key and do not buzz
  (`openspec/specs/options/spec.md:9-11`, `:22-26`),
  the file is read over the console,
  and the buzz's lines stay as they are (`src/platform/app.c:40-42`).
- **Complex, so implemented on `feature/options-across-launches`:**
  the application writes to the card for the first time,
  from a platform file no suite builds,
  in a format later releases must read, and six scenarios take the device.
- **It builds on `develop` alone:** no plan is queued.
- **It lands as `feat(options): keep the options across launches`.**

## What Changes

- Vibration opens as it was left:
  a change is written to the SD card at once and read at the next opening.
- `apps_data/f0_claude_remote/options.txt` holds it as three lines of text.
- With no file, or one the application cannot read, Vibration is `On`,
  and nothing is written until a change.
- The guide, the installation's removal, the USB page, the host tests' page and the architecture follow.

## Capabilities

### New Capabilities

None.

### Modified Capabilities

- `options`: Vibration holds across launches, and the options are kept in a file on the SD card.
- `host-tests`: the keymap takes the saved value at the opening, and the platform keeps what it answers.
- `user-guide`: the guide says a change is kept across launches.

## Impact

`src/core/keymap.h`, `src/core/keymap.c` and `test/keymap_test.c`;
`src/platform/options_file.h` and `src/platform/options_file.c`, new, and `src/platform/app.c`;
`docs/guide/using-the-remote.md`, `docs/guide/installation.md`, `docs/guide/usb.md`,
`docs/development/host-tests.md` and `docs/internals/architecture.md`.
The UI, the transport, `feedback.c`, `application.fam`, `README.md` and `catalog/` stay as they are:
the README's and the description's line on the options holds as written (`README.md:27`, `catalog/description.md:10-11`).
