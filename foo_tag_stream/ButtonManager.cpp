#include "stdafx.h"
#include "ButtonManager.h"

ButtonManager::ButtonManager(CButton button, CWindow* window)
    : m_button(button)
{
    // �{�^���̌��݂̈ʒu�ƃT�C�Y���擾
    CRect rect;
    m_button.GetWindowRect(&rect);
    window->ScreenToClient(&rect);

    m_currentSize = rect.Size();
    m_currentPosition = rect.TopLeft();
}

void ButtonManager::UpdatePosition(int diffWidth, int diffHeight) {
    // �{�^���̐V�����ʒu���v�Z
    int buttonX = diffWidth + m_currentPosition.x;
    int buttonY = diffHeight + m_currentPosition.y;

    // �{�^���̈ʒu���X�V
    m_button.MoveWindow(buttonX, buttonY, m_currentSize.cx, m_currentSize.cy, TRUE);
    m_button.Invalidate();

    // �V�����ʒu��ۑ�
    m_currentPosition.x = buttonX;
    m_currentPosition.y = buttonY;
}
