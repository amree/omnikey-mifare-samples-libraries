VERSION 5.00
Begin VB.Form ContactLessDemoVB 
   Caption         =   "ContactLessDemoVB"
   ClientHeight    =   11115
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   13425
   LinkTopic       =   "Form1"
   ScaleHeight     =   11115
   ScaleWidth      =   13425
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox iCLASSReceivedText 
      Height          =   495
      Left            =   6960
      MultiLine       =   -1  'True
      TabIndex        =   49
      Top             =   7080
      Width           =   6375
   End
   Begin VB.TextBox iCLASSSendText 
      Height          =   375
      Left            =   2160
      TabIndex        =   48
      Top             =   7080
      Width           =   4095
   End
   Begin VB.CommandButton iCLASSTransmit 
      Caption         =   "iCLASS Transmit"
      Height          =   495
      Left            =   120
      TabIndex        =   47
      Top             =   7080
      Width           =   1695
   End
   Begin VB.TextBox StatusText 
      Alignment       =   2  'Center
      Height          =   375
      Left            =   6000
      TabIndex        =   45
      Top             =   8280
      Width           =   2535
   End
   Begin VB.CommandButton DisConnectCard 
      Caption         =   "Disconnect Card "
      Height          =   495
      Left            =   120
      TabIndex        =   44
      Top             =   8280
      Width           =   2055
   End
   Begin VB.CommandButton RefreshOutput 
      Caption         =   "Refresh Output Screen"
      Height          =   495
      Left            =   11280
      TabIndex        =   43
      Top             =   8280
      Width           =   2055
   End
   Begin VB.TextBox DecermentValText 
      Height          =   375
      Left            =   10200
      MaxLength       =   8
      TabIndex        =   35
      Top             =   6000
      Width           =   2775
   End
   Begin VB.TextBox IncrementValText 
      Height          =   375
      Left            =   2640
      MaxLength       =   8
      TabIndex        =   34
      Top             =   6120
      Width           =   2535
   End
   Begin VB.CommandButton Decrement 
      Caption         =   "Decrement"
      Height          =   495
      Left            =   7920
      TabIndex        =   33
      Top             =   5880
      Width           =   1455
   End
   Begin VB.CommandButton Increment 
      Caption         =   "Increment"
      Height          =   495
      Left            =   120
      TabIndex        =   32
      Top             =   6000
      Width           =   1455
   End
   Begin VB.Frame AuthenticationMode 
      Caption         =   "Authentication Mode"
      Height          =   1335
      Left            =   8880
      TabIndex        =   29
      Top             =   3360
      Width           =   4335
      Begin VB.OptionButton ModeOptionB 
         Caption         =   "Mode B"
         Height          =   375
         Left            =   2040
         TabIndex        =   31
         Top             =   480
         Width           =   1935
      End
      Begin VB.OptionButton ModeOptionA 
         Caption         =   "Mode A"
         Height          =   375
         Left            =   360
         TabIndex        =   30
         Top             =   480
         Width           =   1575
      End
   End
   Begin VB.Frame AccessOption 
      Caption         =   "Access Option"
      Height          =   1335
      Left            =   3120
      TabIndex        =   24
      Top             =   3480
      Width           =   5655
      Begin VB.OptionButton OptionKey 
         Caption         =   "Key will be supplied"
         Height          =   255
         Left            =   3000
         TabIndex        =   41
         Top             =   240
         Width           =   2535
      End
      Begin VB.OptionButton OptionKeyNr 
         Caption         =   "Key Nr will be supplied"
         Height          =   255
         Left            =   240
         TabIndex        =   40
         Top             =   240
         Width           =   2415
      End
      Begin VB.TextBox MifAuthentKeyText 
         Height          =   285
         Left            =   3480
         MaxLength       =   12
         TabIndex        =   27
         Top             =   600
         Width           =   2055
      End
      Begin VB.TextBox AuthenKeyNrText 
         Height          =   285
         Left            =   720
         TabIndex        =   25
         Top             =   600
         Width           =   855
      End
      Begin VB.Label Label11 
         Caption         =   "Key ( 6 byte hex)"
         Height          =   255
         Left            =   3600
         TabIndex        =   28
         Top             =   960
         Width           =   1215
      End
      Begin VB.Label Label10 
         Caption         =   "Key Nr (0-1F)"
         Height          =   255
         Left            =   720
         TabIndex        =   26
         Top             =   960
         Width           =   1095
      End
   End
   Begin VB.CommandButton Authenticate 
      Caption         =   "Authenticate"
      Height          =   495
      Left            =   120
      TabIndex        =   23
      Top             =   3720
      Width           =   1455
   End
   Begin VB.TextBox DataWriteText 
      Height          =   375
      Left            =   8280
      MaxLength       =   32
      TabIndex        =   21
      Top             =   5040
      Width           =   4935
   End
   Begin VB.CommandButton Write 
      Caption         =   "Write"
      Height          =   495
      Left            =   6840
      TabIndex        =   20
      Top             =   5040
      Width           =   1215
   End
   Begin VB.TextBox DataReadText 
      Height          =   375
      Left            =   2040
      TabIndex        =   17
      Top             =   5040
      Width           =   4095
   End
   Begin VB.TextBox BlockNrText 
      Alignment       =   2  'Center
      Height          =   375
      Left            =   1920
      TabIndex        =   16
      Text            =   "00"
      Top             =   3720
      Width           =   735
   End
   Begin VB.CommandButton Read 
      Caption         =   "Read"
      Height          =   495
      Left            =   120
      TabIndex        =   15
      Top             =   5040
      Width           =   1335
   End
   Begin VB.TextBox MifKeyToReaderNrText 
      Height          =   285
      Left            =   7320
      MaxLength       =   2
      TabIndex        =   14
      Text            =   "00"
      Top             =   960
      Width           =   735
   End
   Begin VB.TextBox MifareKeyToReaderText 
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   8280
      MaxLength       =   12
      TabIndex        =   12
      Top             =   960
      Width           =   2055
   End
   Begin VB.TextBox CardNameText 
      Height          =   495
      Left            =   10200
      TabIndex        =   7
      Top             =   2040
      Width           =   3015
   End
   Begin VB.TextBox UIDText 
      Height          =   495
      Left            =   6360
      TabIndex        =   6
      Top             =   2040
      Width           =   3495
   End
   Begin VB.TextBox ATRText 
      Height          =   495
      Left            =   480
      TabIndex        =   5
      Top             =   2040
      Width           =   5415
   End
   Begin VB.CommandButton WriteMifKeyToReader 
      Caption         =   "Write Mifare Key To reader"
      Height          =   615
      Left            =   5280
      TabIndex        =   4
      Top             =   840
      Width           =   1815
   End
   Begin VB.PictureBox OmnikeyLogo 
      Height          =   1455
      Left            =   10440
      Picture         =   "ContactLessDemoVB.frx":0000
      ScaleHeight     =   1395
      ScaleWidth      =   2715
      TabIndex        =   3
      Top             =   120
      Width           =   2775
   End
   Begin VB.CommandButton ConnectCard 
      Caption         =   "Connect Card "
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   2640
      Width           =   1455
   End
   Begin VB.ListBox OutPutList 
      Height          =   2790
      Left            =   120
      MultiSelect     =   1  'Simple
      TabIndex        =   1
      Top             =   8880
      Width           =   13335
   End
   Begin VB.ListBox ReaderList 
      Height          =   1620
      Left            =   120
      MultiSelect     =   1  'Simple
      TabIndex        =   0
      Top             =   120
      Width           =   5055
   End
   Begin VB.Label Label21 
      Caption         =   "iCLASS Functionalities"
      Height          =   255
      Left            =   6000
      TabIndex        =   54
      Top             =   6720
      Width           =   1695
   End
   Begin VB.Label Label20 
      Caption         =   "Mifare Functionalities"
      Height          =   255
      Left            =   0
      TabIndex        =   53
      Top             =   0
      Width           =   1575
   End
   Begin VB.Label Label19 
      Caption         =   "Mifare Functionalities"
      Height          =   255
      Left            =   6360
      TabIndex        =   52
      Top             =   3120
      Width           =   1575
   End
   Begin VB.Label Label18 
      Alignment       =   2  'Center
      Caption         =   "Bytes (hex) received"
      Height          =   255
      Left            =   7560
      TabIndex        =   51
      Top             =   7680
      Width           =   4815
   End
   Begin VB.Label Label17 
      Alignment       =   2  'Center
      Caption         =   "Bytes to send(hex)"
      Height          =   255
      Left            =   2520
      TabIndex        =   50
      Top             =   7680
      Width           =   3495
   End
   Begin VB.Line Line3 
      X1              =   0
      X2              =   13440
      Y1              =   8040
      Y2              =   8040
   End
   Begin VB.Label Label16 
      Alignment       =   2  'Center
      Caption         =   "Status"
      Height          =   255
      Left            =   4920
      TabIndex        =   46
      Top             =   8400
      Width           =   855
   End
   Begin VB.Shape Shape1 
      Height          =   615
      Left            =   4800
      Top             =   8160
      Width           =   4095
   End
   Begin VB.Line Line2 
      X1              =   0
      X2              =   13320
      Y1              =   3240
      Y2              =   3240
   End
   Begin VB.Line Line1 
      X1              =   0
      X2              =   13320
      Y1              =   6840
      Y2              =   6840
   End
   Begin VB.Label Label15 
      Alignment       =   2  'Center
      Caption         =   $"ContactLessDemoVB.frx":2022
      Height          =   615
      Left            =   5280
      TabIndex        =   42
      Top             =   120
      Width           =   5055
   End
   Begin VB.Label Label14 
      Alignment       =   2  'Center
      Caption         =   "4-byte hex data"
      Height          =   375
      Left            =   10320
      TabIndex        =   39
      Top             =   6600
      Width           =   2655
   End
   Begin VB.Label Label8 
      Alignment       =   2  'Center
      Caption         =   "4-byte hex data"
      Height          =   255
      Left            =   2760
      TabIndex        =   38
      Top             =   6600
      Width           =   2295
   End
   Begin VB.Label Label13 
      Caption         =   "by"
      Height          =   375
      Left            =   9600
      TabIndex        =   37
      Top             =   6000
      Width           =   375
   End
   Begin VB.Label Label12 
      Caption         =   "by"
      Height          =   375
      Left            =   1920
      TabIndex        =   36
      Top             =   6120
      Width           =   375
   End
   Begin VB.Label Label9 
      Alignment       =   2  'Center
      Caption         =   "Data to be Writen"
      Height          =   255
      Left            =   8400
      TabIndex        =   22
      Top             =   5520
      Width           =   4815
   End
   Begin VB.Label Label7 
      Alignment       =   2  'Center
      Caption         =   "Data read"
      Height          =   255
      Left            =   2160
      TabIndex        =   19
      Top             =   5520
      Width           =   4095
   End
   Begin VB.Label Label6 
      Caption         =   "Block Nr"
      Height          =   255
      Left            =   1920
      TabIndex        =   18
      Top             =   4200
      Width           =   735
   End
   Begin VB.Label Label5 
      Caption         =   "6-Byte Mifare Key (hex)"
      Height          =   255
      Left            =   8400
      TabIndex        =   13
      Top             =   1440
      Width           =   1815
   End
   Begin VB.Label Label4 
      Caption         =   "Key Nr     ( 0 - 1F)"
      Height          =   375
      Left            =   7440
      TabIndex        =   11
      Top             =   1320
      Width           =   735
   End
   Begin VB.Label Label3 
      Caption         =   "Card Name"
      Height          =   255
      Left            =   11400
      TabIndex        =   10
      Top             =   2640
      Width           =   975
   End
   Begin VB.Label Label2 
      Caption         =   "UID"
      Height          =   375
      Left            =   8160
      TabIndex        =   9
      Top             =   2640
      Width           =   495
   End
   Begin VB.Label Label1 
      Caption         =   "ATR"
      Height          =   255
      Left            =   3000
      TabIndex        =   8
      Top             =   2640
      Width           =   735
   End
End
Attribute VB_Name = "ContactLessDemoVB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim hContext As Long
Dim hCard As Long
Dim isContext As Boolean
Dim SelectedReader As String
Dim rc As Long
Dim ATR(64) As Byte
Dim ATRLen As Long
Dim MifKeyNrToReaderStr As String
Dim MifKeyToReader As String
Dim fCardConnected As Boolean
Dim fLookForCard As Boolean

Private Sub Authenticate_Click()
Dim BlockNr As Long
Dim MifareKey(6) As Byte
Dim KeyLen As Long
Dim AccessOption As Byte
Dim Mode As Byte
Dim MifKeyNr As Byte

MifKeyNr = 0

If fCardConnected = False Then
OutPutList.AddItem " At first Card has to be connected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If

BlockNr = HexStrToInt(BlockNrText.Text)
NumofDataLen = 16

If OptionKeyNr.value = True Then
AccessOption = 1
MifKeyNr = HexStrToInt(AuthenKeyNrText.Text)
End If
If OptionKey.value = True Then
AccessOption = 0
KeyLen = StrToArray(MifareKey, 6, MifAuthentKeyText.Text)
End If

If OptionKey.value = False Then
If OptionKeyNr.value = False Then
OutPutList.AddItem " One Access Option must be selected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If
End If

If ModeOptionA.value = True Then
Mode = 96
End If
If ModeOptionB.value = True Then
Mode = 97
End If

If ModeOptionA.value = False Then
If ModeOptionB.value = False Then
OutPutList.AddItem " One Authenticate Mode must be selected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If
End If

rc = SCardCLMifareStdAuthent(hCard, BlockNr, Mode, AccessOption, MifKeyNr, MifareKey(LBound(MifareKey)), KeyLen)

If rc = 0 Then
OutPutList.AddItem " Authentication has been written successfully"
StatusText.Text = " SUCCESS"

End If
If rc <> 0 Then
OutPutList.AddItem " Error in Authentication "
OutPutList.AddItem HandleError(rc)
StatusText.Text = " ERROR"
End If

EXITSUB:
OutPutList.ListIndex = OutPutList.ListCount - 1

End Sub

Private Sub ConnectCard_Click()
Dim i As Integer
Dim curReader As String

Dim myByte As Byte
Dim dwShareMode As Long
Dim dwPreferredProtocols As Long
Dim dwActiveProtocol As Long
Dim UID(12) As Byte
Dim UIDLen As Long

ATRText = ""
UIDText = ""
CardNameText = ""

' get selected Readername from ReaderList
If ReaderList.Text = "" Then
    OutPutList.AddItem "No Reader Selected"
    Exit Sub
Else
    curReader = ReaderList.Text
End If

' Set Mode (see Scard.bas "Modes")
dwShareMode = SCARD_SHARE_SHARED
' Set preferred Protocol (see Scard.bas "Protocols")
dwPreferredProtocols = SCARD_PROTOCOL_T1

' Connect
rc = SCardConnect(hContext, curReader, dwShareMode, dwPreferredProtocols, hCard, dwActiveProtocol)
If rc = 0 Then
OutPutList.AddItem " Card has been connected Succesfully"
StatusText.Text = " SUCCESS"
fCardConnected = True
ATRLen = 64
rc = SCardGetAttrib(hCard, SCARD_ATTR_ATR_STRING, ATR(LBound(ATR)), ATRLen)
If rc = 0 Then
ATRText = ATRText + HexDump(ATR, ATRLen)
UIDLen = 12
rc = SCardCLGetUID(hCard, UID(LBound(UID)), 12, UIDLen)
If rc = 0 Then
UIDText = UIDText + HexDump(UID, UIDLen)
CardNameText = GetCardName()
End If
If rc <> 0 Then
OutPutList.AddItem " Error in SCardCLGetUID"
OutPutList.AddItem HandleError(rc)
StatusText.Text = " ERROR"

End If
End If
If rc <> 0 Then
OutPutList.AddItem "Error in SCardGetAttrib"
OutPutList.AddItem HandleError(rc)
StatusText.Text = " ERROR"

End If
End If
If rc <> 0 Then
OutPutList.AddItem "Error in SCardConnect"
OutPutList.AddItem HandleError(rc)
fCardConnected = False
StatusText.Text = " ERROR"

End If
OutPutList.ListIndex = OutPutList.ListCount - 1
End Sub

Private Sub Decrement_Click()
Dim ucData(4) As Byte
Dim DataLen As Long
Dim BlockNr As Long

If fCardConnected = False Then
OutPutList.AddItem "Card is not Connected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If


BlockNr = HexStrToInt(BlockNrText.Text)
DataLen = StrToArray(ucData, 4, DecermentValText.Text)
rc = SCardCLMifareStdDecrementVal(hCard, BlockNr, ucData(LBound(ucData)), DataLen)
If rc = 0 Then
OutPutList.AddItem "Value has been decremented  successfully"
StatusText.Text = " SUCCESS"
End If

If rc <> 0 Then
OutPutList.AddItem "Error in  SCardCLMifareStdDecrementVal"
OutPutList.AddItem HandleError(rc)
StatusText.Text = " ERROR"
End If

EXITSUB:
OutPutList.ListIndex = OutPutList.ListCount - 1
End Sub

Private Sub DisConnectCard_Click()

If fCardConnected = False Then
OutPutList.AddItem "Card is not Connected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If

 rc = SCardDisconnect(hCard, SCARD_RESET_CARD)
If rc = 0 Then
OutPutList.AddItem "Card has bee disconnected successfully"
fCardConnected = False
ATRText = ""
UIDText = ""
CardNameText = ""
StatusText.Text = " SUCCESS"
End If

If rc <> 0 Then
OutPutList.AddItem "Error in  SCardDisconnect"
OutPutList.AddItem HandleError(rc)
StatusText.Text = " ERROR"

End If

EXITSUB:
OutPutList.ListIndex = OutPutList.ListCount - 1
End Sub

Private Sub Form_Initialize()
Dim rc As Long
Dim dwScope As Long
Dim mszReaders(2048) As Byte
Dim mszGroup(1024) As Byte
Dim pcchReaders As Long
Dim curReader As String
Dim i As Integer
hCard = 0
hContext = 0
fLookForCard = True

' Set Scope (see Scard.bas "Scopes")
dwScope = SCARD_SCOPE_USER

' Establish Context
rc = SCardEstablishContext(dwScope, 0, 0, hContext)

' Set maximum Length of mszReaders
pcchReaders = 2048

' Create a Multistring (terminated with two '\0's)
mszGroup(0) = &H0
mszGroup(1) = &H0

rc = SCardListReaders(hContext, mszGroup(LBound(mszGroup)), mszReaders(LBound(mszReaders)), pcchReaders)
    
ReaderList.Clear


' Split multistring and add single Readers to list
For i = 0 To pcchReaders - 2 Step 1
      curReader = curReader + GetString(mszReaders(i))
    
      If mszReaders(i) = &H0 And i <> 0 Then
        ReaderList.AddItem (curReader)
        curReader = ""
    End If
  
Next i


For i = 0 To ReaderList.ListCount - 1 Step 1
ReaderList.ListIndex = i
If ReaderList.Text = "OMNIKEY CardMan 5121 0" Then
SelectedReader = ReaderList.Text
End If
Next i
   
   
   
End Sub
Private Function HexDump(response() As Byte, ByVal lenr As Long) As String

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
' Convert 1 Byte to String
'
Private Function GetString(ByVal curByte As Byte) As String

GetString = String(1, curByte)

End Function

Private Function HexStrToInt(ByVal str As String) As Integer

Dim i As Integer
Dim iTmp As Integer
Dim sTmp As String

iStrLen = Len(str)

iTmp = 0
For i = 1 To Len(str)
    iTmp = iTmp * 16
    sTmp = Mid$(str, i, 1)
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
Next

HexStrToInt = iTmp

End Function

Private Function StrToArray(ByRef ucBuffer() As Byte, ByVal BufferLen As Integer, ByVal str As String) As Integer

Dim i As Integer
Dim iStrLen As Integer
Dim iTmp As Integer
Dim sTmp As String
Dim temp(64) As Byte
iStrLen = Len(str)

If (iStrLen Mod 2) <> 0 Then
OutPutList.AddItem "Invalid String"
Exit Function
End If

If BufferLen <> iStrLen / 2 Then
OutPutList.AddItem "Buffer size and string size does not match"
Exit Function
End If

iTmp = 0
For i = 1 To iStrLen
    sTmp = Mid$(str, i, 1)
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
  
    If (i Mod 2) = 0 Then
        temp((i / 2)) = iTmp
        iTmp = 0
    End If
    iTmp = iTmp * 16
Next


For i = 0 To BufferLen - 1 Step 1
ucBuffer(i) = temp(i + 1)
Next



StrToArray = iStrLen / 2


End Function

Private Sub iCLASSTransmit_Click()
Dim ucSendData(64) As Byte
Dim lSendDataLen As Long
Dim ucReceivedData(64) As Byte
Dim lReceivedDataLen As Long
Dim iStrLen As Integer

lReceivedDataLen = 64
If fCardConnected = False Then
OutPutList.AddItem " At first Card has to be connected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If

iStrLen = Len(iCLASSSendText.Text)
lSendDataLen = StrToArray(ucSendData, iStrLen / 2, iCLASSSendText.Text)

rc = SCardCLICCTransmit(hCard, ucSendData(LBound(ucSendData)), lSendDataLen, ucReceivedData(LBound(ucReceivedData)), lReceivedDataLen)
If rc <> 0 Then
OutPutList.AddItem "Error in  SCardCLICCTransmit"
OutPutList.AddItem HandleError(rc)
StatusText.Text = " SUCCESS"
End If

If rc = 0 Then
OutPutList.AddItem "SCardCLICCTransmit has been performed successfully"
StatusText.Text = " SUCCESS"
iCLASSReceivedText = HexDump(ucReceivedData, lReceivedDataLen)
End If







EXITSUB:
End Sub

Private Sub Increment_Click()
Dim ucData(4) As Byte
Dim DataLen As Long
Dim BlockNr As Long


If fCardConnected = False Then
OutPutList.AddItem "Card is not Connected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If

BlockNr = HexStrToInt(BlockNrText.Text)
DataLen = StrToArray(ucData, 4, IncrementValText.Text)
rc = SCardCLMifareStdIncrementVal(hCard, BlockNr, ucData(LBound(ucData)), DataLen)
If rc = 0 Then
OutPutList.AddItem "Value has been incremented  Successfully"
StatusText.Text = " SUCCESS"

End If

If rc <> 0 Then
OutPutList.AddItem "Error in  SCardCLMifareStdIncrementVal"
OutPutList.AddItem HandleError(rc)
StatusText.Text = " ERROR"

End If

EXITSUB:

OutPutList.ListIndex = OutPutList.ListCount - 1
End Sub

Private Sub OptionKey_Click()
AuthenKeyNrText.Text = ""
End Sub

Private Sub OptionKeyNr_Click()
AuthenKeyNrText.Text = "00"
End Sub

Private Sub Read_Click()

Dim BlockNr As Long
Dim ucData(16) As Byte
Dim NumofDataLen As Long

If fCardConnected = False Then
OutPutList.AddItem " At first Card has to be connected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If



BlockNr = HexStrToInt(BlockNrText.Text)
NumofDataLen = 16
rc = SCardCLMifareStdRead(hCard, BlockNr, ucData(LBound(ucData)), 16, NumofDataLen)

If rc = 0 Then
OutPutList.AddItem "Reading has been done successfully"
StatusText.Text = " SUCCESS"
DataReadText = HexDump(ucData, NumofDataLen)
End If

If rc <> 0 Then
OutPutList.AddItem "Error in  SCardCLMifareStdRead"
OutPutList.AddItem HandleError(rc)
StatusText.Text = " ERROR"

End If

EXITSUB:
OutPutList.ListIndex = OutPutList.ListCount - 1
End Sub

Private Sub ReaderList_Click()
Dim i As Integer

OutPutList.AddItem "Selected Reader is "
OutPutList.AddItem ReaderList.Text
SelectedReader = ReaderList.Text
End Sub
Private Function GetCardName() As String

CardNameText = "UNKNOWN CARD"
' atr with old driver
If ATRLen = 17 Then
If ATR(1) = 15 Then
If ATR(16) = 17 Then
CardNameText = "Mifare Standard 1K"
End If
If ATR(16) = 33 Then
CardNameText = "Mifare Standard 4K"
End If
If ATR(16) = 49 Then
CardNameText = "Mifare Ultra Light"
End If
If ATR(16) = 22 Then
CardNameText = "AT88RF020"
End If
If ATR(16) = 38 Then
CardNameText = "AT88SC6416CRF"
End If
If ATR(16) = 229 Then
CardNameText = "STm SR176"
End If
If ATR(16) = 245 Then
CardNameText = "STm SRI X4K"
End If
If ATR(16) = 24 Then
CardNameText = "I.CODE 1"
End If
If ATR(16) = 131 Then
CardNameText = "iClass"
End If
If ATR(16) = 212 Then
CardNameText = "KSW TempSens"
End If
If ATR(16) = 20 Then
CardNameText = "SRF55V10P"
End If
If ATR(16) = 180 Then
CardNameText = "I.CODE SLI"
End If
If ATR(16) = 148 Then
CardNameText = "Tag It"
End If
If ATR(16) = 164 Then
CardNameText = "X-ident STm LRI 512"
End If
If ATR(16) = 195 Then
CardNameText = "iCLASS 2K"
End If
If ATR(16) = 147 Then
CardNameText = "iCLASS 2KS"
End If
If ATR(16) = 211 Then
CardNameText = "iCLASS 16K"
End If
If ATR(16) = 163 Then
CardNameText = "iCLASS 16KS"
End If
If ATR(16) = 227 Then
CardNameText = "iCLASS 8x2K"
End If
If ATR(16) = 179 Then
CardNameText = "iCLASS 8x2KS"
End If

End If
End If



' atr with new driver Pc/Sc

If ATRLen = 20 Then
If ATR(13) = 0 Then
If ATR(14) = 1 Then
CardNameText = "Mifare Standard 1K"
End If
If ATR(14) = 2 Then
CardNameText = "Mifare Standard 4K"
End If
If ATR(14) = 3 Then
CardNameText = "Mifare Ultra Light"
End If
If ATR(14) = 4 Then
CardNameText = "SLE55R_XXXX"
End If
If ATR(14) = 6 Then
CardNameText = "SR176"
End If
If ATR(14) = 7 Then
CardNameText = "SRI_X4K"
End If
If ATR(14) = 8 Then
CardNameText = "AT88RF020"
End If
If ATR(14) = 9 Then
CardNameText = "AT88SC0204CRF"
End If
If ATR(14) = 10 Then
CardNameText = "AT88SC0808CRF"
End If
If ATR(14) = 11 Then
CardNameText = "AT88SC1616RF"
End If
If ATR(14) = 12 Then
CardNameText = "AT88SC3216CRF"
End If
If ATR(14) = 13 Then
CardNameText = "AT88SC6416CRF"
End If
If ATR(14) = 14 Then
CardNameText = "SRF55V10P"
End If
If ATR(14) = 15 Then
CardNameText = "SRF55V02P"
End If
If ATR(14) = 16 Then
CardNameText = "SRF55V10S"
End If
If ATR(14) = 17 Then
CardNameText = "SRF55V02S"
End If
If ATR(14) = 18 Then
CardNameText = "TAG_IT"
End If
If ATR(14) = 19 Then
CardNameText = "LRI512"
End If
If ATR(14) = 20 Then
CardNameText = "ICODE.SII"
End If
If ATR(14) = 21 Then
CardNameText = "TEMPSENS"
End If
If ATR(14) = 22 Then
CardNameText = "i.CODE1"
End If
If ATR(14) = 24 Then
CardNameText = "iCLASS2KS"
End If
If ATR(14) = 26 Then
CardNameText = "iCLASS16KS"
End If
If ATR(14) = 28 Then
CardNameText = "iCLASS8x2KS"
End If
If ATR(14) = 29 Then
CardNameText = "iCLASS32KS_16_16"
End If
If ATR(14) = 30 Then
CardNameText = "iCLASS32KS_16_8x2"
End If
If ATR(14) = 31 Then
CardNameText = "iCLASS32KS_8x2_16"
End If
If ATR(14) = 32 Then
CardNameText = "iCLASS32KS_8x2_8x2"
End If

End If
End If

GetCardName = CardNameText
End Function


Private Sub RefreshOutput_Click()
OutPutList.Clear

End Sub

Private Sub Write_Click()

Dim BlockNr As Long
Dim ucData(16) As Byte
Dim DataLen As Long
BlockNr = HexStrToInt(BlockNrText.Text)

If fCardConnected = False Then
OutPutList.AddItem " At first Card has to be connected"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If

If BlockNr < 128 Then
If ((BlockNr + 1) Mod 4) = 0 Then
OutPutList.AddItem " Sector block cannot be written with this applpication"
StatusText.Text = " ERROR"
GoTo EXITSUB
End If
End If
If BlockNr > 128 Then
If ((BlockNr + 1) Mod 16) = 0 Then
OutPutList.AddItem " Sector block cannot be written with this applpication "
StatusText.Text = " ERROR"
GoTo EXITSUB
End If
End If


DataLen = StrToArray(ucData, 16, DataWriteText.Text)

rc = SCardCLMifareStdWrite(hCard, BlockNr, ucData(LBound(ucData)), DataLen)
If rc = 0 Then
OutPutList.AddItem " Data has been written successfully"
StatusText.Text = " SUCCESS"
End If
If rc <> 0 Then
OutPutList.AddItem " Error in writting Data "
StatusText.Text = " ERROR"
OutPutList.AddItem HandleError(rc)
End If

EXITSUB:
OutPutList.ListIndex = OutPutList.ListCount - 1

End Sub

Private Sub WriteMifKeyToReader_Click()
Dim MifKeyToReader(6) As Byte
Dim MifKeyNr As Long
Dim KeyLen As Long

MifKeyNr = HexStrToInt(MifKeyToReaderNrText.Text)
KeyLen = StrToArray(MifKeyToReader, 6, MifareKeyToReaderText.Text)

rc = SCardCLWriteMifareKeyToReader(hCard, hContext, SelectedReader, MifKeyNr, KeyLen, MifKeyToReader(LBound(MifKeyToReader)), False, 0)

If rc = 0 Then
OutPutList.AddItem " Mifare key has been writen to the reader successfully"
StatusText.Text = " SUCCESS"
End If
If rc <> 0 Then
OutPutList.AddItem " Error in writting Mifare key to the reader "
OutPutList.AddItem HandleError(rc)
StatusText.Text = " ERROR"
End If

OutPutList.ListIndex = OutPutList.ListCount - 1
End Sub

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




