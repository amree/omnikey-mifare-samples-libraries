// Prevent multiple includes
#ifndef __SM5X21_H__
	#define __SM5121_H__

#ifdef __SM5X21_C__
	#define EXTERN 
#else
	#define EXTERN extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

// global defines
#define SM_SUCCESS		0x00
#define SM_ERROR		0x01
#define SM_WRONG_HDH	0x02
#define SM_WRONG_SIG	0x03
#define SM_WRONG_LENGTH 0x04



#define SM_SESSION_READ		0x00
#define SM_SESSION_WRITE	0xFF


#define MAX_BUFFER_SIZE		128


/*
 * Global Variables
 */

EXTERN unsigned char bHDH[2];// = {0};
EXTERN unsigned char bRDH[2];// = {0};

EXTERN unsigned char bSessionKey[16];//  = {0};

EXTERN unsigned char bSendBuffer[MAX_BUFFER_SIZE];// = {0};
EXTERN unsigned char bSendBufferLen;// = MAX_BUFFER_SIZE;

EXTERN unsigned char bRecvBuffer[MAX_BUFFER_SIZE];// = {0};
EXTERN unsigned char bRecvBufferLen;// = MAX_BUFFER_SIZE;

EXTERN unsigned char bTempBuffer[MAX_BUFFER_SIZE];// = {0};
EXTERN unsigned char bTmp;

EXTERN unsigned char *bOutTempBuffer;
EXTERN int iOutTmp;


// function declarations

// initialise a secure mode session.
// Parameters:
//		* phCard       - SCARDHANDLE got from SCardConnect
//		* pbKey        - Key (should be Kcur or Kcuw)
//		* bKeyLen      - Length of pbKey
//		* bSessionType - Type of Session (Read or Write)
// return predefined status
unsigned long SecureModeInitSession(SCARDHANDLE hCard,
							unsigned char *	pbKey,
							unsigned char	bKeyLen,
							unsigned char	bSessionType);

// Close current Secure Mode Session
// return predefined status
unsigned long SecureModeCloseSession(SCARDHANDLE hCard);


// Encrypt given command, according to Secure Mode specification,
// send encrypted command to reader through SCardCLICCTransmit
// and decrypt response.
// Paramteres:
//		* pbSend		- IN Command to send
//		* bSendLen		- IN Length of pbSend
//		* pbReceive		- OUT Response from reader/card
//		* bReceiveLen	- IN Length of pbReceive-Buffer / OUT Length of Repsonse Data
//					
// return predefined status
unsigned long SecureModeTransmit(SCARDHANDLE hCard,
						 unsigned char * pbSend,
						 unsigned char	 bSendLen,
						 unsigned char * pbReceive,
						 unsigned char * pbReceiveLen);

#ifdef __cplusplus
}
#endif

#undef EXTERN

#endif
