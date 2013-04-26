/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/dftst/rcs/dftst.h $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
*****************************************************************************/

#ifndef _INC_DFTST
   #define _INC_DFTST


	#ifdef __cplusplus
	extern "C" {
	#endif

   VOID TestSCardConnect(VOID);

   VOID TestSCardReconnect(VOID);

   VOID TestSCardDisconnect(VOID);

   VOID HandleError(
						DWORD dwErrorFlags
						);

	VOID WriteBuffer(
						GPBYTE pbBuffer,
						ULONG ulLength,
						GPUSHORT pusLineNumb,
						ULONG ulPos
						);

   VOID ErrorMessage(
							OKERR eErr
							);


	#ifdef __cplusplus
	}
	#endif

#endif  /* _INC_DFTST */



/*****************************************************************************
* History:
* $Log: dftst.h $
* Revision 1.2  2004/03/09 08:36:47  MPetkov
* No comment given
*
* Revision 1.1  2004/02/17 18:35:09  MPetkov
* First approach
*
******************************************************************************/

