#if !defined(AFX_SECTORTRAILERDLG_H__097EAC13_35B8_4106_83A9_FCF17340D8FC__INCLUDED_)
#define AFX_SECTORTRAILERDLG_H__097EAC13_35B8_4106_83A9_FCF17340D8FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SectorTrailerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SectorTrailerDlg dialog

class SectorTrailerDlg : public CDialog
{
// Construction
public:
	SectorTrailerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SectorTrailerDlg)
	enum { IDD = IDD_SECTORTRAILER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SectorTrailerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SectorTrailerDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECTORTRAILERDLG_H__097EAC13_35B8_4106_83A9_FCF17340D8FC__INCLUDED_)
