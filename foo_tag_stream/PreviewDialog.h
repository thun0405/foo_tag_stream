#pragma once

#include "stdafx.h"
#include "resource.h"

class PreviewDialog : public CDialogImpl<PreviewDialog>
{
public:
    enum {
        IDD = IDD_PREVIEW
    }; // �_�C�A���O�{�b�N�X�̃��\�[�XID

    PreviewDialog(const metadb_handle_list& tracks) : m_tracks(tracks) {}

    // �R���X�g���N�^�ɃA���o������ǉ�
    PreviewDialog(const metadb_handle_list& tracks, const pfc::string8& albumName) : m_tracks(tracks), m_albumName(albumName) {}


    BEGIN_MSG_MAP(PreviewDialog)
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
    // �A���o������ێ����郁���o�ϐ���ǉ�
    pfc::string8 m_albumName;
};

void ShowPreviewDialog(metadb_handle_list m_tracks, pfc::string8 albumName);
