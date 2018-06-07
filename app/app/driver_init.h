/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_crc_sync.h>

#include <hal_flash.h>

#include <hal_spi_m_sync.h>
#include <hal_usart_async.h>
#include <hal_usart_async.h>
#include <hal_can_async.h>

extern struct crc_sync_descriptor CRC_0;

extern struct flash_descriptor       FLASH_INSTANCE;
extern struct spi_m_sync_descriptor  SERIAL_FLASH_SPI;
extern struct usart_async_descriptor DEBUG_UART;
extern struct usart_async_descriptor BT_UART;
extern struct can_async_descriptor   CAN_0;

void FLASH_INSTANCE_init(void);
void FLASH_INSTANCE_CLOCK_init(void);

void SERIAL_FLASH_SPI_PORT_init(void);
void SERIAL_FLASH_SPI_CLOCK_init(void);
void SERIAL_FLASH_SPI_init(void);

void DEBUG_UART_PORT_init(void);
void DEBUG_UART_CLOCK_init(void);
void DEBUG_UART_init(void);

void BT_UART_PORT_init(void);
void BT_UART_CLOCK_init(void);
void BT_UART_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
