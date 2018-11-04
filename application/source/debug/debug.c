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

#include "same51j20a.h"
#include "core_cm4.h"
#include "debugAPI.h"
#include "FreeRTOS_API.h"
#include "driver_init.h"
#include "delay.h"
#include "board_debug.h"
#include "BM71_flash_commands.h"
#include "BM71.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void str_write(const char *s);
static void debug_gets(uint8_t* buff, uint8_t len);
static void debug_processCmd(uint8_t* command);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
static SemaphoreHandle_t printf_mutex;
static uint8_t debugInputBuffer[32];

/*******************************************************************************
* Description: All init needed for the debug.
*
*******************************************************************************/
void debug_init(void)
{
	printf_mutex = xSemaphoreCreateMutex();

	if(printf_mutex == NULL)
	{
		DEBUG_halt();
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
static void str_write(const char *s)
{
	io_write(&DEBUG_UART.io, (const uint8_t *)s, strlen(s));

	while(ERR_BUSY == usart_async_get_status(&DEBUG_UART,NULL))
	{
		; //Wait until transmission has completed before allowing the next print to happen
	}
}

/*******************************************************************************
* Description: This function gets characters on the debug lines and constructs
* commands for processing.
*******************************************************************************/
static void debug_gets(uint8_t* buff, uint8_t len)
{
    uint8_t ch;
    uint8_t* buff_ptr = buff;
    uint8_t rx_count = 0;
    uint8_t string_complete = false;
    while(!string_complete)
    {
        while(0x00 == io_read(&DEBUG_UART.io, &ch, 1))
    	{
    		;
    	}
        switch(ch)
        {
        case '\b':
            if (buff_ptr > buff)
            {
                *--buff_ptr = 0;
                rx_count--;
            }
            break;
        case '\n':
        case '\r':
            *buff_ptr = 0;
            string_complete = true;
            break;
        default:
            *buff_ptr++ = ch;
            rx_count++;
        }
        if (rx_count >= len)
        {
            *buff_ptr = 0;
            string_complete = true;
        }
    }
}

/*******************************************************************************
* Description: Command processing for all debug commands is done here.
*
*******************************************************************************/
static void debug_processCmd(uint8_t* command)
{
    if(!strcmp((char*)command, "RESET"))
    {
        DEBUG_println("MCU Reset command received..\n\n\r");
		brd_MsDelay(50);
		NVIC_SystemReset();
    }
	else if(!strcmp((char*)command, "BM71_UPDATE_FLASH"))
	{
		BM71_checkAndUpdateFlash();
		BM71_ResetToAppMode();
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
        debug_gets(debugInputBuffer, 32);
        debug_processCmd(debugInputBuffer);
    }
}
