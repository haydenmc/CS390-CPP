// MyDraw.h : main header file for the MyDraw application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyDrawApp:
// See MyDraw.cpp for the implementation of this class
//

class CMyDrawApp : public CWinApp
{
public:
	CMyDrawApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyDrawApp theApp;