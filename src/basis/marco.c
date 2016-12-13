/**
* @file 		marco.h
* @brief		使用到的一些宏相关的功能.
* @details	This is the detail description.
* @author		author
* @date		date
* @version	A001
* @par Copyright (c):
* 		XXX公司
* @par History:
*	version: author, date, desc\n
*/
#include "basis/marco.h"
#include <stdlib.h>
#include <string.h>



static char MarcoBuf[64];
/**
 * @brief  获取编译时间.
 *
 * @details This is a detail description.
 *
 * @param[in]	inArgName input argument description.
 * @param[out]	outArgName output argument description.
 * @retval	OK	成功
 * @retval	ERROR	错误
 */

const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
                            "Sep", "Oct", "Nov", "Dec"};
void getCompileDate(uint8_t* pDest,uint8_t dsize)
{

	char temp [] = __DATE__;
	unsigned char i;
	unsigned char month = 1, day, year;
	char *ptmp = MarcoBuf;

	year = atoi(temp + 9);
	*(temp + 6) = 0;
	day = atoi(temp + 4);
	*(temp + 3) = 0;
	for (i = 0; i < 12; i++)
	{
		if (!strcmp(temp, months[i]))
		{
			month = i + 1;
			break;
		}
	}

	*ptmp++ = (year%100)/10+'0';
	*ptmp++ = year%10+'0';
	*ptmp++ = (month%100)/10+'0';
	*ptmp++ = month%10+'0';
	*ptmp++ = (day%100)/10+'0';
	*ptmp++ = day%10+'0';
	*ptmp++ = '_';
	memcpy(ptmp,__TIME__,strlen(__TIME__));

	memcpy(pDest,MarcoBuf, dsize);


}
