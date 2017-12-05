//---------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#ifndef __INC_SMART_BUS_H__
#define __INC_SMART_BUS_H__
#include <stdint.h>
#include "sdhDef.h"

//------------------------------------------------------------------------------
// check for correct compilation options
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------
#define	SMBUS_CHN_AI		0x50

#define	SMBUS_SRC_ADDR		0x10

#define	SMBUS_PREFIX_LEN		0xB0
#define	SMBUS_PREFIX_XOR		0x90

#define	SMBUS_FLAG_END			0xaf
#define	SMBUS_FLAG_ACK			0xc0


#define SMBUS_CMD_QUERY		0xA1

//------------------------------------------------------------------------------
// typedef
//------------------------------------------------------------------------------
typedef enum {
	SmBus_ok = 0,
	SmBus_e_ack,
	SmBus_e_xor,
	SmBus_e_AO_up_limit,
	SmBus_e_AO_floor_limit,
	SmBus_e_mast_xor,
	SmBus_e_timeout,
	SmBus_e_reserve
}SmBus_err_t;
typedef struct {
	uint8_t		cmd;
	uint8_t		src_addr;
	uint8_t		dst_addr;
	uint8_t		len;		//0xBn		n具体长度
}smBUs_head_t;

typedef struct {

	uint8_t		xor_h;			//异或和
	uint8_t		xor_l;
	uint8_t		end_flag;			//0xaf
}smBUs_tail_t;
//------------------------------------------------------------------------------
// global variable declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// function prototypes
//------------------------------------------------------------------------------
int	SmBus_build_query(uint8_t *frame, int f_size, int chn_type, int chn_num);
int	SmBus_decode(IN uint8_t cmd, IN uint8_t *frame, OUT void *result_buf, int buf_szie);

#endif
//------------ End of file ---------------------------
