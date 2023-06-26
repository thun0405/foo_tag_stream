#pragma once
#include "stdafx.h"

class MainWindow : public CWindowImpl<MainWindow, CWindow, CFrameWinTraits>
{
public:
    DECLARE_WND_CLASS_EX(L"MainWindowClass", CS_HREDRAW | CS_VREDRAW, COLOR_WINDOW)

    BEGIN_MSG_MAP(MainWindow)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
    CTabCtrl m_tab;
};

void ShowMainWindow();