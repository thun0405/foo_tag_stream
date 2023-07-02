#include "stdafx.h"
#include "TabContent1.h"
#include "ListViewManager.h"

TabContent1::TabContent1(metadb_handle_list_cref p_data)
    : m_tracks(p_data)
{
}

LRESULT TabContent1::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // ���X�g�r���[�̍쐬
    RECT rect;
    GetClientRect(&rect);
    m_listView.Create(m_hWnd, &rect, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT);

    // ���X�g�r���[�ɃJ������ǉ�
    //m_listView.InsertColumn(0, _T("Column 1"), LVCFMT_LEFT, 100);
    //m_listView.InsertColumn(1, _T("Column 2"), LVCFMT_LEFT, 100);

    ListViewManager listViewManager = ListViewManager(m_listView, this);
    listViewManager.InitializeListView();
    listViewManager.PopulateListView(m_tracks);

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
