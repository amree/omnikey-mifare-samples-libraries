// CardReport.cpp : implementation file
//

#include "stdafx.h"
#include "iClassExplorer.h"
#include "CardReport.h"
#include "KeyInputDlg.h"
#include "DetailDlg.h"

#include "ok.h"
#include "scardcl.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCardReport dialog


CCardReport::CCardReport(CWnd* pParent /*=NULL*/)
	: CDialog(CCardReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCardReport)
		// NOTE: the ClassWizard will add member initialization here
	m_ApplicationIssuer = _T("");
	m_SerialNumber = _T("");
	m_MemoryConfig = _T("");
	m_Fuses = _T("");
	m_Eas = _T("");
	m_ChipConfig = _T("");
	m_BlockWriteLock = _T("");
	m_ApplicationOTPArea = _T("");
	m_ApplicationLimit = _T("");
	m_StaticPage = _T("");
	//}}AFX_DATA_INIT
}


void CCardReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCardReport)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_NEXTPAGE, m_NextPage);
	DDX_Control(pDX, IDC_PREVPAGE, m_PrevPage);
	DDX_Text(pDX, IDC_APPLICATIONISSUER, m_ApplicationIssuer);
	DDX_Text(pDX, IDC_SERIALNUMBER, m_SerialNumber);
	DDX_Text(pDX, IDC_MEMORYCONFIG, m_MemoryConfig);
	DDX_Text(pDX, IDC_FUSES, m_Fuses);
	DDX_Text(pDX, IDC_EAS, m_Eas);
	DDX_Text(pDX, IDC_CHIPCONFIG, m_ChipConfig);
	DDX_Text(pDX, IDC_BLOCKWRITELOCK, m_BlockWriteLock);
	DDX_Text(pDX, IDC_APPOTPAREA, m_ApplicationOTPArea);
	DDX_Text(pDX, IDC_APPLIMIT, m_ApplicationLimit);
	DDX_Text(pDX, IDC_STATIC_PAGE, m_StaticPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCardReport, CDialog)
	//{{AFX_MSG_MAP(CCardReport)
	ON_BN_CLICKED(IDC_NEXTPAGE, OnNextpage)
	ON_BN_CLICKED(IDC_PREVPAGE, OnPrevpage)
	ON_BN_CLICKED(IDC_DETAIL, OnDetail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCardReport message handlers

void CCardReport::SetReaderName(char* pszReaderName)
{
	strcpy(szReaderName,pszReaderName);
}

BOOL CCardReport::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(Show(0) != SUCCESS)
		CDialog::OnOK();

	return TRUE;
}

int CCardReport::Show(unsigned char ucPageNum)
{
	int rc = 0;

	unsigned char ucSelectP1,ucSelectP2,ucDataByte;
	unsigned char ucReceive[32] = {0};
	unsigned long ulReceiveLen=sizeof(ucReceive);

	unsigned char* pucReceive=ucReceive;

	ucSelectP1 = ucSelectP2 = ucDataByte = 0x00;

	// connect to card
	rc = CardConnect();
	if(rc != SUCCESS)
	{
		MessageBox("Unable to Connect to Card","Card Report",MB_ICONSTOP|MB_OK);
		return UNSUCCESSFUL;
	}

	
	ucSelectP1=0x01; // use multipage
	ucDataByte=ucPageNum; 

	// Get Serial Number
	ucSelectP2=0x04;
	
	memset(ucReceive,0x00,sizeof(ucReceive));
	ulReceiveLen=sizeof(ucReceive);
	rc = CardSelect(ucSelectP1,ucSelectP2,ucDataByte,&pucReceive,&ulReceiveLen);
	if(rc != SUCCESS)
	{
		ulReceiveLen=sizeof(ucReceive);
		ucSelectP1=0x00;
		rc = CardSelect(ucSelectP1,ucSelectP2,ucDataByte,&pucReceive,&ulReceiveLen);
		if(rc != SUCCESS)
		{
			goto EXIT;
		}
	}

	// only set current page number to new value if select was successful
	ucCurPageNumber=ucPageNum;

	if(ulReceiveLen > 2)
		memcpy(ucSerialNumber,pucReceive,ulReceiveLen-2);

	// Get Config Block
	ucSelectP2=0x08;
	memset(ucReceive,0x00,sizeof(ucReceive));
	ulReceiveLen=sizeof(ucReceive);
	rc = CardSelect(ucSelectP1,ucSelectP2,ucDataByte,&pucReceive,&ulReceiveLen);
	if(rc != SUCCESS)
	{
		goto EXIT;
	}

	if(ulReceiveLen > 2)
		memcpy(ucConfigBlock,pucReceive,ulReceiveLen-2);

	// Get Application Issuer Data
	ucSelectP2=0x0C;
	memset(ucReceive,0x00,sizeof(ucReceive));
	ulReceiveLen=sizeof(ucReceive);
	rc = CardSelect(ucSelectP1,ucSelectP2,ucDataByte,&pucReceive,&ulReceiveLen);
	if(rc != SUCCESS)
	{
		goto EXIT;
	}

	if(ulReceiveLen > 2)
		memcpy(ucApplicationIssuer,pucReceive,ulReceiveLen-2);


	// show data
	ShowData(0x04,ucSerialNumber);
	ShowData(0x08,ucConfigBlock);
	ShowData(0x0C,ucApplicationIssuer);

EXIT:
	rc = CardDisconnect();
	if(rc != SUCCESS)
	{
		return UNSUCCESSFUL;
	}

	UpdateData(FALSE);

	//return CDialog::DoModal();

	return SUCCESS;
}

int CCardReport::CardConnect()
{
	int rc = UNSUCCESSFUL;
	DWORD dwActiveProtocol;

	rc = SCardEstablishContext(SCARD_SCOPE_USER,NULL,NULL,&hContext);
	if(rc != SCARD_S_SUCCESS)
	{
		return rc;
	}

	rc = SCardConnect(hContext,szReaderName,SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &dwActiveProtocol);
	if(rc != SCARD_S_SUCCESS)
	{
		return rc;
	}

	return SUCCESS;
}

// Disconnect from card and release context
int CCardReport::CardDisconnect()
{
	int rc = SUCCESS;

	if(hCard != 0xFFFFFFFF)
	{
		rc = SCardDisconnect(hCard,SCARD_LEAVE_CARD);
		hCard = 0xFFFFFFFF;
	}
	if(hContext != 0xFFFFFFFF)
	{
		rc = SCardReleaseContext(hContext);
		hContext = 0xFFFFFFFF;
	}

	return rc;
}

// Send a select command to card using SCardICLASSTransmit
// to get Serial Number, Configuration Bytes, and Application Issuer
int CCardReport::CardSelect(unsigned char ucSelectP1, unsigned char ucSelectP2,
			   unsigned char ucDataByte, unsigned char** ppucReceive,unsigned long* pulReceiveLen)
{
	int rc = SUCCESS;
	int x=0;

	unsigned char ucSend[32] = {0};
	unsigned char* pucReceive = *ppucReceive;

	unsigned long ulSendLen=sizeof(ucSend);

	x=0;
	// create select transmit buffer
	ucSend[x++]=0x80;
	ucSend[x++]=0xA6;
	ucSend[x++]=ucSelectP1;
	ucSend[x++]=ucSelectP2;

	// if multipage is used
	// copy pagenumber and length to sendbuffer
	if(ucSelectP1 == 0x01)
	{
		ucSend[x++]=0x01;
		ucSend[x++]=ucDataByte;
	}
	ucSend[x++]=0x08; //(unsigned char)*pulReceiveLen;

	ulSendLen=x;

	rc = SCardCLICCTransmit(hCard,ucSend,ulSendLen,pucReceive,pulReceiveLen);
	if(rc != SCARD_S_SUCCESS)
	{
		MessageBox("Error at SCardCLICCTransmit(...)",NULL,MB_OK);

		return rc;
	}
	if(*(pucReceive+*pulReceiveLen-2)!=0x90)
		return UNSUCCESSFUL;


	return rc;
}

// Display Data
int CCardReport::ShowData(int iType,unsigned char* pucData)
{
	int rc = SUCCESS;
	int i=0;
	char szText[64];

	// 0x04 == Serial Number
	if(iType==0x04)
	{
		memset(szText,0x00,sizeof(szText));
		for(i=0;i<8;i++)
			sprintf(szText,"%s%02X ",szText,pucData[i]);
		this->m_SerialNumber.Format("%s",szText);
	}

	// 0x08 == Configuration Block
	if(iType==0x08)
	{
		memset(szText,0x00,sizeof(szText));

		this->m_ApplicationLimit.Format("%02X",pucData[0]);
		this->m_ApplicationOTPArea.Format("%02X %02X",pucData[1], pucData[2]);
		this->m_BlockWriteLock.Format("%02X",pucData[3]);
		this->m_ChipConfig.Format("%02X",pucData[4]);
		
		// B5 of Configuration Block is used to distinguish between 
		// (2KS or 8x2KS) and 16KS
		switch(pucData[5])
		{
		case 0x1F: 
			// check b4 of config byte to distinguish
			// between 2KS and 8x2KS
			switch((pucData[4] & 0x10) >> 4)
			{
			case 1:
				if(((pucData[7] & 0x18) >> 3) == 0x01)
				{ // K
					this->m_MemoryConfig.Format("%02X (2K Card)",pucData[5]);
				}
				else
				{ // KS
					this->m_MemoryConfig.Format("%02X (2KS Card)",pucData[5]);
				}
				this->m_NextPage.EnableWindow(FALSE);
				break;
			case 0:
				if(((pucData[7] & 0x18) >> 3) == 0x01)
				{ // K
					this->m_MemoryConfig.Format("%02X (8x2K Card)",pucData[5]);
				}
				else
				{ // KS
					this->m_MemoryConfig.Format("%02X (8x2KS Card)",pucData[5]);
				}

				this->m_NextPage.EnableWindow(TRUE);
				break;
			}
			break;
		case 0x9F:
			if(((pucData[7] & 0x18) >> 3) == 0x01)
			{ // K
				this->m_MemoryConfig.Format("%02X (16K Card)",pucData[5]);
			}
			else
				this->m_MemoryConfig.Format("%02X (16KS Card)",pucData[5]);
			this->m_NextPage.EnableWindow(FALSE);
			break;
		case 0xBF:
		case 0x7F:

			switch((pucData[4] & 0x10) >> 4)
			{
			case 1:
				if(((pucData[7] & 0x18) >> 3) == 0x01)
				{ // K
					this->m_MemoryConfig.Format("%02X (32K(1x16) Card)",pucData[5]);
				}
				else
				{ // KS
					this->m_MemoryConfig.Format("%02X (32KS(1x16) Card)",pucData[5]);
				}
				this->m_NextPage.EnableWindow(FALSE);
				break;
			case 0:
				if(((pucData[7] & 0x18) >> 3) == 0x01)
				{ // K
					this->m_MemoryConfig.Format("%02X (32K(8x2) Card)",pucData[5]);
				}
				else
				{ // KS
					this->m_MemoryConfig.Format("%02X (32KS(8x2) Card)",pucData[5]);
				}

				this->m_NextPage.EnableWindow(TRUE);
				break;
			}

			break;
		}


		this->m_Eas.Format("%02X",pucData[6]);
		this->m_Fuses.Format("%02X",pucData[7]);
	}

	// 0x0C == Application Issuer
	if(iType==0x0C)
	{
		memset(szText,0x00,sizeof(szText));
		for(i=0;i<8;i++)
			sprintf(szText,"%s%02X ",szText,pucData[i]);
		this->m_ApplicationIssuer.Format("%s",szText);
	}

	this->m_StaticPage.Format("Page %d",ucCurPageNumber);

	return rc;
}

void CCardReport::OnNextPage() 
{
	if(ucCurPageNumber < 7)
	{
		Show(ucCurPageNumber+1);
		this->m_PrevPage.EnableWindow(TRUE);
		if(ucCurPageNumber == 7)
			this->m_NextPage.EnableWindow(FALSE);
	}
	else
		MessageBox("No more pages available","CardReport",MB_ICONSTOP|MB_OK);
	
	UpdateData(FALSE);
}

void CCardReport::OnPrevPage() 
{
	if(ucCurPageNumber > 0)
	{
		Show(ucCurPageNumber-1);
		this->m_NextPage.EnableWindow(TRUE);
		if(ucCurPageNumber == 0)
			this->m_PrevPage.EnableWindow(FALSE);
	}
	else
		MessageBox("No more pages available","CardReport",MB_ICONSTOP|MB_OK);
	
	UpdateData(FALSE);	
}

void CCardReport::OnDetail() 
{
	int rc;

	char szText[128];

	unsigned long ulAddress;
	unsigned long ulLen;

	unsigned char ucData[2048];
	unsigned char* pucData=ucData;
	unsigned long ulDataLen=sizeof(ucData);

	//unsigned char ucKeyToLoad[8];
	unsigned long ulKeyLen=8;
	unsigned char* pucKeyToLoad;

	unsigned long ulKeyNoLen=0;
	unsigned char* pucKeyNo;

	unsigned char ucKeyStruct;

	CKeyInputDlg ckid(NULL,ucCurPageNumber);
	CDetailDlg cdd;
	
	// get Application data and show it with cdd

	// connect
	rc = CardConnect();
	if(rc != SUCCESS)
	{
		MessageBox("Unable to connect to the card",NULL,MB_ICONSTOP|MB_OK);
		rc = UNSUCCESSFUL;
		goto OnDetailExit;
	}

	// Select Page
	rc = CardSelect(0x01,0x04,ucCurPageNumber,&pucData,&ulDataLen);
	if(rc != SUCCESS)
	{
		ulDataLen=sizeof(ucData);
		rc = CardSelect(0x00,0x04,ucCurPageNumber,&pucData,&ulDataLen);
		if(rc != SUCCESS)
		{
			sprintf(szText,"Unable to select page number %d",ucCurPageNumber);
			MessageBox(szText,NULL,MB_ICONSTOP|MB_OK);
			rc = UNSUCCESSFUL;
			goto OnDetailExit;
		}
	}

	// Show Key Input Dialog
	if((ckid.DoModal())==IDCANCEL)
	{
		goto OnDetailExit;
	}

	rc = GetByteData(ckid.m_KeyNo,&pucKeyNo,&ulKeyNoLen);
	if(rc != SUCCESS)
	{
		MessageBox("Invalid Keynumber",NULL,MB_ICONSTOP|MB_OK);
		rc = UNSUCCESSFUL;
		goto OnDetailExit;
	}

	// get input value, convert from cstring to bytearray
	rc = GetByteData(ckid.m_Key,&pucKeyToLoad,&ulKeyLen);
	if(rc != SUCCESS)
	{
		if(rc == GBD_EMPTY_KEY)
		{
			goto OnDetailSkipLoadKey;
		}
		else
		{
			MessageBox("Invalid Input",NULL,MB_ICONSTOP|MB_OK);
			rc = UNSUCCESSFUL;
			goto OnDetailExit;
		}
	}

	// Load Key 
	if(pucKeyNo[0] == 0x20)
		ucKeyStruct=0x20;
	else
		ucKeyStruct=0x00;

	rc = CardLoadKey(pucKeyToLoad,ulKeyLen,pucKeyNo[0],ucKeyStruct);
	if(rc != SUCCESS)
	{
		MessageBox("Load Key failed",NULL,MB_ICONSTOP|MB_OK);
		rc = UNSUCCESSFUL;
		goto OnDetailExit;
	}

OnDetailSkipLoadKey:

	// authenticate with kiamc stored in readers eeprom
	rc = CardAuthenticate(ckid.m_KeyType,pucKeyNo[0]);
	if(rc != SUCCESS)
	{
		MessageBox("Authentication failed",NULL,MB_ICONSTOP|MB_OK);
		rc = UNSUCCESSFUL;
		goto OnDetailExit;
	}
	
	// if keytype = 0x00 use Application 0 area
	// if keytype = 0x01 use Application 1 area
	switch(ckid.m_KeyType)
	{
	case 0: 
		// length(in bytes) = (application limit block - start block)
		ulAddress=APPLICATION_START_ADDRESS;
		switch(ucConfigBlock[5])
		{
		case 0x1F:
			ulLen=(this->ucConfigBlock[0]-APPLICATION_START_ADDRESS-1);
			if(ulAddress > 0x20 || ulAddress + ulLen > 0x20)
			{
				sprintf(szText,"Invalid Application Limit Byte. 0x%02X",ucConfigBlock[0]);
				MessageBox(szText,NULL,MB_ICONINFORMATION|MB_OK);
				goto OnDetailExit;
			}
			break;
		case 0x9F:
			ulLen=(this->ucConfigBlock[0]-APPLICATION_START_ADDRESS+1);
			if(ulAddress > 0x100 || ulAddress + ulLen > 0x100)
			{
				sprintf(szText,"Invalid Application Limit Byte. 0x%02X",ucConfigBlock[0]);
				MessageBox(szText,NULL,MB_ICONINFORMATION|MB_OK);
				goto OnDetailExit;
			}
			break;
		}
		break;
	case 1:
		// length(in bytes) = (application limit block - start block)
		ulAddress=this->ucConfigBlock[0]+1;
		switch(ucConfigBlock[5])
		{
		case 0x1F:
			ulLen=(0x1F-ulAddress+1);
			if(ulAddress > 0x20 || ulAddress + ulLen > 0x20)
			{
				sprintf(szText,"Invalid Application Limit Byte. 0x%02X",ucConfigBlock[0]);
				MessageBox(szText,NULL,MB_ICONINFORMATION|MB_OK);
				goto OnDetailExit;
			}
			break;
		case 0x9F:
			ulLen=(0xFF-ulAddress+1);
			if(ulAddress > 0x100 || ulAddress + ulLen > 0x100)
			{
				sprintf(szText,"Invalid Application Limit Byte. 0x%02X",ucConfigBlock[0]);
				MessageBox(szText,NULL,MB_ICONINFORMATION|MB_OK);
				goto OnDetailExit;
			}
			break;
		}
		break;
	}

	ulLen *= 8;
	 
	if(ulLen <= 0)
	{
		sprintf(szText,"No Application 2 Area found\r\nApplication Limit Byte. 0x%02X",ucConfigBlock[0]);
		MessageBox(szText,NULL,MB_ICONINFORMATION|MB_OK);
		goto OnDetailExit;
	}

	ulDataLen=sizeof(ucData);
	rc = CardRead(ulAddress,ulLen,ucData,&ulDataLen);
	if(rc != SUCCESS)
	{
		rc = UNSUCCESSFUL;
		goto OnDetailExit;
	}

	cdd.SetApp(ucData,ulDataLen,ulAddress);
	
	rc = CardDisconnect();
	if(rc != SUCCESS)
	{
		rc = UNSUCCESSFUL;
		goto OnDetailExit;
	}

	hCard=0xFFFFFFFF;

	// show DetailDlg
	cdd.DoModal();

OnDetailExit:

	if(hCard != 0xFFFFFFFF)
		CardDisconnect();

}

int CCardReport::CardAuthenticate(unsigned char ucKeyType,unsigned char ucKeyNumber)
{
	int rc = SUCCESS;

	unsigned char ucSend[16];
	unsigned char ucReceive[32];

	unsigned long ulSendLen=sizeof(ucSend);
	unsigned long ulReceiveLen=sizeof(ucReceive);

	// copy send command (authenticate kd with stored kiamc)
	memcpy(ucSend,"\x80\x88",2);
	ucSend[2]=ucKeyType;
	ucSend[3]=ucKeyNumber;
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

int CCardReport::CardRead(unsigned long ulAddress,unsigned long ulLen, unsigned char* pucData,unsigned long* pulDataLen)
{
	int rc = SUCCESS;

	int x=0;
	int y=0;

	unsigned char ucSend[16];

	unsigned long ulSendLen=sizeof(ucSend);

	unsigned long ulDataLen=*pulDataLen;
	unsigned long ulReceived=0;

	memset(pucData,0x00,*pulDataLen);

	do
	{
		x=0;

		ucSend[x++]=0x80; // cla	
		ucSend[x++]=0xB0; // ins read
		ucSend[x++]=0x00;
		ucSend[x++]=(unsigned char)ulAddress+(y/8); // y/8 do get blocknumber
		if(ulLen < 32)
			ucSend[x++]=(unsigned char)ulLen; // size in bytes
		else
			ucSend[x++]=32;

		ulSendLen=x;

		*pulDataLen=ulDataLen;
		rc = SCardCLICCTransmit(hCard,ucSend,ulSendLen,pucData+y,pulDataLen);
		if(rc != SCARD_S_SUCCESS)
		{
			// error
			//sprintf(szTemp,"Error at SCardCLICCTransmit(..)\r\n",szTemp);
			MessageBox("Error at SCardCLICCTransmit() Errorcode: (0x\x08)",NULL,MB_OK);
		}

		ulReceived+=(*pulDataLen-2);

		y=y+(*pulDataLen-2);

		if(ulLen >= 32)
			ulLen -= 32;
		else
			ulLen=0;

	} while(ulLen > 0);

	*pulDataLen=ulReceived;

	return rc;
}

int CCardReport::CardLoadKey(unsigned char* pucKey,unsigned long ulKeyLen, unsigned char ucKeyNumber, unsigned char ucKeyStruct)
{
	int rc = SUCCESS;

	unsigned char ucSend[32];
	unsigned char ucReceive[32];

	unsigned long ulSendLen=sizeof(ucSend);
	unsigned long ulReceiveLen=sizeof(ucReceive);

	ulSendLen=0;
	// copy send command (authenticate kd with stored kiamc)
	ucSend[ulSendLen++]=0x80;
	ucSend[ulSendLen++]=0x82;
	ucSend[ulSendLen++]=ucKeyStruct; // 0x00 or 0x20  right now
	ucSend[ulSendLen++]=ucKeyNumber; // 0x20 or 0xF0  right now
	ucSend[ulSendLen++]=0x08;
	memcpy(ucSend+ulSendLen,pucKey,ulKeyLen);
	ulSendLen+=ulKeyLen;

	rc = SCardCLICCTransmit(hCard,ucSend,ulSendLen,ucReceive,&ulReceiveLen);
	if(rc != SCARD_S_SUCCESS)
	{
		// error
		//sprintf(szTemp,"Error at SCardCLICCTransmit(..)\r\n",szTemp);
		MessageBox("Error at SCardCLICCTransmit() Errorcode: (0x\x08)",NULL,MB_OK);
	}
	else
	{
		rc = UNSUCCESSFUL;
		if(ulReceiveLen >= 2)
			if(ucReceive[ulReceiveLen-2] == 0x90 && ucReceive[ulReceiveLen-1] == 0x00)
			{
				// load key passed
				rc = SUCCESS;
			}
	}

	return rc;
}

// get data from CString, store it in unsigned char buffer and get length
int CCardReport::GetByteData(CString from, unsigned char** to,unsigned long* len)
{
	int rc = GBD_UNSUCCESSFUL;
	int length=0;
	int i=0;
	int value=0;
	unsigned char* temp;

	UpdateData(TRUE);
	length = (int)from.GetLength();

	if(length == 0)
	{
		rc = GBD_EMPTY_KEY;
		goto EXIT;
	}

	// check length to ensure valid BYTE input (hex), ensure a multiple of 8 bytes
	if(length % 2 == 1 || length <= 0) // invalid length
	{
		rc = GBD_INVALID_LENGTH;
		goto EXIT;
	}
	

	*to = (unsigned char*)malloc(sizeof(unsigned char)*length/2);
	temp=*to;

	for(i=0;i<length;i++)
	{
		char ch = from.GetAt(i);

		if(ch<='9' && ch>='0')
		{
			ch = ch - 0x30; // get real value
		}
		else
			switch(ch)
			{
				case 'A':
				case 'a': ch=10; break;
				case 'B':
				case 'b': ch=11; break;
				case 'C':
				case 'c': ch=12; break;
				case 'D':
				case 'd': ch=13; break;
				case 'E':
				case 'e': ch=14; break;
				case 'F':
				case 'f': ch=15; break;
				default:
					MessageBox("Invalid value in Input",NULL,MB_OK);
					goto EXIT;
			}
		if(i%2==0)
		{
			value=ch;
		}
		else
			value=value*16+ch;
		
		if(i%2==1)
		{
			temp[i/2]=value;
			value=0;
		}
	}
	rc = GBD_SUCCESS;
	*len=length/2;
	

EXIT:
	return rc;
}

void CCardReport::OnNextpage() 
{
	if(ucCurPageNumber < 7)
	{
		Show(ucCurPageNumber+1);
		this->m_PrevPage.EnableWindow(TRUE);
		if(ucCurPageNumber == 7)
			this->m_NextPage.EnableWindow(FALSE);
	}
	else
		MessageBox("No more pages available","CardReport",MB_ICONSTOP|MB_OK);
	
	UpdateData(FALSE);	
}

void CCardReport::OnPrevpage() 
{
	if(ucCurPageNumber > 0)
	{
		Show(ucCurPageNumber-1);
		this->m_NextPage.EnableWindow(TRUE);
		if(ucCurPageNumber == 0)
			this->m_PrevPage.EnableWindow(FALSE);
	}
	else
		MessageBox("No more pages available","CardReport",MB_ICONSTOP|MB_OK);
	
	UpdateData(FALSE);		
}
