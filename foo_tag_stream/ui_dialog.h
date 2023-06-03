#pragma once

#include "stdafx.h"
#include "resource.h"

class MyDialog : public CDialogImpl<MyDialog>
{
public:
    enum {
        IDD = IDD_DIALOG
    }; // �_�C�A���O�{�b�N�X�̃��\�[�XID

    MyDialog(const metadb_handle_list& tracks) : m_tracks(tracks) {}

    BEGIN_MSG_MAP(MyDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    CListViewCtrl m_listView;
    CButton m_okButton;
    CButton m_cancelButton;
    CSize m_size;
    CSize m_initialSize;

    metadb_handle_list m_tracks;

    void OnSizeListView(int& newWidth, int& newHeight, int& oldWidth, int& oldHeight);
    void OnSizeButton(int& newWidth, int& newHeight, int& oldWidth, int& oldHeight);
};

void ShowMyDialog(metadb_handle_list m_tracks);
