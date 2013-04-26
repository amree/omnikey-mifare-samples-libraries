// ReadMemoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadMemory.h"
#include "ReadMemoryDlg.h"
#include "SelectTypeDlg.h"
#include "InsertPinDlg.h"
#include "WriteDataDlg.h"
#include "winscard.h"
#include "scard2w.h"
#include "scard3w.h"
#include "scardi2c.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Global variables
SCARDCONTEXT hContext;
SCARDHANDLE hCard=NULL;
DWORD dwActiveProtocol;
char szReaders[10][100];
char mszReaders[1024];
DWORD dwLength = sizeof(mszReaders);
OKERR errorcode;
bool cardistwo=false;
bool cardisthree=false;
bool cardisi2c=false;
int list=0;
int ulOffset=0;
int maxlength=256;
int changed=1;
char selreader[100];
char oldreader[100];
BYTE pbData[500];
BYTE data[500];
// end of global vars

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadMemoryDlg dialog

CReadMemoryDlg::CReadMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadMemoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadMemoryDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadMemoryDlg)
	DDX_Control(pDX, IDC_RICHEDIT1, m_richedit);
	DDX_Control(pDX, IDC_WRITE, m_write);
	DDX_Control(pDX, IDC_PRESENTPIN, m_presentpin);
	DDX_Control(pDX, IDC_Readers, m_readerlist);
	DDX_Control(pDX, IDOK, m_okbutton);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReadMemoryDlg, CDialog)
	//{{AFX_MSG_MAP(CReadMemoryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PRESENTPIN, OnPresentpin)
	ON_BN_CLICKED(IDC_WRITE, OnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadMemoryDlg message handlers

BOOL CReadMemoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// Get Readernames and Context before showing the Dialog

		if(SCARD_S_SUCCESS==(SCardEstablishContext(SCARD_SCOPE_USER,NULL,NULL,&hContext)))
		{
			// SCardEstablishContext successfull
			if(SCARD_S_SUCCESS==(SCardListReaders(hContext,NULL,mszReaders,&dwLength)))
			{
				// SCardListReaders successfull

				// separate readernames
				if (dwLength > 0) // \0\0
				{
					DWORD i;
					DWORD z=0;
					DWORD j=0;

					for (i=0;i<dwLength;i++)
					{
						if (mszReaders[i] == '\0')
				        {
							szReaders [j] [z] = mszReaders[i];
							z=0;
							j++;
						}
						else
						{
							szReaders [j] [z] = mszReaders[i];
							z++;
						}
					}

					for(DWORD k=0;k<j-1;k++)
					{
						// insert readernames into listbox
						CString tempstring(szReaders[k]);

						m_readerlist.AddString(tempstring);
						m_readerlist.SetCurSel(0);
									
						// enable ReadMemory button if more than 0 readers found
						m_okbutton.EnableWindow(true);
						UpdateData(false);
					}
					if(j<=1)
					{
						// if no readers found put errormessage to list and
						// disable readmemory button
						m_okbutton.EnableWindow(false);
						m_readerlist.AddString("no reader found");
					}
				}
			}

			// Create a font with this parameters
			// This parameters are spezifing the TrueType font "Courier"

			CFont font;
			
			int nHeight=0;
			int nWidth=0;
			int nEscapement=0;
			int nOrientation=0;
			int nWeight=400;
			BYTE bItalic=0;
			BYTE bUnderline=0;
			BYTE cStrikeOut=0;
			BYTE nCharSet=0;
			BYTE nOutPrecision=1;
			BYTE nClipPrecision=2;
			BYTE nQuality=1;
			BYTE nPitchAndFamily=49;
			CString name="Courier";

			font.CreateFont(nHeight,nWidth,nEscapement,nOrientation,nWeight,bItalic,bUnderline,
							cStrikeOut,nCharSet,nOutPrecision,nClipPrecision,nQuality,
							nPitchAndFamily,name);

			// set font to richedit (memory output field)
			m_richedit.SetFont(&font);
		}
			
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReadMemoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReadMemoryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReadMemoryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CReadMemoryDlg::OnOK()
{
	// clear field
	m_richedit.SetWindowText("");
	UpdateData(false);
	UpdateWindow();
	int rc=100;

	// if more than 0 readers are availiable
	if(m_readerlist.GetCount()>0)
	{
		// get current selected Reader from readerlist and copy it´s name into selreader
		m_readerlist.GetText(m_readerlist.GetCurSel(),selreader);

		// compare current selected reader with selected reader before
		if(strcmp(oldreader,selreader)==0)
		{
			// if identical do nothing
		}
		else
		{
			// else set hCard to NULL
			hCard=NULL;
			changed=1;
			list=0;
		}
		
		m_readerlist.GetText(m_readerlist.GetCurSel(),oldreader);

		if(changed==1)
		{
			// connect to card
			rc=ConnectToCard();
			list=0;
		}
		else
		{
			// if already connected set returncode (rc) to zero
			rc=0;
			list=0;
		}
		if(rc==0)
		{
			// ReadData if connect was successfull
			int x=0;
			ulOffset=0;
			while((rc==0)&&(x<maxlength/256))
			{
				rc=ReadData();
				if(rc==0)
				{
					ShowData(pbData,x*16);
					x++;
					ulOffset=x*256;
				}
				else
				{
					x=maxlength/256;
					ulOffset=0;
				}
			}
			if(maxlength<256)
			{
				rc=ReadData();
				if(rc==0)
				{
					ShowData(pbData,x*16);
				}
				else
				{
					ulOffset=0;
				}
			}
			if(rc!=0)
			{
				// Error at reading data
				m_richedit.SetSel(-1,-1);
				if(rc==1) m_richedit.SetWindowText("SmartCard has been removed\nReinsert card and try again");
				else m_richedit.SetWindowText("Error at reading data\nReinsert card and try again");
				m_presentpin.EnableWindow(false);
				m_write.EnableWindow(false);
				UpdateData(false);
				changed=1;;
				list=0;
				if(rc==1) OnOK();
			}
		}
		else
		{	
			// Error at Connecting
			m_richedit.SetSel(-1,-1);
			m_richedit.ReplaceSel("Unable to connect to card\nReinsert card and try again");
			UpdateData(false);
			list=0;
			hCard=NULL;
		}
	}	
	else
	{
		// Error at SCardEstablishContext or Listreaders
		// MessageBox("Error at SCardEstablishContext",NULL,MB_OK);
	}
}

void CReadMemoryDlg::errorfunk()
{
	// Errorhandling
	if(errorcode!=OKERR_OK)
	{
		if(errorcode==OKERR_PW_WRONG)
		{   // Erroroutput if false PIN was entered
			MessageBox("The presented PIN is wrong",NULL,MB_OK);
		}
		else
		{
			if(errorcode==OKERR_PW_LOCKED)
			{   // Erroroutput if false PIN was entered to often
				MessageBox("The PIN has been presented several times wrong\nand is therefore locked.\nUsually use some administrator tool to unblock it",NULL,MB_OK);
			}
			else
			{
				if(errorcode==OKERR_PW_TOO_SHORT)
				{	// Erroroutput if entered PIN was too short
					MessageBox("The lenght of the PIN was too short",NULL,MB_OK);
				}
				else
				{	// Erroroutput all other Errors
					char msg[50];
					char bufferx[20];		

					// put ErrorCode to a MessageBox
					strcpy(msg,"Error code: 0x");
					// convert errorcode from int to a string
					_itoa(errorcode,bufferx,16);
					strcat(msg,bufferx);
					strcat(msg,"\nSee ok.h for details");
					MessageBox(msg,NULL,MB_OK);
					list=0;
				}
			}
		}
	}
	else
	{
//		Operation successfull
	}
}

void CReadMemoryDlg::OnPresentpin()
{
	// Create Dialog to input PIN
	InsertPinDlg myinspin;

	// Set "CardType": set a maximum length for PIN-inputfield,
	// 2W cards have 3 Bytes for PIN
	// 3W cards have 2 Bytes for PIN
	myinspin.setCardType(cardistwo);

	// show Dialog
	if(myinspin.DoModal()==IDOK)
	{
		char pin[8];
		int laenge;
		byte bpin[3];

		// get PIN from other Dialog
		myinspin.getPin(&pin[0],&laenge);

		int i=0;
		int j=0;
		int sum=0;

		// Convert PIN from 4 or 6 chars to 2 or 3 bytes

		while(i<laenge)
		{
			switch(pin[i])
			{
				case 'F':	j=15;break;
				case 'E':	j=14;break;
				case 'D':	j=13;break;
				case 'C':	j=12;break;
				case 'B':	j=11;break;
				case 'A':	j=10;break;
				case 'f':	j=15;break;
				case 'e':	j=14;break;
				case 'd':	j=13;break;
				case 'c':	j=12;break;
				case 'b':	j=11;break;
				case 'a':	j=10;break;
				case '9':	j=9;break;
				case '8':	j=8;break;
				case '7':	j=7;break;
				case '6':	j=6;break;
				case '5':	j=5;break;
				case '4':	j=4;break;
				case '3':	j=3;break;
				case '2':	j=2;break;
				case '1':	j=1;break;
				case '0':	j=0;break;
			}

			if(i%2==0)
			{
				j=j*16;
			}
			sum=sum+j;
			i++;
			if((i%2==0)&&(i!=0))
			{
				bpin[i/2-1]=sum;
				sum=0;
			}
		}
		bpin[i/2]='\0';

		// If Card is 2W
		if(cardistwo)
		{
			errorcode=SCard2WBPPresentPIN(hCard,3,&bpin[0]);
		}
		else
		// If Card is 3W
		if(cardisthree)
		{
			errorcode=SCard3WBPPresentPIN(hCard,2,&bpin[0]);
		}
		if(errorcode==OKERR_OK)
		{
			// if PIN is OK enable WRITE MEMORY BUTTON
			m_write.EnableWindow(true);
			m_presentpin.EnableWindow(false);
			m_write.SetFocus();
		}
		else
		{
			// PIN not OK
			// Errorhandling
			if(errorcode==OKERR_SCARD__W_REMOVED_CARD)
			{
				m_richedit.SetWindowText("SmartCard has been removed\nReinsert and try again");
				changed=1;
			}
			else
			{
				errorfunk();
			}
			// Disable WRITE MEMORY BUTTON
			m_write.EnableWindow(false);
		}

	}
}

void CReadMemoryDlg::OnCancel()
{
	// Disconnect from card if connected
	if(hCard!=NULL) SCardDisconnect(hCard,SCARD_LEAVE_CARD);

	CDialog::OnCancel();
}

void CReadMemoryDlg::OnWrite()
{
	char data[300];
	int laenge=0;
	int offset;

	// Create Dialog to enter DATA and OFFSET to write
	WriteDataDlg mywritedata;
	
	// Show Dialog
	if(mywritedata.DoModal()==IDOK)
	{
		// Get DATA, LENGTH of DATA and OFFSET
		mywritedata.getData(&data[0],&laenge,&offset);

		// convert data from char du unsigned char (byte)
		byte databuf[300];
		int i=0;
		while(i<laenge)
		{
			databuf[i]=data[i];
			i++;
		}
		databuf[i]='\0';

		ulOffset=offset;
		// check if offset+laenge is smaller than 256
		if(offset+laenge>maxlength)
			MessageBox("Offset + Length of data is to big");
		else
		{	// if offset is ok
			// if card is 2W
			if(cardistwo)
			{
				errorcode=SCard2WBPWriteData(hCard,laenge,&databuf[0],offset);
			}
			else
			// if card is 3W
			if(cardisthree)
			{
				errorcode=SCard3WBPWriteData(hCard,laenge,&databuf[0],offset,false);
			}
			else
			if(cardisi2c)
			{
				errorcode=SCardI2CWriteData(hCard,&databuf[0],sizeof(databuf),offset,laenge);
			}
			// errorhandling
			if(errorcode==OKERR_OK)
			{
				// ReadMemory again after writing to update display
				CReadMemoryDlg::OnOK();
			}
			else
			// if card has been removed
			if(errorcode==OKERR_SCARD__W_REMOVED_CARD)
			{
				MessageBox("Card has been removed, reinsert and start again",NULL,MB_OK);
				m_richedit.SetWindowText("");
				hCard=NULL;
				m_presentpin.EnableWindow(false);
				m_write.EnableWindow(false);
				//CReadMemoryDlg::OnOK();
			}
			else
			if(errorcode=OKERR_COMMUNICATE)
			{
				MessageBox("General Communication Error,\nmaybe the bytes at entered offset are protected",NULL,MB_OK);
			}
			else
				errorfunk();
		}
	}
	else
	{
		//	MessageBox("No data will be written",NULL,MB_OK);
	}
}

int CReadMemoryDlg::ConnectToCard()
{
	int rc;
	ulOffset=0;
	m_write.EnableWindow(false);
	m_presentpin.EnableWindow(false);
	UpdateWindow();
	
	rc=SCardReconnect(hCard,SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0|SCARD_PROTOCOL_T1,SCARD_LEAVE_CARD,&dwActiveProtocol);
	if(rc!=SCARD_S_SUCCESS)
	{
		hCard=NULL;
		rc=SCardConnect(hContext,selreader,SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0|SCARD_PROTOCOL_T1,&hCard,&dwActiveProtocol);
	}
	if(SCARD_S_SUCCESS==rc)
	{
		// SCardConnect successfull
		changed=0;

		// Check type of card
		BYTE pbAttr[256];
		DWORD pcbAttrLen=255;

		// Send Request ATR to card
		rc=SCardGetAttrib(hCard,SCARD_ATTR_ATR_STRING,pbAttr,&pcbAttrLen);
		if(rc==SCARD_S_SUCCESS)
		{
			// ATR received
			// check ATR

			if(pbAttr[2]==0xa2)
			{
				// ICC is 2W card
				m_presentpin.EnableWindow(true);
				maxlength=256;
				cardistwo=true;
				cardisthree=false;
				cardisi2c=false;
				UpdateWindow();
				return 0;
			}
			else
			if((pbAttr[2]==0x92)||(pbAttr[2]==0x02))
			{
				// ICC is 3W card
				// ReadData from card 256 Bytes start at address 0
				m_presentpin.EnableWindow(true);
				maxlength=1024;
				cardistwo=false;
				cardisthree=true;
				cardisi2c=false;
				UpdateWindow();
				return 0;
			}
			else
			if(pbAttr[2]==0x49)
			{
				// ICC is I2C card
		
				cardistwo=false;
				cardisthree=false;
				cardisi2c=true;
				m_presentpin.EnableWindow(false);
				char typ[10];

				// Call Dialog to select the type
				SelectTypeDlg listtypes;

				if((listtypes.DoModal())==IDOK)
				{
					// get selected typ from dialog
					listtypes.getCurSelItem(typ);

					SCARD_I2C_CARD_PARAMETERS  CardParameters;
					SCARD_I2C_TYPE type;
					
					// check typ and set constant
					if(0==(strcmp(typ,"Default")))
					{ type=NO_PREDEFINED_CARD_PARAMETERS; maxlength=256; }
					if(0==(strcmp(typ,"ST14C02C")))
					{ type=ST14C02C; maxlength=256; }
					if(0==(strcmp(typ,"ST14C04C")))
					{ type=ST14C04C; maxlength=512; }
					if(0==(strcmp(typ,"ST14E32")))
					{ type=ST14E32; maxlength=4096; }
					if(0==(strcmp(typ,"M14C04")))
					{ type=M14C04; maxlength=512; }
					if(0==(strcmp(typ,"M14C16")))
					{ type=M14C16; maxlength=2048; }
					if(0==(strcmp(typ,"M14C32")))
					{ type=M14C32; maxlength=4096; }
					if(0==(strcmp(typ,"M14C64")))
					{ type=M14C64; maxlength=8192; }
					if(0==(strcmp(typ,"M14128")))
					{ type=M14128; maxlength=16384; }
					if(0==(strcmp(typ,"M14256")))
					{ type=M14256; maxlength=32768; }
					if(0==(strcmp(typ,"GFM2K")))
					{ type=GFM2K; maxlength=256; }
					if(0==(strcmp(typ,"GFM4K")))
					{ type=GFM4K; maxlength=512; }
					if(0==(strcmp(typ,"GFM32K")))
					{ type=GFM32K; maxlength=4096; }
					if(0==(strcmp(typ,"AT24C01A")))
					{ type=AT24C01A; maxlength=128; }
					if(0==(strcmp(typ,"AT24C02")))
					{ type=AT24C02; maxlength=256; }
					if(0==(strcmp(typ,"AT24C04")))
					{ type=AT24C04; maxlength=512; }
					if(0==(strcmp(typ,"AT24C08")))
					{ type=AT24C08; maxlength=1024; }
					if(0==(strcmp(typ,"AT24C16")))
					{ type=AT24C16; maxlength=2048; }
					if(0==(strcmp(typ,"AT24C164")))
					{ type=AT24C164; maxlength=2048; }
					if(0==(strcmp(typ,"AT24C32")))
					{ type=AT24C32; maxlength=4096; }
					if(0==(strcmp(typ,"AT24C64")))
					{ type=AT24C64; maxlength=8192; }
					if(0==(strcmp(typ,"AT24C128")))
					{ type=AT24C128; maxlength=16384; }
					if(0==(strcmp(typ,"AT24C256")))
					{ type=AT24C256; maxlength=32768; }
					if(0==(strcmp(typ,"AT24CS128")))
					{ type=AT24CS128; maxlength=16384; }
					if(0==(strcmp(typ,"AT24CS256")))
					{ type=AT24CS256; maxlength=32768; }
					if(0==(strcmp(typ,"AT24C512")))
					{ type=AT24C512; maxlength=64536; }

					// check if type==default
					if(type==NO_PREDEFINED_CARD_PARAMETERS)
					{
						// if type == default use CardParameters
						// set cardparameters (only usefull if type == NO_PREDEFINED_CARD_PARAMETERS
						CardParameters.ucNumberOfAddressBytes=1;
						CardParameters.ucPageSize=8;
						CardParameters.ulMemorySize=256;

						errorcode=SCardI2CInit(hCard,&CardParameters,type);
					}
					else
					{
						// if typ != default use NULL
						errorcode=SCardI2CInit(hCard,NULL,type);
					}
					// errorhandling
					errorfunk();
					if(errorcode==OKERR_OK)
					{
						// INIT successfull
						m_presentpin.EnableWindow(false);
						m_write.EnableWindow(true);
						return 0;

					}
				}
			}
		}
	}
	else
	{
		return 1;
	}
	return 1;
}

int CReadMemoryDlg::ReadData()
{
	int laenge=256;
	
	if(cardistwo)
	{
		laenge=256-ulOffset;
		// ReadData from card 256 Bytes start at address 0
		errorcode=SCard2WBPReadData(hCard,laenge,pbData,ulOffset);
		// errorhandling
		if(errorcode==OKERR_OK)
		{
			list=1; // if DataRead successfull set variable
			return 0;
		}
		else
		{
			list=0;
			ulOffset=0;
			if(errorcode==OKERR_SCARD__W_REMOVED_CARD)
			{
				changed=1;;
				return 1;
			}
			else
			{
				//errorfunk();
				changed=1;
				return 2;
			}
		}
	}
	else
	if(cardisthree)
	{
		errorcode=SCard3WBPReadData(hCard,laenge,pbData,ulOffset);
		// errorhandling
		if(errorcode==OKERR_OK)
		{
			list=1; // if DataRead successfull set variable
			return 0;
		}
		else
		{
			list=0;
			ulOffset=0;
			if(errorcode==OKERR_SCARD__W_REMOVED_CARD)
			{
				changed=1;;
				return 1;
			}
			else
			{
				//errorfunk();
				changed=1;;
				return 2;
			}
		}
	}
	else
	{
		if(maxlength<256) laenge=maxlength;
		errorcode=SCardI2CReadData(hCard,pbData,sizeof(pbData),ulOffset,laenge);
		// errorhandling
		if(errorcode==OKERR_OK)
		{
			list=1; // if DataRead successfull set variable
			return 0;
		}
		else
		{
			ulOffset=0;
			list=0;
			if(errorcode==OKERR_SCARD__W_REMOVED_CARD)
			{
				changed=1;
				return 1;
			}
			else
			{
				//errorfunk();
				changed=1;;
				return 2;
			}
		}
	}
}

void CReadMemoryDlg::ShowData(byte* showData,int rownumber)
{
	// if list == 1 parse data
	// list is set in ReadData if Data returned successfull from card
	for(int u=0;u<256;u++)
	{
		data[u]=showData[u];
	}

	int j;
	int ab=rownumber; // rowcount (0..15)
	// output to file only for tests

/*		
	FILE* fp;
	fp=fopen("test.dat","wb");
	for(int x=0;x<256;x++)
	{
		fwrite(&data[x],1,1,fp);
	}
	fclose(fp);
*/
	// parse data
	int r=256;
	if(maxlength<256) r=128;
	else r=256;
	for(int i=0;i<r;i++)
	{
		// parse data in rows and put them into richeditbox
		
		char databuffer[100];	

		// write offset 00x0
		// write x if its smaller than 10 (0-9)
		databuffer[0]=0x30;
		databuffer[1]=0x30;
		
		// set offset
		char buffer[5];
		itoa(ab,buffer,16);

		databuffer[2]=buffer[0];
		if((ab>15)&&(ab<256))
		{
			databuffer[1]=buffer[0];
			databuffer[2]=buffer[1];
		}
		if(ab>256)
		{
			databuffer[1]=buffer[0];
			databuffer[2]=buffer[1];
			databuffer[3]=buffer[2];
		}
		databuffer[3]=0x30;
		// UPPERCASE offset values
		switch(databuffer[2])
		{
			case 'a':	databuffer[2]='A';break;
			case 'b':	databuffer[2]='B';break;
			case 'c':	databuffer[2]='C';break;
			case 'd':	databuffer[2]='D';break;
			case 'e':	databuffer[2]='E';break;
			case 'f':	databuffer[2]='F';break;
		}
		switch(databuffer[1])
		{
			case 'a':	databuffer[2]='A';break;
			case 'b':	databuffer[2]='B';break;
			case 'c':	databuffer[2]='C';break;
			case 'd':	databuffer[2]='D';break;
			case 'e':	databuffer[2]='E';break;
			case 'f':	databuffer[2]='F';break;
		}
		switch(databuffer[3]) 		
		{
			case 'a':	databuffer[2]='A';break;
			case 'b':	databuffer[2]='B';break;
			case 'c':	databuffer[2]='C';break;
			case 'd':	databuffer[2]='D';break;
			case 'e':	databuffer[2]='E';break;
			case 'f':	databuffer[2]='F';break;
		}

		// write three blanks to separate offset from data
		databuffer[4]=0x20;
		databuffer[5]=0x20;
		databuffer[6]=0x20;

		// write 16 values in hexadecimal look
		for(j=0;j<48;j++)
		{
			char  buffer[2];				
			// convert from byte to string
			_itoa(data[i+j/3],buffer,16);			
				// convert from small letters to big letters
			switch(buffer[0])
			{
				case 'a':	buffer[0]='A';break;
				case 'b':	buffer[0]='B';break;
				case 'c':	buffer[0]='C';break;
				case 'd':	buffer[0]='D';break;
				case 'e':	buffer[0]='E';break;
				case 'f':	buffer[0]='F';break;
			}
			// if value < 16 write first 0 and then value
			if(data[i+j/3]<16)
			{
				databuffer[7+j]=0x30;
				databuffer[8+j]=buffer[0];
			}
			else
			{
				// else write value how it is
				switch(buffer[1])
				{
					case 'a':	buffer[1]='A';break;
					case 'b':	buffer[1]='B';break;
					case 'c':	buffer[1]='C';break;
					case 'd':	buffer[1]='D';break;
					case 'e':	buffer[1]='E';break;
					case 'f':	buffer[1]='F';break;
				}
				databuffer[7+j]=buffer[0];
				databuffer[8+j]=buffer[1];
			}
			// write blank to separate values
			databuffer[9+j]=0x20;					
			// increase j
			j=j+2;
		}
		int k=0;
		// write two blanks
		databuffer[55]=0x20;
		databuffer[56]=0x20;
		// write 16 values how they are
		int bl=57;
		for(k=0;k<16;k++)
		{
			// check for line feed
			if(data[i+k]==0x0A)
			{
				databuffer[bl+k]=' ';
			}
			else
			// check for carriage return
			if(data[i+k]==0x0D)
			{
				databuffer[bl+k]=' ';
			}
			else
			// check for tab
			if(data[i+k]==0x09)
			{
				databuffer[bl+k]=' ';
			}
			else
			// check for backspace
			if(data[i+k]==0x08)
			{
				databuffer[bl+k]=' ';
			}
			else
			// don´t know what 0x0B is, but it makes a newline in richeditbox
			if(data[i+k]==0x0B)
			{
				databuffer[bl+k]=' ';
			}
			else
			// check for \0
			if(data[i+k]==0x00)
			{
				databuffer[bl+k]=' ';
			}
			else databuffer[bl+k]=data[i+k];
		}

		// increase i
		i=i+15;
		ab++;				
		
		// terminate string
		databuffer[73]='\n';
		databuffer[74]='\0';
		
		m_richedit.SetSel(-1,-1);
		m_richedit.ReplaceSel(databuffer);		

					
		UpdateData(false);
	}
}
