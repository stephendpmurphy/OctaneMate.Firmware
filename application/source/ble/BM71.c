//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdio.h>
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
#include "BM71_app_commands.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
#define CMD_LEN_MSB_INDEX       0x01
#define CMD_LEN_LSB_INDEX       0x02
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
static struct io_descriptor *io;
static char BM71_Firmware_Ver[BM71_FIRMWARE_VERSION_LEN] = {0};
static char BM71_Address[BM71_BLUETOOTH_ADDRESS_LEN] = {0};
static uint8_t BM71_Silicon_ID = 0;
static bool initialized = false;

uint8_t BM71_writeBuffer[147];
uint8_t BM71_readBuffer[147];

/*******************************************************************************
* Description: RX callback for the BM71 UART.
*
*******************************************************************************/
static void rx_cb(const struct usart_async_descriptor *const io_desc)
{

}

/*******************************************************************************
* Description: BM71 module init code.
*
*******************************************************************************/
void BM71_init(void)
{
    bool retVal = false;
	//Bluetooth UART init
	usart_async_register_callback(&BT_UART, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_get_io_descriptor(&BT_UART, &io);
	usart_async_enable(&BT_UART);

    //Turn the BM71 chip on
    BM71_setPowerEn(true);
    //Allow the BM71 to power up
    brd_MsDelay(15);

    //Check BM71 config and see if it needs updated
    retVal = CheckAndUpdateFlash();

    if(retVal)
    {
        //Reset the BM71 module to App mode
        BM71_ResetToAppMode();
        //Read local info from the BM71
        BM71_readLocalInfo();
        //Set the BM71 init flag to true
        initialized = true;
    }
}

/*******************************************************************************
* Description: Read the Silicon ID, Firmware Version, and Bluetooth MAC address
* from the BM71 module.
*******************************************************************************/
void BM71_readLocalInfo(void)
{
    //Load the Read Local Info command into the writeBuffer
    BM71_loadSendBuffer(CMD_readLocalInfo, sizeof(CMD_readLocalInfo));
    //Send the command out, adding one to the length for the CRC
    BM71_sendAppCommand(sizeof(CMD_readLocalInfo));

	snprintf(BM71_Firmware_Ver, BM71_FIRMWARE_VERSION_LEN,
								"%02d%02d%02d%02d",
								BM71_readBuffer[BM71_FIRMWARE_VERSION_OFFSET],
								BM71_readBuffer[BM71_FIRMWARE_VERSION_OFFSET+1],
								BM71_readBuffer[BM71_FIRMWARE_VERSION_OFFSET+2],
								BM71_readBuffer[BM71_FIRMWARE_VERSION_OFFSET+3]);

    snprintf(BM71_Address, BM71_BLUETOOTH_ADDRESS_LEN,
							"%02X%02X%02X%02X%02X%02X",
							BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET],
							BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+1],
							BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+2],
							BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+3],
							BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+4],
							BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+5]);

    BM71_Silicon_ID = BM71_readBuffer[BM71_SILICON_ID_OFFSET];

	//Print out the retrieved moduel info
	DEBUG_println("BM71 Silicoin ID: %d   Address: %s   FW Ver: %s", BM71_Silicon_ID, BM71_Address, BM71_Firmware_Ver);
}

/*******************************************************************************
* Description: Send an App command to BM71 and wait back for a response.
*
*******************************************************************************/
void BM71_sendAppCommand(uint8_t sendSize)
{
    uint16_t msgLen = 0;
    //Clear the Ring and Read Buffers
    usart_async_flush_rx_buffer(&BT_UART);
    BM71_clearReadBuffer();
    //Calculate the CRC for the command and add it to the end of the buffer
    BM71_calculateCRC(BM71_writeBuffer, sendSize);
    //Send the command, adding 1 to the send size to account for the CRC
	while(io_write(&BT_UART.io, (const uint8_t*)BM71_writeBuffer, sendSize+1) == ERR_NO_RESOURCE)
	{
		;
	}
	//Wait a bit before checking the buffer for any response
	brd_MsDelay(15);
	//Read out the response into the receive packet
	io_read(&BT_UART.io, BM71_readBuffer, 3);
    //Calculate the total length that we now need to retrieve from the Ring Buffer
    msgLen = ((uint16_t)BM71_readBuffer[CMD_LEN_MSB_INDEX] << 8) + BM71_readBuffer[CMD_LEN_LSB_INDEX];
    //Grab the remaining data from the ring buffer
    io_read(&BT_UART.io, BM71_readBuffer+3, msgLen+1);
}

/*******************************************************************************
* Description: This calculates the CRC for BM71 App commands. Beginning with
* 0xFF. Step through each byte in the message (excluding the 0xAA), and subtract
* it from 0xFF. Once finished, add 0x01 to the result and append it to the last
* index of the buffer.
*******************************************************************************/
void BM71_calculateCRC(uint8_t *buffer, uint8_t len)
{
    uint8_t crc = 0xFF;

    for(uint8_t x=1;x<len;x++)
    {
        crc -= buffer[x];
    }
    buffer[len] = crc+1;
}

/*******************************************************************************
* Description: Pulse the Reset line low for 2ms.
*
*******************************************************************************/
void BM71_PulseRSTPin(void)
{
	BM71_setResetPin(false);
	//Reset pulse greater than 2ms
	brd_MsDelay(2);
	BM71_setResetPin(true);
}

/*******************************************************************************
* Description: Reset the BM71 module.
*
*******************************************************************************/
void BM71_Reset(void)
{
	BM71_PulseRSTPin();
	brd_MsDelay(50);
	BM71_setConfigPin(true);
	brd_MsDelay(100);
}

/*******************************************************************************
* Description: Reset the BM71 module and place it in Test mode once it starts
* back up.
*******************************************************************************/
void BM71_ResetToTestMode(void)
{
	//Test mode is entered if Conf pin is low after a reset
	BM71_setConfigPin(false);
	BM71_Reset();
}

/*******************************************************************************
* Description: Reset the BM71 module and place it in App mode once it starts
* back up.
*******************************************************************************/
void BM71_ResetToAppMode(void)
{
	//App mode is entered if Conf pin is high after a reset
	BM71_setConfigPin(true);
	BM71_Reset();
}

/*******************************************************************************
* Description: Set the reset pin to the value passed in.
*
*******************************************************************************/
void BM71_setResetPin(bool en)
{
	//BM71 reset is Active Low.. So invert the bool logic
	gpio_set_pin_level(BT_NRST, en);
}

/*******************************************************************************
* Description: Turn the BM71 on or off based on the passed in value.
* This will account for the fact that the BM71 FET enable is active low.
*******************************************************************************/
void BM71_setPowerEn(bool en)
{
	//BM71 Power FET is Active Low.. So invert the bool logic
	gpio_set_pin_level(BT_NEN, !en);
}

/*******************************************************************************
* Description: Set the BM71 configuration pin to the passed in value.
*
*******************************************************************************/
void BM71_setConfigPin(bool en)
{
	//BM71 placed in Conf mode when Conf is low after a reset
	gpio_set_pin_level(BT_CONF, en);
}

/*******************************************************************************
* Description: Clear the global writeBuffer used for BM71 comms.
*
*******************************************************************************/
void BM71_clearWriteBuffer(void)
{
    for(uint8_t i = 0; i < sizeof(BM71_writeBuffer); i++)
    BM71_writeBuffer[i] = 0xFF;
}

/*******************************************************************************
* Description: Clear the global readBuffer used for the BM71 module.
*
*******************************************************************************/
void BM71_clearReadBuffer(void)
{
	for(uint8_t i = 0; i < sizeof(BM71_readBuffer); i++)
	{
		BM71_readBuffer[i] = 0x00;
	}
}

/*******************************************************************************
* Description: Load the writeBuffer with an App command passed in.
*
*******************************************************************************/
void BM71_loadSendBuffer( const uint8_t *command, uint8_t bytes)
{
    BM71_clearWriteBuffer();
	memcpy(BM71_writeBuffer, command, bytes);
}
