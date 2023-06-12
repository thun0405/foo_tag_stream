#pragma once

#include "stdafx.h"
#include "resource.h"

class AlbumDialog : public CDialogImpl<AlbumDialog>
{
public:
    enum {
        IDD = IDD_ALBUM
    }; // ダイアログボックスのリソースID

    AlbumDialog(const metadb_handle_list& tracks) : m_tracks(tracks) {}

    BEGIN_MSG_MAP(PreviewDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
        COMMAND_ID_HANDLER(IDC_EDIT, OnEdit)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnEdit(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    CListViewCtrl m_listView;
    CButton m_okButton;
    CButton m_cancelButton;
    CEdit m_editBox; // テキストボックスの追加

    metadb_handle_list m_tracks;
};

void ShowAlbumDialog(metadb_handle_list_cref p_data);