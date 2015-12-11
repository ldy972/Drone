/**

@file

@brief   DVB-T NIM base module definition

DVB-T NIM base module definitions contains NIM module structure, NIM funciton pointers, NIM definitions, and NIM default
functions.

*/


#include "dvbt_nim_base.h"

/**
 * @see   DVBT_NIM_FP_GET_NIM_TYPE
 */
void
dvbt_nim_default_GetNimType(
	DVBT_NIM_MODULE *pNim,
	s32 *pNimType
	)
{
	// Get NIM type from NIM module.
	*pNimType = pNim->NimType;


	return;
}





/**

@see   DVBT_NIM_FP_SET_PARAMETERS

*/
s32
dvbt_nim_default_SetParameters(
	DVBT_NIM_MODULE *pNim,
	u64 RfFreqHz,
	s32 BandwidthMode
	)
{
	TUNER_MODULE *pTuner;
	DVBT_DEMOD_MODULE *pDemod;


	// Get tuner module and demod module.
	pTuner = pNim->pTuner;
	pDemod = pNim->pDemod;


	// Set tuner RF frequency in Hz.
	if(pTuner->SetRfFreqHz(pTuner, RfFreqHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod bandwidth mode.
	if(pDemod->SetBandwidthMode(pDemod, BandwidthMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Reset demod particular registers.
	if(pDemod->ResetFunction(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Reset demod by software reset.
	if(pDemod->SoftwareReset(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_GET_PARAMETERS

*/
s32
dvbt_nim_default_GetParameters(
	DVBT_NIM_MODULE *pNim,
	u64 *pRfFreqHz,
	s32 *pBandwidthMode
	)
{
	TUNER_MODULE *pTuner;
	DVBT_DEMOD_MODULE *pDemod;


	// Get tuner module and demod module.
	pTuner = pNim->pTuner;
	pDemod = pNim->pDemod;


	// Get tuner RF frequency in Hz.
	if(pTuner->GetRfFreqHz(pTuner, pRfFreqHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get demod bandwidth mode.
	if(pDemod->GetBandwidthMode(pDemod, pBandwidthMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_IS_SIGNAL_PRESENT

*/
s32
dvbt_nim_default_IsSignalPresent(
	DVBT_NIM_MODULE *pNim,
	s32 *pAnswer
	)
{
	BASE_INTERFACE_MODULE *pBaseInterface;
	DVBT_DEMOD_MODULE *pDemod;
	s32 i;


	// Get base interface and demod module.
	pBaseInterface = pNim->pBaseInterface;
	pDemod         = pNim->pDemod;


	// Wait for signal present check.
	for(i = 0; i < DVBT_NIM_SINGAL_PRESENT_CHECK_TIMES_MAX_DEFAULT; i++)
	{
		// Wait 20 ms.
		pBaseInterface->WaitMs(pBaseInterface, 20);

		// Check TPS present status on demod.
		// Note: If TPS is locked, stop signal present check.
		if(pDemod->IsTpsLocked(pDemod, pAnswer) != FUNCTION_SUCCESS)
			goto error_status_execute_function;

		if(*pAnswer == YES)
			break;
	}


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_IS_SIGNAL_LOCKED

*/
s32
dvbt_nim_default_IsSignalLocked(
	DVBT_NIM_MODULE *pNim,
	s32 *pAnswer
	)
{
	BASE_INTERFACE_MODULE *pBaseInterface;
	DVBT_DEMOD_MODULE *pDemod;
	s32 i;


	// Get base interface and demod module.
	pBaseInterface = pNim->pBaseInterface;
	pDemod         = pNim->pDemod;


	// Wait for signal lock check.
	for(i = 0; i < DVBT_NIM_SINGAL_LOCK_CHECK_TIMES_MAX_DEFAULT; i++)
	{
		// Wait 20 ms.
		pBaseInterface->WaitMs(pBaseInterface, 20);

		// Check signal lock status on demod.
		// Note: If signal is locked, stop signal lock check.
		if(pDemod->IsSignalLocked(pDemod, pAnswer) != FUNCTION_SUCCESS)
			goto error_status_execute_function;

		if(*pAnswer == YES)
			break;
	}


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_GET_SIGNAL_STRENGTH

*/
s32 dvbt_nim_default_GetSignalStrength(DVBT_NIM_MODULE *pNim, u64 *pSignalStrength)
{
	DVBT_DEMOD_MODULE *pDemod;

	// Get demod module.
	pDemod = pNim->pDemod;

	// Get signal strength from demod.
	if(pDemod->GetSignalStrength(pDemod, pSignalStrength) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	return FUNCTION_SUCCESS;

error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_GET_SIGNAL_QUALITY

*/
s32
dvbt_nim_default_GetSignalQuality(
	DVBT_NIM_MODULE *pNim,
	u64 *pSignalQuality
	)
{
	DVBT_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Get signal quality from demod.
	if(pDemod->GetSignalQuality(pDemod, pSignalQuality) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_GET_BER

*/
s32
dvbt_nim_default_GetBer(
	DVBT_NIM_MODULE *pNim,
	u64 *pBerNum,
	u64 *pBerDen
	)
{
	DVBT_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Get BER from demod.
	if(pDemod->GetBer(pDemod, pBerNum, pBerDen) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**
 * @see   DVBT_NIM_FP_GET_SNR_DB
 */
s32 dvbt_nim_default_GetSnrDb(DVBT_NIM_MODULE *pNim, s64 *pSnrDbNum, s64 *pSnrDbDen)
{
	DVBT_DEMOD_MODULE *pDemod;

	// Get demod module.
	pDemod = pNim->pDemod;

	// Get SNR in dB from demod.
	if(pDemod->GetSnrDb(pDemod, pSnrDbNum, pSnrDbDen) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	return FUNCTION_SUCCESS;

error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_GET_TR_OFFSET_PPM

*/
s32
dvbt_nim_default_GetTrOffsetPpm(
	DVBT_NIM_MODULE *pNim,
	s64 *pTrOffsetPpm
	)
{
	DVBT_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Get TR offset in ppm from demod.
	if(pDemod->GetTrOffsetPpm(pDemod, pTrOffsetPpm) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_GET_CR_OFFSET_HZ

*/
s32
dvbt_nim_default_GetCrOffsetHz(
	DVBT_NIM_MODULE *pNim,
	s64 *pCrOffsetHz
	)
{
	DVBT_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Get CR offset in Hz from demod.
	if(pDemod->GetCrOffsetHz(pDemod, pCrOffsetHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_GET_TPS_INFO

*/
s32
dvbt_nim_default_GetTpsInfo(
	DVBT_NIM_MODULE *pNim,
	s32 *pConstellation,
	s32 *pHierarchy,
	s32 *pCodeRateLp,
	s32 *pCodeRateHp,
	s32 *pGuardInterval,
	s32 *pFftMode
	)
{
	DVBT_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Get TPS constellation information from demod.
	if(pDemod->GetConstellation(pDemod, pConstellation) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get TPS hierarchy information from demod.
	if(pDemod->GetHierarchy(pDemod, pHierarchy) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get TPS low-priority code rate information from demod.
	if(pDemod->GetCodeRateLp(pDemod, pCodeRateLp) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get TPS high-priority code rate information from demod.
	if(pDemod->GetCodeRateHp(pDemod, pCodeRateHp) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get TPS guard interval information from demod.
	if(pDemod->GetGuardInterval(pDemod, pGuardInterval) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get TPS FFT mode information from demod.
	if(pDemod->GetFftMode(pDemod, pFftMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DVBT_NIM_FP_UPDATE_FUNCTION

*/
s32
dvbt_nim_default_UpdateFunction(
	DVBT_NIM_MODULE *pNim
	)
{
	DVBT_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Update demod particular registers.
	if(pDemod->UpdateFunction(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}












