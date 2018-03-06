/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

//FreeRTOS Headers
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
//Project Headers
#include <main.h>
#include <pins.h>
#include <driver_init.h>
#include <debug_task.h>
#include <BLE_task.h>

/************ DEFINITIONS ***************/

/********* FUNCTION PROTOTYPES **********/

/******* EXTERN / GLOBAL VARIABLE *******/

/*********** LOCAL VARIABLES ************/
static TaskHandle_t xBLE_Task;
//char g_ble_recv_buff[BLE_USART_BUFFER_SIZE] = "";
//char g_ble_tran_buff[BLE_USART_BUFFER_SIZE] = "";


void BLE_initTask(void)
{
	if (xTaskCreate(task_BLE, "BLE Task", TASK_BLE_STACK_SIZE, NULL, TASK_BLE_STACK_PRIORITY, xBLE_Task) != pdPASS) {
		while (1) {;}
	}
}

/****************************************
* Name: task_BLE
* Arg: *p
* Return: void
* Notes: Task for BLE 
*****************************************/
void task_BLE(void *p)
{
	(void)p;

	DEBUG_PRINTLN("BLE TASK STARTED \r\n");

	for(;;)
	{
		vTaskDelay(499/portTICK_PERIOD_MS);
		BLE_DEBUG_PRINTLN("BLE TASK RAN \r\n");
	}
}