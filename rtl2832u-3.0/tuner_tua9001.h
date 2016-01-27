#ifndef __TUNER_TUA9001_H
#define __TUNER_TUA9001_H

/**

@file

@brief   TUA9001 tuner module declaration

One can manipulate TUA9001 tuner through TUA9001 module.
TUA9001 module is derived from tunerd module.



@par Example:
@code

// The example is the same as the tuner example in tuner_base.h except the listed lines.



#include "tuner_tua9001.h"


...



s32 main(void)
{
	TUNER_MODULE         *pTuner;
	TUA9001_EXTRA_MODULE *pTunerExtra;

	TUNER_MODULE          TunerModuleMemory;
	BASE_INTERFACE_MODULE BaseInterfaceModuleMemory;
	I2C_BRIDGE_MODULE     I2cBridgeModuleMemory;

	s32 BandwidthMode;


	...



	// Build TUA9001 tuner module.
	BuildTua9001Module(
		&pTuner,
		&TunerModuleMemory,
		&BaseInterfaceModuleMemory,
		&I2cBridgeModuleMemory,
		0xc0								// I2C device address is 0xc0 in 8-bit format.
		);





	// Get TUA9001 tuner extra module.
	pTunerExtra = (T2266_EXTRA_MODULE *)(pTuner->pExtra);





	// ==== Initialize tuner and set its parameters =====

	...

	// Set TUA9001 bandwidth.
	pTunerExtra->SetBandwidthMode(pTuner, TUA9001_BANDWIDTH_6MHZ);





	// ==== Get tuner information =====

	...

	// Get TUA9001 bandwidth.
	pTunerExtra->GetBandwidthMode(pTuner, &BandwidthMode);





	// See the example for other tuner functions in tuner_base.h


	return 0;
}


@endcode

*/


#include "tuner_base.h"
//#include "i2c_rtl2832usb.h"





// The following context is source code provided by Infineon.





// Infineon source code - driver_tua9001.h



/* ============================================================================
** Copyright (C) 1997-2007 Infineon AG All rights reserved.
** ============================================================================
**
** ============================================================================
** Revision Information :
**    File name: driver_tua9001.h
**    Version: 
**    Date: 
**
** ============================================================================
** History: 
** 
** Date         Author  Comment
** ----------------------------------------------------------------------------
**
** 2007.11.06   Walter Pichler    created.
** ============================================================================
*/

 
/*============================================================================
 Named Constants Definitions
============================================================================*/

#define TUA9001_TUNER_OK                       0
#define TUA9001_TUNER_ERR                      0xff

#define TUA9001_H_LEVEL                        1
#define TUA9001_L_LEVEL                        0


/*============================================================================
 Types definition
============================================================================*/


typedef enum {
        TUA9001_TUNER_BANDWIDTH_8MHZ,
        TUA9001_TUNER_BANDWIDTH_7MHZ,
        TUA9001_TUNER_BANDWIDTH_6MHZ,
        TUA9001_TUNER_BANDWIDTH_5MHZ,
        } tua9001tunerDriverBW_t;


typedef enum {
        TUA9001_PLL_LOCKED,
        TUA9001_PLL_NOT_LOCKED
        }tua9001tunerPllLocked_t;


typedef enum {
        TUA9001_STANDBY,
        TUA9001_IDLE,
        TUA9001_RX
        } tua9001tunerReceiverState_t;


typedef enum {
        TUA9001_L_INPUT_ACTIVE,
        TUA9001_UHF_INPUT_ACTIVE,
        TUA9001_VHF_INPUT_ACTIVE
        } tua9001tunerActiveInput_t;

 

/*============================================================================
 Public functions
============================================================================*/

/**
 * tuner initialisation
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/
extern s32 initializeTua9001 (TUNER_MODULE *pTuner);


/**
 * tuner tune
 * @param i_freq   tuning frequency
 * @param i_bandwidth  channel  bandwidth
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/
extern s32 tuneTua9001 (TUNER_MODULE *pTuner, s64 i_freq, tua9001tunerDriverBW_t i_bandwidth);


/**
 * Get tuner state
 * @param o_tunerState tuner state
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/
extern s32 getReceiverStateTua9001 (TUNER_MODULE *pTuner, tua9001tunerReceiverState_t *o_tunerState);

/**
 * Get active input
 * @param o_activeInput active input info
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/
extern s32 getActiveInputTua9001 (TUNER_MODULE *pTuner, tua9001tunerActiveInput_t *o_activeInput);


/**
 * Get baseband gain value
 * @param o_basebandGain  baseband gain value
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/
extern s32 getBasebandGainTua9001 (TUNER_MODULE *pTuner, s8 *o_basebandGain);























// Infineon source code - driver_tua9001_NeededFunctions.h



/*========================================================================================================================
 additional needed external funtions ( have to  be provided by the user! )
========================================================================================================================*/

/**
 * set / reset tuner reset input
 * @param i_state   level
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/

s32 tua9001setRESETN (TUNER_MODULE *pTuner, u32 i_state);


/**
 * set / reset tuner receive enable input
 * @param i_state   level
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/

s32 tua9001setRXEN (TUNER_MODULE *pTuner, u32 i_state);


/**
 * set / reset tuner chiop enable input
 * @param i_state   level
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/

s32 tua9001setCEN (TUNER_MODULE *pTuner, u32 i_state);


/**
 * waitloop 
 * @param i_looptime   * 1uS
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/

s32 tua9001waitloop (TUNER_MODULE *pTuner, u32 i_looptime);


/**
 * i2cBusWrite 
 * @param deviceAdress    chip address 
 * @param registerAdress  register address 
 * @param *data           pointer to data source
 * @param length          number of bytes to transmit
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/

 s32 tua9001i2cBusWrite (TUNER_MODULE *pTuner, u8 deviceAddress, u8 registerAddress, s8 *data,
	 u32 length);


/**
 * i2cBusRead 
 * @param deviceAdress    chip address 
 * @param registerAdress  register address 
 * @param *data           pointer to data destination
 * @param length          number of bytes to read
 * @retval TUA9001_TUNER_OK No error
 * @retval TUA9001_TUNER_ERR Error
*/

 s32 tua9001i2cBusRead (TUNER_MODULE *pTuner, u8 deviceAddress, u8 registerAddress, s8 *data,
	 u32 length);

/*========================================================================================================================
 end of additional needed external funtions
========================================================================================================================*/























// The following context is TUA9001 tuner API source code





/**

@file

@brief   TUA9001 tuner module declaration

One can manipulate TUA9001 tuner through TUA9001 module.
TUA9001 module is derived from tuner module.

*/





// Definitions

// Constant
#define GPO_ADDR	0x1

// Bandwidth modes
enum TUA9001_BANDWIDTH_MODE
{
	TUA9001_BANDWIDTH_5MHZ = TUA9001_TUNER_BANDWIDTH_5MHZ,
	TUA9001_BANDWIDTH_6MHZ = TUA9001_TUNER_BANDWIDTH_6MHZ,
	TUA9001_BANDWIDTH_7MHZ = TUA9001_TUNER_BANDWIDTH_7MHZ,
	TUA9001_BANDWIDTH_8MHZ = TUA9001_TUNER_BANDWIDTH_8MHZ,
};

// Default value
#define TUA9001_RF_FREQ_HZ_DEFAULT			50000000;
#define TUA9001_BANDWIDTH_MODE_DEFAULT		TUA9001_BANDWIDTH_5MHZ;





// Builder
void
BuildTua9001Module(
	TUNER_MODULE **ppTuner,
	TUNER_MODULE *pTunerModuleMemory,
	BASE_INTERFACE_MODULE *pBaseInterfaceModuleMemory,
	I2C_BRIDGE_MODULE *pI2cBridgeModuleMemory,
	u8 DeviceAddr
	);





// Manipulaing functions
void
tua9001_GetTunerType(
	TUNER_MODULE *pTuner,
	s32 *pTunerType
	);

void
tua9001_GetDeviceAddr(
	TUNER_MODULE *pTuner,
	u8 *pDeviceAddr
	);

s32
tua9001_Initialize(
	TUNER_MODULE *pTuner
	);

s32
tua9001_SetRfFreqHz(
	TUNER_MODULE *pTuner,
	u64 RfFreqHz
	);

s32
tua9001_GetRfFreqHz(
	TUNER_MODULE *pTuner,
	u64 *pRfFreqHz
	);





// Extra manipulaing functions
s32
tua9001_SetBandwidthMode(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

s32
tua9001_GetBandwidthMode(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

s32
tua9001_GetRegBytesWithRegAddr(
	TUNER_MODULE *pTuner,
	u8 DeviceAddr,
	u8 RegAddr,
	u8 *pReadingBytes,
	u8 ByteNum
	);

s32
tua9001_SetSysRegByte(
	TUNER_MODULE *pTuner,
	u16 RegAddr,
	u8 WritingByte
	);

s32
tua9001_GetSysRegByte(
	TUNER_MODULE *pTuner,
	u16 RegAddr,
	u8 *pReadingByte
	);















#endif
