
// Project1.h : main header file for the Project1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


/**
 * CProject1App:
 * See Project1.cpp for the implementation of this class
 */
class CProject1App : public CWinApp
{
public:
	CProject1App() noexcept;


// Overrides
public:
	/// Initializes Instance
	/// \returns Boolean
	virtual BOOL InitInstance();
	/// Exits Instance
	/// \returns Int
	virtual int ExitInstance();

// Implementation

public:
	/// On App About
	/// \returns Void
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	/// The Startup input of Gdiplus
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	/// The Gdiplus token used
	ULONG_PTR gdiplusToken = 0;
};

extern CProject1App theApp;
