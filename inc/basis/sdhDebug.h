#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <stdio.h>
#define DEBUG_LEVEL		0
#define DEBUG_SWITCH_ON
#ifdef DEBUG_SWITCH_ON
	#define DPRINTF(format, arg...) printf( format,##arg)
#else 
	#define DPRINTF(format, arg...) 
#endif

#ifdef USE_XENO
#define eprintf(...)
#else
#define eprintf(...) printf (__VA_ARGS__)
#endif

#ifdef DEBUG_SWITCH_ONfff
/** print debug message only if debug message type is enabled...
 *  AND is of correct type AND is at least LWIP_DBG_LEVEL
 */
#define LEVEL_DEBUGF(debug, message) do { \
                               if (debug >= DEBUG_LEVEL) { \
                                 printf(message); \
                                
                               } \
                             } while(0)

#else  /* LWIP_DEBUG */
#define LEVEL_DEBUGF(debug, message) 
#endif /* LWIP_DEBUG */

							 
/**
 * @brief ��ӡ�ȼ�����
 */	

#define 	DDG_EMERG 	0
#define		DDG_ALERT 	1
#define 	DDG_ERR		2
#define		DDG_WARNING	3
#define 	DDG_NOTICE	5
#define		DDG_INFO	6
#define		DDG_DEBUG	7
							 



#endif
