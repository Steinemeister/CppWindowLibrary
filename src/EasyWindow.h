#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace EasyWindow
{
    void init();
    void close();
    void requestClose();
    bool shouldClose();
}