/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/dftst/rcs/dftst041.c $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*-----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
******************************************************************************/

#include <okos.h>
#if defined S_WIN || defined S_WNT
   #include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#include <ok.h>
#include <scrn.h>
#include <str.h>
#include <mem.h>
#include <winscard.h>
#include <time.h>

#include "dftst.h"
#include "dftst041.h"
#include <scarddf.h>


static  CHAR    szText[160] = "\0";           /* Common string for text I/O */


#define MAX_BYTE     0x000000FF
#define MAX_USHORT   0x0000FFFF
#define MAX_ULONG    0xFFFFFFFF


#define TESTAPP_MAX_DATA_READ_LENGTH	  4096

//
#define MEASURE_TIME
#undef MEASURE_TIME
//.

/*****************************************************************************
Description:
	Test function for ContinuousArrayRead scardsyn.dll library function
	
Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_ContinuousArrayRead(
												SCARDHANDLE ulHandleSmartCard
												)
{
   OKERR 	eErr = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[TESTAPP_MAX_DATA_READ_LENGTH];	
   ULONG  	ulPageAdr;
   ULONG  	ulByteAdr;
	ULONG    ulBytesToRead ;
	ULONG    ulBytesRetruned;
   ULONG ulTime1,ulTime2;

		SCRNClear();
		SCRNPutTextAt( 1, 29, "Test AT45DB041 Continuous Array Read");
		SCRNPutTextAt( 2, 29, "------------------------------------");

		usY = 4;
		#define XPOS	  	24

		sprintf(szText,"Handle  : 0x%08X \n", ulHandleSmartCard);
		SCRNPutTextAt(usY++, 2, szText);
	
		SCRNPutTextAt(usY, 2,"Page address   :");
		ulPageAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_TOTAL_PAGES -1);
		
		SCRNPutTextAt(usY, 2,"Byte address   :");
		ulByteAdr = SCRNGetULongAt(usY++,XPOS, 0,TESTAPP_MAX_DATA_READ_LENGTH);
	
		SCRNPutTextAt(usY, 2,"Bytes to read:");
		ulBytesToRead = SCRNGetULongAt(usY++,XPOS, 1,TESTAPP_MAX_DATA_READ_LENGTH );
	
		#undef XPOS
		
		//
		// Call the corresponding sync library data flash function
		//
      ulTime1=GetTickCount();
		eErr = SCardDfContinuousArrayRead(
													ulHandleSmartCard,   	// Handle (get from SCardConnect)
													abData,        			// Pointer to the buffer, where the data read are to be stored
													sizeof(abData),    		// Size of the read buffer
													ulPageAdr,   	   		// page address [0,2048]
													ulByteAdr,   	   		// byta address in a page
													ulBytesToRead,				// Number of bytes to be read
													&ulBytesRetruned			//out: Number of bytes actually read
													);
      ulTime2=GetTickCount();
      ulTime2-=ulTime1;
      StrPrintf(szText," (%dms)",ulTime2);
      SCRNPutText(szText);
		ErrorMessage(
						eErr
						);
		if (eErr == NO_ERROR)
			{
			usY += 2;
	
			WriteBuffer(
						abData,
						ulBytesRetruned,			//ulBytesToRead,
						&usY,
						0
						);
			}
	
		SCRNPutTextAt(23,1,"< Press any key to continue >");
		SCRNGetChar();
}


/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID TestAT45DB041_MainMemoryPageRead(
												SCARDHANDLE ulHandleSmartCard
												)
{
   OKERR 	eErr = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[TESTAPP_MAX_DATA_READ_LENGTH];	
   ULONG  	ulPageAdr;
   ULONG  	ulByteAdr;
	ULONG    ulBytesToRead ;
	ULONG    ulBytesRetruned;

		SCRNClear();
		SCRNPutTextAt( 1, 29, "Test AT45DB041 Main Memory Page Read");
		SCRNPutTextAt( 2, 29, "------------------------------------");

		usY = 4;
		#define XPOS	  	24

		sprintf(szText,"Handle  : 0x%08X \n", ulHandleSmartCard);
		SCRNPutTextAt(usY++, 2, szText);
	
		SCRNPutTextAt(usY, 2,"Page address   :");
		ulPageAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_TOTAL_PAGES -1);
		
		SCRNPutTextAt(usY, 2,"Byte address   :");
		ulByteAdr = SCRNGetULongAt(usY++,XPOS, 0,TESTAPP_MAX_DATA_READ_LENGTH);
	
		SCRNPutTextAt(usY, 2,"Bytes to read:");
		ulBytesToRead = SCRNGetULongAt(usY++,XPOS, 1,TESTAPP_MAX_DATA_READ_LENGTH );
	
		#undef XPOS
		
		//
		// Call the corresponding sync library data flash function
		//
		eErr = SCardDfMainMemoryPageRead(
													ulHandleSmartCard,   	// Handle (get from SCardConnect)
													abData,        			// Pointer to the buffer, where the data read are to be stored
													sizeof(abData),    		// Size of the read buffer
													ulPageAdr,   	   		// page address [0,2048]
													ulByteAdr,   	   		// byta address in a page
													ulBytesToRead,				// Number of bytes to be read
													&ulBytesRetruned			//out: Number of bytes actually read
													);
		ErrorMessage(
						eErr
						);
		if (eErr == NO_ERROR)
			{
			usY += 2;
	
			WriteBuffer(
						abData,
						ulBytesRetruned,			//ulBytesToRead,
						&usY,
						0
						);
			}
	
		SCRNPutTextAt(23,1,"< Press any key to continue >");
		SCRNGetChar();
}



/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID	TestAT45DB041_BufferRead (
									SCARDHANDLE ulHandleSmartCard
									)
{
   OKERR 	eErr = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[TESTAPP_MAX_DATA_READ_LENGTH];	
   ULONG  	ulByteAdr;
	ULONG    ulBytesToRead ;
	ULONG    ulBytesRetruned;
	UCHAR 	ucBufferNr;

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Buffer Read");
		SCRNPutTextAt( 2, 27, "--------------------------");

		usY = 4;
		#define XPOS	  	26

		SCRNPutTextAt(usY,  	2,"Select a buffer[1,2]:");
		ucBufferNr = (UCHAR)SCRNGetULongAt(usY++,XPOS,1,2);

      SCRNPutTextAt(usY,  	2,"Bytes to read[1,264]:");
      ulBytesToRead  = SCRNGetULongAt(usY++,XPOS,1,AT45DB041_BUFFER_SIZE );

      SCRNPutTextAt(usY,	2,"Read address[0,263] :");
      ulByteAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_BUFFER_SIZE -1);

		#undef XPOS
		
		//
		// Call the corresponding sync library data flash function
		//
		eErr = SCardDfBufferRead(
										ulHandleSmartCard,
										abData,
										sizeof(abData),
										ulByteAdr,   	
										ulBytesToRead,		
										ucBufferNr,
										&ulBytesRetruned
										);
		ErrorMessage(
						eErr
						);
		//
		// Display the data read
		//
		if (eErr == NO_ERROR)
			{
			usY += 2;
	
			WriteBuffer(
						abData,
						ulBytesRetruned,			//ulBytesToRead,
						&usY,
						0
						);
			}
	
  	SCRNPutTextAt(23,1,"< Press any key to continue >");
  	SCRNGetChar();
}
	


/*****************************************************************************
Description:

Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_StatusRegRead(
											SCARDHANDLE ulHandleSmartCard
											)
{
   OKERR 	eErr = NO_ERROR;
   USHORT 	usY=4;
   BYTE   	abData[4];	
			
		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Status Register Read");
		SCRNPutTextAt( 2, 27, "-----------------------------------");
	
		eErr = SCardDfStatusRegisterRead (
													ulHandleSmartCard,
													&abData[0]
													);
		ErrorMessage(
						eErr
						);
		//
		// Display the data read
		//
		if (eErr == NO_ERROR)
			{
			usY += 2;
			WriteBuffer(
						abData,
						1,			
						&usY,
						0
						);
			}
  	SCRNPutTextAt(23,1,"< Press any key to continue >");
  	SCRNGetChar();
}




//
//Programm and erase operations
//


/*****************************************************************************
Description:
	Test
				
Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_BufferWrite(
										SCARDHANDLE ulHandleSmartCard
										)
{
   OKERR    eErr = NO_ERROR;
   BYTE     bWriteBuffer[AT45DB041_BUFFER_SIZE];
   ULONG    ulAddress;
   ULONG    ulBytesToWrite;
	USHORT   usY ;
	UCHAR 	ucBufferNr;
	#ifdef MEASURE_TIME
		ULONG    ulTime1,ulTime2;
	#endif
	

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 BufferWrite");
		SCRNPutTextAt( 2, 27, "--------------------------");

		usY = 4;
		#define XPOS	  	26

		SCRNPutTextAt(usY,  	2,"Select a buffer[1,2] :");
		ucBufferNr = (UCHAR)SCRNGetULongAt(usY++,XPOS,1,2);				  				// min,max

      SCRNPutTextAt(usY,  	2,"Bytes to write[1,264]:");
      ulBytesToWrite = SCRNGetULongAt(usY++,XPOS,1,sizeof(bWriteBuffer));	// min,max

      SCRNPutTextAt(usY,	2,"Write address[0,263] :");
      ulAddress = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_BUFFER_SIZE -1);

		#undef XPOS
		
      SCRNPutTextAt(usY, 2,"Data:");
      SCRNGetTextAt(
						usY++, 16,
						(USHORT)ulBytesToWrite,
						bWriteBuffer,
						sizeof(bWriteBuffer)+1
						);

		#ifdef MEASURE_TIME
      ulTime1 = GetTickCount();
		#endif

		eErr = SCardDfBufferWrite(
										ulHandleSmartCard,   	// Handle (get from SCardConnect)
										bWriteBuffer,           // output buffer holding the wrtie data
										ulAddress,
										ulBytesToWrite,
										ucBufferNr
										);

		#ifdef MEASURE_TIME
      ulTime2 =  GetTickCount() - ulTime1;
      StrPrintf(szText," (%d[ms])",ulTime2);
      SCRNPutTextAt(usY++,2,szText);
		#endif
		
      ErrorMessage(eErr);
      SCRNGetChar();
}





/*****************************************************************************
Description:
	
Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_BufferToMainMemoryPageProgram(
													SCARDHANDLE ulHandleSmartCard
													)
{
   OKERR    eErr = NO_ERROR;
   ULONG    ulPageAdr;
	USHORT   usY ;
	UCHAR 	ucBufferNr=1;
	UCHAR 	ucErase=0;
	#ifdef MEASURE_TIME
   ULONG    ulTime1,ulTime2;
	#endif

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Main memory page program");
		SCRNPutTextAt( 2, 27, "---------------------------------------");

		usY = 4;
		#define XPOS		36

		SCRNPutTextAt(usY, 2,"Select buffer[1,2]  :");
		ucBufferNr = (UCHAR)SCRNGetULongAt(usY++,XPOS, 1,2);				  				

		SCRNPutTextAt(usY, 2,"Page address[0,2047]:");
		ulPageAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_TOTAL_PAGES -1);			

		SCRNPutTextAt(usY, 2,"Program without=0/with=1 erase:");
		ucErase = (UCHAR)SCRNGetULongAt(usY++,XPOS, 0,1);				  				

		#undef XPOS
		
		//
		// No used data for this command. The data stored in the buffer nr. are written into the main memory.
		//
	#ifdef MEASURE_TIME
      ulTime1 = GetTickCount();
	#endif

		eErr = SCardDfBufferToMainMemoryPageProgram(
													ulHandleSmartCard,   	// Handle (get from SCardConnect)
													ucBufferNr,
													ulPageAdr,
													ucErase
													);

	#ifdef MEASURE_TIME
      ulTime2 =  GetTickCount();
      ulTime2 -= ulTime1;

      StrPrintf(szText," (%d[ms])",ulTime2);
      SCRNPutTextAt(usY++,2,szText);
	#endif
	
      ErrorMessage(eErr);
      SCRNGetChar();
}


/*****************************************************************************
Description:
	 No used data for this command. The selected page from the main memory is erased
	
Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_PageErase (
									SCARDHANDLE ulHandleSmartCard
									)
{
   OKERR    eErr = NO_ERROR;
   ULONG    ulPageAdr;
	USHORT   usY ;
	#ifdef MEASURE_TIME
		ULONG    ulTime1,ulTime2;
	#endif

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Page erase");
		SCRNPutTextAt( 2, 27, "-------------------------");

		usY = 4;
		#define XPOS		24

		SCRNPutTextAt(usY, 2,"Page address[0,2047]:");
		ulPageAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_TOTAL_PAGES -1);			
		#undef XPOS


		#ifdef MEASURE_TIME
			ulTime1 = GetTickCount();
		#endif

		eErr = SCardDfPageErase(
									ulHandleSmartCard,   	
									ulPageAdr
									);

		#ifdef MEASURE_TIME
			ulTime2 =  GetTickCount() - ulTime1;
			StrPrintf(szText," (%d[ms])",ulTime2);
			SCRNPutTextAt(usY++,2,szText);
		#endif

      ErrorMessage(eErr);
      SCRNGetChar();
}


/*****************************************************************************
Description:
	 No used data for this command. The selected page from the main memory is erased
	
Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_BlockErase (
									SCARDHANDLE ulHandleSmartCard
									)
{
   OKERR    eErr = NO_ERROR;
   ULONG    ulBlockNr;
	USHORT   usY ;
	#ifdef MEASURE_TIME
		ULONG    ulTime1,ulTime2;
	#endif

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Block erase");
		SCRNPutTextAt( 2, 27, "--------------------------");

		usY = 4;
		#define XPOS		24

		SCRNPutTextAt(usY, 2,"Block number[0,255]:");
		ulBlockNr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_MAX_BLOCK_NUMBER );			
		#undef XPOS
		//.
		#ifdef MEASURE_TIME
			ulTime1 = GetTickCount();
		#endif

		eErr = SCardDfBlockErase(
									ulHandleSmartCard,   	
									ulBlockNr
									);

		#ifdef MEASURE_TIME
			ulTime2 =  GetTickCount() - ulTime1;
			StrPrintf(szText," (%d[ms])",ulTime2);
			SCRNPutTextAt(usY++,2,szText);
		#endif

      ErrorMessage(eErr);
      SCRNGetChar();
}



/*****************************************************************************
Description:
	
Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_MainMemoryPageProgramThroughBuffer (
											SCARDHANDLE ulHandleSmartCard
											)
{
   OKERR    eErr = NO_ERROR;
   BYTE     bWriteBuffer[AT45DB041_BUFFER_SIZE];
   ULONG    ulBytesToWrite;
	USHORT   usY ;
	UCHAR 	ucBufferNr;
	ULONG  	ulPageAdr;
	ULONG  	ulByteAdr;
	#ifdef MEASURE_TIME
		ULONG    ulTime1,ulTime2;
	#endif
	

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Main memory page program through buffer");
		SCRNPutTextAt( 2, 27, "------------------------------------------------------");

		usY = 4;

		#define XPOS		26
		// Select a page
		SCRNPutTextAt(usY,  2,"Page address         :");
		ulPageAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_TOTAL_PAGES -1);

		SCRNPutTextAt(usY,  2,"Select a buffer[1,2] :");
		ucBufferNr = (UCHAR)SCRNGetULongAt(usY++,XPOS,1,2);				  				// min,max

      SCRNPutTextAt(usY,  2,"Bytes to write[1,264]:");
      ulBytesToWrite = SCRNGetULongAt(usY++,XPOS,1,sizeof(bWriteBuffer));	// min,max

      SCRNPutTextAt(usY,  2,"Byte address[0,263]  :");
      ulByteAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_BUFFER_SIZE -1);

      SCRNPutTextAt(usY,  2,"Data:");
      SCRNGetTextAt(
						usY++, 16,
						(USHORT)ulBytesToWrite,
						bWriteBuffer,
						sizeof(bWriteBuffer)+1			// +1 for EOS=0 character
						);
		#undef XPOS
		//.

		#ifdef MEASURE_TIME
      ulTime1 = GetTickCount();
		#endif


		eErr = SCardDfMainMemoryPageProgramThroughBuffer (
												ulHandleSmartCard,   	// Handle (get from SCardConnect)
												bWriteBuffer,           // output buffer holding the wrtie data
												ulPageAdr,
												ulByteAdr,
												ulBytesToWrite,
												ucBufferNr
												);

		#ifdef MEASURE_TIME
      ulTime2 =  GetTickCount() - ulTime1;
      StrPrintf(szText," (%d[ms])",ulTime2);
      SCRNPutTextAt(usY++,2,szText);
		#endif
		
      ErrorMessage(eErr);
      SCRNGetChar();

}


/*****************************************************************************
Description:

Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_MainMemoryPageToBufferTransfer(
														SCARDHANDLE ulHandleSmartCard
														)
{
   OKERR    eErr = NO_ERROR;
   ULONG    ulPageAdr;
	USHORT   usY ;
	UCHAR 	ucBufferNr=1;
	#ifdef MEASURE_TIME
   ULONG    ulTime1,ulTime2;
	#endif

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Main memory page to buffer transfer");
		SCRNPutTextAt( 2, 27, "--------------------------------------------------");

		usY = 4;
		#define XPOS		24
		SCRNPutTextAt(usY, 2,"Select buffer[1,2]  :");
		ucBufferNr = (UCHAR)SCRNGetULongAt(usY++,XPOS, 1,2);				  				

		SCRNPutTextAt(usY, 2,"Page address[0,2047]:");
		ulPageAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_TOTAL_PAGES -1);			
		#undef XPOS
		
		//
		// No used data for this command. The data stored in the buffer nr. are written into the main memory.
		//
	#ifdef MEASURE_TIME
      ulTime1 = GetTickCount();
	#endif

		eErr = SCardDfMainMemoryPageToBufferTransfer(
															ulHandleSmartCard,
															ucBufferNr,
															ulPageAdr
															);
	#ifdef MEASURE_TIME
      ulTime2 =  GetTickCount() - ulTime1;
      StrPrintf(szText," (%d[ms])",ulTime2);
      SCRNPutTextAt(usY++,2,szText);
	#endif
	
      ErrorMessage(eErr);
      SCRNGetChar();

}


/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID TestAT45DB041_MainMemoryPageToBufferCompare(
											SCARDHANDLE ulHandleSmartCard
											)
{
   OKERR    eErr = NO_ERROR;
   ULONG    ulPageAdr;
	USHORT   usY ;
	UCHAR 	ucBufferNr=1;
	#ifdef MEASURE_TIME
   ULONG    ulTime1,ulTime2;
	#endif

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Main memory page to buffer compare");
		SCRNPutTextAt( 2, 27, "-------------------------------------------------");

		usY = 4;
		#define XPOS		24
		SCRNPutTextAt(usY, 2,"Select buffer[1,2]  :");
		ucBufferNr = (UCHAR)SCRNGetULongAt(usY++,XPOS, 1,2);				  				

		SCRNPutTextAt(usY, 2,"Page address[0,2047]:");
		ulPageAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_TOTAL_PAGES -1);			
		#undef XPOS
		
		//
		// No used data for this command. The data stored in the buffer nr. are written into the main memory.
		//
	#ifdef MEASURE_TIME
      ulTime1 = GetTickCount();
	#endif

		eErr = SCardDfMainMemoryPageToBufferCompare(
															ulHandleSmartCard,
															ucBufferNr,
															ulPageAdr
															);
	#ifdef MEASURE_TIME
      ulTime2 =  GetTickCount() - ulTime1;
      StrPrintf(szText," (%d[ms])",ulTime2);
      SCRNPutTextAt(usY++,2,szText);
	#endif
	
      ErrorMessage(eErr);
      SCRNGetChar();
}


/*****************************************************************************
Description:

Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestAT45DB041_AutoPageRewriteThroughBuffer(
													SCARDHANDLE ulHandleSmartCard
													)
{
   OKERR    eErr = NO_ERROR;
   ULONG    ulPageAdr;
	USHORT   usY ;
	UCHAR 	ucBufferNr=1;
	#ifdef MEASURE_TIME
   ULONG    ulTime1,ulTime2;
	#endif

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test AT45DB041 Auto page rewrite through buffer ");
		SCRNPutTextAt( 2, 27, "------------------------------------------------");

		usY = 4;
		#define XPOS		24
		SCRNPutTextAt(usY, 2,"Select buffer[1,2]  :");
		ucBufferNr = (UCHAR)SCRNGetULongAt(usY++,XPOS, 1,2);				  				

		SCRNPutTextAt(usY, 2,"Page address[0,2047]:");
		ulPageAdr = SCRNGetULongAt(usY++,XPOS, 0,AT45DB041_TOTAL_PAGES -1);			
		#undef XPOS
		
		//
		// No used data for this command. The data stored in the buffer nr. are written into the main memory.
		//
	#ifdef MEASURE_TIME
      ulTime1 = GetTickCount();
	#endif

		eErr = SCardDfAutoPageRewriteThroughBuffer(
															ulHandleSmartCard,
															ucBufferNr,
															ulPageAdr
															);
	#ifdef MEASURE_TIME
      ulTime2 =  GetTickCount() - ulTime1;
      StrPrintf(szText," (%d[ms])",ulTime2);
      SCRNPutTextAt(usY++,2,szText);
	#endif
	
      ErrorMessage(eErr);
      SCRNGetChar();


}



/*****************************************************************************
Description:

Arguments:

Return Value:

note:
*****************************************************************************/



/*****************************************************************************
* History:
* $Log: dftst041.c $
* Revision 1.8  2006/02/16 12:21:30  TBruendl
* No comment given
*
* Revision 1.7  2004/07/06 07:57:36  TBruendl
* No comment given
*
* Revision 1.6  2004/03/09 08:36:49  MPetkov
* No comment given
*
* Revision 1.5  2004/02/23 16:48:42  MPetkov
* No comment given
*
* Revision 1.4  2004/02/20 15:01:12  MPetkov
* All commands
*
* Revision 1.3  2004/02/19 14:37:48  MPetkov
* No comment given
*
* Revision 1.2  2004/02/18 16:51:23  MPetkov
* No comment given
*
* Revision 1.1  2004/02/17 18:35:10  MPetkov
* First approach
*
******************************************************************************/

