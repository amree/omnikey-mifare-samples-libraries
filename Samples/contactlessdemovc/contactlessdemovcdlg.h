// ContactlessDemoVCDlg.h : header file
//

#if !defined(AFX_CONTACTLESSDEMOVCDLG_H__CB2010EF_2963_4483_9F3D_3CE406E46368__INCLUDED_)
#define AFX_CONTACTLESSDEMOVCDLG_H__CB2010EF_2963_4483_9F3D_3CE406E46368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Led.h"
#include "SectorTrailerDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CContactlessDemoVCDlg dialog

class CContactlessDemoVCDlg : public CDialog
{
// Construction
public:

    static UINT StartCardThread(LPVOID param);	//controlling function header
	typedef struct THREADSTRUCT			 	    //structure for passing to the controlling function
	{
      CContactlessDemoVCDlg*	_this;
	} THREADSTRUCT;

    
	void TurnOnErrorLed(void);
	void ShowCursorOutScreen(void);
	ULONG CheckCLCardType(PUCHAR ATR, DWORD ATRLen);

	void EnableAllFields(void);
	void DisableAllFields(void);
	void ShowTimeRequired(void);
	void TrackCard(void);
	BOOLEAN GiveCardName(UCHAR *ucATR, ULONG ATRLen, char *CardName );
	ULONG ulMifKeyToReaderNr;
	void UcharToStr(UCHAR *ucDataBuffer, ULONG ulDataBufLen, char *str);
	void CStringToUchar(CString str, UCHAR *ucBuffer, ULONG *ulBufferLen);
	BOOLEAN CheckLetter(CString String);
	void ShowErrorMessage(long eError);
	CContactlessDemoVCDlg(CWnd* pParent = NULL);	// standard constructor
	SCARDCONTEXT    hContext;
	SCARDHANDLE     hCard ;
	DWORD dwControlFlags;
    DWORD SCard_Status;
    SCARD_READERSTATE sReaderState;
    BOOLEAN fCM5x21Selected;
	BOOLEAN fCardConnected;
    UCHAR ucATR[64];
	ULONG ulATRLen; 
    DWORD dwActiveProtocols;
    UCHAR ucUID[12];
	ULONG ulUIDBufLen;
	ULONG ulnByteUID;
    OKERR lErr;
	SYSTEMTIME			startTime, stopTime, runTime;
	FILETIME			ftimetmp;
	ULARGE_INTEGER		ulistartTime, ulistopTime, ulirunTime;
	ULONG ulAuthenticatedBlockNr;
    CString m_strCardName;
	CString m_strATR;
	CString m_strUID;
    int iColor;
	int iMode;
    int iCount;

// Dialog Data
	//{{AFX_DATA(CContactlessDemoVCDlg)
	enum { IDD = IDD_CONTACTLESSDEMOVC_DIALOG };
	CLed	m_ledError;
	CLed	m_ledSuccess;
	CListBox	m_ctrAtrList;
	CListBox	m_ctrCardNameList;
	CListBox	m_ctrUidList;
	CListBox	m_ctrOutput;
	CListBox	m_ctrReaderName;
	CString	m_strReaderName;
	long	m_longBlockNr;
	CString	m_strAuthentKey;
	int		m_intAuthentMode;
	//int		m_intAuthentKeyOption;
	int		m_intAccessOption;
	CString	m_strMifAuthentKeyNr;
	CString	m_strDataRead;
	CString	m_strDataToWrite;
	CString	m_strIncrementValue;
	CString	m_strDecrementValue;
	CString	m_strOutPutList;
	int		m_intMifTrOption;
	DWORD	m_dwNByteSend;
	CString	m_strByteSend;
	CString	m_strByteReceive;
	DWORD	m_dwNByteReceive;
	int		m_intMifKeyEnOption;
	CString	m_strMifKeyNrToWrite;
	CString	m_strMifKeyToWrite;
	CString	m_strMifEnKeyNr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContactlessDemoVCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CContactlessDemoVCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeListreader();
	afx_msg void OnRefoutputsc();
	afx_msg void OnMifauthent();
	afx_msg void OnRead();
	afx_msg void OnWrite();
	afx_msg void OnIncrement();
	afx_msg void OnDecrement();
	afx_msg void OnExit();
	afx_msg void OnAccessoptionkeynr();
	afx_msg void OnAccessoptionkey();
	afx_msg void OnTransmit();
	afx_msg void OnChangeBytesend();
	afx_msg void OnChangeAuthentkey();
	afx_msg void OnChangeIncrementval();
	afx_msg void OnChangeDecrementval();
	afx_msg void OnChangeDatatowrite();
	afx_msg void OnWritemifkey();
	afx_msg void OnMifkeytraoptionse();
	afx_msg void OnMifkeytraoptionpl();
	afx_msg void OnCompleteread();
	afx_msg void OnCompletewrite();
	afx_msg void OnMifareEmulatin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTACTLESSDEMOVCDLG_H__CB2010EF_2963_4483_9F3D_3CE406E46368__INCLUDED_)
