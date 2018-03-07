/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

//FreeRTOS Headers
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
//Project Headers
#include <main.h>
#include <driver_init.h>
#include <debug_task.h>

/************ DEFINITIONS ***************/

/********* FUNCTION PROTOTYPES **********/
static void task_Debug(void *p);
char char_read(void);
void str_write(const char *s);
static void tx_cb_USART_DEBUG(const struct usart_async_descriptor *const io_descr);
static void rx_cb_USART_DEBUG(const struct usart_async_descriptor *const io_descr);
/******* EXTERN / GLOBAL VARIABLE *******/
bool BLE_DEBUG_ENABLED = false;
bool UI_DEBUG_ENABLED = false;
/*********** LOCAL VARIABLES ************/
static TaskHandle_t xDebug_Task;
struct io_descriptor *io;
char g_debug_recv_buff[5] = "";
uint8_t recv_buff_index = 0;

/****************************************
* Name:
* Arg:
* Return:
* Notes:
*****************************************/
void DEBUG_initTask(void)
{
	usart_async_register_callback(&USART_DEBUG, USART_ASYNC_RXC_CB, rx_cb_USART_DEBUG);
	usart_async_register_callback(&USART_BLE, USART_ASYNC_TXC_CB, tx_cb_USART_DEBUG);
	usart_async_get_io_descriptor(&USART_DEBUG, &io);
	usart_async_enable(&USART_DEBUG);

	if (xTaskCreate(task_Debug, "Debug Task", TASK_Debug_STACK_SIZE, NULL, TASK_Debug_STACK_PRIORITY, xDebug_Task) != pdPASS) {
		while (1) {;}
	}
}

void DEBUG_println(const char * frmt, ...)
{
	char buf[255] = {0};
	va_list args;
	va_start(args, frmt);
	vsnprintf(buf,255,frmt,args);
	va_end(args);
	str_write(buf);
}

void DEBUG_VOID_println()
{
	//not enabled.. do nothing with this string..
}

void str_write(const char *s)
{
	io_write(&USART_DEBUG.io, (const uint8_t *)s, strlen(s));
}

char char_read()
{
	uint8_t tmp;
	while(ERR_TIMEOUT == io_read(&USART_DEBUG.io,&tmp,1))
	{
		;
	}
	return (char)tmp;
}

void task_Debug(void *p)
{
	(void)p;
	char ch = 0;

	vTaskDelay(5/portTICK_PERIOD_MS);
	DEBUG_PRINTLN("DEBUG TASK STARTED \r\n");

	for(;;)
	{
		ch = char_read();
		switch(ch)
		{
			case 'a':
				DEBUG_PRINTLN("I received an a\r\n");
				break;
			case 'b':
				DEBUG_PRINTLN("BLE STATUS CHANGED\r\n");
				BLE_DEBUG_ENABLED = !BLE_DEBUG_ENABLED;
				break;
			case 'i':
				DEBUG_PRINTLN("UI STATUS CHANGED\r\n");
				UI_DEBUG_ENABLED = !UI_DEBUG_ENABLED;
				break;
			default:
				break;
		}
	}
}


static void tx_cb_USART_DEBUG(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

 static void rx_cb_USART_DEBUG(const struct usart_async_descriptor *const io_descr)
{
	//Char received
}
