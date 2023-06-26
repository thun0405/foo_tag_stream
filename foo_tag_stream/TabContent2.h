#pragma once
#include "stdafx.h"

class TabContent2 : public CWindowImpl<TabContent2>
{
public:
    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP(TabContent2)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
