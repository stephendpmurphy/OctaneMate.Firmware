/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/
//FreeRTOS Headers
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <queue.h>
//Project Headers
#include <main.h>
#include <pins.h>
#include <driver_init.h>
#include <UI_task.h>


/************ DEFINITIONS ***************/

/********* FUNCTION PROTOTYPES **********/

/******* EXTERN / GLOBAL VARIABLE *******/
QueueHandle_t xUI_Queue;
/*********** LOCAL VARIABLES ************/

/****************************************
* Name: task_UI
* Arg: void
* Return: void
* Notes: Main task for the UI engine
*****************************************/
void task_UI(void)
{
	UI_LED_STATE_t UI_State = UI_OFF;
	TickType_t xBlockTime = 10/portTICK_PERIOD_MS;
	
	while(xUI_Queue == 0)
	{
		//Failed to create queue
	}
	
	for(;;)
	{
		// Receive a message on the created queue.  Block for 10 ticks if a
		// message is not immediately available.
		if( xQueueReceive( xUI_Queue, &( UI_State ), xBlockTime ))
		{
				
		}
		switch((int)UI_State)
		{
			case UI_OFF:
				gpio_set_pin_level(MCU_STATUS_LED, true);
				break;
			case UI_SOLID:
				gpio_set_pin_level(MCU_STATUS_LED, false);
				break;
			case UI_FAST_FLASH:
				vTaskDelay(250/portTICK_PERIOD_MS);
				gpio_toggle_pin_level(MCU_STATUS_LED);
				break;
			case UI_SLOW_FLASH:
				vTaskDelay(1000/portTICK_PERIOD_MS);
				gpio_toggle_pin_level(MCU_STATUS_LED);
				break;
			default:
				gpio_set_pin_level(MCU_STATUS_LED, true);
				break;
		}
	}
}