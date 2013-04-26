/**
****************************************************************************** 
* @file
* @brief Testing function for sm5x21t lib
*
*
****************************************************************************** 
* $HeadURL: file:///Z:/subversion/sw/cmsync/trunk/sm5x21lib/src/sm5x21t.c $
*
* @date $LastChangedDate: 2006-11-29 10:35:47 +0100 (Mi, 29 Nov 2006) $
* @version $Revision: 73 $ ($LastChangedRevision: 73 $)
* @author $Author: mf $
* 
* Copyright © 2000 - 2006 OMNIKEY
******************************************************************************/

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <winscard.h>

#define __SM5121T_C__

#include "sm5x21.h"
#include "sm5x21i.h"
#include "sm5x21t.h"

#include "ok.h"
#include "scardcl.h"

/** @brief Transmit a wrong signature to the reader

    Perform a secure mode transmit but insert an error into the signature. So the 
    errorcase can be checked.
    
    @param hCard        Cardhandle
    @param pbSend       Data to send down
    @param bSendLen     Length of data to be send down
    @param pbReceive    Databuffer for returned data
    @param pbReceiveLen Length of data returned in pbReceive
    
    @retval SM_SUCCESS  successfull
    @retval SCARD_*     some SCard-error
*/
unsigned long SecureModeTransmitWrongSignature(SCARDHANDLE hCard,
									   unsigned char * pbSend,
									   unsigned char  bSendLen,
									   unsigned char * pbReceive,
									   unsigned char * pbReceiveLen)
{
	int rc = 0;
	unsigned long ulRecvBufferLen;
	unsigned char i, bByte=0x00;

	// clear all buffers
	memset(bSendBuffer,0x00,sizeof(bSendBuffer));
	memset(bRecvBuffer,0x00,sizeof(bRecvBuffer));
	memset(bTempBuffer,0x00,sizeof(bTempBuffer));
	*pbReceiveLen=0;

	// prepare send buffer
	bSendBufferLen=0x00;
	bSendBuffer[bSendBufferLen++]=pbSend[0]; // CLA
	bSendBuffer[bSendBufferLen++]=pbSend[1]; // INS
	bSendBuffer[bSendBufferLen++]=pbSend[2]; // P1
	bSendBuffer[bSendBufferLen++]=pbSend[3]; // P2
	
	// have to save HDH and RDH for comparison later
	bHDH[0]=GetRandomByte(); bHDH[1]=GetRandomByte();
	// invert last recevied RDH
	bRDH[0]=~bRDH[0]; bRDH[1]=~bRDH[1];

	// Prepare temporary buffer for encryption
	bTmp=0;

	bTempBuffer[bTmp++]=bHDH[0];
	bTempBuffer[bTmp++]=bHDH[1];
	
	bTempBuffer[bTmp++]=bRDH[0];
	bTempBuffer[bTmp++]=bRDH[1];

	// if the given command (pbSend) is more than 4 bytes long length + data have been given
	// copy the length and the data to bTempBuffer, else just say length is zero
	if(bSendLen > 4)
	{
		bTempBuffer[bTmp++]=pbSend[4]; // length of data
		// add data
		for(i=0;i < pbSend[4];i++)
		{
			bTempBuffer[bTmp++]=pbSend[i+5];
		}
	}
	else
		bTempBuffer[bTmp++]=0x00;

	// add padding
	bTempBuffer[bTmp++]=0x80;
	while(bTmp % 8 != 0x00)
		bTempBuffer[bTmp++]=0x00;

	// create and add the signature of this buffer
	sm_create_signature(bSessionKey);

	// *************************************************************
	// change signature
    // *************************************************************

	// just replace byte 4 with byte 5 of the signature and 5 with 4.

	bByte=bTempBuffer[bTmp-4];
	bTempBuffer[bTmp-4]=bTempBuffer[bTmp-3];
	bTempBuffer[bTmp-3]=bByte;
		

	// *************************************************************

	// encrypt it to get omnikey proprietary data
	sm_create_okdata(bSessionKey);

	// check if LE is given
	// (CLA INS P1 P2 [LC] [DATA] [LE]) .. [] fields are optional
	// check if bSendLen > 4 checks if LC is available 
	// check if pbSend[4] (LC) + 5 (size of header) is less than bSendLen 
	if(bSendLen > 4 && (pbSend[4] + 5) < bSendLen)
	{
		// attach LE (the last byte)
		bSendBuffer[bSendBufferLen++]=pbSend[bSendLen-1];
	}

	// send to card/reader
	bRecvBufferLen=sizeof(bRecvBuffer);
	ulRecvBufferLen=bRecvBufferLen;
	rc = SCardCLICCTransmit(hCard,bSendBuffer,bSendBufferLen,bRecvBuffer,&ulRecvBufferLen);
	if(rc != SCARD_S_SUCCESS)
	{
		return rc; //SM_ERROR;
	}
	else
	{
		// check data
		bRecvBufferLen = (unsigned char)ulRecvBufferLen;

		rc = sm_check_data();
		if(rc == SM_SUCCESS)
		{
			// if more than 2 bytes returned
			// copy response data to buffer
			// because of the data structure
			// HDH RDH LC DATA PADDING SIGNATURE
			//  2   2   1  xx    xx      xx			// unsigned charS (xx means variable length)
			// copy starts at byte 5 (DATA) with length stored in byte 4 (LC)
			if(bRecvBufferLen > 2)
			{
				memcpy(pbReceive,&bTempBuffer[5],bTempBuffer[4]);
				*pbReceiveLen=bTempBuffer[4];
			} 

			// attach sw1sw2 which are the last 2 bytes in bRecvBuffer
			memcpy(&pbReceive[*pbReceiveLen],&bRecvBuffer[bRecvBufferLen-2],2);

			// return length (LC + sw1sw2)
			*pbReceiveLen=*pbReceiveLen+2;
		}
		else
		{
			return rc;
		}

	}

	return SM_SUCCESS;
}

/** @brief Transmit a wrong RDH to the reader

    Perform a secure mode transmit but destroy the RDH (reader data header). So the 
    errorcase can be checked.
    
    @param hCard        Cardhandle
    @param pbSend       Data to send down
    @param bSendLen     Length of data to be send down
    @param pbReceive    Databuffer for returned data
    @param pbReceiveLen Length of data returned in pbReceive
    
    @retval SM_SUCCESS  successfull
    @retval SCARD_*     some SCard-error
*/
unsigned long SecureModeTransmitWrongRDH(SCARDHANDLE hCard,
							     unsigned char * pbSend,
							     unsigned char	bSendLen,
							     unsigned char * pbReceive,
							     unsigned char * pbReceiveLen)
{
	int rc = 0;
	unsigned long ulRecvBufferLen;
	unsigned char i, bByte=0x00;

	// clear all buffers
	memset(bSendBuffer,0x00,sizeof(bSendBuffer));
	memset(bRecvBuffer,0x00,sizeof(bRecvBuffer));
	memset(bTempBuffer,0x00,sizeof(bTempBuffer));
	*pbReceiveLen=0;

	// prepare send buffer
	bSendBufferLen=0x00;
	bSendBuffer[bSendBufferLen++]=pbSend[0]; // CLA
	bSendBuffer[bSendBufferLen++]=pbSend[1]; // INS
	bSendBuffer[bSendBufferLen++]=pbSend[2]; // P1
	bSendBuffer[bSendBufferLen++]=pbSend[3]; // P2
	
	// have to save HDH and RDH for comparison later
	bHDH[0]=GetRandomByte(); bHDH[1]=GetRandomByte();
	// invert last recevied RDH
	bRDH[0]=~bRDH[0]; bRDH[1]=~bRDH[1];

	// Prepare temporary buffer for encryption
	bTmp=0;

	bTempBuffer[bTmp++]=bHDH[0];
	bTempBuffer[bTmp++]=bHDH[1];
	
	// *************************************************************
	// change RDH... should be wrong ! ..
	bTempBuffer[bTmp++]=bRDH[0]+1;
	bTempBuffer[bTmp++]=bRDH[1]-1;

	// *************************************************************

	// if the given command (pbSend) is more than 4 bytes long length + data have been given
	// copy the length and the data to bTempBuffer, else just say length is zero
	if(bSendLen > 4)
	{
		bTempBuffer[bTmp++]=pbSend[4]; // length of data
		// add data
		for(i=0;i < pbSend[4];i++)
		{
			bTempBuffer[bTmp++]=pbSend[i+5];
		}
	}
	else
		bTempBuffer[bTmp++]=0x00;

	// add padding
	bTempBuffer[bTmp++]=0x80;
	while(bTmp % 8 != 0x00)
		bTempBuffer[bTmp++]=0x00;

	// create and add the signature of this buffer
	sm_create_signature(bSessionKey);

	// encrypt it to get omnikey proprietary data
	sm_create_okdata(bSessionKey);

	// check if LE is given
	// (CLA INS P1 P2 [LC] [DATA] [LE]) .. [] fields are optional
	// check if bSendLen > 4 checks if LC is available 
	// check if pbSend[4] (LC) + 5 (size of header) is less than bSendLen 
	if(bSendLen > 4 && (pbSend[4] + 5) < bSendLen)
	{
		// attach LE (the last byte)
		bSendBuffer[bSendBufferLen++]=pbSend[bSendLen-1];
	}

	// send to card/reader
	bRecvBufferLen=sizeof(bRecvBuffer);
	ulRecvBufferLen=bRecvBufferLen;
	rc = SCardCLICCTransmit(hCard,bSendBuffer,bSendBufferLen,bRecvBuffer,&ulRecvBufferLen);
	if(rc != SCARD_S_SUCCESS)
	{
		return rc; //SM_ERROR;
	}
	else
	{
		// check data
		bRecvBufferLen = (unsigned char)ulRecvBufferLen;

		rc = sm_check_data();
		if(rc == SM_SUCCESS)
		{
			// if more than 2 bytes returned
			// copy response data to buffer
			// because of the data structure
			// HDH RDH LC DATA PADDING SIGNATURE
			//  2   2   1  xx    xx      xx			// unsigned charS (xx means variable length)
			// copy starts at byte 5 (DATA) with length stored in byte 4 (LC)
			if(bRecvBufferLen > 2)
			{
				memcpy(pbReceive,&bTempBuffer[5],bTempBuffer[4]);
				*pbReceiveLen=bTempBuffer[4];
			} 

			// attach sw1sw2 which are the last 2 bytes in bRecvBuffer
			memcpy(&pbReceive[*pbReceiveLen],&bRecvBuffer[bRecvBufferLen-2],2);

			// return length (LC + sw1sw2)
			*pbReceiveLen=*pbReceiveLen+2;
		}
		else
		{
			return rc;
		}

	}

	return SM_SUCCESS;
}

/** @brief Transmit a wrong ok-data to the reader

    Perform a secure mode transmit but insert an error into the omnikey proprietary data. So the 
    errorcase can be checked.
    
    @param hCard        Cardhandle
    @param pbSend       Data to send down
    @param bSendLen     Length of data to be send down
    @param pbReceive    Databuffer for returned data
    @param pbReceiveLen Length of data returned in pbReceive
    
    @retval SM_SUCCESS  successfull
    @retval SCARD_*     some SCard-error
*/
unsigned long SecureModeTransmitWrongOKData(SCARDHANDLE hCard,
								    unsigned char * pbSend,
									unsigned char  bSendLen,
									unsigned char * pbReceive,
									unsigned char * pbReceiveLen)
{
	int rc = 0;
	unsigned long ulRecvBufferLen;
	unsigned char i, bByte=0x00;

	// clear all buffers
	memset(bSendBuffer,0x00,sizeof(bSendBuffer));
	memset(bRecvBuffer,0x00,sizeof(bRecvBuffer));
	memset(bTempBuffer,0x00,sizeof(bTempBuffer));
	*pbReceiveLen=0;

	// prepare send buffer
	bSendBufferLen=0x00;
	bSendBuffer[bSendBufferLen++]=pbSend[0]; // CLA
	bSendBuffer[bSendBufferLen++]=pbSend[1]; // INS
	bSendBuffer[bSendBufferLen++]=pbSend[2]; // P1
	bSendBuffer[bSendBufferLen++]=pbSend[3]; // P2
	
	// have to save HDH and RDH for comparison later
	bHDH[0]=GetRandomByte(); bHDH[1]=GetRandomByte();
	// invert last recevied RDH
	bRDH[0]=~bRDH[0]; bRDH[1]=~bRDH[1];

	// Prepare temporary buffer for encryption
	bTmp=0;

	bTempBuffer[bTmp++]=bHDH[0];
	bTempBuffer[bTmp++]=bHDH[1];
	
	bTempBuffer[bTmp++]=bRDH[0];
	bTempBuffer[bTmp++]=bRDH[1];

	// if the given command (pbSend) is more than 4 bytes long length + data have been given
	// copy the length and the data to bTempBuffer, else just say length is zero
	if(bSendLen > 4)
	{
		bTempBuffer[bTmp++]=pbSend[4]; // length of data
		// add data
		for(i=0;i < pbSend[4];i++)
		{
			bTempBuffer[bTmp++]=pbSend[i+5];
		}
	}
	else
		bTempBuffer[bTmp++]=0x00;

	// add padding
	bTempBuffer[bTmp++]=0x80;
	while(bTmp % 8 != 0x00)
		bTempBuffer[bTmp++]=0x00;

	// create and add the signature of this buffer
	sm_create_signature(bSessionKey);

		
	// encrypt it to get omnikey proprietary data
	sm_create_okdata(bSessionKey);

	// *************************************************************

	// change send buffer to get wrong okdata

	bByte=bSendBuffer[bSendBufferLen-6];
	bSendBuffer[bSendBufferLen-6]=bSendBuffer[bSendBufferLen-5];
	bSendBuffer[bSendBufferLen-5]=bByte;

	bByte=bSendBuffer[bSendBufferLen-4];
	bSendBuffer[bSendBufferLen-4]=bSendBuffer[bSendBufferLen-3];
	bSendBuffer[bSendBufferLen-3]=bByte;

	bByte=bSendBuffer[bSendBufferLen-2];
	bSendBuffer[bSendBufferLen-2]=bSendBuffer[bSendBufferLen-1];
	bSendBuffer[bSendBufferLen-1]=bByte;


	// *************************************************************

	// check if LE is given
	// (CLA INS P1 P2 [LC] [DATA] [LE]) .. [] fields are optional
	// check if bSendLen > 4 checks if LC is available 
	// check if pbSend[4] (LC) + 5 (size of header) is less than bSendLen 
	if(bSendLen > 4 && (pbSend[4] + 5) < bSendLen)
	{
		// attach LE (the last byte)
		bSendBuffer[bSendBufferLen++]=pbSend[bSendLen-1];
	}

	// send to card/reader
	bRecvBufferLen=sizeof(bRecvBuffer);
	ulRecvBufferLen=bRecvBufferLen;
	rc = SCardCLICCTransmit(hCard,bSendBuffer,bSendBufferLen,bRecvBuffer,&ulRecvBufferLen);
	if(rc != SCARD_S_SUCCESS)
	{
		return rc; //SM_ERROR;
	}
	else
	{
		// check data
		bRecvBufferLen = (unsigned char)ulRecvBufferLen;

		rc = sm_check_data();
		if(rc == SM_SUCCESS)
		{
			// if more than 2 bytes returned
			// copy response data to buffer
			// because of the data structure
			// HDH RDH LC DATA PADDING SIGNATURE
			//  2   2   1  xx    xx      xx			// unsigned charS (xx means variable length)
			// copy starts at byte 5 (DATA) with length stored in byte 4 (LC)
			if(bRecvBufferLen > 2)
			{
				memcpy(pbReceive,&bTempBuffer[5],bTempBuffer[4]);
				*pbReceiveLen=bTempBuffer[4];
			} 

			// attach sw1sw2 which are the last 2 bytes in bRecvBuffer
			memcpy(&pbReceive[*pbReceiveLen],&bRecvBuffer[bRecvBufferLen-2],2);

			// return length (LC + sw1sw2)
			*pbReceiveLen=*pbReceiveLen+2;
		}
		else
		{
			return rc;
		}

	}

	return SM_SUCCESS;
}
