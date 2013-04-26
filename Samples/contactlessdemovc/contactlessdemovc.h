// ContactlessDemoVC.h : main header file for the CONTACTLESSDEMOVC application
//

#if !defined(AFX_CONTACTLESSDEMOVC_H__35D92726_0685_4876_8550_938BBC6F76BD__INCLUDED_)
#define AFX_CONTACTLESSDEMOVC_H__35D92726_0685_4876_8550_938BBC6F76BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CContactlessDemoVCApp:
// See ContactlessDemoVC.cpp for the implementation of this class
//

class CContactlessDemoVCApp : public CWinApp
{
public:
	static void TrackThread(void *pSender);
	CContactlessDemoVCApp();
	LONG  m_hThread;
	BOOL m_fStopThread;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContactlessDemoVCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CContactlessDemoVCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTACTLESSDEMOVC_H__35D92726_0685_4876_8550_938BBC6F76BD__INCLUDED_)
