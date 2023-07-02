#include "stdafx.h"
#include "ListViewManager.h"

ListViewManager::ListViewManager(CListViewCtrl& listView, CWindow* window)
    : m_listView(listView), m_controlManager(listView, window)
{
    m_columns.push_back({ _T("#"), 30, [](int index, const file_info_impl& info) { return pfc::string8(pfc::format_int(index + 1)); } });
    m_columns.push_back({ _T("Title"), 200, [](int index, const file_info_impl& info) { return info.meta_get("TITLE", 0); } });
    m_columns.push_back({ _T("Artist"), 200, [](int index, const file_info_impl& info) { return info.meta_get("ARTIST", 0); } });
    m_columns.push_back({ _T("Album"), 200, [](int index, const file_info_impl& info) { return info.meta_get("ALBUM", 0); } });
}

void ListViewManager::InitializeListView()
{
    // ƒJƒ‰ƒ€‚ð’Ç‰Á
    for (size_t i = 0; i < m_columns.size(); ++i) {
        const ColumnInfo& column = m_columns[i];
        m_listView.InsertColumn(i, column.name, LVCFMT_LEFT, column.width);
    }
}

void ListViewManager::UpdateSize(int diffWidth, int diffHeight)
{
    m_controlManager.UpdateSize(diffWidth, diffHeight);
}

void ListViewManager::PopulateListView(const metadb_handle_list& tracks)
{
    for (size_t i = 0; i < tracks.get_count(); ++i) {
        const metadb_handle_ptr& track = tracks[i];
        file_info_impl info;
        if (track->get_info_async(info)) {
            // Insert a new item for the first column
            const ColumnInfo& firstColumn = m_columns[0];
            pfc::string8 firstData = firstColumn.dataGetter(i, info);
            m_listView.InsertItem(i, pfc::stringcvt::string_os_from_utf8(firstData));

            // Set the text for the remaining columns
            for (int j = 1; j < m_columns.size(); ++j) {
                const ColumnInfo& column = m_columns[j];
                pfc::string8 data = column.dataGetter(i, info);
                m_listView.SetItemText(i, j, pfc::stringcvt::string_os_from_utf8(data));
            }
        }
    }
}


TrackMetadata ListViewManager::GetTrackMetadata(int index)
{
    wchar_t buffer[256];

    //m_listView.GetItemText(index, 0, buffer, sizeof(buffer) / sizeof(wchar_t));
    //int number = _wtoi(buffer);  // Convert string to integer

    m_listView.GetItemText(index, 1, buffer, sizeof(buffer) / sizeof(wchar_t));
    pfc::string8 title = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

    m_listView.GetItemText(index, 2, buffer, sizeof(buffer) / sizeof(wchar_t));
    pfc::string8 artist = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

    m_listView.GetItemText(index, 3, buffer, sizeof(buffer) / sizeof(wchar_t));
    pfc::string8 album = pfc::stringcvt::string_utf8_from_os(buffer).get_ptr();

    return TrackMetadata(title, artist, album);
}
