/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/okbase/sw/ok/rcs/okpon8.h $
* $Revision: 1.1 $
*-----------------------------------------------------------------------------
* $Author: TBruendl $
*-----------------------------------------------------------------------------
* History:
* $Log: okpon8.h $
* Revision 1.1  2000/12/19 14:05:46  TBruendl
* No comment given
*
* Revision 1.1  2000/11/27 08:57:34  TBruendl
* No comment given
*
* Revision 2.6  1998/06/02 07:57:58  CGusenbauer
* No comment given
*
* Revision 2.5  1997/09/24 06:51:37  CGusenbauer
* copyright, next try
*
* Revision 2.4  1997/09/23 12:48:12  CGusenbauer
* removed Safe Concept copyright
* Revision 2.3  1997/04/30 15:05:15  WStoeger
* Structure packing corrected for nested calls
* Revision 2.2  1996/11/25 16:36:14  NGruber
* add handling for msc6.0 (S_KOS2_16 and S_BOOT)
* Revision 2.1  1996/11/21 07:21:20  AWenzel
* Initial revision for 2.1 environment
* Revision 1.1  1996/11/21 07:21:20  AWenzel
* Initial revision
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
   #pragma pack(8)
#endif /* _MSC_VER */

/* OS2 */
#ifdef __OS2__
   #pragma pack(8)
#endif

