#pragma once

#include "stdafx.h"
#include "resource.h"

class MyDialog : public CDialogImpl<MyDialog>
{
public:
    enum {
        IDD = IDD_DIALOG
    }; // ダイアログボックスのリソースID

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
};

void ShowMyDialog(metadb_handle_list m_tracks);


class ListViewManager {
public:
	ListViewManager(CListViewCtrl listView, CWindow* window)
		: m_listView(listView)
	{
		// リストビューコントロールの現在の位置とサイズを取得
		CRect rect;
		m_listView.GetWindowRect(&rect);
		window->ScreenToClient(&rect);

		m_currentSize = rect.Size();
		m_currentPosition = rect.TopLeft();
	}

	void UpdateSize(int diffWidth, int diffHeight);

private:
	CListViewCtrl m_listView;
	CSize m_currentSize;
	CPoint m_currentPosition;
};

class ButtonManager {
public:
	ButtonManager(CButton button, CWindow* window)
		: m_button(button)
	{
		// ボタンの現在の位置とサイズを取得
		CRect rect;
		m_button.GetWindowRect(&rect);
		window->ScreenToClient(&rect);

		m_currentSize = rect.Size();
		m_currentPosition = rect.TopLeft();
	}

	void UpdatePosition(int diffWidth, int diffHeight);

private:
	CButton m_button;
	CSize m_currentSize;
	CPoint m_currentPosition;
};
