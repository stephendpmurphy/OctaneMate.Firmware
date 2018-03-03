/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

#ifndef DRIVER_INIT_H_INCLUDED
#define DRIVER_INIT_H_INCLUDED

#include "pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>
#include <hal_usart_async.h>

extern struct usart_async_descriptor USART_BLE;
extern struct usart_async_descriptor USART_STN;
extern struct usart_async_descriptor USART_DEBUG;

void USART_BLE_PORT_init(void);
void USART_BLE_CLOCK_init(void);
void USART_BLE_init(void);

void USART_STN_PORT_init(void);
void USART_STN_CLOCK_init(void);
void USART_STN_init(void);

void USART_DEBUG_PORT_init(void);
void USART_DEBUG_CLOCK_init(void);
void USART_DEBUG_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_H_INCLUDED
