// CheckProtectedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CheckProtected.h"
#include "CheckProtectedDlg.h"
#include "winscard.h"
#include "scard3w.h"
#include "richedit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SCARDCONTEXT hContext; 
SCARDHANDLE hCard;
DWORD pdwActiveProtocol;
char szReaders[10][100];
char mszReaders[1024];
char selreader[100];
char oldreader[100];
DWORD dwLength = sizeof(mszReaders);
OKERR errorcode;

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
// CCheckProtectedDlg dialog

CCheckProtectedDlg::CCheckProtectedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckProtectedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckProtectedDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCheckProtectedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckProtectedDlg)
	DDX_Control(pDX, IDC_RICHEDIT1, m_richedit);
	DDX_Control(pDX, IDOK, m_okbutton);
	DDX_Control(pDX, IDC_READERLIST, m_readerlist);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckProtectedDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckProtectedDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckProtectedDlg message handlers

BOOL CCheckProtectedDlg::OnInitDialog()
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
			
			// seperate readernames
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
					// if no readers found put error to list and disable readmemory button
					m_okbutton.EnableWindow(false);
					m_readerlist.AddString("no reader found");
				}
			}
		}
	}

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

	m_richedit.SetFont(&font,TRUE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCheckProtectedDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCheckProtectedDlg::OnPaint() 
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
HCURSOR CCheckProtectedDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCheckProtectedDlg::OnOK() 
{
	// Empty window
	m_richedit.SetWindowText("");
	UpdateData(false);
	UpdateWindow();
	int rc;
	int breakvar=0;

	// if more than 0 readers are availiable
	if(m_readerlist.GetCount()>0)
	{
		m_readerlist.GetText(m_readerlist.GetCurSel(),selreader);
		// compare current selected reader with selected reader before
		if(strcmp(oldreader,selreader)==0)
		{
			// if identical to nothing
		}
		else
		{
			// else set hCard to NULL
			hCard=NULL;
		}
		
		m_readerlist.GetText(m_readerlist.GetCurSel(),oldreader);
		
		// if no cardhandle is availiable connect to card
		if(hCard==NULL) 
			rc=ConnectToCard();
		else 
			rc=0;
		// if connect was successfull or connection allready exists
		if(rc==0)
		{
			int ab=0;
			for(int i=0;i<1024;i++)
			{
				char databuffer[100];
				// set font
				CHARFORMAT cf;
				cf.dwEffects=0;
				cf.bCharSet=DEFAULT_CHARSET; 
				cf.crTextColor=0x00000000;
				cf.dwMask=CFM_COLOR; 
				cf.cbSize=sizeof(cf);

				databuffer[0]=0x30;
				databuffer[1]=0x30;

				// set offset
				char buffer[5];
				itoa(ab,buffer,16);

				databuffer[2]=buffer[0];
				if(ab>15) 
				{
					databuffer[1]=buffer[0];
					databuffer[2]=buffer[1];
				}
				databuffer[3]=0x30;
				// UPPERCASE offset values
				switch(databuffer[2]) 
				{
					case 'a':	databuffer[2]='A';
								break;
					case 'b':	databuffer[2]='B';
								break;
					case 'c':	databuffer[2]='C';
								break;
					case 'd':	databuffer[2]='D';
								break;
					case 'e':	databuffer[2]='E';
								break;
					case 'f':	databuffer[2]='F';
								break;
				}
				switch(databuffer[1]) 
				{
					case 'a':	databuffer[2]='A';
								break;
					case 'b':	databuffer[2]='B';
								break;
					case 'c':	databuffer[2]='C';
								break;
					case 'd':	databuffer[2]='D';
								break;
					case 'e':	databuffer[2]='E';
								break;
					case 'f':	databuffer[2]='F';
								break;
				}

				databuffer[4]=0x20;
				databuffer[5]=0x20;
				databuffer[6]=0x20;
				databuffer[7]='\0';
				cf.crTextColor=0x00000000; 
				m_richedit.SetSel(-1,-1);
				m_richedit.SetSelectionCharFormat(cf);
				// write offset to richedit box
				m_richedit.ReplaceSel(databuffer,FALSE);

				for(int j=0;j<32;j++)
				{
					BOOL fProtected;
					// check protectbit
					errorcode=SCard3WBPVerifyProtectBit(hCard,i+j/2,&fProtected);
					if(errorcode==OKERR_OK)
					{
						// if check was successfull
						breakvar=0;
						if(fProtected==TRUE)
						{
							// if byte is protected set font to courier with red color
							cf.dwEffects=0;
							cf.crTextColor=0x000000FF;
							cf.bCharSet=DEFAULT_CHARSET;
							cf.dwMask=CFM_COLOR; 
							cf.cbSize=sizeof(cf);
							m_richedit.SetSel(-1,-1);
							m_richedit.SetSelectionCharFormat(cf);
							// write a +
							m_richedit.ReplaceSel("+",FALSE);
						}
						else
						{
							// if byte isn´t prtected set font to courier with green color
							cf.dwEffects=0;
							cf.bCharSet=DEFAULT_CHARSET; 
							cf.crTextColor=0x0000AA44;
							cf.dwMask=CFM_COLOR; 
							cf.cbSize=sizeof(cf);
							m_richedit.SetSel(-1,-1);
							m_richedit.SetSelectionCharFormat(cf);
							// write a -
							m_richedit.ReplaceSel("-",FALSE);
						}
					}
					else
					{
						// if check wasn´t successfull 
						if(errorcode==OKERR_SCARD__W_REMOVED_CARD)
						{
							// if card has been removed
							// set cardhandle (hCard) to NULL
							// empty richedit box
							// set j to 32 and i to 1024 so loop stops
							// set breakvar to 1 to not write data to richedit any more
							hCard=NULL;
							m_richedit.SetWindowText("");
							UpdateData(false);
	
							UpdateWindow();
							//MessageBox("SmardCard has been removed,\nreinsert and start check again",NULL,MB_OK);
							j=32;
							i=1024;
							breakvar=1;
							OnOK();
						}
						else
						{
							char bufferx[50];
							char msg[100];
							strcpy(msg,"Error occured\nErrorcode: 0x");
							// convert errorcode from int to a string
							_itoa(errorcode,bufferx,16);
							strcat(msg,bufferx);
							strcat(msg,"\nSee ok.h for details");

							m_richedit.SetWindowText(msg);
							breakvar=1;
							j=32;
							i=1024;
						}
					}
					if(breakvar!=1)
					{
						// set sel to (-1,-1) to come to the end of the box
						// write a ' '
						// increase j
						m_richedit.SetSel(-1,-1);
						m_richedit.ReplaceSel(" ",FALSE);
						j++;
					}
				}
				// after writing 16 + / - write a \n to come to new row
				// increase i and ab
				m_richedit.SetSel(-1,-1);
				m_richedit.ReplaceSel("\n",FALSE);
				UpdateData(false);
				UpdateWindow();
				i=i+15;
				ab++;
			}
		}
		else
		// specify errorcodes from SCARD CONNECT
		if(rc==1)
		{
			// Message if ATR wasn´t OK
			m_richedit.SetWindowText("No SLE4418/SLE4428 card inserted !!");
			hCard=NULL;
			UpdateData(false);
			UpdateWindow();
		}
		else
		if(rc==2)
		{
			// Message if SCardConnect wasnt OK

			m_richedit.SetWindowText("Couldn´t connect to card");
			hCard=NULL;
			UpdateData(false);
			UpdateWindow();
		}
		else
		if(rc==3)
		{
			// Message if SCardGetAttr wasn successfull
			m_richedit.SetWindowText("Communication error, try again");
			hCard=NULL;
			UpdateData(false);
			UpdateWindow();
		}
	}
}

int CCheckProtectedDlg::ConnectToCard()
{
	if(SCARD_S_SUCCESS==(SCardConnect(hContext,selreader,SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0|SCARD_PROTOCOL_T1,&hCard,&pdwActiveProtocol)))
	{
		// SCardConnect successfull
	
		// Check typ of card
		BYTE pbAttr[256];
		DWORD pcbAttrLen=255;

		// Send Request ATR to card
		int rc=SCardGetAttrib(hCard,SCARD_ATTR_ATR_STRING,pbAttr,&pcbAttrLen); 
		if(rc==SCARD_S_SUCCESS)
		{
			// ATR received
			// check ATR
			if((pbAttr[2]==0x92)||(pbAttr[2]==0x02))
			{
				// ICC is 3W card
				return 0;
			}
			else
			{
				// ICC isn´t 3W card or has false ATR
				// Disconnect from card and return 1
				rc=SCardDisconnect(hCard,SCARD_LEAVE_CARD);
				hCard=NULL;
				return 1;
			}
		}
		// If an error occurs at SCardGetAttrib return 3
		return 3;
	}
	// if an error occurs at SCardConnect return 2
	return 2;
}

