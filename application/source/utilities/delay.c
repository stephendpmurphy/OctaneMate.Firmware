//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include "hal_delay.h"
#include "delay.h"
#include "FreeRTOS_API.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/*******************************************************************************
* Description: Delay in ms. Uses FreeRTOS delay if the scheduler is running.
*
*******************************************************************************/
void brd_MsDelay(uint16_t delay)
{
	if(xTaskGetSchedulerState() != taskSCHEDULER_RUNNING)
	{
		delay_ms(delay);
	}
	else
	{
		vTaskDelay(delay);
	}
}

/*******************************************************************************
* Description: Does a hardway delay for the specified duration in us.
*
*******************************************************************************/
void brd_UsDelay(uint16_t delay)
{
	delay_us(delay);
}
