/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/smtst/rcs/smtst.c $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF

*-----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
******************************************************************************/

#include <okos.h>
#if defined S_WNT
   #include <windows.h>
   #include <stdlib.h>
   #include <stdio.h>
#endif

#include <ok.h>
#include <scrn.h>
#include <str.h>
#include <mem.h>
#include <winscard.h>
#include "scardsm.h"


#define AT88SC153_USER_ZONES 							3
#define AT88SC153_USER_ZONE_LENGTH					64
#define AT88SC1608_USER_ZONES 	  					8
#define AT88SC1608_USER_ZONE_LENGTH					256
#define AT88SC1608_CONFIG_ZONE_LENGTH				128

#define AT88SC10X_MAXSIZE 1600


//
// Local function prototypes
//
VOID main(VOID);

VOID Test_SCardSmInit(
	 				  		SCARDHANDLE ulHandleSmartCard
	 				  		);

VOID Test_SCardSmReadUserZone(
	 						SCARDHANDLE ulHandleSmartCard
	 						);

VOID Test_SCardSmReadConfigurationZone(
												SCARDHANDLE ulHandleSmartCard
												);

VOID Test_SCardSmWriteConfigurationZone(
												SCARDHANDLE ulHandleSmartCard
												);

VOID Test_SCardSmWriteUserZone(
									SCARDHANDLE ulHandleSmartCard
									);

VOID Test_SCardSmReadFuses(
									SCARDHANDLE ulHandleSmartCard
									);

VOID Test_SCardSmWriteFuses(
									SCARDHANDLE ulHandleSmartCard
									);


VOID Test_SCardSmUseSlaveAddress(void);

BOOL SelectReader(VOID);

GPCHAR StrError(
					OKERR eErr
					);


VOID TestSCardConnect(VOID);

VOID TestSCardReconnect(VOID);

VOID TestSCardDisconnect(VOID);

VOID HandleError(
					DWORD dwErrorFlags
					);

VOID WriteBuffer(
					GPBYTE pbBuffer,
					ULONG ulLength,
					GPUSHORT pusLineNumb,
					ULONG ulPos
					);

VOID ErrorMessage(
					OKERR eErr
					);

VOID Test_SCardSmVerifyPassword(
									SCARDHANDLE ulHandleSmartCard
									);

BOOL AskContinue(
					PUSHORT 	pusY,
					USHORT 	usX
					);

VOID Test_SCardSmVerifyAuthentication(
												SCARDHANDLE ulHandleSmartCard
												);

VOID Test_SCardSmInitAuthentication(
												SCARDHANDLE ulHandleSmartCard
												);

//ct->
VOID Test_SCardSmAT88SC10xCompareSc(
												SCARDHANDLE ulHandleSmartCard
												);
VOID Test_SCardSmAT88SC10xErase(
												SCARDHANDLE ulHandleSmartCard
												);
VOID Test_SCardSmAT88SC10xEraseAz(
												SCARDHANDLE ulHandleSmartCard
												);
VOID Test_SCardSmAT88SC10xRead(
												SCARDHANDLE ulHandleSmartCard
												);
VOID Test_SCardSmAT88SC10xWrite(
												SCARDHANDLE ulHandleSmartCard
												);
VOID Test_SCardSmAT88SC10xBlowFuse(
												SCARDHANDLE ulHandleSmartCard
												);
VOID Test_SCardSmAT88SC10xSetFusPin(
												SCARDHANDLE ulHandleSmartCard
												);
//<-ct

#define MAX_BYTE     0x000000FF
#define MAX_USHORT   0x0000FFFF
#define MAX_ULONG    0xFFFFFFFF


static  CHAR    szText[160] = "\0";           /* Common string for text I/O */
static  BYTE    bInBuffer[512];
static  BYTE    bOutBuffer[512];
static  BYTE    szCardReader[128] = "\0";

SCARDCONTEXT    hContext = 0xFFFFFFFF;
SCARDHANDLE     hCard    = 0xFFFFFFFF;


SCARD_SECURE_MEMORY_TYPE   enCurrentSmType;           // @parm in  | Type of the DataFlash

const char szAT88SC1608[]	= "AT88SC1608";
const char szAT88SC153[]	= "AT88SC153";
static char *pszCurrentSmCard = " NOT INITIALIZED !";

static ULONG ulMaxUserZones, ulMaxUserZoneLen, ulMaxConfigZoneLen;

BOOL  _fSmLibrarySecureCodeVerified = FALSE;				// flag that secure code is verified


/*****************************************************************************
Description:
	Entry point
	
Arguments:

Return Value:

note:
*****************************************************************************/
VOID main(VOID)
   {
   USHORT  usInput;
   USHORT  usLine;
   DWORD   dwErrorFlags = 0;

   SCRNInit();
   dwErrorFlags = SCardEstablishContext(
                                       SCARD_SCOPE_USER,
                                       NULL,
                                       NULL,
                                       &hContext
													);
   if (dwErrorFlags != SCARD_S_SUCCESS)
      {
      HandleError(dwErrorFlags);
      goto L_ExitMain;
      }

   if (SelectReader() == FALSE)
      {
      goto L_ExitMain;
      }

	do {
      SCRNClear();
      SCRNPutTextAt( 1, 5, "Test program for synchronous SecureMemory cards :");
      SCRNPutTextAt( 2, 5, "-------------------------------------------------");
      usLine=4;
      SCRNPutTextAt(usLine++, 5, "11)  TestSCardConnect");
      SCRNPutTextAt(usLine++, 5, "12)  TestSCardReconnect");
      SCRNPutTextAt(usLine++, 5, "13)  TestSCardDisconnect");
		usLine++;
		SCRNPutTextAt(usLine++, 5, "21) Init SecureMemory card type (to be called first)");
		usLine++;
		SCRNPutTextAt(usLine++, 5, " SecureMemory Test Commands (AT88SC153/AT88SC1608):");
		SCRNPutTextAt(usLine++, 5, "----------------------------------------------------");
		SCRNPutTextAt(usLine++, 5, "22) Read  User Zone             23) Write User Zone");
		SCRNPutTextAt(usLine++, 5, "24) Read  Configuration Zone    25) Write Configuration Zone");
		SCRNPutTextAt(usLine++, 5, "26) Read Fuses                  27) Write Fuses");
		SCRNPutTextAt(usLine++, 5, "28) Use Slave Address (DEVICE_CONFIGURATION_REG.0x18 must be init before!)");
		SCRNPutTextAt(usLine++, 5, "29) Verify Password ");
		SCRNPutTextAt(usLine++, 5, "30) Init Authentication         31) Verify Authentication");
		usLine++;
		//ct->
		SCRNPutTextAt(usLine++, 5, " SecureMemory Test Commands (AT88SC101/AT88SC102/AT88SC1003):");
		SCRNPutTextAt(usLine++, 5, "---------------------------------------------------");
		SCRNPutTextAt(usLine++, 5, "32) Compare SC               33) Blow Fuse   34) Erase");
		SCRNPutTextAt(usLine++, 5, "35) Erase Application Zone   36) Read        37) Write");
		SCRNPutTextAt(usLine++, 5, "38) Set FUS Pin");
		//<-ct

		usLine++;
      SCRNPutTextAt(usLine++, 5, "99) Quit");
      SCRNPutTextAt(usLine++, 5, "Selection:");

      switch (usInput = SCRNGetUShort(1, 99))
         {
         case 11 : TestSCardConnect()   ;break;
         case 12 : TestSCardReconnect() ;break;
			case 13 : TestSCardDisconnect();break;

			//------------------------------------------
			case 21 : Test_SCardSmInit(hCard);	break;

			case 22 : Test_SCardSmReadUserZone(hCard);	break;
			case 23 : Test_SCardSmWriteUserZone(hCard); 	break;

			case 24 : Test_SCardSmReadConfigurationZone(hCard);	break;
			case 25 : Test_SCardSmWriteConfigurationZone(hCard); 	break;

			case 26 : Test_SCardSmReadFuses(hCard);  			break;
			case 27 : Test_SCardSmWriteFuses(hCard);  			break;

			case 28 : Test_SCardSmUseSlaveAddress();  	break;
			case 29 : Test_SCardSmVerifyPassword(hCard);  	break;

			case 30 : Test_SCardSmInitAuthentication(hCard);  	break;
			case 31 : Test_SCardSmVerifyAuthentication(hCard);  	break;

//ct->
			case 32 : Test_SCardSmAT88SC10xCompareSc(hCard); break;
			case 33 : Test_SCardSmAT88SC10xBlowFuse(hCard); break;
			case 34 : Test_SCardSmAT88SC10xErase(hCard); break;
			case 35 : Test_SCardSmAT88SC10xEraseAz(hCard); break;
			case 36 : Test_SCardSmAT88SC10xRead(hCard); break;
			case 37 : Test_SCardSmAT88SC10xWrite(hCard); break;
			case 38 : Test_SCardSmAT88SC10xSetFusPin(hCard); break;
//<-ct
         }

		if (usInput != 99)
			{
			SCRNPutTextAt(23,1,"< Press any key to continue >");
			SCRNGetChar();
			}
      }
   while (usInput != 99);


   SCRNClear();
   SCRNExit();

L_ExitMain:
   if (hCard != 0xFFFFFFFF)
      SCardDisconnect(hCard,SCARD_LEAVE_CARD);

   if (hContext != 0xFFFFFFFF)
      SCardReleaseContext(hContext);


   exit(CODE_0);
}



/*****************************************************************************
Description:
To be called first
	
Arguments:

Return Value:

note:
*****************************************************************************/
VOID Test_SCardSmInit(
							SCARDHANDLE	ulHandleSmartCard
							)
{
   OKERR 	lStatus = NO_ERROR;
	USHORT  	usInput;
	USHORT 	usY;


		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test SCardSmInit");
		SCRNPutTextAt( 2, 27, "----------------");
	
		sprintf(szText,"Handle  : 0x%08X \n", ulHandleSmartCard);
		SCRNPutTextAt(4, 2, szText);

		do	{
			usY = 6;

			SCRNPutTextAt( usY++, 5, " 1) AT88SC153 ");
			SCRNPutTextAt( usY++, 5, " 2) AT88SC1608");
//ct->
			SCRNPutTextAt( usY++, 5, " 3) AT88SC101 ");
			SCRNPutTextAt( usY++, 5, " 4) AT88SC102 ");
			SCRNPutTextAt( usY++, 5, " 5) AT88SC1003 ");
//<-ct

			SCRNPutTextAt( usY, 5, "Selection: ");
			switch (usInput = SCRNGetUShort(1,5/*ct 2*/))
				{
				default:
				case 1:	
					lStatus = SCardSmInit(
												ulHandleSmartCard,
												AT88SC153
												);	
					enCurrentSmType  	= AT88SC153;
					pszCurrentSmCard 	= " AT88SC153 ";

					ulMaxUserZones		= AT88SC153_USER_ZONES      ;
					ulMaxUserZoneLen 	= AT88SC153_USER_ZONE_LENGTH ;
					ulMaxConfigZoneLen= AT88SC153_USER_ZONE_LENGTH ;
					break;

				case 2:	
					lStatus = SCardSmInit(
												ulHandleSmartCard,
												AT88SC1608
												);	
					enCurrentSmType  	= AT88SC1608;
					pszCurrentSmCard 	= " AT88SC1608 ";

					ulMaxUserZones 	= AT88SC1608_USER_ZONES   ;
					ulMaxUserZoneLen 	= AT88SC1608_USER_ZONE_LENGTH ;
					ulMaxConfigZoneLen= AT88SC1608_CONFIG_ZONE_LENGTH ;
					break;
//ct->
				case 3:	
					lStatus = SCardSmInit(
												ulHandleSmartCard,
												AT88SC101
												);	
					enCurrentSmType  	= AT88SC101;
					pszCurrentSmCard 	= " AT88SC101 ";
					break;

				case 4:	
					lStatus = SCardSmInit(
												ulHandleSmartCard,
												AT88SC102
												);	
					enCurrentSmType  	= AT88SC102;
					pszCurrentSmCard 	= " AT88SC102 ";
					break;

				case 5:	
					lStatus = SCardSmInit(
												ulHandleSmartCard,
												AT88SC1003
												);	
					enCurrentSmType  	= AT88SC1003;
					pszCurrentSmCard 	= " AT88SC1003 ";
					break;
//<-ct
				}

			SCRNPutTextAt( usY, 20, pszCurrentSmCard);			// print the selection
			}
		while ( 	 usInput !=1
				 && usInput !=2
//ct->
				 && usInput !=3
				 && usInput !=4
				 && usInput !=5
//<-ct
				);

	ErrorMessage(lStatus);
}




/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmReadUserZone(
									SCARDHANDLE ulHandleSmartCard
									)
{
   OKERR 	lStatus = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[MAX_USER_ZONE_LENGTH];	
   ULONG  	ulUserZone;
   ULONG  	ulByteAdr;
	ULONG    ulBytesToRead ;
	ULONG    ulBytesRead;

		SCRNClear();
		SCRNPutTextAt( usY=1, 20, "Test Read User Zone");
		SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "------------------------------------");

		usY = 4;
		#define XPOS	  	24

		SCRNPutTextAt(usY, 2,"Zone address   :");
		ulUserZone = SCRNGetULongAt(usY++,XPOS, 0,ulMaxUserZones -1);

		SCRNPutTextAt(usY, 2,"Byte address   :");
		ulByteAdr = SCRNGetULongAt(usY++,XPOS, 0,ulMaxUserZoneLen -1);
	
		SCRNPutTextAt(usY, 2,"Bytes to read:");
		ulBytesToRead = SCRNGetULongAt(usY++,XPOS, 1,ulMaxUserZoneLen);
	
		#undef XPOS
		
		lStatus = SCardSmReadUserZone(
								  		ulHandleSmartCard,   	
										abData,        		// Pointer to the read buffer
										sizeof(abData),   	// Size of the read buffer
								  		ulUserZone,				// User zone to read from
										ulByteAdr,   	   	// byta address in a page
										ulBytesToRead,			// Number of bytes to be read
										&ulBytesRead			//out: Number of bytes actually read
										);

		if (lStatus == NO_ERROR)
			{
			usY += 2;
			WriteBuffer(
						abData,
						ulBytesRead,
						&usY,
						0
						);
			}

		ErrorMessage(lStatus);
							
}



/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmReadConfigurationZone(
												SCARDHANDLE ulHandleSmartCard
												)
{
   OKERR 	lStatus = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[MAX_USER_ZONE_LENGTH];		// Check the lagerst zone size supported up to now AT88SC1608
   ULONG  	ulByteAdr;
	ULONG    ulBytesToRead;
	ULONG    ulBytesRead;

		SCRNClear();
		SCRNPutTextAt( usY=1, 20, "Test Read Configuration Zone");
		SCRNPutTextAt( usY++, 60, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "------------------------------------");

		usY = 4;
		#define XPOS	  	24

		SCRNPutTextAt(usY, 2,"Byte address   :");
		ulByteAdr = SCRNGetULongAt(usY++,XPOS, 0,ulMaxConfigZoneLen -1);
	
		SCRNPutTextAt(usY, 2,"Bytes to read:");
		ulBytesToRead = SCRNGetULongAt(usY++,XPOS, 1,ulMaxConfigZoneLen);
	
		#undef XPOS
		
		lStatus = SCardSmReadConfigurationZone(
													ulHandleSmartCard,   	
													abData,
													sizeof(abData),
													ulByteAdr,
													ulBytesToRead,
													&ulBytesRead
													);
		if (lStatus == NO_ERROR)
			{
			usY += 2;
			WriteBuffer(
						abData,
						ulBytesRead,
						&usY,
						0
						);
			}
		ErrorMessage(lStatus);
}







/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmWriteUserZone(
									SCARDHANDLE ulHandleSmartCard
									)
{
   OKERR 	lStatus = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[MAX_USER_ZONE_LENGTH];			// the one from at88sc1608
   ULONG  	ulUserZone;
   ULONG  	ulByteAdr;
	ULONG    ulBytesToWrite;
	ULONG    ulBytesWritten;

		SCRNClear();
		SCRNPutTextAt( usY=1, 20, "Test Write User Zone");
		SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "------------------------------------");

		usY = 4;
		#define XPOS	  	24

		SCRNPutTextAt(usY, 2,"Zone address   :");
		ulUserZone = SCRNGetULongAt(usY++,XPOS, 0,ulMaxUserZones -1);

		SCRNPutTextAt(usY, 2,"Write address :");
		ulByteAdr = SCRNGetULongAt(usY++,XPOS,  0,ulMaxUserZoneLen -1);

		SCRNPutTextAt(usY, 2,"Bytes to write:");
		ulBytesToWrite = SCRNGetULongAt(usY++,XPOS, 1,ulMaxUserZoneLen);
		
		#undef XPOS
		
		SCRNPutTextAt(usY, 2,"Data:");
		SCRNGetTextAt(
						usY++, 16,
						(USHORT)ulBytesToWrite,
						abData,
						sizeof(abData)
						);
		
		lStatus = SCardSmWriteUserZone(
											ulHandleSmartCard,   	
											abData,        				
											ulUserZone,				
											ulByteAdr,   	   			
											ulBytesToWrite,				
											&ulBytesWritten  				
											);

		ErrorMessage(lStatus);
}




/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmWriteConfigurationZone(
												SCARDHANDLE ulHandleSmartCard
												)
{
   OKERR 	lStatus = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[MAX_USER_ZONE_LENGTH];			// the one from at88sc1608
   ULONG  	ulByteAdr;
	ULONG    ulBytesToWrite;
	ULONG    ulBytesWritten;

		SCRNClear();
		SCRNPutTextAt( usY=1, 20, "Test SCardSmWriteConfigurationZone");
		SCRNPutTextAt( usY++, 60, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "------------------------------------");

		usY = 4;
		#define XPOS	  	24

		SCRNPutTextAt(usY, 2,"Write address :");
		ulByteAdr = SCRNGetULongAt(usY++,XPOS,  0,ulMaxConfigZoneLen -1);

		SCRNPutTextAt(usY, 2,"Bytes to write:");
		ulBytesToWrite = SCRNGetULongAt(usY++,XPOS, 1,ulMaxConfigZoneLen);
		
		#undef XPOS
		
		SCRNPutTextAt(usY, 2,"Data:");
		SCRNGetTextAt(
						usY++, 16,
						(USHORT)ulBytesToWrite,
						abData,
						sizeof(abData)
						);
		
		if (AskContinue(&usY,2) == TRUE )
			{
			lStatus = SCardSmWriteConfigurationZone(
														ulHandleSmartCard,   	
														abData,        				
														ulByteAdr,   	   			
														ulBytesToWrite,				
														&ulBytesWritten  				
														);
			}
		else
			{
			SCRNPutTextAt(usY, 2,"Command discarded.");
			}


		ErrorMessage(lStatus);
}



/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmUseSlaveAddress(void)
{
   OKERR 	lStatus = NO_ERROR;
   USHORT 	usY;
	UCHAR		ucSlaveAddress;

		SCRNClear();
		SCRNPutTextAt( usY=1, 20, "Test Use Slave Address (!)");
		SCRNPutTextAt( usY++, 60, pszCurrentSmCard);
		SCRNPutTextAt( usY++, 20, "------------------------------------");

		SCRNPutTextAt( usY++, 5, "Attention! AT88SC153 only! Before using this command ");
		SCRNPutTextAt( usY++, 5, "DEVICE_CONFIGURATION_REGISTER at adr 0x18 must be init LBb [b3..b0]");
		SCRNPutTextAt( usY++, 5, "equal to the MSb of the slave address.");

		SCRNPutTextAt( usY++, 5, "In case of error, call again this command with the default slave adr=0xb0 ");
		SCRNPutTextAt( usY++, 5, "Or re-init the library with SCardSmInit() menu pt.21) ");

		usY++;

		switch (enCurrentSmType)
			{
			case AT88SC153:

				#define XPOS 24
				SCRNPutTextAt(usY, 2,"Slave address :");
				ucSlaveAddress = (UCHAR)SCRNGetULongAt(usY++,XPOS, 0, 0xf0);
				#undef XPOS
				
				if (AskContinue(&usY,2) == TRUE)
					{
					lStatus = SCardSmUseSlaveAddress(
															ucSlaveAddress
															);
					}
				else
					{
					SCRNPutTextAt(usY, 2,"Command discarded.");
					}
				break;
										
			case AT88SC1608:
				SCRNPutTextAt(usY, 2,"Command not supported for AT88SC1608.");
				break;
			}

		ErrorMessage(lStatus);
}













/*****************************************************************************
Description:

Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestSCardConnect(VOID)
   {
   DWORD dwErrorFlags;
   DWORD dwShareMode;
   DWORD dwPreferredProtocols;
   DWORD dwActiveProtocols;

		SCRNClear();
		SCRNPutTextAt( 1, 29, "SCardConnect");
		SCRNPutTextAt( 2, 29, "------------");

		dwShareMode = SCARD_SHARE_SHARED;
		dwPreferredProtocols = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;

		dwErrorFlags = SCardConnect(
											hContext,
											szCardReader,
											dwShareMode,
											dwPreferredProtocols,
											&hCard,
											&dwActiveProtocols
											);

		SCRNSetCursorPosition(18,1);
		if (dwErrorFlags == SCARD_S_SUCCESS)
			{
			switch (dwActiveProtocols)
				{
				case SCARD_PROTOCOL_T0 :
					sprintf(szText,"Used protocol = SCARD_PROTOCOL_T0");
					break;

				case SCARD_PROTOCOL_T1 :
					sprintf(szText,"Used protocol = SCARD_PROTOCOL_T1");
					break;

				default :
					sprintf(szText,"Unknown protocol");
					break;
				}
			SCRNPutText(szText);
			}

		SCRNSetCursorPosition(19,1);
		HandleError(dwErrorFlags);

   return;
   }




/*****************************************************************************
Description:

Arguments:

Return Value:

note:
*****************************************************************************/
VOID TestSCardDisconnect(VOID)
   {
   DWORD dwErrorFlags;
   ULONG ulInput;
   DWORD dwDisposition;

   SCRNClear();
   SCRNPutTextAt( 1, 29, "SCardDisconnect");
   SCRNPutTextAt( 2, 29, "---------------");

   SCRNPutTextAt( 5 ,1, "(1) SCARD_LEAVE_CARD");
   SCRNPutTextAt( 6, 1, "(2) SCARD_RESET_CARD");
   SCRNPutTextAt( 7, 1, "(3) SCARD_UNPOWER_CARD");
   SCRNPutTextAt( 8, 1, "(4) SCARD_EJECT_CARD");
   SCRNPutTextAt( 9, 1, "dwDisposition =>");
   ulInput = SCRNGetULong(1,4);
   switch (ulInput)
      {
      case 1: dwDisposition = SCARD_LEAVE_CARD;   break;
      case 2: dwDisposition = SCARD_RESET_CARD;   break;
      case 3: dwDisposition = SCARD_UNPOWER_CARD; break;
      case 4: dwDisposition = SCARD_EJECT_CARD;   break;
      default:dwDisposition = SCARD_LEAVE_CARD;   break;    // MP010322 to avoid the warning
      }

   dwErrorFlags = SCardDisconnect(hCard,
                                  dwDisposition);

   SCRNSetCursorPosition(20,1);
   HandleError(dwErrorFlags);

   return;
   }



VOID TestSCardReconnect(VOID)
   {
   DWORD dwErrorFlags;
   ULONG ulInput;
   DWORD dwShareMode;
   DWORD dwPreferredProtocols;
   DWORD dwActiveProtocols;
   DWORD dwInitialization;


   SCRNClear();
   SCRNPutTextAt( 1, 29, "SCardReconnect");
   SCRNPutTextAt( 2, 29, "--------------");
   dwShareMode = SCARD_SHARE_SHARED;

   dwPreferredProtocols = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;

   SCRNPutTextAt(5 ,1, "(1) SCARD_LEAVE_CARD");
   SCRNPutTextAt(6, 1, "(2) SCARD_RESET_CARD");
   SCRNPutTextAt(7, 1, "(3) SCARD_UNPOWER_CARD");
   SCRNPutTextAt( 8, 1, "dwInitialization => ");
   ulInput = SCRNGetULong(1,3);
   switch (ulInput)
      {
      case 1: dwInitialization = SCARD_LEAVE_CARD;   break;
      case 2: dwInitialization = SCARD_RESET_CARD;   break;
      case 3: dwInitialization = SCARD_UNPOWER_CARD; break;

      default:dwInitialization = SCARD_LEAVE_CARD;   break;      // MP010322+
      }


   dwErrorFlags = SCardReconnect(hCard,
                                 dwShareMode,
                                 dwPreferredProtocols,
                                 dwInitialization,
                                 &dwActiveProtocols);

   SCRNSetCursorPosition(20,1);
   if (dwErrorFlags == SCARD_S_SUCCESS)
      {
      switch (dwActiveProtocols)
         {
         case SCARD_PROTOCOL_T0 :
            printf("dwActiveProtocols = SCARD_PROTOCOL_T0\n");
            break;

         case SCARD_PROTOCOL_T1 :
            printf("dwActiveProtocols = SCARD_PROTOCOL_T1\n");
            break;

         default :
            printf("dwActiveProtocols = %ld",dwActiveProtocols);
            break;
         }
      }

   SCRNSetCursorPosition(19,1);
   HandleError(dwErrorFlags);

//   SCRNPutTextAt(23,1,"< Press any key to continue >");
//   SCRNGetChar();
   return;
   }





/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID HandleError(
					DWORD dwErrorFlags
					)
   {
   BYTE ErrorMsg[256];

   switch (dwErrorFlags)
      {
      case SCARD_E_BAD_SEEK:
         sprintf(ErrorMsg,"An error occurred in setting the smart card file object pointer.");
         break;
      case SCARD_E_CANCELLED:
         sprintf(ErrorMsg,"The action was canceled by an SCardCancel request.");
         break;
      case SCARD_E_CANT_DISPOSE:
         sprintf(ErrorMsg,"The system could not dispose of the media in the requested manner.");
         break;
      case SCARD_E_CARD_UNSUPPORTED:
         sprintf(ErrorMsg,"The smart card does not meet minimal requirements for support.");
         break;
      case SCARD_E_CERTIFICATE_UNAVAILABLE:
         sprintf(ErrorMsg,"The requested certificate could not be obtained.");
         break;
      case SCARD_E_COMM_DATA_LOST:
         sprintf(ErrorMsg,"A communications error with the smart card has been detected.");
         break;
      case SCARD_E_DIR_NOT_FOUND:
         sprintf(ErrorMsg,"The specified directory does not exist in the smart card.");
         break;
      case SCARD_E_DUPLICATE_READER:
         sprintf(ErrorMsg,"The reader driver didn't produce a unique reader name.");
         break;
      case SCARD_E_FILE_NOT_FOUND:
         sprintf(ErrorMsg,"The specified file does not exist in the smart card.");
         break;
      case SCARD_E_ICC_CREATEORDER:
         sprintf(ErrorMsg,"The requested order of object creation is not supported.");
         break;
      case SCARD_E_ICC_INSTALLATION:
         sprintf(ErrorMsg,"No primary provider can be found for the smart card.");
         break;
      case SCARD_E_INSUFFICIENT_BUFFER:
         sprintf(ErrorMsg,"The data buffer for returned data is too small for the returned data.");
         break;
      case SCARD_E_INVALID_ATR:
         sprintf(ErrorMsg,"An ATR string obtained from the registry is not a valid ATR string.");
         break;
      case SCARD_E_INVALID_CHV:
         sprintf(ErrorMsg,"The supplied PIN is incorrect.");
         break;
      case SCARD_E_INVALID_HANDLE:
         sprintf(ErrorMsg,"The supplied handle was invalid.");
         break;
      case SCARD_E_INVALID_PARAMETER:
         sprintf(ErrorMsg,"One or more of the supplied parameters could not be properly interpreted.");
         break;
      case SCARD_E_INVALID_TARGET:
         sprintf(ErrorMsg,"Registry startup information is missing or invalid.");
         break;
      case SCARD_E_INVALID_VALUE:
         sprintf(ErrorMsg,"One or more of the supplied parameter values could not be properly interpreted.");
         break;
      case SCARD_E_NO_ACCESS:
         sprintf(ErrorMsg,"Access is denied to the file.");
         break;
      case SCARD_E_NO_DIR:
         sprintf(ErrorMsg,"The supplied path does not represent a smart card directory.");
         break;
      case SCARD_E_NO_FILE:
         sprintf(ErrorMsg,"The supplied path does not represent a smart card file.");
         break;
      case SCARD_E_NO_MEMORY:
         sprintf(ErrorMsg,"Not enough memory available to complete this command.");
         break;
      case SCARD_E_NO_READERS_AVAILABLE:
         sprintf(ErrorMsg,"No smart card reader is available.");
         break;
      case SCARD_E_NO_SERVICE:
         sprintf(ErrorMsg,"The smart card resource manager is not running.");
         break;
      case SCARD_E_NO_SMARTCARD:
         sprintf(ErrorMsg,"The operation requires a smart card, but no smart card is currently in the device.");
         break;
      case SCARD_E_NO_SUCH_CERTIFICATE:
         sprintf(ErrorMsg,"The requested certificate does not exist.");
         break;
      case SCARD_E_NOT_READY:
         sprintf(ErrorMsg,"The reader or card is not ready to accept commands.");
         break;
      case SCARD_E_NOT_TRANSACTED:
         sprintf(ErrorMsg,"An attempt was made to end a non-existent transaction.");
         break;
      case SCARD_E_PCI_TOO_SMALL:
         sprintf(ErrorMsg,"The PCI receive buffer was too small.");
         break;
      case SCARD_E_PROTO_MISMATCH:
         sprintf(ErrorMsg,"The requested protocols are incompatible with the protocol currently in use with the card.");
         break;
      case SCARD_E_READER_UNAVAILABLE:
         sprintf(ErrorMsg,"The specified reader is not currently available for use.");
         break;
      case SCARD_E_READER_UNSUPPORTED:
         sprintf(ErrorMsg,"The reader driver does not meet minimal requirements for support.");
         break;
      case SCARD_E_SERVICE_STOPPED:
         sprintf(ErrorMsg,"The smart card resource manager has shut down.");
         break;
      case SCARD_E_SHARING_VIOLATION:
         sprintf(ErrorMsg,"The smart card cannot be accessed because of other outstanding connections.");
         break;
      case SCARD_E_SYSTEM_CANCELLED:
         sprintf(ErrorMsg,"The action was canceled by the system, presumably to log off or shut down.");
         break;
      case SCARD_E_TIMEOUT:
         sprintf(ErrorMsg,"The user-specified timeout value has expired.");
         break;
      case SCARD_E_UNEXPECTED:
         sprintf(ErrorMsg,"An unexpected card error has occurred.");
         break;
      case SCARD_E_UNKNOWN_CARD:
         sprintf(ErrorMsg,"The specified smart card name is not recognized.");
         break;
      case SCARD_E_UNKNOWN_READER:
         sprintf(ErrorMsg,"The specified reader name is not recognized.");
         break;
      case SCARD_E_UNKNOWN_RES_MNG:
         sprintf(ErrorMsg,"An unrecognized error code was returned from a layered component.");
         break;
      case SCARD_E_UNSUPPORTED_FEATURE:
         sprintf(ErrorMsg,"This smart card does not support the requested feature.");
         break;
      case SCARD_E_WRITE_TOO_MANY:
         sprintf(ErrorMsg,"An attempt was made to write more data than would fit in the target object.");
         break;
      case SCARD_F_COMM_ERROR:
         sprintf(ErrorMsg,"An internal communications error has been detected.");
         break;
      case SCARD_F_INTERNAL_ERROR:
         sprintf(ErrorMsg,"An internal consistency check failed.");
         break;
      case SCARD_F_UNKNOWN_ERROR:
         sprintf(ErrorMsg,"An internal error has been detected, but the source is unknown.");
         break;
      case SCARD_F_WAITED_TOO_LONG:
         sprintf(ErrorMsg,"An internal consistency timer has expired.");
         break;
      case SCARD_P_SHUTDOWN:
         sprintf(ErrorMsg,"The operation has been aborted to allow the server application to exit.");
         break;
      case SCARD_S_SUCCESS:
         sprintf(ErrorMsg,"SCARD_S_SUCCESS");
         break;
      case SCARD_W_CANCELLED_BY_USER:
         sprintf(ErrorMsg,"The action was cancelled by the user.");
         break;
      case SCARD_W_CHV_BLOCKED:
         sprintf(ErrorMsg,"The card cannot be accessed because the maximum number of PIN entry attempts has been reached.");
         break;
      case SCARD_W_EOF:
         sprintf(ErrorMsg,"The end of the smart card file has been reached.");
         break;
      case SCARD_W_REMOVED_CARD:
         sprintf(ErrorMsg,"The smart card has been removed, so that further communication is not possible.");
         break;
      case SCARD_W_RESET_CARD:
         sprintf(ErrorMsg,"The smart card has been reset, so any shared state information is invalid.");
         break;
      case SCARD_W_SECURITY_VIOLATION:
         sprintf(ErrorMsg,"Access was denied because of a security violation.");
         break;
      case SCARD_W_UNPOWERED_CARD:
         sprintf(ErrorMsg,"Power has been removed from the smart card, so that further communication is not possible.");
         break;
      case SCARD_W_UNRESPONSIVE_CARD:
         sprintf(ErrorMsg,"The smart card is not responding to a reset.");
         break;
      case SCARD_W_UNSUPPORTED_CARD:
         sprintf(ErrorMsg,"The reader cannot communicate with the card, due to ATR string configuration conflicts.");
         break;
      case SCARD_W_WRONG_CHV:
         sprintf(ErrorMsg,"The card cannot be accessed because the wrong PIN was presented.");
         break;

         // Check for windows 32 error. If necessary further codes and descriptions could be added below.
         //---------------------------------------------------------------------------------------------
      case 23: sprintf(ErrorMsg,"(Win32)ERROR_CRC: Data error (cyclic redundancy check)."); break;
      case 31: sprintf(ErrorMsg,"(Win32)ERROR_GEN_FAILURE: A device attached to the system is not functioning.");break;
      case 87: sprintf(ErrorMsg,"(Win32)ERROR_INVALID_PARAMETER: The parameter is incorrect."); break;
      case 121:sprintf(ErrorMsg,"(Win32)ERROR_SEM_TIMEOUT: The semaphore timeout period has expired."); break;
      case 122:sprintf(ErrorMsg,"(Win32)ERROR_INSUFFICIENT_BUFFER: The data area passed to a system call is too small.");break;
      case 1117:sprintf(ErrorMsg,"(NT:STATUS_DATA_LATE_ERROR)->(Win32)ERROR_IO_DEVICE: The request could not be performed because of an I/O device error.");break;
      case 1785:sprintf(ErrorMsg,"(Win32)ERROR_UNRECOGNIZED_MEDIA: The disk media is not recognized. It may not be formatted."); break;

         // The error number wasn't included in the cases above
      default:
         sprintf(ErrorMsg,"No error string available");
         break;
      }

   SCRNPutText(ErrorMsg);

   // Display the error number and the corresponding string
   sprintf(ErrorMsg," [dwErrorFlags=%#lx)]",dwErrorFlags,dwErrorFlags);
   SCRNPutText(ErrorMsg);
   }


// *****************************************************************************
// This function display all readers of the SCARD_DEFAULT_READERS group.
// It is
// not distinguished wheter the reader is currently available or not.
// *****************************************************************************
BOOL SelectReader(VOID)
   {
   DWORD dwErrorFlags;
   CHAR mszReaders [1024];
   DWORD dwLength = sizeof(mszReaders);
   ULONG ulInput;
   DWORD i,j,z;
   CHAR  szReader [10] [100];
		
	
   for (i=0;i<10;i++)
      {
      MemSet(&szReader[i][0],
				 sizeof(&szReader[i][0]),
				 0x00,
				 sizeof(&szReader[i][0])
				 );
      }
   SCRNClear();
   SCRNPutTextAt( 5, 20, "Select reader which you want to use:");
   SCRNPutTextAt( 6, 20, "------------------------------------");


   dwErrorFlags = SCardListReaders(
											hContext,
                                 NULL,
                                 mszReaders,
                                 &dwLength
											);

   if (dwErrorFlags != SCARD_S_SUCCESS)
      {
      HandleError(dwErrorFlags);
      SCRNPutTextAt( 10, 1, "No reader available");
      SCRNGetChar();
      return FALSE;
      }
   else
      {
      if (dwLength > 2) // \0\0
         {
         z=0; j=0;
         for (i=0;i<dwLength;i++)
            {
            if (mszReaders[i] == '\0')
               {
               szReader [j] [z] = mszReaders[i];
               z=0;
               j++;
               }
            else
               {
               szReader [j] [z] = mszReaders[i];
               z++;
               }
            }

         for (j=0;j < 10;j++)
            {
            if (szReader[j] [0] != 0x00)
               {
               sprintf(szText,"(%d) %s",j+1,&szReader[j][0]);
               SCRNPutTextAt( (USHORT)(10+j), 1,szText);
               }
            }

         SCRNPutTextAt( 20, 1, "=>");
         ulInput = SCRNGetULong(1,10);

         StrCpy(
					szCardReader,
					sizeof(szCardReader),
					&szReader[ulInput-1] [0]
					);
         return TRUE;
         }
      else
         {
         SCRNPutTextAt( 5, 1, "No reader available");
         SCRNGetChar();
         return FALSE;
         }
      }
   }





/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
#define ERRCODE(x)  case x: return #x

GPCHAR StrError(
					OKERR eErr
					)
{
   switch (eErr)
      {
      ERRCODE(NO_ERROR);
      ERRCODE(OKERR_PARM1                         );
      ERRCODE(OKERR_PARM2                         );
      ERRCODE(OKERR_PARM3                         );
      ERRCODE(OKERR_PARM4                         );
      ERRCODE(OKERR_PARM5                         );
      ERRCODE(OKERR_PARM6                         );
      ERRCODE(OKERR_PARM7                         );
      ERRCODE(OKERR_PARM8                         );
      ERRCODE(OKERR_PARM9                         );
      ERRCODE(OKERR_PARM10                        );
      ERRCODE(OKERR_PARM11                        );
      ERRCODE(OKERR_PARM12                        );
      ERRCODE(OKERR_PARM13                        );
      ERRCODE(OKERR_PARM14                        );
      ERRCODE(OKERR_PARM15                        );
      ERRCODE(OKERR_PARM16                        );
      ERRCODE(OKERR_PARM17                        );
      ERRCODE(OKERR_PARM18                        );
      ERRCODE(OKERR_PARM19                        );
      ERRCODE(OKERR_INSUFFICIENT_PRIV             );
      ERRCODE(OKERR_PW_WRONG                      );
      ERRCODE(OKERR_PW_LOCKED                     );
      ERRCODE(OKERR_PW_TOO_SHORT                  );
      ERRCODE(OKERR_PW_TOO_LONG                   );
      ERRCODE(OKERR_PW_NOT_LOCKED                 );
      ERRCODE(OKERR_ITEM_NOT_FOUND                );
      ERRCODE(OKERR_ITEMS_LEFT                    );
      ERRCODE(OKERR_INVALID_CFG_FILE              );
      ERRCODE(OKERR_SECTION_NOT_FOUND             );
      ERRCODE(OKERR_ENTRY_NOT_FOUND               );
      ERRCODE(OKERR_NO_MORE_SECTIONS              );
      ERRCODE(OKERR_ITEM_ALREADY_EXISTS           );
      ERRCODE(OKERR_ITEM_EXPIRED                  );
      ERRCODE(OKERR_UNEXPECTED_RET_VALUE          );
      ERRCODE(OKERR_COMMUNICATE                   );
      ERRCODE(OKERR_NOT_ENOUGH_MEMORY             );
      ERRCODE(OKERR_BUFFER_OVERFLOW               );
      ERRCODE(OKERR_TIMEOUT                       );
      ERRCODE(OKERR_NOT_SUPPORTED                 );
      ERRCODE(OKERR_ILLEGAL_ARGUMENT              );
      ERRCODE(OKERR_READ_FIO                      );
      ERRCODE(OKERR_WRITE_FIO                     );
      ERRCODE(OKERR_INVALID_HANDLE                );
      ERRCODE(OKERR_GENERAL_FAILURE               );
      ERRCODE(OKERR_FILE_NOT_FOUND                );
      ERRCODE(OKERR_OPEN_FILE                     );
      ERRCODE(OKERR_SEM_USED                      );
      ERRCODE(OKERR_NOP                           );
      ERRCODE(OKERR_NOK                           );
      ERRCODE(OKERR_FWBUG                         );
      ERRCODE(OKERR_INIT                          );
      ERRCODE(OKERR_FIO                           );
      ERRCODE(OKERR_ALLOC                         );
      ERRCODE(OKERR_SESSION_ERR                   );
      ERRCODE(OKERR_ACCESS_ERR                    );
      ERRCODE(OKERR_OPEN_FAILURE                  );
      ERRCODE(OKERR_CARD_NOT_POWERED              );
      ERRCODE(OKERR_ILLEGAL_CARDTYPE              );
      ERRCODE(OKERR_CARD_NOT_INSERTED             );
      ERRCODE(OKERR_NO_DRIVER                     );
      ERRCODE(OKERR_OUT_OF_SERVICE                );
      ERRCODE(OKERR_EOF_REACHED                   );
      ERRCODE(OKERR_ON_BLACKLIST                  );
      ERRCODE(OKERR_CONSISTENCY_CHECK             );
      ERRCODE(OKERR_IDENTITY_MISMATCH             );
      ERRCODE(OKERR_MULTIPLE_ERRORS               );
      ERRCODE(OKERR_ILLEGAL_DRIVER                );
      ERRCODE(OKERR_ILLEGAL_FW_RELEASE            );
      ERRCODE(OKERR_NO_CARDREADER                 );
      ERRCODE(OKERR_IPC_FAULT                     );
      ERRCODE(OKERR_WAIT_AND_RETRY                );
      ERRCODE(OKERR_SCARD__E_CANCELLED            );
      ERRCODE(OKERR_SCARD__E_INVALID_HANDLE       );
      ERRCODE(OKERR_SCARD__E_INVALID_PARAMETER    );
      ERRCODE(OKERR_SCARD__E_INVALID_TARGET       );
      ERRCODE(OKERR_SCARD__E_NO_MEMORY            );
      ERRCODE(OKERR_SCARD__F_WAITED_TOO_LONG      );
      ERRCODE(OKERR_SCARD__E_INSUFFICIENT_BUFFER  );
      ERRCODE(OKERR_SCARD__E_UNKNOWN_READER       );
      ERRCODE(OKERR_SCARD__E_TIMEOUT              );
      ERRCODE(OKERR_SCARD__E_SHARING_VIOLATION    );
      ERRCODE(OKERR_SCARD__E_NO_SMARTCARD         );
      ERRCODE(OKERR_SCARD__E_UNKNOWN_CARD         );
      ERRCODE(OKERR_SCARD__E_CANT_DISPOSE         );
      ERRCODE(OKERR_SCARD__E_PROTO_MISMATCH       );
      ERRCODE(OKERR_SCARD__E_NOT_READY            );
      ERRCODE(OKERR_SCARD__E_INVALID_VALUE        );
      ERRCODE(OKERR_SCARD__E_SYSTEM_CANCELLED     );
      ERRCODE(OKERR_SCARD__F_COMM_ERROR           );
      ERRCODE(OKERR_SCARD__F_UNKNOWN_ERROR        );
      ERRCODE(OKERR_SCARD__E_INVALID_ATR          );
      ERRCODE(OKERR_SCARD__E_NOT_TRANSACTED       );
      ERRCODE(OKERR_SCARD__E_READER_UNAVAILABLE   );
      ERRCODE(OKERR_SCARD__P_SHUTDOWN             );
      ERRCODE(OKERR_SCARD__E_PCI_TOO_SMALL            );
      ERRCODE(OKERR_SCARD__E_READER_UNSUPPORTED       );
      ERRCODE(OKERR_SCARD__E_DUPLICATE_READER         );
      ERRCODE(OKERR_SCARD__E_CARD_UNSUPPORTED         );
      ERRCODE(OKERR_SCARD__E_NO_SERVICE               );
      ERRCODE(OKERR_SCARD__E_SERVICE_STOPPED          );
      ERRCODE(OKERR_SCARD__E_UNEXPECTED               );
      ERRCODE(OKERR_SCARD__E_ICC_INSTALLATION         );
      ERRCODE(OKERR_SCARD__E_ICC_CREATEORDER          );
      ERRCODE(OKERR_SCARD__E_UNSUPPORTED_FEATURE      );
      ERRCODE(OKERR_SCARD__E_DIR_NOT_FOUND            );
      ERRCODE(OKERR_SCARD__E_FILE_NOT_FOUND           );
      ERRCODE(OKERR_SCARD__E_NO_DIR                   );
      ERRCODE(OKERR_SCARD__E_NO_FILE                  );
      ERRCODE(OKERR_SCARD__E_NO_ACCESS                );
      ERRCODE(OKERR_SCARD__E_WRITE_TOO_MANY           );
      ERRCODE(OKERR_SCARD__E_BAD_SEEK                 );
      ERRCODE(OKERR_SCARD__E_INVALID_CHV              );
      ERRCODE(OKERR_SCARD__E_UNKNOWN_RES_MNG          );
      ERRCODE(OKERR_SCARD__E_NO_SUCH_CERTIFICATE      );

      ERRCODE(OKERR_SCARD__E_CERTIFICATE_UNAVAILABLE  );

      ERRCODE(OKERR_SCARD__E_NO_READERS_AVAILABLE     );
      ERRCODE(OKERR_SCARD__E_COMM_DATA_LOST           );
      ERRCODE(OKERR_SCARD__W_UNSUPPORTED_CARD         );
      ERRCODE(OKERR_SCARD__W_UNRESPONSIVE_CARD        );
      ERRCODE(OKERR_SCARD__W_UNPOWERED_CARD           );
      ERRCODE(OKERR_SCARD__W_RESET_CARD               );
      ERRCODE(OKERR_SCARD__W_REMOVED_CARD             );
      ERRCODE(OKERR_SCARD__W_SECURITY_VIOLATION       );
      ERRCODE(OKERR_SCARD__W_WRONG_CHV                );
      ERRCODE(OKERR_SCARD__W_CHV_BLOCKED              );
      ERRCODE(OKERR_SCARD__W_EOF                      );
      ERRCODE(OKERR_SCARD__W_CANCELLED_BY_USER        );
      default: return "<unknown>";
      }
}





/*****************************************************************************
Description:

Arguments:

Return Value:

note:
*****************************************************************************/
VOID WriteBuffer(
					GPBYTE 	pbBuffer,
					ULONG 	ulLength,
					GPUSHORT pusLineNumb,
               ULONG 	ulPos
					)
   {
   /* 0         1         2         3         4         5         6         7
   /* 01234567890123456789012345678901234567890123456789012345678901234567890 */
   /* addr  xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx  0123456789abcdef */
#define OFFS_HEX  6
#define OFFS_CHAR 55
#define LINE_SIZE 72

   ULONG ulI=0;
   ULONG ulL=0;
   CHAR szLine[LINE_SIZE];
   CHAR szHex[]="0123456789ABCDEF";
   BYTE b;

   MemSet(szLine,LINE_SIZE-1,' ',LINE_SIZE-1);

   szLine[LINE_SIZE-1]=0x00;
   szLine[0]='0';
   szLine[1]='0';
   szLine[2]='0';
   szLine[3]='0';

   while (ulI < ulLength)
      {
      b = pbBuffer[ulI];
      if (b >=' ')
         {
         szLine[OFFS_CHAR + ulL] = (CHAR)b;
         }
      else
         {
         szLine[OFFS_CHAR + ulL]='.';
         }

      szLine[OFFS_HEX +1 +3*ulL] = szHex[b & 0x0f];
      szLine[OFFS_HEX    +3*ulL] = szHex[b / 16];

      ulL++;
      ulI++;
      if (ulL == 16)
         {
         if (*pusLineNumb >= 21)
            {
            (*pusLineNumb)++;
            SCRNPutTextAt(*pusLineNumb, 1,"Hit any key to continue");

            SCRNGetText(1, szText, sizeof(szText));
            SCRNClear();
            (*pusLineNumb)=1;
            }

         /* newline */
         SCRNSetCursorPosition(*pusLineNumb, (USHORT) ulPos);
         SCRNPutText(szLine);
         MemSet(szLine,LINE_SIZE-1,' ',LINE_SIZE-1);

         szLine[3]=szHex[ulI&0x000f];
         szLine[2]=szHex[(ulI&0x00f0)/16];
         szLine[1]=szHex[(ulI&0x0f00)/256];
         szLine[0]=szHex[(ulI&0xf000)/4096];

         (*pusLineNumb)++;

         ulL=0;
         }
      }

   if (ulL!=0)
      {
      if (*pusLineNumb>=21)
         {
         (*pusLineNumb)++;
         SCRNPutTextAt(*pusLineNumb, 1,"Hit any key to continue");

         SCRNGetText(1, szText, sizeof(szText));
         SCRNClear();
         *pusLineNumb=0;
         }

      /* rest */
      SCRNSetCursorPosition(*pusLineNumb, (USHORT) ulPos);
      SCRNPutText(szLine);
      MemSet(szLine,LINE_SIZE-1,' ',LINE_SIZE-1);

      *pusLineNumb++;
      }
   }



/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID ErrorMessage(
					OKERR eErr
					)
{
char *ptr;

   SCRNClearBlock(21, 1,24,80);

   ptr = StrError(eErr);

   StrPrintf(szText,"[OKERR-0x%04X] ",eErr);

   SCRNPutTextAt(22, 1,szText);
   SCRNPutText(ptr);
}




/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmVerifyPassword(
									SCARDHANDLE ulHandleSmartCard
									)
{
   OKERR 	lStatus = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[PASSWORD_LENGTH];		
	UCHAR 	ucPasswordIndex;
	UCHAR		ucAttemptsCounter;
	ULONG 	ulAttemptsCounterAdr=0;

		SCRNClear();
		SCRNPutTextAt( usY=1, 20, "Test Verify Password");
		SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "------------------------------------");

		usY = 4;

		SCRNPutTextAt(usY, 2,"Password Index :");
		ucPasswordIndex = (UCHAR)SCRNGetULongAt(usY++,24, 0,AT88SC1608_VERIFY_PASSWORD_INDEX_MASK);
		

		SCRNPutTextAt(usY, 2,"Password:");
		SCRNGetTextAt(
						usY++, 16,
						PASSWORD_LENGTH,
						abData,
						sizeof(abData)	+1
						);
		
		if (AskContinue(&usY,2) == TRUE)
			{
			lStatus = SCardSmVerifyPassword(
													ulHandleSmartCard,   	
													abData,
													ucPasswordIndex,
													&ucAttemptsCounter			// 0xff success
													);
			if (lStatus == NO_ERROR)
				{
				// Print the corresponding attempt counter
				//
				usY++;
				switch (enCurrentSmType)
					{
					case AT88SC153:
						ulAttemptsCounterAdr = AT88SC153_PASSWORD_CONFIG_ZONE_ADR
																+ (ucPasswordIndex & 0x02)*4 				// write=0, read=1
																+ (ucPasswordIndex & 0x01)*8; 			// pwd set address 0..7
						break;
				
					case AT88SC1608:
						ulAttemptsCounterAdr = AT88SC1608_PASSWORD_CONFIG_ZONE_ADR
																+ (ucPasswordIndex & 0x08)*4 				// write=0, read=1
																+ (ucPasswordIndex & 0x07)*8; 			// pwd set address 0..7
						break;
					}
				
					// Print the attempt counter address and its value
					//
					sprintf(szText,
							  "Attempts Counter (at adr. 0x%02x) = 0x%02X \n",
							  ulAttemptsCounterAdr,
							  ucAttemptsCounter
							  );
					SCRNPutTextAt(usY++, 2, szText);
					}
				}
			else
				{
				SCRNPutTextAt(++usY, 2,"Command discarded.");
				}

		ErrorMessage(lStatus);
}



/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmReadFuses(
								SCARDHANDLE ulHandleSmartCard
								)
{
   OKERR 	lStatus = NO_ERROR;
   USHORT 	usY;
   BYTE   	abData[MAX_USER_ZONE_LENGTH];	

		usY =1;
		SCRNClear();
		SCRNPutTextAt( usY, 20, "Test Read Fuses with ");
		SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "----------------------------------------");

		usY = 4;
		
		lStatus = SCardSmReadFuses(
								  	ulHandleSmartCard,   	
									abData       			// Pointer to the buffer, where the data read are to be stored
									);
		if (lStatus == NO_ERROR)
			{
			usY += 2;
			WriteBuffer(
						abData,
						1,				// must be 1 ulBytesRead,	
						&usY,
						0
						);
			}
		ErrorMessage(lStatus);
}



/*****************************************************************************
Description:

Arguments:

Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmWriteFuses(
								SCARDHANDLE ulHandleSmartCard
								)
{
   OKERR 	lStatus = NO_ERROR;
   USHORT 	usY;
   UCHAR 	ucFuseIndex;	

		usY =1;
		SCRNClear();
		SCRNPutTextAt( usY, 20, "Test Write Fuses with ");
		SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "----------------------------------------");

		usY = 4;

		switch (enCurrentSmType)
			{
			case AT88SC153:
				SCRNPutTextAt(usY, 2,"Fuse to blow:");
				usY = 4;
				#define XPOS	50
				SCRNPutTextAt(usY, 2,"Fuse to blow,sequentially (0=FAB, 2=CMA, 4=PER):");
				ucFuseIndex = (UCHAR)SCRNGetULongAt(usY++,XPOS, 0,0x04);
				#undef XPOS
				break;
				
			case AT88SC1608:
				SCRNPutTextAt(usY++, 2,"Fuses are blown sequentially: FAB,CMA,PER, after each call.");
				break;
			}
	

		if (AskContinue(&usY,2) == TRUE )
			{
			lStatus = SCardSmWriteFuses(
											ulHandleSmartCard,   	
											&ucFuseIndex
											);
			}
		else
			{
			SCRNPutTextAt(usY, 2,"Command discarded.");
			}

		ErrorMessage(lStatus);
}



/*****************************************************************************
Description:
	Some commands are fatal for the consistency of the test card when issued
	with bad parameters.
	
Arguments:

Return Value:
	TRUE,FALS
note:
*****************************************************************************/
BOOL AskContinue(
					PUSHORT pusY,
					USHORT usX
					)
{
int iKey;
USHORT usY;
BOOL fResult;


	usY = *pusY;

	SCRNPutTextAt(usY++, usX,"Are you sure? Continue? (Y/N)");
	iKey = SCRNGetChar();

		if ( iKey == 'y' ||iKey == 'Y' )
			{
			fResult = TRUE;
			}
		else
			{
			fResult = FALSE;
			}

		*pusY = usY;

	return fResult;
}





/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmInitAuthentication(
										SCARDHANDLE ulHandleSmartCard
										)
{
	OKERR 	lStatus = NO_ERROR;
	USHORT 	usY;
	BYTE   	abData[HOST_RANDOM_NUMBER_LEN +1];	
	
		usY =1;
		SCRNClear();
		SCRNPutTextAt( usY, 20, "Test Initialize Authentication with ");
		SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "----------------------------------------");
		
		usY = 4;
		
		switch (enCurrentSmType)
			{
			case AT88SC153:
			case AT88SC1608:
				SCRNPutTextAt(usY, 2,"HostRandomNumber(7 bytes):");
				SCRNGetTextAt(
								usY++, 32,
								HOST_RANDOM_NUMBER_LEN,
								abData,
								sizeof(abData)
								);
				break;
			}
		
		
		if (AskContinue(&usY,2) == TRUE )
			{
			lStatus = SCardSmInitializeAuthentication(
																ulHandleSmartCard,
																abData
																);
			}
		else
			{
			SCRNPutTextAt(usY, 2,"Command discarded.");
			}
		
		ErrorMessage(lStatus);
}





/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmVerifyAuthentication(
												SCARDHANDLE ulHandleSmartCard
												)
{
	OKERR 	lStatus = NO_ERROR;
	USHORT 	usY;
	BYTE   	abData[HOST_RANDOM_NUMBER_LEN +1];	
	UCHAR		ucAttemptsCounter;
	ULONG 	ulAttemptsCounterAdr;
	
		usY =1;
		SCRNClear();
		SCRNPutTextAt( usY, 20, "Test Verify Authentication with ");
		SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
		SCRNPutTextAt( usY, 20, "----------------------------------------");
		
		usY = 4;
		
		switch (enCurrentSmType)
			{
			default:
			case AT88SC153:
			case AT88SC1608:
				SCRNPutTextAt(usY, 2,"HostRandomNumber(7 bytes):");
				SCRNGetTextAt(
								usY++, 32,
								HOST_RANDOM_NUMBER_LEN,
								abData,
								sizeof(abData)
								);
				break;
			}
		
		
		if (AskContinue(&usY,2) == TRUE )
			{
			lStatus = SCardSmVerifyAuthentication(
										  					ulHandleSmartCard,
										  					abData,
															&ucAttemptsCounter
										  					);

			//
			// Print the Authentication Attempts Counter AAC
			//						
			if (lStatus == NO_ERROR)
				{
				// Print the corresponding attempt counter
				//
				usY++;
		
				switch (enCurrentSmType)
					{
					default:
					case AT88SC153:
						ulAttemptsCounterAdr = AT88SC153_AUTHENTICATION_ATTEMPTS_COUNTER_ADR;
						break;
		
					case AT88SC1608:
						ulAttemptsCounterAdr = AT88SC153_AUTHENTICATION_ATTEMPTS_COUNTER_ADR;
						break;
					}
					
				//
				// Print the attepmts counter address and its value
				//
				sprintf(szText,
						  "Attempts Counter (at adr. 0x%02x) = 0x%02X \n",
						  ulAttemptsCounterAdr,
						  ucAttemptsCounter
						  );
				SCRNPutTextAt(usY++, 2, szText);
				}	// Verify success

			}
		else
			{
			SCRNPutTextAt(usY, 2,"Command discarded.");
			}
		
		ErrorMessage(lStatus);
}


//ct->
/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmAT88SC10xCompareSc(
												SCARDHANDLE ulHandleSmartCard
												)
{
	OKERR	lStatus = NO_ERROR;
	USHORT	usY;
	BYTE	abData[16];
	UCHAR	ucAttemptsCounter;

	SCRNClear();
	SCRNPutTextAt( usY=1, 20, "Test Compare Security Code");
	SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
	SCRNPutTextAt( usY, 20, "------------------------------------");

	usY = 4;

	SCRNPutTextAt(usY, 2,"Password:");
	SCRNGetTextAt(
	               usY++, 16,
	               2,
	               abData,
	               sizeof(abData)
	             );
		
	if (AskContinue(&usY,2) == TRUE)
	{
		lStatus = SCardSmAT88SC10xCompareSC(
		                                     ulHandleSmartCard,
		                                     abData,
		                                     &ucAttemptsCounter			// 0xff success
		                                   );
		// Print the corresponding attempt counter
		//
		usY++;

		// Print the attempt counter address and its value
		//
		sprintf(
				 szText,
				 "Attempts Counter = 0x%02X \n",
				 ucAttemptsCounter
			   );
		SCRNPutTextAt(usY++, 2, szText);
	}
	else
	{
		SCRNPutTextAt(++usY, 2,"Command discarded.");
	}

	ErrorMessage(lStatus);
}



/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmAT88SC10xErase(
												SCARDHANDLE ulHandleSmartCard
												)
{
	OKERR   lStatus = NO_ERROR;
	USHORT  usY;

	ULONG   ulWordAdr;
	ULONG   ulWordsToErase;

	SCRNClear();
	SCRNPutTextAt( usY=1, 20, "Test Erase");
	SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
	SCRNPutTextAt( usY, 20, "------------------------------------");

	usY = 4;
	#define XPOS	  	24

	SCRNPutTextAt(usY, 2,"Word address   :");
	ulWordAdr = SCRNGetULongAt(usY++,XPOS, 0, (AT88SC10X_MAXSIZE/16)-1 );
	
	SCRNPutTextAt(usY, 2,"Words to Erase:");
	ulWordsToErase = SCRNGetULongAt(usY++,XPOS, 1, (AT88SC10X_MAXSIZE/16) );
	
	#undef XPOS
		
	lStatus = SCardSmAT88SC10xErase(
	                                 ulHandleSmartCard,
	                                 ulWordAdr,          // word address
	                                 ulWordsToErase      // words to erase
	                               );

	ErrorMessage(lStatus);
}




/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmAT88SC10xEraseAz(
												SCARDHANDLE ulHandleSmartCard
												)
{
	OKERR   lStatus = NO_ERROR;
	USHORT  usY;

	UCHAR   ucAzNumber = 0;
	ULONG   ulInput = 0;
	UCHAR   ucEC = 0;
	ULONG   ulPwLen = 0;
	BYTE    abData[32];
	BOOL    fUseEraseCounter = FALSE;
	BOOL    fEraseCounterAvailable = FALSE;
	
	SCRNClear();
	SCRNPutTextAt( usY=1, 20, "Test Erase Application Zone");
	SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
	SCRNPutTextAt( usY, 20, "------------------------------------");

	usY = 4;

	switch (enCurrentSmType)
	{
		SCRNPutTextAt(usY++, 2,"Application Zone   :");
		SCRNPutTextAt(usY++, 2,"--------------------");
		case AT88SC101:
			SCRNPutTextAt(usY++ ,2, "(1) AZ");
			SCRNPutTextAt(usY++, 2, "Application Zone => ");
			ulInput = SCRNGetULong(1,1);
			ucAzNumber = (UCHAR) ulInput;
			switch (ulInput)
			{
				case 1:
					ulPwLen = 32;
					fEraseCounterAvailable = TRUE;
					break;
			}
			break;

		case AT88SC102:
			SCRNPutTextAt(usY++ ,2, "(1) AZ1");
			SCRNPutTextAt(usY++ ,2, "(2) AZ2");
			SCRNPutTextAt(usY++, 2, "Application Zone => ");
			ulInput = SCRNGetULong(1,2);
			ucAzNumber = (UCHAR) ulInput;
			switch (ulInput)
			{
				case 1:
					ulPwLen = 48;
					break;
				case 2:
					ulPwLen = 32;
					fEraseCounterAvailable = TRUE;
					break;
			}
			break;

		case AT88SC1003:
			SCRNPutTextAt(usY++ ,2, "(1) AZ1");
			SCRNPutTextAt(usY++ ,2, "(2) AZ2");
			SCRNPutTextAt(usY++ ,2, "(3) AZ3");
			SCRNPutTextAt(usY++, 2, "Application Zone => ");
			ulInput = SCRNGetULong(1,3);
			ucAzNumber = (UCHAR) ulInput;
			switch (ulInput)
			{
				case 1:
					ulPwLen = 48;
					break;
				case 2:
					ulPwLen = 32;
					fEraseCounterAvailable = TRUE;
					break;
				case 3:
					ulPwLen = 48;
					break;
			}
			break;

	}

	usY++;
	SCRNPutTextAt(usY, 2,"Password:");
	SCRNGetTextAt(
	               usY++, 16,
	               (USHORT)(ulPwLen/8),
	               abData,
	               sizeof(abData)
	             );

	if (fEraseCounterAvailable == TRUE)
	{
		usY++;
		SCRNPutTextAt(usY++ ,2, "Use Erase Counter   :");
		SCRNPutTextAt(usY++ ,2, "---------------------");
		SCRNPutTextAt(usY++ ,2, "(0) NO");
		SCRNPutTextAt(usY++ ,2, "(1) YES");
		SCRNPutTextAt(usY++, 2, "=> ");
		if (SCRNGetULong(0,1) == 1)
			fUseEraseCounter = TRUE;
	}

	if (AskContinue(&usY,2) == TRUE)
	{
		lStatus = SCardSmAT88SC10xEraseAZ(
										   ulHandleSmartCard,
										   ucAzNumber,
										   abData,
										   fUseEraseCounter,
										   &ucEC
										 );

		if (lStatus == NO_ERROR)
		{
			// Print the corresponding attempt counter
			//
			usY++;

			// Print the attempt counter address and its value
			//
			sprintf(
					 szText,
					 "Erase Counter = %d \n",
					 ucEC
				   );
			SCRNPutTextAt(usY++, 2, szText);
		}
	}
	else
	{
		SCRNPutTextAt(++usY, 2,"Command discarded.");
	}

	ErrorMessage(lStatus);
}




/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmAT88SC10xRead(
												SCARDHANDLE ulHandleSmartCard
												)
{
	OKERR   lStatus = NO_ERROR;
	USHORT  usY;

	BYTE    abData[256];
	ULONG   ulBitAdr;
	ULONG   ulBitsToRead ;
	ULONG   ulBitsRead;
	ULONG   ulBytesRead;

	SCRNClear();
	SCRNPutTextAt( usY=1, 20, "Test Read");
	SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
	SCRNPutTextAt( usY, 20, "------------------------------------");

	usY = 4;
	#define XPOS	  	24

	SCRNPutTextAt(usY, 2,"Bit address   :");
	ulBitAdr = SCRNGetULongAt(usY++,XPOS, 0, AT88SC10X_MAXSIZE-1);
	
	SCRNPutTextAt(usY, 2,"Bits to read:");
	ulBitsToRead = SCRNGetULongAt(usY++,XPOS, 1, AT88SC10X_MAXSIZE);
	
	#undef XPOS
		
	lStatus = SCardSmAT88SC10xRead(
	                                 ulHandleSmartCard,
	                                 ulBitAdr,           // bit address
	                                 ulBitsToRead,       // bits to read
	                                 abData,             // Pointer to the read buffer
	                                 sizeof(abData),     // Size of the read buffer
	                                 &ulBitsRead        // out: Number of bits actually read
	                               );

	ulBytesRead = ulBitsRead / 8;
	if ((ulBitsRead % 8) != 0)
		ulBytesRead++;

	if (lStatus == NO_ERROR)
	{
		usY += 2;
		WriteBuffer(
		             abData,
		             ulBytesRead,
		             &usY,
		             0
		           );
	}

	ErrorMessage(lStatus);
}




/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmAT88SC10xWrite(
												SCARDHANDLE ulHandleSmartCard
												)
{
	OKERR	lStatus = NO_ERROR;
	USHORT	usY;
	BYTE	abData[256];
	ULONG	ulBitAdr;
	ULONG	ulBitsToWrite;
	ULONG	ulBytesToWrite;

	SCRNClear();
	SCRNPutTextAt( usY=1, 20, "Test AT88SC10x Write");
	SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
	SCRNPutTextAt( usY, 20, "------------------------------------");

	usY = 4;
	#define XPOS	  	24

	SCRNPutTextAt(usY, 2,"Write bit address :");
	ulBitAdr = SCRNGetULongAt(usY++,XPOS,  0, AT88SC10X_MAXSIZE-1);

	SCRNPutTextAt(usY, 2,"Bits to write:");
	ulBitsToWrite = SCRNGetULongAt(usY++,XPOS, 1, AT88SC10X_MAXSIZE);
		
	#undef XPOS
		
	ulBytesToWrite = ulBitsToWrite / 8;
	ulBytesToWrite += (ulBitsToWrite%8)?1:0;

	SCRNPutTextAt(usY, 2,"Data:");
	SCRNGetTextAt(
	               usY++, 16,
	               (USHORT)ulBytesToWrite,
	               abData,
	               sizeof(abData)
	             );

	lStatus = SCardSmAT88SC10xWrite (
	                                  ulHandleSmartCard,
	                                  ulBitAdr,
	                                  ulBitsToWrite,
	                                  abData
	                                );

	ErrorMessage(lStatus);
}




/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmAT88SC10xBlowFuse(
												SCARDHANDLE ulHandleSmartCard
												)
{
	OKERR   lStatus = NO_ERROR;
	USHORT  usY;

	ULONG   ulInput;
	UCHAR   ucFuse = 0;
	
	SCRNClear();
	SCRNPutTextAt( usY=1, 20, "Test Blow Fuse");
	SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
	SCRNPutTextAt( usY, 20, "------------------------------------");

	usY = 4;

	SCRNPutTextAt(usY++, 2,"Blow Fuse :");
	SCRNPutTextAt(usY++, 2,"--------------------");
	SCRNPutTextAt(usY++ ,2, "(1) MANUFACTURER");
	SCRNPutTextAt(usY++ ,2, "(2) ISSUER");
	SCRNPutTextAt(usY++ ,2, "(3) ECEN");
	SCRNPutTextAt(usY++, 2, " => ");
	ulInput = SCRNGetULong(1,3);

	switch (ulInput)
	{
		case 1 : ucFuse = AT88SC10X_FUSE_MANUFACTURER; break;
		case 2 : ucFuse = AT88SC10X_FUSE_ISSUER; break;
		case 3 : ucFuse = AT88SC10X_FUSE_ECEN; break;
		default: break;
	}

	if (AskContinue(&usY,2) == TRUE)
	{
		lStatus = SCardSmAT88SC10xBlowFuse(
		                                     ulHandleSmartCard,
		                                     ucFuse
		                                   );
	}
	else
	{
		SCRNPutTextAt(++usY, 2,"Command discarded.");
	}

	ErrorMessage(lStatus);
}




/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/
VOID Test_SCardSmAT88SC10xSetFusPin(
												SCARDHANDLE ulHandleSmartCard
												)
{
	OKERR   lStatus = NO_ERROR;
	USHORT  usY;

	ULONG   ulInput;
	
	SCRNClear();
	SCRNPutTextAt( usY=1, 20, "Test Set FUS Pin");
	SCRNPutTextAt( usY++, 50, pszCurrentSmCard);
	SCRNPutTextAt( usY, 20, "------------------------------------");

	usY = 4;

	SCRNPutTextAt(usY++, 2,"Turn FUS Pin :");
	SCRNPutTextAt(usY++, 2,"--------------------");
	SCRNPutTextAt(usY++ ,2, "(0) OFF");
	SCRNPutTextAt(usY++ ,2, "(1) ON");
	SCRNPutTextAt(usY++, 2, " => ");
	ulInput = SCRNGetULong(0,1);

	lStatus = SCardSmAT88SC10xSetFusPin(
	                                     ulHandleSmartCard,
	                                     (UCHAR)ulInput
	                                   );

	ErrorMessage(lStatus);
}
//<-ct



/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/



/*****************************************************************************
* History:
* $Log: smtst.c $
* Revision 1.13  2006/02/16 12:20:43  TBruendl
* No comment given
*
* Revision 1.12  2005/06/10 08:49:34  TBruendl
* No comment given
*
* Revision 1.11  2005/02/11 07:18:44  TBruendl
* support of AT88SC101/102 added
*
* Revision 1.10  2004/09/28 05:47:49  TBruendl
* No comment given
*
* Revision 1.9  2004/07/20 15:29:57  MPetkov
* No comment given
*
* Revision 1.8  2004/07/15 11:09:22  MPetkov
* No comment given
*
* Revision 1.7  2004/07/13 14:12:36  MPetkov
* No comment given
*
* Revision 1.6  2004/07/09 14:36:41  MPetkov
* All functions are supported.
*
* Revision 1.5  2004/07/08 12:49:22  MPetkov
* No comment given
*
* Revision 1.4  2004/07/07 17:53:58  MPetkov
* No comment given
*
* Revision 1.3  2004/07/07 12:13:43  MPetkov
* No comment given
*
* Revision 1.2  2004/07/06 13:22:35  MPetkov
* No comment given
*
* Revision 1.1  2004/07/05 17:03:25  MPetkov
* No comment given
*
* Revision 1.1  2004/06/29 18:35:07  MPetkov
* First approach
*
******************************************************************************/



