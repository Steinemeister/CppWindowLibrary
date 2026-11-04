# CppWindowLibrary

CppWindowLibrary provides a small, straightforward C++ API for creating one GLFW window and reading keyboard, mouse, and controller input.

## Features

- Simple window lifecycle (`init`, `close`, `shouldClose`, `requestClose`)
- Polling or waiting for events
- Keyboard input helpers
- Mouse button, cursor position, and scroll delta helpers
- Gamepad presence, button, and axis helpers
- Optional terminal input monitor (`debugPrintAllInput`)

## Requirements

- CMake 3.14+
- A C++17-compatible compiler
- Internet access during first configure step (GLFW is fetched via CMake `FetchContent`)

## Build

```bash
git clone https://github.com/Steinemeister/CppWindowLibrary.git
cd CppWindowLibrary
cmake -S . -B build
cmake --build build
```

This builds:
- `EasyWindow` (static library)
- `BeispielApp` (example executable in `example/`)

## Usage

Include the umbrella header:

```cpp
#include "EasyWindow.h"
```

Small usage snippet:

```cpp
#include "EasyWindow.h"
#include <GLFW/glfw3.h>

int main() {
    EasyWindow::init();

    while (!EasyWindow::shouldClose()) {
        EasyWindow::GetEvents(EasyWindow::EventGettingMode::Poll);

        if (EasyWindow::isKeyPressed(GLFW_KEY_SPACE)) {
            EasyWindow::debugPrintAllInput();
        }
    }

    EasyWindow::close();
    return 0;
}
```

Basic loop:

```cpp
EasyWindow::init();

while (!EasyWindow::shouldClose()) {
    EasyWindow::GetEvents(EasyWindow::EventGettingMode::Poll);

    if (EasyWindow::isKeyPressed(GLFW_KEY_ESCAPE)) {
        EasyWindow::requestClose();
    }
}

EasyWindow::close();
```

## Public API Overview

### Window
- `void init()`
- `void GetEvents(EventGettingMode mode = EventGettingMode::Poll)`
- `void close()`
- `bool shouldClose()`
- `void requestClose()`
- `const GLFWwindow* getWindowHandle()`

### Keyboard
- `bool isKeyPressed(int key)`

### Mouse
- `bool isMouseButtonPressed(int button)`
- `double getMouseX()`
- `double getMouseY()`
- `double getScrollX()`
- `double getScrollY()`

### Controller
- `bool isControllerPresent(int jid = 0)`
- `bool isControllerButtonPressed(int button, int jid = 0)`
- `float getControllerAxis(int axis, int jid = 0)`

### Debug
- `void debugPrintAllInput()`

## License

MIT — see [LICENSE](LICENSE).
