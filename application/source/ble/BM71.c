//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>

#include "BM71.h"
#include "FreeRTOS_API.h"
#include "driver_init.h"
#include "debugAPI.h"
#include "delay.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void BM77_setResetPin(bool en);
static void BM71_setPowerEn(bool en);
static void BM71_setConfigPin(bool en);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
struct io_descriptor *io;
BM71_Command_t RxMsg;

static void txc_cb(const struct usart_async_descriptor *const io_descr)
{
	//Do nothing.. This better fucking work
}

void BM71_init(void)
{
	usart_async_register_callback(&BT_UART, USART_ASYNC_TXC_CB, txc_cb);
	usart_async_get_io_descriptor(&BT_UART, &io);
	usart_async_enable(&BT_UART);

	//Put the BM71 into app mode
	BM71_enterAppMode();
	BM71_writeCommand();
}

void BM71_enterAppMode(void)
{
	//Turn the BM71 chip on
	BM71_setPowerEn(true);

	//Allow the BM71 to power up
	brd_MsDelay(100);

	//Set Conf P2_0 to High
	BM71_setConfigPin(true);

	//Place module in reset for 1ms
	BM77_setResetPin(true);

	//Hold it low for 1ms
	brd_MsDelay(1);

	//Pull module back out of reset
	BM77_setResetPin(false);

	//Wait for the chip to start up and enter application mode
	brd_MsDelay(25);
}

void BM71_writeCommand(void)
{
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

	io_read(&BT_UART.io, recBuff, 3);

	RESET_println("Received back byte: %x\n\n\r", recBuff[0]);
}

static void BM77_setResetPin(bool en)
{
	//BM71 reset is Active Low.. So invert the bool logic
	gpio_set_pin_level(BT_NRST, !en);
}

static void BM71_setPowerEn(bool en)
{
	//BM71 Power FET is Active Low.. So invert the bool logic
	gpio_set_pin_level(BT_NEN,!en);
}

static void BM71_setConfigPin(bool en)
{
	//BM71 placed in Conf mode when Conf is low after a reset
	gpio_set_pin_level(BT_CONF, en);
}
