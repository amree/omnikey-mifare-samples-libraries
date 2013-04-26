/**
****************************************************************************** 
* @file
* @brief Functions for sm5x21 lib
*
*
****************************************************************************** 
* $HeadURL: file:///Z:/subversion/sw/cmsync/trunk/sm5x21lib/src/sm5x21.c $
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

// external headers
#include "winscard.h"

#define __SM5X21_C__

// internal headers
#include "des.h"
#include "sm5x21.h"
#include "sm5x21i.h"

#include "ok.h"
#include "scardcl.h"


/**
    @brief Function SecureModeInitSession
 
    Starts a secure mode session, begins a transaction and
    generates and stores the SessionKey
    
    @param hCard        SCARDHANDLE got from SCardConnect
    @param pbKey        Key (should be Kcur or Kcuw)
    @param bKeyLen      Length of pbKey
    @param bSessionType Type of Session (Read or Write)

    @retval SM_SUCCESS      0x00
    @retval SM_ERROR        0x01
    @retval SM_WRONG_HDH    0x02
    @retval SM_WRONG_SIG    0x03
    @retval SM_WRONG_LENGTH 0x04
*/
unsigned long SecureModeInitSession(SCARDHANDLE hCard,
							unsigned char *pbKey,
							unsigned char	bKeyLen,
							unsigned char	bSessionType)
{
	unsigned long rc;
	unsigned long ulRecvBufferLen;
	unsigned long sm_init_vars();
    int i;

	// start the transaction
	rc = SCardBeginTransaction(hCard);
	if(rc != SCARD_S_SUCCESS)
	{
		// handle error
		return SM_ERROR;
	}
	
	// prepare bSendBuffer

	bSendBufferLen=0;
	// manage Session APDU 84 72 00 00 18
	bSendBuffer[bSendBufferLen++]=0x84;
	bSendBuffer[bSendBufferLen++]=0x72;
	bSendBuffer[bSendBufferLen++]=0x00;
	if(bSessionType == SM_SESSION_WRITE)
		bSendBuffer[bSendBufferLen++]=0x01;
	else
		bSendBuffer[bSendBufferLen++]=0x00;
        
        
	// generate HDH, which is a random value;
	bHDH[0]=GetRandomByte();
	bHDH[1]=GetRandomByte();
    
	// set RDH to 0x0000 cause it doesn't matter which value it has
	bRDH[0]=0x00;
	bRDH[1]=0x00;
    
	// generate temporary buffer which will be encrypted.
	bTmp=0;
	
	bTempBuffer[bTmp++]=bHDH[0];
	bTempBuffer[bTmp++]=bHDH[1];
	bTempBuffer[bTmp++]=bRDH[0];
	bTempBuffer[bTmp++]=bRDH[1];
	
	// Add LC (Length of ins data)
	bTempBuffer[bTmp++]=0x08;
	
	// Add random generated 8 Byte
	for(i=0;i<8;i++)
	{
		// session key consists of 8 bytes random data and encrypted signature
		// store the random data part to the SessionKeyBuffer
		bSessionKey[i]=GetRandomByte();
		bTempBuffer[bTmp++]=bSessionKey[i];
	}
	
	// Add Padding, a single 0x80 ..
	bTempBuffer[bTmp++]=0x80;
	
	// .. and 0x00 till bTempBuffer is a multiple of 8
	while(bTmp % 8 != 0)
		bTempBuffer[bTmp++]=0x00;
	
	// create the signature from bTempBuffer
	sm_create_signature(pbKey);
    
	// attach the second part, the encrypted signature to the session key
	memcpy(&bSessionKey[8],&bTempBuffer[bTmp-8],8);
    
	// create omnikey proprietary data (3des encryption of bTempBuffer)
	// and add it to bSendBuffer
	sm_create_okdata(pbKey);
    
	// send prepared command
	bRecvBufferLen=sizeof(bRecvBuffer);
	ulRecvBufferLen=bRecvBufferLen;
	rc = SCardCLICCTransmit(hCard,bSendBuffer,bSendBufferLen,bRecvBuffer,&ulRecvBufferLen);
	if(rc != SCARD_S_SUCCESS)
	{
		// handle ERROR
		
		return SM_ERROR;
	}
	else
	{
		// check returned data
		bRecvBufferLen=(unsigned char)ulRecvBufferLen;

		rc = sm_check_data();

		return rc;
	}
}

/**
    @brief Close the secure mode session
 
    Closes a secure mode session, destroys the session key.
    
    @param hCard       SCARDHANDLE got from SCardConnect
    
    @retval SM_SUCCESS      0x00
    @retval SM_ERROR        0x01
    @retval SM_WRONG_HDH    0x02
    @retval SM_WRONG_SIG    0x03
    @retval SM_WRONG_LENGTH 0x04
*/
unsigned long SecureModeCloseSession(SCARDHANDLE hCard)
{
	unsigned long rc;
	unsigned long ulRecvBufferLen;

	// end Session command
	// size is always 16 bytes (0x10) because there is no data and 
	// hdh (2) + rdh (2) + lc (1) + padding (3, to reach a multiple of 8) 
	// + signature (8) are 16 bytes
	bSendBufferLen=4;
	memcpy(bSendBuffer,"\x84\x72\x01\x00",bSendBufferLen);
	
		
	// generate random HDH
	bHDH[0]=GetRandomByte(); bHDH[1]=GetRandomByte();
	// Invert RDH for next command
	bRDH[0]=~bRDH[0]; bRDH[1]=~bRDH[1];

	// prepare bTempBuffer
	bTmp=0;

	bTempBuffer[bTmp++]=bHDH[0]; 
	bTempBuffer[bTmp++]=bHDH[1];
	bTempBuffer[bTmp++]=bRDH[0];
	bTempBuffer[bTmp++]=bRDH[1];
	bTempBuffer[bTmp++]=0x00; // lc
	bTempBuffer[bTmp++]=0x80; // padding
	while(bTmp % 8 != 0)
		bTempBuffer[bTmp++]=0x00;

	// create the signature
	sm_create_signature(bSessionKey);

	// encrypt to omnikey proprietary data
	sm_create_okdata(bSessionKey);

	// send command
	bRecvBufferLen=sizeof(bRecvBuffer); 
	ulRecvBufferLen=bRecvBufferLen;
	rc = SCardCLICCTransmit(hCard,bSendBuffer,bSendBufferLen,bRecvBuffer,&ulRecvBufferLen);
	if(rc != SCARD_S_SUCCESS)
	{
		// error
		rc = SM_ERROR;
	}
	else
	{
		// success
		bRecvBufferLen = (unsigned char)ulRecvBufferLen;

		if(bRecvBuffer[bRecvBufferLen-2] == 0x69 && bRecvBuffer[bRecvBufferLen-1] == 0x82)
			return SM_ERROR;

		// check return data..
		rc = sm_check_data();
		if(rc == SM_SUCCESS)
		{
			// do anything if close session hasn't been successful
		}
	}

	rc = SCardEndTransaction(hCard,SCARD_LEAVE_CARD);
	if(rc != SCARD_S_SUCCESS)
	{
		rc = SM_ERROR;
	}
    else
        rc = SM_SUCCESS;

	// clear bSessionKey
	memset(bSessionKey,0x00,sizeof(bSessionKey));

	return rc;
}

/**
    @brief Transmit secured data to the reader
 
    this function prepares the command to match omnikey format for secure mode
    and send this down to the reader, receive the response and extract data from
    returned omnikey proprietary format.
    
    @param hCard        SCARDHANDLE got from SCardConnect
    @param pbSend       Data to send down
    @param bSendLen     Length of data to be send down
    @param pbReceive    Databuffer for returned data
    @param pbReceiveLen Length of data returned in pbReceiv
    
    @retval SM_SUCCESS      0x00
    @retval SM_ERROR        0x01
    @retval SM_WRONG_HDH    0x02
    @retval SM_WRONG_SIG    0x03
    @retval SM_WRONG_LENGTH 0x04
*/ 
unsigned long SecureModeTransmit(SCARDHANDLE hCard,
						 unsigned char * pbSend,
						 unsigned char	bSendLen,
						 unsigned char * pbReceive,
						 unsigned char *	pbReceiveLen)
{
	int rc = SM_ERROR;
	unsigned long ulRecvBufferLen;
    unsigned char i;

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
		for(i=0;i < pbSend[4] && (i+5)<bSendLen;i++)
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
		return SM_ERROR;
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

/**
    @brief Return a random value.
 
    @return random value 0x00 to 0xFF
*/  
unsigned char GetRandomByte()
{
	return (rand() % 256);
}

/**
    @brief Create a signature
 
    This function create a signature with data stored in bTempBuffer
    and pbKey, then it attaches the last 8 bytes of the encrypted 
    bTempBuffer as signature to the bTempBuffer.
    
    @param pbKey    Key to use for encryption
*/  
void sm_create_signature(unsigned char * pbKey)
{
	// allocate buffer
	bOutTempBuffer = (unsigned char *)malloc(sizeof(unsigned char)*bTmp);
	iOutTmp=bTmp;

	// encrypt this with the first 8 bytes of pbKey
	encrypt_des(pbKey,bTempBuffer,bTmp,&bOutTempBuffer,&iOutTmp);

	// attach encrypted signature to buffer
	memcpy(&bTempBuffer[bTmp],&bOutTempBuffer[iOutTmp-8],8);
	bTmp+=8;

	// free allocated memory
	free(bOutTempBuffer);
}

/**
    @brief Create the omnikey proprietary data
 
    This function create the omnikey proprietary datagram using pbKey
    and data stored in bTempBuffer. Then it attaches this 3des encrypted
    data to the sendbuffer.
   
    @param pbKey    Key to use for encryption
*/  
void sm_create_okdata(unsigned char * pbKey)
{
	// reallocate buffer	
	bOutTempBuffer = (unsigned char *)malloc(sizeof(unsigned char)*bTmp);
	iOutTmp=bTmp;

	// encrypt whole buffer to get omnikey proprietary data
	encrypt_3des(pbKey,bTempBuffer,bTmp,&bOutTempBuffer,&iOutTmp);

	// add length of data
	bSendBuffer[bSendBufferLen++]=iOutTmp;

	// attach this data to the send buffer
	memcpy(&bSendBuffer[5],bOutTempBuffer,iOutTmp);
	bSendBufferLen+=iOutTmp;

	// free allocated memory
	free(bOutTempBuffer);
}

/**
    @brief Decrypt the omnikey proprietary data
 
    This function decrypt the response data which came from card/reader and 
    put it into bTempBuffer, it do not copy sw1sw2, they remain in bRecvBuffer for 
    later use. It also stores received RDH for further communication.
*/  
void sm_decrypt_okdata()
{
	// allocate buffer
	bOutTempBuffer = (unsigned char *)malloc(sizeof(unsigned char)*(bRecvBufferLen-2));
	iOutTmp=bRecvBufferLen-2;

	// decrypt returned data
	decrypt_3des(bSessionKey,bRecvBuffer,bRecvBufferLen-2,&bOutTempBuffer,&iOutTmp);

	// copy whole decrypted data to bTempBuffer
	memcpy(bTempBuffer,bOutTempBuffer,iOutTmp);
	bTmp=iOutTmp;

	// save returned RDH
	bRDH[0]=bTempBuffer[2];
	bRDH[1]=bTempBuffer[3];

	// free allocated memory
	free(bOutTempBuffer);
}

/**
    @brief Checks the signature of the received data
 
    In this function the signature is recalculated from received data
    and compared with the received signature.
    
    @retval SM_SUCCESS      successfull
    @retval SM_WRONG_SIG    wrong signature received
*/  
unsigned long sm_check_signature()
{
	unsigned long rc = 0;

	// reallocate buffer
	bOutTempBuffer = (unsigned char *)malloc(sizeof(unsigned char)*(bTmp-8));
	iOutTmp=(bTmp-8);

	// encrypt first part of the decrypted response to get the signature
	encrypt_des(bSessionKey,bTempBuffer,iOutTmp,&bOutTempBuffer,&iOutTmp);

	// compare both signatures
	// compare last 8 bytes of decrypted bTempBuffer, and last 8 bytes of recalculated signature
	if(memcmp(&bTempBuffer[bTmp-8],&bOutTempBuffer[iOutTmp-8],8) == 0)
	{
		// signature valid
		rc = SM_SUCCESS;
	}
	else
	{
		// signature invalid
		rc = SM_WRONG_SIG;
	}
	
	// free allocted memory
	free(bOutTempBuffer);

	return rc;
}


/**
    @brief Checks the hdh of the received data
 
    This function is used to check the received HDH with the sent one.
    HDH should be inverted by the reader and sent back this way.
    
    @retval SM_SUCCESS      successfull
    @retval SM_WRONG_HDH    wrong HDH received
*/  
unsigned long sm_check_hdh()
{
	// compare sent and received HDH, have to be inverted from reader
	// casting to unsigned char is necessary, because the ~ operator returns an 4 Byte value
	if(bTempBuffer[0] == (unsigned char)~bHDH[0] && bTempBuffer[1] == (unsigned char)~bHDH[1])
	{
		// header valid
		return SM_SUCCESS;
	}
	else
	{
		// hdh returned WRONG
		return SM_WRONG_HDH;
	}
}

/**
    @brief Checks the received data
 
    This function is used to check the received data. It decrypts it, checks the signature
    and checks the hdh.
    
    @retval SM_SUCCESS      successfull
    @retval SM_WRONG_HDH    wrong HDH received
    @retval SM_WRONG_SIG    wrong signature received
*/  
unsigned long sm_check_data()
{
	unsigned long rc=0;

	// if less than 2 bytes received just break
	// sw1sw2 have to be present
	if(bRecvBufferLen < 2)
		return SM_ERROR;

	// check if more than 2 bytes have been received, ignore sw1sw2
	if( bRecvBufferLen > 2 )
	{

		// decrypt omnikey proprietary data
		sm_decrypt_okdata();

		// check signature
		rc = sm_check_signature();

		if(rc == SM_SUCCESS)
		{			
			// signature is valid
			
			// check returned header
			rc = sm_check_hdh();
			if(rc == SM_SUCCESS)
			{
				// header valid

				return SM_SUCCESS;
			}
			else
			{
				// received header is wrong
				return SM_WRONG_HDH;
			}
		}
		else
		{
			// signature wrong
			return SM_WRONG_SIG;
		}
	}

	return SM_SUCCESS;
}

/**
    @brief Initialise the variables
 
    @return SM_SUCCESS
*/
unsigned long sm_init_vars()
{
	memset(bSessionKey,0x00,16);

	memset(bSendBuffer,0x00,MAX_BUFFER_SIZE);
	bSendBufferLen=MAX_BUFFER_SIZE;

	memset(bRecvBuffer,0x00,MAX_BUFFER_SIZE);
	bRecvBufferLen = MAX_BUFFER_SIZE;

	memset(bHDH,0x00,2);
	memset(bRDH,0x00,2);

	memset(bTempBuffer,0x00,MAX_BUFFER_SIZE);
 
    return SM_SUCCESS;
}
