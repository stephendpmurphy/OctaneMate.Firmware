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
static SemaphoreHandle_t printf_mutex;
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

	printf_mutex = xSemaphoreCreateMutex();

	if(printf_mutex == NULL)
	{
		while(1) {;}
	}

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

	if(xTaskGetSchedulerState() != taskSCHEDULER_RUNNING)
	{	
		str_write(buf);
		delay_ms(10); 
		//It seems like the processor is running faster than the USART can grab the data from the buf variable
		//So we end up overwriting the buffer with a new printf before we can finish the previous write.. So a short delay is added
		//Doesn't seem to be a problem below when Tasks are actually running.
	}
	else
	{
		if(xSemaphoreTake(printf_mutex, portMAX_DELAY) == pdPASS)
		{
			str_write(buf);
			xSemaphoreGive(printf_mutex);
		}
	}

}

void DEBUG_VOID_println()
{
	//not enabled.. do nothing with this string..
}

void str_write(const char *s)
{
	while(io_write(&USART_DEBUG.io, (const uint8_t *)s, strlen(s)) == ERR_NO_RESOURCE)
	{
		//TO-DO: Need to see if there is a better way to do this..
		// Even though the Mutex is freed does not mean that the USART
		// is ready to accept another buffer to output
		;//wait for the usart to free up
	}
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
