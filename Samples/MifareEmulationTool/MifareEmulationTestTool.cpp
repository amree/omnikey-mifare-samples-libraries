// Includes

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <wtypes.h>
#include <winsmcrd.h>
#include <winscard.h>

// Defines

#define output printf

#define CM_IOCTL_SET_RFID_CONTROL_FLAGS	SCARD_CTL_CODE(3213)


//Global variable

DWORD				SCard_Status = 0;

CHAR				szReader[10][100];
CHAR				szReaderName[100];

int					iSelectedMode;

char				szText[512];

SCARDCONTEXT		hContext = 0xFFFFFFFF;
SCARDHANDLE			hCard  = 0xFFFFFFFF;

SCARD_READERSTATE	sReaderState;

// Prototypes

BOOL Init (void);

int main(void)
{
	BYTE	i;

	DWORD	dwActiveProtocol;
	DWORD	dwControlFlag;

	BYTE	InBuffer[16];
    BYTE	OutBuffer[16];
    DWORD	dwInBufferSize ;
    DWORD	dwOutBufferSize;
	DWORD	dwBytesReturned;
	DWORD	*Mask           = (DWORD *)InBuffer;
	DWORD	*Value          = (DWORD *)InBuffer+1;
	DWORD	dwControlCode   = CM_IOCTL_SET_RFID_CONTROL_FLAGS;

	if (Init())
	{

		SCard_Status = SCardConnect(hContext,
									szReaderName,
									SCARD_SHARE_SHARED,
									SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
									&hCard,
									&dwActiveProtocol);
		
		if(SCard_Status != SCARD_S_SUCCESS)
		{
			sprintf(szText,"\nProblem in SCardConnect %s", szReaderName);
			output(szText);
			goto EXIT;
		}

		iSelectedMode = 1;

		sprintf(szText,"\npress [ESC]\tCANCEL\npress [ 0 ]\tMifare emulation off\tT=CL\npress [ 1 ]\tMifare emulation on\n\n");
		output(szText);

		do
		{
			while (!kbhit());
			switch (getch())
			{
				case '0' : dwControlFlag = 0x00000000;
						   break;
				case '1' : dwControlFlag = 0xFFFFFFFF;
						   break;
				default  : iSelectedMode = 0;
					       break;
			}

			if( iSelectedMode == 0) break;

			memset(InBuffer, 0x00, sizeof(InBuffer));
			memset(OutBuffer, 0x00, sizeof(OutBuffer));

			*Mask			= 0x00000004;
			*Value			= dwControlFlag & *Mask;
			dwInBufferSize  = 8;
			dwOutBufferSize = 0;
			dwBytesReturned = 0;

			SCard_Status = SCardControl(hCard,
									    dwControlCode,
									    (LPCVOID)InBuffer,
									    dwInBufferSize,
									    (LPVOID)OutBuffer,
									    dwOutBufferSize,
									    &dwBytesReturned);

			for(i=0; i<79; i++) szText[i] = ' ';
			szText[i++] = 0x0D;
			szText[i] = 0x00;
			output(szText);

			if (SCard_Status == SCARD_S_SUCCESS)
			{
				if(dwControlFlag)
					sprintf(szText,"Mifare\t");
				else
					sprintf(szText,"T=CL\t");
			}
			else
			{
				sprintf(szText,"IO Cntrol error\r");
			}
			output(szText);

			// The card is disconnected after exchange the Mifare emulation
			do
			{
				sReaderState.szReader = szReaderName;
				sReaderState.dwCurrentState = SCARD_STATE_EMPTY;
				sReaderState.dwEventState = SCARD_STATE_EMPTY;
				SCardGetStatusChange(hContext,50,&sReaderState,1);
			}
			while((sReaderState.dwEventState & SCARD_STATE_PRESENT) == 0);
			SCardGetStatusChange(hContext,10,&sReaderState,1);

			if(SCard_Status == SCARD_S_SUCCESS)
			{
				i = 0;
				sprintf(szText, "ATR:");
				while(i < sReaderState.cbAtr)
				{
					sprintf(&szText[strlen(szText)], " % 02X", sReaderState.rgbAtr[i]);
					i++;
				}
				sprintf(&szText[strlen(szText)],"\r");
				output(szText);
			}

			SCard_Status = SCardConnect(hContext,
										szReaderName,
										SCARD_SHARE_SHARED,
										SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
										&hCard,
										&dwActiveProtocol);
			
		}
		while (SCard_Status == SCARD_S_SUCCESS);
	}

	SCard_Status = SCardDisconnect(hCard, SCARD_LEAVE_CARD);

	EXIT:

	SCardReleaseContext(hContext);

	return 0;
}


BOOL Init(void)
{
	DWORD i = 0, z = 0, j =0;
    DWORD dwLength = 1024;// = sizeof(mszReaders);


    for (i=0; i<10; i++)
    {
		memset(&szReader[i][0],0x00,sizeof(&szReader[i][0]));
	}




	SCard_Status = SCardEstablishContext(SCARD_SCOPE_USER,
                                         NULL,
                                         NULL,
                                         &hContext);


    if (SCard_Status != 0)
    {

		sprintf(szText,"\nProblem in SCardEstablishContext");
		output(szText);
		return FALSE;
	}


	char *pmszReaders = NULL;

	SCard_Status = SCardListReaders(hContext,
                                    NULL,
                                    NULL,
                                    &dwLength);

	pmszReaders = (char*)malloc(sizeof(char)*dwLength);
    SCard_Status = SCardListReaders(hContext,
		                            NULL,
									pmszReaders,
									&dwLength);

    if (SCard_Status != 0)
    {
		sprintf(szText,"\nProblem in SCardListReaders");
		output(szText);
		return FALSE;
	}

	// Fill the Reader name field

	if (dwLength > 2) // \0\0
    {
		z=0;
		j=0;
		for (i=0; i<dwLength; i++)
        {
			if (pmszReaders[i] == '\0')
            {
				szReader[j][z] = pmszReaders[i];

				z=0;
				j++;
            }
			else
            {
				szReader [j] [z] = pmszReaders[i];
				z++;
            }

		}
	}

	sprintf(szText,"\nConnected readers are as follows:\n\n");
	output(szText);

	z = 0;
	for (j=0;j < 10;j++)
    {
		if (szReader[j] [0] != 0x00)
        {
			z++;

			sprintf(szText,"%d\t", j);
			output(szText);

			sprintf(szText,"%s\n",szReader[j]);
			output(szText);
        }
	}

	if(z == 0)
	{
		sprintf(szText,"\nNo reader connected!\n");
		output(szText);
		return FALSE;
	}

	memset(szReaderName, 0x00, sizeof(szReaderName));

	do
	{
		sprintf(szText,"\nSelect the reader number and confirm [ENTER]\n");
		output(szText);
		scanf("%d", &iSelectedMode);
		if((iSelectedMode >= 0) && (iSelectedMode <= (int)z))
		{
			strcpy(szReaderName, szReader[iSelectedMode]);
		}
	}
	while (strlen(szReaderName) == 0);


	sprintf(szText,"\nSelect reader is:\t%s\n", szReaderName);
	output(szText);
	
    return TRUE;
}

