#include "stdafx.h"
#include "TabContent2.h"

LRESULT TabContent2::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // ウィンドウのクライアント領域を取得
    RECT rect;
    GetClientRect(&rect);

    // エディットコントロールの作成
    m_edit.Create(m_hWnd, &rect, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL);

    // フォントの作成
    HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

    // フォントの設定
    m_edit.SendMessage(WM_SETFONT, (WPARAM)hFont, TRUE);

    return 0;
}

//LRESULT TabContent2::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
//{
//    PAINTSTRUCT ps;
//    HDC hdc = BeginPaint(&ps);
//    RECT rect;
//    GetClientRect(&rect);
//    DrawText(hdc, _T("This is Tab 2"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//    EndPaint(&ps);
//    return 0;
//}
