//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include "driver_init.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void rx_cb(const struct usart_async_descriptor *const io_desc);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
static struct io_descriptor *io;

void brd_BM71_init(void)
{
    //Bluetooth UART init
    usart_async_register_callback(&BT_UART, USART_ASYNC_RXC_CB, rx_cb);
    usart_async_get_io_descriptor(&BT_UART, &io);
    usart_async_enable(&BT_UART);
}

/*******************************************************************************
* Description: RX callback for the BM71 UART.
*
*******************************************************************************/
static void rx_cb(const struct usart_async_descriptor *const io_desc)
{

}

/*******************************************************************************
* Description: Set the reset pin to the value passed in.
*
*******************************************************************************/
void brd_BM71_setResetPin(bool en)
{
    //BM71 reset is Active Low.. So invert the bool logic
    gpio_set_pin_level(BT_NRST, en);
}

/*******************************************************************************
* Description: Turn the BM71 on or off based on the passed in value.
* This will account for the fact that the BM71 FET enable is active low.
*******************************************************************************/
void brd_BM71_setPowerEn(bool en)
{
    //BM71 Power FET is Active Low.. So invert the bool logic
    gpio_set_pin_level(BT_NEN, !en);
}

/*******************************************************************************
* Description: Set the BM71 configuration pin to the passed in value.
*
*******************************************************************************/
void BRD_BM71_setConfigPin(bool en)
{
    //BM71 placed in Conf mode when Conf is low after a reset
    gpio_set_pin_level(BT_CONF, en);
}
