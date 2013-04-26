/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/syntst/rcs/syntst.h $
* $Revision: 94 $
*-----------------------------------------------------------------------------
* $Author: wfrischauf $
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
*****************************************************************************/

#ifndef _INC_SYNTST
   #define _INC_SYNTST

   #include <winscard.h>
   #include <scard2w.h>
   #include <scard3w.h>

/*****************************************************************************/
/** usefull constants                                                       **/
/*****************************************************************************/


   #define SLESCard2WBP_MAX_DATA_LEN     256   //@cnst Maximum len of data send to the SLE SCard2WBP SC
   #define SLESCard2WBP_PIN_LEN          3     //@cnst Length of PIN


/*****************************************************************************/
/** S28I function interface                                                 **/
/*****************************************************************************/

   #ifdef __cplusplus
extern "C" {
   #endif

   VOID main(VOID);

   VOID TestSCardConnect(VOID);
   VOID TestSCardReconnect(VOID);
   VOID TestSCardDisconnect(VOID);
   VOID HandleError(DWORD dwErrorFlags);

   VOID TestSCard3WBPReadData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPPresentPIN(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPVerifyProtectBit(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPWriteData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPCompareAndProtect(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPChangePIN(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPIsPinPresented(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard3WBPVerifyProtectBitEx(SCARDHANDLE ulHandleSmartcard);

   VOID TestSCard2WBPReadData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPPresentPIN(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPReadProtectionMemory(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPWriteData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPCompareAndProtect(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPReadErrorCounter(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPIsPinPresented(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPChangePIN(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard2WBPReadSecurityMemory(SCARDHANDLE ulHandleSmartcard);

   //MP010321+   I2C bus cards in test_i2c.c
   VOID TestSCard_I2C_Init(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard_I2C_ReadData(SCARDHANDLE ulHandleSmartcard);
   VOID TestSCard_I2C_WriteData(SCARDHANDLE ulHandleSmartcard);
   //MP010321.

   VOID TestSCard4404ReadData(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCard4404WriteData(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCard4404VerifyUserCode(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCardEraseErrorCounter(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCardEraseUserMemory(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCardEraseScratchPadMemory(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCard4404Status(SCARDHANDLE ulHandleSmartCard);
   VOID TestSCard4404ChangeUserCode(SCARDHANDLE ulHandleSmartCard);
   
   BOOL SelectReader(VOID);

   GPCHAR StrError(OKERR eErr);
   VOID ErrorMessage(OKERR eErr);

   VOID WriteBuffer(GPBYTE pbBuffer, ULONG ulLength, GPUSHORT pusLineNumb,
                    ULONG ulPos);


   #ifdef __cplusplus
}
   #endif


#endif  /* _INC_SYNTST */


/*****************************************************************************
* History:
* $Log: syntst.h $
* Revision 1.9  2006/02/16 12:20:54  TBruendl
* No comment given
*
* Revision 1.8  2002/05/15 07:08:17  TBruendl
* SCard3WBPVerifyProtectBitEx added
*
* Revision 1.7  2001/06/07 09:45:18  CHintersteiner
* No comment given
*
* Revision 1.6  2001/03/26 12:45:16  MPetkov
* No comment given
*
* Revision 1.5  2001/02/26 12:32:18  TBruendl
* No comment given
*
* Revision 1.3  2001/01/26 12:41:09  TBruendl
* No comment given
*
* Revision 1.2  2000/11/16 09:12:50  TBruendl
* No comment given
*
* Revision 1.1  2000/11/06 06:57:14  TBruendl
* No comment given
*
* Revision 1.6  2000/02/07 11:52:53  TBruendl
* update copyright info
*
* Revision 1.5  1999/04/19 08:47:02  TBruendl
* No comment given
*
* Revision 1.4  1999/03/04 12:25:39  TBruendl
* No comment given
*
* Revision 1.3  1999/02/22 16:36:40  GWildmann
* add IsPinPresented function
*
* Revision 1.2  1999/02/16 14:31:13  GWildmann
* correct Help-text and EFUNC names
*
* Revision 1.1  1998/12/10 07:12:15  TBruendl
* No comment given
*
******************************************************************************/

