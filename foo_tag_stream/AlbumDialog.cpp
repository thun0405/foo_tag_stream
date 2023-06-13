#include "stdafx.h"
#include "AlbumDialog.h"
#include "PreviewDialog.h"

LRESULT AlbumDialog::OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
{
    m_editBox.Attach(GetDlgItem(IDC_EDIT)); // テキストボックスの初期化
    return LRESULT();
}

LRESULT AlbumDialog::OnOK(WORD, WORD wID, HWND, BOOL&)
{
    wchar_t buffer[256];
    m_editBox.GetWindowText(buffer, sizeof(buffer) / sizeof(wchar_t)); // テキストボックスからテキストを取得

    pfc::string8 albumName = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

    // PreviewDialogを閉じてAlbumDialogを開く
    EndDialog(wID);
    ShowPreviewDialog(m_tracks, albumName);

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

void ShowAlbumDialog(metadb_handle_list_cref p_data) {
    AlbumDialog dlg(p_data);  // Assume AlbumDialog constructor takes metadb_handle_list_cref as parameter
    dlg.DoModal();
}
