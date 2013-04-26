// iClassExplorerDlg.h : header file
//

#if !defined(AFX_ICLASSEXPLORERDLG_H__40584DC3_1612_4D60_89E4_9083B90F1BD0__INCLUDED_)
#define AFX_ICLASSEXPLORERDLG_H__40584DC3_1612_4D60_89E4_9083B90F1BD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winscard.h>

// Global Defines

#define SUCCESS			0x00
#define UNSUCCESSFUL	0x01

#define READERNAMESIZE 128

/////////////////////////////////////////////////////////////////////////////
// CIClassExplorerDlg dialog

class CIClassExplorerDlg : public CDialog
{
// Construction
public:
	CIClassExplorerDlg(CWnd* pParent = NULL);	// standard constructor
	
	SCARDCONTEXT hContext;
	SCARDHANDLE hCard;

	void GetReaders();
// Dialog Data
	//{{AFX_DATA(CIClassExplorerDlg)
	enum { IDD = IDD_ICLASSEXPLORER_DIALOG };
	CButton	m_CardReportButton;
	CListBox	m_ReaderList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIClassExplorerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIClassExplorerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICLASSEXPLORERDLG_H__40584DC3_1612_4D60_89E4_9083B90F1BD0__INCLUDED_)
