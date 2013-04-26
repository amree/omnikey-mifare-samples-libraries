#if !defined(AFX_DETAILDLG_H__A0C95FCB_2DE5_4D77_9454_9CDEAD2B4724__INCLUDED_)
#define AFX_DETAILDLG_H__A0C95FCB_2DE5_4D77_9454_9CDEAD2B4724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DetailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDetailDlg dialog

class CDetailDlg : public CDialog
{
// Construction
public:
	CDetailDlg(CWnd* pParent = NULL);   // standard constructor

	unsigned char ucApp[2048];
	unsigned long ulAppLen;
	unsigned long ulAddress;

	void SetApp(unsigned char* pucApp, unsigned long ulLen,unsigned long ulAddress);
	void Show();

	BOOL OnInitDialog();

// Dialog Data
	//{{AFX_DATA(CDetailDlg)
	enum { IDD = IDD_DETAILDLG };
	CRichEditCtrl	m_ApplicationCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDetailDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DETAILDLG_H__A0C95FCB_2DE5_4D77_9454_9CDEAD2B4724__INCLUDED_)
