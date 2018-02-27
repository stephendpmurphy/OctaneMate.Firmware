/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#ifdef EXAMPLE_CODE
#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using USART_BLE to write "Hello World" using the IO abstraction.
 */
void USART_BLE_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_BLE, &io);
	usart_sync_enable(&USART_BLE);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using USART_STN to write "Hello World" using the IO abstraction.
 */
void USART_STN_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_STN, &io);
	usart_sync_enable(&USART_STN);

	io_write(io, (uint8_t *)"Hello World!", 12);
}
#endif
