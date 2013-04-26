/*

  Header for testing functions, they should never come to customer !!

 */

// Prevent multiple includes
#ifndef __SM5121T_H__
	#define __SM5121T_H__

#ifdef __SM5121T_C__
	#define EXTERN
#else
	#define EXTERN extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

// transmit a wrong signature to the reader
unsigned long SecureModeTransmitWrongSignature(SCARDHANDLE hCard,
									   unsigned char * pbSend,
									   unsigned char   bSendLen,
									   unsigned char * pbReceive,
									   unsigned char * pbReceiveLen);

// transmit a wrong rdh
unsigned long SecureModeTransmitWrongRDH(SCARDHANDLE hCard,
									   unsigned char * pbSend,
									   unsigned char   bSendLen,
									   unsigned char * pbReceive,
									   unsigned char * pbReceiveLen);

// transmit wrong omnikey proprietary data
unsigned long SecureModeTransmitWrongOKData(SCARDHANDLE hCard,
									   unsigned char * pbSend,
									   unsigned char   bSendLen,
									   unsigned char * pbReceive,
									   unsigned char * pbReceiveLen);

#ifdef __cplusplus
}
#endif

#undef EXTERN

#endif
