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

Each problem lives in its own directory with a `solution.cpp` and optional `notes.md`.

## Getting Started

```sh
just build     # configure + compile
just test      # run all tests
just test-one 0001  # run a single problem
```

## Commands

| Command | Description |
|---------|-------------|
| `just build` | Build everything |
| `just test` | Run all tests |
| `just test-one PATTERN` | Run tests matching pattern |
| `just fmt` | Format all source files |
| `just lint` | Run clang-tidy with auto-fix |
| `just new NUM NAME` | Scaffold a new problem |
| `just clean` | Remove build directory |

## Adding a Problem

```sh
just new 0004 median_of_two_sorted_arrays
```

This creates `dsa/0004_median_of_two_sorted_arrays/solution.cpp` from the template.

## Requirements

- CMake 3.25+
- C++23 compiler
- just
- clang-format / clang-tidy (optional, for formatting/linting)
