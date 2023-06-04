#include "stdafx.h"
#include "resource.h"

#include "ui_dialog.h"

LRESULT MyDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_listView = GetDlgItem(IDC_TRACKLIST);
	m_okButton = GetDlgItem(IDOK);
	m_cancelButton = GetDlgItem(IDCANCEL);

	// ダイアログボックスの初期サイズを取得してm_sizeに設定
	CRect rect;
	GetClientRect(&rect);
	m_size = rect.Size();
	m_initialSize = rect.Size();

	// ボタンの現在の位置とサイズを取得
	CRect okButtonRect;
	m_okButton.GetWindowRect(&okButtonRect);
	ScreenToClient(&okButtonRect);

	CRect cancelButtonRect;
	m_cancelButton.GetWindowRect(&cancelButtonRect);
	ScreenToClient(&cancelButtonRect);

	// カラムを追加
	m_listView.InsertColumn(0, _T("Title"), LVCFMT_LEFT, 200);
	m_listView.InsertColumn(1, _T("Artist"), LVCFMT_LEFT, 200);
	m_listView.InsertColumn(2, _T("Album"), LVCFMT_LEFT, 200);

	// 選択したトラックの情報を取得し、リストビューに追加します。
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
	// 新しいダイアログボックスの幅と高さを取得
	int newWidth = LOWORD(lParam);
	int newHeight = HIWORD(lParam);

	int diffWidth = newWidth - m_size.cx;
	int diffHeight = newHeight - m_size.cy;

	ListViewManager listViewManager = ListViewManager(m_listView, this);
	ButtonManager okButtonManager = ButtonManager(m_okButton, this);
	ButtonManager cancelButtonManager = ButtonManager(m_cancelButton, this);

	// リストビューコントロールのサイズを更新
	listViewManager.UpdateSize(diffWidth, diffHeight);

	// ボタンの位置を更新
	okButtonManager.UpdatePosition(diffWidth, diffHeight);
	cancelButtonManager.UpdatePosition(diffWidth, diffHeight);

	// 新しいサイズを保存
	m_size.cx = newWidth;
	m_size.cy = newHeight;

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
	// OKボタンが押されたときの処理をここに書く
	EndDialog(wID);
	return 0;
}
LRESULT MyDialog::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// キャンセルボタンが押されたときの処理をここに書く
	EndDialog(wID);
	return 0;
}

void ShowMyDialog(metadb_handle_list m_tracks)
{
	MyDialog dlg(m_tracks);
	dlg.DoModal();

	return;
}

void ListViewManager::UpdateSize(int diffWidth, int diffHeight) {
	// 新しいリストビューコントロールの幅と高さを計算
	int listViewWidth = m_currentSize.cx + diffWidth;
	int listViewHeight = m_currentSize.cy + diffHeight;

	// リストビューコントロールのサイズを変更
	m_listView.MoveWindow(m_currentPosition.x, m_currentPosition.y, listViewWidth, listViewHeight, TRUE);
	m_listView.Invalidate();

	// 新しいサイズを保存
	m_currentSize.cx = listViewWidth;
	m_currentSize.cy = listViewHeight;
}

void ButtonManager::UpdatePosition(int diffWidth, int diffHeight) {
	// ボタンの新しい位置を計算
	int buttonX = diffWidth + m_currentPosition.x;
	int buttonY = diffHeight + m_currentPosition.y;

	// ボタンの位置を更新
	m_button.MoveWindow(buttonX, buttonY, m_currentSize.cx, m_currentSize.cy, TRUE);
	m_button.Invalidate();

	// 新しい位置を保存
	m_currentPosition.x = buttonX;
	m_currentPosition.y = buttonY;
}