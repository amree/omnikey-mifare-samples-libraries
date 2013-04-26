// CheckProtected.h : main header file for the CHECKPROTECTED application
//

#if !defined(AFX_CHECKPROTECTED_H__E2948F42_C196_49E5_B360_60757B784E14__INCLUDED_)
#define AFX_CHECKPROTECTED_H__E2948F42_C196_49E5_B360_60757B784E14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCheckProtectedApp:
// See CheckProtected.cpp for the implementation of this class
//

class CCheckProtectedApp : public CWinApp
{
public:
	CCheckProtectedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckProtectedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCheckProtectedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKPROTECTED_H__E2948F42_C196_49E5_B360_60757B784E14__INCLUDED_)
