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
#include "board_BM71.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
#define CMD_LEN_MSB_INDEX       0x01
#define CMD_LEN_LSB_INDEX       0x02
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
static char BM71_Firmware_Ver[BM71_FIRMWARE_VERSION_LEN] = {0};
static char BM71_Address[BM71_BLUETOOTH_ADDRESS_LEN] = {0};
static uint8_t BM71_Silicon_ID = 0;
static uint8_t BM71_Status = 0x00;
static char BM71_DeviceName[BM71_MAX_DEVICE_NAME_LEN] = {0};
static bool initialized = false;

uint8_t BM71_writeBuffer[BM71_MAX_COMMAND_LENGTH];
uint8_t BM71_readBuffer[BM71_MAX_COMMAND_LENGTH];

/*******************************************************************************
* Description: BM71 module init code.
*
*******************************************************************************/
void BM71_init(void)
{
    bool retVal = false;

    //Turn the BM71 chip on
    brd_BM71_setPowerEn(true);
    //Allow the BM71 to power up
    brd_MsDelay(15);

    //Check BM71 config and see if it needs updated
    retVal = BM71_checkAndUpdateFlash();
    if(retVal)
    {
        //Reset the BM71 module to App mode
        BM71_ResetToAppMode();
        //Read local info from the BM71
        BM71_readLocalInfo();
        BM71_readDeviceName();
        if(strcmp(BM71_DeviceName, OCTANEMATE_DEVICE_NAME))
        {
            BM71_writeDeviceName();
        }
        if(IDLE_MODE == BM71_readStatus())
        {
            BM71_setAdvertisingEnable(0x01);
        }
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
    BM71_loadWriteBuffer(CMD_readLocalInfo, sizeof(CMD_readLocalInfo));
    //Send the command out
    BM71_sendAppCommand(sizeof(CMD_readLocalInfo));

    snprintf(BM71_Firmware_Ver, 
            BM71_FIRMWARE_VERSION_LEN,
            "%02d.%02d.%02d.%02d",
            BM71_readBuffer[BM71_FIRMWARE_VERSION_OFFSET],
            BM71_readBuffer[BM71_FIRMWARE_VERSION_OFFSET+1],
            BM71_readBuffer[BM71_FIRMWARE_VERSION_OFFSET+2],
            BM71_readBuffer[BM71_FIRMWARE_VERSION_OFFSET+3]);

    snprintf(BM71_Address, 
            BM71_BLUETOOTH_ADDRESS_LEN,
            "%02X:%02X:%02X:%02X:%02X:%02X",
            BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+5],
            BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+4],
            BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+3],
            BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+2],
            BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET+1],
            BM71_readBuffer[BM71_BLUETOOTH_ADDRESS_OFFSET]);

    BM71_Silicon_ID = BM71_readBuffer[BM71_SILICON_ID_OFFSET];

	//Print out the retrieved module info
	DEBUG_println(BLE, "BM71 Silicon ID: %d   MAC Address: %s   FW Ver: %s \n\n\r", BM71_Silicon_ID, BM71_Address, BM71_Firmware_Ver);
}

/*******************************************************************************
* Description: Read the BM71 status.
*
*******************************************************************************/
uint8_t BM71_readStatus(void)
{
    //Load the Read Status command into the writeBuffer
    BM71_loadWriteBuffer(CMD_readBM71Status, sizeof(CMD_readBM71Status));
    //Send the command out
    BM71_sendAppCommand(sizeof(CMD_readBM71Status));

    BM71_Status = BM71_readBuffer[BM71_STATUS_OFFSET];
    DEBUG_println(BLE, "BLE Status: ");
    switch(BM71_Status)
    {
        case SCANNING_MODE:
            DEBUG_printNoTimeStamp(BLE, "SCANNING MODE\n\r");
            break;
        case CONNECTING_MODE:
            DEBUG_printNoTimeStamp(BLE, "CONNECTING MODE\n\r");
            break;
        case STANDBY_MODE:
            DEBUG_printNoTimeStamp(BLE, "STANDBY MODE\n\r");
            break;
        case BROADCAST_MODE:
            DEBUG_printNoTimeStamp(BLE, "BROADCAST MODE\n\r");
            break;
        case TRANSPARENT_SERVICE_ENABLED_MODE:
            DEBUG_printNoTimeStamp(BLE, "TRANSPARENT SERVICE ENABLED MODE\n\r");
            break;
        case IDLE_MODE:
            DEBUG_printNoTimeStamp(BLE, "IDLE MODE\n\r");
            break;
        case SHUTDOWN_MODE:
            DEBUG_printNoTimeStamp(BLE, "SHUTDOWN MODE\n\r");
            break;
        case CONFIGURE_MODE:
            DEBUG_printNoTimeStamp(BLE, "CONFIGURE MODE\n\r");
            break;
        case BLE_CONNECTED_MODE:
            DEBUG_printNoTimeStamp(BLE, "BLE CONNECTED MODE\n\r");
            break;
        default:
            DEBUG_printNoTimeStamp(BLE, "!! UNKOWN !!\n\r");
            break;
    }
    return( BM71_Status );
}

/*******************************************************************************
* Description: Read the BM71 Device Name.
*
*******************************************************************************/
void BM71_readDeviceName(void)
{
    uint16_t msgLen = 0;
    //Clear our the current name we have before reading
    memset(BM71_DeviceName, 0x00, sizeof(BM71_DeviceName));
    //Load the Read Device Name command into the writeBuffer
    BM71_loadWriteBuffer(CMD_readDeviceName, sizeof(CMD_readDeviceName));
    //Send the command out
    msgLen = BM71_sendAppCommand(sizeof(CMD_readDeviceName));
    //We only want to copy the device name.. So subtract bytes for SOM,LENMSB,LENLSB,EVENT,OPCODE,STATUS
    msgLen -= 7;
    //Copy the device name from the readBuffer into our DeviceName var
    memcpy(BM71_DeviceName, (char*)BM71_readBuffer+BM71_READ_DEVICE_NAME_OFFSET, msgLen);
    //Print out the retrieved module info
    DEBUG_println(BLE, "BLE Device Name: %s\n\n\r", BM71_DeviceName);
}

/*******************************************************************************
* Description: Write the BM71 Device Name.
*
*******************************************************************************/
void BM71_writeDeviceName(void)
{
    DEBUG_println(BLE, "Writing new device name...\n\r");	
    //Load the Write Device Name command into the writeBuffer
    BM71_loadWriteBuffer(CMD_writeDeviceName, sizeof(CMD_writeDeviceName));
    //Write the length of the command which is the length of device name plus 1 for the opcode and reserved byte
    BM71_writeBuffer[CMD_LEN_LSB_INDEX] = strlen(OCTANEMATE_DEVICE_NAME) + 2;
    //Copy the Device name into the buffer at the correct spot
    memcpy(BM71_writeBuffer+BM71_WRITE_DEVICE_NAME_OFFSET, OCTANEMATE_DEVICE_NAME, strlen(OCTANEMATE_DEVICE_NAME));
    //Send the command out
    (void)BM71_sendAppCommand(sizeof(CMD_writeDeviceName) + strlen(OCTANEMATE_DEVICE_NAME));
    //Now read the device name back out
    BM71_readDeviceName();
}

/*******************************************************************************
* Description: Set Advertising Enable/Disable
*
*******************************************************************************/
void BM71_setAdvertisingEnable(uint8_t val)
{
    //Load the Set Advertising Enable/Disable command into the writeBuffer
    BM71_loadWriteBuffer(CMD_setAdvertisingEnable, sizeof(CMD_setAdvertisingEnable));
    //Copy the Device name into the buffer at the correct spot
    BM71_writeBuffer[BM71_SET_ADVERTISING_EN_OFFSET] = val;
    //Send the command out
    (void)BM71_sendAppCommand(sizeof(CMD_setAdvertisingEnable));
}

/*******************************************************************************
* Description: Send an App command to BM71 and wait back for a response.
*
*******************************************************************************/
uint16_t BM71_sendAppCommand(uint8_t sendSize)
{
    uint8_t readVal = 0;
    uint8_t rxCnt = 0;
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
    //Read out the response length into the read buffer.. 3 is hard coded here since that will get us the
    //SOM, len MSB, and len LSB
    while(rxCnt != 0x03)
    {
        readVal = io_read(&BT_UART.io, BM71_readBuffer+rxCnt, 0x01);
        if(readVal > 0)
        {
            rxCnt += readVal;
        }
    }
    //Calculate the total length that we now need to retrieve from the Ring Buffer
    msgLen = ((uint16_t)BM71_readBuffer[CMD_LEN_MSB_INDEX] << 8) + BM71_readBuffer[CMD_LEN_LSB_INDEX];
    //Add one to account for the CRC
    msgLen += 1; 
    //Reset our index values so we can read the rest of the message
    readVal = 0;
    rxCnt = 0;
    //Read bytes until we receive the rest of the message
    while(rxCnt != msgLen)
    {
        readVal = io_read(&BT_UART.io, BM71_readBuffer+3+rxCnt, 0x01);
        if(readVal > 0)
        {
            rxCnt += readVal;
        }
    }

    return msgLen+3;
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

    for(uint16_t x=1;x<len;x++)
    {
        crc -= buffer[x];
    }
    buffer[len] = crc+1;
}

/*******************************************************************************
* Description: Clear the global writeBuffer used for BM71 comms.
*
*******************************************************************************/
void BM71_clearWriteBuffer(void)
{
    for(uint16_t i = 0; i < sizeof(BM71_writeBuffer); i++)
    {
        BM71_writeBuffer[i] = 0x00;
    }
}

/*******************************************************************************
* Description: Clear the global readBuffer used for the BM71 module.
*
*******************************************************************************/
void BM71_clearReadBuffer(void)
{
    for(uint16_t i = 0; i < sizeof(BM71_readBuffer); i++)
    {
        BM71_readBuffer[i] = 0x00;
    }
}

/*******************************************************************************
* Description: Load the writeBuffer with an App command passed in.
*
*******************************************************************************/
void BM71_loadWriteBuffer( const uint8_t *command, uint8_t bytes)
{
    BM71_clearWriteBuffer();
    memcpy(BM71_writeBuffer, command, bytes);
}

/*******************************************************************************
* Description: Pulse the Reset line low for 2ms.
*
*******************************************************************************/
void BM71_PulseRSTPin(void)
{
    brd_BM71_setResetPin(false);
    //Reset pulse greater than 2ms
    brd_MsDelay(2);
    brd_BM71_setResetPin(true);
}

/*******************************************************************************
* Description: Reset the BM71 module and place it in Test mode once it starts
* back up.
*******************************************************************************/
void BM71_ResetToTestMode(void)
{
    //Test mode is entered if Conf pin is low after a reset
    BRD_BM71_setConfigPin(false);
    BM71_Reset();
}

/*******************************************************************************
* Description: Reset the BM71 module and place it in App mode once it starts
* back up.
*******************************************************************************/
void BM71_ResetToAppMode(void)
{
    //App mode is entered if Conf pin is high after a reset
    BRD_BM71_setConfigPin(true);
    BM71_Reset();
}

/*******************************************************************************
* Description: Reset the BM71 module.
*
*******************************************************************************/
void BM71_Reset(void)
{
    BM71_PulseRSTPin();
    brd_MsDelay(50);
    BRD_BM71_setConfigPin(true);
    brd_MsDelay(100);
}
