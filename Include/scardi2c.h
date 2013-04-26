/*****************************************************************************
@doc
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/cmsync/sw/scardi2c/rcs/scardi2c.h $
* $Revision: 2 $
*-----------------------------------------------------------------------------
* $Author: tb $

note:
   This file has to be included after the #include <pcsc_cm.h>
*-----------------------------------------------------------------------------
* History: see EOF
*----------------------------------------------------------------------------
* Copyright (c) 2000 - 2006 OMNIKEY
*****************************************************************************/

#ifndef _INC_SCARD_I2C
   #define _INC_SCARD_I2C

   #include <windows.h>
   #ifndef S_WNT
      #define S_WNT
   #endif
   #include <ok.h>

// All structures and unions are aligned with 1.
// The initila pack value is saved in old_value, it will be restore with pop below.
#pragma pack(push,old_value,1)

// DEFINE card types: the constants below are according the i2c card type used
typedef enum _SCARD_I2C_TYPE
   {
   NO_PREDEFINED_CARD_PARAMETERS = 0,
   // I2C cards from ST-Microelectronics:
   ST14C02C,
   ST14C04C,
   ST14E32,
   M14C04,
   M14C16,
   M14C32,
   M14C64,
   M14128,
   M14256,
   // I2C cards from GEMplus:
   GFM2K,
   GFM4K,
   GFM32K,
   // I2C cards from Atmel:
   AT24C01A,
   AT24C02,
   AT24C04,
   AT24C08,
   AT24C16,
   AT24C164,
   AT24C32,
   AT24C64,
   AT24C128,
   AT24C256,
   AT24CS128,
   AT24CS256,
   AT24C512,
   AT24C1024,
   I2C_TYPE_ENUM_TAIL          // must always be the last entry in this enum!!
   } SCARD_I2C_TYPE, *PSCARD_I2C_TYPE;



typedef struct _SCARD_I2C_CARD_PARAMETERS
   {
   UCHAR    ucPageSize;										// @field | Maximal number of bytes that can be written in a successive manner, in a single device select phase.
  	UCHAR 	ucNumberOfAddressBytes;	               // @field | Number of bytes used to address the memory in the I2C card.
  	ULONG 	ulMemorySize;							      // @field | The size of the e2prom allocated in the card
   }
SCARD_I2C_CARD_PARAMETERS, *PSCARD_I2C_CARD_PARAMETERS;
#define SCARD_I2C_CARD_PARAMETERS_SIZE             sizeof(SCARD_I2C_CARD_PARAMETERS)


// the order in the following table has to be according above enum field
static const SCARD_I2C_CARD_PARAMETERS   stI2cCardParameterTable[] =
{
   // ucPageSize, ucNumberOfAddressBytes, ulMemorySize

   {   0,   0,     0},     // NO_PREDEFINED_CARD_PARAMETERS = 0, values of this entry doesn't care
   // I2C cards from ST-Microelectronics:
   {   8,   1,   256},     // ST14C02C
   {   8,   1,   512},     // ST14C04C
   {  32,   2,  4096},     // ST14E32
   {  16,   1,   512},     // M14C04
   {  16,   1,  2048},     // M14C16
   {  32,   2,  4096},     // M14C32
   {  32,   2,  8192},     // M14C64
   {  64,   2, 16384},     // M14128
   {  64,   2, 32768},     // M14256
   // I2C cards from GEMplus:
   {   8,   1,   256},     // GFM2K
   {  16,   1,   512},     // GFM4K
   {  32,   2,  4096},     // GFM32K
   // I2C cards from Atmel:
   {   8,   1,   128},     // AT24C01A
   {   8,   1,   256},     // AT24C02
   {  16,   1,   512},     // AT24C04
   {  16,   1,  1024},     // AT24C08
   {  16,   1,  2048},     // AT24C16
   {  16,   1,  2048},     // AT24C164
   {  32,   2,  4096},     // AT24C32
   {  32,   2,  8192},     // AT24C64
   {  64,   2, 16384},     // AT24C128
   {  64,   2, 32768},     // AT24C256
   {  64,   2, 16384},     // AT24CS128
   {  64,   2, 32768},     // AT24CS256
   { 128,   2, 65536},     // AT24C512
   {   0,   2, 131072}     // AT24C1024 , page size = 0 means 256 bytes
};

// Supported are max 2 byte address
//#define SCARDI2C_MAX_DATA_LEN                65536
#define SCARDI2C_MAX_DATA_LEN          131072


   #ifdef __cplusplus
extern "C" {
   #endif
   // The structure below describes the capabilites of card the application is going to use.
   // Is is also used to configure the driver for the correspondig I2C-bus communication
   // where the following assumptions are made:
   // ucNumberOfAddressBytes:    for 1 or 2 bytes for memory address
   //
   // ulMemorySize:        EEPROM size in bytes(also max possible memory address)
   // 					  	if (ucNumberOfAddressBytes==1) then:
   // 					   		- the max. alowed value would be 8*256 =2048(only 3 bits) are available in the slave(device) address;
   //					   			- if the memory size is between (256,2048] - the most significant bits of the memory address reside in
   //					   				lsb of the slave(device) address.
   //					   			- error is returned when memory size > 2048.
   //
   //					   		if (ucNumberOfAddressBytes==2) then
   // 					   		    - no memory address bits are shifted in the 3 LSBits of the slave(device) address.
   //					   			- error is returned when the defined memory size <= 2048.
   //											
   // bWirteControlOnC2:   Protect is possible for the entire contents of EEPROM and WC signal appears on C2 cards contact.
   // 							For ST1404 it is PRE (protect enable).In this case is up to the application to init
   // 								the "protect flag" (b2) of the "block address pointer" at address 0x1FF
   //
   //						If (bWirteControlOnC2 == ON)
   //						   the WC is set to 0 (enable) before a write operation and set to 1(disabled) after the write operation.
   //						   For read	operations it is always disabled.
   //
   //						If (bWirteControlOnC2 == OFF)   		
   //						 	WC is constantly 0

   /* TB010302
   Fuer den Type wird eine Reihe von Konstanten zur Verfuegung gestellt (zb: STX40C02).
   Der Applikationsprogrammierer kann entweder den Type angeben (wenn er ihn weiss)
   oder die CARD_CAPABILITIES Struktur anfuellen. Wenn er beides angibt, hat der Typ Vorrang.
   */
OKERR ENTRY SCardI2CInit(
                        IN SCARDHANDLE	 		   ulHandleCard,
                        IN SCARD_I2C_CARD_PARAMETERS  *pCardParameters,
                        IN SCARD_I2C_TYPE              Type);            // Type has a priority, if NULL then pCardParameters will be considered


OKERR ENTRY SCardI2CReadData(
									IN SCARDHANDLE   ulHandleCard,          // Handle is ULONG
                           BYTE    *pbReadBuffer,                         // ptr to a buffer where the read data are to be stored
                           ULONG    ulReadBufferSize,
                        	ULONG    ulAddress,   	                        // memory address to read from
                        	ULONG    ulBytesToRead);

OKERR ENTRY SCardI2CWriteData(
									IN SCARDHANDLE   ulHandleCard,
                           BYTE     *pbWriteBuffer,
                           ULONG    ulWriteBufferSize,
                        	ULONG    ulAddress,   	
                        	ULONG    ulBytesToWrite);

#ifdef __cplusplus
}
#endif

#pragma pack(pop,old_value)
// Restóre the old packing value.

#endif  /* _INC_SCARD_I2C */


/*****************************************************************************
* History:
* $Log: scardi2c.h $
* Revision 1.9  2006/02/16 12:20:22  TBruendl
* No comment given
*
* Revision 1.8  2005/06/10 08:49:21  TBruendl
* No comment given
*
* Revision 1.7  2004/06/15 08:41:18  TBruendl
* No comment given
*
* Revision 1.6  2001/08/07 11:24:36  TBruendl
* #pragma for structure packing 1 added
*
* Revision 1.5  2001/08/06 14:24:15  TBruendl
* No comment given
*
* Revision 1.4  2001/04/04 11:18:03  CHintersteiner
* No comment given
*
* Revision 1.3  2001/04/04 07:00:45  CHintersteiner
* No comment given
*
* Revision 1.2  2001/03/26 12:45:49  MPetkov
* No comment given
*
* Revision 1.1  2001/02/20 09:26:35  MPetkov
* No comment given
*
* Revision 1.4  2001/01/26 12:39:45  TBruendl
* No comment given
*
* Revision 1.3  2000/11/16 09:33:46  TBruendl
* No comment given
*
*
******************************************************************************/

