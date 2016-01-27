/**

@file

@brief   QAM demod default function definition

QAM demod default functions.

*/

#include "qam_demod_base.h"





/**

@see   QAM_DEMOD_FP_SET_REG_PAGE

*/
s32
qam_demod_addr_8bit_default_SetRegPage(
	QAM_DEMOD_MODULE *pDemod,
	u64 PageNo
	)
{
#if 0
	BASE_INTERFACE_MODULE *pBaseInterface;

	u8 DeviceAddr;
	u8 WritingBytes[LEN_2_BYTE];


	// Get base interface.
	pBaseInterface = pDemod->pBaseInterface;


	// Get demod device address.
	pDemod->GetDeviceAddr(pDemod, &DeviceAddr);


	// Set demod register page with page number.
	// Note: The I2C format of demod register page setting is as follows:
	//       start_bit + (DeviceAddr | writing_bit) + QAM_DEMOD_PAGE_REG_ADDR + PageNo + stop_bit
	WritingBytes[0] = QAM_DEMOD_PAGE_REG_ADDR;
	WritingBytes[1] = (u8)PageNo;

	if(pBaseInterface->I2cWrite(pBaseInterface, DeviceAddr, WritingBytes, LEN_2_BYTE) != FUNCTION_SUCCESS)
		goto error_status_set_demod_registers;


	return FUNCTION_SUCCESS;


error_status_set_demod_registers:
	return FUNCTION_ERROR;
#endif
	BASE_INTERFACE_MODULE *pBaseInterface;

	struct dvb_usb_device	*d;

	// Get base interface.
	pBaseInterface = pDemod->pBaseInterface;
	
	pBaseInterface->GetUserDefinedDataPointer(pBaseInterface, (void **)&d);  //add by chialing

	if( mutex_lock_interruptible(&d->usb_mutex) )	goto error;

	 pDemod->CurrentPageNo = PageNo;

	mutex_unlock(&d->usb_mutex);

	return FUNCTION_SUCCESS;

error:

	return FUNCTION_ERROR;

}





/**

@see   QAM_DEMOD_FP_SET_REG_BYTES

*/
s32
qam_demod_addr_8bit_default_SetRegBytes(
	QAM_DEMOD_MODULE *pDemod,
	u8 RegStartAddr,
	const u8 *pWritingBytes,
	u64 ByteNum
	)
{
#if 0
	BASE_INTERFACE_MODULE *pBaseInterface;

	u64 i, j;

	u8 DeviceAddr;
	u8 WritingBuffer[I2C_BUFFER_LEN];
	u64 WritingByteNum, WritingByteNumMax, WritingByteNumRem;
	u8 RegWritingAddr;



	// Get base interface.
	pBaseInterface = pDemod->pBaseInterface;


	// Get demod I2C device address.
	pDemod->GetDeviceAddr(pDemod, &DeviceAddr);


	// Calculate maximum writing byte number.
	WritingByteNumMax = pBaseInterface->I2cWritingByteNumMax - LEN_1_BYTE;


	// Set demod register bytes with writing bytes.
	// Note: Set demod register bytes considering maximum writing byte number.
	for(i = 0; i < ByteNum; i += WritingByteNumMax)
	{
		// Set register writing address.
		RegWritingAddr = (u8)(RegStartAddr + i);

		// Calculate remainder writing byte number.
		WritingByteNumRem = ByteNum - i;

		// Determine writing byte number.
		WritingByteNum = (WritingByteNumRem > WritingByteNumMax) ? WritingByteNumMax : WritingByteNumRem;


		// Set writing buffer.
		// Note: The I2C format of demod register byte setting is as follows:
		//       start_bit + (DeviceAddr | writing_bit) + RegWritingAddr + writing_bytes (WritingByteNum bytes) +
		//       stop_bit
		WritingBuffer[0] = RegWritingAddr;

		for(j = 0; j < WritingByteNum; j++)
			WritingBuffer[LEN_1_BYTE + j] = pWritingBytes[i + j];


		// Set demod register bytes with writing buffer.
		if(pBaseInterface->I2cWrite(pBaseInterface, DeviceAddr, WritingBuffer, WritingByteNum + LEN_1_BYTE) != FUNCTION_SUCCESS)
			goto error_status_set_demod_registers;
	}


	return FUNCTION_SUCCESS;


error_status_set_demod_registers:
	return FUNCTION_ERROR;
#endif
	BASE_INTERFACE_MODULE *pBaseInterface;

	u32 i, j;

	u8 DeviceAddr;
	u8 WritingBuffer[I2C_BUFFER_LEN];
	u8 WritingByteNum, WritingByteNumMax, WritingByteNumRem;
	u8 RegWritingAddr;
	u64 PageNo=0;


	struct dvb_usb_device	*d;

	// Get base interface.
	pBaseInterface = pDemod->pBaseInterface;
	
	pBaseInterface->GetUserDefinedDataPointer(pBaseInterface, (void **)&d);  //add by chialing

	// Get demod I2C device address.
	pDemod->GetDeviceAddr(pDemod, &DeviceAddr);

	PageNo=pDemod->CurrentPageNo;
	// Calculate maximum writing byte number.
	WritingByteNumMax = pBaseInterface->I2cWritingByteNumMax - LEN_1_BYTE;


	// Set demod register bytes with writing bytes.
	// Note: Set demod register bytes considering maximum writing byte number.
	for(i = 0; i < ByteNum; i += WritingByteNumMax)
	{
		// Set register writing address.
		RegWritingAddr = RegStartAddr + i;

		// Calculate remainder writing byte number.
		WritingByteNumRem = ByteNum - i;

		// Determine writing byte number.
		WritingByteNum = (WritingByteNumRem > WritingByteNumMax) ? WritingByteNumMax : WritingByteNumRem;


		// Set writing buffer.

		WritingBuffer[0] = RegWritingAddr;

		for(j = 0; j < WritingByteNum; j++)
			WritingBuffer[LEN_1_BYTE + j] = pWritingBytes[i + j];

		
		// Set demod register bytes with writing buffer.
		if(write_demod_register(d, DeviceAddr, PageNo, WritingBuffer[0], WritingBuffer+1, WritingByteNum))
			goto error_status_set_demod_registers;	

		
	}


	return FUNCTION_SUCCESS;


error_status_set_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_REG_BYTES

*/
s32
qam_demod_addr_8bit_default_GetRegBytes(
	QAM_DEMOD_MODULE *pDemod,
	u8 RegStartAddr,
	u8 *pReadingBytes,
	u64 ByteNum
	)
{
#if 0
	BASE_INTERFACE_MODULE *pBaseInterface;

	u64 i;
	u8 DeviceAddr;
	u64 ReadingByteNum, ReadingByteNumMax, ReadingByteNumRem;
	u8 RegReadingAddr;



	// Get base interface.
	pBaseInterface = pDemod->pBaseInterface;


	// Get demod I2C device address.
	pDemod->GetDeviceAddr(pDemod, &DeviceAddr);


	// Calculate maximum reading byte number.
	ReadingByteNumMax = pBaseInterface->I2cReadingByteNumMax;


	// Get demod register bytes.
	// Note: Get demod register bytes considering maximum reading byte number.
	for(i = 0; i < ByteNum; i += ReadingByteNumMax)
	{
		// Set register reading address.
		RegReadingAddr = (u8)(RegStartAddr + i);

		// Calculate remainder reading byte number.
		ReadingByteNumRem = ByteNum - i;

		// Determine reading byte number.
		ReadingByteNum = (ReadingByteNumRem > ReadingByteNumMax) ? ReadingByteNumMax : ReadingByteNumRem;


		// Set demod register reading address.
		// Note: The I2C format of demod register reading address setting is as follows:
		//       start_bit + (DeviceAddr | writing_bit) + RegReadingAddr + stop_bit
		if(pBaseInterface->I2cWrite(pBaseInterface, DeviceAddr, &RegReadingAddr, LEN_1_BYTE) != FUNCTION_SUCCESS)
			goto error_status_set_demod_register_reading_address;

		// Get demod register bytes.
		// Note: The I2C format of demod register byte getting is as follows:
		//       start_bit + (DeviceAddr | reading_bit) + reading_bytes (ReadingByteNum bytes) + stop_bit
		if(pBaseInterface->I2cRead(pBaseInterface, DeviceAddr, &pReadingBytes[i], ReadingByteNum) != FUNCTION_SUCCESS)
			goto error_status_get_demod_registers;
	}


	return FUNCTION_SUCCESS;


error_status_get_demod_registers:
error_status_set_demod_register_reading_address:
	return FUNCTION_ERROR;
#endif
	BASE_INTERFACE_MODULE *pBaseInterface;

	u32 i;
	u8 DeviceAddr;
	u8 ReadingByteNum, ReadingByteNumMax, ReadingByteNumRem;
	u8 RegReadingAddr;
	u64 PageNo;


	struct dvb_usb_device	*d;

	// Get base interface.
	pBaseInterface = pDemod->pBaseInterface;
	
	pBaseInterface->GetUserDefinedDataPointer(pBaseInterface, (void **)&d);  //add by chialing


	// Get demod I2C device address.
	pDemod->GetDeviceAddr(pDemod, &DeviceAddr);

	PageNo=pDemod->CurrentPageNo;


	// Calculate maximum reading byte number.
	ReadingByteNumMax = pBaseInterface->I2cReadingByteNumMax;


	// Get demod register bytes.
	// Note: Get demod register bytes considering maximum reading byte number.
	for(i = 0; i < ByteNum; i += ReadingByteNumMax)
	{
		// Set register reading address.
		RegReadingAddr = RegStartAddr + i;

		// Calculate remainder reading byte number.
		ReadingByteNumRem = ByteNum - i;

		// Determine reading byte number.
		ReadingByteNum = (ReadingByteNumRem > ReadingByteNumMax) ? ReadingByteNumMax : ReadingByteNumRem;

		// Get demod register bytes.
		if(read_demod_register(d, DeviceAddr, PageNo,  RegReadingAddr,  pReadingBytes, ReadingByteNum))
			goto error_status_get_demod_registers;	

		
	}


	return FUNCTION_SUCCESS;


error_status_get_demod_registers:
//error_status_set_demod_register_reading_address:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_SET_REG_MASK_BITS

*/
s32
qam_demod_addr_8bit_default_SetRegMaskBits(
	QAM_DEMOD_MODULE *pDemod,
	u8 RegStartAddr,
	u8 Msb,
	u8 Lsb,
	const u64 WritingValue
	)
{
	s32 i;

	u8 ReadingBytes[LEN_4_BYTE];
	u8 WritingBytes[LEN_4_BYTE];

	u8 ByteNum;
	u64 Mask;
	u8 Shift;

	u64 Value;


	// Calculate writing byte number according to MSB.
	ByteNum = Msb / BYTE_BIT_NUM + LEN_1_BYTE;


	// Generate mask and shift according to MSB and LSB.
	Mask = 0;

	for(i = Lsb; i < (u8)(Msb + 1); i++)
		Mask |= 0x1 << i;

	Shift = Lsb;


	// Get demod register bytes according to register start adddress and byte number.
	if(pDemod->RegAccess.Addr8Bit.GetRegBytes(pDemod, RegStartAddr, ReadingBytes, ByteNum) != FUNCTION_SUCCESS)
		goto error_status_get_demod_registers;


	// Combine reading bytes into an u32eger value.
	// Note: Put lower address byte on value LSB.
	//       Put upper address byte on value MSB.
	Value = 0;

	for(i = 0; i < ByteNum; i++)
		Value |= (u64)ReadingBytes[i] << (BYTE_SHIFT * i);


	// Reserve u32eger value unmask bit with mask and inlay writing value into it.
	Value &= ~Mask;
	Value |= (WritingValue << Shift) & Mask;


	// Separate u32eger value into writing bytes.
	// Note: Pick up lower address byte from value LSB.
	//       Pick up upper address byte from value MSB.
	for(i = 0; i < ByteNum; i++)
		WritingBytes[i] = (u8)((Value >> (BYTE_SHIFT * i)) & BYTE_MASK);


	// Write demod register bytes with writing bytes.
	if(pDemod->RegAccess.Addr8Bit.SetRegBytes(pDemod, RegStartAddr, WritingBytes, ByteNum) != FUNCTION_SUCCESS)
		goto error_status_set_demod_registers;


	return FUNCTION_SUCCESS;


error_status_get_demod_registers:
error_status_set_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_REG_MASK_BITS

*/
s32
qam_demod_addr_8bit_default_GetRegMaskBits(
	QAM_DEMOD_MODULE *pDemod,
	u8 RegStartAddr,
	u8 Msb,
	u8 Lsb,
	u64 *pReadingValue
	)
{
	s32 i;

	u8 ReadingBytes[LEN_4_BYTE];

	u8 ByteNum;
	u64 Mask;
	u8 Shift;

	u64 Value;


	// Calculate writing byte number according to MSB.
	ByteNum = Msb / BYTE_BIT_NUM + LEN_1_BYTE;


	// Generate mask and shift according to MSB and LSB.
	Mask = 0;

	for(i = Lsb; i < (u8)(Msb + 1); i++)
		Mask |= 0x1 << i;

	Shift = Lsb;


	// Get demod register bytes according to register start adddress and byte number.
	if(pDemod->RegAccess.Addr8Bit.GetRegBytes(pDemod, RegStartAddr, ReadingBytes, ByteNum) != FUNCTION_SUCCESS)
		goto error_status_get_demod_registers;


	// Combine reading bytes into an u32eger value.
	// Note: Put lower address byte on value LSB.
	//       Put upper address byte on value MSB.
	Value = 0;

	for(i = 0; i < ByteNum; i++)
		Value |= (u64)ReadingBytes[i] << (BYTE_SHIFT * i);


	// Get register bits from u32egaer value with mask and shift
	*pReadingValue = (Value & Mask) >> Shift;


	return FUNCTION_SUCCESS;


error_status_get_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_SET_REG_BITS

*/
s32
qam_demod_addr_8bit_default_SetRegBits(
	QAM_DEMOD_MODULE *pDemod,
	s32 RegBitName,
	const u64 WritingValue
	)
{
	u8 RegStartAddr;
	u8 Msb;
	u8 Lsb;


	// Check if register bit name is available.
	if(pDemod->BaseRegTable.Addr8Bit[RegBitName].IsAvailable == NO)
		goto error_status_register_bit_name;


	// Get register start address, MSB, and LSB from base register table with register bit name key.
	RegStartAddr = pDemod->BaseRegTable.Addr8Bit[RegBitName].RegStartAddr;
	Msb          = pDemod->BaseRegTable.Addr8Bit[RegBitName].Msb;
	Lsb          = pDemod->BaseRegTable.Addr8Bit[RegBitName].Lsb;


	// Set register mask bits.
	if(pDemod->RegAccess.Addr8Bit.SetRegMaskBits(pDemod, RegStartAddr, Msb, Lsb, WritingValue) != FUNCTION_SUCCESS)
		goto error_status_set_demod_registers;


	return FUNCTION_SUCCESS;


error_status_register_bit_name:
error_status_set_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_REG_BITS

*/
s32
qam_demod_addr_8bit_default_GetRegBits(
	QAM_DEMOD_MODULE *pDemod,
	s32 RegBitName,
	u64 *pReadingValue
	)
{
	u8 RegStartAddr;
	u8 Msb;
	u8 Lsb;


	// Check if register bit name is available.
	if(pDemod->BaseRegTable.Addr8Bit[RegBitName].IsAvailable == NO)
		goto error_status_register_bit_name;


	// Get register start address, MSB, and LSB from base register table with register bit name key.
	RegStartAddr = pDemod->BaseRegTable.Addr8Bit[RegBitName].RegStartAddr;
	Msb          = pDemod->BaseRegTable.Addr8Bit[RegBitName].Msb;
	Lsb          = pDemod->BaseRegTable.Addr8Bit[RegBitName].Lsb;


	// Get register mask bits.
	if(pDemod->RegAccess.Addr8Bit.GetRegMaskBits(pDemod, RegStartAddr, Msb, Lsb, pReadingValue) != FUNCTION_SUCCESS)
		goto error_status_get_demod_registers;


	return FUNCTION_SUCCESS;


error_status_register_bit_name:
error_status_get_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_SET_REG_BITS_WITH_PAGE

*/
s32
qam_demod_addr_8bit_default_SetRegBitsWithPage(
	QAM_DEMOD_MODULE *pDemod,
	s32 RegBitName,
	const u64 WritingValue
	)
{
	u8 PageNo;


	// Get register page number from base register table with register bit name key.
	PageNo = pDemod->BaseRegTable.Addr8Bit[RegBitName].PageNo;


	// Set register page number.
	if(pDemod->RegAccess.Addr8Bit.SetRegPage(pDemod, PageNo) != FUNCTION_SUCCESS)
		goto error_status_set_demod_registers;


	// Set register mask bits with register bit name key.
	if(pDemod->RegAccess.Addr8Bit.SetRegBits(pDemod, RegBitName, WritingValue) != FUNCTION_SUCCESS)
		goto error_status_set_demod_registers;


	return FUNCTION_SUCCESS;


error_status_set_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_REG_BITS_WITH_PAGE

*/
s32
qam_demod_addr_8bit_default_GetRegBitsWithPage(
	QAM_DEMOD_MODULE *pDemod,
	s32 RegBitName,
	u64 *pReadingValue
	)
{
	u8 PageNo;


	// Get register page number from base register table with register bit name key.
	PageNo = pDemod->BaseRegTable.Addr8Bit[RegBitName].PageNo;


	// Set register page number.
	if(pDemod->RegAccess.Addr8Bit.SetRegPage(pDemod, PageNo) != FUNCTION_SUCCESS)
		goto error_status_set_demod_registers;


	// Get register mask bits with register bit name key.
	if(pDemod->RegAccess.Addr8Bit.GetRegBits(pDemod, RegBitName, pReadingValue) != FUNCTION_SUCCESS)
		goto error_status_get_demod_registers;


	return FUNCTION_SUCCESS;


error_status_set_demod_registers:
error_status_get_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_SET_REG_BYTES

*/
s32
qam_demod_addr_16bit_default_SetRegBytes(
	QAM_DEMOD_MODULE *pDemod,
	u16 RegStartAddr,
	const u8 *pWritingBytes,
	u64 ByteNum
	)
{
	BASE_INTERFACE_MODULE *pBaseInterface;

	u64 i, j;

	u8 DeviceAddr;
	u8 WritingBuffer[I2C_BUFFER_LEN];
	u64 WritingByteNum, WritingByteNumMax, WritingByteNumRem;
	u16 RegWritingAddr;



	// Get base interface.
	pBaseInterface = pDemod->pBaseInterface;


	// Get demod I2C device address.
	pDemod->GetDeviceAddr(pDemod, &DeviceAddr);


	// Calculate maximum writing byte number.
	WritingByteNumMax = pBaseInterface->I2cWritingByteNumMax - LEN_1_BYTE;


	// Set demod register bytes with writing bytes.
	// Note: Set demod register bytes considering maximum writing byte number.
	for(i = 0; i < ByteNum; i += WritingByteNumMax)
	{
		// Set register writing address.
		RegWritingAddr = (u16)(RegStartAddr + i);

		// Calculate remainder writing byte number.
		WritingByteNumRem = ByteNum - i;

		// Determine writing byte number.
		WritingByteNum = (WritingByteNumRem > WritingByteNumMax) ? WritingByteNumMax : WritingByteNumRem;


		// Set writing buffer.
		// Note: The I2C format of demod register byte setting is as follows:
		//       start_bit + (DeviceAddr | writing_bit) + RegWritingAddrMsb + RegWritingAddrLsb +
		//       writing_bytes (WritingByteNum bytes) + stop_bit
		WritingBuffer[0] = (RegWritingAddr >> BYTE_SHIFT) & BYTE_MASK;
		WritingBuffer[1] = RegWritingAddr & BYTE_MASK;

		for(j = 0; j < WritingByteNum; j++)
			WritingBuffer[LEN_2_BYTE + j] = pWritingBytes[i + j];


		// Set demod register bytes with writing buffer.
		if(pBaseInterface->I2cWrite(pBaseInterface, DeviceAddr, WritingBuffer, WritingByteNum + LEN_2_BYTE) !=
			FUNCTION_SUCCESS)
			goto error_status_set_demod_registers;
	}


	return FUNCTION_SUCCESS;


error_status_set_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_REG_BYTES

*/
s32
qam_demod_addr_16bit_default_GetRegBytes(
	QAM_DEMOD_MODULE *pDemod,
	u16 RegStartAddr,
	u8 *pReadingBytes,
	u64 ByteNum
	)
{
	BASE_INTERFACE_MODULE *pBaseInterface;

	u64 i;
	u8 DeviceAddr;
	u64 ReadingByteNum, ReadingByteNumMax, ReadingByteNumRem;
	u16 RegReadingAddr;
	u8 WritingBuffer[LEN_2_BYTE];



	// Get base interface.
	pBaseInterface = pDemod->pBaseInterface;


	// Get demod I2C device address.
	pDemod->GetDeviceAddr(pDemod, &DeviceAddr);


	// Calculate maximum reading byte number.
	ReadingByteNumMax = pBaseInterface->I2cReadingByteNumMax;


	// Get demod register bytes.
	// Note: Get demod register bytes considering maximum reading byte number.
	for(i = 0; i < ByteNum; i += ReadingByteNumMax)
	{
		// Set register reading address.
		RegReadingAddr = (u16)(RegStartAddr + i);

		// Calculate remainder reading byte number.
		ReadingByteNumRem = ByteNum - i;

		// Determine reading byte number.
		ReadingByteNum = (ReadingByteNumRem > ReadingByteNumMax) ? ReadingByteNumMax : ReadingByteNumRem;


		// Set demod register reading address.
		// Note: The I2C format of demod register reading address setting is as follows:
		//       start_bit + (DeviceAddr | writing_bit) + RegReadingAddrMsb + RegReadingAddrLsb + stop_bit
		WritingBuffer[0] = (RegReadingAddr >> BYTE_SHIFT) & BYTE_MASK;
		WritingBuffer[1] = RegReadingAddr & BYTE_MASK;

		if(pBaseInterface->I2cWrite(pBaseInterface, DeviceAddr, WritingBuffer, LEN_2_BYTE) != FUNCTION_SUCCESS)
			goto error_status_set_demod_register_reading_address;

		// Get demod register bytes.
		// Note: The I2C format of demod register byte getting is as follows:
		//       start_bit + (DeviceAddr | reading_bit) + reading_bytes (ReadingByteNum bytes) + stop_bit
		if(pBaseInterface->I2cRead(pBaseInterface, DeviceAddr, &pReadingBytes[i], ReadingByteNum) != FUNCTION_SUCCESS)
			goto error_status_get_demod_registers;
	}


	return FUNCTION_SUCCESS;


error_status_get_demod_registers:
error_status_set_demod_register_reading_address:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_SET_REG_MASK_BITS

*/
s32
qam_demod_addr_16bit_default_SetRegMaskBits(
	QAM_DEMOD_MODULE *pDemod,
	u16 RegStartAddr,
	u8 Msb,
	u8 Lsb,
	const u64 WritingValue
	)
{
	s32 i;

	u8 ReadingBytes[LEN_4_BYTE];
	u8 WritingBytes[LEN_4_BYTE];

	u8 ByteNum;
	u64 Mask;
	u8 Shift;

	u64 Value;


	// Calculate writing byte number according to MSB.
	ByteNum = Msb / BYTE_BIT_NUM + LEN_1_BYTE;


	// Generate mask and shift according to MSB and LSB.
	Mask = 0;

	for(i = Lsb; i < (u8)(Msb + 1); i++)
		Mask |= 0x1 << i;

	Shift = Lsb;


	// Get demod register bytes according to register start adddress and byte number.
	if(pDemod->RegAccess.Addr16Bit.GetRegBytes(pDemod, RegStartAddr, ReadingBytes, ByteNum) != FUNCTION_SUCCESS)
		goto error_status_get_demod_registers;


	// Combine reading bytes into an u32eger value.
	// Note: Put lower address byte on value LSB.
	//       Put upper address byte on value MSB.
	Value = 0;

	for(i = 0; i < ByteNum; i++)
		Value |= (u64)ReadingBytes[i] << (BYTE_SHIFT * i);


	// Reserve u32eger value unmask bit with mask and inlay writing value into it.
	Value &= ~Mask;
	Value |= (WritingValue << Shift) & Mask;


	// Separate u32eger value into writing bytes.
	// Note: Pick up lower address byte from value LSB.
	//       Pick up upper address byte from value MSB.
	for(i = 0; i < ByteNum; i++)
		WritingBytes[i] = (u8)((Value >> (BYTE_SHIFT * i)) & BYTE_MASK);


	// Write demod register bytes with writing bytes.
	if(pDemod->RegAccess.Addr16Bit.SetRegBytes(pDemod, RegStartAddr, WritingBytes, ByteNum) != FUNCTION_SUCCESS)
		goto error_status_set_demod_registers;


	return FUNCTION_SUCCESS;


error_status_get_demod_registers:
error_status_set_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_REG_MASK_BITS

*/
s32
qam_demod_addr_16bit_default_GetRegMaskBits(
	QAM_DEMOD_MODULE *pDemod,
	u16 RegStartAddr,
	u8 Msb,
	u8 Lsb,
	u64 *pReadingValue
	)
{
	s32 i;

	u8 ReadingBytes[LEN_4_BYTE];

	u8 ByteNum;
	u64 Mask;
	u8 Shift;

	u64 Value;


	// Calculate writing byte number according to MSB.
	ByteNum = Msb / BYTE_BIT_NUM + LEN_1_BYTE;


	// Generate mask and shift according to MSB and LSB.
	Mask = 0;

	for(i = Lsb; i < (u8)(Msb + 1); i++)
		Mask |= 0x1 << i;

	Shift = Lsb;


	// Get demod register bytes according to register start adddress and byte number.
	if(pDemod->RegAccess.Addr16Bit.GetRegBytes(pDemod, RegStartAddr, ReadingBytes, ByteNum) != FUNCTION_SUCCESS)
		goto error_status_get_demod_registers;


	// Combine reading bytes into an u32eger value.
	// Note: Put lower address byte on value LSB.
	//       Put upper address byte on value MSB.
	Value = 0;

	for(i = 0; i < ByteNum; i++)
		Value |= (u64)ReadingBytes[i] << (BYTE_SHIFT * i);


	// Get register bits from u32egaer value with mask and shift
	*pReadingValue = (Value & Mask) >> Shift;


	return FUNCTION_SUCCESS;


error_status_get_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_SET_REG_BITS

*/
s32
qam_demod_addr_16bit_default_SetRegBits(
	QAM_DEMOD_MODULE *pDemod,
	s32 RegBitName,
	const u64 WritingValue
	)
{
	u16 RegStartAddr;
	u8 Msb;
	u8 Lsb;


	// Check if register bit name is available.
	if(pDemod->BaseRegTable.Addr16Bit[RegBitName].IsAvailable == NO)
		goto error_status_register_bit_name;


	// Get register start address, MSB, and LSB from base register table with register bit name key.
	RegStartAddr = pDemod->BaseRegTable.Addr16Bit[RegBitName].RegStartAddr;
	Msb          = pDemod->BaseRegTable.Addr16Bit[RegBitName].Msb;
	Lsb          = pDemod->BaseRegTable.Addr16Bit[RegBitName].Lsb;


	// Set register mask bits.
	if(pDemod->RegAccess.Addr16Bit.SetRegMaskBits(pDemod, RegStartAddr, Msb, Lsb, WritingValue) != FUNCTION_SUCCESS)
		goto error_status_set_demod_registers;


	return FUNCTION_SUCCESS;


error_status_register_bit_name:
error_status_set_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_REG_BITS

*/
s32
qam_demod_addr_16bit_default_GetRegBits(
	QAM_DEMOD_MODULE *pDemod,
	s32 RegBitName,
	u64 *pReadingValue
	)
{
	u16 RegStartAddr;
	u8 Msb;
	u8 Lsb;


	// Check if register bit name is available.
	if(pDemod->BaseRegTable.Addr16Bit[RegBitName].IsAvailable == NO)
		goto error_status_register_bit_name;


	// Get register start address, MSB, and LSB from base register table with register bit name key.
	RegStartAddr = pDemod->BaseRegTable.Addr16Bit[RegBitName].RegStartAddr;
	Msb          = pDemod->BaseRegTable.Addr16Bit[RegBitName].Msb;
	Lsb          = pDemod->BaseRegTable.Addr16Bit[RegBitName].Lsb;


	// Get register mask bits.
	if(pDemod->RegAccess.Addr16Bit.GetRegMaskBits(pDemod, RegStartAddr, Msb, Lsb, pReadingValue) != FUNCTION_SUCCESS)
		goto error_status_get_demod_registers;


	return FUNCTION_SUCCESS;


error_status_register_bit_name:
error_status_get_demod_registers:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_DEMOD_TYPE

*/
void
qam_demod_default_GetDemodType(
	QAM_DEMOD_MODULE *pDemod,
	s32 *pDemodType
	)
{
	// Get demod type from demod module.
	*pDemodType = pDemod->DemodType;


	return;
}





/**

@see   QAM_DEMOD_FP_GET_DEVICE_ADDR

*/
void
qam_demod_default_GetDeviceAddr(
	QAM_DEMOD_MODULE *pDemod,
	u8 *pDeviceAddr
	)
{
	// Get demod I2C device address from demod module.
	*pDeviceAddr = pDemod->DeviceAddr;


	return;
}





/**

@see   QAM_DEMOD_FP_GET_CRYSTAL_FREQ_HZ

*/
void
qam_demod_default_GetCrystalFreqHz(
	QAM_DEMOD_MODULE *pDemod,
	u64 *pCrystalFreqHz
	)
{
	// Get demod crystal frequency in Hz from demod module.
	*pCrystalFreqHz = pDemod->CrystalFreqHz;


	return;
}





/**

@see   QAM_DEMOD_FP_GET_QAM_MODE

*/
s32
qam_demod_default_GetQamMode(
	QAM_DEMOD_MODULE *pDemod,
	s32 *pQamMode
	)
{
	// Get demod QAM mode from demod module.
	if(pDemod->IsQamModeSet != YES)
		goto error_status_get_demod_qam_mode;

	*pQamMode = pDemod->QamMode;


	return FUNCTION_SUCCESS;


error_status_get_demod_qam_mode:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_SYMBOL_RATE_HZ

*/
s32
qam_demod_default_GetSymbolRateHz(
	QAM_DEMOD_MODULE *pDemod,
	u64 *pSymbolRateHz
	)
{
	// Get demod symbol rate in Hz from demod module.
	if(pDemod->IsSymbolRateHzSet != YES)
		goto error_status_get_demod_symbol_rate;

	*pSymbolRateHz = pDemod->SymbolRateHz;


	return FUNCTION_SUCCESS;


error_status_get_demod_symbol_rate:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_ALPHA_MODE

*/
s32
qam_demod_default_GetAlphaMode(
	QAM_DEMOD_MODULE *pDemod,
	s32 *pAlphaMode
	)
{
	// Get demod alpha mode from demod module.
	if(pDemod->IsAlphaModeSet != YES)
		goto error_status_get_demod_alpha_mode;

	*pAlphaMode = pDemod->AlphaMode;


	return FUNCTION_SUCCESS;


error_status_get_demod_alpha_mode:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_IF_FREQ_HZ

*/
s32
qam_demod_default_GetIfFreqHz(
	QAM_DEMOD_MODULE *pDemod,
	u64 *pIfFreqHz
	)
{
	// Get demod IF frequency in Hz from demod module.
	if(pDemod->IsIfFreqHzSet != YES)
		goto error_status_get_demod_if_frequency;

	*pIfFreqHz = pDemod->IfFreqHz;


	return FUNCTION_SUCCESS;


error_status_get_demod_if_frequency:
	return FUNCTION_ERROR;
}





/**

@see   QAM_DEMOD_FP_GET_SPECTRUM_MODE

*/
s32
qam_demod_default_GetSpectrumMode(
	QAM_DEMOD_MODULE *pDemod,
	s32 *pSpectrumMode
	)
{
	// Get demod spectrum mode from demod module.
	if(pDemod->IsSpectrumModeSet != YES)
		goto error_status_get_demod_spectrum_mode;

	*pSpectrumMode = pDemod->SpectrumMode;


	return FUNCTION_SUCCESS;


error_status_get_demod_spectrum_mode:
	return FUNCTION_ERROR;
}












