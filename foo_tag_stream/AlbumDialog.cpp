#include "stdafx.h"
#include "AlbumDialog.h"

LRESULT AlbumDialog::OnInitDialog(UINT, WPARAM, LPARAM, BOOL&)
{
    m_editBox.Attach(GetDlgItem(IDC_EDIT)); // �e�L�X�g�{�b�N�X�̏�����
    return LRESULT();
}

LRESULT AlbumDialog::OnOK(WORD, WORD wID, HWND, BOOL&)
{
    wchar_t buffer[256];
    m_editBox.GetWindowText(buffer, sizeof(buffer) / sizeof(wchar_t)); // �e�L�X�g�{�b�N�X����e�L�X�g���擾
    // ������buffer�ɕۑ����ꂽ�e�L�X�g���g�p���ĉ������s��
    EndDialog(wID);
    return LRESULT();
}

LRESULT AlbumDialog::OnCancel(WORD, WORD wID, HWND, BOOL&)
{
    EndDialog(wID);
    return LRESULT();
}

LRESULT AlbumDialog::OnEdit(WORD, WORD wID, HWND, BOOL&)
{
    // �e�L�X�g�{�b�N�X�̃C�x���g�n���h��
    return LRESULT();
}
