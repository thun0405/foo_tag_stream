#pragma once
#include "stdafx.h"

class ControlManager {
public:
    ControlManager(CWindow& control, CWindow* window);

    void UpdateSize(int diffWidth, int diffHeight);
    void UpdatePosition(int diffWidth, int diffHeight);

protected:
    CWindow& m_control;
    CWindow* m_window;
    CSize m_currentSize;
    CPoint m_currentPosition;
};