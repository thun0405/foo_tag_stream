#pragma once
#include "stdafx.h"
#include "TrackMetadataList.h"

class TabContent1 : public CWindowImpl<TabContent1>
{
public:
    TabContent1();

    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP(TabContent1)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    void UpdateListView(TrackMetadataList& metadataList);

private:
    CListViewCtrl m_listView;
};
