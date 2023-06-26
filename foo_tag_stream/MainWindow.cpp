#include "stdafx.h"
#include "MainWindow.h"

LRESULT MainWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    RECT rcClient;
    GetClientRect(&rcClient);

    m_tab.Create(m_hWnd, rcClient, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_tab.InsertItem(0, _T("Tab 1"));
    m_tab.InsertItem(1, _T("Tab 2"));

    return 0;
}

LRESULT MainWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    PostQuitMessage(0);
    return 0;
}

void ShowMainWindow() {
    MainWindow wnd;
    wnd.Create(NULL); // NULLは親ウィンドウのハンドルを指定します。ここでは親ウィンドウがないのでNULLを指定します。
    wnd.ShowWindow(SW_SHOW);
}
