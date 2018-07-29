//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include "bleAPI.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"
#include "BM71.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/*******************************************************************************
* Description: All module init needed for the BLE
*
*******************************************************************************/
bool ble_init(void)
{
	return true;
}

/*******************************************************************************
* Description: FreeRTOS task for BLE
*
*******************************************************************************/
void task_ble(void* params)
{
	DEBUG_println("BLE Task Started\n\r");

    //BLE Task Code
    while(1)
    {
		vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
