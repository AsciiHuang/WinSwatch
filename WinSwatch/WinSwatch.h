// WinSwatch.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CWinSwatchApp:
// �аѾ\��@�����O�� WinSwatch.cpp
//

class CWinSwatchApp : public CWinApp
{
public:
	CWinSwatchApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CWinSwatchApp theApp;