#include "stdafx.h"
#include "ui_dialog.h"

LRESULT MyDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // ダイアログボックスの初期化処理をここに書く
    return TRUE;
}

LRESULT MyDialog::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // OKボタンが押されたときの処理をここに書く
    EndDialog(wID);
    return 0;
}

LRESULT MyDialog::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // キャンセルボタンが押されたときの処理をここに書く
    EndDialog(wID);
    return 0;
}

void ShowMyDialog()
{
    MyDialog dlg;
    dlg.DoModal();
}
