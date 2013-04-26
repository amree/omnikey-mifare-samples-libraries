/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/syntst/rcs/scard3w.c $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*-----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
******************************************************************************/

/*****************************************************************************/
/** GLOBAL INCLUDES                                                         **/
/*****************************************************************************/


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
#include <syntst.h>

/*****************************************************************************/
/**  EXTERN DECLARATIONS                                                    **/
/*****************************************************************************/

/*****************************************************************************/
/**  GLOBAL DECLARATIONS                                                    **/
/*****************************************************************************/

static  CHAR    szText[160] = "\0";           /* Common string for text I/O */


#define MAX_BYTE     0x000000FF
#define MAX_USHORT   0x0000FFFF
#define MAX_ULONG    0xFFFFFFFF


/*****************************************************************************/
/** LOCAL FUNCTION PROTOTYPES                                               **/
/*****************************************************************************/



/*****************************************************************************/
/**  IMPLEMENTATION                                                         **/
/*****************************************************************************/


/*****************************************************************************/
/** SUBROUTINES                                                             **/
/*****************************************************************************/




/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPReadData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[1024];
   ULONG  ulDataLen;
   ULONG  ulAddress;
   ULONG ulTime1,ulTime2;

   SCRNClear();
   SCRNPutTextAt( 1, 29, "TEST SCard3WBPRead");
   SCRNPutTextAt( 2, 29, "-------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datalength         :");
   ulDataLen=SCRNGetULongAt(usLine++,23,1,1024);
   SCRNPutTextAt(usLine, 2,"Address            :");
   ulAddress=SCRNGetULongAt(usLine++,23,0,1023);

   ulTime1=GetTickCount();

   /*---- Call function to test ----*/
   eErr = SCard3WBPReadData(ulHandleSmartCard,
                          ulDataLen,
                          abData,
                          ulAddress);

   ulTime2=GetTickCount();
   ulTime2-=ulTime1;
   StrPrintf(szText," (%dms)",ulTime2);
   SCRNPutTextAt(usLine++,2,szText);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr==NO_ERROR)
      {
      usLine+=2;
      WriteBuffer(abData, ulDataLen, &usLine, 0);
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


VOID TestSCard3WBPVerifyProtectBitEx(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[1024];
   ULONG  ulDataLen;
   ULONG  ulAddress;
   ULONG ulTime1,ulTime2;

   SCRNClear();
   SCRNPutTextAt( 1, 29, "TEST SCard3WBPVerifyProtectBitEx");
   SCRNPutTextAt( 2, 29, "--------------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datalength         :");
   ulDataLen=SCRNGetULongAt(usLine++,23,1,1024);
   SCRNPutTextAt(usLine, 2,"Address            :");
   ulAddress=SCRNGetULongAt(usLine++,23,0,1023);

   ulTime1=GetTickCount();

   /*---- Call function to test ----*/
   eErr = SCard3WBPVerifyProtectBitEx(ulHandleSmartCard,
                          ulDataLen,
                          abData,
                          ulAddress);

   ulTime2=GetTickCount();
   ulTime2-=ulTime1;
   StrPrintf(szText," (%dms)",ulTime2);
   SCRNPutTextAt(usLine++,2,szText);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr==NO_ERROR)
      {
      usLine+=2;
      WriteBuffer(abData, ulDataLen, &usLine, 0);
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPPresentPIN(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abPIN[4];

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard3WBPPresentPin");
   SCRNPutTextAt( 2, 27, "-------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"PIN (2 Byte)    :");
   SCRNGetTextAt(usLine++, 20, 2, abPIN, sizeof(abPIN));

   /*---- Call function to test ----*/

   eErr = SCard3WBPPresentPIN(ulHandleSmartCard,
                            2,
                            abPIN);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPVerifyProtectBit(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   ULONG  ulAddress;
   BOOL   fProtected;

   SCRNClear();
   SCRNPutTextAt( 1, 24, "TEST SCard3WBPVerifyProtectBit");
   SCRNPutTextAt( 2, 24, "-------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Address         :");
   ulAddress=SCRNGetULongAt(usLine++,20,0,1023);

   /*---- Call function to test ----*/
   eErr = SCard3WBPVerifyProtectBit (ulHandleSmartCard,
                                   ulAddress,
                                   &fProtected);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr==NO_ERROR)
      {
      usLine+=2;
      if (fProtected)
         SCRNPutTextAt(usLine, 2,"This byte is PROTECTED");
      else
         SCRNPutTextAt(usLine, 2,"This byte is unprotected");
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}



/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPWriteData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[1025];
   ULONG  ulDataLen;
   ULONG  ulAddress;
   ULONG ulTime1,ulTime2;
   BOOL  fProtect;

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard3WBPWriteData");
   SCRNPutTextAt( 2, 27, "-------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datalength  :");
   ulDataLen=SCRNGetULongAt(usLine++,16,1,1024);
   SCRNPutTextAt(usLine, 2,"Data        :");
   SCRNGetTextAt(usLine++, 16,(USHORT)ulDataLen, abData, sizeof(abData));
   SCRNPutTextAt(usLine, 2,"Address     :");
   ulAddress=SCRNGetULongAt(usLine++,16,0,1023);
   SCRNPutTextAt(usLine, 2,"Protect (0=FALSE/1=TRUE) :");
   fProtect=SCRNGetULongAt(usLine++,30,0,1);

   ulTime1=GetTickCount();

   /*---- Call function to test ----*/

   eErr = SCard3WBPWriteData(ulHandleSmartCard,
                           ulDataLen,
                           abData,
                           ulAddress,
                           fProtect);

   ulTime2=GetTickCount();
   ulTime2-=ulTime1;
   StrPrintf(szText," (%dms)",ulTime2);
   SCRNPutTextAt(usLine++,2,szText);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}

/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPCompareAndProtect(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   bData[2];
   ULONG  ulAddress;

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard3WBPCompareAndProtect");
   SCRNPutTextAt( 2, 27, "--------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datenbyte   :");
   SCRNGetTextAt(usLine++, 16,1,bData,sizeof(bData));
   SCRNPutTextAt(usLine, 2,"Addresse    :");
   ulAddress=SCRNGetULongAt(usLine++,16,0,1023);

   /*---- Call function to test ----*/
   eErr = SCard3WBPCompareAndProtect(ulHandleSmartCard,
                                   bData[0],
                                   ulAddress);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPChangePIN(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abOldPIN[4];
   BYTE   abNewPIN[4];

   SCRNClear();
   SCRNPutTextAt( 1, 30, "TEST SCard3WBPChangePIN");
   SCRNPutTextAt( 2, 30, "------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Old PIN (2 Byte):");
   SCRNGetTextAt(usLine++, 20, 2, abOldPIN, sizeof(abOldPIN));
   SCRNPutTextAt(usLine, 2,"New PIN (2 Byte):");
   SCRNGetTextAt(usLine++, 20, 2, abNewPIN, sizeof(abNewPIN));

   /*---- Call function to test ----*/
   eErr = SCard3WBPChangePIN(ulHandleSmartCard,
                           2, abOldPIN,
                           2, abNewPIN);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard3WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard3WBPIsPinPresented(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BOOL   fPinPresented = FALSE;

   SCRNClear();
   SCRNPutTextAt( 1, 25, "TEST SCard3WBPIsPinPresented");
   SCRNPutTextAt( 2, 25, "-----------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);

   /*---- Call function to test ----*/
   eErr = SCard3WBPIsPinPresented(ulHandleSmartCard,
                                &fPinPresented);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr == NO_ERROR)
      {
      if (fPinPresented)
         SCRNPutTextAt(13, 2, "PIN is presented!");
      else
         SCRNPutTextAt(13, 2, "PIN is not presented!");
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}







/*****************************************************************************
* History:
* $Log: scard3w.c $
* Revision 1.10  2006/02/16 12:20:53  TBruendl
* No comment given
*
* Revision 1.9  2002/05/15 07:08:05  TBruendl
* SCard3WBPVerifyProtectBitEx added
*
* Revision 1.8  2001/08/06 14:26:52  TBruendl
* No comment given
*
* Revision 1.7  2001/04/18 16:03:45  CHintersteiner
* No comment given
*
* Revision 1.6  2001/03/26 12:24:57  CHintersteiner
* time measurment added
*
* Revision 1.5  2001/03/26 07:41:03  CHintersteiner
* No comment given
*
* Revision 1.4  2001/02/26 12:32:17  TBruendl
* No comment given
*
* Revision 1.3  2001/01/29 08:04:43  TBruendl
* No comment given
*
* Revision 1.2  2001/01/26 12:41:09  TBruendl
* No comment given
*
* Revision 1.1  2000/11/16 09:12:49  TBruendl
* No comment given
*
* Revision 1.1  2000/11/06 06:57:10  TBruendl
* No comment given
*
* Revision 1.9  2000/06/15 13:51:43  BMildner
* get rid of warnings
*
* Revision 1.8  2000/02/07 12:01:06  TBruendl
* update copyright info
*
* Revision 1.7  1999/04/19 08:46:32  TBruendl
* No comment given
*
* Revision 1.6  1999/03/04 08:13:32  TBruendl
* No comment given
*
* Revision 1.5  1999/03/02 14:55:28  GWildmann
* Add IsPinPresented test function
*
* Revision 1.4  1999/02/16 14:22:57  GWildmann
* update
*
* Revision 1.3  1999/02/08 13:28:22  GWildmann
* Test
*
* Revision 1.1  1998/12/10 07:02:07  TBruendl
* No comment given
*
* Revision 1.1  1998/04/22 10:34:56  TBruendl
* No comment given
*
******************************************************************************/

