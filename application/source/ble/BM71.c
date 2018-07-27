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
#include <string.h>

#include "BM71.h"
#include "FreeRTOS_API.h"
#include "driver_init.h"
#include "debugAPI.h"
#include "delay.h"
#include "hpl_usart_sync.h"
#include "BM71_flash_commands.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
#define CMD_LEN_MSB_INDEX       0x01
#define CMD_LEN_LSB_INDEX       0x02
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
void BM71_readLocalInfo(void);

/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
// SOM  -  LMSB  -  LLSB  -  OP CODE  -  PARAMTER  -  CRC
static const uint8_t CMD_readLocalInfo[4] = {0xAA, 0x00, 0x01, 0x01};
uint8_t BM71_writeBuffer[147];
uint8_t BM71_readBuffer[147];
struct io_descriptor *io;

static void rx_cb(const struct usart_async_descriptor *const io_desc)
{

}

void BM71_init(void)
{
	//Bluetooth UART init
	usart_async_register_callback(&BT_UART, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_get_io_descriptor(&BT_UART, &io);
	usart_async_enable(&BT_UART);

	//Turn the BM71 chip on
	BM71_setPowerEn(true);
	//Allow the BM71 to power up
	brd_MsDelay(50);

	//Check BM71 config and see if it needs updated
	CheckAndUpdateFlash();
	//Reset the BM71 module to App mode
	BM71_ResetToAppMode();
	//Read local info from the BM71
	BM71_readLocalInfo();
}

void BM71_readLocalInfo(void)
{
    //Load the Read Local Info command into the writeBuffer
    BM71_loadSendBuffer(CMD_readLocalInfo, sizeof(CMD_readLocalInfo));
    //Send the command out, adding one to the length for the CRC
    BM71_sendAppCommand(BM71_writeBuffer, sizeof(CMD_readLocalInfo), BM71_readBuffer);
}

void BM71_sendAppCommand(uint8_t *sendPacket, uint8_t sendSize, uint8_t *recievePacket)
{
    uint8_t lenLSB = 0;
    uint8_t lenMSB = 0;
    uint16_t msgLen = 0;
    //Clear the Ring and Read Buffers
    usart_async_flush_rx_buffer(&BT_UART);
    BM71_clearReadBuffer();
    //Calculate the CRC for the command and add it to the end of the buffer
    BM71_calculateCRC(sendPacket, sendSize);
    //Send the command, adding 1 to the send size to account for the CRC
	while(io_write(&BT_UART.io, (const uint8_t*)sendPacket, sendSize+1) == ERR_NO_RESOURCE)
	{
		;
	}
	//Wait a bit before checking the buffer for any response
	brd_MsDelay(15);
	//Read out the response into the receive packet
	io_read(&BT_UART.io, recievePacket, 3);
    //Calculate the total length that we now need to retrieve from the Ring Buffer
    lenMSB = recievePacket[CMD_LEN_MSB_INDEX];
    lenLSB = recievePacket[CMD_LEN_LSB_INDEX];
    msgLen = ((uint16_t)lenMSB << 8) + lenLSB;
    //Clear the Read Buffer before grabbing more from the Ring Buffer
    BM71_clearReadBuffer();
    //Grab the remaining data from the ring buffer
    io_read(&BT_UART.io, BM71_readBuffer, msgLen);
    //Print out the retrieved command
    for(uint8_t x=0;x<msgLen;x++)
    {
        DEBUG_println("%x ", BM71_readBuffer[x]);
    }
    DEBUG_println("\n\n\r");
}

void BM71_calculateCRC(uint8_t *buffer, uint8_t len)
{
    uint8_t crc = 0xFF;

    for(uint8_t x=1;x<len;x++)
    {
        crc -= buffer[x];
    }
    buffer[len] = crc+1;
}

void BM71_PulseRSTPin(void)
{
	BM71_setResetPin(false);
	//Reset pulse greater than 2ms
	brd_MsDelay(2);
	BM71_setResetPin(true);
}

void BM71_Reset(void)
{
	BM71_PulseRSTPin();
	brd_MsDelay(50);
	BM71_setConfigPin(true);
	brd_MsDelay(100);
}

void BM71_ResetToTestMode(void)
{
	//Test mode is entered if Conf pin is low after a reset
	BM71_setConfigPin(false);
	BM71_Reset();
}

void BM71_ResetToAppMode(void)
{
	//App mode is entered if Conf pin is high after a reset
	BM71_setConfigPin(true);
	BM71_Reset();
}

void BM71_setResetPin(bool en)
{
	//BM71 reset is Active Low.. So invert the bool logic
	gpio_set_pin_level(BT_NRST, en);
}

void BM71_setPowerEn(bool en)
{
	//BM71 Power FET is Active Low.. So invert the bool logic
	gpio_set_pin_level(BT_NEN, !en);
}

void BM71_setConfigPin(bool en)
{
	//BM71 placed in Conf mode when Conf is low after a reset
	gpio_set_pin_level(BT_CONF, en);
}

void BM71_clearWriteBuffer(void)
{
    for(uint8_t i = 0; i < sizeof(BM71_writeBuffer); i++)
    BM71_writeBuffer[i] = 0xFF;
}

void BM71_clearReadBuffer(void)
{
	for(uint8_t i = 0; i < sizeof(BM71_readBuffer); i++)
	{
		BM71_readBuffer[i] = 0x00;
	}
}

void BM71_loadSendBuffer( const uint8_t *command, uint8_t bytes)
{
    BM71_clearWriteBuffer();
	memcpy(BM71_writeBuffer, command, bytes);
}
