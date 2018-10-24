/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#if 0
#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using EXT_FLASH_SPI to write "Hello World" using the IO abstraction.
 */
static uint8_t example_EXT_FLASH_SPI[12] = "Hello World!";

void EXT_FLASH_SPI_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&EXT_FLASH_SPI, &io);

	spi_m_sync_enable(&EXT_FLASH_SPI);
	io_write(io, example_EXT_FLASH_SPI, 12);
}

/**
 * Example of using BT_UART to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_BT_UART[12] = "Hello World!";

static void tx_cb_BT_UART(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void BT_UART_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&BT_UART, USART_ASYNC_TXC_CB, tx_cb_BT_UART);
	/*usart_async_register_callback(&BT_UART, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&BT_UART, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&BT_UART, &io);
	usart_async_enable(&BT_UART);

	io_write(io, example_BT_UART, 12);
}

/**
 * Example of using DEBUG_UART to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_DEBUG_UART[12] = "Hello World!";

static void tx_cb_DEBUG_UART(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void DEBUG_UART_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&DEBUG_UART, USART_ASYNC_TXC_CB, tx_cb_DEBUG_UART);
	/*usart_async_register_callback(&DEBUG_UART, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&DEBUG_UART, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&DEBUG_UART, &io);
	usart_async_enable(&DEBUG_UART);

	io_write(io, example_DEBUG_UART, 12);
}

void CAN1_INTF_tx_callback(struct can_async_descriptor *const descr)
{
	(void)descr;
}
void CAN1_INTF_rx_callback(struct can_async_descriptor *const descr)
{
	struct can_message msg;
	uint8_t            data[64];
	msg.data = data;
	can_async_read(descr, &msg);
	return;
}

/**
 * Example of using CAN1_INTF to Encrypt/Decrypt datas.
 */
void CAN1_INTF_example(void)
{
	struct can_message msg;
	struct can_filter  filter;
	uint8_t            send_data[4];
	send_data[0] = 0x00;
	send_data[1] = 0x01;
	send_data[2] = 0x02;
	send_data[3] = 0x03;

	msg.id   = 0x45A;
	msg.type = CAN_TYPE_DATA;
	msg.data = send_data;
	msg.len  = 4;
	msg.fmt  = CAN_FMT_STDID;
	can_async_register_callback(&CAN1_INTF, CAN_ASYNC_TX_CB, (FUNC_PTR)CAN1_INTF_tx_callback);
	can_async_enable(&CAN1_INTF);

	/**
	 * CAN1_INTF_tx_callback callback should be invoked after call
	 * can_async_write, and remote device should recieve message with ID=0x45A
	 */
	can_async_write(&CAN1_INTF, &msg);

	msg.id  = 0x100000A5;
	msg.fmt = CAN_FMT_EXTID;
	/**
	 * remote device should recieve message with ID=0x100000A5
	 */
	can_async_write(&CAN1_INTF, &msg);

	/**
	 * CAN1_INTF_rx_callback callback should be invoked after call
	 * can_async_set_filter and remote device send CAN Message with the same
	 * content as the filter.
	 */
	can_async_register_callback(&CAN1_INTF, CAN_ASYNC_RX_CB, (FUNC_PTR)CAN1_INTF_rx_callback);
	filter.id   = 0x469;
	filter.mask = 0;
	can_async_set_filter(&CAN1_INTF, 0, CAN_FMT_STDID, &filter);

	filter.id   = 0x10000096;
	filter.mask = 0;
	can_async_set_filter(&CAN1_INTF, 1, CAN_FMT_EXTID, &filter);
}

#endif
