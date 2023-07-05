#include "stdafx.h"
#include "TabContent1.h"
#include "ListViewManager.h"

TabContent1::TabContent1()
{
}

LRESULT TabContent1::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // ���X�g�r���[�̍쐬
    RECT rect;
    GetClientRect(&rect);
    m_listView.Create(m_hWnd, &rect, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT);

    return 0;
}

LRESULT TabContent1::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // ���X�g�r���[�̃T�C�Y���E�B���h�E�̃N���C�A���g�̈�ɍ��킹��
    RECT rect;
    GetClientRect(&rect);
    m_listView.MoveWindow(&rect);

    return 0;
}

void TabContent1::UpdateListView(TrackMetadataList& metadataList)
{
    ListViewManager listViewManager = ListViewManager(m_listView, this);
    listViewManager.InitializeListView();
    listViewManager.UpdateListView(metadataList);
}
