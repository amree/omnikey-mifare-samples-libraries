/*****************************************************************************
@doc            TestI2C
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------

 Test I2C-bus synchronous card functions. Called from:  \syntst\syntst.c
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
#include <scardi2c.h>         // This file has to be included after the #include <pcsc_cm.h>



USHORT PrintCdTypeTable(USHORT usY);

void DumpBuffer(
					UCHAR *pucBuffer,
					USHORT usDataLen,
					USHORT *pusY);

/*****************************************************************************/
/**  GLOBAL DECLARATIONS                                                    **/
/*****************************************************************************/
static  CHAR    szText[160] = "\0";           /* Common string for text I/O */

#define MAX_BYTE     0x000000FF
#define MAX_USHORT   0x0000FFFF
#define MAX_ULONG    0xFFFFFFFF


/*****************************************************************************
Description:
   Init according the i2c card to be used
   	
Arguments:

Return Value:
	
note:
   ! For the time being we work and test only with: ST14C02C !
*****************************************************************************/
void TestSCard_I2C_Init(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    eErr = NO_ERROR;
   USHORT   usY, usTemp;
   SCARD_I2C_CARD_PARAMETERS sCdParam;
   SCARD_I2C_TYPE Type;

      SCRNClear();
      SCRNPutTextAt( 1, 20, "TEST I2CInit");
      SCRNPutTextAt( 2, 20, "------------");

		usY = 4;
      sprintf(szText,"Handle : 0x%08X \n", ulHandleSmartCard);
      SCRNPutTextAt(usY++, 2, szText);

      // it is intentionally that the subsequent input values are not restricted
      // the correctness of the values shall be evaluated by SCardI2CInit

      SCRNPutTextAt(usY, 2,"ucNumberOfAddressBytes = ");
      sCdParam.ucNumberOfAddressBytes = (UCHAR)SCRNGetULongAt(usY++,28,0,256);

      SCRNPutTextAt(usY, 2,"ulMemorySize = ");
      sCdParam.ulMemorySize = SCRNGetULongAt(usY++,28,0,(ULONG)(-1));

      SCRNPutTextAt(usY, 2,"ucPageSize = ");
      sCdParam.ucPageSize = (UCHAR)SCRNGetULongAt(usY++,28,0,256);

		SCRNPutTextAt(usY, 2,"Type = ");

		usTemp = usY;
		usY +=2;
		usY = PrintCdTypeTable(usY);
		Type = (UCHAR)SCRNGetULongAt(usTemp,28,0,65536);		// above the table

      eErr = SCardI2CInit(
                         ulHandleSmartCard,
                         &sCdParam,
                         Type);         // !!!! Type has a priority, if NULL then sCdParam has to be initialized.


      ErrorMessage(eErr);                     // display OKERR
      SCRNGetChar();
}



/*****************************************************************************
Description:
	 Test read from the I2C bus
Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCard_I2C_ReadData(
                           SCARDHANDLE ulHandleSmartCard)
{
   OKERR       eErr = NO_ERROR;
   USHORT      usY = 4;
   BYTE        bReadBuffer[1024 * 128];
   ULONG       ulAddress;
   ULONG       ulBytesToRead;
   ULONG       ulTime1,ulTime2;

      SCRNClear();
      SCRNPutTextAt( 1, 29, "TEST I2CRead (max 256 bytes)");
      SCRNPutTextAt( 2, 29, "----------------------------");

      SCRNPutTextAt(usY, 2,"Address:");
      ulAddress = SCRNGetULongAt(usY++,23,0,128*1024);

      SCRNPutTextAt(usY, 2,"BytesToRead:");
      ulBytesToRead = SCRNGetULongAt(usY++,23,1,sizeof(bReadBuffer));

      ulTime1=GetTickCount();

      eErr = SCardI2CReadData(
                           ulHandleSmartCard,                     // ULONG
                           bReadBuffer,
                           sizeof(bReadBuffer),
                           ulAddress,
                           ulBytesToRead);

      ulTime2=GetTickCount();
      ulTime2-=ulTime1;
      StrPrintf(szText," (%dms)",ulTime2);
      SCRNPutTextAt(usY++,2,szText);

      ErrorMessage(eErr);

      usY += 1;
      SCRNPutTextAt(usY, 2,"Data Read:\n");

      usY += 1;
      if (eErr == NO_ERROR)               // Display the data received
         {
         WriteBuffer(bReadBuffer, ulBytesToRead, &usY, 0);
			// DumpBuffer( bReadBuffer,(USHORT)ulBytesToRead, &usY);					
         }
      SCRNGetChar();
   return;
}





/*****************************************************************************
Description:
	 Test write I2C card data. Input of the test parameters

Arguments:

Return Value:
	
note:
*****************************************************************************/
VOID TestSCard_I2C_WriteData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR    eErr = NO_ERROR;
   USHORT   usY = 4;
   BYTE     bWriteBuffer[1025];
   ULONG    ulAddress;
   ULONG    ulBytesToWrite;
   ULONG    ulTime1,ulTime2;

      SCRNClear();
      SCRNPutTextAt( 1, 27, "TEST I2C WriteData");
      SCRNPutTextAt( 2, 27, "------------------");

      SCRNPutTextAt(usY,   2,"BytesToWrite:");
      ulBytesToWrite = SCRNGetULong(1,sizeof(bWriteBuffer));

      SCRNPutTextAt(++usY, 2,"Write Address:");
      ulAddress = SCRNGetULongAt(usY++,16,0,0x20000);			// Support for AT24C1024

      SCRNPutTextAt(usY,   2,"Data:");
      SCRNGetTextAt(usY++, 16,(USHORT)ulBytesToWrite, bWriteBuffer, sizeof(bWriteBuffer));	

      ulTime1=GetTickCount();

      eErr = SCardI2CWriteData(
   							   ulHandleSmartCard,
   							   bWriteBuffer,           // output buffer holding the wrtie data
                           sizeof(bWriteBuffer),
   							   ulAddress,
                           ulBytesToWrite);

      ulTime2=GetTickCount();
      ulTime2-=ulTime1;
      StrPrintf(szText," (%dms)",ulTime2);
      SCRNPutTextAt(usY++,2,szText);

      ErrorMessage(eErr);
      SCRNGetChar();
}



/*****************************************************************************
Description:

Arguments:
		

Return Value:
note:
*****************************************************************************/
void DumpBuffer(
					UCHAR *pucBuffer,
					USHORT usDataLen,
					USHORT *pusY)
{
	char HexStr[2+1];
	int i;
		for(i=0; i< usDataLen; i++)
			{
			MEM_BinToHexString(
									(pucBuffer +i), 1,		// Data and Size,
									HexStr, 2);				  	// String and Size
			if (i%16 == 0)
				SCRNPutTextAt( ++(*pusY), 1, " ");		// Next printf occurs at the next row
			printf("%s ",HexStr);						  	// print the converted 2 hex.chars
			}
}



/*****************************************************************************
Description:
	Display all card types we know for the moment  (in two columns x offest =20)
	
Arguments:
	usY   row
	usX	column	

Return Value:
	The first free column  after the table
	
note:
*****************************************************************************/
USHORT PrintCdTypeTable(USHORT usY)
{
USHORT y,x;

	y = usY;
	x = 1;
	SCRNPutTextAt(y++, x,"NO PREDEFINED CARD=0");
	SCRNPutTextAt(y++, x,"ST14C02C=1 ");
	SCRNPutTextAt(y++, x,"ST14C04C=2 ");
	SCRNPutTextAt(y++, x,"ST14E32 =3 ");
	SCRNPutTextAt(y++, x,"M14C04  =4 ");
	SCRNPutTextAt(y++, x,"M14C16  =5 ");
	SCRNPutTextAt(y++, x,"M14C32  =6 ");
	SCRNPutTextAt(y++, x,"M14C64  =7 ");
	SCRNPutTextAt(y++, x,"M14128  =8 ");
	SCRNPutTextAt(y++, x,"M14256  =9 ");
	SCRNPutTextAt(y++, x,"GFM2K   =10");
	SCRNPutTextAt(y++, x,"GM4K    =11");
	SCRNPutTextAt(y++, x,"GFM32K  =12");

	y = usY;
	x = 22;
	SCRNPutTextAt(y++, x,"	AT24C01A =13");
	SCRNPutTextAt(y++, x,"	AT24C02  =14");
	SCRNPutTextAt(y++, x,"	AT24C04  =15");
	SCRNPutTextAt(y++, x,"	AT24C08  =16");
	SCRNPutTextAt(y++, x,"	AT24C16  =17");
	SCRNPutTextAt(y++, x,"	AT24C164 =18");
	SCRNPutTextAt(y++, x,"	AT24C32  =19");
	SCRNPutTextAt(y++, x,"	AT24C64  =20");
	SCRNPutTextAt(y++, x,"	AT24C128 =21");
	SCRNPutTextAt(y++, x,"	AT24C256 =22");
	SCRNPutTextAt(y++, x,"	AT24CS128=23");
	SCRNPutTextAt(y++, x,"	AT24CS256=24");
	SCRNPutTextAt(y++, x,"	AT24C512 =25");
	SCRNPutTextAt(y++, x,"	AT24C1024 =26");

return y;
}


