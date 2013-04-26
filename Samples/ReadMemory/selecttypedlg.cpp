// SelectTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadMemory.h"
#include "SelectTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int cursel;
char curtyp[10];

/////////////////////////////////////////////////////////////////////////////
// SelectTypeDlg dialog


SelectTypeDlg::SelectTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelectTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelectTypeDlg)
	//}}AFX_DATA_INIT
}


void SelectTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectTypeDlg)
	DDX_Control(pDX, IDC_COMBO1, m_listtyp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectTypeDlg, CDialog)
	//{{AFX_MSG_MAP(SelectTypeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectTypeDlg message handlers
BOOL SelectTypeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add all availiable constants to typelist
	m_listtyp.AddString("Default");
	m_listtyp.AddString("ST14C02C");
 	m_listtyp.AddString("ST14C04C");
 	m_listtyp.AddString("ST14E32");
 	m_listtyp.AddString("M14C04");
 	m_listtyp.AddString("M14C16");
 	m_listtyp.AddString("M14C32");
 	m_listtyp.AddString("M14C64");
 	m_listtyp.AddString("M14128");
 	m_listtyp.AddString("M14256");
  	m_listtyp.AddString("GFM2K");
 	m_listtyp.AddString("GFM4K");
 	m_listtyp.AddString("GFM32K");
	m_listtyp.AddString("AT24C01A");
 	m_listtyp.AddString("AT24C02");
 	m_listtyp.AddString("AT24C04");
 	m_listtyp.AddString("AT24C08");
 	m_listtyp.AddString("AT24C16");
 	m_listtyp.AddString("AT24C164");
 	m_listtyp.AddString("AT24C32");
 	m_listtyp.AddString("AT24C64");
 	m_listtyp.AddString("AT24C128");
 	m_listtyp.AddString("AT24C256");
 	m_listtyp.AddString("AT24CS128");
 	m_listtyp.AddString("AT24CS256");
 	m_listtyp.AddString("AT24C512");

	// set defaultselected
	m_listtyp.SetCurSel(0);
	UpdateData(false);

	return TRUE;
}


void SelectTypeDlg::OnOK()
{
	// TODO: Add extra validation here

	// get current selected index
	cursel=m_listtyp.GetCurSel();
	// get current selected typ and save it to a GLOBAL variable
	m_listtyp.GetLBText(cursel,curtyp);

	// close dialog
	CDialog::OnOK();
}

void SelectTypeDlg::getCurSelItem(char* typ)
{
	// copy type from global variable to a variable from CReadMemoryDlg Class
	int i=0;
	while(i<10)
	{
		typ[i]=curtyp[i];
		i++;
	}
}
