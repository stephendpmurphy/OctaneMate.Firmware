//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include "driver_init.h"
#include "FreeRTOS_API.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	system_init();

	/* Replace with your application code */
	while (1) {
	}
}
