#pragma once
#include "stdafx.h"
#include "resource.h"

class CsvDialog : public CDialogImpl<CsvDialog>
{
public:
    enum { IDD = IDD_CSV_DIALOG };

    CsvDialog(metadb_handle_list_cref p_data);

    BEGIN_MSG_MAP(CsvDialog)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnOK)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

private:
    metadb_handle_list m_data;
    CEdit m_edit;
};