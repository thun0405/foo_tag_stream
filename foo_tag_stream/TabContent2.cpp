#include "stdafx.h"
#include "TabContent2.h"

LRESULT TabContent2::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // ウィンドウのクライアント領域を取得
    RECT rect;
    GetClientRect(&rect);

    // エディットコントロールの作成
    m_edit.Create(m_hWnd, &rect, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL);

    // フォントの作成
    HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

    // フォントの設定
    m_edit.SendMessage(WM_SETFONT, (WPARAM)hFont, TRUE);

    return 0;
}

void TabContent2::SetEditText(const char* text)
{
    m_edit.SetWindowText(CA2W(text, CP_UTF8));
}

pfc::string8 TabContent2::GetEditText()
{
    return pfc::string8();
}
