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
#include "version.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

int main(void)
{
	bool retVal = false;

	/* Initializes MCU, drivers and middleware */
	system_init();
	debug_init();

	gpio_set_pin_level(EXT_FLASH_NEN,false);
	gpio_set_pin_level(BT_NEN,false);

	RESET_println("MurphyTechnology OctaneMate v%d.%d.%d - %s %s\n\n\r", PRODUCT_VERSION, HW_VERSION, FW_VERSION, __DATE__, __TIME__);

	retVal = tasks_CreateTask();

	if(retVal)
	{
		retVal = eventQueue_CreateQueues();
	}
	               
	if(retVal)
	{
		vTaskStartScheduler();
	}

	RESET_println("Scheduler returned. Fault in main!");

	//Something went wrong.. Stop here.
	while (1) {
	}
}

void HardFault_Handler()
{
	RESET_println("!!! Hard fault !!!");
	while(1){

	}
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	RESET_println("%s overflowed its stack!", pcTaskName);
	while(1){
	}
}
