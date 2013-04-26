#if !defined(AFX_SELECTTYPEDLG_H__7538FA18_B13B_4920_A454_86C26545B217__INCLUDED_)
#define AFX_SELECTTYPEDLG_H__7538FA18_B13B_4920_A454_86C26545B217__INCLUDED_

#if _MSC_VER > 1000 
#pragma once
#endif // _MSC_VER > 1000
// SelectTypeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectTypeDlg dialog

class SelectTypeDlg : public CDialog
{
// Construction
public:
	SelectTypeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelectTypeDlg)
	enum { IDD = IDD_TYPEN_DIALOG };
	CComboBox	m_listtyp;
	
	//}}AFX_DATA
	void getCurSelItem(char* typ);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectTypeDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTTYPEDLG_H__7538FA18_B13B_4920_A454_86C26545B217__INCLUDED_)
