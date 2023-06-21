#pragma once
#include "stdafx.h"

class SizeInfo
{
public:
	SizeInfo(CSize size);
	SizeInfo();

	void OnSize(CSize newSize);
	int DiffWidth();
	int DiffHeight();
	CSize GetInitSize();

private:
	CSize m_initiSize;
	CSize m_newSize;
	CSize m_oldSize;
};
