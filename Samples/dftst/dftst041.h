/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/dftst/rcs/dftst041.h $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
*
* Test functions
*****************************************************************************/

#ifndef _INC_DFTST041
   #define _INC_DFTST041

	
	#ifdef __cplusplus
	extern "C" {
	#endif
		

	//
	// Read
	//
	VOID TestAT45DB041_ContinuousArrayRead (
											SCARDHANDLE ulHandleSmartCard
											);

	VOID TestAT45DB041_MainMemoryPageRead (
										SCARDHANDLE ulHandleSmartCard
										);

	VOID TestAT45DB041_BufferRead (
									SCARDHANDLE ulHandleSmartCard
									);
	
	VOID TestAT45DB041_StatusRegRead(
				 					SCARDHANDLE ulHandleSmartCard
				 					);


	//
	// Program and erase test functions
	//
	VOID TestAT45DB041_BufferWrite(
											SCARDHANDLE ulHandleSmartCard
											);


	VOID TestAT45DB041_BufferToMainMemoryPageProgram (
											SCARDHANDLE ulHandleSmartCard
											);

	VOID TestAT45DB041_PageErase (
											SCARDHANDLE ulHandleSmartCard
											);


	VOID TestAT45DB041_BlockErase (
											SCARDHANDLE ulHandleSmartCard
											);


	VOID TestAT45DB041_MainMemoryPageProgramThroughBuffer (
											SCARDHANDLE ulHandleSmartCard
											);


	//
	// Additional commands
	//
	VOID TestAT45DB041_MainMemoryPageToBufferTransfer(
											SCARDHANDLE ulHandleSmartCard
											);

	VOID TestAT45DB041_MainMemoryPageToBufferCompare(
											SCARDHANDLE ulHandleSmartCard
											);

	VOID TestAT45DB041_AutoPageRewriteThroughBuffer(
													SCARDHANDLE ulHandleSmartCard
													);

	#ifdef __cplusplus
	}
	#endif


#endif  /* _INC_DFTST041 */


/*****************************************************************************
* History:
* $Log: dftst041.h $
* Revision 1.6  2004/03/09 08:36:52  MPetkov
* No comment given
*
* Revision 1.5  2004/02/23 16:48:42  MPetkov
* No comment given
*
* Revision 1.4  2004/02/20 15:01:12  MPetkov
* All commands
*
* Revision 1.3  2004/02/19 14:37:49  MPetkov
* No comment given
*
* Revision 1.2  2004/02/18 16:51:24  MPetkov
* No comment given
*
* Revision 1.1  2004/02/17 18:35:11  MPetkov
* First approach
*
******************************************************************************/

