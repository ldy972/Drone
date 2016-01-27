#ifndef __RTL2832U_IOCTL_H__
#define __RTL2832U_IOCTL_H__

#include "rtl2832u_fe.h"
#include "rtl2832u_io.h"

#include "dvbdev.h"


#define FE_RW_SID_CMD     _IOWR('o', 81, struct rtl2832u_ioctl_rwcmd_struct) 
#define FE_RW_DEMOD_INFO  _IOWR('o', 82, struct rtl2832u_ioctl_info_struct)

#define MAX_STD_I2C_BUF_NUM 131



struct rtl2832u_ioctl_rwcmd_struct
{
	s32 cmd_num;
	u8 page;
	u8 dev_i2c_addr;
	u64 reg_addr;
	u8 *data;          
	u32  bytelength;

};

struct rtl2832u_ioctl_info_struct
{
	s32 cmd_num;
	u64 *data;
	u32  data_length;
};

enum FE_RW_DEMOD_DATA_TAG{
		INFO_DATA_VALUE=0,
		INFO_DATA_DEN=1,
		INFO_DEMOD_DATA_LEN=2
};

enum FE_STD_RW_CMD_TAG{
	FE_RW_STD_WR=0,
	FE_RW_STD_RD=1,
	FE_RW_DEMOD_WR=2,
	FE_RW_DEMOD_RD=3,
	FE_RW_STD_P_TEST=4,
	FE_RW_STD_M_TEST=5,
	FE_RW_STD_NUM	
};

enum FE_RW_DEMOD_INFO_TAG{
	FE_GET_SIGN_STRENGTH=0,
	FE_GET_SIGN_QUALITY=1,
	FE_GET_SIGN_LOCK=2,
	FE_GET_DEMOD_BER=3,
	FE_GET_DEMOD_SNR_DB=4,
	FE_GET_DEMOD_TR_PPM=5,
	FE_GET_DEMOD_CR_HZ=6,
	FE_DEMOD_INFO_NUM
};

s32 rtl2832u_ioctl_override(struct dvb_frontend *fe,u32 cmd, void *parg,u32 stage);
	
#endif

