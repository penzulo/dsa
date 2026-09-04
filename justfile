# List all available commands (like `npm run` with no args)
default:
    @just --list

# Configure the build directory (run once, or after CMakeLists.txt changes)
configure:
    cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Build everything
build: configure
    cmake --build build --parallel

# Run every test
test: build
    ctest --test-dir build --output-on-failure --parallel

# Run only tests matching a pattern: `just test-one 0001`
test-one PATTERN: build
    ctest --test-dir build --output-on-failure -R {{PATTERN}}

# Format every source file in place
fmt:
    find . -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i

# Lint everything
lint: configure
    clang-tidy -p build --fix dsa/**/*.cpp

# Nuke the build directory and start fresh
clean:
    rm -rf build

# Scaffold a new dsa problem folder
new NUMBER NAME:
    mkdir -p dsa/{{NUMBER}}_{{NAME}}
    cp templates/solution.cpp dsa/{{NUMBER}}_{{NAME}}/solution.cpp
