set minimum-version := '1.27.0'

source_dir         := 'dsa'
build_dir          := 'build'
release_dir        := 'build-release'
solution_template  := 'templates/solution.cpp'

# Show all available recipes, grouped by category
default:
    @just --list --unsorted

# ---------------------------------------------------------------- setup

# Generate the build system.
# Run once, or after editing the CMakeLists.txt files.
[group('setup')]
configure:
    cmake -B {{build_dir}} -DCMAKE_BUILD_TYPE=Debug

# Symlink compile_commands.json into the project root, e.g. for clangd
[group('setup')]
index: configure
    ln -sfn {{build_dir}}/compile_commands.json compile_commands.json

# ---------------------------------------------------------------- build

# Build every target in Debug mode
[group('build')]
build: configure
    cmake --build {{build_dir}} --parallel

# Build every target in Release mode
[group('build')]
release:
    cmake -S . -B {{release_dir}} -DCMAKE_BUILD_TYPE=Release
    cmake --build {{release_dir}} --parallel

# ---------------------------------------------------------------- test

# Run every registered test
[group('test')]
test: build
    ctest --test-dir {{build_dir}} --output-on-failure --parallel

# Run only tests matching a pattern, e.g. `just test-one 0001`
[group('test')]
test-one PATTERN: build
    ctest --test-dir {{build_dir}} --output-on-failure -R {{PATTERN}}

# ---------------------------------------------------------------- quality

# Format every C++ source file in place
[group('quality')]
fmt:
    @find {{source_dir}} templates \( -name '*.cpp' -o -name '*.hpp' \) -print0 | xargs -0 clang-format -i

# Verify that all sources are formatted, without modifying them
[group('quality')]
fmt-check:
    @find {{source_dir}} templates \( -name '*.cpp' -o -name '*.hpp' \) -print0 | xargs -0 clang-format --dry-run --Werror

# Lint everything with clang-tidy and apply fixes
[group('quality')]
lint: configure
    clang-tidy -p {{build_dir}} --fix {{source_dir}}/**/*.cpp

# Full verification: build, test, format-check and lint
[group('quality')]
check: build test fmt-check lint
    @echo 'All checks passed'

# ---------------------------------------------------------------- scaffold

# Scaffold a new problem folder,
# e.g. `just new 0004 median_of_two_sorted_arrays`
[group('scaffold')]
new NUMBER NAME:
    mkdir -p '{{source_dir}}/{{NUMBER}}_{{NAME}}'
    cp {{solution_template}} '{{source_dir}}/{{NUMBER}}_{{NAME}}/solution.cpp'
    @echo 'Created {{source_dir}}/{{NUMBER}}_{{NAME}}/solution.cpp'

# ---------------------------------------------------------------- maintenance

# Remove all build artifacts
[confirm('This will permanently delete ' + build_dir + '/ and ' + release_dir + '/. Continue?')]
[group('maintenance')]
clean:
    rm -rf {{build_dir}} {{release_dir}}

# ---------------------------------------------------------------- aliases

alias b  := build
alias r  := release
alias t  := test
alias t1 := test-one
alias n  := new
alias cf := configure
alias i  := index
alias f  := fmt
alias l  := lint
alias c  := clean