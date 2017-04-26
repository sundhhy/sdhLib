/*
 * os_depend.h
 *
 *  Created on: 2017-1-13
 *      Author: Administrator
 */

#ifndef QNX_DEPEND_H_
#define QNX_DEPEND_H_
#include <time.h>
#include <stdint.h>
#include <pthread.h>
#include <errno.h>
typedef struct timespec os_time_t;
typedef pthread_mutex_t mutext_t;

void delay_s(int sec);
void delay_ms(int ms);

int get_currenttime(os_time_t *nowtime);
int cal_timediff_ms( os_time_t *ref_time);

int Mutex_init( mutext_t *mutex);
int Mutex_destory( mutext_t *mutex);
int Mutex_lock( mutext_t *mutex);
int Mutex_trylock( mutext_t *mutex);
int Mutex_unlock( mutext_t *mutex);

#endif /* OS_DEPEND_H_ */
