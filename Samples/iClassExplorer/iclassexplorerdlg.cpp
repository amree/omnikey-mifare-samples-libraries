// iClassExplorerDlg.cpp : implementation file
//

#include "stdafx.h"

#include <winscard.h>

#include "iClassExplorer.h"
#include "iClassExplorerDlg.h"

#include "cardreport.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIClassExplorerDlg dialog

CIClassExplorerDlg::CIClassExplorerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIClassExplorerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIClassExplorerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIClassExplorerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIClassExplorerDlg)
	DDX_Control(pDX, IDOK, m_CardReportButton);
	DDX_Control(pDX, IDC_READERLIST, m_ReaderList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIClassExplorerDlg, CDialog)
	//{{AFX_MSG_MAP(CIClassExplorerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIClassExplorerDlg message handlers

BOOL CIClassExplorerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	GetReaders();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIClassExplorerDlg::OnPaint() 
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
HCURSOR CIClassExplorerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIClassExplorerDlg::OnOK() 
{
	CCardReport ccr;

	char szReaderName[READERNAMESIZE];

	this->m_ReaderList.GetText(this->m_ReaderList.GetCurSel(),szReaderName);

	ccr.SetReaderName(szReaderName);

	ccr.DoModal();
}

void CIClassExplorerDlg::GetReaders()
{
	char szReaders[10][100];
	char mszReaders[1024];
	DWORD dwLength = sizeof(mszReaders);
	DWORD rc;

	rc=0;
	hContext=0xFFFFFFFF;

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
			this->m_CardReportButton.EnableWindow(TRUE);
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