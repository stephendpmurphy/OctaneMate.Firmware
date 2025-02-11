//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------
#ifndef EVENTQUEUEAPI_H_
#define EVENTQUEUEAPI_H_

#include <stdint.h>
#include <stdbool.h>
#include "eventQueueConfig.h"
#include "FreeRTOS_API.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
bool eventQueue_CreateQueues(void);
uint8_t eventQueue_sendMsg(event_t mainEvent, event_t subEvent, uint32_t value, uint16_t bufferLen, uint8_t *buffer, queueIndex_t responseQ, queueIndex_t destQ);
uint8_t eventQueue_rcvMsg(queueIndex_t qIndex, eventMsg_t* ptr);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
extern QueueHandle_t queueHandles[kQUEUE_MAX];

#endif /* EVENTQUEUEAPI_H_ */
