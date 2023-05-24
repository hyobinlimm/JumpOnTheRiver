
// MapTool.h : main header file for the MapTool application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// CMapToolApp:
// See MapTool.cpp for the implementation of this class
//

class CMapToolApp : public CWinApp
{
public:
	CMapToolApp() noexcept;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapToolApp theApp;
