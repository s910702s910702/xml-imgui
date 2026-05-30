# Dependencies

This project uses system/package-manager dependencies instead of vendoring third-party source code at this stage.

## Required Build Dependencies

| Dependency | Purpose | macOS | Ubuntu CI |
| --- | --- | --- | --- |
| CMake | Build system generator | `brew install cmake` | `apt-get install cmake` |
| Ninja | Default CMake preset generator | `brew install ninja` | `apt-get install ninja-build` |
| libxml2 | XML parser frontend | `brew install libxml2` | `apt-get install libxml2-dev` |

## macOS Setup

Install all Homebrew dependencies from the repository root:

```sh
brew bundle
```

`libxml2` is intentionally treated as the XML frontend. The project should focus on AST conversion, semantic validation, and code generation instead of implementing XML parsing from scratch.

## Version Tracking

Homebrew does not pin exact formula versions in a portable way by default. For now:

- `Brewfile` records the required package set.
- CI validates against current runner packages.
- Release notes should record known-good dependency versions.

When reproducibility becomes important, consider one of:

- `vcpkg` manifest mode for cross-platform pinned C/C++ dependencies.
- `Conan` lockfiles for pinned package graphs.
- A checked-in container image definition for Linux CI.

## CMake Integration

The project uses CMake's built-in `FindLibXml2` module:

```cmake
find_package(LibXml2 REQUIRED)
target_link_libraries(xml_imgui PUBLIC LibXml2::LibXml2)
```

On macOS, CMake may find either the system `libxml2` or Homebrew's `libxml2`, depending on local paths. If CMake cannot locate Homebrew's keg-only install, configure with:

```sh
cmake --preset debug -DCMAKE_PREFIX_PATH="$(brew --prefix libxml2)"
```
