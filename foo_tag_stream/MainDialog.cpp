#include "stdafx.h"
#include "MainDialog.h"
#include "TrackMetadataList.h"

MainDialog::MainDialog(metadb_handle_list_cref p_data)
    : m_tabContent1(p_data), m_tracks(p_data)

{
}

LRESULT MainDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    m_tab = GetDlgItem(IDC_TAB);

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
    TrackMetadataList metadataList = TrackMetadataList(m_tracks);
    pfc::string8 csv = metadataList.ConvertToCsv();

    // CSVをエディットコントロールに設定
    m_tabContent2.SetEditText(csv.c_str());

    return TRUE;
}

LRESULT MainDialog::OnTabSelChange(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
    int sel = m_tab.GetCurSel();
    if (sel == 0) {
        m_tabContent1.ShowWindow(SW_SHOW);
        m_tabContent2.ShowWindow(SW_HIDE);
    }
    else if (sel == 1) {
        m_tabContent1.ShowWindow(SW_HIDE);
        m_tabContent2.ShowWindow(SW_SHOW);
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