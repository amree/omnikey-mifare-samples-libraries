// InsertPinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadMemory.h"
#include "InsertPinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char pin[8];
int maxtext=0;

/////////////////////////////////////////////////////////////////////////////
// InsertPinDlg dialog


InsertPinDlg::InsertPinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InsertPinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(InsertPinDlg)
	m_pin = _T("");
	//}}AFX_DATA_INIT
}


void InsertPinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InsertPinDlg)
	DDX_Control(pDX, IDC_EDIT1, m_pincrtl);
	DDX_Text(pDX, IDC_EDIT1, m_pin);
	DDV_MaxChars(pDX, m_pin, maxtext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InsertPinDlg, CDialog)
	//{{AFX_MSG_MAP(InsertPinDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InsertPinDlg message handlers

void InsertPinDlg::OnOK() 
{
	// get Data from dialog to vars
	UpdateData(true);
	
	int breakoff=0;
	// check if pin contains illegal values. legal values are { a-f, A-F, 0-9 }
	for(int k=0;k<m_pin.GetLength();k++)
	{
		char tc=m_pin.GetAt(k);
		if((tc>'f')||(tc<'a'))
			if((tc>'F')||(tc<'A'))
				if((tc>'9')||(tc<'0'))
					breakoff=1;
	}
	if(breakoff==1)
	{	// if illegal values are present errormessage
		m_pin="";
		UpdateData(false);
		MessageBox("Pin contains illegal values");
		breakoff=0;
	}
	else
	{
		// copy pin from dialog to global var
		for(int i=0;i<m_pin.GetLength();i++)
		{
			pin[i]=m_pin.GetAt(i);
		}
	
		// close dialog
		CDialog::OnOK();
	}

}

void InsertPinDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void InsertPinDlg::getPin(char* ppin,int* laenge)
{
	// copy pin from global var to pointer from CReadMemoryDlg-class
	int i=0;
	while((pin[i]!='\0')&&(i<maxtext))
	{
		ppin[i]=pin[i];
		i++;
	}
	// copy length
	*laenge=i;
}

void InsertPinDlg::setCardType(bool cardtype)
{
	// set maximum length of PIN
	// if cardtype == true it´s an 2W card (3 BYTES PIN)
	// if cardtype == false it´s an 3W card (2 BYTES PIN)
	if(cardtype)
	{
		maxtext=6;
	}
	else
	{
		maxtext=4;
	}
}
