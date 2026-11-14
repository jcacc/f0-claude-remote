# Design

## Context

See `proposal.md`, Why.
The value and its default stay in the core's keymap (`src/core/keymap.c:15`, `:92`).
Platform-specific code gains `options_file.c`, which keeps the options in a file on the SD card:
the storage and FlipperFormat exist only in the firmware.

| Fact | Where |
|---|---|
| An application's data folder is `/ext/apps_data/<appid>`, on the SD card alone, reached as `APP_DATA_PATH` | documented: Apps Data folder Example, `developer.flipper.net/flipperzero/doxygen/example_app_data.html` |
| Opening a file there makes the folder | its source, `example_apps_data.c:22-26`; `storage_processing.c:535-542`, firmware 1.5.1 |
| A read answers whether it succeeded, and a file is closed even after a failed open | documented: `flipper_format.h:437-450`, `storage.h:80` |
| A bool is written `true` or `false`, and any word but `true` reads as `false` | `flipper_format_stream.c:315`, `:422`, firmware 1.5.1 |

## Goals / Non-Goals

**Goals:** the specs'.

**Non-Goals:** a second option's line, which Backlight's change adds.

## Decisions

- **The keymap opens with Vibration `On` and takes the card's value through `keymap_set_vibration`,**
  not through `keymap_alloc(bool vibration)`:
  the default would move to the platform, where the file is read,
  and the suite's 28 calls of `keymap_alloc` and its table of allocators (`test/keymap_test.c:877`) would change.
- **`app.c` hands `options_file` the keymap's value after every event, and it writes only a value other than the one it holds,
  as `backlight_set` lights (`src/platform/backlight.c:31-33`),**
  not an action the keymap answers:
  a state followed after every event cannot be missed
  (`openspec/changes/archive/2026-11-13-transport-from-the-link/proposal.md:28-30`).
- **`options_file` takes and gives a `bool`,**
  not the keymap: `app.c` alone stands between the keymap and what follows it.
- **The value is the format's bool,**
  not the screen's `On` and `Off`: words for the platform to parse are a rule outside the core.
- **A value is taken from the card only where the read answers true,**
  not read over the default in place:
  that a failed read leaves its argument is in the sources alone (`flipper_format_stream.c:353`).
- **Each change gets one attempt, the value held moving before the write,**
  not after it succeeds:
  a write cut short leaves the card with no value, and a change back would meet the held one and write nothing.
- **The card is written after the screen's three lines of `app_settle`,**
  not before: the row shows its value while the card is written (`src/platform/app.c:66`).

The parts:

- `options_file.c` holds the storage's record and the value,
  behind `options_file_alloc(vibration)`, `_free`, `_vibration` and `_set_vibration`.
  Its path `APP_DATA_PATH("options.txt")`, type `Claude Remote Options`, version 1 and key `Vibration` are each a `static const`.
  `alloc` holds the value handed, then reads: the existing file, the header, type and version compared, the bool.
  `set_vibration` returns on the value held; otherwise it holds the new one and writes: the file opened always, the header, the bool.
  Each opens, closes and frees the file, whatever the open answered.
- `app.c`, at the opening: `keymap_alloc()`, `options_file_alloc(keymap_vibration(…))`,
  `keymap_set_vibration(…, options_file_vibration(…))`, then the rest as now.
  In `app_settle`, `options_file_set_vibration` follows `screen_set_vibration`. The file is freed beside the keymap.

New in `keymap_test.c`, `test_keymap_takes_the_saved_vibration`:
handed `false`, then `true`, a fresh keymap answers each, `ModeNoLink`, `LinkBluetooth` and `KeymapWaitStart` standing.

The walks run over RPC and the console, a held Back kept until the long press.
`on` and `off` are `E_options_vibration_on` and `E_options_vibration_off`:

1. No file: launch; Back: `on`; Back again: still no file. Back, Right: `off`, the file's three lines with `false`. Left: with `true`.
   Right, Back held at once: the application ends, the file with `false`. Launch; Back: `off`.
2. Three files, each planted before a launch, with `Vibration: false` where they have the line:
   the type `Other`; the version 2; no `Vibration`.
   Each launch, Back: `on`. After the third, Right: the file's three lines with `false`.
3. A folder planted as `options.txt`: launch; Back: `on`; Right: `off`; Back held; launch; Back: `on`. The folder is removed.

The pages:
`docs/guide/using-the-remote.md:61` says `On` until changed, and after line 62 that a change is saved on the SD card at once for the next launch;
`docs/guide/installation.md:27`, that the folder holds the options too;
`docs/guide/usb.md:51`, that the link is not saved;
`docs/development/host-tests.md:38` lists the options' file;
`docs/internals/architecture.md` gains a row for `options_file`, hands it Vibration at line 56, and gives the opening a sentence.

Test seams:
`keymap.c`, its suite, red at the undeclared function;
`options_file.c` and `app.c`, with no host test, the build's types, `host-tests`' two greps, and the walks' frames and file.

## Risks / Trade-offs

- The stack runs short, a crash by App Manifests (`developer.flipper.net/flipperzero/doxygen/app_manifests.html`) → its `top`, after the first walk:
  under 512 bytes never used, twice the firmware's floor (`thread.c:27`), `stack_size` doubles.
  By the SDK image's disassembly none of these calls runs deeper than 768 bytes below its caller,
  where a key's press already runs to 704 (`stack-probe/probe.sh`, beside the repository).
- A slow card holds the loop while it writes → the row is drawn first, and the walk notes the milliseconds from each change's tap to its frame.
- A write cut short leaves a file with no value → the next launch opens `On`, and the next change writes the file whole.
- A tap meeting another board acts there, Left or Right on `D_Main` as an arrow to the Mac → the walks send each tap only on the frame it is for.
