Attribute VB_Name = "ScardCL"
' ********************************************
' Functions
' ********************************************
Public Declare Function SCardCLWriteMifareKeyToReader Lib "scardsyn" _
    (ByVal ulHandleCard As Long, _
     ByVal hContext As Long, _
     ByVal pcCardReader As String, _
     ByVal ulMifareKeyNr As Long, _
     ByVal ulMifareKeyLen As Long, _
     ByRef pucMifareKey As Byte, _
     ByVal fSecuredTransmission As Boolean, _
     ByVal ulTransmissionKeyNr As Long) As Long

'OKERR ENTRY SCardCLWriteMifareKeyToReader(
 '                                       IN SCARDHANDLE    ulHandleCard,
  '                                      IN SCARDCONTEXT   hContext,
   '                                     IN PCHAR          pcCardReader,
    '                                    IN ULONG          ulMifareKeyNr,
     '                                   IN ULONG          ulMifareKeyLen,
      '                                  IN PUCHAR         pucMifareKey,
       '                                 IN BOOLEAN        fSecuredTransmission,
        '                                IN ULONG          ulTransmissionKeyNr);
         '

Public Declare Function SCardCLGetUID Lib "scardsyn" _
    (ByVal ulHandleCard As Long, _
     ByRef pucUID As Byte, _
     ByVal ulUIDBufLen As Long, _
     ByRef pulnByteUID As Long) As Long


'OKERR ENTRY SCardCLGetUID(
 '                        IN SCARDHANDLE    ulHandleCard,
  '                       IN OUT PUCHAR     pucUID,
   '                      IN ULONG          ulUIDBufLen,
    '                     IN OUT PULONG     pulnByteUID);



Public Declare Function SCardCLMifareStdRead Lib "scardsyn" _
    (ByVal ulHandleCard As Long, _
     ByVal ulMifareBlockNr As Long, _
     ByRef pucMifareDataRead As Byte, _
     ByVal ulMifareDataReadBufLen As Long, _
     ByRef pulMifareNumOfDataRead As Long) As Long


'OKERR ENTRY SCardCLMifareStdRead(IN SCARDHANDLE ulHandleCard,
 '                                IN ULONG       ulMifareBlockNr,
  '                               IN OUT PUCHAR  pucMifareDataRead,
   '                              IN ULONG       ulMifareDataReadBufLen,
    '                             IN OUT PULONG  pulMifareNumOfDataRead);


Public Declare Function SCardCLMifareStdWrite Lib "scardsyn" _
    (ByVal ulHandleCard As Long, _
     ByVal ulMifareBlockNr As Long, _
     ByRef pucMifareDataWrite As Byte, _
     ByVal ulMifareDataWriteBufLen As Long) As Long


'OKERR ENTRY SCardCLMifareStdWrite(IN SCARDHANDLE   ulHandleCard,
 '                                 IN ULONG         ulMifareBlockNr,
  '                                IN PUCHAR        pucMifareDataWrite,
   '                               IN ULONG         ulMifareDataWriteBufLen);
'

Public Declare Function SCardCLMifareStdAuthent Lib "scardsyn" _
    (ByVal ulHandleCard As Long, _
     ByVal ulMifareBlockNr As Long, _
     ByVal ucMifareAuthMode As Byte, _
     ByVal ucMifareAccessType As Byte, _
     ByVal ucMifareKeyNr As Byte, _
     ByRef pucMifareKey As Byte, _
     ByVal ulMifareKeyLen As Long) As Long




'OKERR ENTRY SCardCLMifareStdAuthent(IN SCARDHANDLE   ulHandleCard,
 '                                   IN ULONG         ulMifareBlockNr,
  '                                  IN UCHAR         ucMifareAuthMode,
   '                                 IN UCHAR         ucMifareAccessType,
    '                                IN UCHAR         ucMifareKeyNr,
     '                               IN PUCHAR        pucMifareKey,
      '                              IN ULONG         ulMifareKeyLen);




Public Declare Function SCardCLMifareStdIncrementVal Lib "scardsyn" _
    (ByVal ulHandleCard As Long, _
     ByVal ulMifareBlockNr As Long, _
     ByRef pucMifareIncrementValue As Byte, _
     ByVal ulMifareIncrementValueBufLen As Long) As Long


'OKERR ENTRY SCardCLMifareStdIncrementVal(IN SCARDHANDLE  ulHandleCard,
 '                                        IN ULONG        ulMifareBlockNr,
  '                                       IN PUCHAR       pucMifareIncrementValue,
   '                                      IN ULONG        ulMifareIncrementValueBufLen);
'

Public Declare Function SCardCLMifareStdDecrementVal Lib "scardsyn" _
    (ByVal ulHandleCard As Long, _
     ByVal ulMifareBlockNr As Long, _
     ByRef pucMifareDecrementValue As Byte, _
     ByVal ulMifareDecrementValueBufLen As Long) As Long



'OKERR ENTRY SCardCLMifareStdDecrementVal(IN SCARDHANDLE  ulHandleCard,
 '                                        IN ULONG        ulMifareBlockNr,
  '                                       IN PUCHAR       pucMifareDecrementValue,
   '                                      IN ULONG        ulMifareDecrementValueBufLen);
'


'OKERR ENTRY SCardCLICCTransmit(IN SCARDHANDLE       ulHandleCard,
'                                  IN PUCHAR             pucSendData,
'                                 IN ULONG              ulSendDataBufLen,
'                                  IN OUT PUCHAR         pucReceivedData,
'                                  IN OUT PULONG         pulReceivedDataBufLen);
'


Public Declare Function SCardCLICCTransmit Lib "scardsyn" _
    (ByVal ulHandleCard As Long, _
     ByRef pucSendData As Byte, _
     ByVal ulSendDataBufLen As Long, _
     ByRef pucReceivedData As Byte, _
     ByRef pulReceivedDataBufLen As Long) As Long


