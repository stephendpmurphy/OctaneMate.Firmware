//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------
#ifndef TASKSCONFIG_H_
#define TASKSCONFIG_H_

//Task Names
#define TASK_NAME_DEV_MANAGER       "Device Manager"
#define TASK_NAME_BLE               "Bluetooth"
#define TASK_NAME_VEH_INTF          "Vehichle Interface"
#define TASK_NAME_UI                "User Interface"
#define TASK_NAME_CONFIG            "Configuration"
#define TASK_NAME_DEBUG             "Debug Interface"

//Task Stack Size
#define TASK_STACK_SIZE_DEV_MANAGER 4096
#define TASK_STACK_SIZE_BLE         4096
#define TASK_STACK_SIZE_VEH_INTF    4096
#define TASK_STACK_SIZE_UI          4096
#define TASK_STACK_SIZE_CONFIG      4096
#define TASK_STACK_SIZE_DEBUG       4096

//Task Priority
#define TASK_PRIORITY_DEV_MANAGER   3
#define TASK_PRIORITY_BLE           4
#define TASK_PRIORITY_VEH_INTF      4
#define TASK_PRIORITY_UI            5
#define TASK_PRIORITY_CONFIG        1
#define TASK_PRIORITY_DEBUG         1

typedef enum
{
    kTASK_DEV_MANAGER   ,
    kTASK_BLE           ,
    kTASK_VEH_INTF      ,
    kTASK_UI            ,
    kTASK_CONFIG        ,
    kTASK_DEBUG         ,
    kTASK_MAX           ,
    kTASK_NULL
}taskIndex_t;

#endif //TASKSCONFIG_H_
