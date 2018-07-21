//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "BM71.h"
#include "FreeRTOS_API.h"
#include "driver_init.h"
#include "debugAPI.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void tx_comp(const struct usart_async_descriptor *const io_descr);
static void rx_comp(const struct usart_async_descriptor *const io_descr);
static void err_cb(const struct usart_async_descriptor *const io_descr);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
struct io_descriptor *io;
BM71_Command_t RxMsg;

static void tx_comp(const struct usart_async_descriptor *const io_descr)
{
	RESET_println("Tx Complete!");
}

static void rx_comp(const struct usart_async_descriptor *const io_descr)
{
	RESET_println("Tx Complete!");
}

static void err_cb(const struct usart_async_descriptor *const io_descr)
{
	RESET_println("Error!");
}

void BM71_init(void)
{
	usart_async_get_io_descriptor(&BT_UART, &io);
	usart_async_register_callback(&BT_UART,USART_ASYNC_ERROR_CB, err_cb);
	usart_async_register_callback(&BT_UART,USART_ASYNC_TXC_CB, tx_comp);
	usart_async_register_callback(&BT_UART,USART_ASYNC_RXC_CB, rx_comp);
	usart_async_enable(&BT_UART);	

	delay_ms(500);
	
	BM71_enterAppMode();
	BM71_writeCommand();
}

void BM71_enterAppMode(void)
{
	//Set Conf P2_0 to High
	gpio_set_pin_level(BT_CONF, true);

	//Pull the reset line low for 1ms
	gpio_set_pin_level(BT_NRST, false);

	//Hold it low for 1ms
	delay_ms(3);

	//Pull the chip back out of reset
	gpio_set_pin_level(BT_NRST, true);

	//Wait for the chip to start up and enter application mode
	delay_ms(25);
}

void BM71_writeCommand(void)
{
	BM71_Command_t TxMsg;
	uint8_t buffer[10] = {0};
	uint8_t recBuff[10] = {0};

	//TxMsg.start = 0xAA;
	//TxMsg.lenMSB = 0x00;
	//TxMsg.lenLSB = 0x00;
	//TxMsg.opCode = READ_LOCAL_INFORMATION;
	//TxMsg.data[0] = 0x01;
	//TxMsg.crc = 0x02;

	buffer[0] = 0xAA; //SOM
	buffer[1] = 0x00; //LEN
	buffer[2] = 0x01; //OPCODE
	buffer[3] = 0x01; //PARAM
	buffer[4] = 0xFE; //CRC

	while(io_write(&BT_UART.io, (const uint8_t *)buffer, 5) == ERR_NO_RESOURCE)
	{
		;
	}
	//buffer[0] = 0x69;
	delay_ms(2000);
	io_read(&BT_UART.io, recBuff, 3);

	RESET_println("Received back byte: %x\n\n\r", recBuff[0]);
	//while(io_write(&BT_UART.io, (const uint8_t *)s, strlen(s)) == ERR_NO_RESOURCE)
	//{
		//TO-DO: Need to see if there is a better way to do this..
		// Even though the Mutex is freed does not mean that the USART
		// is ready to accept another buffer to output
		//;//wait for the usart to free up
	//}
}