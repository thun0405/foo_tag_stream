#pragma once
#include "stdafx.h"
#include "resource.h"
#include "SizeInfo.h"

class PreviewWindow : public CWindowImpl<PreviewWindow>
{
public:
    PreviewWindow(metadb_handle_list_cref tracks);
    ~PreviewWindow();

    BEGIN_MSG_MAP(PreviewWindow)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

private:
    LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnSize(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnGetMinMaxInfo(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnOK(WORD, WORD, HWND, BOOL&);
    LRESULT OnCancel(WORD, WORD, HWND, BOOL&);

    metadb_handle_list m_tracks;
    CListViewCtrl m_listView;
    CButton m_okButton;
    CButton m_cancelButton;
    SizeInfo m_sizeInfo;
};

void ShowPreviewWindow(metadb_handle_list m_tracks);
