#include "stdafx.h"
#include "ControlManager.h"

ControlManager::ControlManager(CWindow& control, CWindow* window)
    : m_control(control), m_window(window)
{
    // �R���g���[���̌��݂̈ʒu�ƃT�C�Y���擾
    CRect rect;
    m_control.GetWindowRect(&rect);
    m_window->ScreenToClient(&rect);

    m_currentSize = rect.Size();
    m_currentPosition = rect.TopLeft();
}

void ControlManager::UpdateSize(int diffWidth, int diffHeight) {
    // �V�����R���g���[���̕��ƍ������v�Z
    int controlWidth = m_currentSize.cx + diffWidth;
    int controlHeight = m_currentSize.cy + diffHeight;

    // �R���g���[���̃T�C�Y��ύX
    m_control.MoveWindow(m_currentPosition.x, m_currentPosition.y, controlWidth, controlHeight, TRUE);
    m_control.Invalidate();

    // �V�����T�C�Y��ۑ�
    m_currentSize.cx = controlWidth;
    m_currentSize.cy = controlHeight;
}

void ControlManager::UpdatePosition(int diffWidth, int diffHeight) {
    // �R���g���[���̐V�����ʒu���v�Z
    int controlX = diffWidth + m_currentPosition.x;
    int controlY = diffHeight + m_currentPosition.y;

    // �R���g���[���̈ʒu���X�V
    m_control.MoveWindow(controlX, controlY, m_currentSize.cx, m_currentSize.cy, TRUE);
    m_control.Invalidate();

    // �V�����ʒu��ۑ�
    m_currentPosition.x = controlX;
    m_currentPosition.y = controlY;
}