#include "stdafx.h"
#include "ListViewManager.h"

ListViewManager::ListViewManager(CListViewCtrl listView, CWindow* window)
    : m_listView(listView)
{
    // リストビューコントロールの現在の位置とサイズを取得
    CRect rect;
    m_listView.GetWindowRect(&rect);
    window->ScreenToClient(&rect);

    m_currentSize = rect.Size();
    m_currentPosition = rect.TopLeft();
}

void ListViewManager::InitializeListView() {
    // カラムを追加
    m_listView.InsertColumn(0, _T("Title"), LVCFMT_LEFT, COLUMN_WIDTH);
    m_listView.InsertColumn(1, _T("Artist"), LVCFMT_LEFT, COLUMN_WIDTH);
    m_listView.InsertColumn(2, _T("Album"), LVCFMT_LEFT, COLUMN_WIDTH);
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

void ListViewManager::PopulateListView(const metadb_handle_list& tracks, const pfc::string8& albumName) {
    // 選択したトラックの情報を取得し、リストビューに追加します。
    for (size_t i = 0; i < tracks.get_count(); ++i) {
        const metadb_handle_ptr& track = tracks[i];
        file_info_impl info;
        if (track->get_info_async(info)) {
            m_listView.InsertItem(i, pfc::stringcvt::string_os_from_utf8(info.meta_get("TITLE", 0)));
            m_listView.SetItemText(i, 1, pfc::stringcvt::string_os_from_utf8(info.meta_get("ARTIST", 0)));

            // アルバム名が入力されていればそれを使用し、そうでなければ元のアルバム名を使用します。
            if (!albumName.is_empty()) {
                m_listView.SetItemText(i, 2, pfc::stringcvt::string_os_from_utf8(albumName));
            }
            else {
                m_listView.SetItemText(i, 2, pfc::stringcvt::string_os_from_utf8(info.meta_get("ALBUM", 0)));
            }
        }
    }
}

TrackMetadata ListViewManager::GetTrackMetadata(int index) {
    wchar_t buffer[256];

    m_listView.GetItemText(index, 0, buffer, sizeof(buffer) / sizeof(wchar_t));
    pfc::string8 title = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

    m_listView.GetItemText(index, 1, buffer, sizeof(buffer) / sizeof(wchar_t));
    pfc::string8 artist = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

    m_listView.GetItemText(index, 2, buffer, sizeof(buffer) / sizeof(wchar_t));
    pfc::string8 album = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

    return TrackMetadata(title, artist, album);
}

