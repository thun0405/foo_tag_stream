#include "stdafx.h"
#include "resource.h"

#include "ui_dialog.h"

LRESULT MyDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_listView = GetDlgItem(IDC_TRACKLIST);

	// �J������ǉ�
	m_listView.InsertColumn(0, _T("Title"), LVCFMT_LEFT, 200);
	m_listView.InsertColumn(1, _T("Artist"), LVCFMT_LEFT, 200);

	// �I�������g���b�N�̏����擾���A���X�g�r���[�ɒǉ����܂��B
	for (size_t i = 0; i < m_tracks.get_count(); ++i) {
		const metadb_handle_ptr& track = m_tracks[i];
		file_info_impl info;
		if (track->get_info_async(info)) {
			m_listView.InsertItem(i, pfc::stringcvt::string_os_from_utf8(info.meta_get("TITLE", 0)));
			m_listView.SetItemText(i, 1, pfc::stringcvt::string_os_from_utf8(info.meta_get("ARTIST", 0)));
		}
	}

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

void ShowMyDialog(metadb_handle_list m_tracks)
{
	MyDialog dlg(m_tracks);
	dlg.DoModal();
}
