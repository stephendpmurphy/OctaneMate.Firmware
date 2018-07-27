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
#include "BM71_flash_commands.h"
#include "BM71_flash_data.h"
#include "BM71.h"
#include "delay.h"
#include "debugAPI.h"
#include "driver_init.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static bool OpenFlashMemory(void);
static void SetBufferAddress(uint16_t address, uint8_t lowByte, uint8_t highByte);
static bool Send128Bytes(uint16_t address, const uint8_t *data);
static bool Read128Bytes(uint16_t address);
static bool EndFlashMemoryAccess(void);
static bool EraseFlashMemory(void);
static uint8_t GetSizeOfMemBlock(void);
static bool SendConfigToEEPROM(void);
static bool CheckConfig(void);
static bool CompareEmptyMemory(uint16_t address);
static bool CompareMemory(uint16_t address, const uint8_t *expectedData);
static void SendFlashCommand(const uint8_t *sendPacket, uint8_t sendSize, uint8_t *recievePacket, uint8_t readSize);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
//Load the memoryBlock array from the "bluetooth_flash_data.h" header so we can read it here
extern const flash128_t memoryBlock[16];
///OPEN FLASH MEMORY
const uint8_t open_Transmit[17] = {0x01,0x05,0x04,0x0D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t open_Response[21] = {0x04,0x0F,0x04,0x00,0x01,0x05,0x04,0x04,0x03,0x0B,0x00,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00};
///READ COMMAND
const uint8_t read_Transmit[19] = {0x02,0xFF,0x0F,0x0E,0x00,0x10,0x01,0x0A,0x00,0x03,0x00,0x00,0x40,0x03,0x00,0x80,0x00,0x00,0x00};
const uint8_t read_Response[19] = {0x04,0x13,0x05,0x01,0xFF,0x0F,0x01,0x00,0x02,0xFF,0x0F,0x86,0x00,0x10,0x01,0x82,0x00,0x00,0x00};
///ERASE ALL FLASH
const uint8_t erase_Transmit[19] = {0x02,0xFF,0x0F,0x0E,0x00,0x12,0x01,0x0A,0x00,0x03,0x00,0x00,0x40,0x03,0x00,0x00,0x20,0x00,0x00};
const uint8_t erase_Response[27] = {0x04,0x13,0x05,0x01,0xFF,0x0F,0x01,0x00,0x02,0xFF,0x0F,0x0E,0x00,0x12,0x01,0x0A,0x00,0x00,0x00,0x00,0x40,0x03,0x00,0x00,0x20,0x00,0x00};
///WRITE COMMAND
const uint8_t write_Transmit[19] = {0x02,0xFF,0x0F,0x8E,0x00,0x11,0x01,0x8A,0x00,0x03,0x00,0x00,0x40,0x03,0x00,0x80,0x00,0x00,0x00};
const uint8_t write_Response[19] = {0x04,0x13,0x05,0x01,0xFF,0x0F,0x01,0x00,0x02,0xFF,0x0F,0x06,0x00,0x11,0x01,0x02,0x00,0x00,0x00};
//CLOSE FLASH MEMORY
const uint8_t close_Transmit[7] = {0x01,0x06,0x04,0x03,0xFF,0x0F,0x00};
const uint8_t close_Response[14] = {0x04,0x0F,0x04,0x00,0x01,0x06,0x04,0x04,0x05,0x04,0x00,0xFF,0x0F,0x00};


static void SetBufferAddress(uint16_t address, uint8_t lowByte, uint8_t highByte)
{
	//Set the MSB and LSB of the 2 byte address in the output buffer at the specified indexes
	BM71_writeBuffer[lowByte] = (uint8_t) address;
	BM71_writeBuffer[highByte] += (uint8_t) (address >> 8);
}

static bool OpenFlashMemory(void)
{
    SendFlashCommand(open_Transmit,sizeof(open_Transmit),BM71_readBuffer, sizeof(open_Response));

	for(uint8_t i = 0; i < 19; i++)
	{
		if(BM71_readBuffer[i] != open_Response[i])
		{
			return false;
		}
	}
	return true;
}

static bool Send128Bytes(uint16_t address, const uint8_t *data)
{
    //Clear the buffers
    BM71_clearWriteBuffer();
    BM71_clearReadBuffer();

    //We first add the 19 byte write command to the beginning of the buffer
    BM71_loadSendBuffer(write_Transmit, sizeof(write_Transmit));

    //We then update the buffer with the specified address to write 128 bytes to
    SetBufferAddress(address, 11, 12);

	//Place the data to be written after the command
    for (uint8_t i = sizeof(write_Transmit); i < 147; i++)
	{
        BM71_writeBuffer[i] = *data++;
	}

    SendFlashCommand(BM71_writeBuffer, sizeof(BM71_writeBuffer), BM71_readBuffer, sizeof(write_Response));
    //Check that the BT device responded with the
    for(uint8_t i = 0; i < 19; i++)
	{
        if(BM71_readBuffer[i] != write_Response[i])
		{
            return false;
		}
    }
    //If the response from the Bluetooth device was what was expected then return a true
    return true;

}

static bool Read128Bytes(uint16_t address)
{
    //Clear the buffers
    BM71_clearWriteBuffer();
    BM71_clearReadBuffer();

    //Populate the read command in the buffer
    BM71_loadSendBuffer(read_Transmit, sizeof(read_Transmit));

    //Update the address of the read command in the buffer
    SetBufferAddress(address, 11, 12);

    //Send the read command
    SendFlashCommand(BM71_writeBuffer, sizeof(read_Transmit), BM71_readBuffer, sizeof(BM71_readBuffer));

    for(uint8_t i = 0; i < 19; i++)
	{
        if(BM71_readBuffer[i] != read_Response[i])
		{
            return false;
		}
    }
    //If the response from the Bluetooth device was what was expected then return a true
    return true;
}

static bool Write128BytesToFlash(uint16_t address, const uint8_t *data )
{
    //Write data to the BM71
    if(!Send128Bytes(address, data))
    {
        return false;
	}

	//Read the data back out
    if(!Read128Bytes(address))
    {
        return false;
	}

	//Verify that the data we just read back matches what we wrote
    for(uint8_t i = sizeof(read_Response); i < sizeof(BM71_readBuffer); i++)
	{
        //We compare byte by byte between the two buffers
        if(BM71_readBuffer[i] != *data++)
        {
            //if the data does not match, we return a false
            return false;
		}
    }
    //If all data matched, we return a true.
    return true;
}

static bool EndFlashMemoryAccess(void)
{
    //Send the close access to the flash memory command and check the response
    SendFlashCommand(close_Transmit,sizeof(close_Transmit),BM71_readBuffer, sizeof(close_Response));

    for(uint8_t i = 0; i < 19; i++)
    {
	    if(BM71_readBuffer[i] != close_Response[i])
	    {
		    return false;
	    }
    }
    return true;
}

static bool EraseFlashMemory(void)
{
    SendFlashCommand(erase_Transmit,sizeof(erase_Transmit),BM71_readBuffer, sizeof(erase_Response));

	for(uint8_t i = 0; i < 19; i++)
	{
		if(BM71_readBuffer[i] != erase_Response[i])
		{
			return false;
		}
	}

    brd_MsDelay(25);

    return  true;
}

static uint8_t GetSizeOfMemBlock()
{
	//Divide the full size of the data memory by the block size to calculate how many blocks are in the struct
    return sizeof(memoryBlock) / 130u;
}

static bool SendConfigToEEPROM(void)
{
    uint8_t sizeOfMemoryBlock = GetSizeOfMemBlock();

    //cycle through each row/index in the "memoryBlock" array and update the
    //flash memory.
    for(uint8_t i = 0; i < sizeOfMemoryBlock; i++)
    {
        //each row has 128 bytes, so we set bytes to 128. We also send the address
        if(!Write128BytesToFlash(memoryBlock[i].address, memoryBlock[i].data))
        {
            return false;
        }
    }

    return true;
}

static bool CheckConfig(void)
{
    uint8_t sizeOfMemoryBlock = GetSizeOfMemBlock();
    bool isAddressInBlock;
    uint8_t index = 0;

    //This is a normal for loop, except we are using address instead of i
    //address is also a 16bit word, not an 8 bit word because the
    //bluetooth's addresses are all 16 bits.
    //Since we are reading/writing 128 bytes at a time, we increment by
    //0x0080 each iteration of the for loop. NOT the number 80, but 128 in hex.
    //This causes us to have the address of the next 128 bytes in the memory each
    //iteration of the for loop.
    //Also, according to the BM71's documentation, the last address in the BM70's
    //EEPROM is 0x1FF0. This is why we only loop to it then stop.
    for(uint16_t address = 0x0000; address <= 0x1FF0; address += 0x0080)
    {
        //Reset address is found in the flash block flag
        isAddressInBlock = false;

        //Reset the starting index location that we will start from when
        //searching the flash memory block
        index = 0;

        //Search through the Flash Block for the address, WHILE
        //we have not reached the end of the memory block's last index
        //AND
        //We have not found the memory address in the block

        //If we find the address, or we reach the end of the indexes
        //in the memory block then stop looking.
        while((index < sizeOfMemoryBlock) &&  !isAddressInBlock)
        {
            //if the current index of the memory block has the same
            //address as the one we are looking for set the isAddressInBlock flag true.
            if(memoryBlock[index].address == address)

                //Set the flag that the address was found in the memory block
                isAddressInBlock = true;
            //If the memory address was not found at the current index, then increment it
            //to the next index and keep looking
            else index++;
        }

        //If the address was found in the memory block
        if(isAddressInBlock)
        {
            //Then check that the 128 bytes after that address match the specified
            //bytes in the memory block
            if(!CompareMemory(address, memoryBlock[index].data))
                //if the 128 bytes did not match, then return with a false
                return false;

            //If the bytes did match, do nothing and continue testing the rest of
            //the memory
        }
        //Else if the address was not found in the flash memory block
        else
        {
            //Then assume that the 128 bytes after this address should be in the
            //erased state "0xFF". Check that all the following 128 bytes are
            //set to "0xFF". If the address is not found in the memory block it
            //is to be assumed it is a fully erased block.
            if(!CompareEmptyMemory(address))

                //If the 128 bytes did not all return as "0xFF" then there is
                //a data mismatch, and return as false.
                return false;

            //If all of the 128 bytes are blank then do nothing and continue testing
            //the rest of the memory
        }
    }

    //If we reach this point, then we have checked all of the flash memory and
    //everything matched (Since we did not return false yet), so return true.
    return true;
}

static bool CompareEmptyMemory(uint16_t address)
{
    if(!Read128Bytes(address))
	{
        return false;
	}

    //If the 128 bytes returned from the BM71 is not all set to 0xFF (Not Empty)
    //we return a false
    //
    //We start at i = sizeof(read_Response) to skip the response command sent back. We only care
    //about the data returned, not the response command.
    //
    //We also use i < sizeof(BM71_readBuffer) to make sure we read all the way to the end of the buffer
    //to read the full 128 bytes.

    for(uint8_t i = sizeof(read_Response); i < sizeof(BM71_readBuffer); i++)
	{
        if(BM71_readBuffer[i] != 0xFF)
		{
            return false;
		}
    }
    //If the values all matched then return true;
    return true;
}

static bool CompareMemory(uint16_t address, const uint8_t *expectedData)
{
    BM71_clearReadBuffer();
    Read128Bytes(address);

    //If the 128 bytes returned from the BM71 does not match the 128 bytes passed
    //into the *expectedData array then return false
    //
    //We start at i = sizeof(read_Response) to skip the response command sent back. We only care
    //about the data returned, not the response command.
    //
    //We also use i < sizeof(BM71_readBuffer) to make sure we read all the way to the end of the buffer
    //to read the full 128 bytes.
    for(uint8_t i = sizeof(read_Response); i < sizeof(BM71_readBuffer); i++)
	{
        if(BM71_readBuffer[i] != *expectedData++)
        {
            return false;
        }
    }

    //If the values all matched then return true;
    return true;

}

static void SendFlashCommand(const uint8_t *sendPacket, uint8_t sendSize, uint8_t *recievePacket, uint8_t readSize)
{
    //Make sure the RX ring buffer is empty
    usart_async_flush_rx_buffer(&BT_UART);
    BM71_clearReadBuffer();
	while(io_write(&BT_UART.io, (const uint8_t*)sendPacket, sendSize) == ERR_NO_RESOURCE)
	{
		; //This prevents us from erroring out before sending a command becuase the UART module is busy
	}
	//Wait a bit before checking the buffer for any response
	brd_MsDelay(25);
	//Read out the response into the receive packet
	io_read(&BT_UART.io, recievePacket, readSize);
}

bool CheckAndUpdateFlash(void)
{
	bool retVal = false;
    //First enter test mode so we can access the BM71 Memory
    BM71_ResetToTestMode();

    DEBUG_println("Checking current BM71 config... ");
	retVal = OpenFlashMemory();
    if(retVal)
	{
		retVal = CheckConfig();
		if(retVal)
		{
			DEBUG_println("Config is up to date!\n\r");
		}
		else
		{
			DEBUG_println("BM71 config is out of date. Starting update... ");
			retVal = EraseFlashMemory();
			if(retVal)
			{
				retVal = SendConfigToEEPROM();
				if(retVal)
				{
					DEBUG_println("New config applied successfully!\n\r");
				}
				else
				{
					DEBUG_println("Failed to apply new config\n\r");
				}
			}
			else
			{
	            DEBUG_println("Failed to erase flash memory.\n\r");
			}
		}
		EndFlashMemoryAccess();
	}
	else
	{
		DEBUG_println("Failed to open flash memory!\n\r");
	}

	return retVal;
}
