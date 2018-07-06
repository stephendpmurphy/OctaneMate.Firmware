//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include <stdbool.h>
#include "tasksAPI.h"
#include "tasksConfig.h"
#include "FreeRTOS_API.h"
#include "devMgrAPI.h"
#include "bleAPI.h"
#include "vehIntfAPI.h"
#include "uiAPI.h"
#include "configAPI.h"
#include "debugAPI.h"

//-------------- DEFINITIONS ---------------------------------------------------
//-------------- TYPEDEFS ------------------------------------------------------
//-------------- FUNCTION PROTOTYPES -------------------------------------------
//-------------- VARIABLE DEFINITIONS ------------------------------------------
TaskHandle_t taskHandles[kTASK_MAX];
bool taskCreationResult[kTASK_MAX];


bool tasks_CreateTask(void)
{

    /* Create the task, storing the handle. */
    taskCreationResult[kTASK_DEV_MANAGER] = xTaskCreate(task_devMgr,
                                                        TASK_NAME_DEV_MANAGER,
                                                        TASK_STACK_SIZE_DEV_MANAGER,
                                                        NULL,
                                                        TASK_PRIORITY_DEV_MANAGER,
                                                        &taskHandles[kTASK_DEV_MANAGER] );

    taskCreationResult[kTASK_BLE] =         xTaskCreate(task_ble,
                                                        TASK_NAME_BLE,
                                                        TASK_STACK_SIZE_BLE,
                                                        NULL,
                                                        TASK_PRIORITY_BLE,
                                                        &taskHandles[kTASK_BLE] );

    taskCreationResult[kTASK_VEH_INTF] =    xTaskCreate(task_vehIntf,
                                                        TASK_NAME_VEH_INTF,
                                                        TASK_STACK_SIZE_VEH_INTF,
                                                        NULL,
                                                        TASK_PRIORITY_VEH_INTF,
                                                        &taskHandles[kTASK_VEH_INTF] );

    taskCreationResult[kTASK_UI] =          xTaskCreate(task_ui,
                                                        TASK_NAME_UI,
                                                        TASK_STACK_SIZE_UI,
                                                        NULL,
                                                        TASK_PRIORITY_UI,
                                                        &taskHandles[kTASK_UI] );

    taskCreationResult[kTASK_CONFIG] =      xTaskCreate(task_config,
                                                        TASK_NAME_CONFIG,
                                                        TASK_STACK_SIZE_CONFIG,
                                                        NULL,
                                                        TASK_PRIORITY_CONFIG,
                                                        &taskHandles[kTASK_CONFIG] );

    taskCreationResult[kTASK_DEBUG] =       xTaskCreate(task_debug,
                                                        TASK_NAME_DEBUG,
                                                        TASK_STACK_SIZE_DEBUG,
                                                        NULL,
                                                        TASK_PRIORITY_DEBUG,
                                                        &taskHandles[kTASK_DEBUG] );

    for(uint8_t x=0;x<kTASK_MAX;x++)
    {
	    if(taskCreationResult[x] != pdPASS)
	    {
		    return false;
	    }
    }

    return true;
}
