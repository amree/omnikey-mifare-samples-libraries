// GetKeyInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetKeyInfo.h"
#include "GetKeyInfoDlg.h"

#include "KeyInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <winscard.h>

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
// CGetKeyInfoDlg dialog

CGetKeyInfoDlg::CGetKeyInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetKeyInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetKeyInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetKeyInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetKeyInfoDlg)
	DDX_Control(pDX, IDC_READERLIST, m_ReaderList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetKeyInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CGetKeyInfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETINFO, OnGetinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetKeyInfoDlg message handlers

BOOL CGetKeyInfoDlg::OnInitDialog()
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

	GetReaders();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetKeyInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetKeyInfoDlg::OnPaint() 
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
HCURSOR CGetKeyInfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetKeyInfoDlg::GetReaders()
{
	char szReaders[10][100];
	char mszReaders[1024];
	DWORD dwLength = sizeof(mszReaders);
	DWORD rc;

	rc=0;
	hContext=0xFFFFFFFF;

	this->m_ReaderList.ResetContent();

	rc = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
	if(rc != SCARD_S_SUCCESS)
	{
		// error
		MessageBox("Unable to establish SmartCard Context!!","SCardEstablishContext",MB_OK);
		goto EXIT;
	}

	rc = SCardListReaders(hContext, NULL,mszReaders,&dwLength);
	if(rc != SCARD_S_SUCCESS)
	{
		// error
		this->m_ReaderList.AddString("no reader found");
		this->m_ReaderList.SetCurSel(0);
		goto EXIT;
	}

	// SCardListReaders successfull
	
	// seperate reader names
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

			this->m_ReaderList.AddString(tempstring);
		}
		if(j<=1)
		{
			this->m_ReaderList.AddString("no reader found");
		}
		this->m_ReaderList.SetCurSel(0);
	}

EXIT:
	if(hContext!=0xFFFFFFFF)
		SCardReleaseContext(hContext);

	
}

void CGetKeyInfoDlg::OnGetinfo() 
{
	UpdateData(TRUE);

	this->m_ReaderList.GetText(this->m_ReaderList.GetCurSel(),this->m_szReaderName);

	KeyInfoDlg kid;

	kid.SetReaderName(this->m_szReaderName);

	kid.DoModal();	
}
