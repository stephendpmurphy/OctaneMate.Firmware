//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include "uiAPI.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"
#include "pins.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

void task_ui(void* params)
{
	DEBUG_println("UI Task Started\n\r");
    //Device Manager Code
    while(1)
    {
		gpio_set_pin_level(MCU_STATUS_LED, true);
		vTaskDelay(1000/portTICK_PERIOD_MS);
		gpio_set_pin_level(MCU_STATUS_LED, false);
		vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
