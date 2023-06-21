#include "stdafx.h"
#include "SizeInfo.h"

SizeInfo::SizeInfo(CSize size)
    : m_initiSize(size), m_newSize(size)
{}

SizeInfo::SizeInfo()
{}

void SizeInfo::OnSize(CSize newSize)
{
    m_oldSize = m_newSize;
    m_newSize = newSize;
}

int SizeInfo::DiffWidth()
{
    return m_newSize.cx - m_oldSize.cx;
}

int SizeInfo::DiffHeight()
{
    return m_newSize.cy - m_oldSize.cy;
}

CSize SizeInfo::GetInitSize()
{
    return m_initiSize;;
}
