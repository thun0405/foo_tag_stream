#include "stdafx.h"
#include "resource.h"

#include "ui_dialog.h"

LRESULT MyDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_listView = GetDlgItem(IDC_TRACKLIST);
	m_okButton = GetDlgItem(IDOK);
	m_cancelButton = GetDlgItem(IDCANCEL);
	// �_�C�A���O�{�b�N�X�̏����T�C�Y���擾����m_size�ɐݒ�
	CRect rect;
	GetClientRect(&rect);
	m_size = rect.Size();
	m_initialSize = rect.Size();

	// �{�^���̌��݂̈ʒu�ƃT�C�Y���擾
	CRect okButtonRect;
	m_okButton.GetWindowRect(&okButtonRect);
	ScreenToClient(&okButtonRect);

	CRect cancelButtonRect;
	m_cancelButton.GetWindowRect(&cancelButtonRect);
	ScreenToClient(&cancelButtonRect);

	// �J������ǉ�
	m_listView.InsertColumn(0, _T("Title"), LVCFMT_LEFT, 200);
	m_listView.InsertColumn(1, _T("Artist"), LVCFMT_LEFT, 200);
	m_listView.InsertColumn(2, _T("Album"), LVCFMT_LEFT, 200);

	// �I�������g���b�N�̏����擾���A���X�g�r���[�ɒǉ����܂��B
	for (size_t i = 0; i < m_tracks.get_count(); ++i) {
		const metadb_handle_ptr& track = m_tracks[i];
		file_info_impl info;
		if (track->get_info_async(info)) {
			m_listView.InsertItem(i, pfc::stringcvt::string_os_from_utf8(info.meta_get("TITLE", 0)));
			m_listView.SetItemText(i, 1, pfc::stringcvt::string_os_from_utf8(info.meta_get("ARTIST", 0)));
			m_listView.SetItemText(i, 2, pfc::stringcvt::string_os_from_utf8(info.meta_get("ALBUM", 0)));
		}
	}

	return TRUE;
}

LRESULT MyDialog::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	// �T�C�Y�ύX��̃_�C�A���O�{�b�N�X�̕��ƍ������擾
	int newWidth = LOWORD(lParam);
	int newHeight = HIWORD(lParam);

	// �T�C�Y�ύX�O�̃_�C�A���O�{�b�N�X�̕��ƍ������擾
	int oldWidth = m_size.cx;
	int oldHeight = m_size.cy;

	OnSizeListView(newWidth, newHeight, oldWidth, oldHeight);
	OnSizeButton(newWidth, newHeight, oldWidth, oldHeight);

	// �T�C�Y�ύX��̃_�C�A���O�{�b�N�X�̕��ƍ�����ۑ�
	m_size = CSize(newWidth, newHeight);

	return 0;
}

LRESULT MyDialog::OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
	pMinMax->ptMinTrackSize.x = m_initialSize.cx;
	pMinMax->ptMinTrackSize.y = m_initialSize.cy;

	return 0;
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

void MyDialog::OnSizeListView(int& newWidth, int& newHeight, int& oldWidth, int& oldHeight)
{
	// ���X�g�r���[�R���g���[���̌��݂̈ʒu�ƃT�C�Y���擾
	CRect rect;
	m_listView.GetWindowRect(&rect);
	ScreenToClient(&rect);

	// �V�������X�g�r���[�R���g���[���̕��ƍ������v�Z
	int listViewWidth = rect.Width() + (newWidth - oldWidth);
	int listViewHeight = rect.Height() + (newHeight - oldHeight);

	// ���X�g�r���[�R���g���[���̃T�C�Y��ύX
	m_listView.SetWindowPos(NULL, 0, 0, listViewWidth, listViewHeight, SWP_NOZORDER | SWP_NOMOVE);

	return;
}
void MyDialog::OnSizeButton(int& newWidth, int& newHeight, int& oldWidth, int& oldHeight)
{
	// �{�^���̌��݂̈ʒu�ƃT�C�Y���擾
	CRect okButtonRect;
	m_okButton.GetWindowRect(&okButtonRect);
	ScreenToClient(&okButtonRect);

	CRect cancelButtonRect;
	m_cancelButton.GetWindowRect(&cancelButtonRect);
	ScreenToClient(&cancelButtonRect);

	// �{�^���̐V�����ʒu���v�Z
	int okButtonX = newWidth - (oldWidth - okButtonRect.left);
	int okButtonY = newHeight - (oldHeight - okButtonRect.top);

	int cancelButtonX = newWidth - (oldWidth - cancelButtonRect.left);
	int cancelButtonY = newHeight - (oldHeight - cancelButtonRect.top);

	// �{�^���̈ʒu���X�V
	m_okButton.MoveWindow(okButtonX, okButtonY, okButtonRect.Width(), okButtonRect.Height(), TRUE);
	m_cancelButton.MoveWindow(cancelButtonX, cancelButtonY, cancelButtonRect.Width(), cancelButtonRect.Height(), TRUE);

	m_okButton.Invalidate();
	m_cancelButton.Invalidate();

	return;
}

void ShowMyDialog(metadb_handle_list m_tracks)
{
	MyDialog dlg(m_tracks);
	dlg.DoModal();

	return;
}

