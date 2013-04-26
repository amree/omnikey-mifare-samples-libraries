// WriteDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadMemory.h"
#include "WriteDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char databuffer[300];
int datalength=0;
//char offsetbuffer[6];
int ioffset;

/////////////////////////////////////////////////////////////////////////////
// WriteDataDlg dialog


WriteDataDlg::WriteDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(WriteDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(WriteDataDlg)
	m_writebuffer = _T("");
	m_offset = _T("");
	//}}AFX_DATA_INIT
}


void WriteDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WriteDataDlg)
	DDX_Control(pDX, IDC_OFFSET, m_offsetctrl);
	DDX_Text(pDX, IDC_WRITEBUFFER, m_writebuffer);
	DDX_Control(pDX, IDC_ONHEX, m_hex);
	DDX_Control(pDX, IDC_ONASCII, m_ascii);
	DDX_Text(pDX, IDC_OFFSET, m_offset);
	DDV_MaxChars(pDX, m_offset, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WriteDataDlg, CDialog)
	//{{AFX_MSG_MAP(WriteDataDlg)
	ON_BN_CLICKED(IDC_ONASCII, OnASCII)
	ON_BN_CLICKED(IDC_ONHEX, OnHEX)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WriteDataDlg message handlers
BOOL WriteDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set default checked
	m_ascii.SetCheck(1);

	return TRUE;
}

void WriteDataDlg::OnASCII() 
{
	// Set ascci button checked
	m_ascii.SetCheck(1);
	m_hex.SetCheck(0);
}

void WriteDataDlg::OnHEX() 
{
	// set hex button checked
	m_ascii.SetCheck(0);
	m_hex.SetCheck(1);
}

void WriteDataDlg::OnOK() 
{
	UpdateData(true);
	// check if offset contains data
	if(m_offset.GetLength()!=0)
	{
		int breakoff2=0;
		int breakoff=0;
		// check if offset contains illegal values. legal values are { a-f, A-F, 0-9 }
		for(int k=0;k<m_offset.GetLength();k++)
		{
			char tc=m_offset.GetAt(k);
			if((tc>'f')||(tc<'a'))
				if((tc>'F')||(tc<'A'))
					if((tc>'9')||(tc<'0'))
						breakoff=1;
		}
		if(breakoff==1)
		{	// if illegal values present errormessage
			m_offset="";
			UpdateData(false);
			MessageBox("Illegal values in offset\nAllowed values are: 0-9, A-F, a-f");
			breakoff=0;
		}
		else
		{	// check if Databuffer contains data
			if(m_writebuffer.GetLength()!=0)
			{
				// check which button is checked, ascii or hex
				if(m_ascii.GetCheck()==1)
				{
					// ascii selected
			
					int i=0;
					// copy data to global var
					while((i<m_writebuffer.GetLength())&&(i<256))
					{
						databuffer[i]=m_writebuffer.GetAt(i);
						i++;
					}
					databuffer[i]='\0';
					// copy length to global var
					datalength=i;
				}
				else
				if(m_hex.GetCheck()==1)
				{
					// hex selected		
					// have to convert from ascii to hex values,... 
					// that means. if there´s an entry like this: "4849" and hex is selected
					// i have to convert it to 0x48 and 0x49 ('H' and 'I')
					// check if data contains illegal values. legal values are { a-f, A-F, 0-9 }
					for(int k=0;k<m_writebuffer.GetLength();k++)
					{
						char tc=m_writebuffer.GetAt(k);
						if((tc>'f')||(tc<'a'))
							if((tc>'F')||(tc<'A'))
								if((tc>'9')||(tc<'0'))
									breakoff2=1;
					}
					if(breakoff2==1)
					{
						// wrong values found
						MessageBox("Wrong Values in Data!\nAllowed values: 0-9, a-f, A-F\nplease check",MB_OK);
					}
					else
					{
						int i=0;
						int j=0;
						int sum=0;
			
						// convert data from hex to chars
						while(i<m_writebuffer.GetLength())
						{
							switch(m_writebuffer.GetAt(i))
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
							// if 2 values are added, write into databuffer
							if((i%2==0)&&(i!=0)) 
							{
								databuffer[i/2-1]=sum;
								sum=0;
							}
						}
						datalength=i/2;
					}
				}
				// Convert offset from CString to integer (0..255)
				int i=0;
				int j=0;
				int sum=0;
			
				while((i<4)&&(i<m_offset.GetLength()))
				{	
					switch(m_offset.GetAt(i))
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
					sum=sum*16;
					sum=sum+j;
					i++;
				}			
				ioffset=sum;
				// check if offset+length is smaller than 256

				if(breakoff2==1) ;
				else // Close Dialog
					CDialog::OnOK();
			}
			else
			{
				// Errormessage if no data inserted
				MessageBox("No Data inserted",NULL,MB_OK);
			}
		}
	}
	else
	{
		// Errormessage if no Offset inserted
		MessageBox("No Offset inserted",NULL,MB_OK);
	}
}

void WriteDataDlg::getData(char* pdata,int* plength,int* poffset)
{
	int i=0;
	// copy data from global var to pointer
	while(i<datalength)
	{
		pdata[i]=databuffer[i];
		i++;
	}
	pdata[i]='\0';
	// copy length from global var to pointer
	*plength=datalength;
	
	// copy offset from global var to pointer
	*poffset=ioffset;
}

void WriteDataDlg::OnCancel() 
{
	CDialog::OnCancel();
}
