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

/************ DEFINITIONS ***************/
#define RESET_println(...)	_println(__VA_ARGS__);

#ifdef DEBUG_BUILD
#define DEBUG_println(...)	_println(__VA_ARGS__);
#else
#define DEBUG_println(...)
#endif

/************** TYPEDEFS ****************/

/********* FUNCTION PROTOTYPES **********/
void _println(const char *frmt, ...);
void debug_init(void);
void task_debug(void* params);

/******* EXTERN / GLOBAL VARIABLE *******/

#endif /* DEBUG_TASK_H_ */
