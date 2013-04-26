/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/scardcl/rcs/scardcl.h $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
*****************************************************************************/

#ifndef _INC_SCARD_CL
   #define _INC_SCARD_CL


#define MIFARE_STD1K          0x0001
#define MIFARE_STD4K          0x0002
#define MIFARE_ULTRALIGHT     0x0003
#define ICLASS_16KS			   0x001A
#define ICLASS_2KS			   0x0018
#define ICLASS_8x2KS		      0x001C
#define UNKNOWN_CARD          0x0000


/* @consts MIFARE AUTHENTICATION Mode | Indicates <b ucMifareAuthMode> in <f SCardCLMifareStdAuthent> and <b ucMifareAuthModeForNewBlock> in <f SCardCLMifareStdRestoreVal>. */
#define MIFARE_AUTHENT1A      0x60 /* @cnst for authentication with Mifare key A */
#define MIFARE_AUTHENT1B      0x61 /* @cnst for authentication with Mifare key B */

/* @consts MIFARE KEY PROVIDING WAY | Indicates <b ucMifareAccessType> in  <f SCardCLMifareStdAuthent> and <b ucMifareAccessTypeForNewBlock> in <f SCardCLMifareStdRestoreVal>. */
#define MIFARE_KEY_INPUT	   0x00 /* @cnst If key is provided */
#define MIFARE_KEYNR_INPUT	   0x01 /* @cnst If key is taken from the reader Mifare key storage*/	




   #ifdef __cplusplus
extern "C" {
   #endif


OKERR ENTRY SCardCLWriteMifareKeyToReader(
                                        IN SCARDHANDLE    ulHandleCard,
                                        IN SCARDCONTEXT   hContext,
                                        IN LPCTSTR         pcCardReader,
                                        IN ULONG          ulMifareKeyNr,
                                        IN ULONG          ulMifareKeyLen,
                                        IN PUCHAR         pucMifareKey,
                                        IN BOOLEAN        fSecuredTransmission,
                                        IN ULONG          ulEncryptionKeyNr);


OKERR ENTRY SCardCLGetUID(
                         IN SCARDHANDLE    ulHandleCard,
                         IN OUT PUCHAR     pucUID,
                         IN ULONG          ulUIDBufLen,
                         IN OUT PULONG     pulnByteUID);


OKERR ENTRY SCardCLMifareStdAuthent(IN SCARDHANDLE   ulHandleCard,
                                    IN ULONG         ulMifareBlockNr,
                                    IN UCHAR         ucMifareAuthMode,
                                    IN UCHAR         ucMifareAccessType,
                                    IN UCHAR         ucMifareKeyNr,
                                    IN PUCHAR        pucMifareKey,
                                    IN ULONG         ulMifareKeyLen);



OKERR ENTRY SCardCLMifareStdRead(IN SCARDHANDLE ulHandleCard,
                                 IN ULONG       ulMifareBlockNr,
                                 IN OUT PUCHAR  pucMifareDataRead,
                                 IN ULONG       ulMifareDataReadBufLen,
                                 IN OUT PULONG  pulMifareNumOfDataRead);



OKERR ENTRY SCardCLMifareStdWrite(IN SCARDHANDLE   ulHandleCard,
                                  IN ULONG         ulMifareBlockNr,
                                  IN PUCHAR        pucMifareDataWrite,
                                  IN ULONG         ulMifareDataWriteBufLen);


OKERR ENTRY SCardCLMifareLightWrite(IN SCARDHANDLE   ulHandleCard,
                                    IN ULONG         ulMifareBlockNr,
                                    IN PUCHAR        pucMifareDataWrite,
                                    IN ULONG         ulMifareDataWriteBufLen);



OKERR ENTRY SCardCLMifareStdIncrementVal(IN SCARDHANDLE  ulHandleCard,
                                         IN ULONG        ulMifareBlockNr,
                                         IN PUCHAR       pucMifareIncrementValue,
                                         IN ULONG        ulMifareIncrementValueBufLen);


OKERR ENTRY SCardCLMifareStdDecrementVal(IN SCARDHANDLE  ulHandleCard,
                                         IN ULONG        ulMifareBlockNr,
                                         IN PUCHAR       pucMifareDecrementValue,
                                         IN ULONG        ulMifareDecrementValueBufLen);




OKERR ENTRY SCardCLMifareStdRestoreVal(IN SCARDHANDLE    ulHandleCard,
                                       IN ULONG          ulMifareOldBlockNr,
                                       IN ULONG          ulMifareNewBlockNr,
                                       IN BOOLEAN        fMifareSameSector,
                                       IN UCHAR          ucMifareAuthModeForNewBlock,
                                       IN UCHAR          ucMifareAccessTypeForNewBlock,
                                       IN UCHAR          ucMifareKeyNrForNewBlock,
                                       IN PUCHAR         pucMifareKeyForNewBlock,
                                       IN ULONG          ulMifareKeyLenForNewBlock);


OKERR ENTRY SCardCLICCTransmit(IN SCARDHANDLE		ulHandleCard,
								  IN PUCHAR     		pucSendData,				
                         		  IN ULONG       		ulSendDataBufLen,
                        		  IN OUT PUCHAR			pucReceivedData,
								  IN OUT PULONG			pulReceivedDataBufLen);


   #ifdef __cplusplus
}
   #endif









#endif  /* _INC_SCARD_CL */


/*****************************************************************************
* History:
* $Log: scardcl.h $
* Revision 1.10  2006/02/16 12:20:13  TBruendl
* No comment given
*
* Revision 1.9  2005/09/07 11:22:48  TBruendl
* No comment given
*
* Revision 1.5  2004/12/23 07:46:31  TBruendl
* No comment given
*
* Revision 1.3  2004/07/09 07:45:21  TBruendl
* No comment given
*
* Revision 1.1  2004/02/26 09:47:44  TBruendl
* No comment given
*
******************************************************************************/

