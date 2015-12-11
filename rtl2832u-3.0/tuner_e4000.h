#ifndef __TUNER_E4000_H
#define __TUNER_E4000_H

/**

@file

@brief   E4000 tuner module declaration

One can manipulate E4000 tuner through E4000 module.
E4000 module is derived from tuner module.



@par Example:
@code

// The example is the same as the tuner example in tuner_base.h except the listed lines.



#include "tuner_e4000.h"


...



s32 main(void)
{
	TUNER_MODULE        *pTuner;
	E4000_EXTRA_MODULE *pTunerExtra;

	TUNER_MODULE          TunerModuleMemory;
	BASE_INTERFACE_MODULE BaseInterfaceModuleMemory;
	I2C_BRIDGE_MODULE     I2cBridgeModuleMemory;

	u64 BandwidthMode;


	...



	// Build E4000 tuner module.
	BuildE4000Module(
		&pTuner,
		&TunerModuleMemory,
		&BaseInterfaceModuleMemory,
		&I2cBridgeModuleMemory,
		0xac,								// I2C device address is 0xac in 8-bit format.
		CRYSTAL_FREQ_16384000HZ,			// Crystal frequency is 16.384 MHz.
		E4000_AGC_INTERNAL					// The E4000 AGC mode is internal AGC mode.
		);





	// Get E4000 tuner extra module.
	pTunerExtra = (T2266_EXTRA_MODULE *)(pTuner->pExtra);





	// ==== Initialize tuner and set its parameters =====

	...

	// Set E4000 bandwidth.
	pTunerExtra->SetBandwidthMode(pTuner, E4000_BANDWIDTH_6MHZ);





	// ==== Get tuner information =====

	...

	// Get E4000 bandwidth.
	pTunerExtra->GetBandwidthMode(pTuner, &BandwidthMode);



	// See the example for other tuner functions in tuner_base.h


	return 0;
}


@endcode

*/





#include "tuner_base.h"





// The following context is implemented for E4000 source code.


// Definition (implemeted for E4000)
#define E4000_1_SUCCESS			1
#define E4000_1_FAIL			0
#define E4000_I2C_SUCCESS		1
#define E4000_I2C_FAIL			0



// Function (implemeted for E4000)
s32
I2CReadByte(
	TUNER_MODULE *pTuner,
	u8 NoUse,
	u8 RegAddr,
	u8 *pReadingByte
	);

s32
I2CWriteByte(
	TUNER_MODULE *pTuner,
	u8 NoUse,
	u8 RegAddr,
	u8 WritingByte
	);

s32
I2CWriteArray(
	TUNER_MODULE *pTuner,
	u8 NoUse,
	u8 RegStartAddr,
	u8 ByteNum,
	u8 *pWritingBytes
	);



// Functions (from E4000 source code)
s32 tunerreset (TUNER_MODULE *pTuner);
s32 Tunerclock(TUNER_MODULE *pTuner);
s32 Qpeak(TUNER_MODULE *pTuner);
s32 DCoffloop(TUNER_MODULE *pTuner);
s32 GainControlinit(TUNER_MODULE *pTuner);

s32 Gainmanual(TUNER_MODULE *pTuner);
s32 E4000_gain_freq(TUNER_MODULE *pTuner, s32 frequency);
s32 PLL(TUNER_MODULE *pTuner, s32 Ref_clk, s32 Freq);
s32 LNAfilter(TUNER_MODULE *pTuner, s32 Freq);
s32 IFfilter(TUNER_MODULE *pTuner, s32 bandwidth, s32 Ref_clk);
s32 freqband(TUNER_MODULE *pTuner, s32 Freq);
s32 DCoffLUT(TUNER_MODULE *pTuner);
s32 GainControlauto(TUNER_MODULE *pTuner);

s32 E4000_sensitivity(TUNER_MODULE *pTuner, s32 Freq, s32 bandwidth);
s32 E4000_linearity(TUNER_MODULE *pTuner, s32 Freq, s32 bandwidth);
s32 E4000_high_linearity(TUNER_MODULE *pTuner);
s32 E4000_nominal(TUNER_MODULE *pTuner, s32 Freq, s32 bandwidth);



























// The following context is E4000 tuner API source code





// Definitions

// Bandwidth in Hz
enum E4000_BANDWIDTH_HZ
{
	E4000_BANDWIDTH_6000000HZ = 6000000,
	E4000_BANDWIDTH_7000000HZ = 7000000,
	E4000_BANDWIDTH_8000000HZ = 8000000,
};





// Builder
void
BuildE4000Module(
	TUNER_MODULE **ppTuner,
	TUNER_MODULE *pTunerModuleMemory,
	BASE_INTERFACE_MODULE *pBaseInterfaceModuleMemory,
	I2C_BRIDGE_MODULE *pI2cBridgeModuleMemory,
	u8 DeviceAddr,
	u64 CrystalFreqHz
	);





// Manipulaing functions
void
e4000_GetTunerType(
	TUNER_MODULE *pTuner,
	s32 *pTunerType
	);

void
e4000_GetDeviceAddr(
	TUNER_MODULE *pTuner,
	u8 *pDeviceAddr
	);

s32
e4000_Initialize(
	TUNER_MODULE *pTuner
	);

s32
e4000_SetRfFreqHz(
	TUNER_MODULE *pTuner,
	u64 RfFreqHz
	);

s32
e4000_GetRfFreqHz(
	TUNER_MODULE *pTuner,
	u64 *pRfFreqHz
	);





// Extra manipulaing functions
s32
e4000_GetRegByte(
	TUNER_MODULE *pTuner,
	u8 RegAddr,
	u8 *pReadingByte
	);

s32
e4000_SetBandwidthHz(
	TUNER_MODULE *pTuner,
	u64 BandwidthHz
	);

s32
e4000_GetBandwidthHz(
	TUNER_MODULE *pTuner,
	u64 *pBandwidthHz
	);













#endif
