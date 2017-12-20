/*
 * os_depend.c
 *
 *  Created on: 2017-1-13
 *      Author: Administrator
 */
#include "os/os_depend.h"
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include <assert.h>
#include <stdio.h>
#include "basis/sdhError.h"

osSemaphoreId sid_Sem0;                             
osSemaphoreDef(rtxSemaphore0); 

osSemaphoreId sid_Sem1;                             
osSemaphoreDef(rtxSemaphore1);                              

osSemaphoreId sid_Sem2;                             
osSemaphoreDef(rtxSemaphore2); 
  
osSemaphoreId sid_Sem3;                             
osSemaphoreDef(rtxSemaphore3); 

osSemaphoreId sid_Sem4;                             
osSemaphoreDef(rtxSemaphore4); 

osSemaphoreId sid_Sem5;                             
osSemaphoreDef(rtxSemaphore5); 

osSemaphoreId sid_Sem6;                             
osSemaphoreDef(rtxSemaphore6);

void delay_s(int sec)
{
	;
}

void delay_ms(int ms)
{
	osDelay(ms);
}

void delay_ns( unsigned long nsec )
{
	;
}

//不能在中断中运行
int get_currenttime(os_time_t *ref_time)
{
	*ref_time = osKernelSysTick(); 
	return RET_OK;

}

void PrintTime(os_time_t *time)
{
	;
}

int cal_timediff_ms( os_time_t *ref_time)
{

	uint32_t tick;
	uint32_t tick_1ms; 
	tick_1ms = osKernelSysTickMicroSec(1);
	tick = osKernelSysTick(); 
	if( tick > *ref_time)
		tick -= *ref_time;
	else
	{
		tick = tick + 0xffffffff - *ref_time;
		
	}
	return tick/tick_1ms;

}

int DiffTimes_ms( os_time_t *p_start, os_time_t *P_end)
{

	uint32_t tick_1ms = osKernelSysTickMicroSec(1); 
	
	if( *P_end > *p_start)
		*P_end -= *p_start;
	else
	{
		*P_end = *P_end + 0xffffffff - *p_start;
		
	}
	return *P_end/tick_1ms;

}

int Sem_init(sem_t *sem)
{
	sem_t s = *sem;
	int ret = RET_OK;
	switch( s)
	{
		case 0:
			sid_Sem0 = osSemaphoreCreate (osSemaphore(rtxSemaphore0), 1);
			if (!sid_Sem0) {
				ret = ERR_OSRSU_UNAVAILABLE;
			}
			osSemaphoreWait( sid_Sem0, 0 );
			break;
		case 1:
			sid_Sem1 = osSemaphoreCreate (osSemaphore(rtxSemaphore1), 1);
			if (!sid_Sem1) {
				ret = ERR_OSRSU_UNAVAILABLE;
			}
			osSemaphoreWait( sid_Sem1, 0 );
			break;
		case 2:
			sid_Sem2 = osSemaphoreCreate (osSemaphore(rtxSemaphore2), 1);
			if (!sid_Sem2) {
				ret = ERR_OSRSU_UNAVAILABLE;
			}
			osSemaphoreWait( sid_Sem2, 0 );
			break;
		case 3:
			sid_Sem3 = osSemaphoreCreate (osSemaphore(rtxSemaphore3), 1);
			if (!sid_Sem3) {
				ret = ERR_OSRSU_UNAVAILABLE;
			}
			osSemaphoreWait( sid_Sem3, 0 );
			break;
		case 4:
			sid_Sem4 = osSemaphoreCreate (osSemaphore(rtxSemaphore4), 1);
			if (!sid_Sem4) {
				ret = ERR_OSRSU_UNAVAILABLE;
			}
			osSemaphoreWait( sid_Sem4, 0 );
			break;
		case 5:
			sid_Sem5 = osSemaphoreCreate (osSemaphore(rtxSemaphore5), 1);
			if (!sid_Sem5) {
				ret = ERR_OSRSU_UNAVAILABLE;
			}
			osSemaphoreWait( sid_Sem5, 0 );
			break;
		case 6:
			sid_Sem6 = osSemaphoreCreate(osSemaphore(rtxSemaphore6), 1);
			if (!sid_Sem6) {
				ret = ERR_OSRSU_UNAVAILABLE;
			}
			ret = osSemaphoreWait( sid_Sem6, 0 );
			break;
		default:
			ret = ERR_BAD_PARAMETER;
			break;
		
	}
	return ret;
	
	
}

int Sem_wait(sem_t *sem, int ms)
{
	
	sem_t s = *sem;
	switch( s)
	{
		case 0:
			return osSemaphoreWait( sid_Sem0, ms );
		case 1:
			return osSemaphoreWait( sid_Sem1, ms );
		case 2:
			return osSemaphoreWait( sid_Sem2, ms );
		case 3:
			return osSemaphoreWait( sid_Sem3, ms );
		case 4:
			return osSemaphoreWait( sid_Sem4, ms );
		case 5:
			return osSemaphoreWait( sid_Sem5, ms );
		case 6:
			return osSemaphoreWait( sid_Sem6, ms );
		default:
			break;
		
	}
	return ERR_BAD_PARAMETER;
}

int Sem_post(sem_t *sem)
{
	sem_t s = *sem;
	int	ret = 0;
	switch( s)
	{
		case 0:
			ret = osSemaphoreRelease( sid_Sem0);
			break;
		case 1:
			ret = osSemaphoreRelease( sid_Sem1);
			break;
		case 2:
			ret = osSemaphoreRelease( sid_Sem2);
			break;
		case 3:
			ret = osSemaphoreRelease( sid_Sem3);
			break;
		case 4:
			ret = osSemaphoreRelease( sid_Sem4);
			break;
		case 5:
			ret = osSemaphoreRelease( sid_Sem5);
		case 6:
			ret = osSemaphoreRelease( sid_Sem6);
			break;
		default:
			return ERR_BAD_PARAMETER;
		
	}
	return ret;
}


int Mutex_init( mutext_t *mutex)
{
	return RET_OK;

}
int Mutex_destory( mutext_t *mutex)
{
	
	
	return RET_OK;
}
int Mutex_lock( mutext_t *mutex)
{
	return RET_OK;
}

int Mutex_trylock( mutext_t *mutex)
{
	return RET_OK;
}

int Mutex_unlock( mutext_t *mutex)
{
	return RET_OK;
}
