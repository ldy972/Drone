/**

@file

@brief   DTMB NIM base module definition

DTMB NIM base module definitions contains NIM module structure, NIM funciton pointers, NIM definitions, and NIM default
functions.

*/


#include "dtmb_nim_base.h"





/**

@see   DTMB_NIM_FP_GET_NIM_TYPE

*/
void
dtmb_nim_default_GetNimType(
	DTMB_NIM_MODULE *pNim,
	s32 *pNimType
	)
{
	// Get NIM type from NIM module.
	*pNimType = pNim->NimType;


	return;
}





/**

@see   DTMB_NIM_FP_SET_PARAMETERS

*/
s32
dtmb_nim_default_SetParameters(
	DTMB_NIM_MODULE *pNim,
	u64 RfFreqHz
	)
{
	TUNER_MODULE *pTuner;
	DTMB_DEMOD_MODULE *pDemod;


	// Get tuner module and demod module.
	pTuner = pNim->pTuner;
	pDemod = pNim->pDemod;


	// Set tuner RF frequency in Hz.
	if(pTuner->SetRfFreqHz(pTuner, RfFreqHz) != FUNCTION_SUCCESS)
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

@see   DTMB_NIM_FP_GET_PARAMETERS

*/
s32
dtmb_nim_default_GetParameters(
	DTMB_NIM_MODULE *pNim,
	u64 *pRfFreqHz
	)
{
	TUNER_MODULE *pTuner;


	// Get tuner module.
	pTuner = pNim->pTuner;


	// Get tuner RF frequency in Hz.
	if(pTuner->GetRfFreqHz(pTuner, pRfFreqHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DTMB_NIM_FP_IS_SIGNAL_PRESENT

*/
s32
dtmb_nim_default_IsSignalPresent(
	DTMB_NIM_MODULE *pNim,
	s32 *pAnswer
	)
{
	BASE_INTERFACE_MODULE *pBaseInterface;
	DTMB_DEMOD_MODULE *pDemod;
	s32 i;


	// Get base interface and demod module.
	pBaseInterface = pNim->pBaseInterface;
	pDemod         = pNim->pDemod;


	// Wait for signal present check.
	for(i = 0; i < DTMB_NIM_SINGAL_PRESENT_CHECK_TIMES_MAX_DEFAULT; i++)
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

@see   DTMB_NIM_FP_IS_SIGNAL_LOCKED

*/
s32
dtmb_nim_default_IsSignalLocked(
	DTMB_NIM_MODULE *pNim,
	s32 *pAnswer
	)
{
	BASE_INTERFACE_MODULE *pBaseInterface;
	DTMB_DEMOD_MODULE *pDemod;
	s32 i;


	// Get base interface and demod module.
	pBaseInterface = pNim->pBaseInterface;
	pDemod         = pNim->pDemod;


	// Wait for signal lock check.
	for(i = 0; i < DTMB_NIM_SINGAL_LOCK_CHECK_TIMES_MAX_DEFAULT; i++)
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

@see   DTMB_NIM_FP_GET_SIGNAL_STRENGTH

*/
s32
dtmb_nim_default_GetSignalStrength(
	DTMB_NIM_MODULE *pNim,
	u64 *pSignalStrength
	)
{
	DTMB_DEMOD_MODULE *pDemod;


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

@see   DTMB_NIM_FP_GET_SIGNAL_QUALITY

*/
s32
dtmb_nim_default_GetSignalQuality(
	DTMB_NIM_MODULE *pNim,
	u64 *pSignalQuality
	)
{
	DTMB_DEMOD_MODULE *pDemod;


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

@see   DTMB_NIM_FP_GET_BER

*/
s32
dtmb_nim_default_GetBer(
	DTMB_NIM_MODULE *pNim,
	u64 *pBerNum,
	u64 *pBerDen
	)
{
	DTMB_DEMOD_MODULE *pDemod;


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

@see   DTMB_NIM_FP_GET_PER

*/
s32
dtmb_nim_default_GetPer(
	DTMB_NIM_MODULE *pNim,
	u64 *pPerNum,
	u64 *pPerDen
	)
{
	DTMB_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Get PER from demod.
	if(pDemod->GetPer(pDemod, pPerNum, pPerDen) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DTMB_NIM_FP_GET_SNR_DB

*/
s32
dtmb_nim_default_GetSnrDb(
	DTMB_NIM_MODULE *pNim,
	s64 *pSnrDbNum,
	s64 *pSnrDbDen
	)
{
	DTMB_DEMOD_MODULE *pDemod;


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

@see   DTMB_NIM_FP_GET_TR_OFFSET_PPM

*/
s32
dtmb_nim_default_GetTrOffsetPpm(
	DTMB_NIM_MODULE *pNim,
	s64 *pTrOffsetPpm
	)
{
	DTMB_DEMOD_MODULE *pDemod;


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

@see   DTMB_NIM_FP_GET_CR_OFFSET_HZ

*/
s32
dtmb_nim_default_GetCrOffsetHz(
	DTMB_NIM_MODULE *pNim,
	s64 *pCrOffsetHz
	)
{
	DTMB_DEMOD_MODULE *pDemod;


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

@see   DTMB_NIM_FP_GET_SIGNAL_INFO

*/
s32
dtmb_nim_default_GetSignalInfo(
	DTMB_NIM_MODULE *pNim,
	s32 *pCarrierMode,
	s32 *pPnMode,
	s32 *pQamMode,
	s32 *pCodeRateMode,
	s32 *pTimeInterleaverMode
	)
{
	DTMB_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Get signal information from demod.
	if(pDemod->GetCarrierMode(pDemod, pCarrierMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	if(pDemod->GetPnMode(pDemod, pPnMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	if(pDemod->GetQamMode(pDemod, pQamMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	if(pDemod->GetCodeRateMode(pDemod, pCodeRateMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	if(pDemod->GetTimeInterleaverMode(pDemod, pTimeInterleaverMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   DTMB_NIM_FP_UPDATE_FUNCTION

*/
s32
dtmb_nim_default_UpdateFunction(
	DTMB_NIM_MODULE *pNim
	)
{
	DTMB_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Update demod particular registers.
	if(pDemod->UpdateFunction(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}












