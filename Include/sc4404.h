/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/sc4404/rcs/sc4404.h $
* $Revision: 94 $
*-----------------------------------------------------------------------------
* $Author: wfrischauf $
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
*****************************************************************************/

#ifndef _INC_SC4404
   #define _INC_SC4404

   #include <windows.h>
   #ifndef S_WNT
      #define S_WNT
   #endif
   #include <ok.h>
   #include <winscard.h>

/*****************************************************************************/
/** CONSTANTS                                                               **/
/*****************************************************************************/
#define  SCARD4404_MEMORY_SIZE_IN_BIT            416
#define  SCARD4404_MEMORY_COUNTER_SIZE_IN_BIT     64
#define  SCARD4404_ERROR_COUNTER_SIZE_IN_BIT       4

#define  SCARD4404_MEMORY_COUNTER_ADDRESS         112
#define  SCARD4404_ERROR_COUNTER_ADDRESS          80
#define  SCARD4404_SCRATCH_PAD_MEMORY_ADDRESS     96


/*****************************************************************************/
/** FUNCTIION PROTOTYPES                                                    **/
/*****************************************************************************/

   #ifdef __cplusplus
extern "C" {
   #endif

OKERR ENTRY SCard4404ReadData(
                                 IN  SCARDHANDLE ulHandleSmartCard,
                                 IN  ULONG       ulBitsToRead,
                                 IN  ULONG       ulBitAddress,
                                 OUT LPBYTE      pbReadBuffer,
                                 ULONG           ulReadBufferSize);

OKERR ENTRY SCard4404WriteData(
                                 IN  SCARDHANDLE  ulHandleSmartCard,
                                 IN  LPBYTE       pbData,
                                 IN  ULONG        ulBitsToWrite,
                                 IN  ULONG        ulBitAddress);

OKERR ENTRY SCard4404EraseUserMemory(
                                 IN  SCARDHANDLE  ulHandleSmartCard,
                                 IN  ULONG        ulBitAddress);

OKERR ENTRY SCard4404EraseScratchPadMemory(
                                 IN  SCARDHANDLE  ulHandleSmartCard,
                                 IN  ULONG        ulBitAddress);

OKERR ENTRY SCard4404EraseErrorCounter(
                                 IN  SCARDHANDLE  ulHandleSmartCard,
                                 IN  ULONG        ulBitAddress);

OKERR ENTRY SCard4404VerifyUserCode(
                                 IN  SCARDHANDLE  ulHandleSmartCard,
                                 IN  LPBYTE       pbData);

OKERR ENTRY SCard4404ChangeUserCode(
								IN  SCARDHANDLE  ulHandleSmartCard,
								IN  LPBYTE       pbOldPin,
								IN  LPBYTE       pbNewPin);

   #ifdef __cplusplus
}
   #endif


#endif  /* _INC_SC4404 */


/*****************************************************************************
* History:
* $Log: sc4404.h $
* Revision 1.6  2006/11/14 11:44:06  CHintersteiner
* No comment given
*
* Revision 1.5  2006/02/16 12:21:42  TBruendl
* No comment given
*
* Revision 1.4  2005/06/10 08:49:57  TBruendl
* No comment given
*
* Revision 1.3  2001/08/14 07:25:20  CHintersteiner
* No comment given
*
* Revision 1.2  2001/06/29 12:48:14  CHintersteiner
* No comment given
*
* Revision 1.1  2001/06/07 09:42:01  CHintersteiner
* No comment given
*
******************************************************************************/

