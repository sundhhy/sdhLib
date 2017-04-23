/**
* @file 		marco.h
* @brief		ʹ�õ���һЩ����صĹ���.
* @details	This is the detail description.
* @author		author
* @date		date
* @version	A001
* @par Copyright (c):
* 		XXX��˾
* @par History:
*	version: author, date, desc\n
*/
#include "basis/marco.h"
#include <stdlib.h>
#include <string.h>



/**
 * @brief  ��ȡ����ʱ��.
 *
 * @details This is a detail description.
 *
 * @param[in]	inArgName input argument description.
 * @param[out]	outArgName output argument description.
 * @retval	OK	�ɹ�
 * @retval	ERROR	����
 */
const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
                            "Sep", "Oct", "Nov", "Dec"};
void getCompileDate(uint8_t* pDest,uint8_t dsize)
{
	char marcoBuf[64];
	//ע�⣺keil5 ����ǣ�Apr 23 2017 - 22:33:42 �������ͱ�����û����֤
	char temp [] = __DATE__;
	unsigned char i;
	unsigned char month = 1, day, year;
	char *ptmp = marcoBuf;

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

	memcpy(pDest,marcoBuf, dsize);


}

//char GetCompileYear()
//{
//	char temp [] = __DATE__;
//	unsigned char i;
//	unsigned char month = 1, day, year;

//	year = atoi(temp + 9);
//	

//	return year;
//}

unsigned char GetCompileMoth(void)
{
	char temp [] = __DATE__;
	unsigned char i;
	unsigned char month = 1;

	
	*(temp + 6) = 0;
	*(temp + 3) = 0;
	for (i = 0; i < 12; i++)
	{
		if (!strcmp(temp, months[i]))
		{
			month = i + 1;
			break;
		}
	}

	return month;
}

unsigned char GetCompileDay( void) 
{
	char temp [] = __DATE__;
	unsigned char day;

	
	*(temp + 6) = 0;
	day = atoi(temp + 4);
	

	return day;
}
