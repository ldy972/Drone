#ifndef __DVBT_NIM_BASE_H
#define __DVBT_NIM_BASE_H

/**

@file

@brief   DVB-T NIM base module definition

DVB-T NIM base module definitions contains NIM module structure, NIM funciton pointers, NIM definitions, and NIM default
functions.



@par Example:
@code


#include "nim_demodx_tunery.h"



s32
CustomI2cRead(
	BASE_INTERFACE_MODULE *pBaseInterface,
	u8 DeviceAddr,
	u8 *pReadingBytes,
	u64 ByteNum
	)
{
	// I2C reading format:
	// start_bit + (DeviceAddr | reading_bit) + reading_byte * ByteNum + stop_bit

	...

	return FUNCTION_SUCCESS;

error_status:
	return FUNCTION_ERROR;
}



s32
CustomI2cWrite(
	BASE_INTERFACE_MODULE *pBaseInterface,
	u8 DeviceAddr,
	const u8 *pWritingBytes,
	u64 ByteNum
	)
{
	// I2C writing format:
	// start_bit + (DeviceAddr | writing_bit) + writing_byte * ByteNum + stop_bit

	...

	return FUNCTION_SUCCESS;

error_status:
	return FUNCTION_ERROR;
}



void
CustomWaitMs(
	BASE_INTERFACE_MODULE *pBaseInterface,
	u64 WaitTimeMs
	)
{
	// Wait WaitTimeMs milliseconds.

	...

	return;
}



s32 main(void)
{
	DVBT_NIM_MODULE *pNim;
	DVBT_NIM_MODULE DvbtNimModuleMemory;
	DEMODX_EXTRA_MODULE DemodxExtraModuleMemory;
	TUNERY_EXTRA_MODULE TuneryExtraModuleMemory;

	u64 RfFreqHz;
	s32 BandwidthMode;

	s32 Answer;
	u64 SignalStrength, SignalQuality;
	u64 BerNum, BerDen, PerNum, PerDen;
	double Ber, Per;
	u64 SnrDbNum, SnrDbDen;
	double SnrDb;
	s64 TrOffsetPpm, CrOffsetHz;

	s32 Constellation;
	s32 Hierarchy;
	s32 CodeRateLp;
	s32 CodeRateHp;
	s32 GuardInterval;
	s32 FftMode;



	// Build Demod-X Tuner-Y NIM module.
	BuildDemodxTuneryModule(
		&pNim,
		&DvbtNimModuleMemory,

		9,								// Maximum I2C reading byte number is 9.
		8,								// Maximum I2C writing byte number is 8.
		CustomI2cRead,					// Employ CustomI2cRead() as basic I2C reading function.
		CustomI2cWrite,					// Employ CustomI2cWrite() as basic I2C writing function.
		CustomWaitMs,					// Employ CustomWaitMs() as basic waiting function.

		&DemodxExtraModuleMemory,		// Employ Demod-X extra module.
		0x20,							// The Demod-X I2C device address is 0x20 in 8-bit format.
		CRYSTAL_FREQ_28800000HZ,		// The Demod-X crystal frequency is 28.8 MHz.
		TS_INTERFACE_SERIAL,			// The Demod-X TS interface mode is serial.
		...								// Other arguments for Demod-X

		&TunerxExtraModuleMemory,		// Employ Tuner-Y extra module.
		0xc0,							// The Tuner-Y I2C device address is 0xc0 in 8-bit format.
		...								// Other arguments for Tuner-Y
		);



	// Get NIM type.
	// Note: NIM types are defined in the MODULE_TYPE enumeration.
	pNim->GetNimType(pNim, &NimType);







	// ==== Initialize NIM and set its parameters =====

	// Initialize NIM.
	pNim->Initialize(pNim);

	// Set NIM parameters. (RF frequency, bandwdith mode)
	// Note: In the example:
	//       1. RF frequency is 666 MHz.
	//       2. Bandwidth mode is 8 MHz.
	RfFreqHz      = 666000000;
	BandwidthMode = DVBT_BANDWIDTH_8MHZ;
	pNim->SetParameters(pNim, RfFreqHz, BandwidthMode);



	// Wait 1 second for demod convergence.





	// ==== Get NIM information =====

	// Get NIM parameters. (RF frequency, bandwdith mode)
	pNim->GetParameters(pNim, &RfFreqHz, &BandwidthMode);


	// Get signal present status.
	// Note: 1. The argument Answer is YES when the NIM module has found DVB-T signal in the RF channel.
	//       2. The argument Answer is NO when the NIM module does not find DVB-T signal in the RF channel.
	// Recommendation: Use the IsSignalPresent() function for channel scan.
	pNim->IsSignalPresent(pNim, &Answer);

	// Get signal lock status.
	// Note: 1. The argument Answer is YES when the NIM module has locked DVB-T signal in the RF channel.
	//          At the same time, the NIM module sends TS packets through TS interface hardware pins.
	//       2. The argument Answer is NO when the NIM module does not lock DVB-T signal in the RF channel.
	// Recommendation: Use the IsSignalLocked() function for signal lock check.
	pNim->IsSignalLocked(pNim, &Answer);


	// Get signal strength.
	// Note: 1. The range of SignalStrength is 0~100.
	//       2. Need to map SignalStrength value to UI signal strength bar manually.
	pNim->GetSignalStrength(pNim, &SignalStrength);

	// Get signal quality.
	// Note: 1. The range of SignalQuality is 0~100.
	//       2. Need to map SignalQuality value to UI signal quality bar manually.
	pNim->GetSignalQuality(pNim, &SignalQuality);


	// Get BER.
	pNim->GetBer(pNim, &BerNum, &BerDen);
	Ber = (double)BerNum / (double)BerDen;

	// Get SNR in dB.
	pNim->GetSnrDb(pNim, &SnrDbNum, &SnrDbDen);
	SnrDb = (double)SnrDbNum / (double)SnrDbDen;


	// Get TR offset (symbol timing offset) in ppm.
	pNim->GetTrOffsetPpm(pNim, &TrOffsetPpm);

	// Get CR offset (RF frequency offset) in Hz.
	pNim->GetCrOffsetHz(pNim, &CrOffsetHz);


	// Get TPS information.
	// Note: One can find TPS information definitions in the enumerations as follows:
	//       1. DVBT_CONSTELLATION_MODE.
	//       2. DVBT_HIERARCHY_MODE.
	//       3. DVBT_CODE_RATE_MODE. (for low-priority and high-priority code rate)
	//       4. DVBT_GUARD_INTERVAL_MODE.
	//       5. DVBT_FFT_MODE_MODE
	pNim->GetTpsInfo(pNim, &Constellation, &Hierarchy, &CodeRateLp, &CodeRateHp, &GuardInterval, &FftMode);



	return 0;
}


@endcode

*/


#include "foundation.h"
#include "tuner_base.h"
#include "dvbt_demod_base.h"





// Definitions
#define DVBT_NIM_SINGAL_PRESENT_CHECK_TIMES_MAX_DEFAULT			1
#define DVBT_NIM_SINGAL_LOCK_CHECK_TIMES_MAX_DEFAULT			1





/// DVB-T NIM module pre-definition
typedef struct DVBT_NIM_MODULE_TAG DVBT_NIM_MODULE;





/**

@brief   DVB-T demod type getting function pointer

One can use DVBT_NIM_FP_GET_NIM_TYPE() to get DVB-T NIM type.


@param [in]    pNim       The NIM module pointer
@param [out]   pNimType   Pointer to an allocated memory for storing NIM type


@note
	-# NIM building function will set DVBT_NIM_FP_GET_NIM_TYPE() with the corresponding function.


@see   MODULE_TYPE

*/
typedef void
(*DVBT_NIM_FP_GET_NIM_TYPE)(
	DVBT_NIM_MODULE *pNim,
	s32 *pNimType
	);





/**

@brief   DVB-T NIM initializing function pointer

One can use DVBT_NIM_FP_INITIALIZE() to initialie DVB-T NIM.


@param [in]   pNim   The NIM module pointer


@retval   FUNCTION_SUCCESS   Initialize NIM successfully.
@retval   FUNCTION_ERROR     Initialize NIM unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_INITIALIZE() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_INITIALIZE)(
	DVBT_NIM_MODULE *pNim
	);





/**

@brief   DVB-T NIM parameter setting function pointer

One can use DVBT_NIM_FP_SET_PARAMETERS() to set DVB-T NIM parameters.


@param [in]   pNim            The NIM module pointer
@param [in]   RfFreqHz        RF frequency in Hz for setting
@param [in]   BandwidthMode   Bandwidth mode for setting


@retval   FUNCTION_SUCCESS   Set NIM parameters successfully.
@retval   FUNCTION_ERROR     Set NIM parameters unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_SET_PARAMETERS() with the corresponding function.


@see   DVBT_BANDWIDTH_MODE

*/
typedef s32
(*DVBT_NIM_FP_SET_PARAMETERS)(
	DVBT_NIM_MODULE *pNim,
	u64 RfFreqHz,
	s32 BandwidthMode
	);





/**

@brief   DVB-T NIM parameter getting function pointer

One can use DVBT_NIM_FP_GET_PARAMETERS() to get DVB-T NIM parameters.


@param [in]    pNim             The NIM module pointer
@param [out]   pRfFreqHz        Pointer to an allocated memory for storing NIM RF frequency in Hz
@param [out]   pBandwidthMode   Pointer to an allocated memory for storing NIM bandwidth mode


@retval   FUNCTION_SUCCESS   Get NIM parameters successfully.
@retval   FUNCTION_ERROR     Get NIM parameters unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_GET_PARAMETERS() with the corresponding function.


@see   DVBT_BANDWIDTH_MODE

*/
typedef s32
(*DVBT_NIM_FP_GET_PARAMETERS)(
	DVBT_NIM_MODULE *pNim,
	u64 *pRfFreqHz,
	s32 *pBandwidthMode
	);





/**

@brief   DVB-T NIM signal present asking function pointer

One can use DVBT_NIM_FP_IS_SIGNAL_PRESENT() to ask DVB-T NIM if signal is present.


@param [in]    pNim      The NIM module pointer
@param [out]   pAnswer   Pointer to an allocated memory for storing answer


@retval   FUNCTION_SUCCESS   Perform signal present asking to NIM successfully.
@retval   FUNCTION_ERROR     Perform signal present asking to NIM unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_IS_SIGNAL_PRESENT() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_IS_SIGNAL_PRESENT)(
	DVBT_NIM_MODULE *pNim,
	s32 *pAnswer
	);





/**

@brief   DVB-T NIM signal lock asking function pointer

One can use DVBT_NIM_FP_IS_SIGNAL_LOCKED() to ask DVB-T NIM if signal is locked.


@param [in]    pNim      The NIM module pointer
@param [out]   pAnswer   Pointer to an allocated memory for storing answer


@retval   FUNCTION_SUCCESS   Perform signal lock asking to NIM successfully.
@retval   FUNCTION_ERROR     Perform signal lock asking to NIM unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_IS_SIGNAL_LOCKED() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_IS_SIGNAL_LOCKED)(
	DVBT_NIM_MODULE *pNim,
	s32 *pAnswer
	);





/**

@brief   DVB-T NIM signal strength getting function pointer

One can use DVBT_NIM_FP_GET_SIGNAL_STRENGTH() to get signal strength.


@param [in]    pNim              The NIM module pointer
@param [out]   pSignalStrength   Pointer to an allocated memory for storing signal strength (value = 0 ~ 100)


@retval   FUNCTION_SUCCESS   Get NIM signal strength successfully.
@retval   FUNCTION_ERROR     Get NIM signal strength unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_GET_SIGNAL_STRENGTH() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_GET_SIGNAL_STRENGTH)(
	DVBT_NIM_MODULE *pNim,
	u64 *pSignalStrength
	);





/**

@brief   DVB-T NIM signal quality getting function pointer

One can use DVBT_NIM_FP_GET_SIGNAL_QUALITY() to get signal quality.


@param [in]    pNim             The NIM module pointer
@param [out]   pSignalQuality   Pointer to an allocated memory for storing signal quality (value = 0 ~ 100)


@retval   FUNCTION_SUCCESS   Get NIM signal quality successfully.
@retval   FUNCTION_ERROR     Get NIM signal quality unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_GET_SIGNAL_QUALITY() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_GET_SIGNAL_QUALITY)(
	DVBT_NIM_MODULE *pNim,
	u64 *pSignalQuality
	);





/**

@brief   DVB-T NIM BER value getting function pointer

One can use DVBT_NIM_FP_GET_BER() to get BER.


@param [in]    pNim            The NIM module pointer
@param [out]   pBerNum         Pointer to an allocated memory for storing BER numerator
@param [out]   pBerDen         Pointer to an allocated memory for storing BER denominator


@retval   FUNCTION_SUCCESS   Get NIM BER value successfully.
@retval   FUNCTION_ERROR     Get NIM BER value unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_GET_BER() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_GET_BER)(
	DVBT_NIM_MODULE *pNim,
	u64 *pBerNum,
	u64 *pBerDen
	);





/**

@brief   DVB-T NIM SNR getting function pointer

One can use DVBT_NIM_FP_GET_SNR_DB() to get SNR in dB.


@param [in]    pNim        The NIM module pointer
@param [out]   pSnrDbNum   Pointer to an allocated memory for storing SNR dB numerator
@param [out]   pSnrDbDen   Pointer to an allocated memory for storing SNR dB denominator


@retval   FUNCTION_SUCCESS   Get NIM SNR successfully.
@retval   FUNCTION_ERROR     Get NIM SNR unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_GET_SNR_DB() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_GET_SNR_DB)(
	DVBT_NIM_MODULE *pNim,
	s64 *pSnrDbNum,
	s64 *pSnrDbDen
	);





/**

@brief   DVB-T NIM TR offset getting function pointer

One can use DVBT_NIM_FP_GET_TR_OFFSET_PPM() to get TR offset in ppm.


@param [in]    pNim           The NIM module pointer
@param [out]   pTrOffsetPpm   Pointer to an allocated memory for storing TR offset in ppm


@retval   FUNCTION_SUCCESS   Get NIM TR offset successfully.
@retval   FUNCTION_ERROR     Get NIM TR offset unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_GET_TR_OFFSET_PPM() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_GET_TR_OFFSET_PPM)(
	DVBT_NIM_MODULE *pNim,
	s64 *pTrOffsetPpm
	);





/**

@brief   DVB-T NIM CR offset getting function pointer

One can use DVBT_NIM_FP_GET_CR_OFFSET_HZ() to get CR offset in Hz.


@param [in]    pNim          The NIM module pointer
@param [out]   pCrOffsetHz   Pointer to an allocated memory for storing CR offset in Hz


@retval   FUNCTION_SUCCESS   Get NIM CR offset successfully.
@retval   FUNCTION_ERROR     Get NIM CR offset unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_GET_CR_OFFSET_HZ() with the corresponding function.

*/
typedef s32
(*DVBT_NIM_FP_GET_CR_OFFSET_HZ)(
	DVBT_NIM_MODULE *pNim,
	s64 *pCrOffsetHz
	);





/**

@brief   DVB-T NIM TPS information getting function pointer

One can use DVBT_NIM_FP_GET_TPS_INFO() to get TPS information.


@param [in]    pNim             The NIM module pointer
@param [out]   pConstellation   Pointer to an allocated memory for storing demod constellation mode
@param [out]   pHierarchy       Pointer to an allocated memory for storing demod hierarchy mode
@param [out]   pCodeRateLp      Pointer to an allocated memory for storing demod low-priority code rate mode
@param [out]   pCodeRateHp      Pointer to an allocated memory for storing demod high-priority code rate mode
@param [out]   pGuardInterval   Pointer to an allocated memory for storing demod guard interval mode
@param [out]   pFftMode         Pointer to an allocated memory for storing demod FFT mode


@retval   FUNCTION_SUCCESS   Get NIM TPS information successfully.
@retval   FUNCTION_ERROR     Get NIM TPS information unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_GET_TPS_INFO() with the corresponding function.


@see   DVBT_CONSTELLATION_MODE, DVBT_HIERARCHY_MODE, DVBT_CODE_RATE_MODE, DVBT_GUARD_INTERVAL_MODE, DVBT_FFT_MODE_MODE

*/
typedef s32
(*DVBT_NIM_FP_GET_TPS_INFO)(
	DVBT_NIM_MODULE *pNim,
	s32 *pConstellation,
	s32 *pHierarchy,
	s32 *pCodeRateLp,
	s32 *pCodeRateHp,
	s32 *pGuardInterval,
	s32 *pFftMode
	);





/**

@brief   DVB-T NIM updating function pointer

One can use DVBT_NIM_FP_UPDATE_FUNCTION() to update NIM register setting.


@param [in]   pNim   The NIM module pointer


@retval   FUNCTION_SUCCESS   Update NIM setting successfully.
@retval   FUNCTION_ERROR     Update NIM setting unsuccessfully.


@note
	-# NIM building function will set DVBT_NIM_FP_UPDATE_FUNCTION() with the corresponding function.



@par Example:
@code


#include "nim_demodx_tunery.h"


s32 main(void)
{
	DVBT_NIM_MODULE *pNim;
	DVBT_NIM_MODULE DvbtNimModuleMemory;
	DEMODX_EXTRA_MODULE DemodxExtraModuleMemory;
	TUNERY_EXTRA_MODULE TuneryExtraModuleMemory;


	// Build Demod-X Tuner-Y NIM module.
	BuildDemodxTuneryModule(
		...
		);

	...


	return 0;
}


void PeriodicallyExecutingFunction
{
	// Executing UpdateFunction() periodically.
	pNim->UpdateFunction(pNim);
}


@endcode

*/
typedef s32
(*DVBT_NIM_FP_UPDATE_FUNCTION)(
	DVBT_NIM_MODULE *pNim
	);





// RTL2832 MT2266 extra module
typedef struct RTL2832_MT2266_EXTRA_MODULE_TAG RTL2832_MT2266_EXTRA_MODULE;
struct RTL2832_MT2266_EXTRA_MODULE_TAG
{
	// Extra variables
	u8 LnaConfig;
	u8 UhfSens;
	u8 AgcCurrentState;
	u64 LnaGainOld;
};





// RTL2832 E4000 extra module
typedef struct RTL2832_E4000_EXTRA_MODULE_TAG RTL2832_E4000_EXTRA_MODULE;
struct RTL2832_E4000_EXTRA_MODULE_TAG
{
	// Extra variables
	u64 TunerModeUpdateWaitTimeMax;
	u64 TunerModeUpdateWaitTime;
	u8 TunerGainMode;
};





// RTL2832 MT2063 extra module
typedef struct RTL2832_MT2063_EXTRA_MODULE_TAG RTL2832_MT2063_EXTRA_MODULE;
struct RTL2832_MT2063_EXTRA_MODULE_TAG
{
	// Extra variables
	u64 IfFreqHz;
};





// RTL2832 FC0012 extra module
typedef struct RTL2832_FC0012_EXTRA_MODULE_TAG RTL2832_FC0012_EXTRA_MODULE;
struct RTL2832_FC0012_EXTRA_MODULE_TAG
{
	// Extra variables
	u64 LnaUpdateWaitTimeMax;
	u64 LnaUpdateWaitTime;
	u64 RssiRCalOn;
};





// RTL2832 FC0013 extra module
typedef struct RTL2832_FC0013_EXTRA_MODULE_TAG RTL2832_FC0013_EXTRA_MODULE;
struct RTL2832_FC0013_EXTRA_MODULE_TAG
{
	// Extra variables
	u64 LnaUpdateWaitTimeMax;
	u64 LnaUpdateWaitTime;
	u64 RssiRCalOn;
};





/// DVB-T NIM module structure
struct DVBT_NIM_MODULE_TAG
{
	// Private variables
	s32 NimType;

	union														///<   NIM extra module used by driving module
	{
		RTL2832_MT2266_EXTRA_MODULE Rtl2832Mt2266;
		RTL2832_E4000_EXTRA_MODULE  Rtl2832E4000;
		RTL2832_MT2063_EXTRA_MODULE Rtl2832Mt2063;
		RTL2832_FC0012_EXTRA_MODULE Rtl2832Fc0012;
		RTL2832_FC0013_EXTRA_MODULE Rtl2832Fc0013;
	}
	Extra;


	// Modules
	BASE_INTERFACE_MODULE *pBaseInterface;						///<   Base interface module pointer
	BASE_INTERFACE_MODULE BaseInterfaceModuleMemory;			///<   Base interface module memory

	I2C_BRIDGE_MODULE *pI2cBridge;								///<   I2C bridge module pointer
	I2C_BRIDGE_MODULE I2cBridgeModuleMemory;					///<   I2C bridge module memory

	TUNER_MODULE *pTuner;										///<   Tuner module pointer
	TUNER_MODULE TunerModuleMemory;								///<   Tuner module memory

	DVBT_DEMOD_MODULE *pDemod;									///<   DVB-T demod module pointer
	DVBT_DEMOD_MODULE DvbtDemodModuleMemory;					///<   DVB-T demod module memory


	// NIM manipulating functions
	DVBT_NIM_FP_GET_NIM_TYPE          GetNimType;
	DVBT_NIM_FP_INITIALIZE            Initialize;
	DVBT_NIM_FP_SET_PARAMETERS        SetParameters;
	DVBT_NIM_FP_GET_PARAMETERS        GetParameters;
	DVBT_NIM_FP_IS_SIGNAL_PRESENT     IsSignalPresent;
	DVBT_NIM_FP_IS_SIGNAL_LOCKED      IsSignalLocked;
	DVBT_NIM_FP_GET_SIGNAL_STRENGTH   GetSignalStrength;
	DVBT_NIM_FP_GET_SIGNAL_QUALITY    GetSignalQuality;
	DVBT_NIM_FP_GET_BER               GetBer;
	DVBT_NIM_FP_GET_SNR_DB            GetSnrDb;
	DVBT_NIM_FP_GET_TR_OFFSET_PPM     GetTrOffsetPpm;
	DVBT_NIM_FP_GET_CR_OFFSET_HZ      GetCrOffsetHz;
	DVBT_NIM_FP_GET_TPS_INFO          GetTpsInfo;
	DVBT_NIM_FP_UPDATE_FUNCTION       UpdateFunction;
};







// DVB-T NIM default manipulaing functions
void
dvbt_nim_default_GetNimType(
	DVBT_NIM_MODULE *pNim,
	s32 *pNimType
	);

s32
dvbt_nim_default_SetParameters(
	DVBT_NIM_MODULE *pNim,
	u64 RfFreqHz,
	s32 BandwidthMode
	);

s32
dvbt_nim_default_GetParameters(
	DVBT_NIM_MODULE *pNim,
	u64 *pRfFreqHz,
	s32 *pBandwidthMode
	);

s32
dvbt_nim_default_IsSignalPresent(
	DVBT_NIM_MODULE *pNim,
	s32 *pAnswer
	);

s32
dvbt_nim_default_IsSignalLocked(
	DVBT_NIM_MODULE *pNim,
	s32 *pAnswer
	);

s32
dvbt_nim_default_GetSignalStrength(
	DVBT_NIM_MODULE *pNim,
	u64 *pSignalStrength
	);

s32
dvbt_nim_default_GetSignalQuality(
	DVBT_NIM_MODULE *pNim,
	u64 *pSignalQuality
	);

s32
dvbt_nim_default_GetBer(
	DVBT_NIM_MODULE *pNim,
	u64 *pBerNum,
	u64 *pBerDen
	);

s32
dvbt_nim_default_GetSnrDb(
	DVBT_NIM_MODULE *pNim,
	s64 *pSnrDbNum,
	s64 *pSnrDbDen
	);

s32
dvbt_nim_default_GetTrOffsetPpm(
	DVBT_NIM_MODULE *pNim,
	s64 *pTrOffsetPpm
	);

s32
dvbt_nim_default_GetCrOffsetHz(
	DVBT_NIM_MODULE *pNim,
	s64 *pCrOffsetHz
	);

s32
dvbt_nim_default_GetTpsInfo(
	DVBT_NIM_MODULE *pNim,
	s32 *pConstellation,
	s32 *pHierarchy,
	s32 *pCodeRateLp,
	s32 *pCodeRateHp,
	s32 *pGuardInterval,
	s32 *pFftMode
	);

s32
dvbt_nim_default_UpdateFunction(
	DVBT_NIM_MODULE *pNim
	);







#endif
