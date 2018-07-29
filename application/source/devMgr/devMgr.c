//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include "devMgrAPI.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/*******************************************************************************
* Description: FreeRTOS task for the Device Manager functionality.
*
*******************************************************************************/
void task_devMgr(void* params)
{
	DEBUG_println("Device Manager Task Started\n\r");
    //Device Manager Code
    while(1)
    {
		vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
