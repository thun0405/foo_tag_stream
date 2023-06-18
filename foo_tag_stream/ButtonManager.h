#pragma once
#include "stdafx.h"
#include "ControlManager.h"

class ButtonManager {
public:
    ButtonManager(CButton& button, CWindow* window);

    void UpdatePosition(int diffWidth, int diffHeight);

private:
    CButton& m_button;
    ControlManager m_controlManager;
};
