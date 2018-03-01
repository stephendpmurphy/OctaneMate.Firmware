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
#include <BLE_task.h>

/************ DEFINITIONS ***************/

/********* FUNCTION PROTOTYPES **********/

/******* EXTERN / GLOBAL VARIABLE *******/

/*********** LOCAL VARIABLES ************/
char g_ble_recv_buff[BLE_USART_BUFFER_SIZE] = "";
char g_ble_tran_buff[BLE_USART_BUFFER_SIZE] = "";

/****************************************
* Name: task_BLE
* Arg: *p
* Return: void
* Notes: Task for BLE 
*****************************************/
void task_BLE(void *p)
{
	(void)p;

	for(;;)
	{
		vTaskDelay(10/portTICK_PERIOD_MS);
	}
}

void BLE_USART_Handler(void)
{

}