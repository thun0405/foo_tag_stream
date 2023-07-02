#include "stdafx.h"
#include "resource.h"
#include "PreviewDialog.h"
#include "ListViewManager.h"
#include "ButtonManager.h"

class file_info_filter_impl : public file_info_filter
{
public:
	file_info_filter_impl(const file_info& source) : m_source(source) {}

	bool apply_filter(trackRef p_location, t_filestats p_stats, file_info& p_info) override
	{
		p_info = m_source;
		return true;
	}

private:
	const file_info& m_source;
};

PreviewDialog::PreviewDialog(metadb_handle_list_cref tracks, const pfc::string8& albumName)
	: m_tracks(tracks), m_albumName(albumName)
{}

LRESULT PreviewDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_listView = GetDlgItem(IDC_TRACKLIST);
	m_okButton = GetDlgItem(IDOK);
	m_cancelButton = GetDlgItem(IDCANCEL);

	// ダイアログボックスの初期サイズを取得してm_sizeに設定
	CRect rect;
	GetClientRect(&rect);
	m_sizeInfo = SizeInfo(rect.Size());

	ListViewManager listViewManager = ListViewManager(m_listView, this);
	listViewManager.InitializeListView();
	listViewManager.PopulateListView(m_tracks);

	return TRUE;
}

LRESULT PreviewDialog::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	m_sizeInfo.OnSize(CSize(LOWORD(lParam), HIWORD(lParam)));
	int diffWidth = m_sizeInfo.DiffWidth();
	int diffHeight = m_sizeInfo.DiffHeight();

	ListViewManager listViewManager = ListViewManager(m_listView, this);
	ButtonManager okButtonManager = ButtonManager(m_okButton, this);
	ButtonManager cancelButtonManager = ButtonManager(m_cancelButton, this);

	// リストビューコントロールのサイズを更新
	listViewManager.UpdateSize(diffWidth, diffHeight);

	// ボタンの位置を更新
	okButtonManager.UpdatePosition(diffWidth, diffHeight);
	cancelButtonManager.UpdatePosition(diffWidth, diffHeight);

	return 0;
}


LRESULT PreviewDialog::OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	CSize initSize = m_sizeInfo.GetInitSize();
	MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
	pMinMax->ptMinTrackSize.x = initSize.cx;
	pMinMax->ptMinTrackSize.y = initSize.cy;

	return 0;
}

LRESULT PreviewDialog::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ListViewManager listViewManager = ListViewManager(m_listView, this);
	// OKボタンが押されたときの処理をここに書く
	// ここでは、リストビューに表示されているデータを元にメタデータを更新する
	for (size_t i = 0; i < m_tracks.get_count(); ++i) {
		const metadb_handle_ptr& track = m_tracks[i];
		file_info_impl info;
		if (track->get_info_async(info)) {
			TrackMetadata metadata = listViewManager.GetTrackMetadata(i);

			info.meta_set("TITLE", metadata.GetTitle());
			info.meta_set("ARTIST", metadata.GetArtist());
			info.meta_set("ALBUM", metadata.GetAlbum());

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
	// キャンセルボタンが押されたときの処理をここに書く
	EndDialog(wID);
	return 0;
}

void ShowPreviewDialog(metadb_handle_list m_tracks, pfc::string8 albumName)
{
	PreviewDialog dlg(m_tracks, albumName);
	dlg.DoModal();

	return;
}
