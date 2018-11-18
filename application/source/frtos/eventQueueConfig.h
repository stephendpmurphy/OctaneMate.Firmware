//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------
#ifndef EVENTQUEUECONFIG_H_
#define EVENTQUEUECONFIG_H_

/*-------------- HEADER INCLUDE FILES ----------------------------------------*/
#include "FreeRTOS_API.h"
#include "eventDef.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
//size of buffer in the event
#define EVENT_BUFFER_MAX_SIZE           256

//Maximum number of bytes in an event entry
#define QUEUE_ENTRY_SIZE_MAX            sizeof(eventMsg_t)

//Lengths must be defined for each queue as QUEUE_LENGTH_ +name
#define QUEUE_LENGTH_BLE                5
#define QUEUE_LENGTH_CONFIG             5
#define QUEUE_LENGTH_DEBUG              5
#define QUEUE_LENGTH_DEV_MANAGER        5
#define QUEUE_LENGTH_VEH_INTF           5

//Any sizes must be defined same as QUEUE_ENTRY_SIZE_ +name
#define QUEUE_ENTRY_SIZE_BLE            QUEUE_ENTRY_SIZE_MAX
#define QUEUE_ENTRY_SIZE_CONFIG         QUEUE_ENTRY_SIZE_MAX
#define QUEUE_ENTRY_SIZE_DEBUG          QUEUE_ENTRY_SIZE_MAX
#define QUEUE_ENTRY_SIZE_DEV_MANAGER    QUEUE_ENTRY_SIZE_MAX
#define QUEUE_ENTRY_SIZE_VEH_INTF       QUEUE_ENTRY_SIZE_MAX
/*-------------- MAPPING DEFINITIONS -----------------------------------------*/
/*-------------- ENUMERATIONS-------------------------------------------------*/
/*-------------- TYPES -------------------------------------------------------*/
//Queue Names must be defined for each queue as kQUEUE_ +ModuleName
typedef enum
{
    kQUEUE_BLE          ,
    kQUEUE_CONFIG       ,
    kQUEUE_DEBUG        ,
    kQUEUE_DEV_MANAGER  ,
    kQUEUE_VEH_INTF     ,
    kQUEUE_MAX          ,
    kQUEUE_NULL         ,
}queueIndex_t;

typedef struct
{
    event_t mainEvent;
    event_t subEvent;
    uint32_t value;
    uint8_t  bufferLen;
    uint8_t  buffer[EVENT_BUFFER_MAX_SIZE];
    queueIndex_t responseQ;
    queueIndex_t destQ;
} eventMsg_t;

#endif //EVENTQUEUECONFIG_H_
