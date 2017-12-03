//============================================================================//
//            G L O B A L   D E F I N I T I O N S                             //
//============================================================================//
#include "Communication/smart_bus.h"
//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// module global vars
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// global function prototypes
//------------------------------------------------------------------------------

//============================================================================//
//            P R I V A T E   D E F I N I T I O N S                           //
//============================================================================//

//------------------------------------------------------------------------------
// const defines
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// local types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// local vars
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------

static uint8_t SmBus_crc(uint8_t	*frame);
static int	SmBus_query(uint8_t *frame, OUT uint8_t *chn_num);

//============================================================================//
//            P U B L I C   F U N C T I O N S                                 //
//============================================================================//


//chn_type AI AO 。。。
//错误：负数的错误码
//正确：报文长度
int	SmBus_build_query(uint8_t *frame, int f_size, int chn_type, int chn_num)
{
	smBUs_head_t	*s_head = (smBUs_head_t *)frame;
	smBUs_tail_t	*s_tail = (smBUs_tail_t *)(frame + sizeof(smBUs_head_t));
	uint8_t			sb_xor = 0;
	if(f_size < 7)
		return ERR_MEM_LACK;
	
	s_head->cmd = SMBUS_CMD_QUERY;
	s_head->src_addr = SMBUS_SRC_ADDR;
	s_head->dst_addr = chn_type | chn_num;
	s_head->len = 0xB0;
	sb_xor = SmBus_crc(frame);
	
	s_tail->xor_l = SMBUS_PREFIX_XOR | (sb_xor & 0x0f);
	sb_xor >>=4;
	s_tail->xor_h = SMBUS_PREFIX_XOR | (sb_xor & 0x0f);
	s_tail->end_flag = SMBUS_FLAG_END;
	
	return 7;
}

int	SmBus_decode(IN uint8_t cmd, IN uint8_t *frame, OUT void *result_buf, int buf_szie)
{
	int	ret = RET_OK;
	
	switch(cmd)
	{
		
		case SMBUS_CMD_QUERY:
			ret = SmBus_query(frame, result_buf);
			break;
		default:
			ret = ERR_CMM_ILLEGAL;
			break;
	}
	
	return ret ;
}

//=========================================================================//
//                                                                         //
//          P R I V A T E   D E F I N I T I O N S                          //
//                                                                         //
//=========================================================================//
/// \name Private Functions
/// \{
static uint8_t SmBus_crc(uint8_t	*frame)
{
	smBUs_head_t	*s_head = (smBUs_head_t *)frame;
	uint8_t			check_xor = 0;
	uint8_t			i,crc = 0;
	uint8_t			f_len = s_head->len & 0xf + 4;
	
	for(i = 0; i < f_len; i ++)
		crc ^= frame[i];
	return check_xor;
}


//返回命令字中的错误码
static int SmBus_Cmd_err(uint8_t	cmd)
{
	uint8_t  err_code = cmd & 0x0f;
	if((cmd & 0xf0) != SMBUS_FLAG_ACK)
		return SmBus_e_ack;
	
	switch(err_code)
	{
		case 0:
			return SmBus_ok;
		case 2:
			return SmBus_e_xor;
		case 0xb:
			return SmBus_e_AO_up_limit;
		case 0xc:
			return SmBus_e_AO_floor_limit;
		case 0xd:
			return SmBus_e_mast_xor;
		case 0xf:
			return SmBus_e_timeout;
		default:
			break;
		
	}
	
	return SmBus_e_reserve;
	
}
uint8_t SmBus_Get_crc(IN smBUs_tail_t *tail)
{
	
	uint8_t crc_h = tail->xor_h & 0x0f;
	uint8_t crc_l = tail->xor_l & 0x0f;
	
	return (crc_h << 4) | crc_l;
}

static int SmBus_Check_tail(IN smBUs_tail_t *tail)
{
	if((tail->xor_h & 0xf0) != SMBUS_PREFIX_XOR)
		return ERR_CMM_ILLEGAL;
	if((tail->xor_l & 0xf0) != SMBUS_PREFIX_XOR)
		return ERR_CMM_ILLEGAL;
	if(tail->end_flag != SMBUS_FLAG_END)
		return ERR_CMM_ILLEGAL;
	return RET_OK;
}

//0xc0,0x50,0x10,0xb0,0x90,0x93,0xaf
static int	SmBus_query(uint8_t *frame, OUT uint8_t *chn_num)
{
	
	int				ret = 0;
	smBUs_head_t	*s_head = (smBUs_head_t *)frame;
	smBUs_tail_t	*s_tail = (smBUs_tail_t *)(frame + sizeof(smBUs_head_t));
	uint8_t			rd_crc = 0, cal_crc = 0;
	
	
	ret = SmBus_Check_tail(s_tail);
	if(ret != RET_OK)
		return ret;
	
	if( SmBus_Cmd_err(s_head->cmd) != SmBus_ok)
		return ERR_CMM_CMDERR;
	

	
	cal_crc = SmBus_crc(frame);
	rd_crc = SmBus_Get_crc(s_tail);
	
	if(cal_crc != rd_crc)
		return ERR_CMM_CKECKERR;
	
	*chn_num = s_head->src_addr & 0x0f;
	
	return ret;
}


