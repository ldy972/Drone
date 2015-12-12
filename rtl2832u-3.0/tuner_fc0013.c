/**
@file
@brief   FC0013 tuner module definition

One can manipulate FC0013 tuner through FC0013 module.
FC0013 module is derived from tuner module.

*/

#include "tuner_fc0013.h"


/**

@brief   FC0013 tuner module builder

Use BuildFc0013Module() to build FC0013 module, set all module function pointers with the corresponding functions,
and initialize module private variables.

@param [in]   ppTuner                      Pointer to FC0013 tuner module pointer
@param [in]   pTunerModuleMemory           Pointer to an allocated tuner module memory
@param [in]   pBaseInterfaceModuleMemory   Pointer to an allocated base interface module memory
@param [in]   pI2cBridgeModuleMemory       Pointer to an allocated I2C bridge module memory
@param [in]   DeviceAddr                   FC0013 I2C device address
@param [in]   CrystalFreqHz                FC0013 crystal frequency in Hz

@note
	-# One should call BuildFc0013Module() to build FC0013 module before using it.

*/
void
BuildFc0013Module(
	TUNER_MODULE **ppTuner,
	TUNER_MODULE *pTunerModuleMemory,
	BASE_INTERFACE_MODULE *pBaseInterfaceModuleMemory,
	I2C_BRIDGE_MODULE *pI2cBridgeModuleMemory,
	u8 DeviceAddr,
	u64 CrystalFreqHz)
{
	TUNER_MODULE *pTuner;
	FC0013_EXTRA_MODULE *pExtra;

	// Set tuner module pointer.
	*ppTuner = pTunerModuleMemory;

	// Get tuner module.
	pTuner = *ppTuner;

	// Set base interface module pointer and I2C bridge module pointer.
	pTuner->pBaseInterface = pBaseInterfaceModuleMemory;
	pTuner->pI2cBridge = pI2cBridgeModuleMemory;

	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Fc0013);

	// Set tuner type.
	pTuner->TunerType = TUNER_TYPE_FC0013;

	// Set tuner I2C device address.
	pTuner->DeviceAddr = DeviceAddr;

	// Initialize tuner parameter setting status.
	pTuner->IsRfFreqHzSet = NO;

	// Set tuner module manipulating function pointers.
	pTuner->GetTunerType  = fc0013_GetTunerType;
	pTuner->GetDeviceAddr = fc0013_GetDeviceAddr;

	pTuner->Initialize    = fc0013_Initialize;
	pTuner->SetRfFreqHz   = fc0013_SetRfFreqHz;
	pTuner->GetRfFreqHz   = fc0013_GetRfFreqHz;

	// Initialize tuner extra module variables.
	pExtra->CrystalFreqHz      = CrystalFreqHz;
	pExtra->IsBandwidthModeSet = NO;

	// Set tuner extra module function pointers.
	pExtra->SetBandwidthMode = fc0013_SetBandwidthMode;
	pExtra->GetBandwidthMode = fc0013_GetBandwidthMode;
	pExtra->RcCalReset       = fc0013_RcCalReset;
	pExtra->RcCalAdd         = fc0013_RcCalAdd;

	// Set tuner RF frequency and tuner bandwidth mode.
	// Note: Need to give default tuner RF frequency and tuner bandwidth mode,
	//       because FC0013 API use one funnction to set RF frequency and bandwidth mode.
	pTuner->RfFreqHz      = FC0013_RF_FREQ_HZ_DEFAULT;
	pExtra->BandwidthMode = FC0013_BANDWIDTH_MODE_DEFAULT;

	return;
}


/**

@see   TUNER_FP_GET_TUNER_TYPE

*/
void
fc0013_GetTunerType(
	TUNER_MODULE *pTuner,
	s32 *pTunerType
	)
{
	// Get tuner type from tuner module.
	*pTunerType = pTuner->TunerType;


	return;
}





/**

@see   TUNER_FP_GET_DEVICE_ADDR

*/
void
fc0013_GetDeviceAddr(
	TUNER_MODULE *pTuner,
	u8 *pDeviceAddr
	)
{
	// Get tuner I2C device address from tuner module.
	*pDeviceAddr = pTuner->DeviceAddr;


	return;
}





/**

@see   TUNER_FP_INITIALIZE

*/
s32
fc0013_Initialize(
	TUNER_MODULE *pTuner
	)
{
	FC0013_EXTRA_MODULE *pExtra;



	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Fc0013);


	// Initialize tuner.
	if(FC0013_Open(pTuner) != FC0013_FUNCTION_SUCCESS)
		goto error_status_initialize_tuner;


	return FUNCTION_SUCCESS;


error_status_initialize_tuner:
	return FUNCTION_ERROR;
}





/**

@see   TUNER_FP_SET_RF_FREQ_HZ

*/
s32
fc0013_SetRfFreqHz(
	TUNER_MODULE *pTuner,
	u64 RfFreqHz
	)
{
	FC0013_EXTRA_MODULE *pExtra;
	u64 RfFreqKhz;



	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Fc0013);


	// Set tuner RF frequency in KHz.
	// Note: RfFreqKhz = round(RfFreqHz / 1000)
	RfFreqKhz = (RfFreqHz + 500) / 1000;

	if(FC0013_SetFrequency(pTuner, RfFreqKhz, (u16)(pExtra->BandwidthMode)) != FC0013_FUNCTION_SUCCESS)
		goto error_status_set_tuner_rf_frequency;


	// Set tuner RF frequency parameter.
	pTuner->RfFreqHz      = RfFreqHz;
	pTuner->IsRfFreqHzSet = YES;


	return FUNCTION_SUCCESS;


error_status_set_tuner_rf_frequency:
	return FUNCTION_ERROR;
}





/**

@see   TUNER_FP_GET_RF_FREQ_HZ

*/
s32
fc0013_GetRfFreqHz(
	TUNER_MODULE *pTuner,
	u64 *pRfFreqHz
	)
{
	// Get tuner RF frequency in Hz from tuner module.
	if(pTuner->IsRfFreqHzSet != YES)
		goto error_status_get_tuner_rf_frequency;

	*pRfFreqHz = pTuner->RfFreqHz;


	return FUNCTION_SUCCESS;


error_status_get_tuner_rf_frequency:
	return FUNCTION_ERROR;
}





/**

@brief   Set FC0013 tuner bandwidth mode.

*/
s32
fc0013_SetBandwidthMode(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	)
{
	FC0013_EXTRA_MODULE *pExtra;
	u64 RfFreqKhz;



	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Fc0013);


	// Set tuner bandwidth mode.
	// Note: RfFreqKhz = round(RfFreqHz / 1000)
	RfFreqKhz = (pTuner->RfFreqHz + 500) / 1000;

	if(FC0013_SetFrequency(pTuner, RfFreqKhz, (u16)BandwidthMode) != FC0013_FUNCTION_SUCCESS)
		goto error_status_set_tuner_bandwidth_mode;


	// Set tuner bandwidth mode parameter.
	pExtra->BandwidthMode      = BandwidthMode;
	pExtra->IsBandwidthModeSet = YES;


	return FUNCTION_SUCCESS;


error_status_set_tuner_bandwidth_mode:
	return FUNCTION_ERROR;
}





/**

@brief   Get FC0013 tuner bandwidth mode.

*/
s32
fc0013_GetBandwidthMode(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	)
{
	FC0013_EXTRA_MODULE *pExtra;



	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Fc0013);


	// Get tuner bandwidth mode from tuner module.
	if(pExtra->IsBandwidthModeSet != YES)
		goto error_status_get_tuner_bandwidth_mode;

	*pBandwidthMode = pExtra->BandwidthMode;


	return FUNCTION_SUCCESS;


error_status_get_tuner_bandwidth_mode:
	return FUNCTION_ERROR;
}























// The following context is implemented for FC0013 source code.


// Read FC0013 register.
s32 FC0013_Read(TUNER_MODULE *pTuner, u8 RegAddr, u8 *pByte)
{
	I2C_BRIDGE_MODULE *pI2cBridge;
	u8 DeviceAddr;


	// Get I2C bridge.
	pI2cBridge = pTuner->pI2cBridge;

	// Get tuner device address.
	pTuner->GetDeviceAddr(pTuner, &DeviceAddr);


	// Set tuner register reading address.
	// Note: The I2C format of tuner register reading address setting is as follows:
	//       start_bit + (DeviceAddr | writing_bit) + addr + stop_bit
	if(pI2cBridge->ForwardI2cWritingCmd(pI2cBridge, DeviceAddr, &RegAddr, LEN_1_BYTE) != FUNCTION_SUCCESS)
		goto error_status_set_tuner_register_reading_address;

	// Get tuner register byte.
	// Note: The I2C format of tuner register byte getting is as follows:
	//       start_bit + (DeviceAddr | reading_bit) + read_data + stop_bit
	if(pI2cBridge->ForwardI2cReadingCmd(pI2cBridge, DeviceAddr, pByte, LEN_1_BYTE) != FUNCTION_SUCCESS)
		goto error_status_get_tuner_registers;


	return FC0013_I2C_SUCCESS;


error_status_get_tuner_registers:
error_status_set_tuner_register_reading_address:
	return FC0013_I2C_ERROR;
}





// Write FC0013 register.
s32 FC0013_Write(TUNER_MODULE *pTuner, u8 RegAddr, u8 Byte)
{
	I2C_BRIDGE_MODULE *pI2cBridge;
	u8 DeviceAddr;
	u8 WritingBuffer[LEN_2_BYTE];


	// Get I2C bridge.
	pI2cBridge = pTuner->pI2cBridge;

	// Get tuner device address.
	pTuner->GetDeviceAddr(pTuner, &DeviceAddr);


	// Set writing bytes.
	// Note: The I2C format of tuner register byte setting is as follows:
	//       start_bit + (DeviceAddr | writing_bit) + addr + data + stop_bit
	WritingBuffer[0] = RegAddr;
	WritingBuffer[1] = Byte;

	// Set tuner register bytes with writing buffer.
	if(pI2cBridge->ForwardI2cWritingCmd(pI2cBridge, DeviceAddr, WritingBuffer, LEN_2_BYTE) != FUNCTION_SUCCESS)
		goto error_status_set_tuner_registers;


	return FC0013_I2C_SUCCESS;


error_status_set_tuner_registers:
	return FC0013_I2C_ERROR;
}





// Set FC0013 register mask bits.
s32
fc0013_SetRegMaskBits(
	TUNER_MODULE *pTuner,
	u8 RegAddr,
	u8 Msb,
	u8 Lsb,
	const u8 WritingValue
	)
{
	s32 i;

	u8 ReadingByte;
	u8 WritingByte;

	u8 Mask;
	u8 Shift;


	// Generate mask and shift according to MSB and LSB.
	Mask = 0;

	for(i = Lsb; i < (Msb + 1); i++)
		Mask |= 0x1 << i;

	Shift = Lsb;


	// Get tuner register byte according to register adddress.
	if(FC0013_Read(pTuner, RegAddr, &ReadingByte) != FUNCTION_SUCCESS)
		goto error_status_get_tuner_registers;


	// Reserve byte unmask bit with mask and inlay writing value into it.
	WritingByte = ReadingByte & (~Mask);
	WritingByte |= (WritingValue << Shift) & Mask;


	// Write tuner register byte with writing byte.
	if(FC0013_Write(pTuner, RegAddr, WritingByte) != FUNCTION_SUCCESS)
		goto error_status_set_tuner_registers;


	return FUNCTION_SUCCESS;


error_status_get_tuner_registers:
error_status_set_tuner_registers:
	return FUNCTION_ERROR;
}





// Get FC0013 register mask bits.
s32
fc0013_GetRegMaskBits(
	TUNER_MODULE *pTuner,
	u8 RegAddr,
	u8 Msb,
	u8 Lsb,
	u8 *pReadingValue
	)
{
	s32 i;

	u8 ReadingByte;

	u8 Mask;
	u8 Shift;


	// Generate mask and shift according to MSB and LSB.
	Mask = 0;

	for(i = Lsb; i < (Msb + 1); i++)
		Mask |= 0x1 << i;

	Shift = Lsb;


	// Get tuner register byte according to register adddress.
	if(FC0013_Read(pTuner, RegAddr, &ReadingByte) != FUNCTION_SUCCESS)
		goto error_status_get_tuner_registers;


	// Get register bits from reading byte with mask and shift
	*pReadingValue = (ReadingByte & Mask) >> Shift;


	return FUNCTION_SUCCESS;


error_status_get_tuner_registers:
	return FUNCTION_ERROR;
}



























// The following context is source code provided by fitipower.





// fitipower source code - FC0013_Tuner_Code.cpp


//=====================================================================
//	Fitipower Integrated Technology Inc.
//
//	FC0013 Tuner Code
//
//	Version 0.7
//
//	Date: 2010/12/23
//
//	Copyright 2010, All rights reversed.
//
//	Compile in Visual Studio 2005 C++ Win32 Console
//=====================================================================

// Data Format:
// BYTE: u8, 1 byte, 8 bits
// WORD: u16, 2 bytes, 16 bits
// DWORD: u32, 4 bytes, 32 bits

// include header, just for testing.
//#include "stdafx.h"
//#include "stdlib.h"
//#include <complex>
//#include <stdio.h>
//#include <dos.h>
//#include <conio.h>
//#include "I2C.h"

//#define Crystal_Frequency 28800			// FC0013 Crystal Clock (kHz)


//void FC0013_Write(u8 address, u8 data);
//u8 FC0013_Read(u8 address);
//void FC0013_Open();
//void FC0013_Close();
//void FC0013_RSSI();
//void FC0013_Band_Selection(bool Band_Selection_DVBT);
//void FC0013_SetFrequency(u32 Frequency, u16 Bandwidth);

//u8 FC0013_RSSI_Calibration_Value;
/*
// Console main function, just for testing
s32 main(s32 argc, const s8* argv[])
{
	printf("\n");

	if ( argc > 1 )
	{
		for( s32 i = 1; i < argc; i++ )
		{
			FC0013_SetFrequency( atoi(argv[i]), 8 );
		}	
	}

	return 0;
}

void Delay(u32)
{
	// delay function
}

// FC0013 I2C Write Function
void FC0013_Write(u8 address, u8 data)
{
	// depend on driver function in demodulator vendor.
	I2C_Write(address, data);
}

// FC0013 I2C Read Function
u8 FC0013_Read(u8 address)
{
	// depend on driver function in demodulator vendor.
	return return I2C_Read(address);
}
*/
// FC0013 Open Function, includes enable/reset pin control and registers initialization.
//void FC0013_Open() 
s32 FC0013_Open(TUNER_MODULE *pTuner)
{
	// Enable FC0013 Power
	// (...)
	// FC0013 Enable = High
	// (...)
	// FC0013 Reset = High -> Low
	// (...)

    //================================ update base on new FC0013 register bank
	if(FC0013_Write(pTuner, 0x01, 0x09) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x02, 0x16) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x03, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x04, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x05, 0x17) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x06, 0x02) != FC0013_I2C_SUCCESS) goto error_status;
//	if(FC0013_Write(pTuner, 0x07, 0x27) != FC0013_I2C_SUCCESS) goto error_status;		// 28.8MHz, GainShift: 15               
	if(FC0013_Write(pTuner, 0x07, 0x2A) != FC0013_I2C_SUCCESS) goto error_status;		// 28.8MHz, modified by Realtek               
	if(FC0013_Write(pTuner, 0x08, 0xFF) != FC0013_I2C_SUCCESS) goto error_status;      
	if(FC0013_Write(pTuner, 0x09, 0x6F) != FC0013_I2C_SUCCESS) goto error_status;		// Enable Loop Through
	if(FC0013_Write(pTuner, 0x0A, 0xB8) != FC0013_I2C_SUCCESS) goto error_status;      
	if(FC0013_Write(pTuner, 0x0B, 0x82) != FC0013_I2C_SUCCESS) goto error_status;      

	if(FC0013_Write(pTuner, 0x0C, 0xFE) != FC0013_I2C_SUCCESS) goto error_status;   // Modified for up-dowm AGC by Realtek(for master, and for 2836BU dongle).
//	if(FC0013_Write(pTuner, 0x0C, 0xFC) != FC0013_I2C_SUCCESS) goto error_status;   // Modified for up-dowm AGC by Realtek(for slave, and for 2832 mini dongle).

//	if(FC0013_Write(pTuner, 0x0D, 0x09) != FC0013_I2C_SUCCESS) goto error_status;      
	if(FC0013_Write(pTuner, 0x0D, 0x01) != FC0013_I2C_SUCCESS) goto error_status;   // Modified for AGC non-forcing by Realtek.

	if(FC0013_Write(pTuner, 0x0E, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x0F, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x10, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x11, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x12, 0x00) != FC0013_I2C_SUCCESS) goto error_status;      
	if(FC0013_Write(pTuner, 0x13, 0x00) != FC0013_I2C_SUCCESS) goto error_status;

	if(FC0013_Write(pTuner, 0x14, 0x50) != FC0013_I2C_SUCCESS) goto error_status;		// DVB-T, High Gain
//	if(FC0013_Write(pTuner, 0x14, 0x48) != FC0013_I2C_SUCCESS) goto error_status;		// DVB-T, Middle Gain
//	if(FC0013_Write(pTuner, 0x14, 0x40) != FC0013_I2C_SUCCESS) goto error_status;		// DVB-T, Low Gain

	if(FC0013_Write(pTuner, 0x15, 0x01) != FC0013_I2C_SUCCESS) goto error_status;


	return FC0013_FUNCTION_SUCCESS;

error_status:
	return FC0013_FUNCTION_ERROR;
}

/*
// FC0013 Close Function, control enable/reset and power.
void FC0013_Close()
{
	// FC0013 Enable = Low
	// (...)
	// FC0013 Reset = Low -> High
	// (...)
	// Disable FC0013 Power
	// (...)
}


void FC0013_Band_Selection(bool Band_Selection_DVBT)
{
	if( Band_Selection_DVBT == true )
	{
	    FC0013_Write(0x14, (FC0013_Read(0x14) & 0x9F) | 0x40);
	}
	else
	{
		FC0013_Write(0x14, (FC0013_Read(0x14) & 0x9F) | 0x20);
	}
}


// Get RSSI ADC value
u8 Get_RSSI_Value()
{
	return 0x00;	// return RSSI value
}


// RSSI Calibration Function
void FC0013_RSSI_Calibration()
{
	FC0013_Write(0x09, ( FC0013_Read(0x09) | 0x10 ) );		// set the register 9 bit4 EN_CAL_RSSI as 1
	FC0013_Write(0x06, ( FC0013_Read(0x06) | 0x01 ) );		// set the register 6 bit 0 LNA_POWER_DOWN as 1

	Delay(100);												// delay 100ms

	FC0013_RSSI_Calibration_Value = Get_RSSI_Value();		// read DC value from RSSI pin as rssi_calibration

	FC0013_Write(0x09, ( FC0013_Read(0x09) & 0xEF ) );		// set the register 9 bit4 EN_CAL_RSSI as 0
	FC0013_Write(0x06, ( FC0013_Read(0x06) & 0xFE ) );		// set the register 6 bit 0 LNA_POWER_DOWN as 0
}


// RSSI & LNA Control, call this function if FC0013 is in the External RSSI ADC mode.
void FC0013_RSSI()
{
	u8 Input_Power = 0;									// Get Input power information from RSSI
																	// it should be the difference between RSSI ADC value and RSSI calibration value
	u8 LNA_value;
	u8 RSSI_Value, RSSI_Difference;

	Delay(500);														// Delay 500 ms

	RSSI_Value = Get_RSSI_Value();									// Get RSSI Value from demodulator ADC

	if( RSSI_Value < FC0013_RSSI_Calibration_Value )				// adjust RSSI Calibration Value
		FC0013_RSSI_Calibration_Value = RSSI_Value;

	RSSI_Difference = RSSI_Value - FC0013_RSSI_Calibration_Value;	// Calculate voltage difference of RSSI

	LNA_value = FC0013_Read(0x14);

	//------------------------------------------------ arios modify 2010-12-24
	// " | 0x07" ==> " | 0x27"   (make sure reg[0x07] bit5 = 1)
	// " | 0x0F" ==> " | 0x2F"   (make sure reg[0x07] bit5 = 1)
	// add default in switch case
	switch( (LNA_value & 0x1F) )
	{
		case 0x10:
			if( RSSI_Difference > 6 )									
			{
				FC0013_Write(0x14, (LNA_value & 0xE0) | 0x17);		
				FC0013_Write(0x07, (FC0013_Read(0x07) & 0xF0) | 0x27);
			}
			break;

		case 0x17:													
			if( RSSI_Difference > 40 )									
			{
				FC0013_Write(0x14, (LNA_value & 0xE0) | 0x08);		
				FC0013_Write(0x07, (FC0013_Read(0x07) & 0xF0) | 0x27);
			}
			else if( RSSI_Difference < 3 )							
			{
				FC0013_Write(0x14, (LNA_value & 0xE0) | 0x10);		
				FC0013_Write(0x07, (FC0013_Read(0x07) & 0xF0) | 0x2F);
			}
			break;

		case 0x08:													
			if( RSSI_Difference > 40 )									
			{
				FC0013_Write(0x14, (LNA_value & 0xE0) | 0x02);		
				FC0013_Write(0x07, (FC0013_Read(0x07) & 0xF0) | 0x27);
			}
			else if( RSSI_Difference < 7 )							
			{
				FC0013_Write(0x14, (LNA_value & 0xE0) | 0x17);		
				FC0013_Write(0x07, (FC0013_Read(0x07) & 0xF0) | 0x27);
			}
			break;

		case 0x02:													
			if( RSSI_Difference < 2 )									
			{
				FC0013_Write(0x14, (LNA_value & 0xE0) | 0x08);		
				FC0013_Write(0x07, (FC0013_Read(0x07) & 0xF0) | 0x27);
			}
			break;

		default:
			FC0013_Write(0x14, (LNA_value & 0xE0) | 0x10);		
			FC0013_Write(0x07, (FC0013_Read(0x07) & 0xF0) | 0x2F);
			break;
	}
}
*/


// Set VHF Track depends on input frequency
// Frequency Unit: KHz
s32 FC0013_SetVhfTrack(TUNER_MODULE *pTuner, u64 FrequencyKHz)
{
	u8 read_byte;

    if (FrequencyKHz <= 177500)	// VHF Track: 7
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x1C) != FC0013_I2C_SUCCESS) goto error_status;

    }
    else if (FrequencyKHz <= 184500)	// VHF Track: 6
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x18) != FC0013_I2C_SUCCESS) goto error_status;

    }
    else if (FrequencyKHz <= 191500)	// VHF Track: 5
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x14) != FC0013_I2C_SUCCESS) goto error_status;

    }
    else if (FrequencyKHz <= 198500)	// VHF Track: 4
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x10) != FC0013_I2C_SUCCESS) goto error_status;

    }
    else if (FrequencyKHz <= 205500)	// VHF Track: 3
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x0C) != FC0013_I2C_SUCCESS) goto error_status;

    }
    else if (FrequencyKHz <= 212500)	// VHF Track: 2
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x08) != FC0013_I2C_SUCCESS) goto error_status;

    }
    else if (FrequencyKHz <= 219500)	// VHF Track: 2
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x08) != FC0013_I2C_SUCCESS) goto error_status;

    }
    else if (FrequencyKHz <= 226500)	// VHF Track: 1
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x04) != FC0013_I2C_SUCCESS) goto error_status;
    }
    else	// VHF Track: 1
    {
		if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x04) != FC0013_I2C_SUCCESS) goto error_status;

    }
	
	//------------------------------------------------ arios modify 2010-12-24
	// " | 0x10" ==> " | 0x30"   (make sure reg[0x07] bit5 = 1)

	// Enable VHF filter.
	if(FC0013_Read(pTuner, 0x07, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x07, read_byte | 0x10) != FC0013_I2C_SUCCESS) goto error_status;

	// Disable UHF & GPS.
	if(FC0013_Read(pTuner, 0x14, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x14, read_byte & 0x1F) != FC0013_I2C_SUCCESS) goto error_status;


	return FC0013_FUNCTION_SUCCESS;

error_status:
	return FC0013_FUNCTION_ERROR;
}



// FC0013 frequency/bandwidth setting function.
// Frequency unit: KHz, bandwidth unit: MHz
//void FC0013_SetFrequency(u32 Frequency, u16 Bandwidth)
s32 FC0013_SetFrequency(TUNER_MODULE *pTuner, u64 Frequency, u16 Bandwidth)
{
//    bool VCO1 = false;
//    u32 doubleVCO;
//    u16 xin, xdiv;
//	u8 reg[21], am, pm, multi;
    s32 VCO1 = FC0013_FALSE;
    u64 doubleVCO;
    u16 xin, xdiv;
	u8 reg[21], am, pm, multi;

	u8 read_byte;

	FC0013_EXTRA_MODULE *pExtra;
	u64 CrystalFreqKhz;


	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Fc0013);

	// Get tuner crystal frequency in KHz.
	// Note: CrystalFreqKhz = round(CrystalFreqHz / 1000)
	CrystalFreqKhz = (pExtra->CrystalFreqHz + 500) / 1000;

	// modified 2011-02-09: for D-Book test
	// set VHF_Track = 7
	if(FC0013_Read(pTuner, 0x1D, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
	
	// VHF Track: 7
    if(FC0013_Write(pTuner, 0x1D, (read_byte & 0xE3) | 0x1C) != FC0013_I2C_SUCCESS) goto error_status;


	if( Frequency < 300000 )   
	{
		// Set VHF Track.
		if(FC0013_SetVhfTrack(pTuner, Frequency) != FC0013_I2C_SUCCESS) goto error_status;

		// Enable VHF filter.
		if(FC0013_Read(pTuner, 0x07, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x07, read_byte | 0x10) != FC0013_I2C_SUCCESS) goto error_status;
		
		// Disable UHF & disable GPS.
		if(FC0013_Read(pTuner, 0x14, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x14, read_byte & 0x1F) != FC0013_I2C_SUCCESS) goto error_status;
	}
	else if ( (Frequency >= 300000) && (Frequency <= 862000) )
	{
		// Disable VHF filter.
		if(FC0013_Read(pTuner, 0x07, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x07, read_byte & 0xEF) != FC0013_I2C_SUCCESS) goto error_status;
		
		// enable UHF & disable GPS.
		if(FC0013_Read(pTuner, 0x14, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x14, (read_byte & 0x1F) | 0x40) != FC0013_I2C_SUCCESS) goto error_status;
	}
	else if (Frequency > 862000)
	{
		// Disable VHF filter
		if(FC0013_Read(pTuner, 0x07, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x07, read_byte & 0xEF) != FC0013_I2C_SUCCESS) goto error_status;
		
		// Disable UHF & enable GPS
		if(FC0013_Read(pTuner, 0x14, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x14, (read_byte & 0x1F) | 0x20) != FC0013_I2C_SUCCESS) goto error_status;	
	}

	if (Frequency * 96 < 3560000)
    {
        multi = 96;
        reg[5] = 0x82;
        reg[6] = 0x00;
    }
    else if (Frequency * 64 < 3560000)
    {
        multi = 64;
        reg[5] = 0x02;
        reg[6] = 0x02;
    }
    else if (Frequency * 48 < 3560000)
    {
        multi = 48;
        reg[5] = 0x42;
        reg[6] = 0x00;
    }
    else if (Frequency * 32 < 3560000)
    {
        multi = 32;
        reg[5] = 0x82;
        reg[6] = 0x02;
    }
    else if (Frequency * 24 < 3560000)
    {
        multi = 24;
        reg[5] = 0x22;
        reg[6] = 0x00;
    }
    else if (Frequency * 16 < 3560000)
    {
        multi = 16;
        reg[5] = 0x42;
        reg[6] = 0x02;
    }
    else if (Frequency * 12 < 3560000)
    {
        multi = 12;
        reg[5] = 0x12;
        reg[6] = 0x00;
    }
    else if (Frequency * 8 < 3560000)
    {
        multi = 8;
        reg[5] = 0x22;
        reg[6] = 0x02;
    }
    else if (Frequency * 6 < 3560000)
    {
        multi = 6;
        reg[5] = 0x0A;
        reg[6] = 0x00;
    }
    else if (Frequency * 4 < 3800000)
    {
        multi = 4;
        reg[5] = 0x12;
        reg[6] = 0x02;
    }
	else
	{
        Frequency = Frequency / 2;
		multi = 4;
        reg[5] = 0x0A;
        reg[6] = 0x02;
	}

    doubleVCO = Frequency * multi;

    reg[6] = reg[6] | 0x08;
//	VCO1 = true;
	VCO1 = FC0013_TRUE;

	// Calculate VCO parameters: ap & pm & xin.
//	xdiv = (u16)(doubleVCO / (Crystal_Frequency/2));
	xdiv = (u16)(doubleVCO / (CrystalFreqKhz/2));
//	if( (doubleVCO - xdiv * (Crystal_Frequency/2)) >= (Crystal_Frequency/4) )
	if( (doubleVCO - xdiv * (CrystalFreqKhz/2)) >= (CrystalFreqKhz/4) )
	{
		xdiv = xdiv + 1;
	}

	pm = (u8)( xdiv / 8 );			
    am = (u8)( xdiv - (8 * pm));		

    if (am < 2)
    {
        reg[1] = am + 8;
        reg[2] = pm - 1;
    }
    else
    {
        reg[1] = am;
        reg[2] = pm;
    }

//	xin = (u16)(doubleVCO - ((u16)(doubleVCO / (Crystal_Frequency/2))) * (Crystal_Frequency/2));						
	xin = (u16)(doubleVCO - ((u16)(doubleVCO / (CrystalFreqKhz/2))) * (CrystalFreqKhz/2));						
//	xin = ((xin << 15)/(Crystal_Frequency/2));															
	xin = (u16)((xin << 15)/(CrystalFreqKhz/2));															

//	if( xin >= (u16) pow( (double)2, (double)14) )
//	{
//		xin = xin + (u16) pow( (double)2, (double)15);
//	}
	if( xin >= (u16) 16384 )
		xin = xin + (u16) 32768;

	reg[3] = (u8)(xin >> 8);			
	reg[4] = (u8)(xin & 0x00FF);
	
	
	//===================================== Only for testing 
//	printf("Frequency: %d, Fa: %d, Fp: %d, Xin:%d \n", Frequency, am, pm, xin);

	
	// Set Low-Pass Filter Bandwidth.
    switch(Bandwidth)
    {
        case 6: 
			reg[6] = 0x80 | reg[6];
            break;
        case 7: 
			reg[6] = ~0x80 & reg[6];
            reg[6] = 0x40 | reg[6];
            break;
        case 8:
        default: 
			reg[6] = ~0xC0 & reg[6];
            break;
    }

	reg[5] = reg[5] | 0x07;

	if(FC0013_Write(pTuner, 0x01, reg[1]) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x02, reg[2]) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x03, reg[3]) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x04, reg[4]) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x05, reg[5]) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x06, reg[6]) != FC0013_I2C_SUCCESS) goto error_status;

	if (multi == 64)
	{
//		FC0013_Write(0x11, FC0013_Read(0x11) | 0x04);
		if(FC0013_Read(pTuner, 0x11, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x11, read_byte | 0x04) != FC0013_I2C_SUCCESS) goto error_status;
	}
	else
	{
//		FC0013_Write(0x11, FC0013_Read(0x11) & 0xFB);
		if(FC0013_Read(pTuner, 0x11, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
		if(FC0013_Write(pTuner, 0x11, read_byte & 0xFB) != FC0013_I2C_SUCCESS) goto error_status;
	}

	if(FC0013_Write(pTuner, 0x0E, 0x80) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x0E, 0x00) != FC0013_I2C_SUCCESS) goto error_status;

	if(FC0013_Write(pTuner, 0x0E, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
//	reg[14] = 0x3F & FC0013_Read(0x0E);
	if(FC0013_Read(pTuner, 0x0E, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;
	reg[14] = 0x3F & read_byte;

	if (VCO1)
    {
        if (reg[14] > 0x3C)				
        {
            reg[6] = ~0x08 & reg[6];

			if(FC0013_Write(pTuner, 0x06, reg[6]) != FC0013_I2C_SUCCESS) goto error_status;

			if(FC0013_Write(pTuner, 0x0E, 0x80) != FC0013_I2C_SUCCESS) goto error_status;
			if(FC0013_Write(pTuner, 0x0E, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
        }
    }
	else
    {
        if (reg[14] < 0x02)				
        {
            reg[6] = 0x08 | reg[6];

			if(FC0013_Write(pTuner, 0x06, reg[6]) != FC0013_I2C_SUCCESS) goto error_status;

			if(FC0013_Write(pTuner, 0x0E, 0x80) != FC0013_I2C_SUCCESS) goto error_status;
			if(FC0013_Write(pTuner, 0x0E, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
        }
    }


	return FC0013_FUNCTION_SUCCESS;

error_status:
	return FC0013_FUNCTION_ERROR;
}





// Reset IQ LPF Bandwidth
s32
fc0013_RcCalReset(
	TUNER_MODULE *pTuner
	)
{
	// not forcing RC_cal and ADC_Ext enable
	if(FC0013_Write(pTuner, 0x0D, 0x01) != FC0013_I2C_SUCCESS) goto error_status;
	if(FC0013_Write(pTuner, 0x10, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
 	

	return FC0013_FUNCTION_SUCCESS;


error_status:
	return FC0013_FUNCTION_ERROR;
}





// Increase IQ LPF bandwidth
s32
fc0013_RcCalAdd(
	TUNER_MODULE *pTuner,
	s32 RcValue
	)
{
	u8 read_byte;
	u8 rc_cal;
	s32 WriteValue;
	
	FC0013_EXTRA_MODULE *pExtra;

	// Get tuner extra module.
	pExtra = &(pTuner->Extra.Fc0013);


	// Push RC_cal value Get RC_cal value
	if(FC0013_Write(pTuner, 0x10, 0x00) != FC0013_I2C_SUCCESS) goto error_status;

	//Get RC_cal value
	if(FC0013_Read(pTuner, 0x10, &read_byte) != FC0013_I2C_SUCCESS) goto error_status;

	rc_cal = read_byte & 0x0F;

	WriteValue = (s32)rc_cal + RcValue;


	// Forcing RC_cal
	if(FC0013_Write(pTuner, 0x0D, 0x11) != FC0013_I2C_SUCCESS) goto error_status;

	// Modify RC_cal value
    if( WriteValue > 15 )
    {   
        if(FC0013_Write(pTuner, 0x10, 0x0F) != FC0013_I2C_SUCCESS) goto error_status;
    }
    else if( WriteValue < 0 )
    {
        if(FC0013_Write(pTuner, 0x10, 0x00) != FC0013_I2C_SUCCESS) goto error_status;
    }
    else
    {
        if(FC0013_Write(pTuner, 0x10, (u8)WriteValue) != FC0013_I2C_SUCCESS) goto error_status;
    }


	return FC0013_FUNCTION_SUCCESS;


error_status:
	return FC0013_FUNCTION_ERROR;
}













