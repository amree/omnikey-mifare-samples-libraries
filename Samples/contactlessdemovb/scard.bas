Attribute VB_Name = "Scard"

' *******************************************************
' Common SCard functions
' *******************************************************

'
' Establish a context to resource manager
' Parameters:
'       dwScope         = Scope (see Scopes)
'       pvReserved1     = Reserved for further use
'       pvReserved2     = Reserved for further use
'       phContext       = Pointer to Context
'
Public Declare Function SCardEstablishContext Lib "WINSCARD" _
    (ByVal dwScope As Long, _
     ByVal pvReserved1 As Long, _
     ByVal pvReserved2 As Long, _
     ByRef phContext As Long) As Long

'
' Release current Context
' Parameters:
'       hContext        = current Context
'
Public Declare Function SCardReleaseContext Lib "WINSCARD" _
    (ByVal hContext As Long) As Long

'
' List all availiable Readers
' Parameters:
'       hContext        = current Context
'       mszGroups       = multistring, containing groupnames
'                          if mszGroups is not null only Readers which are
'                          in specified groups are listed
'       mszReaders      = multistring, containing all availiable Readers
'       pcchReaders     = Length of mszReaders in Bytes
'
Public Declare Function SCardListReaders Lib "WINSCARD" Alias "SCardListReadersA" _
    (ByVal hContext As Long, _
     ByVal mszGroups As Byte, _
     ByRef mszReaders As Byte, _
     ByRef pcchReaders As Long) As Long

'
' Connect to one specific Reader
' Parameters:
'       hContext                = current Context
'       szReaders               = name of a Reader
'       dwShareMode             = Share Mode (see ShareModes)
'       dwPreferredProtocols    = Preferred Protocol (see Protocols)
'       hCard                   = Handle to Card
'       dwActiveProtocol        = Returned Protocol
'
Public Declare Function SCardConnect Lib "WINSCARD" Alias "SCardConnectA" _
    (ByVal hContext As Long, _
     ByVal szReader As String, _
     ByVal dwShareMode As Long, _
     ByVal dwPreferredProtocols As Long, _
     ByRef hCard As Long, _
     ByRef dwActiveProtocol As Long) As Long
     
     
 Public Declare Function SCardGetAttrib Lib "WINSCARD" _
    (ByVal hCard As Long, _
     ByVal dwAttrId As Long, _
     ByRef pbAttr As Byte, _
     ByRef pcbAttrLen As Long) As Long
     
    
     
'
' Disconnect from Card
' Parameters:
'       hCard           = Handle to Card
'       dwDisposition   = Action to do with Card (see Dispositions)
'
Public Declare Function SCardDisconnect Lib "WINSCARD" _
    (ByVal hCard As Long, _
     ByVal dwDisposition As Long) As Long

' *******************************************************
' Constants
' *******************************************************

'
' Scopes
'
Public Const SCARD_SCOPE_USER       As Long = 0 'The context is a user context, and any
                                                ' database operations are performed within the
                                                ' domain of the user.
Public Const SCARD_SCOPE_TERMINAL   As Long = 1 'The context is that of the current terminal,
                                                ' and any database operations are performed
                                                ' within the domain of that terminal.  (The
                                                ' calling application must have appropriate
                                                ' access permissions for any database actions.)
Public Const SCARD_SCOPE_SYSTEM     As Long = 2 'The context is the system context, and any
                                                ' database operations are performed within the
                                                ' domain of the system.  (The calling
                                                ' application must have appropriate access
                                                ' permissions for any database actions.)

'
' Share Modes
'
Public Const SCARD_SHARE_EXCLUSIVE  As Long = 1 ' This application is not willing to share this
                                                ' card with other applications.
Public Const SCARD_SHARE_SHARED     As Long = 2 ' This application is willing to share this
                                                ' card with other applications.
Public Const SCARD_SHARE_DIRECT     As Long = 3 ' This application demands direct control of
                                                ' the reader, so it is not available to other
                                                ' applications.
Public Const SCARD_ATTR_ATR_STRING As Long = 590595

'
' Protocols
'
Public Const SCARD_PROTOCOL_UNDEFINED   As Long = &H0       ' There is no active protocol.
Public Const SCARD_PROTOCOL_T0          As Long = &H1       ' T=0 is the active protocol.
Public Const SCARD_PROTOCOL_T1          As Long = &H2       ' T=1 is the active protocol.
Public Const SCARD_PROTOCOL_RAW         As Long = &H10000   ' Raw is the active protocol.


'
' Dispositions (after disconnecting)
'
Public Const SCARD_LEAVE_CARD   As Long = 0   ' Don't do anything special on close
Public Const SCARD_RESET_CARD   As Long = 1   ' Reset the card on close
Public Const SCARD_UNPOWER_CARD As Long = 2   ' Power down the card on close
Public Const SCARD_EJECT_CARD   As Long = 3   ' Eject the card on close

'
' Smart Card Error Codes
' All for SCARD error codes of the resource manager , a OK error code exists.
'
Public Const OKERR_SCARD__E_CANCELLED                As Long = &H80100002 '@cnst  The action was cancelled by an SCardCancel request
Public Const OKERR_SCARD__E_INVALID_HANDLE           As Long = &H80100003 '@cnst  The supplied handle was invalid
Public Const OKERR_SCARD__E_INVALID_PARAMETER        As Long = &H80100004 '@cnst  One or more of the supplied parameters could not be properly interpreted
Public Const OKERR_SCARD__E_INVALID_TARGET           As Long = &H80100005 '@cnst  Registry startup information is missing or invalid
Public Const OKERR_SCARD__E_NO_MEMORY                As Long = &H80100006 '@cnst  Not enough memory available to complete this command
Public Const OKERR_SCARD__F_WAITED_TOO_LONG          As Long = &H80100007 '@cnst  An internal consistency timer has expired
Public Const OKERR_SCARD__E_INSUFFICIENT_BUFFER      As Long = &H80100008 '@cnst  The data buffer to receive returned data is too small for the returned data
Public Const OKERR_SCARD__E_UNKNOWN_READER           As Long = &H80100009 '@cnst  The specified reader name is not recognized
Public Const OKERR_SCARD__E_TIMEOUT                  As Long = &H8010000A '@cnst  The user-specified timeout value has expired
Public Const OKERR_SCARD__E_SHARING_VIOLATION        As Long = &H8010000B '@cnst  The smart card cannot be accessed because of other connections outstanding
Public Const OKERR_SCARD__E_NO_SMARTCARD             As Long = &H8010000C '@cnst  The operation requires a Smart Card, but no Smart Card is currently in the device
Public Const OKERR_SCARD__E_UNKNOWN_CARD             As Long = &H8010000D '@cnst  The specified smart card name is not recognized
Public Const OKERR_SCARD__E_CANT_DISPOSE             As Long = &H8010000E '@cnst  The system could not dispose of the media in the requested manner
Public Const OKERR_SCARD__E_PROTO_MISMATCH           As Long = &H8010000F '@cnst  The requested protocols are incompatible with the protocol currently in use with the smart card
Public Const OKERR_SCARD__E_NOT_READY                As Long = &H80100010 '@cnst  The reader or smart card is not ready to accept commands
Public Const OKERR_SCARD__E_INVALID_VALUE            As Long = &H80100011 '@cnst  One or more of the supplied parameters values could not be properly interpreted
Public Const OKERR_SCARD__E_SYSTEM_CANCELLED         As Long = &H80100012 '@cnst  The action was cancelled by the system, presumably to log off or shut down
Public Const OKERR_SCARD__F_COMM_ERROR               As Long = &H80100013 '@cnst  An internal communications error has been detected
Public Const OKERR_SCARD__F_UNKNOWN_ERROR            As Long = &H80100014 '@cnst  An internal error has been detected, but the source is unknown
Public Const OKERR_SCARD__E_INVALID_ATR              As Long = &H80100015 '@cnst  An ATR obtained from the registry is not a valid ATR string
Public Const OKERR_SCARD__E_NOT_TRANSACTED           As Long = &H80100016 '@cnst  An attempt was made to end a non-existent transaction
Public Const OKERR_SCARD__E_READER_UNAVAILABLE       As Long = &H80100017 '@cnst  The specified reader is not currently available for use
Public Const OKERR_SCARD__P_SHUTDOWN                 As Long = &H80100018 '@cnst  The operation has been aborted to allow the server application to exit
Public Const OKERR_SCARD__E_PCI_TOO_SMALL            As Long = &H80100019 '@cnst  The PCI Receive buffer was too small
Public Const OKERR_SCARD__E_READER_UNSUPPORTED       As Long = &H8010001A '@cnst  The reader driver does not meet minimal requirements for support
Public Const OKERR_SCARD__E_DUPLICATE_READER         As Long = &H8010001B '@cnst  The reader driver did not produce a unique reader name
Public Const OKERR_SCARD__E_CARD_UNSUPPORTED         As Long = &H8010001C '@cnst  The smart card does not meet minimal requirements for support
Public Const OKERR_SCARD__E_NO_SERVICE               As Long = &H8010001D '@cnst  The Smart card resource manager is not running
Public Const OKERR_SCARD__E_SERVICE_STOPPED          As Long = &H8010001E '@cnst  The Smart card resource manager has shut down
Public Const OKERR_SCARD__E_UNEXPECTED               As Long = &H8010001F '@cnst  An unexpected card error has occurred
Public Const OKERR_SCARD__E_ICC_INSTALLATION         As Long = &H80100020 '@cnst  No Primary Provider can be found for the smart card
Public Const OKERR_SCARD__E_ICC_CREATEORDER          As Long = &H80100021 '@cnst  The requested order of object creation is not supported
Public Const OKERR_SCARD__E_UNSUPPORTED_FEATURE      As Long = &H80100022 '@cnst  This smart card does not support the requested feature
Public Const OKERR_SCARD__E_DIR_NOT_FOUND            As Long = &H80100023 '@cnst  The identified directory does not exist in the smart card
Public Const OKERR_SCARD__E_FILE_NOT_FOUND           As Long = &H80100024 '@cnst  The identified file does not exist in the smart card
Public Const OKERR_SCARD__E_NO_DIR                   As Long = &H80100025 '@cnst  The supplied path does not represent a smart card directory
Public Const OKERR_SCARD__E_NO_FILE                  As Long = &H80100026 '@cnst  The supplied path does not represent a smart card file
Public Const OKERR_SCARD__E_NO_ACCESS                As Long = &H80100027 '@cnst  Access is denied to this file
Public Const OKERR_SCARD__E_WRITE_TOO_MANY           As Long = &H80100028 '@cnst  An attempt was made to write more data than would fit in the target object
Public Const OKERR_SCARD__E_BAD_SEEK                 As Long = &H80100029 '@cnst  There was an error trying to set the smart card file object pointer
Public Const OKERR_SCARD__E_INVALID_CHV              As Long = &H8010002A '@cnst  The supplied PIN is incorrect
Public Const OKERR_SCARD__E_UNKNOWN_RES_MNG          As Long = &H8010002B '@cnst  An unrecognized error code was returned from a layered component
Public Const OKERR_SCARD__E_NO_SUCH_CERTIFICATE      As Long = &H8010002C '@cnst  The requested certificate does not exist
Public Const OKERR_SCARD__E_CERTIFICATE_UNAVAILABLE  As Long = &H8010002D '@cnst  The requested certificate could not be obtained
Public Const OKERR_SCARD__E_NO_READERS_AVAILABLE     As Long = &H8010002E '@cnst  Cannot find a smart card reader
Public Const OKERR_SCARD__E_COMM_DATA_LOST           As Long = &H8010002F '@cnst  A communications error with the smart card has been detected
Public Const OKERR_SCARD__W_UNSUPPORTED_CARD         As Long = &H80100065 '@cnst  The reader cannot communicate with the smart card, due to ATR configuration conflicts
Public Const OKERR_SCARD__W_UNRESPONSIVE_CARD        As Long = &H80100066 '@cnst  The smart card is not responding to a reset
Public Const OKERR_SCARD__W_UNPOWERED_CARD           As Long = &H80100067 '@cnst  Power has been removed from the smart card, so that further communication is not possible
Public Const OKERR_SCARD__W_RESET_CARD               As Long = &H80100068 '@cnst  The smart card has been reset, so any shared state information is invalid
Public Const OKERR_SCARD__W_REMOVED_CARD             As Long = &H80100069 '@cnst  The smart card has been removed, so that further communication is not possible
Public Const OKERR_SCARD__W_SECURITY_VIOLATION       As Long = &H8010006A '@cnst  Access was denied because of a security violation
Public Const OKERR_SCARD__W_WRONG_CHV                As Long = &H8010006B '@cnst  The card cannot be accessed because the wrong PIN was presented
Public Const OKERR_SCARD__W_CHV_BLOCKED              As Long = &H8010006C '@cnst  The card cannot be accessed because the maximum number of PIN entry attempts has been reached
Public Const OKERR_SCARD__W_EOF                      As Long = &H8010006D '@cnst  The end of the smart card file has been reached
Public Const OKERR_SCARD__W_CANCELLED_BY_USER        As Long = &H8010006E '@cnst  The action was cancelled by the user

Public Const OKERR_PARM1                As Long = &H81000000 'Error in parameter 1
Public Const OKERR_PARM2                As Long = &H81000001 'Error in parameter 2
Public Const OKERR_PARM3                As Long = &H81000002 'Error in parameter 3
Public Const OKERR_PARM4                As Long = &H81000003 'Error in parameter 4
Public Const OKERR_PARM5                As Long = &H81000004 'Error in parameter 5
Public Const OKERR_PARM6                As Long = &H81000005 'Error in parameter 6
Public Const OKERR_PARM7                As Long = &H81000006 'Error in parameter 7
Public Const OKERR_PARM8                As Long = &H81000007 'Error in parameter 8
Public Const OKERR_PARM9                As Long = &H81000008 'Error in parameter 9
Public Const OKERR_PARM10               As Long = &H81000009 'Error in parameter 10
Public Const OKERR_PARM11               As Long = &H8100000A 'Error in parameter 11
Public Const OKERR_PARM12               As Long = &H8100000B 'Error in parameter 12
Public Const OKERR_PARM13               As Long = &H8100000C 'Error in parameter 13
Public Const OKERR_PARM14               As Long = &H8100000D 'Error in parameter 14
Public Const OKERR_PARM15               As Long = &H8100000E 'Error in parameter 15
Public Const OKERR_PARM16               As Long = &H8100000F 'Error in parameter 16
Public Const OKERR_PARM17               As Long = &H81000010 'Error in parameter 17
Public Const OKERR_PARM18               As Long = &H81000011 'Error in parameter 18
Public Const OKERR_PARM19               As Long = &H81000012 'Error in parameter 19
Public Const OKERR_INSUFFICIENT_PRIV    As Long = &H81100000 'You currently do not have the rights to execute the requested action. Usually a password has to be presented in advance.
Public Const OKERR_PW_WRONG             As Long = &H81100001 'The presented password is wrong
Public Const OKERR_PW_LOCKED            As Long = &H81100002 'The password has been presented several times wrong and is therefore locked. Usually use some administrator tool to unblock it.
Public Const OKERR_PW_TOO_SHORT         As Long = &H81100003 'The lenght of the password was too short.
Public Const OKERR_PW_TOO_LONG          As Long = &H81100004 'The length of the password was too long.
Public Const OKERR_PW_NOT_LOCKED        As Long = &H81100005 'The password is not locked
Public Const OKERR_ITEM_NOT_FOUND       As Long = &H81200000 'An item (e.g. a key of a specific name) could not be found
Public Const OKERR_ITEMS_LEFT           As Long = &H81200001 'There are still items left, therefore e.g. the directory / structure etc. can't be deleted.
Public Const OKERR_INVALID_CFG_FILE     As Long = &H81200002 'Invalid configuration file
Public Const OKERR_SECTION_NOT_FOUND    As Long = &H81200003 'Section not found
Public Const OKERR_ENTRY_NOT_FOUND      As Long = &H81200004 'Entry not found
Public Const OKERR_NO_MORE_SECTIONS     As Long = &H81200005 'No more sections
Public Const OKERR_ITEM_ALREADY_EXISTS  As Long = &H81200006 'The specified item alread exists.
Public Const OKERR_ITEM_EXPIRED         As Long = &H81200007 'Some item (e.g. a certificate) has expired.
Public Const OKERR_UNEXPECTED_RET_VALUE As Long = &H81300000 'Unexpected return value
Public Const OKERR_COMMUNICATE          As Long = &H81300001 'General communication error
Public Const OKERR_NOT_ENOUGH_MEMORY    As Long = &H81300002 'Not enough memory
Public Const OKERR_BUFFER_OVERFLOW      As Long = &H81300003 'Buffer overflow
Public Const OKERR_TIMEOUT              As Long = &H81300004 'A timeout has occurred
Public Const OKERR_NOT_SUPPORTED        As Long = &H81300005 'The requested functionality is not supported at this time / under this OS / in this situation etc.
Public Const OKERR_ILLEGAL_ARGUMENT     As Long = &H81300006 'Illegal argument
Public Const OKERR_READ_FIO             As Long = &H81300007 'File IO read error
Public Const OKERR_WRITE_FIO            As Long = &H81300008 'File IO write error
Public Const OKERR_INVALID_HANDLE       As Long = &H81300009 'Invalid handle
Public Const OKERR_GENERAL_FAILURE      As Long = &H8130000A 'General failure. Use this error code in cases where no other errors match and it is not worth to define a new error code.
Public Const OKERR_FILE_NOT_FOUND       As Long = &H8130000B 'File not found
Public Const OKERR_OPEN_FILE            As Long = &H8130000C 'File opening failed
Public Const OKERR_SEM_USED             As Long = &H8130000D 'The semaphore is currently use by an other process
Public Const OKERR_NOP                  As Long = &H81F00001 'No operation done
Public Const OKERR_NOK                  As Long = &H81F00002 'Function not executed
Public Const OKERR_FWBUG                As Long = &H81F00003 'Internal error detected
Public Const OKERR_INIT                 As Long = &H81F00004 'Module not initialized
Public Const OKERR_FIO                  As Long = &H81F00005 'File IO error detected
Public Const OKERR_ALLOC                As Long = &H81F00006 'Cannot allocate memory
Public Const OKERR_SESSION_ERR          As Long = &H81F00007 'General error
Public Const OKERR_ACCESS_ERR           As Long = &H81F00008 'Access not allowed
Public Const OKERR_OPEN_FAILURE         As Long = &H81F00009 'An open command was not successful
Public Const OKERR_CARD_NOT_POWERED     As Long = &H81F0000A 'Card is not powered
Public Const OKERR_ILLEGAL_CARDTYPE     As Long = &H81F0000B 'Illegal cardtype
Public Const OKERR_CARD_NOT_INSERTED    As Long = &H81F0000C 'Card not inserted
Public Const OKERR_NO_DRIVER            As Long = &H81F0000D 'No device driver installed
Public Const OKERR_OUT_OF_SERVICE       As Long = &H81F0000E 'The service is currently not available
Public Const OKERR_EOF_REACHED          As Long = &H81F0000F 'End of file reached
Public Const OKERR_ON_BLACKLIST         As Long = &H81F00010 'The ID is on a blacklist, the requested action is therefore not allowed.
Public Const OKERR_CONSISTENCY_CHECK    As Long = &H81F00011 'Error during consistency check
Public Const OKERR_IDENTITY_MISMATCH    As Long = &H81F00012 'The identity does not match a defined cross-check identity
Public Const OKERR_MULTIPLE_ERRORS      As Long = &H81F00013 'Multiple errors have occurred. Use this if there is only the possibility to return one error code, but there happened different errors before (e.g. each thread returned a different error and the controlling thread may only report one).
Public Const OKERR_ILLEGAL_DRIVER       As Long = &H81F00014 'Illegal driver
Public Const OKERR_ILLEGAL_FW_RELEASE   As Long = &H81F00015 'The connected hardware whose firmware is not useable by this software
Public Const OKERR_NO_CARDREADER        As Long = &H81F00016 'No cardreader attached
Public Const OKERR_IPC_FAULT            As Long = &H81F00017 'General failure of inter process communication
Public Const OKERR_WAIT_AND_RETRY       As Long = &H81F00018 'The service currently does not take calls. The task has to go back to the message loop and try again at a later time (Windows 3.1 only). The code may also be used, in every situation where a ‘  wait and retry ’  action is requested.

