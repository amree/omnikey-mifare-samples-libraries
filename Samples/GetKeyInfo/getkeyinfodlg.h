// GetKeyInfoDlg.h : header file
//

#if !defined(AFX_GETKEYINFODLG_H__0CE37A55_3AC1_480F_B5E2_4E5E8A03EEFC__INCLUDED_)
#define AFX_GETKEYINFODLG_H__0CE37A55_3AC1_480F_B5E2_4E5E8A03EEFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winscard.h>

/////////////////////////////////////////////////////////////////////////////
// CGetKeyInfoDlg dialog

class CGetKeyInfoDlg : public CDialog
{
// Construction
public:
	CGetKeyInfoDlg(CWnd* pParent = NULL);	// standard constructor

	SCARDCONTEXT hContext;
	SCARDHANDLE hCard;

	char m_szReaderName[128];

	void GetReaders();

// Dialog Data
	//{{AFX_DATA(CGetKeyInfoDlg)
	enum { IDD = IDD_GETKEYINFO_DIALOG };
	CListBox	m_ReaderList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetKeyInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetKeyInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetinfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETKEYINFODLG_H__0CE37A55_3AC1_480F_B5E2_4E5E8A03EEFC__INCLUDED_)
