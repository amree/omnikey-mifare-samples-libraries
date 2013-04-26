/*****************************************************************************
@doc            SC4404
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------

 Test SLE4404 synchronous card functions. Called from:  \syntst\syntst.c
*-----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
******************************************************************************/

#define NO_ERRL

#include <okos.h>
#if defined S_WIN || defined S_WNT
   #include <windows.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <ok.h>
#include <scrn.h>
// #include <errl.h>
#include <str.h>
#include <mem.h>
#include <winscard.h>

#include <syntst.h>
#include <sc4404.h>         // This file has to be included after the #include <pcsc_cm.h>



/*****************************************************************************/
/**  GLOBAL DECLARATIONS                                                    **/
/*****************************************************************************/
static  CHAR    szText[160] = "\0";           /* Common string for text I/O */
static  BYTE    bReadBuffer[512];

#define MAX_BYTE     0x000000FF
#define MAX_USHORT   0x0000FFFF
#define MAX_ULONG    0xFFFFFFFF


/*****************************************************************************
Description:
   	
Arguments:

Return Value:
	
note:
*****************************************************************************/


/*****************************************************************************
Description:
Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCard4404ReadData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    okErr = NO_ERROR;
   USHORT   usY;
   ULONG    ulBitsToRead,ulBitAddress,ulBytesToRead;
   ULONG    ulTime1,ulTime2;

      SCRNClear();
      SCRNPutTextAt( 1, 20, "TEST SCard4404ReadData");
      SCRNPutTextAt( 2, 20, "----------------------");

		usY = 4;
      sprintf(szText,"Handle : 0x%08X \n", ulHandleSmartCard);
      SCRNPutTextAt(usY++, 2, szText);

      SCRNPutTextAt(usY, 2,"ulBitsToRead = ");
      ulBitsToRead = SCRNGetUShortAt(usY++,23,1,sizeof(bReadBuffer)*8);
      ulBytesToRead = ulBitsToRead/8 + ((ulBitsToRead%8) ? 1:0);

      SCRNPutTextAt(usY, 2,"ulBitAddress:");
      ulBitAddress = SCRNGetUShortAt(usY++,23,0,0xFFFF);

      ulTime1=GetTickCount();
      okErr = SCard4404ReadData(
                           ulHandleSmartCard,
                           ulBitsToRead,
                           ulBitAddress,
                           bReadBuffer,
                           sizeof(bReadBuffer));

      ulTime2=GetTickCount();
      ulTime2-=ulTime1;
      StrPrintf(szText," (%dms)",ulTime2);
      SCRNPutTextAt(usY++,2,szText);

      ErrorMessage(okErr);

      usY += 1;
      SCRNPutTextAt(usY, 2,"Data Read:\n");

      usY += 1;
      if (okErr == NO_ERROR)               // Display the data received
         {
         WriteBuffer(bReadBuffer, ulBytesToRead, &usY, 0);
			// DumpBuffer( bReadBuffer,(USHORT)ulBytesToRead, &usY);					
         }
      SCRNGetChar();
   return;
}



/*****************************************************************************
Description:

Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCard4404WriteData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    okErr = NO_ERROR;
   USHORT   usY = 4;
   BYTE     bWriteBuffer[1025];
   ULONG    ulBitsToWrite,ulBitAddress,ulBytesToWrite;
   ULONG    ulTime1,ulTime2;
   //UCHAR    i;

      SCRNClear();
      SCRNPutTextAt( 1, 27, "TEST SCard4404WriteData");
      SCRNPutTextAt( 2, 27, "-----------------------");

      SCRNPutTextAt(usY,   2,"ulBitsToWrite:");
      ulBitsToWrite = SCRNGetULong(1,sizeof(bWriteBuffer)*8);
      ulBytesToWrite = ulBitsToWrite/8 + ((ulBitsToWrite%8) ? 1:0);

      SCRNPutTextAt(++usY, 2,"ulBitAddress:");
      ulBitAddress = SCRNGetULongAt(usY++,16,0,0xFFFF);

      SCRNPutTextAt(usY,   2,"Data:");
      SCRNGetTextAt(usY++, 16,(USHORT)ulBytesToWrite, bWriteBuffer, sizeof(bWriteBuffer));

      ulTime1=GetTickCount();

      okErr = SCard4404WriteData(
   							   ulHandleSmartCard,
   							   bWriteBuffer,           // output buffer holding the wrtie data
   							   ulBitsToWrite,
							   ulBitAddress);

      ulTime2=GetTickCount();
      ulTime2-=ulTime1;
      StrPrintf(szText," (%dms)",ulTime2);
      SCRNPutTextAt(usY++,2,szText);

      ErrorMessage(okErr);
      SCRNGetChar();
}

/*****************************************************************************
Description:

Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCard4404VerifyUserCode(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    okErr = NO_ERROR;
   USHORT   usY = 4;
   BYTE     bWriteBuffer[1025];
   ULONG    ulBytesToWrite;
   ULONG    ulTime1,ulTime2;

      SCRNClear();
      SCRNPutTextAt( 1, 27, "TEST SCard4404VerifyUserCode");
      SCRNPutTextAt( 2, 27, "----------------------------");

      ulBytesToWrite = 2;

	  SCRNPutTextAt(usY,   2,"Data:");
      SCRNGetTextAt(usY++, 16,(USHORT)ulBytesToWrite, bWriteBuffer, sizeof(bWriteBuffer));

      ulTime1=GetTickCount();

      okErr = SCard4404VerifyUserCode(
   							   ulHandleSmartCard,
   							   bWriteBuffer);

	  

      ulTime2=GetTickCount();
      ulTime2-=ulTime1;
      StrPrintf(szText," (%dms)",ulTime2);
      SCRNPutTextAt(usY++,2,szText);

      ErrorMessage(okErr);
      SCRNGetChar();
}


/*****************************************************************************
Description:

Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCardEraseErrorCounter(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    okErr = NO_ERROR;
   ULONG    ulBitAddress;

      SCRNClear();
      SCRNPutTextAt( 1, 27, "TEST SCard4404EraseErrorCounter");
      SCRNPutTextAt( 2, 27, "-------------------------------");

      SCRNPutTextAt(4, 2,"ulBitAddress:");
      ulBitAddress = SCRNGetULongAt(4,16,0,0xFFFF);

      okErr = SCard4404EraseErrorCounter( ulHandleSmartCard,
                                          ulBitAddress);
      ErrorMessage(okErr);
      SCRNGetChar();
}


/*****************************************************************************
Description:

Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCardEraseUserMemory(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    okErr = NO_ERROR;
   ULONG    ulBitAddress;

      SCRNClear();
      SCRNPutTextAt( 1, 27, "TEST SCard4404EraseUserMemory");
      SCRNPutTextAt( 2, 27, "-----------------------------");

      SCRNPutTextAt(4, 2,"ulBitAddress:");
      ulBitAddress = SCRNGetULongAt(4,16,0,0xFFFF);
      okErr = SCard4404EraseUserMemory( ulHandleSmartCard,
                                        ulBitAddress);

      ErrorMessage(okErr);
      SCRNGetChar();
}


/*****************************************************************************
Description:

Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCardEraseScratchPadMemory(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    okErr = NO_ERROR;
   ULONG    ulBitAddress;

      SCRNClear();
      SCRNPutTextAt( 1, 27, "TEST SCard4404ScratchPadMemory");
      SCRNPutTextAt( 2, 27, "------------------------------");

      SCRNPutTextAt(4, 2,"ulBitAddress:");
      ulBitAddress = SCRNGetULongAt(4,16,0,0xFFFF);

      okErr = SCard4404EraseScratchPadMemory( ulHandleSmartCard,
                                              ulBitAddress);

      ErrorMessage(okErr);
      SCRNGetChar();
}



/*****************************************************************************
Description:

Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCard4404Status(SCARDHANDLE ulHandleSmartCard)
{
	OKERR		okErr = NO_ERROR;
	BYTE		szReader[200] = "\0";
	BYTE		bAttr[32];
	DWORD		cByte = 32;
	USHORT		usY;
	DWORD		dwState, dwProtocol, dwReaderLen;

		SCRNClear();
		SCRNPutTextAt( 1, 27, "TEST SCard4404Status");
		SCRNPutTextAt( 2, 27, "--------------------");

		// Determine the status.
		// hCardHandle was set by an earlier call to SCardConnect.
		okErr = SCardStatus(ulHandleSmartCard,
					  szReader,
                      &dwReaderLen,
                      &dwState,
                      &dwProtocol,
                      (LPBYTE)&bAttr,
                      &cByte);
		
		// Wait for confirmation
		usY = 4;
		sprintf(szText,"Reader :", ulHandleSmartCard);
		SCRNPutTextAt(usY++, 2, szText);
		SCRNGetChar();

		if ( SCARD_S_SUCCESS != okErr )
		{
			SCRNPutTextAt( 2, 27, "Failed SCardStatus\n");
		}

		// Examine retrieved status elements.
		// Look at the reader name and card state.

		switch ( dwState )
		{
			case SCARD_ABSENT:
				printf("Card absent.\n");
				break;
			case SCARD_PRESENT:
				printf("Card present.\n");
				break;
			case SCARD_SWALLOWED:
				printf("Card swallowed.\n");
				break;
			case SCARD_POWERED:
				printf("Card has power.\n");
				break;
			case SCARD_NEGOTIABLE:
				printf("Card reset and waiting PTS negotiation.\n");
				break;
			case SCARD_SPECIFIC:
				printf("Card has specific communication protocols set.\n");
				break;
			default:
				printf("Unknown or unexpected card state.\n");
				break;
		}

	//ErrorMessage(okErr);
	SCRNPutTextAt(23,1,"< Press any key to continue >");
	SCRNGetChar();		// Wait for confirmation
}


/*****************************************************************************
Description:

Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCard4404ChangeUserCode(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    okErr = NO_ERROR;
   USHORT   usY = 4;
   BYTE     bOldPinBuffer[1025];
   BYTE     bNewPinBuffer[1025];
   ULONG    ulBytesToWrite;
   ULONG    ulTime1,ulTime2;

      SCRNClear();
      SCRNPutTextAt( 1, 27, "TEST SCard4404ChangeUserCode");
      SCRNPutTextAt( 2, 27, "----------------------------");

      ulBytesToWrite = 16;
	  SCRNPutTextAt(usY,   2,"OldPin:");
      SCRNGetTextAt(usY++, 16,(USHORT)ulBytesToWrite, bOldPinBuffer, sizeof(bOldPinBuffer));

	  ulBytesToWrite = 16;
	  SCRNPutTextAt(usY,   2,"NewPin:");
      SCRNGetTextAt(usY++, 16,(USHORT)ulBytesToWrite, bNewPinBuffer, sizeof(bNewPinBuffer));

      ulTime1=GetTickCount();

      okErr = SCard4404ChangeUserCode(
   							   ulHandleSmartCard,
   							   bOldPinBuffer,
							   bNewPinBuffer);

      ulTime2=GetTickCount();
      ulTime2-=ulTime1;
      StrPrintf(szText," (%dms)",ulTime2);
      SCRNPutTextAt(usY++,2,szText);

      ErrorMessage(okErr);
      SCRNGetChar();
}
