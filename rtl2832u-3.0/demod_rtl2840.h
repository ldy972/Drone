#ifndef __DEMOD_RTL2840_H
#define __DEMOD_RTL2840_H

/**

@file

@brief   RTL2840 QAM demod module declaration

One can manipulate RTL2840 QAM demod through RTL2840 module.
RTL2840 module is derived from QAM demod module.



@par Example:
@code

// The example is the same as the QAM demod example in qam_demod_base.h except the listed lines.



#include "demod_rtl2840.h"


...



s32 main(void)
{
	QAM_DEMOD_MODULE *pDemod;

	QAM_DEMOD_MODULE      QamDemodModuleMemory;
	BASE_INTERFACE_MODULE BaseInterfaceModuleMemory;
	I2C_BRIDGE_MODULE     I2cBridgeModuleMemory;


	...



	// Build RTL2840 demod module.
	BuildRtl2840Module(
		&pDemod,
		&QamDemodModuleMemory,
		&BaseInterfaceModuleMemory,
		&I2cBridgeModuleMemory,
		0x44,								// I2C device address is 0x44 in 8-bit format.
		CRYSTAL_FREQ_28800000HZ,			// Crystal frequency is 28.8 MHz.
		TS_INTERFACE_SERIAL,				// TS interface mode is serial.
		QAM_DEMOD_EN_AM_HUM					// Enhancement mode is AM-hum.
		);



	// See the example for other QAM demod functions in qam_demod_base.h

	...


	return 0;
}


@endcode

*/


#include "qam_demod_base.h"





// Definitions
#define RTL2840_BASE_REG_TABLE_LEN				88
#define RTL2840_MONITOR_REG_TABLE_LEN			7

#define RTL2840_PAGE_REG_ADDR					0x0
#define RTL2840_SYS_VERSION_VALUE				0xa3



// Specific register
#define RTL2840_SPEC_REG_0_VAL_START_ADDR		0x5e



// Initialization
#define RTL2840_SPEC_MONITOR_INIT_0_COMPARISON_TIMES		30

// RF_AGC_VALUE register
#define RTL2840_RF_AGC_VALUE_BIT_NUM		11

// IF_AGC_VALUE register
#define RTL2840_IF_AGC_VALUE_BIT_NUM		11

// CR_OFFSET register
#define RTL2840_CR_OFFSET_BIT_NUM			32

// TR_OFFSET register
#define RTL2840_TR_OFFSET_BIT_NUM			31



// BER and UPER
#define RTL2840_BER_WAIT_TIME_MS			10
#define RTL2840_BER_REG2_MSB_SHIFT			16

// SNR
// Note: RTL2840_SNR_DB_DEN = round(log2(10) * pow(2, RTL2840_SNR_FRAC_BIT_NUM))
#define RTL2840_SNR_FRAC_BIT_NUM			7
#define RTL2840_SNR_DB_DEN					425



// Singal strength and signal quality
#define RTL2840_SIGNAL_QUALITY_FRAC_BIT_NUM			7





// Table length
#define RTL2840_SPEC_REG_0_VALUE_TABLE_LEN						11
#define RTL2840_SYMBOL_RATE_VALUE_TABLE_LEN						9

#define RTL2840_INIT_REG_TABLE_LEN								45
#define RTL2840_INIT_SPEC_REG_0_TABLE_LEN						13
#define RTL2840_TS_INTERFACE_INIT_TABLE_LEN						3

#define RTL2840_QAM_MODE_REG_TABLE_LEN							25
#define RTL2840_QAM_MODE_SPEC_REG_0_TABLE_LEN					3

#define RTL2840_ALPHA_VALUE_TABLE_LEN							16

#define RTL2840_SYMBOL_RATE_TABLE_LEN							3





// Builder
void
BuildRtl2840Module(
	QAM_DEMOD_MODULE **ppDemod,
	QAM_DEMOD_MODULE *pQamDemodModuleMemory,
	BASE_INTERFACE_MODULE *pBaseInterfaceModuleMemory,
	I2C_BRIDGE_MODULE *pI2cBridgeModuleMemory,
	u8 DeviceAddr,
	u64 CrystalFreqHz,
	s32 TsInterfaceMode,
	s32 EnhancementMode
	);





// Manipulaing functions
void
rtl2840_IsConnectedToI2c(
	QAM_DEMOD_MODULE *pDemod,
	s32 *pAnswer
	);

s32
rtl2840_SoftwareReset(
	QAM_DEMOD_MODULE *pDemod
	);

s32
rtl2840_Initialize(
	QAM_DEMOD_MODULE *pDemod
	);

s32
rtl2840_SetQamMode(
	QAM_DEMOD_MODULE *pDemod,
	s32 QamMode
	);

s32
rtl2840_SetSymbolRateHz(
	QAM_DEMOD_MODULE *pDemod,
	u64 SymbolRateHz
	);

s32
rtl2840_SetAlphaMode(
	QAM_DEMOD_MODULE *pDemod,
	s32 AlphaMode
	);

s32
rtl2840_SetIfFreqHz(
	QAM_DEMOD_MODULE *pDemod,
	u64 IfFreqHz
	);

s32
rtl2840_SetSpectrumMode(
	QAM_DEMOD_MODULE *pDemod,
	s32 SpectrumMode
	);

s32
rtl2840_GetRfAgc(
	QAM_DEMOD_MODULE *pDemod,
	s64 *pRfAgc
	);

s32
rtl2840_GetIfAgc(
	QAM_DEMOD_MODULE *pDemod,
	s64 *pIfAgc
	);

s32
rtl2840_GetDiAgc(
	QAM_DEMOD_MODULE *pDemod,
	u64 *pDiAgc
	);

s32
rtl2840_GetTrOffsetPpm(
	QAM_DEMOD_MODULE *pDemod,
	s64 *pTrOffsetPpm
	);

s32
rtl2840_GetCrOffsetHz(
	QAM_DEMOD_MODULE *pDemod,
	s64 *pCrOffsetHz
	);

s32
rtl2840_IsAagcLocked(
	QAM_DEMOD_MODULE *pDemod,
	s32 *pAnswer
	);

s32
rtl2840_IsEqLocked(
	QAM_DEMOD_MODULE *pDemod,
	s32 *pAnswer
	);

s32
rtl2840_IsFrameLocked(
	QAM_DEMOD_MODULE *pDemod,
	s32 *pAnswer
	);

s32
rtl2840_GetErrorRate(
	QAM_DEMOD_MODULE *pDemod,
	u64 TestVolume,
	u32 WaitTimeMsMax,
	u64 *pBerNum,
	u64 *pBerDen,
	u64 *pPerNum,
	u64 *pPerDen
	);

s32
rtl2840_GetSnrDb(
	QAM_DEMOD_MODULE *pDemod,
	s64 *pSnrDbNum,
	s64 *pSnrDbDen
	);

s32
rtl2840_GetSignalStrength(
	QAM_DEMOD_MODULE *pDemod,
	u64 *pSignalStrength
	);

s32
rtl2840_GetSignalQuality(
	QAM_DEMOD_MODULE *pDemod,
	u64 *pSignalQuality
	);

s32
rtl2840_UpdateFunction(
	QAM_DEMOD_MODULE *pDemod
	);

s32
rtl2840_ResetFunction(
	QAM_DEMOD_MODULE *pDemod
	);





// Demod AM-hum enhancement functions
s32
rtl2840_am_hum_en_SetQamMode(
	QAM_DEMOD_MODULE *pDemod,
	s32 QamMode
	);





// I2C command forwarding functions
s32
rtl2840_ForwardI2cReadingCmd(
	I2C_BRIDGE_MODULE *pI2cBridge,
	u8 DeviceAddr,
	u8 *pReadingBytes,
	u64 ByteNum
	);

s32
rtl2840_ForwardI2cWritingCmd(
	I2C_BRIDGE_MODULE *pI2cBridge,
	u8 DeviceAddr,
	const u8 *pWritingBytes,
	u64 ByteNum
	);





// Register table initialization
void
rtl2840_InitBaseRegTable(
	QAM_DEMOD_MODULE *pDemod
	);

void
rtl2840_InitMonitorRegTable(
	QAM_DEMOD_MODULE *pDemod
	);





// Register getting methods	
s32
rtl2840_GetInnerStrobeRegBits(
	QAM_DEMOD_MODULE *pDemod,
	s32 RegBitName,
	u64 *pReadingValue
	);

s32
rtl2840_GetMonitorRegBits(
	QAM_DEMOD_MODULE *pDemod,
	s32 MonitorRegBitName,
	u64 *pReadingValue
	);





// I2C birdge module builder
void
rtl2840_BuildI2cBridgeModule(
	QAM_DEMOD_MODULE *pDemod
	);















#endif
