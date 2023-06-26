#include "stdafx.h"
#include "TabContent2.h"

LRESULT TabContent2::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(&ps);

    RECT rect;
    GetClientRect(&rect);
    DrawText(hdc, _T("This is Tab 2"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    EndPaint(&ps);
    return 0;
}
