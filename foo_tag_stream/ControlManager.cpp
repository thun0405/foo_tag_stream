#include "stdafx.h"
#include "ControlManager.h"

ControlManager::ControlManager(CWindow& control, CWindow* window)
    : m_control(control), m_window(window)
{
    // コントロールの現在の位置とサイズを取得
    CRect rect;
    m_control.GetWindowRect(&rect);
    m_window->ScreenToClient(&rect);

    m_currentSize = rect.Size();
    m_currentPosition = rect.TopLeft();
}

void ControlManager::UpdateSize(int diffWidth, int diffHeight) {
    // 新しいコントロールの幅と高さを計算
    int controlWidth = m_currentSize.cx + diffWidth;
    int controlHeight = m_currentSize.cy + diffHeight;

    // コントロールのサイズを変更
    m_control.MoveWindow(m_currentPosition.x, m_currentPosition.y, controlWidth, controlHeight, TRUE);
    m_control.Invalidate();

    // 新しいサイズを保存
    m_currentSize.cx = controlWidth;
    m_currentSize.cy = controlHeight;
}

void ControlManager::UpdatePosition(int diffWidth, int diffHeight) {
    // コントロールの新しい位置を計算
    int controlX = diffWidth + m_currentPosition.x;
    int controlY = diffHeight + m_currentPosition.y;

    // コントロールの位置を更新
    m_control.MoveWindow(controlX, controlY, m_currentSize.cx, m_currentSize.cy, TRUE);
    m_control.Invalidate();

    // 新しい位置を保存
    m_currentPosition.x = controlX;
    m_currentPosition.y = controlY;
}