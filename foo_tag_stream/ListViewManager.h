#pragma once
#include "stdafx.h"
#include "ControlManager.h"
#include "TrackMetadata.h"
#include "TrackMetadataList.h"

class ListViewManager
{
public:
    struct ColumnInfo
    {
        const TCHAR* name;
        int width;
        std::function<pfc::string8(int, const TrackMetadata&)> dataGetter;
    };

    ListViewManager(CListViewCtrl& listView, CWindow* window);
    void InitializeListView();
    void UpdateSize(int diffWidth, int diffHeight);
    void PopulateListView(const TrackMetadataList& tracks);
    TrackMetadata GetTrackMetadata(int index);

private:
    CListViewCtrl& m_listView;
    ControlManager m_controlManager;
    std::vector<ColumnInfo> m_columns;
};
