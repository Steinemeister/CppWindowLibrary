#pragma once

struct GLFWwindow;

namespace EasyWindow::Internal {

    void InitMouseCallbacks(GLFWwindow* window);

    void ResetScrollDeltas();
}