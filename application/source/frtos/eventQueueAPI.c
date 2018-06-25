//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdbool.h>
#include "eventQueueAPI.h"
#include "eventQueueConfig.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
QueueHandle_t queueHandles[kQUEUE_MAX];

bool eventQueue_CreateQueues(void)
{
    queueHandles[kQUEUE_BLE] =          xQueueCreate(QUEUE_LENGTH_BLE,QUEUE_ENTRY_SIZE_BLE);
    queueHandles[kQUEUE_CONFIG] =       xQueueCreate(QUEUE_LENGTH_CONFIG,QUEUE_ENTRY_SIZE_CONFIG);
    queueHandles[kQUEUE_DEBUG] =        xQueueCreate(QUEUE_LENGTH_DEBUG,QUEUE_ENTRY_SIZE_DEBUG);
    queueHandles[kQUEUE_DEV_MANAGER] =  xQueueCreate(QUEUE_LENGTH_DEV_MANAGER,QUEUE_ENTRY_SIZE_DEV_MANAGER);
    queueHandles[kQUEUE_VEH_INTF] =     xQueueCreate(QUEUE_LENGTH_VEH_INTF,QUEUE_ENTRY_SIZE_VEH_INTF);

    //Do not continue if any of the queues were not created correctly
    for(uint8_t x=0;x<kQUEUE_MAX;x++)
    {
        if(queueHandles[x] == NULL)
        {
            return false;
        }
    }

    return true;
}
