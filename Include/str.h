/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/okbase/sw/str/rcs/str.h $
* $Revision: 1.3 $
*-----------------------------------------------------------------------------
* $Author: GWildmann $
*-----------------------------------------------------------------------------
* History:
* $Log: str.h $
* Revision 1.3  2001/09/13 16:09:53  GWildmann
* Some Modifications for WinCE (_WIN32_WCE)
*
* Revision 1.2  2000/12/20 06:12:38  TBruendl
* No comment given
*
* Revision 1.1  2000/11/27 08:56:10  TBruendl
* No comment given
*
*----------------------------------------------------------------------------
*
* Copyright (c) 2000-2001 OMNIKEY AG
*****************************************************************************/


#ifndef _INC_STR
#define _INC_STR

#if defined S_SHARC
#elif defined S_BOOT
#elif defined(_WIN32_WCE)
#else
   #include <time.h>
#endif

#include <okpon.h>

/*===========================================================================*/
/* Definition von Konstanten                                                 */
/*===========================================================================*/

/*
   @consts STR Adjust parameters |
   Use these values as <p uiType> parameter in <f StrAdjust>.
*/

#define STR_ADJUST_LEFT       0     //@cnst Leftbound
#define STR_ADJUST_RIGHT      1     //@cnst Rightbound
#define STR_ADJUST_CENTER     2     //@cnst Centered

/*
   @consts STR Trim parameters |
   Use these values as <p uiType> parameter in <f StrTrim>.
*/

#define STR_TRIM_START        0     //@cnst Leading spaces
#define STR_TRIM_END          1     //@cnst Trailing spaces
#define STR_TRIM_ALL          2     //@cnst Leading and trailing spaces

/*
   @consts STR Case parameters |
   Use these values as <p uiType> parameter in <f StrFindChar> etc.
*/
#define STR_CASE_SENSITIVE    0     //@cnst Case sensitive
#define STR_CASE_INSENSITIVE  1     //@cnst Case insensitive

/*===========================================================================*/
/* Funktions-Prototypen                                                      */
/*===========================================================================*/

#if defined S_MVS || defined S_VMS
   #define StrCpy   SSTRCPY
   #define StrNCpy  SSTRNCPY
   #define StrCat   SSTRCAT
   #define StrNCat  SSTRNCAT
   #define StrCmp   SSTRCMP
   #define StrNCmp  SSTRNCMP
   #define StrLen   SSTRLEN
#elif defined S_KOS2_32
   #define StrCpy   SSTRCPY
   #define StrNCpy  SSTRNCPY
   #define StrCat   SSTRCAT
   #define StrNCat  SSTRNCAT
   #define StrCmp   SSTRCMP
   #define StrNCmp  SSTRNCMP
   #define StrLen   SSTRLEN
   #define StrUpr   SSTRUPR
#endif

#ifdef __cplusplus
   extern "C" {
#endif


OKERR ENTRY StrItoa    (ULONG ulValue, PSZ pszString,
                         ULONG ulLength, UINT iRadix);

#if !defined(_WIN32_WCE)
GPCHAR ENTRY StrCpy     (GPCHAR pszDestination, UINT uiDestLen,
                         GPCONSTCHAR pszSource);
GPCHAR ENTRY StrNCpy    (GPCHAR pszDestination, UINT uiDestLen,
                         GPCONSTCHAR pszSource, UINT uiNumber);
#else
#define StrCpy(pszDestination,uiDestLen,pszSource) strcpy(pszDestination,pszSource)
#define StrNCpy(pszDestination,uiDestLen,pszSource,uiNumber) strcpy(pszDestination,pszSource)
#endif

#if !defined(_WIN32_WCE)
GPCHAR ENTRY StrCat     (GPCHAR pszDestination, UINT uiDestLen,
                         GPCONSTCHAR pszSource);
GPCHAR ENTRY StrNCat    (GPCHAR pszDestination, UINT uiDestLen,
                         GPCONSTCHAR pszSource, UINT uiNumber);
#else
#define StrCat(pszDestination,uiDestLen,pszSource) strcat(pszDestination,pszSource)
#define StrNCat(pszDestination,uiDestLen,pszSource,uiNumber) strcat(pszDestination,pszSource)
#endif

#if !defined(_WIN32_WCE)
INT    ENTRY StrCmp     (GPCONSTCHAR pszString1, GPCONSTCHAR pszString2);
INT    ENTRY StrNCmp    (GPCONSTCHAR pszString1, GPCONSTCHAR pszString2,
                         UINT uiNumber);
#else
#define StrCmp(pszString1,pszString2) strcmp(pszString1,pszString2)
#define StrNCmp(pszString1, pszString2, uiNumber) (uiNumber>0) ? memcmp(pszString1,pszString2,uiNumber) : strcmp(pszString1,pszString2)
#endif
INT    ENTRY StrNCaseCmp(GPCONSTCHAR pszString1, GPCONSTCHAR pszString2,
                         UINT uiNumber);

GPCHAR ENTRY StrSet     (GPCHAR pszString, UINT uiStrLen, CHAR cCharacter);
GPCHAR ENTRY StrNSet    (GPCHAR pszString, UINT uiStrLen, CHAR cCharacter,
                         UINT uiNumber);
GPCHAR ENTRY StrFillChar(GPCHAR pszString, UINT uiStrLen, CHAR cCharacter);

GPCHAR ENTRY StrDelChar (GPCHAR pszString, UINT uiStrLen, UINT uiOffset,
                         UINT uiNumber);
GPCHAR ENTRY StrInsChar (GPCHAR pszString, UINT uiStrLen, CHAR cCharacter,
                         UINT uiOffset, UINT uiNumber);
GPCHAR ENTRY StrInsStr  (GPCHAR pszString, UINT uiStrLen, GPCONSTCHAR pszInsStr,
                         UINT uiOffset, UINT uiNumber);
GPCHAR ENTRY StrOverStr (GPCHAR pszString, UINT uiStrLen, GPCONSTCHAR pszInsStr,
                         UINT uiOffset, UINT uiNumber);
GPCHAR ENTRY StrPad     (GPCHAR pszString, UINT uiStrLen, CHAR cCharacter,
                         UINT uiNumber);

GPCHAR ENTRY StrAdjust  (GPCHAR pszString, UINT uiStrlen, UINT uiType);
GPCHAR ENTRY StrTrim    (GPCHAR pszString, UINT uiStrLen, UINT uiType);
VOID   ENTRY StrTrim_r  (GPCONSTCHAR szSource, GPCHAR szDest, UINT uiLen);
GPCHAR ENTRY StrFmt     (GPCHAR pszDestination, UINT uiDestLen,
                         GPCONSTCHAR pszSource, UINT uiMaxLineLen);

GPCHAR ENTRY StrUpr     (GPCHAR pszString);

#if !defined(_WIN32_WCE)
INT    ENTRY StrFindChar(GPCHAR pszString, UINT uiStrLen, CHAR cCharacter,
                         UINT uiCount, UINT uiType);
#else
#define StrFindChar(pszString,uiStrLen,cCharacter,uiCount,uiType) (strchr(pszString,cCharacter) != NULL) ? \
((INT)(strchr(pszString,cCharacter)-pszString)) : (-1)
#endif

#if !defined(_WIN32_WCE)
UINT   ENTRY StrLen     (GPCONSTCHAR pszString);
#else
#define StrLen(pszString) strlen(pszString)
#endif
BOOL   ENTRY StrIsAPrefix (GPCONSTCHAR szPrefix,
                           GPCONSTCHAR szLongstr, UINT uiLen);

LPSZ   ENTRY StrIPToStr (ULONG ulIPAddr);
ULONG  ENTRY StrStrToIP (LPSZ pszIPAddr);

#if defined S_BOOT
INT    StrScanf   (GPCONSTCHAR buf, GPCONSTCHAR fmt, ...);
INT    StrPrintf  (GPCHAR buffer, GPCONSTCHAR format, ...);
#else
#define StrScanf  scanf
#define StrPrintf sprintf
#endif


#ifndef S_SHARC
UINT  ENTRY StrFTime   (GPCHAR s, UINT maxsize, GPCONSTCHAR fmt,
                         const struct tm *t);
#endif

#ifdef __cplusplus
   }
#endif

#include <okpoff.h>

#endif /* _INC_STR */
