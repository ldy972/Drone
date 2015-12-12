#ifndef __TUNER_BASE_H
#define __TUNER_BASE_H

/**

@file

@brief   Tuner base module definition

Tuner base module definitions contains tuner module structure, tuner funciton pointers, and tuner definitions.



@par Example:
@code


#include "demod_xxx.h"
#include "tuner_xxx.h"



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
	BASE_INTERFACE_MODULE *pBaseInterface;
	BASE_INTERFACE_MODULE BaseInterfaceModuleMemory;

	XXX_DEMOD_MODULE *pDemod;
	XXX_DEMOD_MODULE XxxDemodModuleMemory;

	TUNER_MODULE *pTuner;
	TUNER_MODULE TunerModuleMemory;

	I2C_BRIDGE_MODULE I2cBridgeModuleMemory;

	u64 RfFreqHz;

	s32 TunerType;
	u8 DeviceAddr;



	// Build base interface module.
	BuildBaseInterface(
		&pBaseInterface,
		&BaseInterfaceModuleMemory,
		9,								// Set maximum I2C reading byte number with 9.
		8,								// Set maximum I2C writing byte number with 8.
		CustomI2cRead,					// Employ CustomI2cRead() as basic I2C reading function.
		CustomI2cWrite,					// Employ CustomI2cWrite() as basic I2C writing function.
		CustomWaitMs					// Employ CustomWaitMs() as basic waiting function.
		);


	// Build dmeod XXX module.
	// Note: Demod module builder will set I2cBridgeModuleMemory for tuner I2C command forwarding.
	//       Must execute demod builder to set I2cBridgeModuleMemory before use tuner functions.
	BuildDemodXxxModule(
		&pDemod,
		&XxxDemodModuleMemory,
		&BaseInterfaceModuleMemory,
		&I2cBridgeModuleMemory,
		...								// Other arguments by each demod module
		)


	// Build tuner XXX module.
	BuildTunerXxxModule(
		&pTuner,
		&TunerModuleMemory,
		&BaseInterfaceModuleMemory,
		&I2cBridgeModuleMemory,
		0xc0,							// Tuner I2C device address is 0xc0 in 8-bit format.
		...								// Other arguments by each demod module
		);





	// ==== Initialize tuner and set its parameters =====

	// Initialize tuner.
	pTuner->Initialize(pTuner);


	// Set tuner parameters. (RF frequency)
	// Note: In the example, RF frequency is 474 MHz.
	RfFreqHz = 474000000;

	pTuner->SetIfFreqHz(pTuner, RfFreqHz);





	// ==== Get tuner information =====

	// Get tuenr type.
	// Note: One can find tuner type in MODULE_TYPE enumeration.
	pTuner->GetTunerType(pTuner, &TunerType);

	// Get tuner I2C device address.
	pTuner->GetDeviceAddr(pTuner, &DeviceAddr);


	// Get tuner parameters. (RF frequency)
	pTuner->GetRfFreqHz(pTuner, &RfFreqHz);



	return 0;
}


@endcode

*/


#include "foundation.h"





/// tuner module pre-definition
typedef struct TUNER_MODULE_TAG TUNER_MODULE;





/**

@brief   Tuner type getting function pointer

One can use TUNER_FP_GET_TUNER_TYPE() to get tuner type.


@param [in]    pTuner       The tuner module pointer
@param [out]   pTunerType   Pointer to an allocated memory for storing tuner type


@note
	-# Tuner building function will set TUNER_FP_GET_TUNER_TYPE() with the corresponding function.


@see   TUNER_TYPE

*/
typedef void
(*TUNER_FP_GET_TUNER_TYPE)(
	TUNER_MODULE *pTuner,
	s32 *pTunerType
	);





/**

@brief   Tuner I2C device address getting function pointer

One can use TUNER_FP_GET_DEVICE_ADDR() to get tuner I2C device address.


@param [in]    pTuner        The tuner module pointer
@param [out]   pDeviceAddr   Pointer to an allocated memory for storing tuner I2C device address


@retval   FUNCTION_SUCCESS   Get tuner device address successfully.
@retval   FUNCTION_ERROR     Get tuner device address unsuccessfully.


@note
	-# Tuner building function will set TUNER_FP_GET_DEVICE_ADDR() with the corresponding function.

*/
typedef void
(*TUNER_FP_GET_DEVICE_ADDR)(
	TUNER_MODULE *pTuner,
	u8 *pDeviceAddr
	);





/**

@brief   Tuner initializing function pointer

One can use TUNER_FP_INITIALIZE() to initialie tuner.


@param [in]   pTuner   The tuner module pointer


@retval   FUNCTION_SUCCESS   Initialize tuner successfully.
@retval   FUNCTION_ERROR     Initialize tuner unsuccessfully.


@note
	-# Tuner building function will set TUNER_FP_INITIALIZE() with the corresponding function.

*/
typedef s32
(*TUNER_FP_INITIALIZE)(
	TUNER_MODULE *pTuner
	);





/**

@brief   Tuner RF frequency setting function pointer

One can use TUNER_FP_SET_RF_FREQ_HZ() to set tuner RF frequency in Hz.


@param [in]   pTuner     The tuner module pointer
@param [in]   RfFreqHz   RF frequency in Hz for setting


@retval   FUNCTION_SUCCESS   Set tuner RF frequency successfully.
@retval   FUNCTION_ERROR     Set tuner RF frequency unsuccessfully.


@note
	-# Tuner building function will set TUNER_FP_SET_RF_FREQ_HZ() with the corresponding function.

*/
typedef s32
(*TUNER_FP_SET_RF_FREQ_HZ)(
	TUNER_MODULE *pTuner,
	u64 RfFreqHz
	);





/**

@brief   Tuner RF frequency getting function pointer

One can use TUNER_FP_GET_RF_FREQ_HZ() to get tuner RF frequency in Hz.


@param [in]   pTuner      The tuner module pointer
@param [in]   pRfFreqHz   Pointer to an allocated memory for storing demod RF frequency in Hz


@retval   FUNCTION_SUCCESS   Get tuner RF frequency successfully.
@retval   FUNCTION_ERROR     Get tuner RF frequency unsuccessfully.


@note
	-# Tuner building function will set TUNER_FP_GET_RF_FREQ_HZ() with the corresponding function.

*/
typedef s32
(*TUNER_FP_GET_RF_FREQ_HZ)(
	TUNER_MODULE *pTuner,
	u64 *pRfFreqHz
	);





// TDCG-G052D extra module
typedef struct TDCGG052D_EXTRA_MODULE_TAG TDCGG052D_EXTRA_MODULE;
struct TDCGG052D_EXTRA_MODULE_TAG
{
	// TDCG-G052D extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control;
	u8 BandSwitch;
	u8 Auxiliary;
};





// TDCH-G001D extra module
typedef struct TDCHG001D_EXTRA_MODULE_TAG TDCHG001D_EXTRA_MODULE;
struct TDCHG001D_EXTRA_MODULE_TAG
{
	// TDCH-G001D extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control;
	u8 BandSwitch;
	u8 Auxiliary;
};





// TDQE3-003A extra module
#define TDQE3003A_CONTROL_BYTE_NUM		3

typedef struct TDQE3003A_EXTRA_MODULE_TAG TDQE3003A_EXTRA_MODULE;
struct TDQE3003A_EXTRA_MODULE_TAG
{
	// TDQE3-003A extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control[TDQE3003A_CONTROL_BYTE_NUM];
};





// DCT-7045 extra module
typedef struct DCT7045_EXTRA_MODULE_TAG DCT7045_EXTRA_MODULE;
struct DCT7045_EXTRA_MODULE_TAG
{
	// DCT-7045 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control;
};





/// MT2062 extra module
typedef struct MT2062_EXTRA_MODULE_TAG MT2062_EXTRA_MODULE;

// MT2062 handle openning function pointer
typedef s32
(*MT2062_FP_OPEN_HANDLE)(
	TUNER_MODULE *pTuner
	);

// MT2062 handle closing function pointer
typedef s32
(*MT2062_FP_CLOSE_HANDLE)(
	TUNER_MODULE *pTuner
	);

// MT2062 handle getting function pointer
typedef void
(*MT2062_FP_GET_HANDLE)(
	TUNER_MODULE *pTuner,
	void **pDeviceHandle
	);

// MT2062 IF frequency setting function pointer
typedef s32
(*MT2062_FP_SET_IF_FREQ_HZ)(
	TUNER_MODULE *pTuner,
	u64 IfFreqHz
	);

// MT2062 IF frequency getting function pointer
typedef s32
(*MT2062_FP_GET_IF_FREQ_HZ)(
	TUNER_MODULE *pTuner,
	u64 *pIfFreqHz
	);

// MT2062 extra module
struct MT2062_EXTRA_MODULE_TAG
{
	// MT2062 extra variables
	void *DeviceHandle;
	s32 LoopThroughMode;

	u64 IfFreqHz;

	s32 IsIfFreqHzSet;

	// MT2062 extra function pointers
	MT2062_FP_OPEN_HANDLE      OpenHandle;
	MT2062_FP_CLOSE_HANDLE     CloseHandle;
	MT2062_FP_GET_HANDLE       GetHandle;
	MT2062_FP_SET_IF_FREQ_HZ   SetIfFreqHz;
	MT2062_FP_GET_IF_FREQ_HZ   GetIfFreqHz;
};





/// MxL5005S extra module
#define INITCTRL_NUM		40
#define CHCTRL_NUM			36
#define MXLCTRL_NUM			189
#define TUNER_REGS_NUM		104

typedef struct MXL5005S_EXTRA_MODULE_TAG MXL5005S_EXTRA_MODULE;

// MXL5005 Tuner Register Struct
typedef struct _TunerReg_struct
{
	u16 	Reg_Num ;							// Tuner Register Address
	u16	Reg_Val ;							// Current sofware programmed value waiting to be writen
} TunerReg_struct ;

// MXL5005 Tuner Control Struct
typedef struct _TunerControl_struct {
	u16	Ctrl_Num ;							// Control Number
	u16	size ;								// Number of bits to represent Value
	u16 	addr[25] ;							// Array of Tuner Register Address for each bit position
	u16 	bit[25] ;							// Array of bit position in Register Address for each bit position
	u16 	val[25] ;							// Binary representation of Value
} TunerControl_struct ;

// MXL5005 Tuner Struct
typedef struct _Tuner_struct
{
	u8			Mode ;				// 0: Analog Mode ; 1: Digital Mode
	u8			IF_Mode ;			// for Analog Mode, 0: zero IF; 1: low IF
	u64			Chan_Bandwidth ;	// filter  channel bandwidth (6, 7, 8)
	u64			IF_OUT ;			// Desired IF Out Frequency
	u16			IF_OUT_LOAD ;		// IF Out Load Resistor (200/300 Ohms)
	u64			RF_IN ;				// RF Input Frequency
	u64			Fxtal ;				// XTAL Frequency
	u8			AGC_Mode ;			// AGC Mode 0: Dual AGC; 1: Single AGC
	u16			TOP ;				// Value: take over point
	u8			CLOCK_OUT ;			// 0: turn off clock out; 1: turn on clock out
	u8			DIV_OUT ;			// 4MHz or 16MHz
	u8			CAPSELECT ;			// 0: disable On-Chip pulling cap; 1: enable
	u8			EN_RSSI ;			// 0: disable RSSI; 1: enable RSSI
	u8			Mod_Type ;			// Modulation Type; 
										// 0 - Default;	1 - DVB-T; 2 - ATSC; 3 - QAM; 4 - Analog Cable
	u8			TF_Type ;			// Tracking Filter Type
										// 0 - Default; 1 - Off; 2 - Type C; 3 - Type C-H

	// Calculated Settings
	u64			RF_LO ;				// Synth RF LO Frequency
	u64			IF_LO ;				// Synth IF LO Frequency
	u64			TG_LO ;				// Synth TG_LO Frequency

	// Pointers to ControlName Arrays
	u16					Init_Ctrl_Num ;					// Number of INIT Control Names
	TunerControl_struct		Init_Ctrl[INITCTRL_NUM] ;		// INIT Control Names Array Pointer
	u16					CH_Ctrl_Num ;					// Number of CH Control Names
	TunerControl_struct		CH_Ctrl[CHCTRL_NUM] ;			// CH Control Name Array Pointer
	u16					MXL_Ctrl_Num ;					// Number of MXL Control Names
	TunerControl_struct		MXL_Ctrl[MXLCTRL_NUM] ;			// MXL Control Name Array Pointer

	// Pointer to Tuner Register Array
	u16					TunerRegs_Num ;		// Number of Tuner Registers
	TunerReg_struct			TunerRegs[TUNER_REGS_NUM] ;			// Tuner Register Array Pointer
} Tuner_struct ;

// MxL5005S register setting function pointer
typedef s32
(*MXL5005S_FP_SET_REGS_WITH_TABLE)(
	TUNER_MODULE *pTuner,
	u8 *pAddrTable,
	u8 *pByteTable,
	s32 TableLen
	);

// MxL5005S register mask bits setting function pointer
typedef s32
(*MXL5005S_FP_SET_REG_MASK_BITS)(
	TUNER_MODULE *pTuner,
	u8 RegAddr,
	u8 Msb,
	u8 Lsb,
	const u8 WritingValue
	);

// MxL5005S spectrum mode setting function pointer
typedef s32
(*MXL5005S_FP_SET_SPECTRUM_MODE)(
	TUNER_MODULE *pTuner,
	s32 SpectrumMode
	);

// MxL5005S bandwidth setting function pointer
typedef s32
(*MXL5005S_FP_SET_BANDWIDTH_HZ)(
	TUNER_MODULE *pTuner,
	u64 BandwidthHz
	);

// MxL5005S extra module
struct MXL5005S_EXTRA_MODULE_TAG
{
	// MxL5005S function pointers
	MXL5005S_FP_SET_REGS_WITH_TABLE   SetRegsWithTable;
	MXL5005S_FP_SET_REG_MASK_BITS     SetRegMaskBits;
	MXL5005S_FP_SET_SPECTRUM_MODE     SetSpectrumMode;
	MXL5005S_FP_SET_BANDWIDTH_HZ      SetBandwidthHz;


	// MxL5005S extra data
	u8 AgcMasterByte;			//   Variable name in MaxLinear source code: AGC_MASTER_BYTE

	// MaxLinear defined struct
	Tuner_struct MxlDefinedTunerStructure;
};





// TDVM-H715P extra module
typedef struct TDVMH715P_EXTRA_MODULE_TAG TDVMH751P_EXTRA_MODULE;
struct TDVMH715P_EXTRA_MODULE_TAG
{
	// TDVM-H715P extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control;
	u8 BandSwitch;
	u8 Auxiliary;
};





// UBA00AL extra module
typedef struct UBA00AL_EXTRA_MODULE_TAG UBA00AL_EXTRA_MODULE;
struct UBA00AL_EXTRA_MODULE_TAG
{
	// UBA00AL extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 BandSwitch;
	u8 Control2;
};





/// MT2266 extra module
typedef struct MT2266_EXTRA_MODULE_TAG MT2266_EXTRA_MODULE;

// MT2266 handle openning function pointer
typedef s32
(*MT2266_FP_OPEN_HANDLE)(
	TUNER_MODULE *pTuner
	);

// MT2266 handle closing function pointer
typedef s32
(*MT2266_FP_CLOSE_HANDLE)(
	TUNER_MODULE *pTuner
	);

// MT2266 handle getting function pointer
typedef void
(*MT2266_FP_GET_HANDLE)(
	TUNER_MODULE *pTuner,
	void **pDeviceHandle
	);

// MT2266 bandwidth setting function pointer
typedef s32
(*MT2266_FP_SET_BANDWIDTH_HZ)(
	TUNER_MODULE *pTuner,
	u64 BandwidthHz
	);

// MT2266 bandwidth getting function pointer
typedef s32
(*MT2266_FP_GET_BANDWIDTH_HZ)(
	TUNER_MODULE *pTuner,
	u64 *pBandwidthHz
	);

// MT2266 extra module
struct MT2266_EXTRA_MODULE_TAG
{
	// MT2266 extra variables
	void *DeviceHandle;
	u64 BandwidthHz;
	s32 IsBandwidthHzSet;

	// MT2266 extra function pointers
	MT2266_FP_OPEN_HANDLE        OpenHandle;
	MT2266_FP_CLOSE_HANDLE       CloseHandle;
	MT2266_FP_GET_HANDLE         GetHandle;
	MT2266_FP_SET_BANDWIDTH_HZ   SetBandwidthHz;
	MT2266_FP_GET_BANDWIDTH_HZ   GetBandwidthHz;
};





// FC2580 extra module
typedef struct FC2580_EXTRA_MODULE_TAG FC2580_EXTRA_MODULE;

// FC2580 bandwidth mode setting function pointer
typedef s32
(*FC2580_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

// FC2580 bandwidth mode getting function pointer
typedef s32
(*FC2580_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

// FC2580 extra module
struct FC2580_EXTRA_MODULE_TAG
{
	// FC2580 extra variables
	u64 CrystalFreqHz;
	s32 AgcMode;
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;

	// FC2580 extra function pointers
	FC2580_FP_SET_BANDWIDTH_MODE   SetBandwidthMode;
	FC2580_FP_GET_BANDWIDTH_MODE   GetBandwidthMode;
};





/// TUA9001 extra module
typedef struct TUA9001_EXTRA_MODULE_TAG TUA9001_EXTRA_MODULE;

// Extra manipulaing function
typedef s32
(*TUA9001_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

typedef s32
(*TUA9001_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

typedef s32
(*TUA9001_FP_GET_REG_BYTES_WITH_REG_ADDR)(
	TUNER_MODULE *pTuner,
	u8 DeviceAddr,
	u8 RegAddr,
	u8 *pReadingByte,
	u8 ByteNum
	);

typedef s32
(*TUA9001_FP_SET_SYS_REG_BYTE)(
	TUNER_MODULE *pTuner,
	u16 RegAddr,
	u8 WritingByte
	);

typedef s32
(*TUA9001_FP_GET_SYS_REG_BYTE)(
	TUNER_MODULE *pTuner,
	u16 RegAddr,
	u8 *pReadingByte
	);

// TUA9001 extra module
struct TUA9001_EXTRA_MODULE_TAG
{
	// TUA9001 extra variables
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;

	// TUA9001 extra function pointers
	TUA9001_FP_SET_BANDWIDTH_MODE            SetBandwidthMode;
	TUA9001_FP_GET_BANDWIDTH_MODE            GetBandwidthMode;
	TUA9001_FP_GET_REG_BYTES_WITH_REG_ADDR   GetRegBytesWithRegAddr;
	TUA9001_FP_SET_SYS_REG_BYTE              SetSysRegByte;
	TUA9001_FP_GET_SYS_REG_BYTE              GetSysRegByte;
};





// DTT-75300 extra module
typedef struct DTT75300_EXTRA_MODULE_TAG DTT75300_EXTRA_MODULE;
struct DTT75300_EXTRA_MODULE_TAG
{
	// DTT-75300 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
	u8 Control4;
};





// MxL5007T extra module
typedef struct MXL5007T_EXTRA_MODULE_TAG MXL5007T_EXTRA_MODULE;

// MxL5007 TunerConfig Struct
typedef struct _MxL5007_TunerConfigS
{
	s32	I2C_Addr;
	s32	Mode;
	s32	IF_Diff_Out_Level;
	s32	Xtal_Freq;
	s32	IF_Freq;
	s32 IF_Spectrum;
	s32	ClkOut_Setting;
    s32	ClkOut_Amp;
	s32 BW_MHz;
	u32 RF_Freq_Hz;

	// Additional definition
	TUNER_MODULE *pTuner;

} MxL5007_TunerConfigS;

// MxL5007T bandwidth mode setting function pointer
typedef s32
(*MXL5007T_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

// MxL5007T bandwidth mode getting function pointer
typedef s32
(*MXL5007T_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

// MxL5007T extra module
struct MXL5007T_EXTRA_MODULE_TAG
{
	// MxL5007T extra variables
	s32 LoopThroughMode;
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;

	// MxL5007T MaxLinear-defined structure
	MxL5007_TunerConfigS *pTunerConfigS;
	MxL5007_TunerConfigS TunerConfigSMemory;

	// MxL5007T extra function pointers
	MXL5007T_FP_SET_BANDWIDTH_MODE   SetBandwidthMode;
	MXL5007T_FP_GET_BANDWIDTH_MODE   GetBandwidthMode;
};





// VA1T1ED6093 extra module
typedef struct VA1T1ED6093_EXTRA_MODULE_TAG VA1T1ED6093_EXTRA_MODULE;
struct VA1T1ED6093_EXTRA_MODULE_TAG
{
	// VA1T1ED6093 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





/// TUA8010 extra module
typedef struct TUA8010_EXTRA_MODULE_TAG TUA8010_EXTRA_MODULE;

// Extra manipulaing function
typedef s32
(*TUA8010_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

typedef s32
(*TUA8010_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

typedef s32
(*TUA8010_FP_GET_REG_BYTES_WITH_REG_ADDR)(
	TUNER_MODULE *pTuner,
	u8 DeviceAddr,
	u8 RegAddr,
	u8 *pReadingByte,
	u8 ByteNum
	);

// TUA8010 extra module
struct TUA8010_EXTRA_MODULE_TAG
{
	// TUA8010 extra variables
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;

	// TUA8010 extra function pointers
	TUA8010_FP_SET_BANDWIDTH_MODE            SetBandwidthMode;
	TUA8010_FP_GET_BANDWIDTH_MODE            GetBandwidthMode;
	TUA8010_FP_GET_REG_BYTES_WITH_REG_ADDR   GetRegBytesWithRegAddr;
};





// E4000 extra module
typedef struct E4000_EXTRA_MODULE_TAG E4000_EXTRA_MODULE;

// E4000 register byte getting function pointer
typedef s32
(*E4000_FP_GET_REG_BYTE)(
	TUNER_MODULE *pTuner,
	u8 RegAddr,
	u8 *pReadingByte
	);

// E4000 bandwidth Hz setting function pointer
typedef s32
(*E4000_FP_SET_BANDWIDTH_HZ)(
	TUNER_MODULE *pTuner,
	u64 BandwidthHz
	);

// E4000 bandwidth Hz getting function pointer
typedef s32
(*E4000_FP_GET_BANDWIDTH_HZ)(
	TUNER_MODULE *pTuner,
	u64 *pBandwidthHz
	);

// E4000 extra module
struct E4000_EXTRA_MODULE_TAG
{
	// E4000 extra variables
	u64 CrystalFreqHz;
	s32 BandwidthHz;
	s32 IsBandwidthHzSet;

	// E4000 extra function pointers
	E4000_FP_GET_REG_BYTE       GetRegByte;
	E4000_FP_SET_BANDWIDTH_HZ   SetBandwidthHz;
	E4000_FP_GET_BANDWIDTH_HZ   GetBandwidthHz;
};





// DCT-70704 extra module
typedef struct DCT70704_EXTRA_MODULE_TAG DCT70704_EXTRA_MODULE;
struct DCT70704_EXTRA_MODULE_TAG
{
	// DCT-70704 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 BandSwitch;
	u8 Control2;
};





/// MT2063 extra module
typedef struct MT2063_EXTRA_MODULE_TAG MT2063_EXTRA_MODULE;

// MT2063 handle openning function pointer
typedef s32
(*MT2063_FP_OPEN_HANDLE)(
	TUNER_MODULE *pTuner
	);

// MT2063 handle closing function pointer
typedef s32
(*MT2063_FP_CLOSE_HANDLE)(
	TUNER_MODULE *pTuner
	);

// MT2063 handle getting function pointer
typedef void
(*MT2063_FP_GET_HANDLE)(
	TUNER_MODULE *pTuner,
	void **pDeviceHandle
	);

// MT2063 IF frequency setting function pointer
typedef s32
(*MT2063_FP_SET_IF_FREQ_HZ)(
	TUNER_MODULE *pTuner,
	u64 IfFreqHz
	);

// MT2063 IF frequency getting function pointer
typedef s32
(*MT2063_FP_GET_IF_FREQ_HZ)(
	TUNER_MODULE *pTuner,
	u64 *pIfFreqHz
	);

// MT2063 bandwidth setting function pointer
typedef s32
(*MT2063_FP_SET_BANDWIDTH_HZ)(
	TUNER_MODULE *pTuner,
	u64 BandwidthHz
	);

// MT2063 bandwidth getting function pointer
typedef s32
(*MT2063_FP_GET_BANDWIDTH_HZ)(
	TUNER_MODULE *pTuner,
	u64 *pBandwidthHz
	);

// MT2063 extra module
struct MT2063_EXTRA_MODULE_TAG
{
	// MT2063 extra variables
	void *DeviceHandle;
	s32 StandardMode;
	u64 VgaGc;

	u64 IfFreqHz;
	u64 BandwidthHz;

	s32 IsIfFreqHzSet;
	s32 IsBandwidthHzSet;

	// MT2063 extra function pointers
	MT2063_FP_OPEN_HANDLE        OpenHandle;
	MT2063_FP_CLOSE_HANDLE       CloseHandle;
	MT2063_FP_GET_HANDLE         GetHandle;
	MT2063_FP_SET_IF_FREQ_HZ     SetIfFreqHz;
	MT2063_FP_GET_IF_FREQ_HZ     GetIfFreqHz;
	MT2063_FP_SET_BANDWIDTH_HZ   SetBandwidthHz;
	MT2063_FP_GET_BANDWIDTH_HZ   GetBandwidthHz;
};





// FC0012 extra module
typedef struct FC0012_EXTRA_MODULE_TAG FC0012_EXTRA_MODULE;

// FC0012 bandwidth mode setting function pointer
typedef s32
(*FC0012_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

// FC0012 bandwidth mode getting function pointer
typedef s32
(*FC0012_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

// FC0012 extra module
struct FC0012_EXTRA_MODULE_TAG
{
	// FC0012 extra variables
	u64 CrystalFreqHz;
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;

	// FC0012 extra function pointers
	FC0012_FP_SET_BANDWIDTH_MODE   SetBandwidthMode;
	FC0012_FP_GET_BANDWIDTH_MODE   GetBandwidthMode;
};





// TDAG extra module
typedef struct TDAG_EXTRA_MODULE_TAG TDAG_EXTRA_MODULE;
struct TDAG_EXTRA_MODULE_TAG
{
	// TDAG extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// ADMTV804 extra module
typedef struct ADMTV804_EXTRA_MODULE_TAG ADMTV804_EXTRA_MODULE;

// ADMTV804 standard bandwidth mode setting function pointer
typedef s32
(*ADMTV804_FP_SET_STANDARD_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

// ADMTV804 standard bandwidth mode getting function pointer
typedef s32
(*ADMTV804_FP_GET_STANDARD_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

// ADMTV804 RF power level getting function pointer
typedef s32
(*ADMTV804_FP_GET_RF_POWER_LEVEL)(
	TUNER_MODULE *pTuner,
	s64 *pRfPowerLevel
	);

// ADMTV804 extra module
struct ADMTV804_EXTRA_MODULE_TAG
{
	// ADMTV804 extra variables (from ADMTV804 source code)
	u8 REV_INFO;
	u8 g_curBand;
	u8 pddiv3;
	u8 REG24;
	u8 REG2B;
	u8 REG2E;
	u8 REG30;
	u8 REG31;
	u8 REG5A;
	u8 REG61;  // V1.6 added 

	// ADMTV804 extra variables
	u64 CrystalFreqHz;
	s32 StandardBandwidthMode;
	s32 IsStandardBandwidthModeSet;
	s64 RfPowerLevel;

	// ADMTV804 extra function pointers
	ADMTV804_FP_SET_STANDARD_BANDWIDTH_MODE   SetStandardBandwidthMode;
	ADMTV804_FP_GET_STANDARD_BANDWIDTH_MODE   GetStandardBandwidthMode;
	ADMTV804_FP_GET_RF_POWER_LEVEL            GetRfPowerLevel;
};





// MAX3543 extra module
typedef struct MAX3543_EXTRA_MODULE_TAG MAX3543_EXTRA_MODULE;

// MAX3543 bandwidth mode setting function pointer
typedef s32
(*MAX3543_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

// MAX3543 bandwidth mode getting function pointer
typedef s32
(*MAX3543_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

// MAX3543 extra module
struct MAX3543_EXTRA_MODULE_TAG
{
	// MAX3543 extra variables (from MAX3543 source code)
	u16 TFRomCoefs[3][4];
	u16 denominator;   
	u64  fracscale ;
	u16 regs[22];
	u16 IF_Frequency;

	s32 broadcast_standard;
	s32 XTALSCALE;
	s32 XTALREF;
	s32 LOSCALE;


	// MAX3543 extra variables
	u64 CrystalFreqHz;
	s32 StandardMode;
	u64 IfFreqHz;
	s32 OutputMode;
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;

	// MAX3543 extra function pointers
	MAX3543_FP_SET_BANDWIDTH_MODE   SetBandwidthMode;
	MAX3543_FP_GET_BANDWIDTH_MODE   GetBandwidthMode;
};





// TDA18272 extra module
typedef struct TDA18272_EXTRA_MODULE_TAG TDA18272_EXTRA_MODULE;

// TDA18272 standard bandwidth mode setting function pointer
typedef s32
(*TDA18272_FP_SET_STANDARD_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 StandardBandwidthMode
	);

// TDA18272 standard bandwidth mode getting function pointer
typedef s32
(*TDA18272_FP_GET_STANDARD_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pStandardBandwidthMode
	);

// TDA18272 power mode setting function pointer
typedef s32
(*TDA18272_FP_SET_POWER_MODE)(
	TUNER_MODULE *pTuner,
	s32 PowerMode
	);

// TDA18272 power mode getting function pointer
typedef s32
(*TDA18272_FP_GET_POWER_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pPowerMode
	);

// TDA18272 IF frequency getting function pointer
typedef s32
(*TDA18272_FP_GET_IF_FREQ_HZ)(
	TUNER_MODULE *pTuner,
	u64 *pIfFreqHz
	);

// TDA18272 extra module
struct TDA18272_EXTRA_MODULE_TAG
{
	// TDA18272 extra variables
	u64 CrystalFreqHz;
	s32 UnitNo;
	s32 IfOutputVppMode;
	s32 StandardBandwidthMode;
	s32 IsStandardBandwidthModeSet;
	s32 PowerMode;
	s32 IsPowerModeSet;

	// TDA18272 extra function pointers
	TDA18272_FP_SET_STANDARD_BANDWIDTH_MODE   SetStandardBandwidthMode;
	TDA18272_FP_GET_STANDARD_BANDWIDTH_MODE   GetStandardBandwidthMode;
	TDA18272_FP_SET_POWER_MODE                SetPowerMode;
	TDA18272_FP_GET_POWER_MODE                GetPowerMode;
	TDA18272_FP_GET_IF_FREQ_HZ                GetIfFreqHz;
};





// FC0013 extra module
typedef struct FC0013_EXTRA_MODULE_TAG FC0013_EXTRA_MODULE;

// FC0013 bandwidth mode setting function pointer
typedef s32
(*FC0013_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

// FC0013 bandwidth mode getting function pointer
typedef s32
(*FC0013_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

// FC0013 reset IQ LPF BW
typedef s32
(*FC0013_FP_RC_CAL_RESET)(
	TUNER_MODULE *pTuner
	);

// FC0013 increase IQ LPF BW
typedef s32
(*FC0013_FP_RC_CAL_ADD)(
	TUNER_MODULE *pTuner,
	s32 RcValue
	);

// FC0013 extra module
struct FC0013_EXTRA_MODULE_TAG
{
	// FC0013 extra variables
	u64 CrystalFreqHz;
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;

	// FC0013 extra function pointers
	FC0013_FP_SET_BANDWIDTH_MODE   SetBandwidthMode;
	FC0013_FP_GET_BANDWIDTH_MODE   GetBandwidthMode;
	FC0013_FP_RC_CAL_RESET         RcCalReset;
	FC0013_FP_RC_CAL_ADD           RcCalAdd;
};





// VA1E1ED2403 extra module
typedef struct VA1E1ED2403_EXTRA_MODULE_TAG VA1E1ED2403_EXTRA_MODULE;
struct VA1E1ED2403_EXTRA_MODULE_TAG
{
	// VA1E1ED2403 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// Avalon extra module
#define AVALON_RF_REG_MAX_ADDR		0x60
#define AVALON_BB_REG_MAX_ADDR		0x4f

typedef struct _AVALON_CONFIG_STRUCT {
	double RFChannelMHz;
	double dIfFrequencyMHz;
	double f_dac_MHz;
	s32 TVStandard;
} AVALON_CONFIG_STRUCT, *PAVALON_CONFIG_STRUCT;

typedef struct AVALON_EXTRA_MODULE_TAG AVALON_EXTRA_MODULE;

// AVALON standard bandwidth mode setting function pointer
typedef s32
(*AVALON_FP_SET_STANDARD_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 StandardBandwidthMode
	);

// AVALON standard bandwidth mode getting function pointer
typedef s32
(*AVALON_FP_GET_STANDARD_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pStandardBandwidthMode
	);

// AVALON extra module
struct AVALON_EXTRA_MODULE_TAG
{
	// AVALON extra variables (from AVALON source code)
	u8 g_avalon_rf_reg_work_table[AVALON_RF_REG_MAX_ADDR+1];
	u8 g_avalon_bb_reg_work_table[AVALON_BB_REG_MAX_ADDR+1];

	s32
	(*g_avalon_i2c_read_handler)(
		TUNER_MODULE *pTuner,
		u8 DeviceAddr,
		u8 *pReadingBuffer,
		u16 *pByteNum
		);

	s32
	(*g_avalon_i2c_write_handler)(
		TUNER_MODULE *pTuner,
		u8 DeviceAddr,
		u8 *pWritingBuffer,
		u16 *pByteNum
		);

	AVALON_CONFIG_STRUCT AvalonConfig;


	// AVALON extra variables
	u8 AtvDemodDeviceAddr;
	u64 CrystalFreqHz;
	u64 IfFreqHz;
	s32 StandardBandwidthMode;
	s32 IsStandardBandwidthModeSet;

	// AVALON extra function pointers
	AVALON_FP_SET_STANDARD_BANDWIDTH_MODE   SetStandardBandwidthMode;
	AVALON_FP_GET_STANDARD_BANDWIDTH_MODE   GetStandardBandwidthMode;
};





// SutRx201 extra module
typedef struct SUTRE201_EXTRA_MODULE_TAG SUTRE201_EXTRA_MODULE;

// SUTRE201 standard bandwidth mode setting function pointer
typedef s32
(*SUTRE201_FP_SET_STANDARD_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 StandardBandwidthMode
	);

// SUTRE201 standard bandwidth mode getting function pointer
typedef s32
(*SUTRE201_FP_GET_STANDARD_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pStandardBandwidthMode
	);

// SUTRE201 tuner enabling function pointer
typedef s32
(*SUTRE201_FP_ENABLE)(
	TUNER_MODULE *pTuner
	);

// SUTRE201 tuner disabling function pointer
typedef s32
(*SUTRE201_FP_DISABLE)(
	TUNER_MODULE *pTuner
	);

// SUTRE201 tuner IF port mode setting function pointer
typedef s32
(*SUTRE201_FP_SET_IF_PORT_MODE)(
	TUNER_MODULE *pTuner,
	s32 IfPortMode
	);

// SUTRE201 extra module
struct SUTRE201_EXTRA_MODULE_TAG
{
	// SUTRE201 extra variables
	u64 CrystalFreqHz;
	u64 IfFreqHz;
	s32 IfPortMode;
	s32 CountryMode;
	s32 StandardBandwidthMode;
	s32 IsStandardBandwidthModeSet;

	// SUTRE201 extra function pointers
	SUTRE201_FP_SET_STANDARD_BANDWIDTH_MODE   SetStandardBandwidthMode;
	SUTRE201_FP_GET_STANDARD_BANDWIDTH_MODE   GetStandardBandwidthMode;
	SUTRE201_FP_ENABLE                        Enable;
	SUTRE201_FP_DISABLE                       Disable;
	SUTRE201_FP_SET_IF_PORT_MODE              SetIfPortMode;
};





// MR1300 extra module
typedef struct MR1300_EXTRA_MODULE_TAG MR1300_EXTRA_MODULE;
struct MR1300_EXTRA_MODULE_TAG
{
	// MR1300 extra data
	u64 CrystalFreqHz;
};





// TDAC7 extra module
typedef struct TDAC7_EXTRA_MODULE_TAG TDAC7_EXTRA_MODULE;
struct TDAC7_EXTRA_MODULE_TAG
{
	// TDAC7 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// VA1T1ER2094 extra module
typedef struct VA1T1ER2094_EXTRA_MODULE_TAG VA1T1ER2094_EXTRA_MODULE;
struct VA1T1ER2094_EXTRA_MODULE_TAG
{
	// VA1T1ER2094 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// TDAC3 extra module
typedef struct TDAC3_EXTRA_MODULE_TAG TDAC3_EXTRA_MODULE;
struct TDAC3_EXTRA_MODULE_TAG
{
	// TDAC3 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// RT910 extra module
#define RT910_INITIAL_TABLE_LENGTH     25
typedef struct RT910_EXTRA_MODULE_TAG RT910_EXTRA_MODULE;

// RT910 bandwidth mode setting function pointer
typedef s32
(*RT910_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

// RT910 bandwidth mode getting function pointer
typedef s32
(*RT910_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

// RT910 extra module
struct RT910_EXTRA_MODULE_TAG
{
	// RT910 extra variables
	u64 CrystalFreqHz;
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;
	u8 RT910RegsMap[RT910_INITIAL_TABLE_LENGTH];
	u8 RT910BW8MCalib[RT910_INITIAL_TABLE_LENGTH];  // 80MHz for C.F. cali.


	// RT910 extra function pointers
	RT910_FP_SET_BANDWIDTH_MODE   SetBandwidthMode;
	RT910_FP_GET_BANDWIDTH_MODE   GetBandwidthMode;
};





// DTM4C20 extra module
typedef struct DTM4C20_EXTRA_MODULE_TAG DTM4C20_EXTRA_MODULE;
struct DTM4C20_EXTRA_MODULE_TAG
{
	// DTM4C20 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// GTFD32 extra module
typedef struct GTFD32_EXTRA_MODULE_TAG GTFD32_EXTRA_MODULE;
struct GTFD32_EXTRA_MODULE_TAG
{
	// GTFD32 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// GTLP10 extra module
typedef struct GTLP10_EXTRA_MODULE_TAG GTLP10_EXTRA_MODULE;
struct GTLP10_EXTRA_MODULE_TAG
{
	// GTLP10 extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// JSS66T extra module
typedef struct JSS66T_EXTRA_MODULE_TAG JSS66T_EXTRA_MODULE;
struct JSS66T_EXTRA_MODULE_TAG
{
	// JSS66T extra data
	u8 DividerMsb;
	u8 DividerLsb;
	u8 Control1;
	u8 Control2;
	u8 Control3;
};





// FC0013B extra module
typedef struct FC0013B_EXTRA_MODULE_TAG FC0013B_EXTRA_MODULE;

// FC0013B bandwidth mode setting function pointer
typedef s32
(*FC0013B_FP_SET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 BandwidthMode
	);

// FC0013B bandwidth mode getting function pointer
typedef s32
(*FC0013B_FP_GET_BANDWIDTH_MODE)(
	TUNER_MODULE *pTuner,
	s32 *pBandwidthMode
	);

// FC0013B reset IQ LPF BW
typedef s32
(*FC0013B_FP_RC_CAL_RESET)(
	TUNER_MODULE *pTuner
	);

// FC0013B increase IQ LPF BW
typedef s32
(*FC0013B_FP_RC_CAL_ADD)(
	TUNER_MODULE *pTuner,
	s32 RcValue
	);

// FC0013B extra module
struct FC0013B_EXTRA_MODULE_TAG
{
	// FC0013B extra variables
	u64 CrystalFreqHz;
	s32 BandwidthMode;
	s32 IsBandwidthModeSet;

	// FC0013B extra function pointers
	FC0013B_FP_SET_BANDWIDTH_MODE   SetBandwidthMode;
	FC0013B_FP_GET_BANDWIDTH_MODE   GetBandwidthMode;
	FC0013B_FP_RC_CAL_RESET         RcCalReset;
	FC0013B_FP_RC_CAL_ADD           RcCalAdd;
};





/// Tuner module structure
struct TUNER_MODULE_TAG
{
	// Private variables
	s32           TunerType;									///<   Tuner type
	u8 DeviceAddr;									///<   Tuner I2C device address
	u64 RfFreqHz;										///<   Tuner RF frequency in Hz

	s32 IsRfFreqHzSet;											///<   Tuner RF frequency in Hz (setting status)

	union														///<   Tuner extra module used by driving module
	{
		TDCGG052D_EXTRA_MODULE   Tdcgg052d;
		TDCHG001D_EXTRA_MODULE   Tdchg001d;
		TDQE3003A_EXTRA_MODULE   Tdqe3003a;
		DCT7045_EXTRA_MODULE     Dct7045;
		MT2062_EXTRA_MODULE      Mt2062;
		MXL5005S_EXTRA_MODULE    Mxl5005s;
		TDVMH751P_EXTRA_MODULE   Tdvmh751p;
		UBA00AL_EXTRA_MODULE     Uba00al;
		MT2266_EXTRA_MODULE      Mt2266;
		FC2580_EXTRA_MODULE      Fc2580;
		TUA9001_EXTRA_MODULE     Tua9001;
		DTT75300_EXTRA_MODULE    Dtt75300;
		MXL5007T_EXTRA_MODULE    Mxl5007t;
		VA1T1ED6093_EXTRA_MODULE Va1t1ed6093;
		TUA8010_EXTRA_MODULE     Tua8010;
		E4000_EXTRA_MODULE       E4000;
		DCT70704_EXTRA_MODULE    Dct70704;
		MT2063_EXTRA_MODULE      Mt2063;
		FC0012_EXTRA_MODULE      Fc0012;
		TDAG_EXTRA_MODULE        Tdag;
		ADMTV804_EXTRA_MODULE    Admtv804;
		MAX3543_EXTRA_MODULE     Max3543;
		TDA18272_EXTRA_MODULE    Tda18272;
		FC0013_EXTRA_MODULE      Fc0013;
		VA1E1ED2403_EXTRA_MODULE Va1e1ed2403;
		AVALON_EXTRA_MODULE      Avalon;
		SUTRE201_EXTRA_MODULE    Sutre201;
		MR1300_EXTRA_MODULE      Mr1300;
		TDAC7_EXTRA_MODULE       Tdac7;
		VA1T1ER2094_EXTRA_MODULE Va1t1er2094;
		TDAC3_EXTRA_MODULE       Tdac3;
		RT910_EXTRA_MODULE       Rt910;
		DTM4C20_EXTRA_MODULE     Dtm4c20;
		GTFD32_EXTRA_MODULE      Gtfd32;
		GTLP10_EXTRA_MODULE      Gtlp10;
		JSS66T_EXTRA_MODULE      Jss66t;
		FC0013B_EXTRA_MODULE     Fc0013b;
	}
	Extra;

	BASE_INTERFACE_MODULE *pBaseInterface;						///<   Base interface module
	I2C_BRIDGE_MODULE *pI2cBridge;								///<   I2C bridge module


	// Tuner manipulating functions
	TUNER_FP_GET_TUNER_TYPE    GetTunerType;				///<   Tuner type getting function pointer
	TUNER_FP_GET_DEVICE_ADDR   GetDeviceAddr;				///<   Tuner I2C device address getting function pointer

	TUNER_FP_INITIALIZE        Initialize;					///<   Tuner initializing function pointer
	TUNER_FP_SET_RF_FREQ_HZ    SetRfFreqHz;					///<   Tuner RF frequency setting function pointer
	TUNER_FP_GET_RF_FREQ_HZ    GetRfFreqHz;					///<   Tuner RF frequency getting function pointer
};

















#endif
