#include "stdafx.h"
#include "CsvDialog.h"
#include <iostream>

CsvDialog::CsvDialog(metadb_handle_list_cref p_data)
    : m_data(p_data)
{
    // コンストラクタ内で他の初期化処理を行うことも可能です。
}

LRESULT CsvDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    m_edit.Attach(GetDlgItem(IDC_CSV_EDIT));
    return TRUE;
}

LRESULT CsvDialog::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
// テキストエリアからテキストを取得し、何らかの形で保存します
// ここでは、簡単のためにテキストをコンソールに出力します
    int len = m_edit.GetWindowTextLength();
    if (len > 0) {
        std::vector<TCHAR> buffer(len + 1);
        m_edit.GetWindowText(&buffer[0], len + 1);
        std::wcout << &buffer[0] << std::endl;
    }

    EndDialog(IDOK);
    return 0;
}

LRESULT CsvDialog::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
    EndDialog(IDCANCEL);
    return 0;
}