#include "stdafx.h"
#include "ui_dialog.h"

LRESULT MyDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // �_�C�A���O�{�b�N�X�̏����������������ɏ���
    return TRUE;
}

LRESULT MyDialog::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // OK�{�^���������ꂽ�Ƃ��̏����������ɏ���
    EndDialog(wID);
    return 0;
}

LRESULT MyDialog::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // �L�����Z���{�^���������ꂽ�Ƃ��̏����������ɏ���
    EndDialog(wID);
    return 0;
}

void ShowMyDialog()
{
    MyDialog dlg;
    dlg.DoModal();
}
