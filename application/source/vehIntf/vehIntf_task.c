//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include "vehIntfAPI.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/*******************************************************************************
* Description: FreeRTOS task for the vehichle interface.
*
*******************************************************************************/
void task_vehIntf(void* params)
{
	DEBUG_println(VEHINTF, "Vehicle Interface Task Started\n\r");
    //Vehicle Interface Code
    while(1)
    {
		vTaskDelay(100);
    }
}
