# DSA

LeetCode-style data structures and algorithms practice in C++23.

## Structure

```
dsa/
├── 0001_two_sum/
│   ├── solution.cpp
│   └── notes.md
├── 0002_add_two_numbers/
│   └── ...
└── ...
```

Each problem lives in its own directory with a `solution.cpp`, optional `notes.md`, and sometimes variant files (`solution_suboptimal.cpp`, `solution_wrong.cpp`). Every C++ file starts with a `// Problem:` comment holding its LeetCode URL; problems without a LeetCode page (company OAs, tracked under the reserved `9xxx` range, e.g. `9001_minimum_adjacent_swaps_to_separate_binary_array`) put the problem description there instead. Helper scripts live in `scripts/`.

## Getting Started

```sh
just build     # configure + compile
just test      # run all tests
just test-one 0001  # run a single problem
just random    # pick a random problem (JSON: | jq '.url', | from json)
```

Run bare `just` to list every available recipe.

## Commands

| Command | Description |
|---------|-------------|
| `just build` | Build everything |
| `just release` | Build the Release tree |
| `just test` | Run all tests |
| `just test-one PATTERN` | Run tests matching pattern |
| `just random` | Pick a random problem to practice (emits JSON for `jq` / nushell `from json`) |
| `just log` | Scaffold/open today's practice-diary entry |
| `just log-add NUM` | Append a diary section for a problem |
| `just log-topics [NAME]` | List or scaffold a topic note |
| `just log-summary` | JSON summary of every logged attempt |
| `just configure` | (Re)generate the build system |
| `just index` | Symlink compile_commands.json for clangd |
| `just fmt` | Format all source files |
| `just fmt-check` | Verify formatting without modifying |
| `just lint` | Run clang-tidy (report only, no auto-fix) |
| `just check-links` | Verify every problem file starts with a `// Problem:` header |
| `just check` | Build + test + fmt-check + check-links + lint |
| `just new NUM NAME` | Scaffold a new problem |
| `just clean` | Remove build directories |

## Adding a Problem

```sh
just new 0004 median_of_two_sorted_arrays
```

This creates `dsa/0004_median_of_two_sorted_arrays/solution.cpp` from the template.

## Practice Diary

A private, **git-ignored** `journal/` records what was attempted and what to
review, kept in two layers:

```
journal/                     # git-ignored
├── daily/2026-10-12.md      # one entry per timed session
└── topics/bfs.md            # evolving notes per DSA concept
```

```sh
just log                # scaffold/open today's entry in $EDITOR
just log-add 0102       # append a blank section for that problem
just log-topics bfs     # open (or list) a concept note
just log-summary        # JSON: outcomes, per-tag pass rates, flagged problems
```

Each problem section is a `## NNNN Title — <done/partial/failed/learned>` heading with a
`tags:` line and `missed / correct / couldn't see / review` prompts. Problem
numbers are resolved through the `// Problem:` headers, and `just log-summary`
aggregates the headings so you can see weak areas over time:

```sh
just log-summary | from json | get by_tag     # nushell
```

## Requirements

- CMake 3.25+
- C++23 compiler
- just
- Python 3 (for `just random` / `scripts/random_problem.py`)
- clang-format / clang-tidy (optional, for formatting/linting)
