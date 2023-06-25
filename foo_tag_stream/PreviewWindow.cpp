#include "stdafx.h"
#include "resource.h"
#include "PreviewWindow.h"
#include "ListViewManager.h"
#include "ButtonManager.h"

PreviewWindow::PreviewWindow(metadb_handle_list_cref tracks)
    : m_tracks(tracks)
{}

PreviewWindow::~PreviewWindow()
{}

LRESULT PreviewWindow::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // ダイアログボックスの初期サイズを取得してm_sizeに設定
    CRect rect;
    GetClientRect(&rect);
    m_sizeInfo = SizeInfo(rect.Size());

    ListViewManager listViewManager = ListViewManager(m_listView, this);
    listViewManager.InitializeListView();
    listViewManager.PopulateListView(m_tracks, "");

    return TRUE;
}

LRESULT PreviewWindow::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    PostQuitMessage(0);
    return 0;
}

LRESULT PreviewWindow::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    m_sizeInfo.OnSize(CSize(LOWORD(lParam), HIWORD(lParam)));
    int diffWidth = m_sizeInfo.DiffWidth();
    int diffHeight = m_sizeInfo.DiffHeight();

    ListViewManager listViewManager = ListViewManager(m_listView, this);
    ButtonManager okButtonManager = ButtonManager(m_okButton, this);
    ButtonManager cancelButtonManager = ButtonManager(m_cancelButton, this);

    // リストビューコントロールのサイズを更新
    listViewManager.UpdateSize(diffWidth, diffHeight);

    // ボタンの位置を更新
    okButtonManager.UpdatePosition(diffWidth, diffHeight);
    cancelButtonManager.UpdatePosition(diffWidth, diffHeight);

    return 0;
}

LRESULT PreviewWindow::OnGetMinMaxInfo(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
    CSize initSize = m_sizeInfo.GetInitSize();
    MINMAXINFO* pMinMax = (MINMAXINFO*)lParam;
    pMinMax->ptMinTrackSize.x = initSize.cx;
    pMinMax->ptMinTrackSize.y = initSize.cy;

    return 0;
}

LRESULT PreviewWindow::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // OKボタンが押されたときの処理をここに書く
    // ここでは、リストビューに表示されているデータを元にメタデータを更新する
    // （この部分はPreviewDialogの目的に合わせて修正する必要があります）

    return 0;
}

LRESULT PreviewWindow::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // キャンセルボタンが押されたときの処理をここに書く

    return 0;
}

void ShowPreviewWindow(metadb_handle_list m_tracks)
{
    PreviewWindow wnd(m_tracks);
    wnd.Create(NULL, CWindow::rcDefault, _T("Preview Window"), WS_OVERLAPPEDWINDOW);
    wnd.ShowWindow(SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
