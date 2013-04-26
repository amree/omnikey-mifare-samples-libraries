// GetKeyInfo.h : main header file for the GETKEYINFO application
//

#if !defined(AFX_GETKEYINFO_H__B380E4C4_73CC_4BF2_9EAB_E98CBD843EF1__INCLUDED_)
#define AFX_GETKEYINFO_H__B380E4C4_73CC_4BF2_9EAB_E98CBD843EF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetKeyInfoApp:
// See GetKeyInfo.cpp for the implementation of this class
//

class CGetKeyInfoApp : public CWinApp
{
public:
	CGetKeyInfoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetKeyInfoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetKeyInfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETKEYINFO_H__B380E4C4_73CC_4BF2_9EAB_E98CBD843EF1__INCLUDED_)
