#pragma once
#include "stdafx.h"

class ListViewManager {
public:
    ListViewManager(CListViewCtrl listView, CWindow* window);

    void InitializeListView();
    void UpdateSize(int diffWidth, int diffHeight);
    void PopulateListView(const metadb_handle_list& tracks, const pfc::string8& albumName);

private:
    CListViewCtrl m_listView;
    CSize m_currentSize;
    CPoint m_currentPosition;

    static const int COLUMN_WIDTH = 200;
};
