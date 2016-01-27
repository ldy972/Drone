#ifndef __TUNER_FC0013_H
#define __TUNER_FC0013_H

/**

@file

@brief   FC0013 tuner module declaration

One can manipulate FC0013 tuner through FC0013 module.
FC0013 module is derived from tuner module.



@par Example:
@code

// The example is the same as the tuner example in tuner_base.h except the listed lines.



#include "tuner_fc0013.h"


...



s32 main(void)
{
	TUNER_MODULE        *pTuner;
	FC0013_EXTRA_MODULE *pTunerExtra;

	TUNER_MODULE          TunerModuleMemory;
	BASE_INTERFACE_MODULE BaseInterfaceModuleMemory;
	I2C_BRIDGE_MODULE     I2cBridgeModuleMemory;

	u64 BandwidthMode;


	...



	// Build FC0013 tuner module.
	BuildFc0013Module(
		&pTuner,
		&TunerModuleMemory,
		&BaseInterfaceModuleMemory,
		&I2cBridgeModuleMemory,
		0xc6,								// I2C device address is 0xc6 in 8-bit format.
		CRYSTAL_FREQ_36000000HZ				// Crystal frequency is 36.0 MHz.
		);





	// Get FC0013 tuner extra module.
	pTunerExtra = &(pTuner->Extra.Fc0013);





	// ==== Initialize tuner and set its parameters =====

	...

	// Set FC0013 bandwidth.
	pTunerExtra->SetBandwidthMode(pTuner, FC0013_BANDWIDTH_6MHZ);





	// ==== Get tuner information =====

	...

	// Get FC0013 bandwidth.
	pTunerExtra->GetBandwidthMode(pTuner, &BandwidthMode);



	// See the example for other tuner functions in tuner_base.h


	return 0;
}


@endcode

*/





#include "tuner_base.h"





// The following context is implemented for FC0013 source code.


// Definitions
enum FC0013_TRUE_FALSE_STATUS
{
	FC0013_FALSE,
	FC0013_TRUE,
};


enum FC0013_I2C_STATUS
{
	FC0013_I2C_SUCCESS,
	FC0013_I2C_ERROR,
};


enum FC0013_FUNCTION_STATUS
{
	FC0013_FUNCTION_SUCCESS,
	FC0013_FUNCTION_ERROR,
};



// Functions
s32 FC0013_Read(TUNER_MODULE *pTuner, u8 RegAddr, u8 *pByte);
s32 FC0013_Write(TUNER_MODULE *pTuner, u8 RegAddr, u8 Byte);

s32
fc0013_SetRegMaskBits(
	TUNER_MODULE *pTuner,
	u8 RegAddr,
	u8 Msb,
	u8 Lsb,
	const u8 WritingValue
	);

s32
fc0013_GetRegMaskBits(
	TUNER_MODULE *pTuner,
	u8 RegAddr,
	u8 Msb,
	u8 Lsb,
	u8 *pReadingValue
	);

s32 FC0013_Open(TUNER_MODULE *pTuner);
s32 FC0013_SetFrequency(TUNER_MODULE *pTuner, u64 Frequency, u16 Bandwidth);

// Set VHF Track depends on input frequency
s32 FC0013_SetVhfTrack(TUNER_MODULE *pTuner, u64 Frequency);



























// The following context is FC0013 tuner API source code





// Definitions

// Bandwidth mode
enum FC0013_BANDWIDTH_MODE
{
	FC0013_BANDWIDTH_6000000HZ = 6,
	FC0013_BANDWIDTH_7000000HZ = 7,
	FC0013_BANDWIDTH_8000000HZ = 8,
};


// Default for initialing
#define FC0013_RF_FREQ_HZ_DEFAULT			50000000
#define FC0013_BANDWIDTH_MODE_DEFAULT		FC0013_BANDWIDTH_8000000HZ


// Tuner LNA
enum FC0013_LNA_GAIN_VALUE
{
	FC0013_LNA_GAIN_LOW     = 0x00,	// -6.3dB
	FC0013_LNA_GAIN_MIDDLE  = 0x08,	//  7.1dB
	FC0013_LNA_GAIN_HIGH_17 = 0x11,	// 19.1dB
	FC0013_LNA_GAIN_HIGH_19 = 0x10,	// 19.7dB
};





// Builder
void
BuildFc0013Module(
	TUNER_MODULE **ppTuner,
	TUNER_MODULE *pTunerModuleMemory,
	BASE_INTERFACE_MODULE *pBaseInterfaceModuleMemory,
	I2C_BRIDGE_MODULE *pI2cBridgeModuleMemory,
	u8 DeviceAddr,
	u64 CrystalFreqHz
	);





// Manipulaing functions
void
fc0013_GetTunerType(
	TUNER_MODULE *pTuner,
	s32 *pTunerType
	);

void
fc0013_GetDeviceAddr(
	TUNER_MODULE *pTuner,
	u8 *pDeviceAddr
	);

s32
fc0013_Initialize(
	TUNER_MODULE *pTuner
	);

s32
fc0013_SetRfFreqHz(
	TUNER_MODULE *pTuner,
	u64 RfFreqHz
	);

s32
fc0013_GetRfFreqHz(
	TUNER_MODULE *pTuner,
	u64 *pRfFreqHz
	);





// Extra manipulaing functions
s32
fc0013_SetBandwidthMode(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

s32
fc0013_GetBandwidthMode(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

s32
fc0013_RcCalReset(
	TUNER_MODULE *pTuner
	);

s32
fc0013_RcCalAdd(
	TUNER_MODULE *pTuner,
	s32 RcValue
	);













#endif
