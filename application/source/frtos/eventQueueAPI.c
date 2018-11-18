//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "eventQueueAPI.h"
#include "eventQueueConfig.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
QueueHandle_t queueHandles[kQUEUE_MAX];

/*******************************************************************************
* Description: FreeRTOS queue init for all of our tasks
*
*******************************************************************************/
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

uint8_t eventQueue_sendMsg(event_t mainEvent, event_t subEvent, uint32_t value, uint16_t bufferLen, uint8_t *buffer, queueIndex_t responseQ, queueIndex_t destQ)
{
    BaseType_t status = false;
    eventMsg_t txMsg = {0};

    if( mainEvent > kEVENT_NULL || subEvent > kEVENT_NULL || destQ > kQUEUE_NULL || bufferLen > EVENT_BUFFER_MAX_SIZE)
    {
        return false;
    }

    txMsg.mainEvent = mainEvent;
    txMsg.subEvent = subEvent;
    txMsg.value = value;
    txMsg.bufferLen = bufferLen;
    memcpy(txMsg.buffer, buffer, bufferLen);
    txMsg.responseQ = responseQ;
    txMsg.destQ = destQ;

    if(__get_IPSR())
    {
        portBASE_TYPE taskToWake = pdFALSE;
        if(pdTRUE == xQueueSendFromISR(queueHandles[destQ], (const void*)&txMsg, &taskToWake))
        {
            if(taskToWake == pdTRUE)
            {
                portYIELD();
            }
            status = true;
        }
        else
        {
            status = false;
        }
    }
    else
    {
        if( pdTRUE == xQueueSend(queueHandles[destQ], (const void*)&txMsg, 10) )
        {
            status = true;
        }
        else
        {
            status = false;
        }
    }

    return (uint8_t)status;
}

uint8_t eventQueue_rcvMsg(queueIndex_t qIndex, eventMsg_t* ptr)
{
    BaseType_t status = false;
    
    if( qIndex < kQUEUE_NULL && ptr )
    {
        if(__get_IPSR())
        {
            portBASE_TYPE taskToWake = pdFALSE;
            if (pdTRUE == xQueueReceiveFromISR(queueHandles[qIndex], ptr, &taskToWake))
            {
                if (pdTRUE == taskToWake)
                {
                    portYIELD(); /*! @Note portYIELD_FROM_ISR( taskToWake ); ???*/
                }
                status = true;
            }
            else
            {
                status = false;
            }
        }
        else
        {
            if( pdTRUE == xQueueReceive(queueHandles[qIndex], ptr, portMAX_DELAY) )
            {
                status = true;
            }
            else
            {
                status = false;
            }
        }
    }
    
    return (uint8_t)status;
}
