# numops

A trivial C++ arithmetic library demonstrating a fully automated CI/CD pipeline
with Conan 2 packaging, multi-platform builds, and label-driven release workflows.

## Overview

This project implements a complete DevOps CI/CD pipeline for a small C++ library.
The library itself is intentionally simple — the focus is on the build, test,
packaging, and release automation.

## Library

`numops` provides basic arithmetic operations:

- `add(int a, int b)` — addition
- `subtract(int a, int b)` — subtraction
- `multiply(int a, int b)` — multiplication

## Building

### Prerequisites

- C++17 compatible compiler
- [mise](https://mise.jdx.dev/) (or [asdf](https://asdf-vm.com/)) for tool
  version management
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html) (install via
  Homebrew: `brew install clang-format`)

### Setup

```shell
mise install                       # installs Python, CMake, and linter tools
pip install -r requirements.txt    # installs Conan
```

### Build from source

```shell
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build
```

### Build with Conan

```shell
conan create .
```

## CI/CD Pipeline

### Pull Request Verification

Every PR triggers:

- **Linting** — MegaLinter (YAML, Markdown, Python, CMake, shell) +
  clang-format/clang-tidy for C++
- **Build matrix** — Linux (GCC), macOS (Apple Clang), Windows (MSVC)
- **Unit tests** — GoogleTest via CTest
- **Dependency pinning** — Conan profiles ensure deterministic builds

### Label-Driven Workflows

- **`verify`** — triggers integration tests (consumer project builds against
  the library package)
- **`publish`** — builds release candidate packages and uploads to `conan-rc`

### Release on Merge

When a `publish`-labeled PR is merged:

1. Conan packages are published to `conan-stable`
2. Git tag `vX.Y.Z` is created
3. GitHub Release is created with release notes

## Versioning

- Semantic versioning (SemVer)
- Version source of truth: `CMakeLists.txt` `project(VERSION X.Y.Z)`
- Pre-merge RC builds: `numops/X.Y.Z-dev-<short-sha>`
- Release builds: `numops/X.Y.Z`

## Conan Package

### Installation

```shell
conan install --requires=numops/1.0.0
```

### Usage in CMake

```cmake
find_package(numops CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE numops::numops)
```

## Linting

Linting runs automatically on every PR via GitHub Actions. To run locally:

```shell
clang-format --dry-run --Werror include/**/*.h src/*.cpp tests/*.cpp
markdownlint-cli2 "**/*.md"
yamllint -c .yamllint.yml .github/workflows/*.yml
ruff check .
```

## Project Structure

```text
├── CMakeLists.txt              # Build system (version source of truth)
├── conanfile.py                # Conan 2 package recipe
├── .tool-versions              # Tool versions for mise/asdf
├── requirements.txt            # Python dependencies (Conan)
├── cmake/                      # CMake package config template
├── conan/profiles/             # Platform-specific Conan profiles
├── include/numops/             # Public headers
├── src/                        # Implementation
├── tests/                      # Unit tests (GoogleTest)
├── test_package/               # Integration test (Conan consumer)
├── scripts/                    # Repository setup automation
├── .github/workflows/          # CI/CD pipelines
├── .clang-format               # C++ formatting rules
├── .clang-tidy                 # C++ static analysis config
├── .mega-linter.yml            # MegaLinter configuration
├── .markdownlint.yml           # Markdown linting rules
└── .yamllint.yml               # YAML linting rules
```

## License

[MIT](LICENSE)
