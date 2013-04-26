// KeyInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iClassExplorer.h"
#include "KeyInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyInputDlg dialog


CKeyInputDlg::CKeyInputDlg(CWnd* pParent /*=NULL*/, unsigned char ucPage)
	: CDialog(CKeyInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyInputDlg)
	m_Key = _T("");
	m_Page = ucPage;
	m_KeyNo = _T("");
	//}}AFX_DATA_INIT
}


void CKeyInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyInputDlg)
	DDX_Text(pDX, IDC_KEY, m_Key);
	DDV_MaxChars(pDX, m_Key, 16);
	DDX_Text(pDX, IDC_KEYNO, m_KeyNo);
	DDV_MaxChars(pDX, m_KeyNo, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyInputDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyInputDlg)
	ON_BN_CLICKED(IDC_KDRADIO, OnKdradio)
	ON_BN_CLICKED(IDC_KCRADIO, OnKcradio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyInputDlg message handlers

BOOL CKeyInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	char szText[128];

	sprintf(szText,"Enter Key for Page %02X",m_Page);
	SetWindowText(szText);

	((CButton*)GetDlgItem(IDC_KCRADIO))->SetCheck(BST_CHECKED);
	this->m_KeyType=0x01;
	this->m_KeyNo.Format("20");

	UpdateData(FALSE);

	return TRUE;
}

void CKeyInputDlg::OnKdradio() 
{
	this->m_KeyType=0x01;	
}


void CKeyInputDlg::OnKcradio() 
{
	this->m_KeyType=0x00;
}

void CKeyInputDlg::OnOK() 
{
	UpdateData(TRUE);	

	CDialog::OnOK();
}
