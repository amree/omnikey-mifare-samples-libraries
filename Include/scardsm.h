/*****************************************************************************
@doc
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/scardsm/rcs/scardsm.h $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 -2006 OMNIKEY
*****************************************************************************/

#ifndef _INC_SCARD_SM
   #define _INC_SCARD_SM
	
   #include <windows.h>
   #ifndef S_WNT
      #define S_WNT
   #endif
	
#include <ok.h>


#ifdef __cplusplus
extern "C"
{
#endif


#define MAX_USER_ZONES 										8
#define MAX_USER_ZONE_LENGTH								256
#define MAX_PAGE_LENGTH										64

#define DEFAULT_SM_SLAVE_ADDRESS							0xb0
#define PASSWORD_LENGTH										3

#define HOST_RANDOM_NUMBER_LEN							8


//	
// Verify password command b3,b2 indicating the passoword index used in the compare operation
//				
#define AT88SC153_WRITE_PASSWORD_0_INDEX				0x00
#define AT88SC153_READ_PASSWORD_0_INDEX				0x02
#define AT88SC153_WRITE_PASSWORD_1_INDEX				0x01
#define AT88SC153_READ_PASSWORD_1_INDEX				0x03
//
// Secure code password is the same as WRITE_PASSWORD_1
//
#define AT88SC153_SECURE_CODE_INDEX						0x01

//
// Fuse indeces
//
#define AT88SC153_FAB_FUSE_INDEX							0x01
#define AT88SC153_CMA_FUSE_INDEX							0x02
#define AT88SC153_PER_FUSE_INDEX							0x04


#define AT88SC153_PASSWORD_CONFIG_ZONE_ADR  			0x30
#define AT88SC1608_PASSWORD_CONFIG_ZONE_ADR  		0x40


#define AT88SC153_AUTHENTICATION_ATTEMPTS_COUNTER_ADR 	0x20

// Limits of the bit field
#define AT88SC153_VERIFY_PASSWORD_INDEX_MASK			0x03
#define AT88SC1608_VERIFY_PASSWORD_INDEX_MASK		0x0f

#define PAC_SUCCESS 											0xff
#define AAC_SUCCESS 											0xff

//ct->
#define AT88SC101_MAX_SIZE           1520
#define AT88SC102_MAX_SIZE           1568
#define AT88SC1003_MAX_SIZE          1600

#define AT88SC10X_FUSE_MANUFACTURER     1
#define AT88SC10X_FUSE_ISSUER           2
#define AT88SC10X_FUSE_ECEN             3
//<-ct

// Constants used as a SecureMemory card type

typedef enum _SCARD_SECURE_MEMORY_TYPE
   {
   AT88SC153 = 0,
   AT88SC1608,
   AT88SC101,
   AT88SC102,
   AT88SC1003,
	// .......
	NOT_SUPPORTED
   }
SCARD_SECURE_MEMORY_TYPE, *PSCARD_SECURE_MEMORY_TYPE;


OKERR SCardSmInit(
						IN SCARDHANDLE	 	   			ulHandleCard, 	
						IN SCARD_SECURE_MEMORY_TYPE   Type
						);

OKERR SCardSmReadUserZone(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE   		pbReadBuffer,
								IN ULONG    	ulReadBufferSize,	
								IN ULONG 		ulUserZone,			
								IN ULONG    	ulByteAdr,   		
								IN ULONG    	ulBytesToRead,		
								OUT PULONG  	pulBytesRead	
								);

OKERR SCardSmReadConfigurationZone(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE   		pbReadBuffer,
								IN ULONG    	ulReadBufferSize,		
								IN ULONG    	ulByteAdr,
								IN ULONG    	ulBytesToRead,
								OUT PULONG  	pulBytesRead
								);

OKERR SCardSmWriteUserZone(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE   		pbWriteBuffer,
								IN ULONG 		ulUserZone,
								IN ULONG    	ulByteAdr,
								IN ULONG    	ulBytesToWrite,
								OUT PULONG  	pulBytesWritten	
								);

OKERR SCardSmWriteConfigurationZone(
	  					 		IN SCARDHANDLE ulHandleCard,   		
	  					  		IN PBYTE   		pbWriteBuffer,
	  					  		IN ULONG    	ulByteAdr,   			
	  					  		IN ULONG    	ulBytesToWrite,		
	  					  		OUT PULONG  	pulBytesWritten	
	  					  		);


OKERR SCardSmVerifyPassword(
	  					 		IN SCARDHANDLE ulHandleCard,   			
	  					  		IN PBYTE   		pbPasswordBuffer,
								IN	UCHAR			ucPasswordIndex,			
								OUT PUCHAR		pucAttemptCounter			
	  					  		);

OKERR SCardSmReadFuses(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE   		pbReadBuffer
								);

OKERR SCardSmWriteFuses(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE    	pucFuseIndex
								);

OKERR SCardSmInitializeAuthentication(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE    	pbHostRandomNumber
								);

OKERR SCardSmVerifyAuthentication(
								IN SCARDHANDLE ulHandleCard,
								IN PBYTE    	pbHostRandomNumber,
								OUT PUCHAR		pucAttemptsCounter
								);

//
// AT88SC153 only
//
OKERR SCardSmUseSlaveAddress(
				 				IN UCHAR    	ucSlaveAddress
								);

//
// AT88SC1608 only
//
OKERR SCardSmSetUserZoneAddress(
								IN SCARDHANDLE ulHandleCard,
								IN UCHAR 		ucUserZone	
								);


//ct->
//
// AT88SC101 AT88SC102 AT88SC1003
//
OKERR SCardSmAT88SC10xRead (
                             IN SCARDHANDLE  ulHandleCard,
                             IN ULONG        ulBitAddress,
                             IN ULONG        ulBitsToRead,
                             OUT LPBYTE      pbReadBuffer,
                             IN ULONG        ulReadBufferSize,
                             OUT PULONG      pulBitsRead
                           );

OKERR SCardSmAT88SC10xErase (
                              IN SCARDHANDLE  ulHandleCard,
                              IN ULONG        ulWordAddress,
                              IN ULONG        ulWordsToErase
                            );

OKERR SCardSmAT88SC10xEraseAZ (
                                IN SCARDHANDLE  ulHandleCard,
                                IN UCHAR        ucAzNumber,
                                IN PBYTE        pbCompareBuffer,
                                IN BOOL         fUseEraseCounter,
                                OUT PUCHAR      pucEC
                              );

OKERR SCardSmAT88SC10xCompareSC (
                                  IN SCARDHANDLE  ulHandleCard,
                                  IN PBYTE        pbCompareBuffer,
                                  OUT PUCHAR      pucAC
                                );

OKERR SCardSmAT88SC10xBlowFuse (
                                 IN SCARDHANDLE  ulHandleCard,
                                 IN UCHAR        ucFuse
                               );

OKERR SCardSmAT88SC10xWrite (
                              IN SCARDHANDLE  ulHandleCard,
                              IN ULONG        ulBitAddress,
                              IN ULONG        ulBitsToWrite,
                              IN LPBYTE       pbWriteBuffer
                            );

OKERR SCardSmAT88SC10xSetFusPin (
                                  IN SCARDHANDLE  ulHandleCard,
                                  IN UCHAR        ucFUS
                                );
//<-ct


#ifdef __cplusplus
}
#endif


#endif  /* _INC_SCARD_SM */


/*****************************************************************************
* History:
* $Log: scardsm.h $
* Revision 1.11  2006/02/16 12:20:30  TBruendl
* No comment given
*
* Revision 1.10  2005/06/10 08:49:25  TBruendl
* No comment given
*
* Revision 1.9  2005/02/11 07:18:01  TBruendl
* support of AT88SC101/102
*
* Revision 1.8  2004/07/20 15:29:13  MPetkov
* No comment given
*
* Revision 1.7  2004/07/15 11:10:11  MPetkov
* No comment given
*
* Revision 1.6  2004/07/09 14:36:18  MPetkov
* All functions are supported.
*
* Revision 1.5  2004/07/08 12:49:57  MPetkov
* Verify password with secure code
*
* Revision 1.4  2004/07/07 17:53:49  MPetkov
* Write operation split in page size
*
* Revision 1.3  2004/07/07 12:13:24  MPetkov
* No comment given
*
* Revision 1.2  2004/07/06 13:22:17  MPetkov
* at88sc1608 and read fuses are supported.
*
* Revision 1.1  2004/07/05 17:02:42  MPetkov
* Card replied. First approach
*
* Revision 1.0  2004/06/28 14:36:08  MPetkov
* No comment given
*
******************************************************************************/

