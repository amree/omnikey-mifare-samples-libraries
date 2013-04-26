#if !defined(AFX_KEYINFODLG_H__BFF1BAD6_E249_429D_B54E_806169F0CE52__INCLUDED_)
#define AFX_KEYINFODLG_H__BFF1BAD6_E249_429D_B54E_806169F0CE52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyInfoDlg.h : header file
//
#include <winscard.h>

#define SUCCESS			0x00
#define UNSUCCESSFUL	0x01



/////////////////////////////////////////////////////////////////////////////
// KeyInfoDlg dialog

class KeyInfoDlg : public CDialog
{
// Construction
public:
	KeyInfoDlg(CWnd* pParent = NULL);   // standard constructor

	unsigned char m_KeyPlaceList[8];
	int m_KeyPlaceListLen;
	unsigned char m_P1;

	char szReaderName[128];

	SCARDCONTEXT hContext;
	SCARDHANDLE hCard;

	BOOL OnInitDialog();

	void SetReaderName(char* pszReaderName);
	void SetKeyPlaceList(unsigned char* pucKeyPlaceList,int x,unsigned char ucP1);

	int CardGetKeyInfo(unsigned char ucP1,unsigned char ucKeyPlace,
				   unsigned char* pucKeyInfo,unsigned long *pulKeyInfoLen);

	int CardConnect();
	int CardDisconnect();
	int CardEstablishContext();
	int CardReleaseContext();
	int CardAuthenticateKiamc();

// Dialog Data
	//{{AFX_DATA(KeyInfoDlg)
	enum { IDD = IDD_KEYINFO };
	CListCtrl	m_KeyInfoListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(KeyInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(KeyInfoDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYINFODLG_H__BFF1BAD6_E249_429D_B54E_806169F0CE52__INCLUDED_)
