/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/dftst/rcs/dftst.c $
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
#include "dftst041.h"
#include "dftst.h"
#include "scarddf.h"


//
// Local funcrion prototypes
//
VOID main(VOID);

BOOL SelectReader(VOID);

GPCHAR StrError(
					OKERR eErr
					);

OKERR ENTRY Test_SCardDfInit(
										SCARDHANDLE 				ulHandleSmartCard,
										SCARD_DATA_FLASH_TYPE   Type
										);


#define MAX_BYTE     0x000000FF
#define MAX_USHORT   0x0000FFFF
#define MAX_ULONG    0xFFFFFFFF


static  CHAR    szText[160] = "\0";           /* Common string for text I/O */
static  BYTE    bInBuffer[512];
static  BYTE    bOutBuffer[512];
static  BYTE    szCardReader[128] = "\0";

SCARDCONTEXT    hContext = 0xFFFFFFFF;
SCARDHANDLE     hCard    = 0xFFFFFFFF;




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
   ULONG   ulScreen;
   DWORD   dwErrorFlags = 0;

   SCRNInit();
   usInput = 0;

   dwErrorFlags = SCardEstablishContext(
                                       SCARD_SCOPE_USER,
                                       NULL,
                                       NULL,
                                       &hContext
													);
   if (dwErrorFlags != SCARD_S_SUCCESS)
      {
      HandleError(
					dwErrorFlags
					);
      goto L_ExitMain;
      }


   if (SelectReader() == FALSE)
      {
      goto L_ExitMain;
      }

	ulScreen = 1;
   while (usInput != 99)						// +++++
      {
      SCRNClear();
      SCRNPutTextAt( 1, 5, "Test program for synchronous DataFlash cards :");
      SCRNPutTextAt( 2, 5, "----------------------------------------------");
      usLine=3;

      SCRNPutTextAt(usLine++, 5, " 1) Display card connect commands");
      SCRNPutTextAt(usLine++, 5, " 2) Display Test DataFlash AT45DB041B commands");
      usLine++;

      switch (ulScreen)
         {
         default:
         case 1:					// Menu for screen-1 card connect commands
            SCRNPutTextAt(usLine++, 5, "11)  TestSCardConnect");
            SCRNPutTextAt(usLine++, 5, "12)  TestSCardReconnect");
            SCRNPutTextAt(usLine++, 5, "13)  TestSCardDisconnect");
            break;

			case 2:
				SCRNPutTextAt(usLine++, 5, " Test DataFlash AT45DB041B Commands:");
				SCRNPutTextAt(usLine++, 5, "------------------------------------");
				SCRNPutTextAt(usLine++, 5, "21) Init dataflash card type (to be called first)");

				//
				// Read commands
				//
				SCRNPutTextAt(usLine++, 5, "22) Continuous array read");
				SCRNPutTextAt(usLine++, 5, "23) Main memory page read");
				SCRNPutTextAt(usLine++, 5, "24) Buffer read");
				SCRNPutTextAt(usLine++, 5, "25) Status register read");

				//
				// Program and erase commands
				//
				SCRNPutTextAt(usLine++, 5, "26) Buffer write");
				SCRNPutTextAt(usLine++, 5, "27) Buffer to main memory page program");
				SCRNPutTextAt(usLine++, 5, "28) Page erase");
				SCRNPutTextAt(usLine++, 5, "29) Block erase");
            SCRNPutTextAt(usLine++, 5, "30) Main memory page program through buffer");

				//
				// Additional commands
				//
				SCRNPutTextAt(usLine++, 5, "31) Main memory page to buffer transfer");
				SCRNPutTextAt(usLine++, 5, "32) Main memory page to buffer compare");
				SCRNPutTextAt(usLine++, 5, "33) Auto page rewrite through buffer");

				break;
         }

		usLine++;
      SCRNPutTextAt(usLine++, 5, "99) Quit");
      SCRNPutTextAt(usLine++, 5, "Selection: ");

      usInput = SCRNGetUShort(1, 99);				// Get selection

      switch (usInput)
         {
         case 1:
         case 2:
         case 3:
         case 4:
         case 5:
         case 6:
            ulScreen=(ULONG)usInput;			// do nothing
            break;

         case 11 : TestSCardConnect()   	;break;
         case 12 : TestSCardReconnect()   ;break;
         case 13 : TestSCardDisconnect()  ;break;

			//
			// AT45DB041B commands
			//
			case 21 : Test_SCardDfInit(
												hCard,
												AT45DB041		// the one we used
												);	
				break;

  			//
			// Read commands
  			//
			case 22 : TestAT45DB041_ContinuousArrayRead (hCard);	break;
			case 23 : TestAT45DB041_MainMemoryPageRead (hCard);   break;
			case 24 : TestAT45DB041_BufferRead (hCard);     		break;
			case 25 : TestAT45DB041_StatusRegRead (hCard);    		break;

			//
			// Programm and erase commands
			//
			case 26 : TestAT45DB041_BufferWrite (hCard);     		break;
			case 27 : TestAT45DB041_BufferToMainMemoryPageProgram (hCard);break;
			case 28 : TestAT45DB041_PageErase (hCard);				break;
			case 29 : TestAT45DB041_BlockErase(hCard);				break;
			case 30 : TestAT45DB041_MainMemoryPageProgramThroughBuffer (hCard); break;

			//
			// additional commands
			//
			case 31 : TestAT45DB041_MainMemoryPageToBufferTransfer(hCard); break;
			case 32 : TestAT45DB041_MainMemoryPageToBufferCompare(hCard);	break;
			case 33 : TestAT45DB041_AutoPageRewriteThroughBuffer(hCard);   break;
         }
      }  /*** end while ***/

   SCRNClear();
   SCRNExit();

L_ExitMain:
   if (hContext != 0xFFFFFFFF)
      SCardReleaseContext(hContext);

   if (hCard != 0xFFFFFFFF)
      SCardDisconnect(hCard,SCARD_LEAVE_CARD);

   exit(CODE_0);
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
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();                            // Wait for confirmation
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
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
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
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
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
// This function displays all readers of the SCARD_DEFAULT_READERS group.
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
      MemSet(&szReader[i][0],sizeof(&szReader[i][0]),0x00,sizeof(&szReader[i][0]));
      }
   SCRNClear();
   SCRNPutTextAt( 5, 20, "Select reader which you want to use:");
   SCRNPutTextAt( 6, 20, "------------------------------------");


   dwErrorFlags = SCardListReaders(hContext,
                                   NULL,
                                   mszReaders,
                                   &dwLength);

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
         z=0;
         j=0;
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
         StrCpy(szCardReader,sizeof(szCardReader),&szReader[ulInput-1] [0]);
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
OKERR ENTRY Test_SCardDfInit(
							  		SCARDHANDLE 					ulHandleSmartCard,
							  		IN SCARD_DATA_FLASH_TYPE   Type
							  		)
{
   OKERR lErr = NO_ERROR;

		SCRNClear();
		SCRNPutTextAt( 1, 27, "Test SCardDfInit");
		SCRNPutTextAt( 2, 27, "----------------");
	
		lErr = SCardDfInit(
								ulHandleSmartCard,	
								Type
								);
	
		ErrorMessage(lErr);
		SCRNGetChar();

	return lErr;
}




/*****************************************************************************
Description:
Arguments:
Return Value:
note:
*****************************************************************************/



/*****************************************************************************
* History:
* $Log: dftst.c $
* Revision 1.9  2006/02/16 12:21:29  TBruendl
* No comment given
*
* Revision 1.8  2005/06/10 08:50:21  TBruendl
* No comment given
*
* Revision 1.7  2004/03/10 13:40:57  TBruendl
* No comment given
*
* Revision 1.6  2004/03/09 08:36:43  MPetkov
* No comment given
*
* Revision 1.5  2004/03/08 08:59:35  MPetkov
* No comment given
*
* Revision 1.4  2004/02/20 15:01:11  MPetkov
* All commands
*
* Revision 1.3  2004/02/19 14:37:47  MPetkov
* No comment given
*
* Revision 1.2  2004/02/18 16:51:22  MPetkov
* No comment given
*
* Revision 1.1  2004/02/17 18:35:07  MPetkov
* First approach
*
******************************************************************************/



