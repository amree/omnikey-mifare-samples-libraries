Attribute VB_Name = "SCard2WBP"
' ********************************************
' Functions
' ********************************************
'
' Read Bytes to Card
' Parameters:
'       hCard           = Handle to current Card
'       ulBytesToRead   = Number of Bytes to Read
'       pbData          = Array of Bytes containing data
'       ulAddress       = Offset where read starts
'
Public Declare Function SCard2WBPReadData Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByVal ulBytesToRead As Long, _
     ByRef pbData As Byte, _
     ByVal ulAddress As Long) As Long
    
'
' Read Protection Bits of first 32 Bytes
'       hCard           = Handle to current Card
'       ulDataLen       = Length of pbData (have to be 4)
'       pbData          = Returned Data
'
Public Declare Function SCard2WBPReadProtectionMemory Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByVal ulDataLen As Long, _
     ByRef pbData As Byte) As Long

'
' Write Bytes to Card
' Parameters:
'       hCard           = Handle to current Card
'       ulDataLen       = Size of pbData
'       pbData          = Array of Bytes storing data
'       ulAddress       = Offset where write starts
'
Public Declare Function SCard2WBPWriteData Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByVal ulDataLen As Long, _
     ByRef pbData As Byte, _
     ByVal ulAddress As Long) As Long
'
' Compare bytes and protect them if they are equal
' Parameters:
'       hCard       = Handle to current Card
'       bData       = Bytes to compare with
'       ulAddress   = Starting to compare at this Address
'
Public Declare Function SCard2WBPCompareAndProtect Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByRef bData As Byte, _
     ByVal ulAddress As Long) As Long

'
' Presents a PIN
' Parameters:
'       hCard        = Handle to current Card
'       ulPINLen     = Length of PIN (have to be 3)
'       pbPIN        = Byte-array containing PIN
'
Public Declare Function SCard2WBPPresentPIN Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByVal ulPINLen As Long, _
     ByRef pbPIN As Byte) As Long

'
' Change PIN of current Card
' Parameters:
'       hCard           = Handle to current Card
'       ulOldPINLen     = Length of old PIN (have to be 3)
'       pbOldPIN        = Byte-array containing old PIN
'       ulNewPINLen     = Length of new PIN (have to be 3)
'       pbNewPIN        = Byte-array containing new PIN
'
Public Declare Function SCard2WBPChangePIN Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByVal ulOldPINLen As Long, _
     ByRef pbOldPIN As Byte, _
     ByVal ulNewPINLen As Long, _
     ByRef pbNewPIN As Byte) As Long

'
' Check if PIN is presented
' Parameters
'       hCard           = Handle to current Card
'       pfPinPresented  = TRUE  (1) if PIN is already presented
'                         FALSE (0) if PIN is not presented
'       ATTENTION:  In VB TRUE is -1 in C/C++ TRUE is 1
'                   FALSE is 0 in VB and C/C++
'
Public Declare Function SCard2WBPIsPinPresented Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByRef pfPinPresented As Long) As Long
