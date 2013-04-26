/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/syntst/rcs/scard2w.c $
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
#if  defined S_WNT
   #include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard2WBPReadData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[256];
   ULONG  ulDataLen;
   ULONG  ulAddress;
   ULONG ulTime1,ulTime2;

   SCRNClear();
   SCRNPutTextAt( 1, 29, "TEST SCard2WBPRead");
   SCRNPutTextAt( 2, 29, "-------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datalength         :");
   ulDataLen=SCRNGetULongAt(usLine++,23,1,256);
   SCRNPutTextAt(usLine, 2,"Address            :");
   ulAddress=SCRNGetULongAt(usLine++,23,0,255);

   /*---- Call function to test ----*/
   ulTime1=GetTickCount();
   eErr = SCard2WBPReadData(ulHandleSmartCard,
                          ulDataLen,
                          abData,
                          ulAddress);


   ulTime2=GetTickCount();
   ulTime2-=ulTime1;
   StrPrintf(szText," (%dms)",ulTime2);
   SCRNPutTextAt(usLine++,2,szText);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr == NO_ERROR)
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
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard2WBPPresentPIN(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abPIN[16];

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard2WBPPresentPin");
   SCRNPutTextAt( 2, 27, "-------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"PIN (3 Byte)    :");
   SCRNGetTextAt(usLine++, 20,3, abPIN, sizeof(abPIN));

   /*---- Call function to test ----*/


   eErr = SCard2WBPPresentPIN(ulHandleSmartCard,
                          3,
                          abPIN);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard2WBPReadProtectionMemory(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[16];

   SCRNClear();
   SCRNPutTextAt( 1, 24, "TEST SCard2WBPReadProtectionMemory");
   SCRNPutTextAt( 2, 24, "-----------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);

   /*---- Call function to test ----*/
   eErr = SCard2WBPReadProtectionMemory(ulHandleSmartCard,
                                      4L,
                                      abData);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr == NO_ERROR)
      {
      usLine+=2;
      WriteBuffer(abData, 4L, &usLine, 0);
      }

   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}



/*****************************************************************************/
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard2WBPWriteData(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[257];
   ULONG  ulDataLen;
   ULONG  ulAddress;
   ULONG ulTime1,ulTime2;





   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard2WBPWriteData");
   SCRNPutTextAt( 2, 27, "-------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Datalength  :");
   ulDataLen=SCRNGetULongAt(usLine++,16,1,256);
   SCRNPutTextAt(usLine, 2,"Data        :");
   SCRNGetTextAt(usLine++, 16,(USHORT)ulDataLen, abData, sizeof(abData));
   SCRNPutTextAt(usLine, 2,"Address     :");
   ulAddress=SCRNGetULongAt(usLine++,16,0,255);

   /*---- Call function to test ----*/
   ulTime1=GetTickCount();

   eErr = SCard2WBPWriteData(ulHandleSmartCard,
                           ulDataLen,
                           abData,
                           ulAddress);

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
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard2WBPCompareAndProtect(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abData[8];
   ULONG  ulAddress;

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard2WBPCompareAndProtect");
   SCRNPutTextAt( 2, 27, "--------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Databyte    :");
   SCRNGetTextAt(usLine++, 16,1,abData,sizeof(abData));
   SCRNPutTextAt(usLine, 2,"Address     :");
   ulAddress=SCRNGetULongAt(usLine++,16,0,255);

   /*---- Call function to test ----*/
   eErr = SCard2WBPCompareAndProtect(ulHandleSmartCard,
                                   abData[0],
                                   ulAddress);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard2WBPReadErrorCounter(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   bErrorCount;
   BYTE   szText[80];

   SCRNClear();
   SCRNPutTextAt( 1, 27, "TEST SCard2WBPReadErrorCounter");
   SCRNPutTextAt( 2, 27, "-------------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);

   /*---- Call function to test ----*/
   eErr = SCard2WBPReadErrorCounter(ulHandleSmartCard,
                                  &bErrorCount);


   StrPrintf(szText,"Errorcount: %02X", bErrorCount);
   SCRNPutTextAt(13, 1, szText);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard2WBPChangePIN(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BYTE   abOldPIN[4];
   BYTE   abNewPIN[4];

   SCRNClear();
   SCRNPutTextAt( 1, 30, "TEST SCard2WBPChangePIN");
   SCRNPutTextAt( 2, 30, "------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);
   SCRNPutTextAt(usLine, 2,"Old PIN (3 Byte):");
   SCRNGetTextAt(usLine++, 20, 3, abOldPIN, sizeof(abOldPIN));
   SCRNPutTextAt(usLine, 2,"New PIN (3 Byte):");
   SCRNGetTextAt(usLine++, 20, 3, abNewPIN, sizeof(abNewPIN));

   /*---- Call function to test ----*/
   eErr = SCard2WBPChangePIN(ulHandleSmartCard,
                           3, abOldPIN,
                           3, abNewPIN);

   /*---- Display results ----*/
   ErrorMessage(eErr);


   /*---- Wait for confirmation ----*/
   SCRNPutTextAt(23,1,"< Press any key to continue >");
   SCRNGetChar();
   return;
}


/*****************************************************************************/
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/


/*****************************************************************************/
/** SLE SCard2WBP commands                                                       **/
/*****************************************************************************/

VOID TestSCard2WBPIsPinPresented(SCARDHANDLE ulHandleSmartCard)
{
   OKERR eErr = NO_ERROR;
   USHORT usLine = 4;
   BOOL   fPinPresented = FALSE;

   SCRNClear();
   SCRNPutTextAt( 1, 25, "TEST SCard2WBPIsPinPresented");
   SCRNPutTextAt( 2, 25, "-----------------------");

   /*---- Get input parameters ----*/
   sprintf(szText,"Handle             : 0x%08X \n", ulHandleSmartCard);
   SCRNPutTextAt(usLine++, 2, szText);

   /*---- Call function to test ----*/
   eErr = SCard2WBPIsPinPresented(ulHandleSmartCard,
                                &fPinPresented);

   /*---- Display results ----*/
   ErrorMessage(eErr);

   if (eErr == NO_ERROR)
      {
      usLine+=2;
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
* $Log: scard2w.c $
* Revision 1.8  2006/02/16 12:20:52  TBruendl
* No comment given
*
* Revision 1.7  2004/07/09 07:47:38  TBruendl
* No comment given
*
* Revision 1.6  2001/04/18 16:03:45  CHintersteiner
* No comment given
*
* Revision 1.5  2001/02/26 12:32:17  TBruendl
* No comment given
*
* Revision 1.4  2001/01/29 08:04:42  TBruendl
* No comment given
*
* Revision 1.3  2001/01/26 12:41:08  TBruendl
* No comment given
*
* Revision 1.2  2000/11/23 12:02:51  TBruendl
* No comment given
*
* Revision 1.1  2000/11/16 09:12:48  TBruendl
* No comment given
*
* Revision 1.1  2000/11/06 06:57:11  TBruendl
* No comment given
*
* Revision 1.7  2000/06/15 14:00:34  BMildner
* get rid of warnings
*
* Revision 1.6  2000/02/07 12:01:08  TBruendl
* update copyright info
*
* Revision 1.5  1999/04/19 08:46:40  TBruendl
* No comment given
*
* Revision 1.4  1999/02/22 16:38:23  GWildmann
* add IsPinPresented test function
*
* Revision 1.3  1999/02/08 13:50:25  GWildmann
* No comment given
*
* Revision 1.2  1999/02/05 08:49:34  TBruendl
* No comment given
*
* Revision 1.1  1998/12/10 07:13:04  TBruendl
* No comment given
*
* Revision 1.1  1998/04/22 10:34:56  TBruendl
* No comment given
*
* Revision 1.3  1998/03/26 16:51:38  THuettner
* No comment given
*
******************************************************************************/

