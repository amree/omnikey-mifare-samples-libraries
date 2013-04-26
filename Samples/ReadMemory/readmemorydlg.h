// ReadMemoryDlg.h : header file
//

#if !defined(AFX_READMEMORYDLG_H__DE505B2F_21E7_47A0_B7E8_8839308CC525__INCLUDED_)
#define AFX_READMEMORYDLG_H__DE505B2F_21E7_47A0_B7E8_8839308CC525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReadMemoryDlg dialog

class CReadMemoryDlg : public CDialog
{
// Construction
public:
	CReadMemoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReadMemoryDlg)
	enum { IDD = IDD_READMEMORY_DIALOG };
	CRichEditCtrl	m_richedit;
	CButton	m_write;
	CButton	m_presentpin;
	CListBox	m_readerlist;
	CButton	m_okbutton;
	//}}AFX_DATA
	int ConnectToCard();
	int ReadData();
	void ShowData(BYTE*,int);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadMemoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReadMemoryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void errorfunk();
	afx_msg void OnPresentpin();
	virtual void OnCancel();
	afx_msg void OnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READMEMORYDLG_H__DE505B2F_21E7_47A0_B7E8_8839308CC525__INCLUDED_)
