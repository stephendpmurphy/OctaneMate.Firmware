//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

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
#include <hal_flash.h>
#include <hal_spi_m_sync.h>
#include <hal_usart_async.h>
#include <hal_can_async.h>

extern struct flash_descriptor       FLASH_0;
extern struct spi_m_sync_descriptor  EXT_FLASH_SPI;
extern struct usart_async_descriptor BT_UART;
extern struct usart_async_descriptor DEBUG_UART;
extern struct can_async_descriptor   CAN1_INTF;

void FLASH_0_init(void);
void FLASH_0_CLOCK_init(void);

void EXT_FLASH_SPI_PORT_init(void);
void EXT_FLASH_SPI_CLOCK_init(void);
void EXT_FLASH_SPI_init(void);

void BT_UART_PORT_init(void);
void BT_UART_CLOCK_init(void);
void BT_UART_init(void);

void DEBUG_UART_PORT_init(void);
void DEBUG_UART_CLOCK_init(void);
void DEBUG_UART_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
