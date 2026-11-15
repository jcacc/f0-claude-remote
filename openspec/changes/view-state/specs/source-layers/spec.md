# Spec Delta

## ADDED Requirements

### Requirement: One state crosses to the UI
What a frame shows SHALL cross from the platform to the UI as one state, of a type the UI names,
and the UI SHALL draw a frame from it alone.
The platform SHALL keep one copy of it, with one setter, which takes it whole,
and no word for a value of its own,
so a frame never shows a state half set.

#### Scenario: Drawn from one state
- **WHEN** `git grep -n -E '_draw\([^,]*, const ViewState\* state\);' -- src/ui` runs
- **THEN** it prints three lines, a draw call each: the view's and its two boards'

#### Scenario: Set whole
- **WHEN** `git grep -n 'screen_set_' -- src/platform/screen.h` runs
- **THEN** it prints one line, `screen_set_state`'s

#### Scenario: No word of its own
- **WHEN** `git grep -n '_Atomic' -- src` runs
- **THEN** it prints nothing
