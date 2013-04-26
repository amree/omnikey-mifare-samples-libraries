/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/okbase/sw/mem/rcs/mem.h $
* $Revision: 1.3 $
*-----------------------------------------------------------------------------
* $Author: GWildmann $
*-----------------------------------------------------------------------------
* History:
* $Log: mem.h $
* Revision 1.3  2001/09/13 15:54:12  GWildmann
* Some Modification for WinCE (_WIN32_WCE)
*
* Revision 1.2  2000/12/19 14:05:05  TBruendl
* No comment given
*
* Revision 1.1  2000/11/27 08:53:25  TBruendl
* No comment given
*
* Revision 2.13  2000/02/01 09:25:43  CGusenbauer
* eliminated the 'conditional expression' warning
*
* Revision 2.12  2000/01/03 14:37:48  cg
* Debug model: a call to MemFree also sets the pointer to NULL
*
* Revision 2.11  1999/06/09 14:48:57  NGruber
* correct an error for KOS2_16
*
* Revision 2.10  1999/04/12 07:38:59  TBruendl
* MemGetLastEntry and MemGetFreeBytes for boot model added
*
* Revision 2.9  1999/03/12 12:03:10  cg
* made MEM_TRACE default for debug-models; enable it using USCMEMLOG environment variable
*
* Revision 2.8  1998/09/25 08:41:51  WStoeger
* Added MemAllocWithTag function in S_KNT model only.
*
* Revision 2.7  1998/06/02 07:50:27  CGusenbauer
* No comment given
*
* Revision 2.6  1997/09/24 06:50:00  CGusenbauer
* copyright, next try
*
* Revision 2.5  1997/09/23 12:46:35  CGusenbauer
* removed Safe Concept copyright
* Revision 2.4  1997/05/21 10:44:12  CGusenbauer
* new MemT* functions
* Revision 2.3  1997/04/17 11:46:12  NGruber
* MEMVirtToPhys for S_KOS2_16 inserted
* Revision 2.2  1996/11/20 15:12:58  GW
* Add implementation for VXD model
* Revision 2.1  1996/11/20 15:12:58  AWenzel
* Initial revision in 2.1 environment
* Revision 1.1  1996/11/20 15:12:58  AWenzel
* Initial revision
* Revision 1.2  1996/11/11 07:47:24  NGruber
* Changes made for 32 Bit OS/2 Kernel Model (S_KOS2_32)
* Revision 1.1  1996/10/28 13:57:12  HHoffmann
* Initial revision
* Revision 1.1  1996/10/10 08:01:44  HHoffmann
* Initial revision
*----------------------------------------------------------------------------
*
* Copyright (c) 1996-98 Utimaco Safeware AG
*****************************************************************************/


#ifndef _INC_MEM
#define _INC_MEM

#include <okpon.h>

/****************************************************************************/
/* Funktions-Prototypen                                                     */
/****************************************************************************/

#if defined OKDEBUG && ! defined MEM_TRACE_NOT_USED
   /* for trace of mem functions; now default in debug versions;
      to enable it, set environment variable USCMEMLOG and let it point
      to the logfile (full path!)
   */
   #define MEM_TRACE
#endif

#if defined S_MVS || defined S_VMS
   #define MemCpy  MMEMCPY
   #define MemCmp  MMEMCMP
   #define MemSet  MMEMSET
#elif defined S_KOS2_32
   #define MemCpy  MMEMCPY
   #define MemCmp  MMEMCMP
   #define MemSet  MMEMSET
#endif

#ifdef __cplusplus
   extern "C" {
#endif
#ifdef S_KOS2_16
   OKERR ENTRY MemInit (ULONG ulHeapSize);
   ULONG  ENTRY MemVirtToPhys(PVOID pVirt);
#endif

GPVOID ENTRY MemMove(GPVOID pDestination, UINT uiDestLen, GPCONSTVOID pSource,
                     UINT uiNumber);

#if defined(_WIN32_WCE)
#define MemSet(mem,len,bByte,uiNumber) memset(mem,(int)bByte,uiNumber)
	
#else
GPVOID ENTRY MemSet (GPVOID pArray, UINT uiArrLen, BYTE bByte,
                    UINT uiNumber);
#endif

#if defined(_WIN32_WCE)
#define MemCmp(dst,src,srclen) memcmp(dst,src, srclen)
#else
INT    ENTRY MemCmp (GPCONSTVOID pArray1, GPCONSTVOID pArray2, UINT uiNumber);
#endif

#if defined(_WIN32_WCE)
#define MemCpy(dst,dstlen,src,srclen) memcpy(dst,src, (((long)srclen)<=((long)dstlen)) ? srclen : dstlen)
#else
GPVOID ENTRY MemCpy (GPVOID pDestination, UINT uiDestLen, GPCONSTVOID pSource,
                     UINT uiNumber);
#endif

#if defined MEM_TRACE && ! defined S_SHARC && ! defined S_KOS2_16
   #define MemRealloc(b,s)  MemTRealloc(b,s, __FILE__, __LINE__)
   #define MemAlloc(s)      MemTAlloc(s,__FILE__, __LINE__)
   #define MemFree(p)       do { \
                                MemTFree(p, __FILE__, __LINE__); \
                                p = NULL; \
                            } while (p)
#elif defined(_WIN32_WCE)
   #define MemRealloc(b,s)  realloc(b,s)
   #define MemAlloc(s)      malloc(s)
   #define MemFree(p)       free(p)
#else
   GPVOID ENTRY MemRealloc(GPVOID pBuffer, UINT uiSize);

   GPVOID ENTRY MemAlloc(UINT uiSize);

   VOID   ENTRY MemFree(GPVOID pPointer);
#endif /* MEM_TRACE && !S_SHARC */

#if defined S_KNT
   GPVOID ENTRY MemAllocWithTag(UINT uiSize,ULONG ulTag);
#endif

VOID   ENTRY MemTFree(GPVOID pPointer, GPCHAR szFile, INT iLine);
GPVOID ENTRY MemTAlloc(UINT uiSize, GPCHAR szFile, INT iLine);
GPVOID ENTRY MemTRealloc(GPVOID pBuffer,UINT uiSize,GPCHAR szFile, INT iLine);

/* Memory - related Funktionen, die NICHT Systemfunktionen emulieren ! */
/* Man beachte auch den MEM-praefix */

VOID   ENTRY MEMReleaseName(POK_NAME psToBeReleased);
VOID   ENTRY MEMReleaseItem(POK_ITEM psToBeReleased);
BOOL   ENTRY MEMbIsLegalName(POK_NAME psName);

VOID   ENTRY MEM_UlongToMSBFirst (GPBYTE pbBuffer, ULONG ulValue);
ULONG  ENTRY MEM_MSBFirstToUlong (GPBYTE pbBuffer);
VOID   ENTRY MEM_UshortToMSBFirst (GPBYTE pbBuffer, USHORT usValue);
USHORT ENTRY MEM_MSBFirstToUshort (GPBYTE pbBuffer);

ULONG  ENTRY MEM_ntohl(ULONG ulValue);
ULONG  ENTRY MEM_htonl(ULONG ulValue);

OKERR ENTRY MEM_BinToHexString (GPBYTE pbData, UINT uiDataSize,
                                 GPCHAR pszHexString, UINT uiStringSize);
OKERR ENTRY MEM_HexStringToBin (GPCHAR pszHexString,
                                 GPBYTE pbData, GPUINT puiDataSize);

#if defined S_BOOT
UINT MEMGetFreeBytes(VOID);
VOID MEMGetLastEntry(LPUINT puiLastEntry,
                     LPUINT puiMaxEntries);
#endif


#ifdef __cplusplus
   }
#endif

#include <okpoff.h>

#endif /* _INC_MEM */
