#pragma once
#include "stdafx.h"

class TabContent2 : public CWindowImpl<TabContent2>
{
public:
    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP(TabContent2)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        //MESSAGE_HANDLER(WM_PAINT, OnPaint)
    END_MSG_MAP()

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    void SetEditText(const char* text);
private:
    CEdit m_edit;
};
