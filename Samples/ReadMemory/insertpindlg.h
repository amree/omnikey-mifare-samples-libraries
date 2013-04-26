#if !defined(AFX_INSERTPINDLG_H__5A3B0292_C531_42D0_B4FA_097AB068B41B__INCLUDED_)
#define AFX_INSERTPINDLG_H__5A3B0292_C531_42D0_B4FA_097AB068B41B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertPinDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// InsertPinDlg dialog

class InsertPinDlg : public CDialog
{
// Construction
public:
	InsertPinDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(InsertPinDlg)
	enum { IDD = IDD_INSERTPIN };
	CEdit	m_pincrtl;
	CString	m_pin;
	//}}AFX_DATA
	void getPin(char*,int*);
	void setCardType(bool);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InsertPinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(InsertPinDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTPINDLG_H__5A3B0292_C531_42D0_B4FA_097AB068B41B__INCLUDED_)
