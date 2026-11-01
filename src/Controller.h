#pragma once

namespace EasyWindow {
    bool isControllerPresent(int jid = 0);
    bool isControllerButtonPressed(int button, int jid = 0);
    float getControllerAxis(int axis, int jid = 0);
}