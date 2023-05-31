#pragma once

#include "stdafx.h"
#include "resource.h"

class MyDialog : public CDialogImpl<MyDialog>
{
public:
    enum {
        IDD = IDD_DIALOG
    }; // ダイアログボックスのリソースID

    MyDialog(const metadb_handle_list& tracks) : m_tracks(tracks) {}

    BEGIN_MSG_MAP(MyDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    CListViewCtrl m_listView;
    metadb_handle_list m_tracks;
};

void ShowMyDialog(metadb_handle_list m_tracks);
