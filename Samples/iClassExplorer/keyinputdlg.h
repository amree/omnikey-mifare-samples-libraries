#if !defined(AFX_KEYINPUTDLG_H__8AD7AD3B_0DC6_423A_A1F2_39ADE803AEB2__INCLUDED_)
#define AFX_KEYINPUTDLG_H__8AD7AD3B_0DC6_423A_A1F2_39ADE803AEB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyInputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKeyInputDlg dialog

class CKeyInputDlg : public CDialog
{
// Construction
public:
	CKeyInputDlg(CWnd* pParent = NULL, unsigned char ucPage = 0x00);   // standard constructor

	BOOL OnInitDialog();

	unsigned char m_Page;
	unsigned char m_KeyType;

// Dialog Data
	//{{AFX_DATA(CKeyInputDlg)
	enum { IDD = IDD_KEYDLG };
	CString	m_Key;
	CString	m_KeyNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKeyInputDlg)
	afx_msg void OnKdradio();
	afx_msg void OnKcradio();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYINPUTDLG_H__8AD7AD3B_0DC6_423A_A1F2_39ADE803AEB2__INCLUDED_)
