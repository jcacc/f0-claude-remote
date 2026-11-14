# Proposal

## Why

Every action the remote sends buzzes the device (`src/platform/app.c:40-42`),
and the one switch for it is the firmware's, Settings → LCD and Notifications → Vibro,
which silences every application
(`notification_settings_app.c:236-237`, `notification_app.c:205`, `:297`, firmware 1.5.1).
The owner asked on 2026-11-04 for a switch that keeps the vibration,
and on 2026-11-14 put the options first, Vibration and Backlight.
Claude Design drew them at canvas version `1794663074-5159`:
a gear joined to Back's plate on `D_Main`, `D_usb_main` and the nine `D_sent_*` boards,
and five `E_options_*` boards of two rows (notes `noteE` and `risksE`).

Decisions:

- **This change brings the options' screen and Vibration, and Backlight is the next change,**
  not both at once:
  together they leave the budgets, and Backlight's `Auto` is undecided,
  as `noteE` has a press on a dark screen only light it,
  while SDK 1.5.1 lets an application send to the backlight and read nothing back
  (`notification.h:12`, `:89-108`).
  Until then the boards' `Backlight` row stays empty,
  and Up and Down, the cursor's keys, idle.
- **Vibration is `On` at every launch,**
  not saved at each change, as `noteE` has it:
  a file on the SD card brings its own decisions, the path, the format and a card left out,
  so keeping the options is a change of its own.
- **A tap on Back opens the options from `D_Main` alone** (`noteE`),
  not from a no-link board, which shows no gear.
  A hold leaves from the options too, never showing them first (`risksE`, item 1):
  a hold sends no tap (`input.c:146-149`, firmware 1.5.1).
- **A lost link leaves the options open, under the no-link mark** (`E_options_no_link`),
  not closed for `D_disconnected`, which a tap on Back then shows.
  Once the offer stops, 60 s after the drop, `D_stopped` takes their place:
  there any button starts over.
- **With Vibration `Off` the flash alone confirms** (`risksE`, item 7),
  so the guide, the README and the Flipper Apps Catalog's description
  stop promising that no buzz means nothing sent.
- **Frames are read over RPC through taps that send no key and do not buzz,**
  Back's, and Left's and Right's on the options;
  the owner gives one trial of the buzz, one Disconnect in the Mac's Bluetooth settings
  and three screenshots in qFlipper, as in `3f65835`.
- **Complex, so implemented on `feature/options-screen`:**
  two modes, three layers, three suites, five specs and the owner's hands.
- **It builds on `develop` alone:** no plan is queued.
- **It lands as `feat(options): add an options screen with a vibration switch`.**

## What Changes

- A tap on Back on the main screen opens the options, marked by a gear in Back's plate.
- The options show `Vibration`, which a tap on Left or Right turns `Off` or `On` at once:
  `Off`, no action buzzes, and each still acts and flashes.
- A link lost on the options changes their mark alone.
- The guide, the README, the Flipper Apps Catalog's description and three screenshots follow.

## Capabilities

### New Capabilities

- `options`: how Back opens and closes the options, what the buttons do there, and Vibration.

### Modified Capabilities

- `app-screen`: a tap on Back ends nothing, and the options have boards of their own.
- `button-actions`: the buzz takes Vibration `On`, and the taps and holds the options closed.
- `host-tests`: the core holds Vibration, decides the buzz from it, and keeps the options lit.
- `user-guide`: twelve rows of keys, and the options in the guide and the README.

## Impact

The core's `mode.h`, `display.c`, keymap and feedback, with three suites;
the UI's `view` and `view_idle.c`, and `view_options` and `view_plate`, new;
the platform's `screen` and `app.c`;
`asset/image/options.png`, new;
`asset/screenshot/main.png`, `main-usb.png` and `options-bt.png`, new and linked under `docs/assets/screenshot/`;
`README.md`, `docs/index.md`, `docs/guide/using-the-remote.md`, `docs/guide/troubleshooting.md`,
`docs/internals/architecture.md` and `catalog/description.md`.
The transport, `actions.c`, `deed.c`
and the screenshots `.github/workflows/release.yml` lists stay as they are.
Every other requirement holds as written with the options closed,
as each already holds outside voice,
and `app-screen`'s flashes on the boards the canvas redrew.
