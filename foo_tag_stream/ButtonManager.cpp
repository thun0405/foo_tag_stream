#include "stdafx.h"
#include "ButtonManager.h"

ButtonManager::ButtonManager(CButton button, CWindow* window)
    : m_button(button)
{
    // ボタンの現在の位置とサイズを取得
    CRect rect;
    m_button.GetWindowRect(&rect);
    window->ScreenToClient(&rect);

    m_currentSize = rect.Size();
    m_currentPosition = rect.TopLeft();
}

void ButtonManager::UpdatePosition(int diffWidth, int diffHeight) {
    // ボタンの新しい位置を計算
    int buttonX = diffWidth + m_currentPosition.x;
    int buttonY = diffHeight + m_currentPosition.y;

    // ボタンの位置を更新
    m_button.MoveWindow(buttonX, buttonY, m_currentSize.cx, m_currentSize.cy, TRUE);
    m_button.Invalidate();

    // 新しい位置を保存
    m_currentPosition.x = buttonX;
    m_currentPosition.y = buttonY;
}
