#pragma once
#include "stdafx.h"

class ButtonManager {
public:
    ButtonManager(CButton& button, CWindow* window);

    //void InitializeButtons();
    void UpdatePosition(int diffWidth, int diffHeight);

private:
    CButton& m_button;
    CSize m_currentSize;
    CPoint m_currentPosition;
};
