//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdbool.h>
#include "driver_init.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

int main(void)
{
	bool retVal = false;

	/* Initializes MCU, drivers and middleware */
	system_init();

	gpio_set_pin_level(EXT_FLASH_NEN,false);
	gpio_set_pin_level(BT_NEN,false);

	DEBUG_println("This is a test %d", 1);

	retVal = tasks_CreateTask();

	//while(1)
	//{
		//gpio_set_pin_level(MCU_STATUS_LED, true);
		//delay_ms(500/portTICK_PERIOD_MS);
		//gpio_set_pin_level(MCU_STATUS_LED, false);
		//delay_ms(500/portTICK_PERIOD_MS);
	//}

	if(retVal)
	{
		vTaskStartScheduler();
	}

	/* Replace with your application code */
	while (1) {
	}
}

void HardFault_Handler()
{
	while(1){

	}
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	while(1){
		
	}
}
