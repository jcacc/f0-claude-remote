# Spec Delta

## MODIFIED Requirements

### Requirement: The platform follows the options
The platform SHALL show the options and their cursor, keep the values on the SD card and buzz
by the core's answers alone, at the opening as after an event.
Every unit SHALL reach an option by its name among the options,
through no function named for one option and no comparison with an enumerator.

#### Scenario: The platform follows
- **WHEN** `git grep -n -E 'keymap_(option|cursor)' -- src/platform` runs
- **THEN** it prints seven lines of `app.c`:
  one hands the card its fallback, two give the backlight its light,
  two give the screen's state the options and the cursor, one hands the card each option,
  and one asks about the buzz

#### Scenario: By its name alone
- **WHEN** `git grep -n -E '_(vibration|backlight)\(|(==|!=) Option' -- src` runs
- **THEN** it prints nothing
