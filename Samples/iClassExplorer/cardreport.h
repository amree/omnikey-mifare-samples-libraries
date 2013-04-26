#if !defined(AFX_CARDREPORT_H__557A967D_4643_4188_8C83_A2E290695D86__INCLUDED_)
#define AFX_CARDREPORT_H__557A967D_4643_4188_8C83_A2E290695D86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CardReport.h : header file
//

#include <winscard.h>
#include "iClassExplorerDlg.h"

#define APPLICATION_START_ADDRESS 0x06

#define GBD_SUCCESS			0x00
#define GBD_UNSUCCESSFUL	0x01
#define GBD_INVALID_LENGTH	0x02
#define GBD_EMPTY_KEY		0x03

/////////////////////////////////////////////////////////////////////////////
// CCardReport dialog

class CCardReport : public CDialog
{
// Construction
public:
	CCardReport(CWnd* pParent = NULL);   // standard constructor

	SCARDCONTEXT hContext;
	SCARDHANDLE hCard;

	char szReaderName[READERNAMESIZE];

	unsigned char ucCurPageNumber;

	unsigned char ucSerialNumber[8];
	unsigned char ucConfigBlock[8];
	unsigned char ucApplicationIssuer[8];

	BOOL OnInitDialog();

	void SetReaderName(char* pszReaderName);

	int GetByteData(CString from, unsigned char** to,unsigned long* len);

	int Show(unsigned char ucPageNum);
	int ShowData(int iType,unsigned char* pucData);

	int CardConnect();
	int CardDisconnect();
	int CardSelect(unsigned char ucSelectP1, unsigned char ucSelectP2,
					unsigned char ucDataByte, unsigned char** ppucReceive,unsigned long* piReceiveLen);
	int CardAuthenticate(unsigned char ucKeyType,unsigned char ucKeyNumber);
	int CardRead(unsigned long ulAddress,unsigned long ulLen, unsigned char* ucData,unsigned long* ulDataLen);
	int CardLoadKey(unsigned char* pucKey,unsigned long ulKeyLen, unsigned char ucKeyNumber, unsigned char ucKeyStruct);

// Dialog Data
	//{{AFX_DATA(CCardReport)
	enum { IDD = IDD_CARDREPORT };
	CButton	m_NextPage;
	CButton	m_PrevPage;
	CString	m_ApplicationIssuer;
	CString	m_SerialNumber;
	CString	m_MemoryConfig;
	CString	m_Fuses;
	CString	m_Eas;
	CString	m_ChipConfig;
	CString	m_BlockWriteLock;
	CString	m_ApplicationOTPArea;
	CString	m_ApplicationLimit;
	CString	m_StaticPage;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCardReport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCardReport)
	afx_msg void OnNextPage();
	afx_msg void OnPrevPage();
	afx_msg void OnDetail();
	afx_msg void OnNextpage();
	afx_msg void OnPrevpage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARDREPORT_H__557A967D_4643_4188_8C83_A2E290695D86__INCLUDED_)
