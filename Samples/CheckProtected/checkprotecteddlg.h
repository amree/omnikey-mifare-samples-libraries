// CheckProtectedDlg.h : header file
//

#if !defined(AFX_CHECKPROTECTEDDLG_H__A16EF989_3D95_4777_B4DC_11DA551BC132__INCLUDED_)
#define AFX_CHECKPROTECTEDDLG_H__A16EF989_3D95_4777_B4DC_11DA551BC132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCheckProtectedDlg dialog

class CCheckProtectedDlg : public CDialog
{
// Construction
public:
	CCheckProtectedDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckProtectedDlg)
	enum { IDD = IDD_CHECKPROTECTED_DIALOG };
	CRichEditCtrl	m_richedit;
	CButton	m_okbutton;
	CListBox	m_readerlist;
	//}}AFX_DATA
	int ConnectToCard();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckProtectedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCheckProtectedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKPROTECTEDDLG_H__A16EF989_3D95_4777_B4DC_11DA551BC132__INCLUDED_)
