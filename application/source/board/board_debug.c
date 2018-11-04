//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "driver_init.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void rxc_cb(const struct usart_async_descriptor *const io_descr);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
static struct io_descriptor *io;

/*******************************************************************************
* Description: Debug board level init.
*
*******************************************************************************/
void brd_debug_init(void)
{
    //Debug UART init
    usart_async_register_callback(&DEBUG_UART, USART_ASYNC_RXC_CB, rxc_cb);
    usart_async_get_io_descriptor(&DEBUG_UART, &io);
    usart_async_enable(&DEBUG_UART);
}

/*******************************************************************************
* Description: Transmission complete callback for the debug UART.
*
*******************************************************************************/
static void rxc_cb(const struct usart_async_descriptor *const io_descr)
{
    //Do nothing..
}

