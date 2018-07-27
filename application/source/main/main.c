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
#include "BM71.h"
#include "extFlash.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void FreeRTOS_init(void);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

int main(void)
{
	//Board init
	system_init();

	//Debug init
	debug_init();
	RESET_println("MurphyTechnology OctaneMate v%d.%d.%d - %s %s\n\n\r", PRODUCT_VERSION, HW_VERSION, FW_VERSION, __DATE__, __TIME__);

	//Module init
	extFlash_init();

	//Initialize FreeRTOS and start the scheduler.. Should not return from this function call.
	FreeRTOS_init();

	//Something went wrong.. Stop here.
	DEBUG_halt();
}

void HardFault_Handler()
{
	RESET_println("!!! Hard fault !!!");
	DEBUG_halt();
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	RESET_println("%s overflowed its stack!", pcTaskName);
	DEBUG_halt();
}

static void FreeRTOS_init(void)
{
	//Init all of the Module Tasks
	if( !tasks_CreateTasks() )
	{
		RESET_println("Failed to create task(s)");
		DEBUG_halt();
	}

	//Init all of the Module Queues
	if( !eventQueue_CreateQueues() )
	{
		RESET_println("Failed to create queue(s)");
		DEBUG_halt();
	}

	//Start the FreeRTOS scheduler..
	vTaskStartScheduler();

	//Should never have returned from the above call..
	RESET_println("!!! ERROR !!! Scheduler returned...");
}
