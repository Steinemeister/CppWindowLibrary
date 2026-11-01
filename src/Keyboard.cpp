#include "Keyboard.h"
#include "Window.h"

namespace EasyWindow
{
    bool isKeyPressed(int key)
    {
        const GLFWwindow *windowHandle = getWindowHandle();
        if (!windowHandle)
        {
            return false;
        }
        int state = glfwGetKey(const_cast<GLFWwindow *>(windowHandle), key);
        return state == GLFW_PRESS;
    }
}