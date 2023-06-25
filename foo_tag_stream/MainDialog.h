#pragma once
#include "stdafx.h"
#include "resource.h"

class MainDialog :
    public CDialogImpl<MainDialog>
{
public:
    enum { IDD = IDD_MAIN_DIALOG };

    BEGIN_MSG_MAP(TabDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnOk)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

private:
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnOk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

    CTabCtrl m_tab;
};

void ShowMainDialog();