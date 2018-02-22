/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
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

#include <hal_usart_sync.h>

#include <hal_usart_sync.h>

extern struct usart_sync_descriptor USART_BLE;

extern struct usart_sync_descriptor USART_STN;

void USART_EDBG_PORT_init(void);
void USART_EDBG_CLOCK_init(void);
void USART_EDBG_init(void);

void USART_BLE_PORT_init(void);
void USART_BLE_CLOCK_init(void);
void USART_BLE_init(void);

void USART_STN_PORT_init(void);
void USART_STN_CLOCK_init(void);
void USART_STN_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_H_INCLUDED
