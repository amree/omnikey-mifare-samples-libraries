// ContactlessDemoVCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ContactlessDemoVC.h"
#include "ContactlessDemoVCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CM_IOCTL_SET_RFID_CONTROL_FLAGS		SCARD_CTL_CODE(3213)

#define Card_Absent  0x00
#define Card_Present 0x01
#define Card_Changed 0x02
/*****************************************************************************/
/*			 ISO standard CS(CCCC****)
******************************************************************************/


/*****************************************************************************/
/*			 Chip Type CS(****SSSS)
******************************************************************************/

#define UNKNOWNCARD 	   0x0000
#define Mifare_Standard_1K 0x0001 
#define Mifare_Standard_4K 0x0002
#define Mifare_Ultra_light 0x0003
#define SLE55R_XXXX 	   0x0004 
#define SR176			   0x0006 
#define SRI_X4K 		   0x0007 
#define AT88RF020		   0x0008
#define AT88SC0204CRF	   0x0009
#define AT88SC0808CRF	   0x000A
#define AT88SC1616CRF	   0x000B
#define AT88SC3216CRF	   0x000C
#define AT88SC6416CRF	   0x000D
#define SRF55V10P		   0x000E
#define SRF55V02P		   0x000F
#define SRF55V10S		   0x0010
#define SRF55V02S		   0x0011 
#define TAG_IT			   0x0012
#define LRI512			   0x0013
#define ICODESLI		   0x0014
#define TEMPSENS		   0x0015
#define I_CODE1 		   0x0016 
#define ICLASS2KS		   0x0018
#define ICLASS16KS		   0x001A
#define ICLASS8x2KS 	   0x001C
#define ICLASS32KS_16_16   0x001D
#define ICLASS32KS_16_8x2  0x001E
#define ICLASS32KS_8x2_16  0x001F
#define ICLASS32KS_8x2_8x2 0x0020
#define LRI64              0x0021

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum
	{
		IDD = IDD_ABOUTBOX
	};
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
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
// CContactlessDemoVCDlg dialog

CContactlessDemoVCDlg::CContactlessDemoVCDlg(CWnd* pParent /*=NULL*/)
: CDialog(CContactlessDemoVCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContactlessDemoVCDlg)
	m_strReaderName = _T("");
	m_longBlockNr = 0;
	m_strAuthentKey = _T("");
	m_intAuthentMode = -1;
	m_intAccessOption = -1;
	m_strMifAuthentKeyNr = _T("");
	m_strDataRead = _T("");
	m_strDataToWrite = _T("");
	m_strIncrementValue = _T("");
	m_strDecrementValue = _T("");
	m_strOutPutList = _T("");
	m_dwNByteSend = 0;
	m_strByteSend = _T("");
	m_strByteReceive = _T("");
	m_dwNByteReceive = 0;
	m_intMifKeyEnOption = -1;
	m_strMifKeyNrToWrite = _T("");
	m_strMifKeyToWrite = _T("");
	m_strMifEnKeyNr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CContactlessDemoVCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContactlessDemoVCDlg)
	DDX_Control(pDX, IDC_LEDERROR, m_ledError);
	DDX_Control(pDX, IDC_LEDSUCCESS, m_ledSuccess);
	DDX_Control(pDX, IDC_ATRLIST, m_ctrAtrList);
	DDX_Control(pDX, IDC_CARDNAMELIST, m_ctrCardNameList);
	DDX_Control(pDX, IDC_UIDLIST, m_ctrUidList);
	DDX_Control(pDX, IDC_LISTOUTPUT, m_ctrOutput);
	DDX_Control(pDX, IDC_LISTREADER, m_ctrReaderName);
	DDX_LBString(pDX, IDC_LISTREADER, m_strReaderName);
	DDX_Text(pDX, IDC_AUTHENTBLOCKNR, m_longBlockNr);
	DDV_MinMaxLong(pDX, m_longBlockNr, 0, 255);
	DDX_Text(pDX, IDC_AUTHENTKEY, m_strAuthentKey);
	DDV_MaxChars(pDX, m_strAuthentKey, 12);
	DDX_Radio(pDX, IDC_MODEA, m_intAuthentMode);
	DDX_Radio(pDX, IDC_ACCESSOPTIONKEYNR, m_intAccessOption);
	DDX_CBString(pDX, IDC_MIFAUTHENTKEYNR, m_strMifAuthentKeyNr);
	DDX_Text(pDX, IDC_DATAREAD, m_strDataRead);
	DDX_Text(pDX, IDC_DATATOWRITE, m_strDataToWrite);
	DDV_MaxChars(pDX, m_strDataToWrite, 32);
	DDX_Text(pDX, IDC_INCREMENTVAL, m_strIncrementValue);
	DDV_MaxChars(pDX, m_strIncrementValue, 8);
	DDX_Text(pDX, IDC_DECREMENTVAL, m_strDecrementValue);
	DDV_MaxChars(pDX, m_strDecrementValue, 8);
	DDX_LBString(pDX, IDC_LISTOUTPUT, m_strOutPutList);
	DDX_Text(pDX, IDC_NBYTESEND, m_dwNByteSend);
	DDX_Text(pDX, IDC_BYTESEND, m_strByteSend);
	DDX_Text(pDX, IDC_BYTERECEIVED, m_strByteReceive);
	DDX_Text(pDX, IDC_NBYTERECEIVED, m_dwNByteReceive);
	DDX_Radio(pDX, IDC_MIFKEYTRAOPTIONPL, m_intMifKeyEnOption);
	DDX_CBString(pDX, IDC_MIFKEYTOREADERNR, m_strMifKeyNrToWrite);
	DDX_Text(pDX, IDC_MIFKEYTOREADER, m_strMifKeyToWrite);
	DDV_MaxChars(pDX, m_strMifKeyToWrite, 16);
	DDX_CBString(pDX, IDC_MIFENKEYNR, m_strMifEnKeyNr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CContactlessDemoVCDlg, CDialog)
//{{AFX_MSG_MAP(CContactlessDemoVCDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_LBN_SELCHANGE(IDC_LISTREADER, OnSelchangeListreader)
ON_BN_CLICKED(IDC_REFOUTPUTSC, OnRefoutputsc)
ON_BN_CLICKED(IDC_MIFAUTHENT, OnMifauthent)
ON_BN_CLICKED(IDC_READ, OnRead)
ON_BN_CLICKED(IDC_WRITE, OnWrite)
ON_BN_CLICKED(IDC_INCREMENT, OnIncrement)
ON_BN_CLICKED(IDC_DECREMENT, OnDecrement)
ON_BN_CLICKED(IDOK, OnExit)
ON_BN_CLICKED(IDC_ACCESSOPTIONKEYNR, OnAccessoptionkeynr)
ON_BN_CLICKED(IDC_ACCESSOPTIONKEY, OnAccessoptionkey)
ON_BN_CLICKED(IDC_TRANSMIT, OnTransmit)
ON_EN_CHANGE(IDC_BYTESEND, OnChangeBytesend)
ON_EN_CHANGE(IDC_AUTHENTKEY, OnChangeAuthentkey)
ON_EN_CHANGE(IDC_INCREMENTVAL, OnChangeIncrementval)
ON_EN_CHANGE(IDC_DECREMENTVAL, OnChangeDecrementval)
ON_EN_CHANGE(IDC_DATATOWRITE, OnChangeDatatowrite)
ON_BN_CLICKED(IDC_WRITEMIFKEY, OnWritemifkey)
ON_BN_CLICKED(IDC_MIFKEYTRAOPTIONSE, OnMifkeytraoptionse)
ON_BN_CLICKED(IDC_MIFKEYTRAOPTIONPL, OnMifkeytraoptionpl)
ON_BN_CLICKED(IDC_COMPLETEREAD, OnCompleteread)
ON_BN_CLICKED(IDC_COMPLETEWRITE, OnCompletewrite)
	ON_BN_CLICKED(IDC_MIFARE_EMU, OnMifareEmulatin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContactlessDemoVCDlg message handlers

BOOL CContactlessDemoVCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.
	DWORD i = 0, z = 0, j =0;
	CHAR mszReaders [1024];
	DWORD dwLength = sizeof(mszReaders);
	CHAR  szReader [10] [100];
	hCard = 0x00000000;
	hContext = 0x00000000;
	fCM5x21Selected = FALSE;
	GetDlgItem(IDC_MIFARE_EMU)->EnableWindow(FALSE);
	char str[80] = "";
	ulUIDBufLen = 12;
	fCardConnected = FALSE;
	memset(ucATR,sizeof(ucATR),0);
	ulATRLen = sizeof(ucATR);
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
	//	when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE); 	  // Set big icon
	SetIcon(m_hIcon, FALSE);	  // Set small icon
	
	// TODO: Add extra initialization here
	
	
	
	iMode = CLed::LED_DISABLED;
	iColor = CLed::LED_COLOR_RED;
	m_ledError.SetLed(iColor,iMode,CLed::LED_SQUARE);
	
	iMode = CLed::LED_DISABLED;
	iColor = CLed::LED_COLOR_GREEN;
	m_ledSuccess.SetLed(iColor,iMode,CLed::LED_SQUARE);
	
	
	
	
	
	
	m_ctrOutput.AddString("CM5x21 Demo Application, please see the help file of Synchronous API for detail functionality");
	
	
	SCard_Status = SCardEstablishContext(
		SCARD_SCOPE_USER,
		NULL,
		NULL,
		&hContext);
	
	
	
	if ( SCard_Status == SCARD_S_SUCCESS)
	{
		
		for (i=0;i<10;i++)
		{
			memset(&szReader[i][0],0x00,sizeof(&szReader[i][0]));
		}
		
		
		
		
		SCard_Status = SCardListReaders(hContext,
			NULL,
			mszReaders,
			&dwLength);
		
		
		if ( SCard_Status == SCARD_S_SUCCESS)
		{
			
			if (dwLength > 2) // \0\0
			{
				z=0;
				j=0;
				for (i=0;i<dwLength;i++)
				{
					if (mszReaders[i] == '\0')
					{
						szReader [j] [z] = mszReaders[i];
						z=0;
						j++;
					}
					else
					{
						szReader [j] [z] = mszReaders[i];
						z++;
					}
					
				}
			}
			
			
			for (j=0;j < 10;j++)
			{
				if (szReader[j] [0] != 0x00)
				{
					m_ctrReaderName.AddString(szReader[j]);
					
					if (strcmp( szReader[j],"OMNIKEY CardMan 5x21-CL 0")==0)
					{
						m_strReaderName = "OMNIKEY CardMan 5x21-CL 0";
						m_ctrOutput.AddString("Selected Reader is :");
						m_ctrOutput.AddString(m_strReaderName);
						fCM5x21Selected = TRUE;
					}
				}
			}
			
			
		}
		else
		{
			m_ctrOutput.AddString("Error in SCardListReaders, may be no reader available");
			TurnOnErrorLed();
			
			
		}
		
	}
	else
	{
		m_ctrOutput.AddString("Error in SCardEstablishContext");
		TurnOnErrorLed();
	}
	
	//If a card is present connect the card and show the ATR, UID, CardName
	//If not present start the thread to auto detection of the card
	
	UpdateData(FALSE);
	DisableAllFields();
	GetDlgItem(IDC_MIFAUTHENTKEYNR)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTHENTKEY)->EnableWindow(FALSE);
	
	m_strMifKeyNrToWrite = "00";
	m_intAuthentMode = 0;
	m_intAccessOption = 0;
	m_intMifKeyEnOption = 1;
	m_strMifEnKeyNr = "80";
	
	UpdateData(FALSE);
	
	TrackCard();
	ShowCursorOutScreen();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
   }
   
   void CContactlessDemoVCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
   
   void CContactlessDemoVCDlg::OnPaint()
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
   HCURSOR CContactlessDemoVCDlg::OnQueryDragIcon()
   {
	   return(HCURSOR) m_hIcon;
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void CContactlessDemoVCDlg::OnMifauthent()
   {
	   UCHAR ucMifareAuthMode;
	   UCHAR ucMifareKey[6] = {0};
	   ULONG ulMifareKeyLen = 0;
	   UCHAR ucMifareAccessType;
	   UCHAR ucMifareKeyNr;
	   
	   UpdateData(TRUE);
	   
	   if (m_intAuthentMode == 0)ucMifareAuthMode = MIFARE_AUTHENT1A;
	   else
		   if (m_intAuthentMode == 1)ucMifareAuthMode = MIFARE_AUTHENT1B;
		   else
		   {
			   TurnOnErrorLed();
			   m_ctrOutput.AddString("One Authentication mode must be selected");
			   goto EXIT;
		   }
		   
		   if (m_intAccessOption == 1)
		   {
			   ucMifareAccessType = MIFARE_KEY_INPUT;
			   if (m_strAuthentKey.GetLength() != 12)
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Key length must be 6");
				   goto EXIT;
			   }
			   CStringToUchar(m_strAuthentKey,ucMifareKey,&ulMifareKeyLen);
			   
		   }
		   else
			   if (m_intAccessOption == 0)
			   {
				   
				   CStringToUchar(m_strMifAuthentKeyNr,ucMifareKey,&ulMifareKeyLen);
				   ucMifareKeyNr = ucMifareKey[0];
				   ucMifareAccessType = MIFARE_KEYNR_INPUT;
				   
			   }
			   else
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("One Key option must be selected");
				   goto EXIT;
			   }
			   
			   
			   if (fCardConnected == TRUE)
			   {
				   if (m_strCardName == "MIFARE_ST1K" && m_longBlockNr >63)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The Block number is not valid");
					   goto EXIT;
				   }
				   
				   if (m_strCardName == "MIFARE_ST4K" && m_longBlockNr >255)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The Block number is not valid");
					   goto EXIT;
				   }
				   
				   GetSystemTime(&startTime);
				   
				   lErr = SCardCLMifareStdAuthent(hCard,m_longBlockNr,ucMifareAuthMode,ucMifareAccessType,ucMifareKeyNr,
					   ucMifareKey, ulMifareKeyLen);
				   GetSystemTime(&stopTime);
				   
				   if (lErr==NO_ERROR)
				   {
					   m_ctrOutput.AddString("Authentication has been done successfully");
					   ulAuthenticatedBlockNr= m_longBlockNr;
					   ShowTimeRequired();
				   }
				   else
				   {
					   m_ctrOutput.AddString("Error in Authentication, may be the key is not correct");
					   ShowErrorMessage(lErr);
				   }
				   
			   }
			   else
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("The Card is not connected");
			   }
			   
			   
EXIT:
			   ShowCursorOutScreen();
			   m_strAuthentKey.Empty();
			   
			   UpdateData(FALSE);
			   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void CContactlessDemoVCDlg::OnRead()
   {
	   UCHAR  ucMifareDataRead[16] ={0};
	   ULONG  ulMifareNumOfDataRead = 0;
	   char str[80] = "";
	   m_strDataRead.Empty();
	   
	   UpdateData(TRUE);
	   
	   if (fCardConnected == TRUE)
	   {
		   if (m_strCardName == "MIFARE_ST1K" || m_strCardName ==  "MIFARE_ST4K" )
		   {
			   
			   if (m_longBlockNr<128)
			   {
				   if (ulAuthenticatedBlockNr/4 != ((ULONG)m_longBlockNr)/4)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The selected block sector is not authenticated");
					   goto EXIT;
					   
				   }
				   
				   
			   }
			   else
			   {
				   if (ulAuthenticatedBlockNr /16 != ((ULONG)m_longBlockNr)/16)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The selected block sector is not authenticated");
					   goto EXIT;
					   
				   }
				   
			   }
			   
			   
			   
			   
		   }
		   
		   
		   GetSystemTime(&startTime);
		   
		   lErr = SCardCLMifareStdRead(hCard,m_longBlockNr,ucMifareDataRead,16,&ulMifareNumOfDataRead);
		   
		   GetSystemTime(&stopTime);
		   
		   if (lErr == NO_ERROR)
		   {
			   UcharToStr(ucMifareDataRead,ulMifareNumOfDataRead,str);
			   m_strDataRead = str;
			   m_ctrOutput.AddString("Reading has been done successfully");
			   ShowTimeRequired();
		   }
		   else
		   {
			   ShowErrorMessage(lErr);
		   }
		   
	   }
	   else
	   {
		   TurnOnErrorLed();
		   m_ctrOutput.AddString("The Card is not connected");
	   }
	   
EXIT:
	   ShowCursorOutScreen();
	   UpdateData(FALSE);
	   
	   
	   
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnWrite()
   {
	   
	   ULONG ulBufferLen = 0;
	   UCHAR ucDataToWrite[16]={0};
	   SectorTrailerDlg hSectorTrailerDlg;
	   m_strDataToWrite.Empty();
	   
	   UpdateData(TRUE);
	   
	   if (fCardConnected == TRUE)
	   {
		   
		   if (m_strCardName == "Mifare_Standard_1K" || m_strCardName ==  "Mifare_Standard_4K" )
		   {
			   
			   if (m_longBlockNr == 0)
			   {
				   
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Block 0 can not be written");
				   goto EXIT;
			   }
			   
			   
			   if (m_longBlockNr<128)
			   {
				   if (ulAuthenticatedBlockNr/4 != ((ULONG)m_longBlockNr)/4)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The selected block sector is not authenticated");
					   goto EXIT;
					   
				   }
				   
				   
			   }
			   else
			   {
				   if (ulAuthenticatedBlockNr /16 != ((ULONG)m_longBlockNr)/16)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The selected block sector is not authenticated");
					   goto EXIT;
					   
				   }
				   
			   }
			   
			   if (m_longBlockNr < 128)
			   {
				   if (((m_longBlockNr + 1)%4)==0)
				   {
					   if (hSectorTrailerDlg.DoModal()!= IDOK)
						   goto EXIT;
				   }
			   }
			   else
				   if (m_longBlockNr> 128)
				   {
					   if (((m_longBlockNr + 1)%16)==0)
					   {
						   if (hSectorTrailerDlg.DoModal()!= IDOK)
							   goto EXIT;
					   }
				   }
		   }
		   
		   
		   if (m_strCardName == "MIFARE_ULIT")
		   {
			   
			   if (m_longBlockNr == 0 || m_longBlockNr == 1)
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Block 0 and 1 can not be written");
				   goto EXIT;
			   }
			   
			   
			   if (m_longBlockNr == 2)
			   {
				   
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Block 2 internal and lock block, modifying lock block will lock the pages as Read Only, block 2 is  not allowed to write by this application ");
				   goto EXIT;
			   }
			   
			   if (m_longBlockNr == 3)
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Block 3 is OTP, block 3 is  not allowed to write by this application");
				   goto EXIT;
			   }
			   
			   
		   }
		   
		   CStringToUchar(m_strDataToWrite,ucDataToWrite,&ulBufferLen);
		   if (ulBufferLen != 16)
		   {
			   TurnOnErrorLed();
			   m_ctrOutput.AddString("The length of the data to be written must be 16");
			   goto EXIT;
		   }
		   
		   
		   GetSystemTime(&startTime);
		   
		   lErr = SCardCLMifareStdWrite(hCard, m_longBlockNr,ucDataToWrite,ulBufferLen);
		   GetSystemTime(&stopTime);
		   
		   if (lErr != NO_ERROR)
		   {
			   ShowErrorMessage(lErr);
		   }
		   else
		   {
			   m_ctrOutput.AddString("Writing has been done successfully");
			   ShowTimeRequired();
		   }
		   
	  }
	  else
	  {
		  TurnOnErrorLed();
		  m_ctrOutput.AddString("The Card is not connected");
	  }
	  
	  
EXIT:
	  ShowCursorOutScreen();
	  UpdateData(FALSE);
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnIncrement()
   {
	   UCHAR ucMifareIncrementValue[4] = {0};
	   ULONG ulMifareIncrementValueBufLen = 4;
	   
	   m_strIncrementValue.Empty();
	   
	   UpdateData(TRUE);
	   if (fCardConnected == TRUE)
	   {
		   
		   if (m_strCardName == "Mifare_Standard_1K" || m_strCardName ==  "Mifare_Standard_4K" )
		   {
			   
			   if (m_longBlockNr == 0)
			   {
				   
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Block 0 can not be incremented");
				   goto EXIT;
			   }
			   
			   
			   if (m_longBlockNr<128)
			   {
				   if (ulAuthenticatedBlockNr/4 != ((ULONG)m_longBlockNr)/4)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The selected block sector is not authenticated");
					   goto EXIT;
					   
				   }
				   
				   
			   }
			   else
			   {
				   if (ulAuthenticatedBlockNr /16 != ((ULONG)m_longBlockNr)/16)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The selected block sector is not authenticated");
					   goto EXIT;
					   
				   }
				   
			   }
			   
			   
			   if (m_longBlockNr < 128)
			   {
				   if (((m_longBlockNr + 1)%4)==0)
				   {
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("Trailer block cannot be incremented");
					   goto EXIT;
				   }
			   }
			   else
			   {
				   if (m_longBlockNr> 128)
					   if (((m_longBlockNr + 1)%16)==0)
					   {
						   TurnOnErrorLed();
						   m_ctrOutput.AddString("Trailer block cannot be incremented");
						   
					   }
			   }
			   
			   
			   
			   CStringToUchar(m_strIncrementValue,ucMifareIncrementValue,&ulMifareIncrementValueBufLen);
			   if (ulMifareIncrementValueBufLen != 4)
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("The length of the data by incremented must be 4");
				   goto EXIT;
			   }
			   GetSystemTime(&startTime);
			   
			   lErr = SCardCLMifareStdIncrementVal(hCard,m_longBlockNr,ucMifareIncrementValue,ulMifareIncrementValueBufLen);
			   GetSystemTime(&stopTime);
			   
			   if (lErr== NO_ERROR)
			   {
				   m_ctrOutput.AddString("Increment value has been done successfully");
				   ShowTimeRequired();
				   
			   }
			   else
			   {
				   ShowErrorMessage(lErr);
				   m_ctrOutput.AddString("May be the block is not a value block");
				   
			   }
		   }
		   else
		   {
			   TurnOnErrorLed();
			   m_ctrOutput.AddString("Except Mifare 1K or Mifare4K, other cards do not support Mifare std increment");
		   }
	   }
	   
	   else
	   {
		   TurnOnErrorLed();
		   m_ctrOutput.AddString("The Card is not connected");
	   }
EXIT:
	   ShowCursorOutScreen();
	   UpdateData(FALSE);
	   
	   
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnDecrement()
   {
	   
	   UCHAR ucMifareDecrementValue[4] = {0};
	   ULONG ulMifareDecrementValueBufLen = 4;
	   m_strDecrementValue.Empty();
	   
	   UpdateData(TRUE);
	   if (fCardConnected == TRUE)
	   {
		   
		   if (m_strCardName == "Mifare_Standard_1K" || m_strCardName ==  "Mifare_Standard_4K" )
		   {
			   
			   if (m_longBlockNr == 0)
			   {
				   
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Block 0 can not be decremented");
				   goto EXIT;
			   }
			   
			   
			   if (m_longBlockNr<128)
			   {
				   if (ulAuthenticatedBlockNr/4 != ((ULONG)m_longBlockNr)/4)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The selected block sector is not authenticated");
					   goto EXIT;
					   
				   }
				   
				   
			   }
			   else
			   {
				   if (ulAuthenticatedBlockNr /16 != ((ULONG)m_longBlockNr)/16)
				   {
					   
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("The selected block sector is not authenticated");
					   goto EXIT;
					   
				   }
				   
			   }
			   
			   
			   if (m_longBlockNr < 128)
			   {
				   if (((m_longBlockNr + 1)%4)==0)
				   {
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("Trailer block cannot be decremented");
					   goto EXIT;
				   }
			   }
			   else
			   {
				   if (m_longBlockNr> 128)
					   if (((m_longBlockNr + 1)%16)==0)
					   {
						   TurnOnErrorLed();
						   m_ctrOutput.AddString("Trailer block cannot be decremented");
						   
					   }
			   }
			   
			   
			   
			   CStringToUchar(m_strDecrementValue,ucMifareDecrementValue,&ulMifareDecrementValueBufLen);
			   if (ulMifareDecrementValueBufLen != 4)
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("The length of the data by decremented must be 4");
				   goto EXIT;
			   }
			   GetSystemTime(&startTime);
			   lErr = SCardCLMifareStdDecrementVal(hCard,m_longBlockNr,ucMifareDecrementValue,ulMifareDecrementValueBufLen);
			   GetSystemTime(&stopTime);
			   
			   
			   if (lErr == NO_ERROR)
			   {
				   m_ctrOutput.AddString("Decrement value has been done successfully");
				   ShowTimeRequired();
				   
			   }
			   else
			   {
				   ShowErrorMessage(lErr);
				   m_ctrOutput.AddString("May be the block is not a value block");
				   
			   }
			   
		   }
		   else
		   {
			   TurnOnErrorLed();
			   m_ctrOutput.AddString("Except Mifare 1K or Mifare4K, other cards do not support Mifare std decrement");
		   }
	   }
	   
	   else
	   {
		   TurnOnErrorLed();
		   m_ctrOutput.AddString("The Card is not connected");
	   }
	   
EXIT:
	   ShowCursorOutScreen();
	   UpdateData(FALSE);
	   
   }
   
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void CContactlessDemoVCDlg::TrackCard()
   {
	   
	   UpdateData(TRUE);
	   m_ctrAtrList.ResetContent();
	   m_ctrUidList.ResetContent();
	   m_ctrCardNameList.ResetContent();
	   
	   THREADSTRUCT *_param = new THREADSTRUCT;
	   _param->_this = this;
	   AfxBeginThread (StartCardThread, _param);
	   UpdateData(FALSE);
	   
	   
   }
   
   
   
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   UINT CContactlessDemoVCDlg::StartCardThread (LPVOID param)
   {
	   THREADSTRUCT* ts = (THREADSTRUCT*)param;
	   char str[80] = "";
	   UCHAR PresentCardState = Card_Absent ;
	   UCHAR PreviousCardState = Card_Absent ;
	   UCHAR hATR[64] = {0};
	   
	   //here is the time-consuming process which interacts with your dialog
	   
	   while (ts->_this->fCM5x21Selected == TRUE)
	   {
		   
		   ts->_this->sReaderState.szReader = strdup(ts->_this->m_strReaderName);
		   ts->_this->sReaderState.dwCurrentState = SCARD_STATE_EMPTY;
		   ts->_this->sReaderState.dwEventState = SCARD_STATE_EMPTY;
		   
		   //Look for the card state
		   SCardGetStatusChange(ts->_this->hContext,500,&(ts->_this->sReaderState),1);
		   if (ts->_this->sReaderState.dwEventState & SCARD_STATE_PRESENT)
		   {
			   PresentCardState = Card_Present ; //Card is present
			   
			   //Here find if the ATR has been changed	
			   memcpy(hATR,ts->_this->sReaderState.rgbAtr,ts->_this->sReaderState.cbAtr);
			   
			   if (memcmp(hATR,ts->_this->ucATR,64) != 0)
				   PresentCardState = Card_Changed;
			   
			   if (PreviousCardState == Card_Absent || PresentCardState == Card_Changed )
			   {
				   if (SCardConnect(ts->_this->hContext,ts->_this->m_strReaderName,
					   SCARD_SHARE_SHARED,SCARD_PROTOCOL_T0|SCARD_PROTOCOL_T1,&(ts->_this->hCard),&(ts->_this->dwActiveProtocols))
					   == SCARD_S_SUCCESS)
				   {
					   PresentCardState =  Card_Present;
					   ts->_this->fCardConnected = TRUE;
					   ts->_this->GetDlgItem(IDC_MIFARE_EMU)->EnableWindow(TRUE);
					   
				   }
				   else
				   {
					   ts->_this->fCardConnected = FALSE;
					   ts->_this->GetDlgItem(IDC_MIFARE_EMU)->EnableWindow(FALSE);
				   }
				   
			   }
			   
		   }
		   else
		   {
			   PresentCardState = Card_Absent; //Card is not present
			   ts->_this->m_ctrAtrList.ResetContent();
			   ts->_this->m_ctrUidList.ResetContent();
			   ts->_this->m_ctrCardNameList.ResetContent();
			   ts->_this->DisableAllFields();
			   ts->_this->ulAuthenticatedBlockNr = 257;
			   ts->_this->GetDlgItem(IDC_MIFARE_EMU)->EnableWindow(FALSE);
		   }
		   
		   
		   
		   if (PreviousCardState != PresentCardState)
		   {
			   if (PresentCardState == Card_Present)
			   {
				   ts->_this->m_ctrOutput.AddString("Card is present");
				   
				   memset(ts->_this->ucATR,0,64);
				   ts->_this->ulATRLen = ts->_this->sReaderState.cbAtr;
				   memcpy(ts->_this->ucATR,hATR,ts->_this->ulATRLen);
				   ts->_this->UcharToStr(ts->_this->ucATR,ts->_this->ulATRLen,str);
				   ts->_this->m_strATR = str;
				   ts->_this->m_ctrAtrList.AddString(ts->_this->m_strATR);


				   if (ts->_this->GiveCardName(ts->_this->ucATR,ts->_this->ulATRLen,str)==TRUE)
				   {
     				   ts->_this->m_ctrCardNameList.AddString(ts->_this->m_strCardName);
					   memset(ts->_this->ucUID,12,0);
					   ts->_this->ulnByteUID = 12;
					   if (SCardCLGetUID(ts->_this->hCard,ts->_this->ucUID,ts->_this->ulUIDBufLen, &ts->_this->ulnByteUID)==
						   NO_ERROR)
					   {
						   ts->_this->UcharToStr(ts->_this->ucUID,ts->_this->ulnByteUID,str);
						   ts->_this->m_strUID = str;
						   ts->_this->m_ctrUidList.AddString(ts->_this->m_strUID );
						   
						   
					   }
				   }
				   else
					   ts->_this->m_strUID = "";
				   
			   }
			   else if (PresentCardState == Card_Absent)
			   {
				   ts->_this->m_ctrOutput.AddString("Card is not present");
				   ts->_this->hCard = 0;
				   
				   
			   }
		   }
		   
		   
		   ts->_this->ShowCursorOutScreen();
		   PreviousCardState = PresentCardState;
		   Sleep(500);
		   
	   } //while loop
	   
	   
	   AfxEndThread(0);
	   return 1;
   }
   
   
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::ShowErrorMessage(long eError)
   {
	   CString strUnknownErr;
	   TurnOnErrorLed();
	   
	   switch (eError)
	   {
		   
	   case SCARD_E_CANCELLED:
		   m_ctrOutput.AddString( "SCARD_E_CANCELLED:\r\n   The action was canceled by an SCardCancel request.");
		   break;
		   
	   case SCARD_E_CANT_DISPOSE:
		   m_ctrOutput.AddString( "SCARD_E_CANT_DISPOSE:\r\n   The system could not dispose of the media in the requested manner.");
		   break;
		   
	   case SCARD_E_CARD_UNSUPPORTED:
		   m_ctrOutput.AddString( "SCARD_E_CARD_UNSUPPORTED:\r\n   The smart card does not meet minimal requirements for support.");
		   break;
		   
	   case SCARD_E_DUPLICATE_READER:
		   m_ctrOutput.AddString( "SCARD_E_DUPLICATE_READER:\r\n   The reader driver didn't produce a unique reader name.");
		   break;
		   
		   
	   case SCARD_E_INSUFFICIENT_BUFFER:
		   m_ctrOutput.AddString( "SCARD_E_INSUFFICIENT_BUFFER:\r\n   The data buffer for returned data is too small for the returned data.");
		   break;
		   
	   case SCARD_E_INVALID_ATR:
		   m_ctrOutput.AddString( "SCARD_E_INVALID_ATR:\r\n   An ATR string obtained from the registry is not a valid ATR string.");
		   break;
		   
		   
	   case SCARD_E_INVALID_HANDLE:
		   m_ctrOutput.AddString( "SCARD_E_INVALID_HANDLE:\r\n   The supplied handle was invalid.");
		   break;
		   
	   case SCARD_E_INVALID_PARAMETER:
		   m_ctrOutput.AddString( "SCARD_E_INVALID_PARAMETER:\r\n   One or more of the supplied parameters could not be properly interpreted.");
		   break;
		   
	   case SCARD_E_INVALID_TARGET:
		   m_ctrOutput.AddString( "SCARD_E_INVALID_TARGET:\r\n   Registry startup information is missing or invalid.");
		   break;
		   
	   case SCARD_E_INVALID_VALUE:
		   m_ctrOutput.AddString( "SCARD_E_INVALID_VALUE:\r\n   One or more of the supplied parameter values could not be properly interpreted.");
		   break;
		   
		   
	   case SCARD_E_NO_MEMORY:
		   m_ctrOutput.AddString( "SCARD_E_NO_MEMORY:\r\n   Not enough memory available to complete this command.");
		   break;
		   
		   
	   case SCARD_E_NO_SERVICE:
		   m_ctrOutput.AddString( "SCARD_E_NO_SERVICE:\r\n   The smart card resource manager is not running.");
		   break;
		   
	   case SCARD_E_NO_SMARTCARD:
		   m_ctrOutput.AddString( "SCARD_E_NO_SMARTCARD:\r\n   The operation requires a smart card,\r\n\tbut no smart card is currently in the device.");
		   break;
		   
		   
	   case SCARD_E_NOT_READY:
		   m_ctrOutput.AddString( "SCARD_E_NOT_READY:\r\n   The reader or card is not ready to accept commands.");
		   break;
		   
	   case SCARD_E_NOT_TRANSACTED:
		   m_ctrOutput.AddString( "SCARD_E_NOT_TRANSACTED:\r\n   An attempt was made to end a non-existent transaction.");
		   break;
		   
	   case SCARD_E_PCI_TOO_SMALL:
		   m_ctrOutput.AddString( "SCARD_E_PCI_TOO_SMALL:\r\n   The PCI receive buffer was too small.");
		   break;
		   
	   case SCARD_E_PROTO_MISMATCH:
		   m_ctrOutput.AddString( "SCARD_E_PROTO_MISMATCH:\r\n   The requested protocols are incompatible with the protocol\r\n\tcurrently in use with the card.");
		   break;
		   
	   case SCARD_E_READER_UNAVAILABLE:
		   m_ctrOutput.AddString( "SCARD_E_READER_UNAVAILABLE:\r\n   The specified reader is not currently available for use.");
		   break;
		   
	   case SCARD_E_READER_UNSUPPORTED:
		   m_ctrOutput.AddString( "SCARD_E_READER_UNSUPPORTED:\r\n   The reader driver does not meet minimal requirements for support.");
		   break;
		   
	   case SCARD_E_SERVICE_STOPPED:
		   m_ctrOutput.AddString( "SCARD_E_SERVICE_STOPPED:\r\n   The smart card resource manager has shut down.");
		   break;
		   
	   case SCARD_E_SHARING_VIOLATION:
		   m_ctrOutput.AddString( "SCARD_E_SHARING_VIOLATION:\r\n   The smart card cannot be accessed because of other outstanding connections.");
		   break;
		   
	   case SCARD_E_SYSTEM_CANCELLED:
		   m_ctrOutput.AddString( "SCARD_E_SYSTEM_CANCELLED:\r\n   The action was canceled by the system, presumably to log off or shut down.");
		   break;
		   
	   case SCARD_E_TIMEOUT:
		   m_ctrOutput.AddString( "SCARD_E_TIMEOUT:\r\n   The user-specified timeout value has expired.");
		   break;
		   
		   
	   case SCARD_E_UNKNOWN_CARD:
		   m_ctrOutput.AddString( "SCARD_E_UNKNOWN_CARD:\r\n   The specified smart card name is not recognized.");
		   break;
		   
	   case SCARD_E_UNKNOWN_READER:
		   m_ctrOutput.AddString( "SCARD_E_UNKNOWN_READER:\r\n   The specified reader name is not recognized.");
		   break;
		   
		   
	   case SCARD_F_COMM_ERROR:
		   m_ctrOutput.AddString( "SCARD_F_COMM_ERROR:\r\n   An internal communications error has been detected.");
		   break;
		   
	   case SCARD_F_INTERNAL_ERROR:
		   m_ctrOutput.AddString( "SCARD_F_INTERNAL_ERROR:\r\n   An internal consistency check failed.");
		   break;
		   
	   case SCARD_F_UNKNOWN_ERROR:
		   m_ctrOutput.AddString( "SCARD_F_UNKNOWN_ERROR:\r\n   An internal error has been detected, but the source is unknown.");
		   break;
		   
	   case SCARD_F_WAITED_TOO_LONG:
		   m_ctrOutput.AddString( "SCARD_F_WAITED_TOO_LONG:\r\n   An internal consistency timer has expired.");
		   break;
		   
	   case SCARD_P_SHUTDOWN:
		   m_ctrOutput.AddString( "SCARD_P_SHUTDOWN:\r\n   The operation has been aborted to allow the server application to exit.");
		   break;
		   
	   case SCARD_S_SUCCESS:
		   m_ctrOutput.AddString( "SCARD_S_SUCCESS:\r\n   No error was encountered.");
		   break;
		   
		   
	   case SCARD_W_REMOVED_CARD:
		   m_ctrOutput.AddString( "SCARD_W_REMOVED_CARD:\r\n   The smart card has been removed, so that further communication is not possible.");
		   break;
		   
	   case SCARD_W_RESET_CARD:
		   m_ctrOutput.AddString( "SCARD_W_RESET_CARD:\r\n   The smart card has been reset, so any shared state information is invalid.");
		   break;
		   
		   
	   case SCARD_W_UNPOWERED_CARD:
		   m_ctrOutput.AddString( "SCARD_W_UNPOWERED_CARD:\r\n   Power has been removed from the smart card, so that further communication is not possible.");
		   break;
		   
	   case SCARD_W_UNRESPONSIVE_CARD:
		   m_ctrOutput.AddString( "SCARD_W_UNRESPONSIVE_CARD:\r\n   The smart card is not responding to a reset.");
		   break;
		   
	   case SCARD_W_UNSUPPORTED_CARD:
		   m_ctrOutput.AddString( "SCARD_W_UNSUPPORTED_CARD:\r\n   The reader cannot communicate with the card, due to ATR string configuration conflicts.");
		   break;
		   
	   default:
		   strUnknownErr.Format("There was error in this operation, No error string available, ErrorCode = 0x%08X",eError);
		   m_ctrOutput.AddString(strUnknownErr);
		   break;
	  }
	  
	  iCount = m_ctrOutput. GetCount( );
	  for (int iUnsel = 0; iUnsel<iCount - 2;iUnsel++)
		  m_ctrOutput.SetSel(iUnsel,  FALSE );
	  
	  m_ctrOutput.SetSel(iCount - 1,  TRUE );
	  
	  
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void CContactlessDemoVCDlg::CStringToUchar(CString str, UCHAR *ucBuffer, ULONG *ulBufferLen)
   {
	   int Length = 0;
	   int DataLength = 0;
	   char cstr[] ="";
	   char strcstring[512] ="";
	   byte hexval=0x00;
	   int i = 0;
	   
	   Length = str.GetLength();
	   
	   for (i = 0; i<Length; i++)
		   strcstring[i] = str.GetAt(i);
	   
	   DataLength = Length / 2;
	   for (i = 0; i<DataLength; i++)
	   {
		   cstr[0] = strcstring[2*i];
		   cstr[1] = strcstring[2*i+1];
		   sscanf( cstr, "%02x", &hexval );
		   ucBuffer[i]=hexval;
		   
	   }
	   
	   *ulBufferLen = DataLength;
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::UcharToStr(UCHAR *ucDataBuffer, ULONG ulDataBufLen, char *str)
   {
	   ULONG i = 0;
	   char bytetochar[3] ="";
	   char Temp[1024] ="";
	   
	   
	   for (i=0;i<ulDataBufLen;i++)
	   {
		   _itoa(ucDataBuffer[i],bytetochar,16);
		   if (ucDataBuffer[i]<=0x0F)strcat(Temp,"0");
		   strcat(Temp,bytetochar);
	   }
	   
	   memcpy(str,Temp,ulDataBufLen*2);
	   str[ulDataBufLen*2] = 0;
	   
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnSelchangeListreader()
   {
	   
	   UpdateData(TRUE);
	   m_ctrOutput.AddString("Selected Reader is :");
	   m_ctrOutput.AddString(m_strReaderName);
	   fCM5x21Selected = TRUE; 
	   TrackCard();
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   
   BOOLEAN CContactlessDemoVCDlg::GiveCardName(UCHAR *ucATR, ULONG ATRLen, char *CardName)
   {
	   char strCardName[80] ="";
	   
	   
	   switch(CheckCLCardType(ucATR,ATRLen))
	   {
		   
	   case Mifare_Standard_1K:
		   m_strMifAuthentKeyNr = "00";
		   strcat(strCardName,"Mifare_Standard_1K");
		   EnableAllFields();
		   break;
		   
		   
	   case Mifare_Standard_4K:
		   m_strMifAuthentKeyNr = "00";
		   strcat(strCardName,"Mifare_Standard_4K");
		   EnableAllFields();
		   break;
		   
	   case Mifare_Ultra_light:
		   strcat(strCardName,"Mifare_Ultra_light");
		   GetDlgItem(IDC_AUTHENTBLOCKNR)->EnableWindow(TRUE);
		   GetDlgItem(IDC_READ)->EnableWindow(TRUE);
		   GetDlgItem(IDC_DATAREAD)->EnableWindow(TRUE);
		   GetDlgItem(IDC_WRITE)->EnableWindow(TRUE);
		   GetDlgItem(IDC_DATATOWRITE)->EnableWindow(TRUE);
		   GetDlgItem(IDC_COMPLETEREAD)->EnableWindow(TRUE);
		   GetDlgItem(IDC_COMPLETEWRITE)->EnableWindow(TRUE);
		   
		   
		   break;
		   
	   case SLE55R_XXXX:
		   strcat(strCardName,"SLE55R_XXXX");
		   break;
		   
	   case SR176:
		   strcat(strCardName,"SR176");
		   break;
		   
		   
	   case SRI_X4K:
		   strcat(strCardName,"SRI_X4K");
		   break;
		   
	   case AT88RF020:
		   strcat(strCardName,"AT88RF020");
		   break;
		   
	   case AT88SC0204CRF:
		   strcat(strCardName,"AT88SC0204CRF");
		   break;
		   
	   case AT88SC0808CRF:
		   strcat(strCardName,"AT88SC0808CRF");
		   break;
		   
	   case AT88SC1616CRF:
		   strcat(strCardName,"AT88SC1616CRF");
		   break;
		   
	   case AT88SC3216CRF:
		   strcat(strCardName,"AT88SC3216CRF");
		   break;
		   
	   case AT88SC6416CRF:
		   strcat(strCardName,"AT88SC6416CRF");
		   break;
		   
	   case SRF55V10P:
		   strcat(strCardName,"SRF55V10P");
		   break;
		   
	   case SRF55V02P:
		   strcat(strCardName,"SRF55V02P");
		   break;
		   
	   case SRF55V10S:
		   strcat(strCardName,"SRF55V10S");
		   break;
		   
	   case SRF55V02S:
		   strcat(strCardName,"SRF55V02S");
		   break;
		   
	   case TAG_IT:
		   strcat(strCardName,"TAG_IT");
		   break;
		   
	   case LRI512:
		   strcat(strCardName,"LRI512");
		   break;
		   
	   case LRI64:
		   strcat(strCardName,"LRI64");
		   break;
		   
	   case ICODESLI:
		   strcat(strCardName,"ICODESLI");
		   break;
		   
	   case TEMPSENS:
		   strcat(strCardName,"TEMPSENS");
		   break;
		   
	   case I_CODE1:
		   strcat(strCardName,"I_CODE1");
		   break;
		   
	   case ICLASS16KS:    
		   strcat(strCardName,"ICLASS 16KS");
		   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
		   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);
		   break;
		   
	   case ICLASS2KS:	  
		   strcat(strCardName,"ICLASS 2KS");
		   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
		   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);
		   break;
		   
	   case ICLASS8x2KS:	
		   strcat(strCardName,"ICLASS 8x2KS");
		   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
		   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);
		   break;
		   
		   
	   case ICLASS32KS_16_16:	
		   strcat(strCardName,"ICLASS32KS_16_16");
		   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
		   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);
		   break;
		   
		   
	   case ICLASS32KS_16_8x2:	
		   strcat(strCardName,"ICLASS32KS_16_8x2");
		   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
		   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);
		   break;
		   
	   case ICLASS32KS_8x2_16:	
		   strcat(strCardName,"ICLASS32KS_8x2_16");
		   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
		   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);
		   break;
		   
	   case ICLASS32KS_8x2_8x2:	
		   strcat(strCardName,"ICLASS32KS_8x2_8x2");
		   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
		   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);
		   break;
		   
		   
	   default:
		   strcat(strCardName,"Unknown Card");
		   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
		   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
		   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);
		   
		   
	   }
	   
	   
	   
	   
	   m_strCardName = strCardName;
	   return TRUE;
	   
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnRefoutputsc()
   {
	   m_ctrOutput.ResetContent();
	   m_ctrOutput.AddString("CardMan5x21 Demo Application Programming, please go through the developer's guide for detail");
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::ShowTimeRequired()
   {
	   char bytetochar[10]={'0'};
	   char strFortime[80]="";
	   
	   SystemTimeToFileTime(&startTime, &ftimetmp);
	   ulistartTime.LowPart=ftimetmp.dwLowDateTime;
	   ulistartTime.HighPart=ftimetmp.dwHighDateTime;
	   SystemTimeToFileTime(&stopTime, &ftimetmp);
	   ulistopTime.LowPart=ftimetmp.dwLowDateTime;
	   ulistopTime.HighPart=ftimetmp.dwHighDateTime;
	   ulirunTime.QuadPart=ulistopTime.QuadPart-ulistartTime.QuadPart;
	   ftimetmp.dwHighDateTime=ulirunTime.HighPart;
	   ftimetmp.dwLowDateTime=ulirunTime.LowPart;
	   FileTimeToSystemTime(&ftimetmp, &runTime);
	   
	   
	   _itoa(runTime.wSecond,bytetochar,10);
	   if (runTime.wSecond<=9)strncat(strFortime,"0",19);
	   strncat(strFortime,bytetochar,19);
	   strncat(strFortime,":",19);
	   
	   _itoa((runTime.wMilliseconds/10),bytetochar,10);
	   if ((runTime.wMilliseconds/10)<=9)strncat(strFortime,"0",19);
	   strncat(strFortime,bytetochar,19);
	   
	   _itoa((runTime.wMilliseconds - (runTime.wMilliseconds/10)*10) ,bytetochar,10);
	   strncat(strFortime,bytetochar,19);
	   
	   m_ctrOutput.AddString("Currently executed operation took :  " +	CString(strFortime) + " Sec");
	   
	   startTime.wMilliseconds = 0;
	   startTime.wSecond = 0;
	   stopTime.wMilliseconds = 0;
	   stopTime.wSecond = 0;
	   runTime.wMilliseconds = 0;
	   runTime.wSecond = 0;
	   
	   iMode = CLed::LED_DISABLED;
	   iColor = CLed::LED_COLOR_RED;
	   m_ledError.SetLed(iColor,iMode,CLed::LED_SQUARE);
	   
	   iMode = CLed::LED_ON;
	   iColor = CLed::LED_COLOR_GREEN;
	   m_ledSuccess.SetLed(iColor,iMode,CLed::LED_SQUARE);
	   
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::DisableAllFields()
   {
	   
	   GetDlgItem(IDC_MIFAUTHENT)->EnableWindow(FALSE);
	   GetDlgItem(IDC_AUTHENTBLOCKNR)->EnableWindow(FALSE);
	   GetDlgItem(IDC_ACCESSOPTIONKEYNR)->EnableWindow(FALSE);
	   GetDlgItem(IDC_MIFAUTHENTKEYNR)->EnableWindow(FALSE);
	   GetDlgItem(IDC_ACCESSOPTIONKEY)->EnableWindow(FALSE);
	   GetDlgItem(IDC_AUTHENTKEY)->EnableWindow(FALSE);
	   GetDlgItem(IDC_MODEA)->EnableWindow(FALSE);
	   GetDlgItem(IDC_MODEB)->EnableWindow(FALSE);
	   GetDlgItem(IDC_READ)->EnableWindow(FALSE);
	   GetDlgItem(IDC_DATAREAD)->EnableWindow(FALSE);
	   GetDlgItem(IDC_WRITE)->EnableWindow(FALSE);
	   GetDlgItem(IDC_DATATOWRITE)->EnableWindow(FALSE);
	   GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
	   GetDlgItem(IDC_INCREMENTVAL)->EnableWindow(FALSE);
	   GetDlgItem(IDC_DECREMENT)->EnableWindow(FALSE);
	   GetDlgItem(IDC_DECREMENTVAL)->EnableWindow(FALSE);
	   GetDlgItem(IDC_TRANSMIT)->EnableWindow(FALSE);
	   GetDlgItem(IDC_BYTESEND)->EnableWindow(FALSE);
	   GetDlgItem(IDC_NBYTESEND)->EnableWindow(FALSE);
	   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(FALSE);
   	   GetDlgItem(IDC_COMPLETEREAD)->EnableWindow(FALSE);
	   GetDlgItem(IDC_COMPLETEWRITE)->EnableWindow(FALSE);
	   
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::EnableAllFields()
   {
	   
	   GetDlgItem(IDC_MIFAUTHENT)->EnableWindow(TRUE);
	   GetDlgItem(IDC_AUTHENTBLOCKNR)->EnableWindow(TRUE);
	   GetDlgItem(IDC_ACCESSOPTIONKEYNR)->EnableWindow(TRUE);
	   GetDlgItem(IDC_ACCESSOPTIONKEY)->EnableWindow(TRUE);
	   GetDlgItem(IDC_MIFAUTHENTKEYNR)->EnableWindow(TRUE);
	   GetDlgItem(IDC_MODEA)->EnableWindow(TRUE);
	   GetDlgItem(IDC_MODEB)->EnableWindow(TRUE);
	   GetDlgItem(IDC_READ)->EnableWindow(TRUE);
	   GetDlgItem(IDC_DATAREAD)->EnableWindow(TRUE);
	   GetDlgItem(IDC_WRITE)->EnableWindow(TRUE);
	   GetDlgItem(IDC_DATATOWRITE)->EnableWindow(TRUE);
	   GetDlgItem(IDC_INCREMENT)->EnableWindow(TRUE);
	   GetDlgItem(IDC_INCREMENTVAL)->EnableWindow(TRUE);
	   GetDlgItem(IDC_DECREMENT)->EnableWindow(TRUE);
	   GetDlgItem(IDC_DECREMENTVAL)->EnableWindow(TRUE);
	   GetDlgItem(IDC_COMPLETEREAD)->EnableWindow(TRUE);
	   GetDlgItem(IDC_COMPLETEWRITE)->EnableWindow(TRUE);
	   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
	   GetDlgItem(IDC_TRANSMIT)->EnableWindow(TRUE);
	   GetDlgItem(IDC_BYTESEND)->EnableWindow(TRUE);
	   GetDlgItem(IDC_NBYTESEND)->EnableWindow(TRUE);
	   GetDlgItem(IDC_NBYTERECEIVED)->EnableWindow(TRUE);


	   
	   
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnExit()
   {
	   
	   fCM5x21Selected = FALSE;
	   SCardDisconnect(hCard,SCARD_LEAVE_CARD );
	   SCardReleaseContext(hContext);
	   exit(0);
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::ShowCursorOutScreen()
   {
	   
	   int iCount = m_ctrOutput. GetCount( );
	   for (int iUnsel = 0; iUnsel<iCount - 1;iUnsel++)
		   m_ctrOutput.SetSel(iUnsel,  FALSE );
	   m_ctrOutput.SetSel(iCount - 1,  TRUE );
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::TurnOnErrorLed()
   {
	   
	   iMode = CLed::LED_ON;
	   iColor = CLed::LED_COLOR_RED;
	   m_ledError.SetLed(iColor,iMode,CLed::LED_SQUARE);
	   
	   iMode = CLed::LED_DISABLED;
	   iColor = CLed::LED_COLOR_RED;
	   m_ledSuccess.SetLed(iColor,iMode,CLed::LED_SQUARE);
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnAccessoptionkeynr()
   {
	   
	   UpdateData(TRUE);
	   m_strMifAuthentKeyNr ="00";
	   m_strAuthentKey = " ";
	   m_intAccessOption = 0 ;
	   GetDlgItem(IDC_MIFAUTHENTKEYNR)->EnableWindow(TRUE);
	   GetDlgItem(IDC_AUTHENTKEY)->EnableWindow(FALSE);
	   UpdateData(FALSE);
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnAccessoptionkey()
   {
	   UpdateData(TRUE);
	   m_strMifAuthentKeyNr ="";
	   m_intAccessOption = 1 ;
	   m_strAuthentKey = "FFFFFFFFFFFF";
	   GetDlgItem(IDC_MIFAUTHENTKEYNR)->EnableWindow(FALSE);
	   GetDlgItem(IDC_AUTHENTKEY)->EnableWindow(TRUE);
	   UpdateData(FALSE);
	   
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnTransmit()
   {
	   UCHAR ucByteSend[270] = {0};
	   UCHAR ucByteReceive[260] = {0};
	   ULONG ulnByteSend = 0;
	   DWORD dwRecvLength = 260;
	   char str[1024] = "";
	   SCARD_IO_REQUEST pioSendPci;
	   
	   
	   if (dwActiveProtocols == SCARD_PROTOCOL_T0)
	   {
		   pioSendPci.dwProtocol= SCARD_PCI_T0->dwProtocol;
		   pioSendPci.cbPciLength= SCARD_PCI_T0->cbPciLength;
	   }
	   else
		   if (dwActiveProtocols == SCARD_PROTOCOL_T1)
		   {
			   pioSendPci.dwProtocol= SCARD_PCI_T1->dwProtocol;
			   pioSendPci.cbPciLength= SCARD_PCI_T1->cbPciLength;
			   
		   }
		   
		   
		   UpdateData(TRUE);
		   
		   
		   CStringToUchar(m_strByteSend,ucByteSend,&ulnByteSend);
		   
		   if (ulnByteSend != m_dwNByteSend)
		   {
			   MessageBox(" Problem in length of Data send and number of bytes send");
			   TurnOnErrorLed();
			   goto EXIT;
		   }
		   
		   GetSystemTime(&startTime);
		   
		   
		   if(m_strCardName.Find("ICLASS") != -1)
		   {
			   
			   SCard_Status = SCardCLICCTransmit(hCard,ucByteSend,m_dwNByteSend,ucByteReceive,&dwRecvLength);
			   
			   
		   }
		   else
		   {
			   
			   SCard_Status = SCardTransmit (hCard,
				   &pioSendPci,
				   ucByteSend,
				   m_dwNByteSend,
				   NULL,
				   ucByteReceive,
				   &dwRecvLength);
		   }
		   
		   GetSystemTime(&stopTime);
		   
		   if (SCard_Status == 0)
		   {
			   m_ctrOutput.AddString("Transmission has been done succesfully");
			   m_dwNByteReceive = dwRecvLength;
			   UcharToStr(ucByteReceive,dwRecvLength,str);
			   m_strByteReceive = str;
			   ShowTimeRequired();
		   }
		   else
		   {
			   ShowErrorMessage(SCard_Status);
			   m_strByteReceive = "";
			   TurnOnErrorLed();
		   }
		   
		   
		   UpdateData(FALSE);
EXIT:
		   ;
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnChangeBytesend()
   {
	   UpdateData(TRUE);
	   if (CheckLetter(m_strByteSend)!= TRUE)
	   {
		   m_strByteSend.Remove(m_strByteSend.GetAt(m_strByteSend.GetLength()-1));
	   }
	   
	   m_dwNByteSend = m_strByteSend.GetLength()/2;
	   
	   UpdateData(FALSE);
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   BOOLEAN CContactlessDemoVCDlg::CheckLetter(CString String)
   {
	   int i = 0;
	   int k = 0;
	   for (i = 0;i<String.GetLength();i++)
	   {
		   if ((String.GetAt(i) >= '0' && String.GetAt(i) <= '9') ||(String.GetAt(i) >= 'A' && String.GetAt(i) <= 'F'))
			   k = 0;
		   else
		   {
			   
			   MessageBox("The values must be a hex value");
			   return FALSE;
		   }
	   }
	   return TRUE;
   }
   
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnChangeAuthentkey() 
   {
	   UpdateData(TRUE);
	   
	   if (CheckLetter(m_strAuthentKey)!= TRUE)
	   {
		   m_strAuthentKey.Remove(m_strAuthentKey.GetAt(m_strAuthentKey.GetLength()-1));
	   }
	   
	   UpdateData(FALSE);
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnChangeIncrementval() 
   {
	   UpdateData(TRUE);
	   
	   if (CheckLetter(m_strIncrementValue)!= TRUE)
	   {
		   m_strIncrementValue.Remove(m_strIncrementValue.GetAt(m_strIncrementValue.GetLength()-1));
	   }
	   
	   UpdateData(FALSE);
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnChangeDecrementval() 
   {
	   UpdateData(TRUE);
	   
	   if (CheckLetter(m_strDecrementValue)!= TRUE)
	   {
		   m_strDecrementValue.Remove(m_strDecrementValue.GetAt(m_strDecrementValue.GetLength()-1));
	   }
	   
	   UpdateData(FALSE);
   }
   
   void CContactlessDemoVCDlg::OnChangeDatatowrite() 
   {
	   UpdateData(TRUE);
	   if (CheckLetter(m_strDataToWrite)!= TRUE)
	   {
		   m_strDataToWrite.Remove(m_strDataToWrite.GetAt(m_strDataToWrite.GetLength()-1));
	   }
	   
	   UpdateData(FALSE);
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void CContactlessDemoVCDlg::OnWritemifkey() 
   {
	   UCHAR ucMifareKey[8] = {0};
	   ULONG ulMifareKeyLen = 0;
	   char Reader[80]=" ";
	   UCHAR ucKeyNr[1]={0};
	   ULONG ulKeyNrLen = 0;
	   ULONG ulEnKeyNr = 0;
	   BOOLEAN fSecuredTransmission = FALSE;
	   
	   
	   UpdateData(TRUE);
	   
	   if (m_intMifKeyEnOption == 0)
	   {
		   fSecuredTransmission = FALSE;
		   if (m_strMifKeyToWrite.GetLength() != 12)
		   {
			   m_ctrOutput.AddString("The Key must be of 6 bytes");
			   TurnOnErrorLed();
			   goto EXIT;
			   
			   
		   }
		   
		   
	   }
	   else
		   if (m_intMifKeyEnOption == 1)
		   {
			   fSecuredTransmission = TRUE;
			   if (m_strMifKeyToWrite.GetLength() != 16)
			   {
				   m_ctrOutput.AddString("The Key must be of 8 bytes");
				   TurnOnErrorLed();
				   goto EXIT;
				   
			   }
			   
			   CStringToUchar(m_strMifEnKeyNr,ucKeyNr,&ulKeyNrLen);
			   ulEnKeyNr = ucKeyNr[0];
			   
			   
		   }
		   else
		   {
			   m_ctrOutput.AddString("One transmission option must be selected");
			   TurnOnErrorLed();
			   goto EXIT;
			   
			   
		   }
		   
		   
		   CStringToUchar(m_strMifKeyToWrite,ucMifareKey,&ulMifareKeyLen);
		   
		   CStringToUchar(m_strMifKeyNrToWrite,ucKeyNr,&ulKeyNrLen);
		   ulMifKeyToReaderNr = ucKeyNr[0];
		   
		   if (fCM5x21Selected == TRUE)
		   {
			   
			   strcpy(Reader,(LPCTSTR) m_strReaderName);
			   
			   if (fCardConnected != TRUE)hCard = 0x00000000;
			   
			   GetSystemTime(&startTime);
			   
			   lErr = SCardCLWriteMifareKeyToReader(hCard,hContext,Reader,ulMifKeyToReaderNr,ulMifareKeyLen,
				   ucMifareKey,fSecuredTransmission,ulEnKeyNr);
			   
			   GetSystemTime(&stopTime);
			   
			   if (lErr == NO_ERROR)
			   {
				   
				   m_ctrOutput.AddString("The key has been written succesfully");
				   ShowTimeRequired();
				   
			   }
			   else
			   {
				   ShowErrorMessage(lErr);
			   }
		   }
		   else
		   {
			   
			   m_ctrOutput.AddString("For any operation one reader must be selected");
			   TurnOnErrorLed();
		   }
		   
EXIT:
		   ShowCursorOutScreen();
		   m_strMifKeyToWrite.Empty();
		   UpdateData(FALSE);
		   
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void CContactlessDemoVCDlg::OnMifkeytraoptionse() 
   {
	   UpdateData(TRUE); 
	   GetDlgItem(IDC_MIFENKEYNR)->EnableWindow(TRUE);
	   m_strMifEnKeyNr = "80";
	   m_intMifKeyEnOption = 1;
	   UpdateData(FALSE);
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   void CContactlessDemoVCDlg::OnMifkeytraoptionpl() 
   {
	   UpdateData(TRUE); 
	   GetDlgItem(IDC_MIFENKEYNR)->EnableWindow(FALSE);
	   m_intMifKeyEnOption = 0;
	   m_strMifEnKeyNr = " ";
	   UpdateData(FALSE);
	   
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ULONG CContactlessDemoVCDlg::CheckCLCardType(PUCHAR ATR, DWORD ATRLen)
   {
	   
	   UCHAR ucExpectedATR[20]={0x3B,0x8F,0x80,0x01,0x80,
		   0x4F,0x0C,0xA0,0x00,0x00,
		   0x03,0x06,0xFF,0x00,0xFF,
		   0x00,0x00,0x00,0x00,0xFF};
	   
	   
	   if (ATRLen == 17 && ATR[1] == 0x0F && ATR[2] == 0xFF) //old driver version
	   {
		   if (ATR[16] == 0x11)
			   return Mifare_Standard_1K;
		   else
			   if (ATR[16] == 0x21)
				   return Mifare_Standard_4K;
			   else
				   if (ATR[16] == 0x31)
					   return Mifare_Ultra_light;
				   else
					   if (ATR[16] == 0x93)
						   return ICLASS2KS;
					   else
						   if (ATR[16] == 0xA3)
							   return ICLASS16KS;
						   else
							   if (ATR[16] == 0xB3)
								   return ICLASS8x2KS;
							   else
								   return UNKNOWNCARD;
							   
							   
	   }
	   else
		   if (ATRLen == 20)				  //new driver ps/sc atr
		   {
			   memcpy(ucExpectedATR+12,ATR+12,3);
			   ucExpectedATR[19] = ATR[19];
			   
			   if (memcmp(ucExpectedATR,ATR,ATRLen) != 0)
				   return UNKNOWN_CARD;
			   else
			   {
				   return(ATR[13]<<8) | ATR[14];
				   
			   }
		   }
		   else
			   return UNKNOWN_CARD;
		   
		   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnCompleteread() 
   {
	   
	   UCHAR ucMifareAuthMode;
	   UCHAR ucMifareKey[6] = {0};
	   ULONG ulMifareKeyLen = 0;
	   UCHAR ucMifareAccessType;
	   UCHAR ucMifareKeyNr;
   	   UCHAR ucMifareDataRead[16] ={0};
	   ULONG ulMifareNumOfDataRead = 0;
	   ULONG ulMaximumblockNr = 64;
	   
	   UpdateData(TRUE);
	   
	   
	   if( strcmp("Mifare_Standard_4K",m_strCardName) == 0)
		   ulMaximumblockNr = 128;
	   
	   
	   GetSystemTime(&startTime);
	   
	   
	   if( strcmp("Mifare_Ultra_light",m_strCardName) == 0) 
	   {
		   
		   for(m_longBlockNr = 0; m_longBlockNr <16; m_longBlockNr+=4)
		   {
			   lErr = SCardCLMifareStdRead(hCard,m_longBlockNr,ucMifareDataRead,16,&ulMifareNumOfDataRead);
			   if(lErr != NO_ERROR)
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Error in reading");
				   goto EXIT;
				   
			   }
		   }
		   
		   
	   }
	   else //Mifare 1k or 4 k card
	   {
		   if (m_intAuthentMode == 0)ucMifareAuthMode = MIFARE_AUTHENT1A;
		   else
			   if (m_intAuthentMode == 1)ucMifareAuthMode = MIFARE_AUTHENT1B;
			   else
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("One Authentication mode must be selected");
				   goto EXIT;
			   }
			   
			   if (m_intAccessOption == 0)
			   {
				   
				   CStringToUchar(m_strMifAuthentKeyNr,ucMifareKey,&ulMifareKeyLen);
				   ucMifareKeyNr = ucMifareKey[0];
				   ucMifareAccessType = MIFARE_KEYNR_INPUT;
				   
			   }
			   else
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Here the key nr option is only implemented");
				   goto EXIT;
			   }
			   
			   
			   
			   for(m_longBlockNr = 0; m_longBlockNr <(LONG)ulMaximumblockNr; m_longBlockNr++)
			   {
				   
				   if((m_longBlockNr % 4) == 0x00) //authenticate only once for each sector
				   {
					   
					   lErr = SCardCLMifareStdAuthent(hCard,m_longBlockNr,ucMifareAuthMode,ucMifareAccessType,ucMifareKeyNr,
						   ucMifareKey, ulMifareKeyLen);
					   
					   if(lErr != NO_ERROR)
					   {
						   TurnOnErrorLed();
						   m_ctrOutput.AddString("Error in authentication");
						   goto EXIT;
						   
					   }
					   
					   
				   }
				   
				   //now read the block
				   
				   lErr = SCardCLMifareStdRead(hCard,m_longBlockNr,ucMifareDataRead,16,&ulMifareNumOfDataRead);
				   
				   if(lErr != NO_ERROR)
				   {
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("Error in reading");
					   goto EXIT;
					   
				   }
				   
			   }
			   
			   //if the card is Mifare 4k then read the rest 2K
			   if( strcmp("Mifare_Standard_4K",m_strCardName) == 0)
			   {
				   for(m_longBlockNr = ulMaximumblockNr; m_longBlockNr <256; m_longBlockNr++)
				   {
					   
					   if((m_longBlockNr % 16) == 0x00) //authenticate only once for each sector
					   {
						   
						   lErr = SCardCLMifareStdAuthent(hCard,m_longBlockNr,ucMifareAuthMode,ucMifareAccessType,ucMifareKeyNr,
							   ucMifareKey, ulMifareKeyLen);
						   
						   if(lErr != NO_ERROR)
						   {
							   TurnOnErrorLed();
							   m_ctrOutput.AddString("Error in authentication");
							   goto EXIT;
							   
						   }
						   
						   
					   }
					   
					   //now read the block
					   
					   lErr = SCardCLMifareStdRead(hCard,m_longBlockNr,ucMifareDataRead,16,&ulMifareNumOfDataRead);
					   
					   if(lErr != NO_ERROR)
					   {
						   TurnOnErrorLed();
						   m_ctrOutput.AddString("Error in reading");
						   goto EXIT;
						   
					   }
					   
				   }
				   
			   }
			   
			   
			   
			   
			   
			   
			   
			   
			   
	   }
	   
	   
	   GetSystemTime(&stopTime);
	   m_ctrOutput.AddString("Reading has been done successfully");
	   ShowTimeRequired();
	   m_longBlockNr--; 
EXIT:
	   UpdateData(FALSE);
	   
	   
	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   void CContactlessDemoVCDlg::OnCompletewrite() 
   {
	   UCHAR ucMifareAuthMode;
	   UCHAR ucMifareKey[6] = {0};
	   ULONG ulMifareKeyLen = 0;
	   UCHAR ucMifareAccessType;
	   UCHAR ucMifareKeyNr;
   	   UCHAR ucDataToWrite[16] ={0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0xFF,0x00};
	   ULONG ulBufferLen = 16;
	   ULONG ulMaximumblockNr = 64;
	   
	   UpdateData(TRUE);
	   
	   
	   if( strcmp("Mifare_Standard_4K",m_strCardName) == 0)
		   ulMaximumblockNr = 128;
	   
	   
	   GetSystemTime(&startTime);
	   
	   
	   if( strcmp("Mifare_Ultra_light",m_strCardName) == 0) 
	   {
		   
		   for(m_longBlockNr = 4; m_longBlockNr <16; m_longBlockNr+=4)
		   {
		   lErr = SCardCLMifareStdWrite(hCard, m_longBlockNr,ucDataToWrite,ulBufferLen);
			   if(lErr != NO_ERROR)
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Error in writing");
				   goto EXIT;
				   
			   }
		   }
		   
		   
	   }
	   else //Mifare 1k or 4 k card
	   {
		   if (m_intAuthentMode == 0)ucMifareAuthMode = MIFARE_AUTHENT1A;
		   else
			   if (m_intAuthentMode == 1)ucMifareAuthMode = MIFARE_AUTHENT1B;
			   else
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("One Authentication mode must be selected");
				   goto EXIT;
			   }
			   
			   if (m_intAccessOption == 0)
			   {
				   
				   CStringToUchar(m_strMifAuthentKeyNr,ucMifareKey,&ulMifareKeyLen);
				   ucMifareKeyNr = ucMifareKey[0];
				   ucMifareAccessType = MIFARE_KEYNR_INPUT;
				   
			   }
			   else
			   {
				   TurnOnErrorLed();
				   m_ctrOutput.AddString("Here the key nr option is only implemented");
				   goto EXIT;
			   }
			   
			   
			   
			   for(m_longBlockNr = 0; m_longBlockNr <(LONG)ulMaximumblockNr; m_longBlockNr++)
			   {
				   
				   if((m_longBlockNr % 4) == 0x00) //authenticate only once for each sector
				   {
					   
					   lErr = SCardCLMifareStdAuthent(hCard,m_longBlockNr,ucMifareAuthMode,ucMifareAccessType,ucMifareKeyNr,
						   ucMifareKey, ulMifareKeyLen);
					   
					   if(lErr != NO_ERROR)
					   {
						   TurnOnErrorLed();
						   m_ctrOutput.AddString("Error in authentication");
						   goto EXIT;
						   
					   }
					   
					   
				   }
				   
				   //now write the block

				   if( m_longBlockNr != 0) //do not write block 0
				   if(((m_longBlockNr+1)%4) != 0) //do not write sector trailer 
				   {
					lErr = SCardCLMifareStdWrite(hCard, m_longBlockNr,ucDataToWrite,ulBufferLen);
				   
				   if(lErr != NO_ERROR)
				   {
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("Error in writing");
					   goto EXIT;
					   
				   }
				   }
				   
			   }
			   
			   //if the card is Mifare 4k then write the rest 2K
			   if( strcmp("Mifare_Standard_4K",m_strCardName) == 0)
			   {
				   for(m_longBlockNr = ulMaximumblockNr; m_longBlockNr <256; m_longBlockNr++)
				   {
					   
					   if((m_longBlockNr % 16) == 0x00) //authenticate only once for each sector
					   {
						   
						   lErr = SCardCLMifareStdAuthent(hCard,m_longBlockNr,ucMifareAuthMode,ucMifareAccessType,ucMifareKeyNr,
							   ucMifareKey, ulMifareKeyLen);
						   
						   if(lErr != NO_ERROR)
						   {
							   TurnOnErrorLed();
							   m_ctrOutput.AddString("Error in authentication");
							   goto EXIT;
							   
						   }
						   
						   
					   }
					   
					   //now write the block
					   
				   if(((m_longBlockNr+1)%16) != 0) //do not write sector trailer
				   {
					lErr = SCardCLMifareStdWrite(hCard, m_longBlockNr,ucDataToWrite,ulBufferLen);
				   
				   if(lErr != NO_ERROR)
				   {
					   TurnOnErrorLed();
					   m_ctrOutput.AddString("Error in writing");
					   goto EXIT;
					   
				   }
				   }
					   
				   }
				   
			   }
	   }
	   
	   
	   GetSystemTime(&stopTime);
	   m_ctrOutput.AddString("Writing has been done successfully");
	   ShowTimeRequired();
	   m_longBlockNr--; 
	   
	   
EXIT:
	   UpdateData(FALSE);
	   
	   
	   	   
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CContactlessDemoVCDlg::OnMifareEmulatin() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
    BYTE  InBuffer[16];
    BYTE  OutBuffer[16];
	DWORD dwControlCode   = CM_IOCTL_SET_RFID_CONTROL_FLAGS;
    DWORD dwInBufferSize  = 8;
    DWORD dwOutBufferSize = 0;
	DWORD dwBytesReturned = 0;
	DWORD *Mask           = (DWORD *)InBuffer;
	DWORD *Value          = (DWORD *)InBuffer+1;
	
	CString	strButtonTitle;
	CString strDriverState;

	memset(InBuffer, 0x00, sizeof(InBuffer));
	memset(OutBuffer, 0x00, sizeof(OutBuffer));

	dwControlFlags = ~dwControlFlags;
	*Mask  = 0x00000004;
	*Value = dwControlFlags & *Mask;

	GetSystemTime(&startTime);

	lErr = SCardControl(hCard,
                        dwControlCode,
                        (LPCVOID)InBuffer,
                        dwInBufferSize,
                        (LPVOID)OutBuffer,                          // The reply from IFD -> driver -> res.manager
                        dwOutBufferSize,
                        &dwBytesReturned);

	GetSystemTime(&stopTime);

	if (lErr == SCARD_S_SUCCESS)
    {
		if (*Value == 0)
		{
			strDriverState.LoadString(IDS_MIFARE_EMU_OFF);
			strDriverState.MakeLower();
			strButtonTitle.LoadString(IDS_MIFARE_EMU_ON);
		}
		else
		{
			strDriverState.LoadString(IDS_MIFARE_EMU_ON);
			strDriverState.MakeLower();
			strButtonTitle.LoadString(IDS_MIFARE_EMU_OFF);
		}
		m_ctrOutput.AddString("CM_IOCTL_SET_RFID_CONTROL_FLAGS has been done successfully, now " + (strDriverState));
		ShowTimeRequired();
		GetDlgItem(IDC_MIFARE_EMU)->SetWindowText(strButtonTitle);
		GetDlgItem(IDC_MIFARE_EMU)->EnableWindow(FALSE);
	}
	else
	{
	   ShowErrorMessage(lErr);
	}

	ShowCursorOutScreen();
	UpdateData(FALSE);
}
