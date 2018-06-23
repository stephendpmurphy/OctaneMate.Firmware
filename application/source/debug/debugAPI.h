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

void DEBUG_initTask(void);
void DEBUG_println(const char *frmt, ...);

void task_debug(void* params);

#endif /* DEBUG_TASK_H_ */
