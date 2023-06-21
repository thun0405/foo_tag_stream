#pragma once
#include "stdafx.h"
#include "resource.h"
#include "SizeInfo.h"

class PreviewDialog : public CDialogImpl<PreviewDialog>
{
public:
    enum { IDD = IDD_PREVIEW };

    PreviewDialog(metadb_handle_list_cref tracks, const pfc::string8& albumName);

    BEGIN_MSG_MAP(PreviewDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

private:
    LRESULT OnInitDialog(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnSize(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnGetMinMaxInfo(UINT, WPARAM, LPARAM, BOOL&);
    LRESULT OnOK(WORD, WORD, HWND, BOOL&);
    LRESULT OnCancel(WORD, WORD, HWND, BOOL&);

    metadb_handle_list m_tracks;
    pfc::string8 m_albumName;
    CListViewCtrl m_listView;
    CButton m_okButton;
    CButton m_cancelButton;
    SizeInfo m_sizeInfo;
};

void ShowPreviewDialog(metadb_handle_list m_tracks, pfc::string8 albumName);
