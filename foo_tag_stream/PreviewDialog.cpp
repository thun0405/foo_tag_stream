#include "stdafx.h"
#include "resource.h"

#include "PreviewDialog.h"

class ListViewManager {
public:
	ListViewManager(CListViewCtrl listView, CWindow* window)
		: m_listView(listView)
	{
		// ���X�g�r���[�R���g���[���̌��݂̈ʒu�ƃT�C�Y���擾
		CRect rect;
		m_listView.GetWindowRect(&rect);
		window->ScreenToClient(&rect);

		m_currentSize = rect.Size();
		m_currentPosition = rect.TopLeft();
	}

	void UpdateSize(int diffWidth, int diffHeight);

private:
	CListViewCtrl m_listView;
	CSize m_currentSize;
	CPoint m_currentPosition;
};

class ButtonManager {
public:
	ButtonManager(CButton button, CWindow* window)
		: m_button(button)
	{
		// �{�^���̌��݂̈ʒu�ƃT�C�Y���擾
		CRect rect;
		m_button.GetWindowRect(&rect);
		window->ScreenToClient(&rect);

		m_currentSize = rect.Size();
		m_currentPosition = rect.TopLeft();
	}

	void UpdatePosition(int diffWidth, int diffHeight);

private:
	CButton m_button;
	CSize m_currentSize;
	CPoint m_currentPosition;
};

class file_info_filter_impl : public file_info_filter {
public:
	file_info_filter_impl(const file_info& source) : m_source(source) {}

	bool apply_filter(trackRef p_location, t_filestats p_stats, file_info& p_info) override {
		p_info = m_source;
		return true;
	}

private:
	const file_info& m_source;
};


LRESULT PreviewDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
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

			// �A���o���������͂���Ă���΂�����g�p���A�����łȂ���Ό��̃A���o�������g�p���܂��B
			if (!m_albumName.is_empty()) {
				m_listView.SetItemText(i, 2, pfc::stringcvt::string_os_from_utf8(m_albumName));
			}
			else {
				m_listView.SetItemText(i, 2, pfc::stringcvt::string_os_from_utf8(info.meta_get("ALBUM", 0)));
			}
		}
	}

	return TRUE;
}

LRESULT PreviewDialog::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	// �V�����_�C�A���O�{�b�N�X�̕��ƍ������擾
	int newWidth = LOWORD(lParam);
	int newHeight = HIWORD(lParam);

	int diffWidth = newWidth - m_size.cx;
	int diffHeight = newHeight - m_size.cy;

	ListViewManager listViewManager = ListViewManager(m_listView, this);
	ButtonManager okButtonManager = ButtonManager(m_okButton, this);
	ButtonManager cancelButtonManager = ButtonManager(m_cancelButton, this);

	// ���X�g�r���[�R���g���[���̃T�C�Y���X�V
	listViewManager.UpdateSize(diffWidth, diffHeight);

	// �{�^���̈ʒu���X�V
	okButtonManager.UpdatePosition(diffWidth, diffHeight);
	cancelButtonManager.UpdatePosition(diffWidth, diffHeight);

	// �V�����T�C�Y��ۑ�
	m_size.cx = newWidth;
	m_size.cy = newHeight;

	return 0;
}


LRESULT PreviewDialog::OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
	pMinMax->ptMinTrackSize.x = m_initialSize.cx;
	pMinMax->ptMinTrackSize.y = m_initialSize.cy;

	return 0;
}

LRESULT PreviewDialog::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// OK�{�^���������ꂽ�Ƃ��̏����������ɏ���
	// �����ł́A���X�g�r���[�ɕ\������Ă���f�[�^�����Ƀ��^�f�[�^���X�V����
	for (size_t i = 0; i < m_tracks.get_count(); ++i) {
		const metadb_handle_ptr& track = m_tracks[i];
		file_info_impl info;
		if (track->get_info_async(info)) {
			wchar_t buffer[256];

			m_listView.GetItemText(i, 0, buffer, sizeof(buffer) / sizeof(wchar_t));
			pfc::string8 title = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

			m_listView.GetItemText(i, 1, buffer, sizeof(buffer) / sizeof(wchar_t));
			pfc::string8 artist = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

			m_listView.GetItemText(i, 2, buffer, sizeof(buffer) / sizeof(wchar_t));
			pfc::string8 album = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

			info.meta_set("TITLE", title);
			info.meta_set("ARTIST", artist);
			info.meta_set("ALBUM", album);

			metadb_handle_list trackList;
			trackList.add_item(track);

			service_ptr_t<file_info_filter> filter = new service_impl_t<file_info_filter_impl>(info);
			static_api_ptr_t<metadb_io_v2>()->update_info_async(trackList, filter, 0, NULL, completion_notify_ptr());
		}
	}

	EndDialog(wID);
	return 0;
}

LRESULT PreviewDialog::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// �L�����Z���{�^���������ꂽ�Ƃ��̏����������ɏ���
	EndDialog(wID);
	return 0;
}

void ShowPreviewDialog(metadb_handle_list m_tracks, pfc::string8 albumName)
{
	PreviewDialog dlg(m_tracks, albumName);
	dlg.DoModal();

	return;
}

void ListViewManager::UpdateSize(int diffWidth, int diffHeight) {
	// �V�������X�g�r���[�R���g���[���̕��ƍ������v�Z
	int listViewWidth = m_currentSize.cx + diffWidth;
	int listViewHeight = m_currentSize.cy + diffHeight;

	// ���X�g�r���[�R���g���[���̃T�C�Y��ύX
	m_listView.MoveWindow(m_currentPosition.x, m_currentPosition.y, listViewWidth, listViewHeight, TRUE);
	m_listView.Invalidate();

	// �V�����T�C�Y��ۑ�
	m_currentSize.cx = listViewWidth;
	m_currentSize.cy = listViewHeight;
}

void ButtonManager::UpdatePosition(int diffWidth, int diffHeight) {
	// �{�^���̐V�����ʒu���v�Z
	int buttonX = diffWidth + m_currentPosition.x;
	int buttonY = diffHeight + m_currentPosition.y;

	// �{�^���̈ʒu���X�V
	m_button.MoveWindow(buttonX, buttonY, m_currentSize.cx, m_currentSize.cy, TRUE);
	m_button.Invalidate();

	// �V�����ʒu��ۑ�
	m_currentPosition.x = buttonX;
	m_currentPosition.y = buttonY;
}