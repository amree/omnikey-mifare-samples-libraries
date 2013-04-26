VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Synchronous API VB Sample"
   ClientHeight    =   8040
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6255
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   8040
   ScaleWidth      =   6255
   StartUpPosition =   3  'Windows-Standard
   Begin VB.Frame Frame4 
      Caption         =   "Card Operations"
      Height          =   2415
      Left            =   3960
      TabIndex        =   20
      Top             =   2520
      Width           =   2175
      Begin VB.ComboBox CARDTYPE 
         Height          =   315
         ItemData        =   "Form1.frx":1272
         Left            =   120
         List            =   "Form1.frx":1274
         Style           =   2  'Dropdown-Liste
         TabIndex        =   24
         Top             =   360
         Width           =   1935
      End
      Begin VB.CommandButton READBUTTON 
         Caption         =   "Read Data"
         Height          =   375
         Left            =   120
         TabIndex        =   23
         Top             =   840
         Width           =   1935
      End
      Begin VB.CommandButton WRITEBUTTON 
         Caption         =   "Write Data"
         Enabled         =   0   'False
         Height          =   375
         Left            =   120
         TabIndex        =   22
         Top             =   1800
         Width           =   1935
      End
      Begin VB.CommandButton PRESENTPIN 
         Caption         =   "Present Pin"
         Height          =   375
         Left            =   120
         TabIndex        =   21
         Top             =   1320
         Width           =   1935
      End
   End
   Begin VB.Frame Frame10 
      Caption         =   "Write (Bytes)"
      Height          =   1935
      Left            =   120
      TabIndex        =   16
      Top             =   6000
      Width           =   3735
      Begin VB.Frame Frame9 
         Caption         =   "PIN"
         Height          =   735
         Left            =   2400
         TabIndex        =   25
         Top             =   960
         Width           =   975
         Begin VB.TextBox PIN 
            Height          =   405
            Left            =   120
            TabIndex        =   26
            Text            =   "FFFF"
            Top             =   240
            Width           =   735
         End
      End
      Begin VB.Frame Frame11 
         Caption         =   "Adress (Hex)"
         Height          =   735
         Left            =   2400
         TabIndex        =   18
         Top             =   120
         Width           =   1215
         Begin VB.TextBox Adress 
            Alignment       =   1  'Rechts
            Height          =   405
            Left            =   120
            TabIndex        =   19
            Text            =   "00"
            Top             =   240
            Width           =   975
         End
      End
      Begin VB.TextBox WRITEDATA 
         Height          =   1455
         Left            =   120
         MultiLine       =   -1  'True
         TabIndex        =   17
         Top             =   240
         Width           =   2175
      End
   End
   Begin VB.Frame Frame8 
      Caption         =   "No. to Read (Hex)"
      Height          =   735
      Left            =   3960
      TabIndex        =   14
      Top             =   6360
      Width           =   2175
      Begin VB.TextBox BYTESTOREAD 
         Alignment       =   1  'Rechts
         Height          =   375
         Left            =   120
         TabIndex        =   15
         Text            =   "100"
         Top             =   240
         Width           =   1935
      End
   End
   Begin VB.Frame Frame7 
      Caption         =   "Message"
      Height          =   1095
      Left            =   120
      TabIndex        =   10
      Top             =   1320
      Width           =   3735
      Begin VB.TextBox MESSAGETEXT 
         Enabled         =   0   'False
         Height          =   735
         Left            =   120
         MultiLine       =   -1  'True
         TabIndex        =   11
         Top             =   240
         Width           =   3495
      End
   End
   Begin VB.Frame Frame6 
      Caption         =   "SCard2IC"
      Height          =   1215
      Left            =   3960
      TabIndex        =   7
      Top             =   5040
      Width           =   2175
      Begin VB.ComboBox I2CTYPE 
         Enabled         =   0   'False
         Height          =   315
         ItemData        =   "Form1.frx":1276
         Left            =   120
         List            =   "Form1.frx":1278
         Style           =   2  'Dropdown-Liste
         TabIndex        =   13
         Top             =   240
         Width           =   1935
      End
      Begin VB.CommandButton INITI2CBUTTON 
         Caption         =   "Init"
         Enabled         =   0   'False
         Height          =   375
         Left            =   120
         TabIndex        =   12
         Top             =   720
         Width           =   1935
      End
   End
   Begin VB.CommandButton ESTCONTEXTBUTTON 
      Caption         =   "Establish Context"
      Height          =   375
      Left            =   4080
      TabIndex        =   6
      Top             =   480
      Width           =   1935
   End
   Begin VB.CommandButton RELCONTEXTBUTTON 
      Caption         =   "Release Context"
      Height          =   375
      Left            =   4080
      TabIndex        =   5
      Top             =   1920
      Width           =   1935
   End
   Begin VB.Frame Frame3 
      Caption         =   "Common SCard Operations"
      Height          =   2295
      Left            =   3960
      TabIndex        =   4
      Top             =   120
      Width           =   2175
      Begin VB.CommandButton DISCONNECTBUTTON 
         Caption         =   "Disconnect"
         Height          =   375
         Left            =   120
         TabIndex        =   9
         Top             =   1320
         Width           =   1935
      End
      Begin VB.CommandButton CONNECTBUTTON 
         Caption         =   "Connect"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   840
         Width           =   1935
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Reply Data"
      Height          =   3375
      Left            =   120
      TabIndex        =   2
      Top             =   2520
      Width           =   3735
      Begin VB.TextBox REPLYDATA 
         BeginProperty Font 
            Name            =   "Courier New"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   3015
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertikal
         TabIndex        =   3
         Top             =   240
         Width           =   3495
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Readers"
      Height          =   1095
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3735
      Begin VB.ListBox ReaderList 
         Height          =   645
         ItemData        =   "Form1.frx":127A
         Left            =   120
         List            =   "Form1.frx":127C
         TabIndex        =   1
         Top             =   240
         Width           =   3495
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim hContext As Long
Dim hCard As Long
Dim isContext As Boolean
Dim isCard As Boolean

Private Function HexStrToInt(ByVal str As String) As Integer

Dim i As Integer
Dim iTmp As Integer
Dim sTmp As String

iStrLen = Len(str)

iTmp = 0
For i = 1 To Len(str)
    iTmp = iTmp * 16
    sTmp = Mid$(str, i, 1)
    If (sTmp >= "0" And sTmp <= "9") Then
        iTmp = iTmp + Switch(1 = 1, sTmp)
    Else
        iTmp = iTmp + Switch(sTmp = "A", 10, _
                         sTmp = "a", 10, _
                         sTmp = "B", 11, _
                         sTmp = "b", 11, _
                         sTmp = "C", 12, _
                         sTmp = "c", 12, _
                         sTmp = "D", 13, _
                         sTmp = "d", 13, _
                         sTmp = "E", 14, _
                         sTmp = "e", 14, _
                         sTmp = "F", 15, _
                         sTmp = "f", 15, _
                         1 = 1, 0 _
                         )
    End If
        
Next

HexStrToInt = iTmp

End Function

Private Function StrToArray(ByRef bArr() As Byte, ByVal str As String) As Integer

'Convert query string to byte array
Dim i As Integer
Dim iStrLen As Integer
Dim iTmp As Integer
Dim sTmp As String

iStrLen = Len(str)
If (iStrLen = 0) Then
    StrToArray = 0
    Exit Function
End If

If (iStrLen Mod 2) <> 0 Then
    rc = MsgBox("Invalid Value", vbOKOnly, "Error")
    StrToArray = 0
    Exit Function
End If

ReDim bArr(1 To iStrLen / 2) As Byte
iTmp = 0
For i = 1 To iStrLen
    sTmp = Mid$(str, i, 1)
    If (sTmp >= "0" And sTmp <= "9") Or (sTmp >= "a" And sTmp <= "f") Or (sTmp >= "A" And sTmp <= "F") Then
        iTmp = iTmp + Switch(sTmp = "A", 10, _
                             sTmp = "a", 10, _
                             sTmp = "B", 11, _
                             sTmp = "b", 11, _
                             sTmp = "C", 12, _
                             sTmp = "c", 12, _
                             sTmp = "D", 13, _
                             sTmp = "d", 13, _
                             sTmp = "E", 14, _
                             sTmp = "e", 14, _
                             sTmp = "F", 15, _
                             sTmp = "f", 15, _
                             1 = 1, sTmp _
                             )
    Else
        Form1.MESSAGETEXT.Text = "Invalid Value ! Please enter hexadecimal values"
        Exit Function
    End If
    
    If (i Mod 2) = 0 Then
        bArr((i / 2)) = iTmp
        iTmp = 0
    End If
    iTmp = iTmp * 16
Next

StrToArray = iStrLen / 2

End Function

Rem Private Sub CARDTYPE_Validate(Cancel As Boolean)
Rem Private Sub CARDTYPE_Change()
Private Sub CARDTYPE_Click()

Rem Disable all Buttons
Form1.READBUTTON.Enabled = False
Form1.WRITEBUTTON.Enabled = False
Form1.PRESENTPIN.Enabled = False
Form1.INITI2CBUTTON.Enabled = False
Form1.I2CTYPE.Enabled = False
    
Rem Enable 2W Buttons
If (CARDTYPE.Text = "2W") Then
    Form1.READBUTTON.Enabled = True
    Form1.WRITEBUTTON.Enabled = False
    Form1.PRESENTPIN.Enabled = True
End If

Rem Enable 3W Buttons
If (CARDTYPE.Text = "3W") Then
    Form1.READBUTTON.Enabled = True
    Form1.WRITEBUTTON.Enabled = False
    Form1.PRESENTPIN.Enabled = True
End If

Rem Enable I2C Buttons
If (CARDTYPE.Text = "I2C") Then
    Form1.INITI2CBUTTON.Enabled = True
    Form1.READBUTTON.Enabled = True
    Form1.WRITEBUTTON.Enabled = False
    Form1.I2CTYPE.Enabled = True
End If

End Sub




Private Sub Form_load()

' I2C cards from ST-Microelectronics:
I2CTYPE.AddItem ("ST14C02C")
I2CTYPE.AddItem ("ST14C04C")
I2CTYPE.AddItem ("ST14E32")
I2CTYPE.AddItem ("M14C04")
I2CTYPE.AddItem ("M14C16")
I2CTYPE.AddItem ("M14C32")
I2CTYPE.AddItem ("M14C64")
I2CTYPE.AddItem ("M14128")
I2CTYPE.AddItem ("M14256")
' I2C cards from GEMplus:
I2CTYPE.AddItem ("GFM2K")
I2CTYPE.AddItem ("GFM4K")
I2CTYPE.AddItem ("GFM32K")
' I2C cards from Atmel:
I2CTYPE.AddItem ("AT24C01A")
I2CTYPE.AddItem ("AT24C02")
I2CTYPE.AddItem ("AT24C04")
I2CTYPE.AddItem ("AT24C08")
I2CTYPE.AddItem ("AT24C16")
I2CTYPE.AddItem ("AT24C164")
I2CTYPE.AddItem ("AT24C32")
I2CTYPE.AddItem ("AT24C64")
I2CTYPE.AddItem ("AT24C128")
I2CTYPE.AddItem ("AT24C256")
I2CTYPE.AddItem ("AT24CS128")
I2CTYPE.AddItem ("AT24CS256")
I2CTYPE.AddItem ("AT24C512")
I2CTYPE.AddItem ("AT24C1024")

I2CTYPE.ListIndex = 0

CARDTYPE.AddItem ("2W")
CARDTYPE.AddItem ("3W")
CARDTYPE.AddItem ("I2C")

CARDTYPE.ListIndex = 0

End Sub

'
' Convert 1 Byte to String
'
Private Function GetString(ByVal curByte As Byte) As String

GetString = String(1, curByte)

End Function

'
' Gets an array of bytes and its length and return a viewable
' dump of this byte-array
' For Example: a bytearray with values
'   array(0) = &H3B
'   array(1) = &HA2
' becomes the String "3B A2"
'
Private Function HexDump(response() As Byte, ByVal lenr As Integer) As String

Dim rc As Integer
Dim OUT As String
Dim count As Integer
Dim value As Integer

For count = 0 To lenr - 1 Step 1
    value = response(count)

    ifvalue = Fix(value / 16)
    If ifvalue > -1 And ifvalue < 10 Then
        OUT = OUT + String(1, ifvalue + 48)
    Else
        If ifvalue > 9 And ifvalue < 16 Then
            OUT = OUT + String(1, ifvalue + 55)
        End If
    End If

    value = Fix(value Mod 16)

    If value > -1 And value < 10 Then
        OUT = OUT + String(1, value + 48)
    Else
        If value > 9 And value < 16 Then
            OUT = OUT + String(1, value + 55)
        End If
    End If

    OUT = OUT + " "
Next count

HexDump = OUT

End Function

'
' Handles errorcodes defined in Scard.bas and return an errormessage as String
'
Private Function HandleError(ByVal rc As Long) As String

HandleError = "Unknown Error"
If rc = OKERR_OK Then HandleError = "No Error"
If rc = OKERR_SCARD__E_CANCELLED Then HandleError = "The action was cancelled by an SCardCancel request"
If rc = OKERR_SCARD__E_INVALID_HANDLE Then HandleError = "The supplied handle was invalid"
If rc = OKERR_SCARD__E_INVALID_PARAMETER Then HandleError = "One or more of the supplied parameters could not be properly interpreted"
If rc = OKERR_SCARD__E_INVALID_TARGET Then HandleError = "Registry startup information is missing or invalid"
If rc = OKERR_SCARD__E_NO_MEMORY Then HandleError = "Not enough memory available to complete this command"
If rc = OKERR_SCARD__F_WAITED_TOO_LONG Then HandleError = "An internal consistency timer has expired"
If rc = OKERR_SCARD__E_INSUFFICIENT_BUFFER Then HandleError = "The data buffer to receive returned data is too small for the returned data"
If rc = OKERR_SCARD__E_UNKNOWN_READER Then HandleError = "The specified reader name is not recognized"
If rc = OKERR_SCARD__E_TIMEOUT Then HandleError = "The user-specified timeout value has expired"
If rc = OKERR_SCARD__E_SHARING_VIOLATION Then HandleError = "The smart card cannot be accessed because of other connections outstanding"
If rc = OKERR_SCARD__E_NO_SMARTCARD Then HandleError = "The operation requires a Smart Card, but no Smart Card is currently in the device"
If rc = OKERR_SCARD__E_UNKNOWN_CARD Then HandleError = "The specified smart card name is not recognized"
If rc = OKERR_SCARD__E_CANT_DISPOSE Then HandleError = "The system could not dispose of the media in the requested manner"
If rc = OKERR_SCARD__E_PROTO_MISMATCH Then HandleError = "The requested protocols are incompatible with the protocol currently in use with the smart card"
If rc = OKERR_SCARD__E_NOT_READY Then HandleError = "The reader or smart card is not ready to accept commands"
If rc = OKERR_SCARD__E_INVALID_VALUE Then HandleError = "One or more of the supplied parameters values could not be properly interpreted"
If rc = OKERR_SCARD__E_SYSTEM_CANCELLED Then HandleError = "The action was cancelled by the system, presumably to log off or shut down"
If rc = OKERR_SCARD__F_COMM_ERROR Then HandleError = "An internal communications error has been detected"
If rc = OKERR_SCARD__F_UNKNOWN_ERROR Then HandleError = "An internal error has been detected, but the source is unknown"
If rc = OKERR_SCARD__E_INVALID_ATR Then HandleError = "An ATR obtained from the registry is not a valid ATR string"
If rc = OKERR_SCARD__E_NOT_TRANSACTED Then HandleError = "An attempt was made to end a non-existent transaction"
If rc = OKERR_SCARD__E_READER_UNAVAILABLE Then HandleError = "The specified reader is not currently available for use"
If rc = OKERR_SCARD__P_SHUTDOWN Then HandleError = "The operation has been aborted to allow the server application to exit"
If rc = OKERR_SCARD__E_PCI_TOO_SMALL Then HandleError = "The PCI Receive buffer was too small"
If rc = OKERR_SCARD__E_READER_UNSUPPORTED Then HandleError = "The reader driver does not meet minimal requirements for support"
If rc = OKERR_SCARD__E_DUPLICATE_READER Then HandleError = "The reader driver did not produce a unique reader name"
If rc = OKERR_SCARD__E_CARD_UNSUPPORTED Then HandleError = "The smart card does not meet minimal requirements for support"
If rc = OKERR_SCARD__E_NO_SERVICE Then HandleError = "The Smart card resource manager is not running"
If rc = OKERR_SCARD__E_SERVICE_STOPPED Then HandleError = "The Smart card resource manager has shut down"
If rc = OKERR_SCARD__E_UNEXPECTED Then HandleError = "An unexpected card error has occurred"
If rc = OKERR_SCARD__E_ICC_INSTALLATION Then HandleError = "No Primary Provider can be found for the smart card"
If rc = OKERR_SCARD__E_ICC_CREATEORDER Then HandleError = "The requested order of object creation is not supported"
If rc = OKERR_SCARD__E_UNSUPPORTED_FEATURE Then HandleError = "This smart card does not support the requested feature"
If rc = OKERR_SCARD__E_DIR_NOT_FOUND Then HandleError = "The identified directory does not exist in the smart card"
If rc = OKERR_SCARD__E_FILE_NOT_FOUND Then HandleError = "The identified file does not exist in the smart card"
If rc = OKERR_SCARD__E_NO_DIR Then HandleError = "The supplied path does not represent a smart card directory"
If rc = OKERR_SCARD__E_NO_FILE Then HandleError = "The supplied path does not represent a smart card file"
If rc = OKERR_SCARD__E_NO_ACCESS Then HandleError = "Access is denied to this file"
If rc = OKERR_SCARD__E_WRITE_TOO_MANY Then HandleError = "An attempt was made to write more data than would fit in the target object"
If rc = OKERR_SCARD__E_BAD_SEEK Then HandleError = "There was an error trying to set the smart card file object pointer"
If rc = OKERR_SCARD__E_INVALID_CHV Then HandleError = "The supplied PIN is incorrect"
If rc = OKERR_SCARD__E_UNKNOWN_RES_MNG Then HandleError = "An unrecognized error code was returned from a layered component"
If rc = OKERR_SCARD__E_NO_SUCH_CERTIFICATE Then HandleError = "The requested certificate does not exist"
If rc = OKERR_SCARD__E_CERTIFICATE_UNAVAILABLE Then HandleError = "The requested certificate could not be obtained"
If rc = OKERR_SCARD__E_NO_READERS_AVAILABLE Then HandleError = "Cannot find a smart card reader"
If rc = OKERR_SCARD__E_COMM_DATA_LOST Then HandleError = "A communications error with the smart card has been detected"
If rc = OKERR_SCARD__W_UNSUPPORTED_CARD Then HandleError = "The reader cannot communicate with the smart card, due to ATR configuration conflicts"
If rc = OKERR_SCARD__W_UNRESPONSIVE_CARD Then HandleError = "The smart card is not responding to a reset"
If rc = OKERR_SCARD__W_UNPOWERED_CARD Then HandleError = "Power has been removed from the smart card, so that further communication is not possible"
If rc = OKERR_SCARD__W_RESET_CARD Then HandleError = "The smart card has been reset, so any shared state information is invalid"
If rc = OKERR_SCARD__W_REMOVED_CARD Then HandleError = "The smart card has been removed, so that further communication is not possible"
If rc = OKERR_SCARD__W_SECURITY_VIOLATION Then HandleError = "Access was denied because of a security violation"
If rc = OKERR_SCARD__W_WRONG_CHV Then HandleError = "The card cannot be accessed because the wrong PIN was presented"
If rc = OKERR_SCARD__W_CHV_BLOCKED Then HandleError = "The card cannot be accessed because the maximum number of PIN entry attempts has been reached"
If rc = OKERR_SCARD__W_EOF Then HandleError = "The end of the smart card file has been reached"
If rc = OKERR_SCARD__W_CANCELLED_BY_USER Then HandleError = "The action was cancelled by the user"

If rc = OKERR_PARM1 Then HandleError = "Error in parameter 1"
If rc = OKERR_PARM2 Then HandleError = "Error in parameter 2"
If rc = OKERR_PARM3 Then HandleError = "Error in parameter 3"
If rc = OKERR_PARM4 Then HandleError = "Error in parameter 4"
If rc = OKERR_PARM5 Then HandleError = "Error in parameter 5"
If rc = OKERR_PARM6 Then HandleError = "Error in parameter 6"
If rc = OKERR_PARM7 Then HandleError = "Error in parameter 7"
If rc = OKERR_PARM8 Then HandleError = "Error in parameter 8"
If rc = OKERR_PARM9 Then HandleError = "Error in parameter 9"
If rc = OKERR_PARM10 Then HandleError = "Error in parameter 10"
If rc = OKERR_PARM11 Then HandleError = "Error in parameter 11"
If rc = OKERR_PARM12 Then HandleError = "Error in parameter 12"
If rc = OKERR_PARM13 Then HandleError = "Error in parameter 13"
If rc = OKERR_PARM14 Then HandleError = "Error in parameter 14"
If rc = OKERR_PARM15 Then HandleError = "Error in parameter 15"
If rc = OKERR_PARM16 Then HandleError = "Error in parameter 16"
If rc = OKERR_PARM17 Then HandleError = "Error in parameter 17"
If rc = OKERR_PARM18 Then HandleError = "Error in parameter 18"
If rc = OKERR_PARM19 Then HandleError = "Error in parameter 19"
If rc = OKERR_INSUFFICIENT_PRIV Then HandleError = "You currently do not have the rights to execute the requested action. Usually a password has to be presented in advance."
If rc = OKERR_PW_WRONG Then HandleError = "The presented password is wrong"
If rc = OKERR_PW_LOCKED Then HandleError = "The password has been presented several times wrong and is therefore locked. Usually use some administrator tool to unblock it."
If rc = OKERR_PW_TOO_SHORT Then HandleError = "The lenght of the password was too short."
If rc = OKERR_PW_TOO_LONG Then HandleError = "The length of the password was too long."
If rc = OKERR_PW_NOT_LOCKED Then HandleError = "The password is not locked"
If rc = OKERR_ITEM_NOT_FOUND Then HandleError = "An item (e.g. a key of a specific name) could not be found"
If rc = OKERR_ITEMS_LEFT Then HandleError = "There are still items left, therefore e.g. the directory / structure etc. can't be deleted."
If rc = OKERR_INVALID_CFG_FILE Then HandleError = "Invalid configuration file"
If rc = OKERR_SECTION_NOT_FOUND Then HandleError = "Section not found"
If rc = OKERR_ENTRY_NOT_FOUND Then HandleError = "Entry not found"
If rc = OKERR_NO_MORE_SECTIONS Then HandleError = "No more sections"
If rc = OKERR_ITEM_ALREADY_EXISTS Then HandleError = "The specified item alread exists."
If rc = OKERR_ITEM_EXPIRED Then HandleError = "Some item (e.g. a certificate) has expired."
If rc = OKERR_UNEXPECTED_RET_VALUE Then HandleError = "Unexpected return value"
If rc = OKERR_COMMUNICATE Then HandleError = "General communication error"
If rc = OKERR_NOT_ENOUGH_MEMORY Then HandleError = "Not enough memory"
If rc = OKERR_BUFFER_OVERFLOW Then HandleError = "Buffer overflow"
If rc = OKERR_TIMEOUT Then HandleError = "A timeout has occurred"
If rc = OKERR_NOT_SUPPORTED Then HandleError = "The requested functionality is not supported at this time / under this OS / in this situation etc."
If rc = OKERR_ILLEGAL_ARGUMENT Then HandleError = "Illegal argument"
If rc = OKERR_READ_FIO Then HandleError = "File IO read error"
If rc = OKERR_WRITE_FIO Then HandleError = "File IO write error"
If rc = OKERR_INVALID_HANDLE Then HandleError = "Invalid handle"
If rc = OKERR_GENERAL_FAILURE Then HandleError = "General failure."
If rc = OKERR_FILE_NOT_FOUND Then HandleError = "File not found"
If rc = OKERR_OPEN_FILE Then HandleError = "File opening failed"
If rc = OKERR_SEM_USED Then HandleError = "The semaphore is currently use by an other process"
If rc = OKERR_NOP Then HandleError = "No operation done"
If rc = OKERR_NOK Then HandleError = "Function not executed"
If rc = OKERR_FWBUG Then HandleError = "Internal error detected"
If rc = OKERR_INIT Then HandleError = "Module not initialized"
If rc = OKERR_FIO Then HandleError = "File IO error detected"
If rc = OKERR_ALLOC Then HandleError = "Cannot allocate memory"
If rc = OKERR_SESSION_ERR Then HandleError = "General error"
If rc = OKERR_ACCESS_ERR Then HandleError = "Access not allowed"
If rc = OKERR_OPEN_FAILURE Then HandleError = "An open command was not successful"
If rc = OKERR_CARD_NOT_POWERED Then HandleError = "Card is not powered"
If rc = OKERR_ILLEGAL_CARDTYPE Then HandleError = "Illegal cardtype"
If rc = OKERR_CARD_NOT_INSERTED Then HandleError = "Card not inserted"
If rc = OKERR_NO_DRIVER Then HandleError = "No device driver installed"
If rc = OKERR_OUT_OF_SERVICE Then HandleError = "The service is currently not available"
If rc = OKERR_EOF_REACHED Then HandleError = "End of file reached"
If rc = OKERR_ON_BLACKLIST Then HandleError = "The ID is on a blacklist, the requested action is therefore not allowed."
If rc = OKERR_CONSISTENCY_CHECK Then HandleError = "Error during consistency check"
If rc = OKERR_IDENTITY_MISMATCH Then HandleError = "The identity does not match a defined cross-check identity"
If rc = OKERR_MULTIPLE_ERRORS Then HandleError = "Multiple errors have occurred. Use this if there is only the possibility to return one error code, but there happened different errors before (e.g. each thread returned a different error and the controlling thread may only report one)."
If rc = OKERR_ILLEGAL_DRIVER Then HandleError = "Illegal driver"
If rc = OKERR_ILLEGAL_FW_RELEASE Then HandleError = "The connected hardware whose firmware is not useable by this software"
If rc = OKERR_NO_CARDREADER Then HandleError = "No cardreader attached"
If rc = OKERR_IPC_FAULT Then HandleError = "General failure of inter process communication"
If rc = OKERR_WAIT_AND_RETRY Then HandleError = "The service currently does not take calls. The task has to go back to the message loop and try again at a later time (Windows 3.1 only). The code may also be used, in every situation where a ‘  wait and retry ’  action is requested."

End Function

'
' Connect to Card
'
Private Sub CONNECTBUTTON_Click()

Dim rc As Long
Dim i As Integer
Dim curReader As String

Dim myByte As Byte
Dim dwShareMode As Long
Dim dwPreferredProtocols As Long
Dim dwActiveProtocol As Long


' get selected Readername from ReaderList
If ReaderList.Text = "" Then
    MESSAGETEXT.Text = ("No Reader Selected")
    Exit Sub
Else
    curReader = ReaderList.Text
End If

' Set Mode (see Scard.bas "Modes")
dwShareMode = SCARD_SHARE_SHARED
' Set preferred Protocol (see Scard.bas "Protocols")
dwPreferredProtocols = SCARD_PROTOCOL_T0

' Connect
rc = SCardConnect(hContext, curReader, dwShareMode, dwPreferredProtocols, hCard, dwActiveProtocol)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = HandleError(rc)
    Exit Sub
End If

MESSAGETEXT.Text = "Connect successfull"
isCard = True

End Sub

'
' Disconnects from Card
'
Private Sub DISCONNECTBUTTON_Click()
Dim rc As Long
Dim dwDisposition As Long

' check if a card is connected
If isCard = False Then
    MESSAGETEXT.Text = "Not connected"
    Exit Sub
End If

' Set Disposition (see Scard.bas "Dispositions")
dwDisposition = SCARD_LEAVE_CARD

'Disconnect from Card
rc = SCardDisconnect(hCard, dwDisposition)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
End If

MESSAGETEXT.Text = "Disconnect successfull"
isCard = False

End Sub

'
' Establish Context and List Readers
'
Private Sub ESTCONTEXTBUTTON_Click()

Dim rc As Long
Dim dwScope As Long

Dim mszReaders(2048) As Byte
Dim mszGroup(1024) As Byte
Dim pcchReaders As Long

Dim curReader As String

' if a Context is established, release it first
If isContext = True Then RELCONTEXTBUTTON_Click

' Set Scope (see Scard.bas "Scopes")
dwScope = SCARD_SCOPE_USER

' Establish Context
rc = SCardEstablishContext(dwScope, 0, 0, hContext)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
End If

' Set maximum Length of mszReaders
pcchReaders = 2048

' Create a Multistring (terminated with two '\0's)
mszGroup(0) = &H0
mszGroup(1) = &H0

rc = SCardListReaders(hContext, mszGroup(LBound(mszGroup)), mszReaders(LBound(mszReaders)), pcchReaders)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
End If

ReaderList.Clear

Dim i As Integer

' Split multistring and add single Readers to list
For i = 0 To pcchReaders - 2 Step 1
    If mszReaders(i) = &H0 And i <> 0 Then
        ReaderList.AddItem (curReader)
        ReaderList.ListIndex = 0
        curReader = ""
        i = i + 1
    End If

    curReader = curReader + GetString(mszReaders(i))
Next i

MESSAGETEXT.Text = "Establish successfull, ListReaders successfull"
isContext = True

End Sub

'
' InitI2C
'
Private Sub INITI2CBUTTON_Click()

Dim rc As Long
Dim CardParameters As SCARD_I2C_CARD_PARAMETERS
Dim pCardParameters As Long
Dim lType As Long

' Type (see SCardI2C.bas "Predefined Cardtypes")
lType = NO_PREDEFINED_PARAMETERS
If I2CTYPE.Text = "ST14C02C" Then lType = ST14C02C
If I2CTYPE.Text = "ST14C04C" Then lType = ST14C04C
If I2CTYPE.Text = "ST14E32" Then lType = ST14E32
If I2CTYPE.Text = "M14C04" Then lType = M14C04
If I2CTYPE.Text = "M14C16" Then lType = M14C16
If I2CTYPE.Text = "M14C32" Then lType = M14C32
If I2CTYPE.Text = "M14C64" Then lType = M14C64
If I2CTYPE.Text = "M14128" Then lType = M14128
If I2CTYPE.Text = "M14256" Then lType = M14256
If I2CTYPE.Text = "GFM2K" Then lType = GFM2K
If I2CTYPE.Text = "GFM4K" Then lType = GFM4K
If I2CTYPE.Text = "GFM32K" Then lType = GFM32K
If I2CTYPE.Text = "AT24C01A" Then lType = AT24C01A
If I2CTYPE.Text = "AT24C02" Then lType = AT24C02
If I2CTYPE.Text = "AT24C04" Then lType = AT24C04
If I2CTYPE.Text = "AT24C08" Then lType = AT24C08
If I2CTYPE.Text = "AT24C16" Then lType = AT24C16
If I2CTYPE.Text = "AT24C164" Then lType = AT24C164
If I2CTYPE.Text = "AT24C32" Then lType = AT24C32
If I2CTYPE.Text = "AT24C64" Then lType = AT24C64
If I2CTYPE.Text = "AT24C128" Then lType = AT24C128
If I2CTYPE.Text = "AT24C256" Then lType = AT24C256
If I2CTYPE.Text = "AT24CS128" Then lType = AT24CS128
If I2CTYPE.Text = "AT24CS256" Then lType = AT24CS256
If I2CTYPE.Text = "AT24C512" Then lType = AT24C512
If I2CTYPE.Text = "AT24C1024" Then lType = AT24C1024

' get pointer do CardParameters
pCardParameters = VarPtr(CardParameters)

' Init
rc = SCardI2CInit(hCard, pCardParameters, lType)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = HandleError(rc)
    Exit Sub
End If

Form1.WRITEBUTTON.Enabled = True

MESSAGETEXT.Text = "InitI2C successfull"

End Sub

Private Sub PRESENTPIN_Click()
Dim rc As Long
Dim ulPINLen As Long
Dim bPin() As Byte

ulPINLen = StrToArray(bPin, Form1.PIN.Text)
If ulPINLen = 0 Then
    Exit Sub
End If

If (Form1.CARDTYPE.Text = "2W") Then
    rc = SCard2WBPPresentPIN(hCard, ulPINLen, bPin(LBound(bPin)))
End If
If (Form1.CARDTYPE.Text = "3W") Then
    rc = SCard3WBPPresentPIN(hCard, ulPINLen, bPin(LBound(bPin)))
End If

If rc <> OKERR_OK Then
    MESSAGETEXT.Text = HandleError(rc)
    Exit Sub
End If

Form1.WRITEBUTTON.Enabled = True

MESSAGETEXT.Text = "PresentPin successfull"

End Sub

Private Sub PresentPin2W_Click()

Dim rc As Long
Dim ulPINLen As Long
Dim bPin() As Byte

ulPINLen = StrToArray(bPin, Form1.PIN.Text)
If ulPINLen = 0 Then
    Exit Sub
End If

rc = SCard2WBPPresentPIN(hCard, ulPINLen, bPin(LBound(bPin)))
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = HandleError(rc)
    Exit Sub
End If

MESSAGETEXT.Text = "2W - PresentPin successfull"

End Sub

Private Sub PRESENTPIN3W_Click()

Dim rc As Long
Dim ulPINLen As Long
Dim bPin() As Byte

ulPINLen = StrToArray(bPin, Form1.PIN.Text)
If ulPINLen = 0 Then
    Exit Sub
End If

rc = SCard3WBPPresentPIN(hCard, ulPINLen, bPin(LBound(bPin)))
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = HandleError(rc)
    Exit Sub
End If

MESSAGETEXT.Text = "3W - PresentPin successfull"

End Sub

Private Sub READBUTTON_Click()
Dim rc As Long
Dim bData() As Byte
Dim ulBytesToRead As Long

ulBytesToRead = HexStrToInt(BYTESTOREAD.Text)
ReDim bData(ulBytesToRead)


If (Form1.CARDTYPE = "2W") Then
    ' Read
    rc = SCard2WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
    If rc <> OKERR_OK Then
        MESSAGETEXT.Text = HandleError(rc)
        Exit Sub
    End If
End If

If (Form1.CARDTYPE.Text = "3W") Then
    ' Read
    rc = SCard3WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
    If rc <> OKERR_OK Then
        MESSAGETEXT.Text = (HandleError(rc))
        Exit Sub
    End If
End If

If (Form1.CARDTYPE.Text = "I2C") Then
    ' Read
    rc = SCardI2CReadData(hCard, bData(LBound(bData)), ulBytesToRead, 0, ulBytesToRead)
    If rc <> OKERR_OK Then
        MESSAGETEXT.Text = (HandleError(rc))
        Exit Sub
    End If
End If

Dim OUT As String

' Create a Hexdump from returned data
OUT = OUT + HexDump(bData, ulBytesToRead)

MESSAGETEXT.Text = "Read successfull"

' Show Data
REPLYDATA.Text = OUT

End Sub

'
' Read 100 Bytes from 2WCard
'
Private Sub READBUTTON2W_Click()

Dim rc As Long
Dim bData() As Byte
Dim ulBytesToRead As Long

ulBytesToRead = HexStrToInt(BYTESTOREAD.Text)
ReDim bData(ulBytesToRead)

' Read
rc = SCard2WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = HandleError(rc)
    Exit Sub
End If

Dim OUT As String

' Create a HexDump from returned Data
OUT = OUT + HexDump(bData, ulBytesToRead)

MESSAGETEXT.Text = "Read2W successfull"

' Show Data
REPLYDATA.Text = OUT

End Sub

'
' Read 100 Bytes from 3WCard
'
Private Sub READBUTTON3W_Click()

Dim rc As Long
Dim bData() As Byte
Dim ulBytesToRead As Long

ulBytesToRead = HexStrToInt(BYTESTOREAD.Text)
ReDim bData(ulBytesToRead)


If (Form1.CARDTYPE = "2W") Then
    ' Read
    rc = SCard2WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
    If rc <> OKERR_OK Then
        MESSAGETEXT.Text = HandleError(rc)
        Exit Sub
    End If
End If

If (Form1.CARDTYPE.Text = "3W") Then
    ' Read
    rc = SCard3WBPReadData(hCard, ulBytesToRead, bData(LBound(bData)), 0)
    If rc <> OKERR_OK Then
        MESSAGETEXT.Text = (HandleError(rc))
        Exit Sub
    End If
End If

If (Form1.CARDTYPE.Text = "I2C") Then
    ' Read
    rc = SCardI2CReadData(hCard, bData(LBound(bData)), ulReadBufferSize, 0, ulBytesToRead)
    If rc <> OKERR_OK Then
        MESSAGETEXT.Text = (HandleError(rc))
        Exit Sub
    End If
End If

Dim OUT As String

' Create a Hexdump from returned data
OUT = OUT + HexDump(bData, ulBytesToRead)

MESSAGETEXT.Text = "Read successfull"

' Show Data
REPLYDATA.Text = OUT

End Sub

'
' Read 100 Bytes from I2CCard
'
Private Sub READBUTTONI2C_Click()

Dim rc As Long
Dim bData() As Byte
Dim ulReadBufferSize As Long
Dim ulBytesToRead As Long

ulBytesToRead = BYTESTOREAD.Text
ulReadBufferSize = ulBytesToRead
ReDim bData(ulReadBufferSize)

' Read
rc = SCardI2CReadData(hCard, bData(LBound(bData)), ulReadBufferSize, 0, ulBytesToRead)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
End If

Dim OUT As String

'Create Hexdump from returned data
OUT = OUT + HexDump(bData, ulBytesToRead)

MESSAGETEXT.Text = "ReadI2C successfull"
' Show data
REPLYDATA.Text = OUT

End Sub

'
' Release context
'
Private Sub RELCONTEXTBUTTON_Click()

' if a Card is connected, disconnect first
If isCard = True Then DISCONNECTBUTTON_Click

' check if a context is established
If isContext = False Then
    MESSAGETEXT.Text = "No context established"
    Exit Sub
End If

' release
rc = SCardReleaseContext(hContext)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
End If

' remove readers from readerlist
ReaderList.Clear
MESSAGETEXT.Text = "Release successfull"

isContext = False

End Sub

Private Sub Form_unload(Cancel As Integer)

' release context before closing application
If isContext = True Then RELCONTEXTBUTTON_Click

End Sub

Private Sub WRITEBUTTON_Click()

Dim rc As Long
Dim bData() As Byte
Dim bDataLen As Integer
Dim iAdress As Integer

iAdress = HexStrToInt(Form1.Adress.Text)
bDataLen = StrToArray(bData, Form1.WRITEDATA.Text)

If bDataLen = 0 Then
    Exit Sub
End If

If (Form1.CARDTYPE.Text = "2W") Then
    rc = SCard2WBPWriteData(hCard, _
                            bDataLen, _
                            bData(LBound(bData)), _
                            iAdress)
End If

If (Form1.CARDTYPE.Text = "3W") Then
    rc = SCard3WBPWriteData(hCard, _
                            bDataLen, _
                            bData(LBound(bData)), _
                            iAdress, _
                            0)
End If

If (Form1.CARDTYPE.Text = "I2C") Then
    rc = SCardI2CWriteData(hCard, _
                           bData(LBound(bData)), _
                           bDataLen, _
                           iAdress, _
                           bDataLen)
End If

If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
End If

MESSAGETEXT.Text = "WriteData successfull"

End Sub

Private Sub WRITEBUTTON2W_Click()

Dim rc As Long
Dim bData() As Byte
Dim bDataLen As Integer
Dim iAdress As Integer

iAdress = HexStrToInt(Form1.Adress.Text)

bDataLen = StrToArray(bData, Form1.WRITEDATA.Text)

If bDataLen = 0 Then
    Exit Sub
End If

rc = SCard2WBPWriteData(hCard, _
                        bDataLen, _
                        bData(LBound(bData)), _
                        iAdress)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
End If

MESSAGETEXT.Text = "2W WriteData successfull"

End Sub

Private Sub WRITEBUTTON3W_Click()

Dim rc As Long
Dim bData() As Byte
Dim bDataLen As Integer
Dim iAdress As Integer

iAdress = HexStrToInt(Form1.Adress.Text)

bDataLen = StrToArray(bData, Form1.WRITEDATA.Text)

If bDataLen = 0 Then
    Exit Sub
End If

rc = SCard3WBPWriteData(hCard, _
                        bDataLen, _
                        bData(LBound(bData)), _
                        iAdress, _
                        0)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
End If

MESSAGETEXT.Text = "3W WriteData successfull"

End Sub

Private Sub WRITEBUTTONI2C_Click()

Dim rc As Long
Dim bData() As Byte
Dim ulWriteBufferSize As Long
Dim ulBytesToWrite As Long
Dim intIx As Integer
Dim iAdress As Integer

'ulWriteBufferSize = BYTESTOREAD.Text
'ulBytesToWrite = ulWriteBufferSize
'ReDim bData(ulBytesToWrite)

ulBytesToWrite = StrToArray(bData, Form1.WRITEDATA.Text)
ulWriteBufferSize = ulBytesToWrite

iAdress = HexStrToInt(Form1.Adress.Text)

'For intIx = LBound(bData) To UBound(bData)
'    bData(intIx) = intIx Mod 256
'Next intIx
' Write
rc = SCardI2CWriteData(hCard, bData(LBound(bData)), ulWriteBufferSize, iAdress, ulBytesToWrite)
If rc <> OKERR_OK Then
    MESSAGETEXT.Text = (HandleError(rc))
    Exit Sub
Else
    MsgBox "Write OK,click ok to reread data.."
    Call READBUTTONI2C_Click
End If

End Sub
