# xml-imgui

`xml-imgui` converts declarative XML UI descriptions into a C++ representation that can later be rendered with [Dear ImGui](https://github.com/ocornut/imgui).

The long-term goal is to let frontend/UI authors describe tools and panels in XML, while C++ code consumes a validated object tree and binds it to runtime behavior.

## Current Status

This repository currently contains the initial project infrastructure:

- C++20 library target: `xml_imgui`
- Minimal CLI target: `xml_imgui_cli`
- CMake presets for Debug and Release builds
- Basic test executable wired into CTest
- GitHub Actions CI template
- Product requirements draft in `docs/PRD.md`

## Build

Requirements:

- CMake 3.20+
- Ninja
- A C++20 compiler

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

## Try the CLI

```sh
echo '<Window title="Demo"></Window>' | ./build/debug/xml_imgui_cli
```

Expected output:

```txt
root: Window
```

## Project Direction

The parser is intentionally tiny for now. The next milestones are:

1. Define the XML schema for ImGui concepts.
2. Parse attributes and child nodes.
3. Add validation and useful diagnostics.
4. Map XML nodes to an intermediate UI object tree.
5. Generate or drive Dear ImGui rendering code from that tree.

See `docs/PRD.md` for the first planning draft.
