# source-layers Specification

## Purpose

Keeps each source file in the folder of its layer,
so a path names the layer and an include line shows which way a dependency points.

## Requirements

### Requirement: Every source file sits in its layer's folder
`src/` SHALL hold no file directly and no deeper folder:
each source file and header sits in `src/core/`, `src/ui/` or `src/platform/`.

#### Scenario: Paths
- **WHEN** `git ls-files src | grep -vE '^src/(core|ui|platform)/[^/]+$'` runs
- **THEN** it prints nothing

### Requirement: Includes point down the layers
A file SHALL include nothing from a layer above its own:
the core includes only from its own folder,
and the UI reaches outside its folder only into the core.

#### Scenario: The core
- **WHEN** `git grep -E '#include "[^"]*/' -- src/core` runs
- **THEN** it prints nothing

#### Scenario: The UI
- **WHEN** `git grep -E '#include "[^"]*/' -- src/ui | grep -vF '"../core/'` runs
- **THEN** it prints nothing

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
