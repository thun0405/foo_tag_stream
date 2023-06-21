#include "stdafx.h"
#include "ButtonManager.h"

ButtonManager::ButtonManager(CButton& button, CWindow* window)
    : m_button(button), m_controlManager(button, window)
{}

void ButtonManager::UpdatePosition(int diffWidth, int diffHeight)
{
    m_controlManager.UpdatePosition(diffWidth, diffHeight);
}
