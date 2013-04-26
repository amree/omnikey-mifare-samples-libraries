Attribute VB_Name = "SCardI2C"
' ********************************************
' Data Types
' ********************************************

'
' Predefined Cardtypes
'
Enum SCARD_I2C_TYPE
   NO_PREDEFINED_CARD_PARAMETERS = 0
   ' I2C cards from ST-Microelectronics:
   ST14C02C
   ST14C04C
   ST14E32
   M14C04
   M14C16
   M14C32
   M14C64
   M14128
   M14256
   ' I2C cards from GEMplus:
   GFM2K
   GFM4K
   GFM32K
   ' I2C cards from Atmel:
   AT24C01A
   AT24C02
   AT24C04
   AT24C08
   AT24C16
   AT24C164
   AT24C32
   AT24C64
   AT24C128
   AT24C256
   AT24CS128
   AT24CS256
   AT24C512
   AT24C1024
   I2C_TYPE_ENUM_TAIL          ' must always be the last entry in this enum!!
End Enum

'
' Card Parameters Structure
'
Public Type SCARD_I2C_CARD_PARAMETERS
    ucPageSize As Byte              ' Maximal number of bytes that can be written in a successive manner, in a single device select phase.
    ucNumberOfAddressBytes As Byte  ' Number of bytes used to address the memory in the I2C card.
    ulMemorySize As Integer         ' The size of the e2prom allocated in the card
End Type

' ********************************************
' Functions
' ********************************************

'
' Initialize an I2C Card
' Parameters:
'       hCard               = Handle to current Card
'       pCardParameters     = Pointer to a SCARD_I2C_CARD_PARAMETERS type
'       lType               = Predefined Cardtype (SCARD_I2C_TYPE)
'
Public Declare Function SCardI2CInit Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByRef pCardParameters As Long, _
     ByVal lType As Long) As Long

'
' Read Bytes from Card
' Parameters:
'       hCard               = Handle to current Card
'       pbReadBuffer        = Array of Bytes where data should be stored in
'       ulReadBufferSize    = Size of ReadBuffer
'       ulAddress           = Offset where read starts
'       ulBytesToRead       = Number of Bytes to read
'
Public Declare Function SCardI2CReadData Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByRef pbReadBuffer As Byte, _
     ByVal ulReadBufferSize As Long, _
     ByVal ulAddress As Long, _
     ByVal ulBytesToRead As Long) As Long

'
' Write Bytes to Card
' Parameters:
'       hCard               = Handle to current Card
'       pbWriteBuffer       = Array of Bytes storing data
'       ulWriteBufferSize   = Size of WriteBuffer
'       ulAddress           = Offset where write starts
'       ulBytesToWrite      = Number of Bytes to write
'
Public Declare Function SCardI2CWriteData Lib "scardsyn" _
    (ByVal hCard As Long, _
     ByRef pbWriteBuffer As Byte, _
     ByVal ulWriteBufferSize As Long, _
     ByVal ulAddress As Long, _
     ByVal ulBytesToWrite As Long) As Long


