#include "stdafx.h"
#include "MainDialog.h"

MainDialog::MainDialog(metadb_handle_list_cref p_data)
    : m_tabContent1(p_data), m_tracks(p_data), m_metadataList(p_data)
{
}

LRESULT MainDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    m_tab = GetDlgItem(IDC_TAB);
    m_csvSwitchButton = GetDlgItem(IDC_CSV_SWITCH);

    m_tab.InsertItem(0, _T("Tab 1"));
    m_tab.InsertItem(1, _T("Tab 2"));

    CRect rect;
    m_tab.GetClientRect(&rect);
    rect.DeflateRect(5, 25, 5, 5);

    m_tabContent1.Create(m_tab.m_hWnd, rect, NULL, WS_CHILD | WS_VISIBLE);
    m_tabContent2.Create(m_tab.m_hWnd, rect, NULL, WS_CHILD);

    m_tabContent1.MoveWindow(&rect);
    m_tabContent2.MoveWindow(&rect);

    // 選択したトラックのメタデータをCSV形式に変換
    pfc::string8 csv = m_metadataList.ConvertToCsv();

    // CSVをエディットコントロールに設定
    m_tabContent2.SetEditText(csv.c_str());

    OnTabSelChange(0, nullptr, bHandled);

    return TRUE;
}

LRESULT MainDialog::OnTabSelChange(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
    int selectedTab = m_tab.GetCurSel();

    switch (selectedTab)
    {
    case 0: // Tab1が選択された場合
        m_tabContent1.ShowWindow(SW_SHOW);
        m_tabContent2.ShowWindow(SW_HIDE);
        m_csvSwitchButton.SetWindowText(_T("CSV Input"));
        break;
    case 1: // Tab2が選択された場合
        m_tabContent1.ShowWindow(SW_HIDE);
        m_tabContent2.ShowWindow(SW_SHOW);
        m_csvSwitchButton.SetWindowText(_T("CSV Output"));
        break;
    default:
        break;
    }

    return 0;
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

void ShowMainDialog(metadb_handle_list_cref p_data) {
    MainDialog dlg = MainDialog(p_data);
    dlg.DoModal();
}

LRESULT MainDialog::OnCsvSwitch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    int selectedTab = m_tab.GetCurSel();

    switch (selectedTab)
    {
    case 0: // Tab1が選択された場合
        // Tab1用の処理を行う
        m_tab.SetCurSel(1); // Tab1が選択されていた場合、Tab2を選択
        break;
    case 1: // Tab2が選択された場合
        // Tab2用の処理を行う
        m_tab.SetCurSel(0); // Tab2が選択されていた場合、Tab1を選択
        break;
    default:
        break;
    }

    // タブの選択状態が変わったので、タブの内容を更新
    OnTabSelChange(0, nullptr, bHandled);

    return 0;
}
