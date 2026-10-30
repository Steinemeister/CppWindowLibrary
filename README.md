# CppWindowLibrary

A small C++ library using GLFW to simplify multi-window management.

## File structure

```text
CppWindowLibrary/
├── CMakeLists.txt
├── include/
│   └── CppWindowLibrary/
│       ├── Window.hpp
│       └── WindowManager.hpp
├── src/
│   ├── Window.cpp
│   └── WindowManager.cpp
└── examples/
    └── multiwindow_demo.cpp
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Example

`examples/multiwindow_demo.cpp` creates two GLFW windows and updates them through `WindowManager`.
