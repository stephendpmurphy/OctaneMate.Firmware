//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "debugAPI.h"
#include "FreeRTOS_API.h"
#include "driver_init.h"
#include "delay.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
void str_write(const char *s);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
static SemaphoreHandle_t printf_mutex;
static struct io_descriptor *io;

/*******************************************************************************
* Description: Transmission complete callback for the debug UART.
*
*******************************************************************************/
static void txc_cb(const struct usart_async_descriptor *const io_descr)
{
	//Do nothing..
}

/*******************************************************************************
* Description: All init needed for the debug.
*
*******************************************************************************/
void debug_init(void)
{
	usart_async_register_callback(&DEBUG_UART, USART_ASYNC_TXC_CB, txc_cb);
	usart_async_get_io_descriptor(&DEBUG_UART, &io);
	usart_async_enable(&DEBUG_UART);

	printf_mutex = xSemaphoreCreateMutex();

	if(printf_mutex == NULL)
	{
		while(1) {;}
	}
}

/*******************************************************************************
* Description: Debug print statement which behaves differently if the print
* happens before or after the FreeRTOS scheduler has started.
*******************************************************************************/
void _println(const char * frmt, ...)
{

	char buf[255] = {0};
	va_list args;
	va_start(args, frmt);
	vsnprintf(buf,255,frmt,args);
	va_end(args);

	if(xTaskGetSchedulerState() != taskSCHEDULER_RUNNING)
	{
		str_write(buf);
		brd_MsDelay(10);
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

/*******************************************************************************
* Description: Low level function that actually sends a passed in string out the
* debug UART.
*******************************************************************************/
void str_write(const char *s)
{
	while(io_write(&DEBUG_UART.io, (const uint8_t *)s, strlen(s)) == ERR_NO_RESOURCE)
	{
		//TO-DO: Need to see if there is a better way to do this..
		// Even though the Mutex is freed does not mean that the USART
		// is ready to accept another buffer to output
		;//wait for the usart to free up
	}
}

/*******************************************************************************
* Description: FreeRTOS task for the debug and test input.
*
*******************************************************************************/
void task_debug(void* params)
{
    while(1)
    {
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
