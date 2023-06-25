#include "stdafx.h"
#include "CsvDialog.h"
#include <iostream>

CsvDialog::CsvDialog(metadb_handle_list_cref p_data)
    : m_data(p_data)
{
    // �R���X�g���N�^���ő��̏������������s�����Ƃ��\�ł��B
}

LRESULT CsvDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    m_edit.Attach(GetDlgItem(IDC_CSV_EDIT));
    return TRUE;
}

LRESULT CsvDialog::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
// �e�L�X�g�G���A����e�L�X�g���擾���A���炩�̌`�ŕۑ����܂�
// �����ł́A�ȒP�̂��߂Ƀe�L�X�g���R���\�[���ɏo�͂��܂�
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