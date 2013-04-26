/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/scard2w/rcs/scard2w.h $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
*****************************************************************************/

#ifndef _INC_SCARD2W
   #define _INC_SCARD2W

   #include <windows.h>
   #ifndef S_WNT
      #define S_WNT
   #endif
   #include <ok.h>
   #include <winscard.h>

/*****************************************************************************/
/** CONSTANTS                                                               **/
/*****************************************************************************/
   #define SCARD2W_MAX_DATA_LEN     256
   #define SCARD2W_PIN_LEN          3




/*****************************************************************************/
/** FUNCTIION PROTOTYPES                                                    **/
/*****************************************************************************/

   #ifdef __cplusplus
extern "C" {
   #endif


   OKERR ENTRY SCard2WBPReadData             (IN  SCARDHANDLE ulHandleSmartCard,
                                              IN  ULONG  ulBytesToRead,
                                              OUT LPBYTE pbData,
                                              IN  ULONG  ulAddress);

   OKERR ENTRY SCard2WBPReadProtectionMemory (IN  SCARDHANDLE ulHandleSmartCard,
                                              IN  ULONG  ulDataLen,
                                              OUT LPBYTE pbData);

   OKERR ENTRY SCard2WBPWriteData            (IN  SCARDHANDLE ulHandleSmartCard,
                                              IN  ULONG  ulDataLen,
                                              IN  LPBYTE pbData,
                                              IN  ULONG  ulAddress);

   OKERR ENTRY SCard2WBPCompareAndProtect    (IN  SCARDHANDLE ulHandleSmartCard,
                                              IN  BYTE bData,
                                              IN  ULONG ulAddress);

   OKERR ENTRY SCard2WBPPresentPIN           (IN  SCARDHANDLE ulHandleSmartCard,
                                              IN  ULONG       ulPINLen,
                                              IN  LPBYTE      pbPIN);

   OKERR ENTRY SCard2WBPChangePIN            (IN  SCARDHANDLE ulHandleSmartCard,
                                              IN  ULONG       ulOldPINLen,
                                              IN  LPBYTE      pbOldPIN,
                                              IN  ULONG       ulNewPINLen,
                                              IN  LPBYTE      pbNewPIN);

   OKERR ENTRY SCard2WBPIsPinPresented       (IN  SCARDHANDLE ulHandleSmartCard,
                                              OUT LPBOOL      pfPinPresented);


   OKERR ENTRY SCard2WBPReadErrorCounter (
                                         IN  SCARDHANDLE ulHandleSmartCard,
                                         OUT LPBYTE pbCounter
                                         );

   #ifdef __cplusplus
}
   #endif


#endif  /* _INC_SCARD2W */


/*****************************************************************************
* History:
* $Log: scard2w.h $
* Revision 1.10  2006/02/16 12:19:58  TBruendl
* No comment given
*
* Revision 1.9  2005/06/10 08:48:35  TBruendl
* No comment given
*
* Revision 1.8  2004/06/15 08:41:55  TBruendl
* No comment given
*
* Revision 1.7  2001/08/13 13:22:14  TBruendl
* No comment given
*
* Revision 1.6  2001/08/08 10:09:18  MFuehrlinger
* No comment given
*
* Revision 1.5  2001/02/26 12:31:31  TBruendl
* No comment given
*
* Revision 1.4  2001/01/26 12:39:45  TBruendl
* No comment given
*
* Revision 1.3  2000/11/16 09:33:46  TBruendl
* No comment given
*
*
******************************************************************************/

