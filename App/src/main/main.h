/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

#ifndef MAIN_H_
#define MAIN_H_

/************ DEFINITIONS ***************/
#define FW_MAJOR	0x01
#define FW_MINOR	0x01
#define FW_BUILD	0x00

#define TASK_BLE_STACK_SIZE (1024 / sizeof(portSTACK_TYPE))
#define TASK_UI_STACK_SIZE (1024 / sizeof(portSTACK_TYPE))
#define TASK_UISender_STACK_SIZE (1024 / sizeof(portSTACK_TYPE))
#define TASK_Debug_STACK_SIZE (1024 / sizeof(portSTACK_TYPE))

#define TASK_Debug_STACK_PRIORITY (tskIDLE_PRIORITY + 1)
#define TASK_BLE_STACK_PRIORITY (tskIDLE_PRIORITY + 2)
#define TASK_UI_STACK_PRIORITY (tskIDLE_PRIORITY + 3)
#define TASK_UISender_STACK_PRIORITY (tskIDLE_PRIORITY + 4)

/************** TYPEDEFS ****************/

/********* FUNCTION PROTOTYPES **********/

/******* EXTERN / GLOBAL VARIABLE *******/

#endif /* MAIN_H_ */