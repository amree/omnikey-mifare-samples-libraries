/*****************************************************************************
@doc
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/scarddf/rcs/scarddf.h $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
*****************************************************************************/

#ifndef _INC_SCARD_SPI
   #define _INC_SCARD_SPI

   #include <windows.h>
   #ifndef S_WNT
      #define S_WNT
   #endif
	
#include <ok.h>


//
// All structures and unions are aligned with 1.
// The initial pack value is saved in old_value, it will be restored with pop below.
//

#pragma pack(push,old_value,1)




// DEFINE card types: the constants below are according the i2c card type used
typedef enum _SCARD_DATA_FLASH_TYPE
   {
   // DataFlash cards from Atmel:
   AT45DB041 = 0xc1,
// comming soon:
//   AT45DB011,
//   AT45DB021,
//   AT45DB081,
//   AT45DB0161,
//   AT45DB0231,
	
   DATAFLASH_TYPE_ENUM_TAIL          // must always be the last entry in this enum!!
   }
SCARD_DATA_FLASH_TYPE, *PSCARD_DATA_FLASH_TYPE;

//
// AT45DB041B
//
#define AT45DB041_TOTAL_PAGES 						2048
#define AT45DB041_PAGE_SIZE	 						264
#define AT45DB041_BUFFER_SIZE 						264
#define AT45DB041_MAX_BLOCK_NUMBER 					255

#ifdef __cplusplus
extern "C" {
#endif

OKERR ENTRY SCardDfInit(
								IN SCARDHANDLE	 	   	ulHandleCard,	
								IN SCARD_DATA_FLASH_TYPE Type
								);

OKERR ENTRY SCardDfContinuousArrayRead(
										IN SCARDHANDLE ulHandleCard,   	
										IN BYTE    		*pbReadBuffer,
										IN ULONG    	ulReadBufferSize,
										IN ULONG    	ulPageAdr,   	
										IN ULONG    	ulByteAdr,   	
										IN ULONG    	ulBytesToRead,		
										OUT PULONG    	pulBytesReturned	
										);


OKERR ENTRY SCardDfMainMemoryPageRead(
										IN SCARDHANDLE ulHandleCard,
										IN BYTE    		*pbReadBuffer,
										IN ULONG    	ulReadBufferSize,
										IN ULONG    	ulPageAdr,   	
										IN ULONG    	ulByteAdr,   	
										IN ULONG    	ulBytesToRead,		
										OUT PULONG    	pulBytesReturned	
										);


OKERR ENTRY SCardDfBufferRead	(
										IN SCARDHANDLE ulHandleCard,
										IN BYTE    		*pbReadBuffer,
										IN ULONG    	ulReadBufferSize,
										IN ULONG    	ulByteAdr,   	
										IN ULONG    	ulBytesToRead,		
										IN UCHAR			ucBufferNumber,
										OUT PULONG    	pulBytesReturned	
										);

OKERR ENTRY SCardDfStatusRegisterRead (
  										IN SCARDHANDLE ulHandleCard,
  										IN BYTE    		*pbReadBuffer
  										);

//
// Program and erase functions
//
OKERR ENTRY SCardDfBufferWrite(
										IN SCARDHANDLE ulHandleCard,
										IN BYTE     	*pbWriteBuffer,
										IN ULONG    	ulAddress,   	
										IN ULONG    	ulBytesToWrite,
										IN UCHAR			ucBufferNumber
										);

OKERR ENTRY SCardDfBufferToMainMemoryPageProgram(
										IN SCARDHANDLE	ulHandleCard,   //  Handle (get from SCardConnect)
										IN UCHAR			ucBufferNumber,
										IN ULONG   		ulPageAdr,   	         //  page address to read from
										IN BOOL			fErase
										);


OKERR ENTRY  SCardDfPageErase(
										IN SCARDHANDLE	ulHandleCard,
										IN ULONG   		ulPageAdr
										);

OKERR ENTRY  SCardDfBlockErase(
										IN SCARDHANDLE	ulHandleCard,
										IN ULONG   		ulBlockNr
										);


OKERR ENTRY SCardDfMainMemoryPageProgramThroughBuffer (
										IN SCARDHANDLE ulHandleCard,
										IN BYTE     	*pbWriteBuffer,
										IN ULONG    	ulPageAdr,   	
										IN ULONG    	ulByteAdr,   	
										IN ULONG    	ulBytesToWrite,
										IN UCHAR			ucBufferNumber
										);

//
// Additional commands
//
OKERR ENTRY SCardDfMainMemoryPageToBufferTransfer(
  										IN SCARDHANDLE	ulHandleCard,
  										IN UCHAR			ucBufferNumber,
  										IN ULONG   		ulPageAdr
  										);

OKERR ENTRY SCardDfMainMemoryPageToBufferCompare(
														IN SCARDHANDLE	ulHandleCard,
														IN UCHAR			ucBufferNumber,
														IN ULONG   		ulPageAdr
														);

OKERR ENTRY SCardDfAutoPageRewriteThroughBuffer(
														IN SCARDHANDLE	ulHandleCard,
														IN UCHAR			ucBufferNumber,
														IN ULONG   		ulPageAdr
														);


#ifdef __cplusplus
}
#endif




#pragma pack(pop,old_value)
// Restóre the old packing value.

#endif  /* _INC_SCARD_SPI */


/*****************************************************************************
* History:
* $Log: scarddf.h $
* Revision 1.9  2006/02/16 12:20:17  TBruendl
* No comment given
*
* Revision 1.8  2005/06/10 08:49:13  TBruendl
* No comment given
*
* Revision 1.7  2004/03/09 08:36:08  MPetkov
* No comment given
*
* Revision 1.6  2004/02/23 16:49:11  MPetkov
* No comment given
*
* Revision 1.5  2004/02/20 15:01:48  MPetkov
* All commands are supported
*
* Revision 1.4  2004/02/19 14:36:57  MPetkov
* No comment given
*
* Revision 1.3  2004/02/18 16:51:04  MPetkov
* No comment given
*
* Revision 1.2  2004/02/17 18:33:17  MPetkov
* First approach
*
* Revision 1.1  2004/02/13 14:00:56  TBruendl
* No comment given
*
******************************************************************************/

