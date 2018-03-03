/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using USART_BLE to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART_BLE[12] = "Hello World!";

static void tx_cb_USART_BLE(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void USART_BLE_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&USART_BLE, USART_ASYNC_TXC_CB, tx_cb_USART_BLE);
	/*usart_async_register_callback(&USART_BLE, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_BLE, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART_BLE, &io);
	usart_async_enable(&USART_BLE);

	io_write(io, example_USART_BLE, 12);
}

/**
 * Example of using USART_STN to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART_STN[12] = "Hello World!";

static void tx_cb_USART_STN(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void USART_STN_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&USART_STN, USART_ASYNC_TXC_CB, tx_cb_USART_STN);
	/*usart_async_register_callback(&USART_STN, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_STN, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART_STN, &io);
	usart_async_enable(&USART_STN);

	io_write(io, example_USART_STN, 12);
}

/**
 * Example of using USART_DEBUG to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART_DEBUG[12] = "Hello World!";

static void tx_cb_USART_DEBUG(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void USART_DEBUG_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&USART_DEBUG, USART_ASYNC_TXC_CB, tx_cb_USART_DEBUG);
	/*usart_async_register_callback(&USART_DEBUG, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_DEBUG, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART_DEBUG, &io);
	usart_async_enable(&USART_DEBUG);

	io_write(io, example_USART_DEBUG, 12);
}
