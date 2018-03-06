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
static TaskHandle_t xUI_Task;

void UI_initTask(void)
{
	if (xTaskCreate(task_UI, "UI Task", TASK_UI_STACK_SIZE, NULL, TASK_UI_STACK_PRIORITY, xUI_Task) != pdPASS) {
		while (1) {;}
	}

	xUI_Queue = xQueueCreate(5, sizeof(UI_Task_Msg));	
}

/****************************************
* Name: task_UI
* Arg: void
* Return: void
* Notes: Main task for the UI engine
*****************************************/
void task_UI(void *p)
{
	(void)p;
	uint32_t MCU_LED_Reference = 0;
	uint32_t BLE_LED_Reference = 0;
	UI_LED_DUR_t MCU_LED_DUR = UI_OFF;
	UI_LED_DUR_t BLE_LED_DUR = UI_OFF;
	UI_Task_Msg RxMsg;
	TickType_t xBlockTime = 10/portTICK_PERIOD_MS;
	
	while(xUI_Queue == 0)
	{
		//Failed to create queue
	}
	
	MCU_LED_Reference = xTaskGetTickCount();
	BLE_LED_Reference = xTaskGetTickCount();
	
	for(;;)
	{
		// Receive a message on the created queue.  Block for 10 ticks if a
		// message is not immediately available.
		if( xQueueReceive( xUI_Queue, &( RxMsg ), xBlockTime ))
		{
			if(RxMsg.led == MCU_LED)
			{
				MCU_LED_DUR = RxMsg.dur;
			}
			else if(RxMsg.led == BLE_LED)
			{
				BLE_LED_DUR = RxMsg.dur;
			}
			else
			{
				
			}
		}
		
		if( (xTaskGetTickCount() - MCU_LED_Reference) >= MCU_LED_DUR )
		{
			if( (MCU_LED_DUR != UI_OFF) && (MCU_LED_DUR != UI_SOLID) )
			{
				gpio_toggle_pin_level(MCU_STATUS_LED);
			}
			else if( MCU_LED_DUR == UI_OFF )
			{
				gpio_set_pin_level(MCU_STATUS_LED, true);
			}
			else if( MCU_LED_DUR == UI_SOLID )
			{
				gpio_set_pin_level(MCU_STATUS_LED, false);
			}
			MCU_LED_Reference = xTaskGetTickCount();
		}
		
		if( (xTaskGetTickCount() - BLE_LED_Reference) >= BLE_LED_DUR )
		{
			if( (BLE_LED_DUR != UI_OFF) && (BLE_LED_DUR != UI_SOLID) )
			{
				gpio_toggle_pin_level(BLE_STATUS_LED);
			}
			else if( BLE_LED_DUR == UI_OFF )
			{
				gpio_set_pin_level(BLE_STATUS_LED, true);
			}
			else if( BLE_LED_DUR == UI_SOLID )
			{
				gpio_set_pin_level(BLE_STATUS_LED, false);
			}
			BLE_LED_Reference = xTaskGetTickCount();
		}
		
		vTaskDelay(150/portTICK_PERIOD_MS);
	}
}