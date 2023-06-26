#pragma once
#include "stdafx.h"
#include "resource.h"
#include "TabContent1.h"
#include "TabContent2.h"

class MainDialog : public CDialogImpl<MainDialog>
{
public:
    MainDialog(metadb_handle_list_cref p_data);

    enum { IDD = IDD_MAIN_DIALOG };

    BEGIN_MSG_MAP(MainDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        NOTIFY_HANDLER(IDC_TAB, TCN_SELCHANGE, OnTabSelChange)
        COMMAND_ID_HANDLER(IDOK, OnOk)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnTabSelChange(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
    LRESULT OnOk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

private:
    CTabCtrl m_tab;
    TabContent1 m_tabContent1;
    TabContent2 m_tabContent2;
    metadb_handle_list m_tracks;
};

void ShowMainDialog(metadb_handle_list_cref p_data);
