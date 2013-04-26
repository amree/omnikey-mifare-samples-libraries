/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/okbase/sw/ok/rcs/okpon.h $
* $Revision: 1.1 $
*-----------------------------------------------------------------------------
* $Author: TBruendl $
*-----------------------------------------------------------------------------
* History:
* $Log: okpon.h $
* Revision 1.1  2000/12/19 14:05:44  TBruendl
* No comment given
*
* Revision 1.1  2000/11/27 08:57:32  TBruendl
* No comment given
*
* Revision 2.6  1998/06/02 07:57:57  CGusenbauer
* No comment given
*
* Revision 2.5  1997/09/24 06:51:36  CGusenbauer
* copyright, next try
*
* Revision 2.4  1997/09/23 12:48:11  CGusenbauer
* removed Safe Concept copyright
* Revision 2.3  1997/04/30 15:05:14  WStoeger
* Structure packing corrected for nested calls
* Revision 2.2  1996/11/25 16:36:14  NGruber
* add handling for msc6.0 (S_KOS2_16 and S_BOOT)
* Revision 2.1  1996/11/20 15:16:10  AWenzel
* Initial revision in 2.1 environment
* Revision 1.1  1996/11/20 15:16:10  AWenzel
* Initial revision
*----------------------------------------------------------------------------
*
* Copyright (c) 2000 OMNIKEY AG
*****************************************************************************/

#if defined _MSC_VER
   #if !(defined S_KOS2_16) && !(defined S_BOOT)
      #pragma warning (disable: 4103) /* allows #pragma for structure alignment */
   #endif

   #if defined S_MSDOS || defined S_BOOT || defined S_WIN
      #pragma pack(2)
   #elif defined S_VXD || defined S_WNT || defined S_KNT
      #pragma pack(8)
   #elif defined S_KOS2_16
      #pragma pack(4)
   #endif
#endif /* _MSC_VER */

/* OS2 */
#ifdef __OS2__
   #pragma pack(4)
#endif

