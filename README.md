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
pip install -r requirements.txt    # installs Conan into .venv
```

Tool versions are pinned in `.tool-versions` (compatible with both mise and asdf).
A `mise.toml` configures a Python virtual environment (`.venv/`) so that IDE
tools like Pylance and mypy can resolve Conan imports.

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

Every PR triggers two workflows automatically:

- **Lint** (`lint.yml`) — MegaLinter (YAML, Markdown, Python, CMake, shell) +
  clang-format checks for C++ via `cpp-linter-action`
- **Build** (`build.yml`) — CMake configure, build, and unit tests (ctest) on:
  - Linux (ubuntu-latest, GCC)
  - macOS (macos-latest, Apple Clang)
  - Windows (windows-latest, MSVC)

### Label-Driven Workflows

- **`verify` label** (`verify.yml`) — runs integration tests on all platforms
  using `conan create` with RC version format (`X.Y.Z-dev-<short-sha>`)
- **`publish` label** (`publish.yml`):
  - Validates that `CMakeLists.txt` version is bumped vs the PR base branch
  - Checks that the release version does not already exist in `conan-stable`
  - Builds RC packages on all platforms
  - Uploads RC packages to `conan-rc` remote (JFrog Artifactory)

### Release on Merge

When a `publish`-labeled PR is merged (`release.yml`):

1. Version is extracted from `CMakeLists.txt`
2. Git tag `vX.Y.Z` is created
3. GitHub Release is created with auto-generated release notes
4. Conan packages are built and published to `conan-stable` for all platforms
5. Platform-specific `.tar.gz` artifacts (headers + libraries) are attached to
   the GitHub Release

## Versioning

- Semantic versioning (SemVer)
- Version source of truth: `CMakeLists.txt` `project(VERSION X.Y.Z)`
- Pre-merge RC builds: `numops/X.Y.Z-dev-<short-sha>`
- Release builds: `numops/X.Y.Z`
- `publish`-labeled PRs must bump version above base branch before RC publish

## Conan Package

### Remotes

The project uses two Conan remotes hosted on JFrog Artifactory:

- **`conan-rc`** — release candidate packages (pre-merge, `X.Y.Z-dev-<sha>`)
- **`conan-stable`** — final release packages (post-merge, `X.Y.Z`)

### Installation

```shell
conan remote add conan-stable <JFROG_URL>/conan-stable
conan install --requires=numops/<version> -r conan-stable
```

### Usage in CMake

```cmake
find_package(numops CONFIG REQUIRED)
target_link_libraries(your_target PRIVATE numops::numops)
```

### Required GitHub Secrets

| Secret | Description |
| ------------ | ---------------------------------------- |
| `JFROG_URL` | JFrog Artifactory Conan API base URL |
| `JFROG_USER` | JFrog username or email |
| `JFROG_TOKEN` | JFrog access token |

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
