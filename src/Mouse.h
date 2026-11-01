#pragma once

#include <functional>

namespace EasyWindow
{
    bool isMouseButtonPressed(int button);

    double getMouseX();
    double getMouseY();

    double getScrollX();
    double getScrollY();
}