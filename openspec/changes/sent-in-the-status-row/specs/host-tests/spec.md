# Spec Delta

## ADDED Requirements

### Requirement: The core says how long a sent action stays named
For how long `app-screen`'s status row names an action SHALL be decided in `src/core/`:
3 s for each action that flashes, and no time for any other.
The feedback's suite SHALL pin it, and the platform SHALL name an action by that answer alone.

#### Scenario: Named
- **WHEN** the core is asked of effort high, effort max, clear, Esc, Enter and each arrow
- **THEN** it answers 3000 ms

#### Scenario: Not named
- **WHEN** it is asked of no action, the start or the stop of voice, exit, giving up or starting over
- **THEN** it answers none

#### Scenario: By that answer alone
- **WHEN** `git grep -n 'feedback_sent_ms' -- src/ui src/platform` runs
- **THEN** it prints one line of `app.c`
