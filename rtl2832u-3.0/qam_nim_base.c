/**

@file

@brief   QAM NIM base module definition

QAM NIM base module definitions contains NIM module structure, NIM funciton pointers, NIM definitions, and NIM default
functions.

*/


#include "qam_nim_base.h"





/**

@see   QAM_NIM_FP_GET_NIM_TYPE

*/
void
qam_nim_default_GetNimType(
	QAM_NIM_MODULE *pNim,
	s32 *pNimType
	)
{
	// Get NIM type from NIM module.
	*pNimType = pNim->NimType;


	return;
}





/**

@see   QAM_NIM_FP_SET_PARAMETERS

*/
s32
qam_nim_default_SetParameters(
	QAM_NIM_MODULE *pNim,
	u64 RfFreqHz,
	s32 QamMode,
	u64 SymbolRateHz,
	s32 AlphaMode
	)
{
	TUNER_MODULE *pTuner;
	QAM_DEMOD_MODULE *pDemod;


	// Get tuner module and demod module.
	pTuner = pNim->pTuner;
	pDemod = pNim->pDemod;


	// Set tuner RF frequency in Hz.
	if(pTuner->SetRfFreqHz(pTuner, RfFreqHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod QAM mode.
	if(pDemod->SetQamMode(pDemod, QamMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod symbol rate in Hz.
	if(pDemod->SetSymbolRateHz(pDemod, SymbolRateHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Set demod alpha mode.
	if(pDemod->SetAlphaMode(pDemod, AlphaMode) != FUNCTION_SUCCESS)
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

@see   QAM_NIM_FP_GET_PARAMETERS

*/
s32
qam_nim_default_GetParameters(
	QAM_NIM_MODULE *pNim,
	u64 *pRfFreqHz,
	s32 *pQamMode,
	u64 *pSymbolRateHz,
	s32 *pAlphaMode
	)
{
	TUNER_MODULE *pTuner;
	QAM_DEMOD_MODULE *pDemod;


	// Get tuner module and demod module.
	pTuner = pNim->pTuner;
	pDemod = pNim->pDemod;


	// Get tuner RF frequency in Hz.
	if(pTuner->GetRfFreqHz(pTuner, pRfFreqHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get demod QAM mode.
	if(pDemod->GetQamMode(pDemod, pQamMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get demod symbol rate in Hz.
	if(pDemod->GetSymbolRateHz(pDemod, pSymbolRateHz) != FUNCTION_SUCCESS)
		goto error_status_execute_function;

	// Get demod alpha mode.
	if(pDemod->GetAlphaMode(pDemod, pAlphaMode) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   QAM_NIM_FP_IS_SIGNAL_PRESENT

*/
s32
qam_nim_default_IsSignalPresent(
	QAM_NIM_MODULE *pNim,
	s32 *pAnswer
	)
{
	BASE_INTERFACE_MODULE *pBaseInterface;
	QAM_DEMOD_MODULE *pDemod;
	s32 i;


	// Get base interface and demod module.
	pBaseInterface = pNim->pBaseInterface;
	pDemod         = pNim->pDemod;


	// Wait maximum 1000 ms for signal present check.
	for(i = 0; i < DEFAULT_QAM_NIM_SINGAL_PRESENT_CHECK_TIMES_MAX; i++)
	{
		// Wait 20 ms.
		pBaseInterface->WaitMs(pBaseInterface, 20);

		// Check signal present status on demod.
		// Note: If frame is locked, stop signal present check.
		if(pDemod->IsFrameLocked(pDemod, pAnswer) != FUNCTION_SUCCESS)
			goto error_status_execute_function;

		if(*pAnswer == YES)
			break;
	}


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   QAM_NIM_FP_IS_SIGNAL_LOCKED

*/
s32
qam_nim_default_IsSignalLocked(
	QAM_NIM_MODULE *pNim,
	s32 *pAnswer
	)
{
	BASE_INTERFACE_MODULE *pBaseInterface;
	QAM_DEMOD_MODULE *pDemod;
	s32 i;


	// Get base interface and demod module.
	pBaseInterface = pNim->pBaseInterface;
	pDemod         = pNim->pDemod;


	// Wait maximum 1000 ms for signal lock check.
	for(i = 0; i < DEFAULT_QAM_NIM_SINGAL_LOCK_CHECK_TIMES_MAX; i++)
	{
		// Wait 20 ms.
		pBaseInterface->WaitMs(pBaseInterface, 20);

		// Check frame lock status on demod.
		// Note: If frame is locked, stop signal lock check.
		if(pDemod->IsFrameLocked(pDemod, pAnswer) != FUNCTION_SUCCESS)
			goto error_status_execute_function;

		if(*pAnswer == YES)
			break;
	}


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   QAM_NIM_FP_GET_SIGNAL_STRENGTH

*/
s32
qam_nim_default_GetSignalStrength(
	QAM_NIM_MODULE *pNim,
	u64 *pSignalStrength
	)
{
	QAM_DEMOD_MODULE *pDemod;


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

@see   QAM_NIM_FP_GET_SIGNAL_QUALITY

*/
s32
qam_nim_default_GetSignalQuality(
	QAM_NIM_MODULE *pNim,
	u64 *pSignalQuality
	)
{
	QAM_DEMOD_MODULE *pDemod;


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

@see   QAM_NIM_FP_GET_ERROR_RATE

*/
s32
qam_nim_default_GetErrorRate(
	QAM_NIM_MODULE *pNim,
	u64 TestVolume,
	u32 WaitTimeMsMax,
	u64 *pBerNum,
	u64 *pBerDen,
	u64 *pPerNum,
	u64 *pPerDen
	)
{
	QAM_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Get error rate from demod.
	if(pDemod->GetErrorRate(pDemod, TestVolume, WaitTimeMsMax, pBerNum, pBerDen, pPerNum, pPerDen) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}





/**

@see   QAM_NIM_FP_GET_SNR_DB

*/
s32
qam_nim_default_GetSnrDb(
	QAM_NIM_MODULE *pNim,
	s64 *pSnrDbNum,
	s64 *pSnrDbDen
	)
{
	QAM_DEMOD_MODULE *pDemod;


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

@see   QAM_NIM_FP_GET_TR_OFFSET_PPM

*/
s32
qam_nim_default_GetTrOffsetPpm(
	QAM_NIM_MODULE *pNim,
	s64 *pTrOffsetPpm
	)
{
	QAM_DEMOD_MODULE *pDemod;


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

@see   QAM_NIM_FP_GET_CR_OFFSET_HZ

*/
s32
qam_nim_default_GetCrOffsetHz(
	QAM_NIM_MODULE *pNim,
	s64 *pCrOffsetHz
	)
{
	QAM_DEMOD_MODULE *pDemod;


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

@see   QAM_NIM_FP_UPDATE_FUNCTION

*/
s32
qam_nim_default_UpdateFunction(
	QAM_NIM_MODULE *pNim
	)
{
	QAM_DEMOD_MODULE *pDemod;


	// Get demod module.
	pDemod = pNim->pDemod;


	// Update demod particular registers.
	if(pDemod->UpdateFunction(pDemod) != FUNCTION_SUCCESS)
		goto error_status_execute_function;


	return FUNCTION_SUCCESS;


error_status_execute_function:
	return FUNCTION_ERROR;
}












