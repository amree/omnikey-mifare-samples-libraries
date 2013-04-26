/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/scard3w/rcs/scard3w.h $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*-----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
******************************************************************************/

#ifndef _INC_SCARD3W
   #define _INC_SCARD3W


   #include <windows.h>
   #ifndef S_WNT
      #define S_WNT
   #endif
   #include <ok.h>
   #include <winscard.h>

/*****************************************************************************/
/** CONSTANTS                                                                */
/*****************************************************************************/


   #define SCARD3W_MAX_DATA_LEN     1024
   #define SCARD3W_PIN_LEN          2


/*****************************************************************************/
/** FUNCTION PROTOTYPES                                                      */
/*****************************************************************************/

   #ifdef __cplusplus
extern "C" {
   #endif



   OKERR ENTRY SCard3WBPReadData         (IN  SCARDHANDLE ulHandleSmartCard,
                                           IN  ULONG       ulBytesToRead,
                                           OUT LPBYTE      pbReadBuffer,
                                           IN  ULONG       ulAddress);

   OKERR ENTRY SCard3WBPVerifyProtectBit (IN  SCARDHANDLE ulHandleSmartCard,
                                           IN  ULONG       ulAddress,
                                           OUT LPBOOL      pfProtected);

   OKERR ENTRY SCard3WBPVerifyProtectBitEx(
                IN  SCARDHANDLE ulHandleSmartCard,
                IN  ULONG       ulBytesToRead,
                OUT LPBYTE      pbReadBuffer,
                IN  ULONG       ulAddress);

   OKERR ENTRY SCard3WBPWriteData        (IN  SCARDHANDLE ulHandleSmartCard,
                                           IN  ULONG       ulDataLen,
                                           IN  LPBYTE      pbData,
                                           IN  ULONG       ulAddress,
                                           IN  BOOL        fProtected);

   OKERR ENTRY SCard3WBPCompareAndProtect(IN  SCARDHANDLE ulHandleSmartCard,
                                           IN  BYTE        bData,
                                           IN  ULONG       ulAddress);

   OKERR ENTRY SCard3WBPPresentPIN       (IN  SCARDHANDLE ulHandleSmartCard,
                                           IN  ULONG       ulPINLen,
                                           IN  LPBYTE      pbPIN);

   OKERR ENTRY SCard3WBPChangePIN        (IN  SCARDHANDLE ulHandleSmartCard,
                                           IN  ULONG       ulOldPINLen,
                                           IN  LPBYTE      pbOldPIN,
                                           IN  ULONG       ulNewPINLen,
                                           IN  LPBYTE      pbNewPIN);

   OKERR ENTRY SCard3WBPIsPinPresented   (IN  SCARDHANDLE ulHandleSmartCard,
                                           OUT LPBOOL      pfPinPresented);

   #ifdef __cplusplus
}
   #endif

#endif /* _INC_SCARD3W */

/*****************************************************************************
* History:
* $Log: scard3w.h $
* Revision 1.6  2006/02/16 12:20:08  TBruendl
* No comment given
*
* Revision 1.5  2005/06/10 08:48:45  TBruendl
* No comment given
*
* Revision 1.4  2002/05/15 07:07:41  TBruendl
* SCard3WBPVerifyProtectBitEx added
*
* Revision 1.3  2001/01/26 12:40:14  TBruendl
* No comment given
*
* Revision 1.2  2000/11/16 09:35:49  TBruendl
* No comment given
*
*
******************************************************************************/

