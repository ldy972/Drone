#ifndef __NIM_RTL2832_TDA18272
#define __NIM_RTL2832_TDA18272

/**

@file

@brief   RTL2832 TDA18272 NIM module declaration

One can manipulate RTL2832 TDA18272 NIM through RTL2832 TDA18272 NIM module.
RTL2832 TDA18272 NIM module is derived from DVB-T NIM module.



@par Example:
@code

// The example is the same as the NIM example in dvbt_nim_base.h except the listed lines.



#include "nim_rtl2832_tda18272.h"


...



s32 main(void)
{
	DVBT_NIM_MODULE *pNim;
	DVBT_NIM_MODULE DvbtNimModuleMemory;

	...



	// Build RTL2832 TDA18272 NIM module.
	BuildRtl2832Tda18272Module(
		&pNim,
		&DvbtNimModuleMemory,

		9,								// Maximum I2C reading byte number is 9.
		8,								// Maximum I2C writing byte number is 8.
		CustomI2cRead,					// Employ CustomI2cRead() as basic I2C reading function.
		CustomI2cWrite,					// Employ CustomI2cWrite() as basic I2C writing function.
		CustomWaitMs,					// Employ CustomWaitMs() as basic waiting function.

		0x20,							// The RTL2832 I2C device address is 0x20 in 8-bit format.
		CRYSTAL_FREQ_28800000HZ,		// The RTL2832 crystal frequency is 28.8 MHz.
		TS_INTERFACE_SERIAL,			// The RTL2832 TS interface mode is serial.
		RTL2832_APPLICATION_STB,		// The RTL2832 application mode is STB mode.
		200,							// The RTL2832 update function reference period is 200 millisecond
		YES,							// The RTL2832 Function 1 enabling status is YES.

		0xc0,							// The TDA18272 I2C device address is 0xc0 in 8-bit format.
		CRYSTAL_FREQ_16000000HZ,		// The TDA18272 crystal frequency is 16.0 MHz.
		TDA18272_UNIT_0,				// The TDA18272 unit number is 0.
		TDA18272_IF_OUTPUT_VPP_0P7V		// The TDA18272 IF output Vp-p is 0.7 V.
		);



	// See the example for other NIM functions in dvbt_nim_base.h

	...


	return 0;
}


@endcode

*/


#include "demod_rtl2832.h"
#include "tuner_tda18272.h"
#include "dvbt_nim_base.h"





// Definitions
#define RTL2832_TDA18272_ADDITIONAL_INIT_REG_TABLE_LEN		21





// Builder
void
BuildRtl2832Tda18272Module(
	DVBT_NIM_MODULE **ppNim,							// DVB-T NIM dependence
	DVBT_NIM_MODULE *pDvbtNimModuleMemory,

	u64 I2cReadingByteNumMax,					// Base interface dependence
	u64 I2cWritingByteNumMax,
	BASE_FP_I2C_READ I2cRead,
	BASE_FP_I2C_WRITE I2cWrite,
	BASE_FP_WAIT_MS WaitMs,

	u8 DemodDeviceAddr,						// Demod dependence
	u64 DemodCrystalFreqHz,
	s32 DemodTsInterfaceMode,
	s32 DemodAppMode,
	u64 DemodUpdateFuncRefPeriodMs,
	s32 DemodIsFunc1Enabled,

	u8 TunerDeviceAddr,						// Tuner dependence
	u64 TunerCrystalFreqHz,
	s32 TunerUnitNo,
	s32 TunerIfOutputVppMode
	);





// RTL2832 TDA18272 NIM manipulaing functions
s32
rtl2832_tda18272_Initialize(
	DVBT_NIM_MODULE *pNim
	);

s32
rtl2832_tda18272_SetParameters(
	DVBT_NIM_MODULE *pNim,
	u64 RfFreqHz,
	s32 BandwidthMode
	);

s32
rtl2832_tda18272_GetRfPowerLevelDbm(
	DVBT_NIM_MODULE *pNim,
	s64 *pRfPowerLevelDbm
	);






#endif


