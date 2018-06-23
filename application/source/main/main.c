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
#include "tasksAPI.h"
#include "FreeRTOS_API.h"
#include "debug_API.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

int main(void)
{
	bool retVal = false;

	/* Initializes MCU, drivers and middleware */
	system_init();

	DEBUG_println("This is a test %d", 1);

	retVal = tasks_CreateTask();

	if(retVal)
	{
		vTaskStartScheduler();
	}

	/* Replace with your application code */
	while (1) {
	}
}
