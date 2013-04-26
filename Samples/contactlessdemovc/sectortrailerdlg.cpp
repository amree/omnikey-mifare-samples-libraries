// SectorTrailerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "contactlessdemovc.h"
#include "SectorTrailerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SectorTrailerDlg dialog


SectorTrailerDlg::SectorTrailerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SectorTrailerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SectorTrailerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SectorTrailerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SectorTrailerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SectorTrailerDlg, CDialog)
	//{{AFX_MSG_MAP(SectorTrailerDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SectorTrailerDlg message handlers
