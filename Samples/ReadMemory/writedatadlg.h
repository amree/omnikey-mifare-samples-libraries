#if !defined(AFX_WRITEDATADLG_H__B2A9616C_B0DC_4CDA_BB15_CB9352326336__INCLUDED_)
#define AFX_WRITEDATADLG_H__B2A9616C_B0DC_4CDA_BB15_CB9352326336__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WriteDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WriteDataDlg dialog

class WriteDataDlg : public CDialog
{
// Construction
public:
	WriteDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(WriteDataDlg)
	enum { IDD = IDD_DATADIALOG };
	CEdit	m_offsetctrl;
	CString	m_writebuffer;
	CButton	m_hex;
	CButton	m_ascii;
	CString	m_offset;
	CString	m_muhkuh;
	//}}AFX_DATA
	void getData(char*,int*,int*);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WriteDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WriteDataDlg)
	afx_msg void OnASCII();
	afx_msg void OnHEX();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEDATADLG_H__B2A9616C_B0DC_4CDA_BB15_CB9352326336__INCLUDED_)
