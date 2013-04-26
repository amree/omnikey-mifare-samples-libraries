// DetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iClassExplorer.h"
#include "DetailDlg.h"
#include "CardReport.h"
#include "iClassExplorerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailDlg dialog


CDetailDlg::CDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDetailDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDetailDlg)
	DDX_Control(pDX, IDC_APPLICATION, m_ApplicationCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CDetailDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailDlg message handlers

void CDetailDlg::SetApp(unsigned char* pucApp, unsigned long ulLen,unsigned long ulAdd)
{
	memset(ucApp,0x00,2048);

	memcpy(ucApp,pucApp,ulLen);
	ulAppLen=ulLen;
	ulAddress = ulAdd;
}

BOOL CDetailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont font;
	char szText[128];
		
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

	m_ApplicationCtrl.SetFont(&font,TRUE);


	Show();

	if(ulAddress > (unsigned long)APPLICATION_START_ADDRESS)
		sprintf(szText,"Application 2");
	else
		sprintf(szText,"Application 1");

	SetWindowText(szText);

	return TRUE;
}

void CDetailDlg::Show()
{
	int i=0;
	int x=0;

	char szText[80];
	
	for(i=0;i<(int)(ulAppLen);i++)
	{
		memset(szText,0x00,80);
		sprintf(szText,"%04X  ",(i/8)+ulAddress);
		for(x=0;x<8 && i<(int)ulAppLen;i++,x++)
			sprintf(szText,"%s%02X ",szText,ucApp[i]);

		sprintf(szText,"%s\r\n",szText);

		m_ApplicationCtrl.SetSel(-1,-1);
		m_ApplicationCtrl.ReplaceSel(szText,FALSE);
		m_ApplicationCtrl.HideSelection(FALSE,FALSE);
	
		UpdateData(FALSE);
		UpdateWindow();
		i--;
	}
}