/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

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
#include <BLE_task.h>
#include <debug_task.h>

/************ DEFINITIONS ***************/

/********* FUNCTION PROTOTYPES **********/
static void _task_UI_Sender(void *p);

/******* EXTERN / GLOBAL VARIABLE *******/


/*********** LOCAL VARIABLES ************/
static TaskHandle_t xUISender_Task;


/****************************************
* Name: main
* Arg: void 
* Return: void
* Notes: main entry to program
*****************************************/
int main(void)
{
	/* Initializes MCU, drivers and middleware */
	system_init();
	DEBUG_initTask();
	UI_initTask();
	BLE_initTask();

	if (xTaskCreate(_task_UI_Sender, "UI Sender Task", TASK_UISender_STACK_SIZE, NULL, TASK_UISender_STACK_PRIORITY, xUISender_Task) != pdPASS) {
		while (1) {;}
	}

	DEBUG_PRINTLN("OctaneMate v%d.%d.%d\r\n", FW_MAJOR, FW_MINOR, FW_BUILD);
	delay_ms(2000);
	vTaskStartScheduler();
}

static void _task_UI_Sender(void *p)
{
	(void)p;
	TickType_t xBlockTime = 5/portTICK_PERIOD_MS;
	UI_Task_Msg TxMsg;
	TxMsg.led = MCU_LED;
	TxMsg.dur = UI_OFF;
	DEBUG_PRINTLN("UI SENDER TASK STARTED \r\n");

	for(;;)
	{
		TxMsg.dur = UI_FAST_FLASH;
		xQueueSend( xUI_Queue, ( void * ) &TxMsg, xBlockTime );
		UI_DEBUG_PRINTLN("FAST SEQUENCE SENT.\r\n");
		vTaskDelay(5000/portTICK_PERIOD_MS);
		
		TxMsg.dur = UI_SLOW_FLASH;
		xQueueSend( xUI_Queue, ( void * ) &TxMsg, xBlockTime );
		UI_DEBUG_PRINTLN("SLOW SEQUENCE SENT.\r\n");
		vTaskDelay(5000/portTICK_PERIOD_MS);
	}
}

void HardFault_Handler()
{
	while(1)
	{

	}
}
