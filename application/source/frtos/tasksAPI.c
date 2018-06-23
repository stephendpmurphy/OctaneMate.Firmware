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

    for(uint8_t x=0;x<kTASK_MAX;x++)
    {
        if(taskCreationResult[x] != pdPASS)
        {
            return false;
        }
    }

    return true;
}
