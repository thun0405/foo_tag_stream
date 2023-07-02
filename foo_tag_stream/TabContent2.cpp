#include "stdafx.h"
#include "TabContent2.h"

LRESULT TabContent2::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // �E�B���h�E�̃N���C�A���g�̈���擾
    RECT rect;
    GetClientRect(&rect);

    // �G�f�B�b�g�R���g���[���̍쐬
    m_edit.Create(m_hWnd, &rect, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL);

    // �t�H���g�̍쐬
    HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

    // �t�H���g�̐ݒ�
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
