#include "stdafx.h"
#include "AlbumDialog.h"

LRESULT AlbumDialog::OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
{
    m_editBox.Attach(GetDlgItem(IDC_EDIT)); // テキストボックスの初期化
    return LRESULT();
}

LRESULT AlbumDialog::OnOK(WORD, WORD wID, HWND, BOOL&)
{
    wchar_t buffer[256];
    m_editBox.GetWindowText(buffer, sizeof(buffer) / sizeof(wchar_t)); // テキストボックスからテキストを取得
    // ここでbufferに保存されたテキストを使用して何かを行う
    EndDialog(wID);
    return LRESULT();
}

LRESULT AlbumDialog::OnCancel(WORD, WORD wID, HWND, BOOL&)
{
    EndDialog(wID);
    return LRESULT();
}

LRESULT AlbumDialog::OnEdit(WORD, WORD wID, HWND, BOOL&)
{
    // テキストボックスのイベントハンドラ
    return LRESULT();
}
