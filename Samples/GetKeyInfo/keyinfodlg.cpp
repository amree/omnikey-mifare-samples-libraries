// KeyInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetKeyInfo.h"
#include "KeyInfoDlg.h"

#include <winscard.h>

#include "ok.h"
#include "scardcl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// KeyInfoDlg dialog


KeyInfoDlg::KeyInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(KeyInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(KeyInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void KeyInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(KeyInfoDlg)
	DDX_Control(pDX, IDC_VOLMEMKEYLIST, m_KeyInfoListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(KeyInfoDlg, CDialog)
	//{{AFX_MSG_MAP(KeyInfoDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// KeyInfoDlg message handlers
void KeyInfoDlg::SetKeyPlaceList(unsigned char* pucKeyPlaceList,int x,unsigned char ucP1)
{
	memcpy(this->m_KeyPlaceList,pucKeyPlaceList,x);
	this->m_KeyPlaceListLen=x;
	this->m_P1=ucP1;
}

void KeyInfoDlg::SetReaderName(char* pszReaderName)
{
	strcpy(szReaderName,pszReaderName);
}

BOOL KeyInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int i=0;
	int rc=0;
	int y=0;

	LONG lWnd;
	CRect rct;

	CString csSlot;
	CString csAccess;
	CString csKeyName;
	CString csKeyLength;
	CString csAddInfo;

	unsigned char ucKeyInfo[4] = {0};
	unsigned long ulKeyInfoLen = sizeof(ucKeyInfo);

	// Set style
	lWnd=::GetWindowLong(m_KeyInfoListCtrl.GetSafeHwnd(),GWL_STYLE);
	lWnd |= LVS_REPORT;
	::SetWindowLong(m_KeyInfoListCtrl.GetSafeHwnd(),GWL_STYLE,lWnd);
	this->m_KeyInfoListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);


	m_KeyInfoListCtrl.GetClientRect(& rct);

	// insert columns
	m_KeyInfoListCtrl.InsertColumn(0,"Slot",LVCFMT_LEFT,30,-1);
	m_KeyInfoListCtrl.InsertColumn(1,"Name",LVCFMT_LEFT,120,-1);
	m_KeyInfoListCtrl.InsertColumn(2,"Length",LVCFMT_LEFT,40,-1);
	m_KeyInfoListCtrl.InsertColumn(3,"Access",LVCFMT_LEFT,140,-1);
	m_KeyInfoListCtrl.InsertColumn(4,"Additional Information",LVCFMT_LEFT,rct.Width()-300,-1);


	// Connect
	rc = CardEstablishContext();
	if(rc != SUCCESS)
	{
		MessageBox("Unable to establish Context",NULL,MB_ICONSTOP|MB_OK);
		CDialog::OnOK();
		return FALSE;
	}
	rc = CardConnect();
	if(rc!=SUCCESS)	
	{
		MessageBox("Unable to connect, please insert card",NULL,MB_ICONSTOP|MB_OK);
		CDialog::OnOK();
		return FALSE;
	}

	y=0;

	
	for(i=0;i<256;i++)
	{
		csKeyName.Format("");
		csKeyLength.Format("");
		csAccess.Format("");
		csAddInfo.Format("");

		
		if((i >= 0x00 && i <= 0x35))
		{
			ulKeyInfoLen = sizeof(ucKeyInfo);
			rc = CardGetKeyInfo(0x00,(unsigned char)i,ucKeyInfo,&ulKeyInfoLen);
			if(rc != SUCCESS) // try next keyplace
			{
				i=256;
				CDialog::OnOK();
				continue;		
			}

			if(ucKeyInfo[0] >= 0x00 && ucKeyInfo[0] <= 0x1F)
			{
				csKeyName.Format("Mifare Key %d",ucKeyInfo[0]);
				csKeyLength.Format("6");
			}
			else
				switch(ucKeyInfo[0])
				{
				case 0x20: csKeyName.Format("Kiamc");
					csKeyLength.Format("8");
					break;
				case 0x21: csKeyName.Format("Kmdc");
					csKeyLength.Format("8");
					break;
				case 0x22: csKeyName.Format("Kmdo");
					csKeyLength.Format("8");
					break;
				case 0x23: csKeyName.Format("Kmc0");
					csKeyLength.Format("8");
					break;
				case 0x24: csKeyName.Format("Kmd1");
					csKeyLength.Format("8");
					break;
				case 0x25: csKeyName.Format("Kmc1");
					csKeyLength.Format("8");
					break;
				case 0x26: csKeyName.Format("Kmd2");
					csKeyLength.Format("8");
					break;
				case 0x27: csKeyName.Format("Kmc2");
					csKeyLength.Format("8");
					break;
				case 0x28: csKeyName.Format("Kmd3");
					csKeyLength.Format("8");
					break;
				case 0x29: csKeyName.Format("Kmc3");
					csKeyLength.Format("8");
					break;
				case 0x2A: csKeyName.Format("Kmd4");
					csKeyLength.Format("8");
					break;
				case 0x2B: csKeyName.Format("Kmc4");
					csKeyLength.Format("8");
					break;
				case 0x2C: csKeyName.Format("Kmd5");
					csKeyLength.Format("8");
					break;
				case 0x2D: csKeyName.Format("Kmc5");
					csKeyLength.Format("8");
					break;
				case 0x2E: csKeyName.Format("Kmd6");
					csKeyLength.Format("8");
					break;
				case 0x2F: csKeyName.Format("Kmc6");
					csKeyLength.Format("8");
					break;
				case 0x30: csKeyName.Format("Kmd7");
					csKeyLength.Format("8");
					break;
				case 0x31: csKeyName.Format("Kmc7");
					csKeyLength.Format("8");
					break;
				case 0x80: csKeyName.Format("Kcur");
					csKeyLength.Format("16");
					break;
				case 0x81: csKeyName.Format("Kcuw");
					csKeyLength.Format("16");
					break;
				case 0x82: csKeyName.Format("Kenc");
					csKeyLength.Format("16");
					break;
				case 0xF0: csKeyName.Format("Kvap");
					csKeyLength.Format("8");
					csAddInfo.Format("volatile memory");
					break;
				}

			csSlot.Format("%02X",i/*this->m_KeyPlaceList[i]*/);
				
			
			if(ulKeyInfoLen == 2 && ucKeyInfo[ulKeyInfoLen-2] == 0x63 && ucKeyInfo[ulKeyInfoLen-1] == 0x00)
			{
				csAccess.Format("n/a");
				csAddInfo.Format("no information given");
			}
			else
			if(ulKeyInfoLen == 2 && ucKeyInfo[ulKeyInfoLen-2] == 0x63 && ucKeyInfo[ulKeyInfoLen-1] == 0x01)
			{
				csAccess.Format("n/a");
				csAddInfo.Format("empty");
			}
			else
			if(ulKeyInfoLen > 2 && ucKeyInfo[ulKeyInfoLen-2] == 0x90 && ucKeyInfo[ulKeyInfoLen-1] == 0x00)
			{
				// valid sw1sw2

				if(!(ucKeyInfo[1] & 0x04))
				{
					// valid key data
					switch(ucKeyInfo[1] & 0x03)
					{
					case 0: csAccess.Format("always");
						break;
					case 1: csAccess.Format("only in OMNIKEY secured mode");
						break;
					case 2: csAccess.Format("never");
						break;
					case 3: csAccess.Format("RFU");
						break;
					}
				}
			}

			m_KeyInfoListCtrl.InsertItem(y,csSlot);
			m_KeyInfoListCtrl.SetItem(y,1,LVIF_TEXT,csKeyName,0,0,0,0);
			m_KeyInfoListCtrl.SetItem(y,2,LVIF_TEXT,csKeyLength,0,0,0,0);
			m_KeyInfoListCtrl.SetItem(y,3,LVIF_TEXT,csAccess,0,0,0,0);
			m_KeyInfoListCtrl.SetItem(y,4,LVIF_TEXT,csAddInfo,0,0,0,0);

			y++;
		}

	}

	// ignore returncode
	rc = CardDisconnect();
	rc = CardReleaseContext();
	
	return rc;
}


int KeyInfoDlg::CardConnect()
{
	int rc = UNSUCCESSFUL;
	DWORD dwActiveProtocol;

	rc = SCardConnect(hContext,this->szReaderName,SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
	if(rc != SCARD_S_SUCCESS)
	{
		return rc;
	}

	return SUCCESS;
}

int KeyInfoDlg::CardEstablishContext()
{
	int rc = UNSUCCESSFUL;

	rc = SCardEstablishContext(SCARD_SCOPE_USER,NULL,NULL,&hContext);
	if(rc != SCARD_S_SUCCESS)
	{
		rc = UNSUCCESSFUL;
	}

	return rc;
}

// Disconnect from card and release context
int KeyInfoDlg::CardDisconnect()
{
	int rc = SUCCESS;

	if(hCard != 0xFFFFFFFF)
	{
		rc = SCardDisconnect(hCard,SCARD_LEAVE_CARD);
		hCard = 0xFFFFFFFF;
	}

	return rc;
}

int KeyInfoDlg::CardReleaseContext()
{
	int rc = SUCCESS;

	if(hContext != 0xFFFFFFFF)
	{
		rc = SCardReleaseContext(hContext);
		hContext = 0xFFFFFFFF;
	}

	return rc;
}


int KeyInfoDlg::CardGetKeyInfo(unsigned char ucP1,unsigned char ucKeyPlace,
				   unsigned char* pucKeyInfo,unsigned long *pulKeyInfoLen)
{
	int rc = SUCCESS;

	char szTemp[128];

	unsigned char ucSend[8] = {0};
	unsigned long ulSendLen = 0;

	ucSend[ulSendLen++]=0x80;
	ucSend[ulSendLen++]=0xC4;
	ucSend[ulSendLen++]=0x00;
	//ucSend[ulSendLen++]=ucP1;
	//ucSend[ulSendLen++]=0x01;
	ucSend[ulSendLen++]=ucKeyPlace;
	ucSend[ulSendLen++]=0x02;

	rc = SCardCLICCTransmit(hCard,ucSend,ulSendLen,pucKeyInfo,pulKeyInfoLen);
	if(rc != SCARD_S_SUCCESS)
	{
		// error
		sprintf(szTemp,"Error at SCardCLICCTransmit() (0x%08X)\r\n",rc);
		MessageBox(szTemp,NULL,MB_ICONSTOP|MB_OK);
	}

	return rc;
}

int KeyInfoDlg::CardAuthenticateKiamc()
{
	int rc = SUCCESS;

	unsigned char ucSend[16];
	unsigned char ucReceive[32];

	unsigned long ulSendLen=sizeof(ucSend);
	unsigned long ulReceiveLen=sizeof(ucReceive);

	// copy send command (authenticate kd with stored kiamc)
	memcpy(ucSend,"\x80\x88\x00\x20",4);
	ulSendLen=4;

	rc = SCardCLICCTransmit(hCard,ucSend,ulSendLen,ucReceive,&ulReceiveLen);
	if(rc != SCARD_S_SUCCESS)
	{
		// error
		//sprintf(szTemp,"Error at SCardCLICCTransmit(..)\r\n",szTemp);
		MessageBox("Error at SCardCLICCTransmit() Errorcode: (0x\x08)",NULL,MB_OK);
	}

	
	rc = UNSUCCESSFUL;
	if(ulReceiveLen >= 2)
	{
		if(ucReceive[ulReceiveLen-2] == 0x90 && ucReceive[ulReceiveLen-1] == 0x00)
		{
			// authenticate passed
			rc = SUCCESS;
		}
	}

	return rc;
}
