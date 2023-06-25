#include "stdafx.h"
#include "resource.h"
#include "MainDialog.h"

LRESULT MainDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // タブコントロールの取得
    m_tab = GetDlgItem(IDC_TAB);

    // タブの追加
    m_tab.InsertItem(0, _T("Tab 1"));
    m_tab.InsertItem(1, _T("Tab 2"));

    return TRUE;
}

LRESULT MainDialog::OnOk(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    EndDialog(IDOK);
    return 0;
}

LRESULT MainDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    EndDialog(IDCANCEL);
    return 0;
}

void ShowMainDialog() {
    MainDialog dlg;
    dlg.DoModal();
}