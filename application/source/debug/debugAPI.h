//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#ifndef DEBUG_TASK_H_
#define DEBUG_TASK_H_

#include "hpl_reset.h"
#include "FreeRTOS_API.h"

/*-------------- TYPEDEFS ----------------------------------------------------*/
typedef enum
{
    MAIN = 0x00,
    BLE,
    CONFIG,
    DEVMGR,
    UI,
    VEHINTF,
    DEBUG_SRC,
    DEBUG_SOURCE_NULL,
    DEBUG_SOURCE_MAX
} debugSource_t;

/*-------------- DEFINITIONS -------------------------------------------------*/
#ifdef DEBUG_BUILD
#define DEBUG_halt()	__asm__("BKPT")
#else
#define DEBUG_halt()	DEBUG_println("DEBUG HALT - %s %s\n\n\r", __FILE__, __LINE__); while(1);
#endif

/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
void DEBUG_println(debugSource_t source, const char * frmt, ...);
void DEBUG_printNoTimeStamp(debugSource_t source, const char * frmt, ...);
void debug_init(void);
void task_debug(void* params);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

#endif /* DEBUG_TASK_H_ */
