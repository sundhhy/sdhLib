/*
 * marco.h
 *
 *  Created on: 2016-11-4
 *      Author: Administrator
 */
#ifndef __MARCO_H__
#define __MARCO_H__
#include <stdint.h>

#define LINE_DIF(line_base) (__LINE__ - line_base)

void getCompileDate(uint8_t* pDest,uint8_t dsize);
unsigned char GetCompileMoth( void);
unsigned char GetCompileDay( void);

#endif
