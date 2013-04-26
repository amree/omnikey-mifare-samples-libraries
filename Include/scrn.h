/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/okbase/sw/scrn/rcs/scrn.h $
* $Revision: 1.2 $
*-----------------------------------------------------------------------------
* $Author: TBruendl $
*-----------------------------------------------------------------------------
* History:
* $Log: scrn.h $
* Revision 1.2  2000/12/19 14:06:06  TBruendl
* No comment given
*
* Revision 1.1  2000/11/27 08:53:52  TBruendl
* No comment given
*
* Revision 2.6  1998/06/02 07:50:48  CGusenbauer
* No comment given
*
* Revision 2.5  1997/09/24 06:50:09  CGusenbauer
* copyright, next try
*
* Revision 2.4  1997/09/23 12:46:45  CGusenbauer
* removed Safe Concept copyright
* Revision 2.3  1997/04/14 17:30:47  GWildmann
* Add Function SetColor in Boot-Model
* Revision 2.2  1997/01/14 15:17:56  CGusenbauer
* Implemented boot model.
* Revision 2.1  1996/11/20 15:12:58  AWenzel
* Initial revision in 2.1 environment
* Revision 1.1  1996/11/20 15:12:58  AWenzel
* Initial revision
* Revision 1.1  1996/09/06 11:09:26  HHoffmann
* Initial revision
*----------------------------------------------------------------------------
*
* Copyright (c) 1996-98 Utimaco Safeware AG
*****************************************************************************/

#ifndef _INC_SCRN
#define _INC_SCRN

#if defined S_UNIX || defined S_VMS
   #include <curses.h>
#elif defined S_OS2_32
   #pragma info (nogen)
#elif defined S_WIN || defined S_MSDOS || defined S_WNT || defined S_BOOT
#else
   #error "Es wurde kein Zielsystem definiert!"
#endif

#include <okpon.h>

/****************************************************************************/
/* Wichtige Konstanten                                                      */
/****************************************************************************/

#ifdef S_VMS
   #define cbreak  crmode
   #define keypad(a,b)
   #define nodelay(a,b)
#elif defined S_OS2_32 || defined S_WIN || defined S_UNIX || \
      defined S_MSDOS || defined S_WNT || defined S_BOOT
#else
   #error "Es wurde kein Zielsystem definiert!"
#endif

/***** In der Eingabe verstandene Sonderzeichen *****/

#ifdef S_UNIX
   #define _RETURN       10
#elif defined S_OS2_32 || defined S_WIN || defined S_UNIX || \
      defined S_MSDOS || defined S_WNT || defined S_BOOT
   #define _RETURN       13
#else
   #error "Es wurde kein Zielsystem definiert!"
#endif

#define _BACKSPACE_SCAN_VMS  127
#define _BACKSPACE_SCAN_AIX 1863
#define _BACKSPACE             8
#define _BACKSLASH            36  /* '$' unter UNIX da leichter einzugeben */
#define _TAB                   9
#define _ESC                  27
#define _UP                 KEY_UP   /* KEY_ Konstante aus curses.h */
#define _DOWN               KEY_DOWN
#define _LEFT               KEY_LEFT
#define _RIGHT              KEY_RIGHT

#define _F1                 KEY_F(1)
#define _F2                 KEY_F(2)
#define _F3                 KEY_F(3)
#define _F4                 KEY_F(4)
#define _F5                 KEY_F(5)
#define _F6                 KEY_F(6)
#define _F7                 KEY_F(7)
#define _F8                 KEY_F(8)
#define _F9                 KEY_F(9)
#define _F10                KEY_F(10)

#if defined S_WIN || defined S_MSDOS || defined S_WNT || defined S_BOOT
   #define F_KEY            0
   #ifndef ERR
      #define ERR           -1
   #endif
#elif defined S_OS2_32
   #define F_KEY            0  //??
   #define C_KEY            0  //??
#endif


#if defined(S_BOOT)

	// ---------------------------------------------------------
	// Definition der Farben für das BOOT Modell
	// ---------------------------------------------------------
	
	// Vordergrund Farben
	
	#define VG_SCHWARZ      0x00
	#define VG_BLAU         0x01
	#define VG_GRUEN        0x02
	#define VG_TUERKIS      0x03
	#define VG_ROT          0x04
	#define VG_VIOLETT      0x05
	#define VG_BRAUN        0x06
	#define VG_HELLGRAU     0x07
	#define VG_DUNKELGRAU   0x08
	#define VG_HELLBLAU     0x09
	#define VG_HELLGRUEN    0x0A
	#define VG_HELLTUERKIS  0x0B
	#define VG_HELLROT      0x0C
	#define VG_HELLVIOLETT  0x0D
	#define VG_GELB         0x0E
	#define VG_WEISS        0x0F
	
	// Hintergrund Farben
	
	#define HG_SCHWARZ      0x00
	#define HG_BLAU         0x01
	#define HG_GRUEN        0x02
	#define HG_TUERKIS      0x03
	#define HG_ROT          0x04
	#define HG_VIOLETT      0x05
	#define HG_BRAUN        0x06
	#define HG_HELLGRAU     0x07
	
#endif


/****************************************************************************/
/* Funktions-Prototypen                                                     */
/****************************************************************************/

#ifdef __cplusplus
   extern "C" {
#endif

VOID   ENTRY  SCRNInit              (VOID);
VOID   ENTRY  SCRNClear             (VOID);
VOID   ENTRY  SCRNClearBlock        (USHORT usRow1, USHORT usColumn1,
                                     USHORT usRow2, USHORT usColumn2);
INT    ENTRY  SCRNGetChar           (VOID);
VOID   ENTRY  SCRNGetCursorType     (GPUSHORT pusStartZeile,
                                     GPUSHORT pusEndZeile);
BOOL   ENTRY  SCRNGetText           (USHORT usFieldLen, GPSTR pszText,
                                     USHORT usTextLen);
BOOL   ENTRY  SCRNGetText2          (USHORT usFieldLen, GPSTR pszText,
                                     USHORT usTextLen, BOOL fHideInput);
BOOL   ENTRY  SCRNGetTextAt         (USHORT usRow, USHORT usColumn,
                                     USHORT usFieldLen, GPSTR pszText,
                                     USHORT usTextLen);
VOID   ENTRY  SCRNExit              (VOID);
ULONG  ENTRY  SCRNGetULong          (ULONG ulMin, ULONG ulMax);
ULONG  ENTRY  SCRNGetULongAt        (USHORT usRow, USHORT usColumn,
                                     ULONG  ulMin, ULONG  ulMax);
VOID   ENTRY  SCRNPutText           (GPSTR pszText);
VOID   ENTRY  SCRNPutTextAt         (USHORT usRow, USHORT usColumn,
                                     GPSTR pszText);
VOID   ENTRY  SCRNSetCursorPosition (USHORT usRow, USHORT usColumn);
VOID   ENTRY  SCRNSetCursorType     (BOOL fCursorOff, USHORT usStartZeile,
                                     USHORT usEndZeile);
BOOL   ENTRY  SCRNKeyPressed        (GPULONG pulKey);
USHORT ENTRY  SCRNGetFuncKey        (VOID);
VOID   ENTRY  SCRNPutHex            (USHORT usStartLine, GPBYTE pbBuffer,
                                     ULONG ulLength, GPUSHORT pusNextLine);
#if defined S_BOOT
   VOID ENTRY SCRNPutChar           (CHAR cChar);
	VOID ENTRY SCRNSetColor          (BYTE bBackGround,BYTE bForeGround);
	VOID ENTRY SCRNCenterTextAt      (USHORT usRow,GPSTR pszText);
#endif
/*
** Macros for compatibility of old style programs
*/
#define SCRNGetUShort(usMin, usMax)    (USHORT)SCRNGetULong((ULONG) usMin, (ULONG) usMax)
#define SCRNGetUShortAt(usRow,usColumn,usMin, usMax)  (USHORT)SCRNGetULongAt(usRow, usColumn, (ULONG) usMin, (ULONG) usMax)

#ifdef __cplusplus
   }
#endif

#include <okpoff.h>

#endif /* _INC_SCRN */
