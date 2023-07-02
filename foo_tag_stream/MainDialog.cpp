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

    // �I�������g���b�N�̃��^�f�[�^��CSV�`���ɕϊ�
    pfc::string8 csv = m_metadataList.ConvertToCsv();

    // CSV���G�f�B�b�g�R���g���[���ɐݒ�
    m_tabContent2.SetEditText(csv.c_str());

    OnTabSelChange(0, nullptr, bHandled);

    return TRUE;
}

LRESULT MainDialog::OnTabSelChange(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
    int selectedTab = m_tab.GetCurSel();

    switch (selectedTab)
    {
    case 0: // Tab1���I�����ꂽ�ꍇ
        m_tabContent1.ShowWindow(SW_SHOW);
        m_tabContent2.ShowWindow(SW_HIDE);
        m_csvSwitchButton.SetWindowText(_T("CSV Input"));
        break;
    case 1: // Tab2���I�����ꂽ�ꍇ
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
    case 0: // Tab1���I�����ꂽ�ꍇ
        // Tab1�p�̏������s��
        m_tab.SetCurSel(1); // Tab1���I������Ă����ꍇ�ATab2��I��
        break;
    case 1: // Tab2���I�����ꂽ�ꍇ
        // Tab2�p�̏������s��
        m_tab.SetCurSel(0); // Tab2���I������Ă����ꍇ�ATab1��I��
        break;
    default:
        break;
    }

    // �^�u�̑I����Ԃ��ς�����̂ŁA�^�u�̓��e���X�V
    OnTabSelChange(0, nullptr, bHandled);

    return 0;
}
