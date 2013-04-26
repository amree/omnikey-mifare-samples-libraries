/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/okbase/sw/ok/rcs/okos.h $
* $Revision: 1.1 $
*-----------------------------------------------------------------------------
* $Author: TBruendl $
*-----------------------------------------------------------------------------
* History:
* $Log: okos.h $
* Revision 1.1  2000/12/19 14:05:43  TBruendl
* No comment given
*
* Revision 1.1  2000/11/27 08:57:31  TBruendl
* No comment given
*
* Revision 2.9  1998/06/02 07:57:57  CGusenbauer
* No comment given
*
* Revision 2.8  1997/11/28 12:29:17  CGusenbauer
* disabled warning 4504 for win16
*
* Revision 2.7  1997/09/24 06:51:36  CGusenbauer
* copyright, next try
*
* Revision 2.6  1997/09/23 12:48:11  CGusenbauer
* removed Safe Concept copyright
* Revision 2.5  1997/09/12 14:38:44  GWildmann
* Additional defines for VXD - build
* Revision 2.4  1997/04/03 18:34:46  GWildmann
* Remove defined S_BOOT because MSC6.00 doesn't support #pragma warning
* Revision 2.3  1996/12/27 11:01:38  GW
* Modifications for VXD model implementation of GSENC
* Revision 2.2  1996/12/27 11:01:38  AWenzel
* definitions for S_VXD added
* Revision 2.1  1996/11/20 15:16:10  AWenzel
* Initial revision in 2.1 environment
* Revision 1.1  1996/11/20 15:16:10  AWenzel
* Initial revision
* Revision 1.2  1996/10/31 16:44:50  HSchuetz
* Error Fix: 'warning (default:' was replaced by 'warning (disable:'
* Revision 1.1  1996/09/16 06:47:54  HSchuetz
* Initial revision
*----------------------------------------------------------------------------
*
* Copyright (c) 2000 OMNIKEY AG
*****************************************************************************/

#ifndef _INC_OKOS
#define _INC_OKOS


/* Disabling warnings allows usage of WIN32 <windows.h> at warning level 4   */

#if defined _MSC_VER
   /* remove defined S_BOOT because MSC6.00 doesn't support #pragma warning  */
   #if defined S_MSDOS || defined S_WIN
      #pragma warning (disable: 4001) /*nonstd. extension 'single line comm. */
      #pragma warning (disable: 4057) /*indirection to slightly diff. types  */
      #pragma warning (disable: 4103) /* allows #pragma for structure alignment */
      #pragma warning (disable: 4209) /*non.ex. benign typedef redefinition  */
      #pragma warning (disable: 4505) /*unreferenced functions removed       */
      #pragma warning (disable: 4699) /*Precompiled Headers ...              */
   #elif defined S_VXD || defined S_WNT || defined S_KNT
      #pragma warning (disable: 4001) /*nonstd. extension 'single line comm. */
      #pragma warning (disable: 4057) /*'uns. char *' differs in indirection */
      #pragma warning (disable: 4103) /* allows #pragma for structure alignment */
      #pragma warning (disable: 4115) /*named type definition in parentheses */
      #pragma warning (disable: 4200) /*non.ex. zero-sized array in str/union*/
      #pragma warning (disable: 4201) /*non.ex. nameless struct/union        */
      #pragma warning (disable: 4209) /*non.ex. benign typedef redefinition  */
      #pragma warning (disable: 4214) /*non.ex. bit field types other th. int*/
      #pragma warning (disable: 4514) /*unreferenced inline function removed */
   #endif
#endif /* _MSC_VER */

#if defined S_VXD
   /* standard definitions moved from CFLAGS to reduce CL command line length     */
   #define _X86_
   #define WANTVXDWRAPS
   #define VTOOLSD
   #define IS_32
   #if defined OKDEBUG
      #define DEBUG
   #endif
   #if defined WFW311 && !defined WIN31
      #define WIN31
   #endif
   /* Disabling warnings allows usage of <vtoolsc.h> at warning level 4           */
   #pragma warning (disable: 4032) /*formal parameter 1 has different type when...*/
   #pragma warning (disable: 4229) /*anachronism used: modifiers on data ignored  */
#endif

#endif /* _INC_OKOS */
