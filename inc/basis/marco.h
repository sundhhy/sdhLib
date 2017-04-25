/*
 * marco.h
 *
 *  Created on: 2016-11-4
 *      Author: Administrator
 */
#ifndef __MARCO_H__
#define __MARCO_H__
#include <stdint.h>

#define IN
#define OUT

#define LINE_DIF(line_base) (__LINE__ - line_base)
#define CHECK_BIT( bitmap, num) ( ( (uint8_t *)bitmap)[ num >> 3] & ( 1 << ( num & 0x7)) )
#define SET_BIT( bitmap, num) ( (uint8_t *)bitmap)[ num >> 3] = ( (uint8_t *)bitmap)[ num/8] | ( 1 << ( num & 0x7))
#define CLR_BIT( bitmap, num) ( (uint8_t *)bitmap)[ num>> 3] =  ( (uint8_t *)bitmap)[ num/8] & ~( 1 << ( num & 0x7))

void getCompileDate(uint8_t* pDest,uint8_t dsize);
unsigned char GetCompileMoth( void);
unsigned char GetCompileDay( void);

#endif
