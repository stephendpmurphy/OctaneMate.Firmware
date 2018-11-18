//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include "configAPI.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"
#include "board_intFlash.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void readAllConfigs(void);
static void writeAllConfigs(void);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
static nvm_device_config_t device_config = {0};
static bool nvmWriteQueued = false;

/*******************************************************************************
* Description: FreeRTOS task for the config functionality.
*
*******************************************************************************/
void task_config(void* params)
{
    eventMsg_t rxMsg = {0};

	DEBUG_println(CONFIG, "Config Task Started\n\r");
    //Config Manager Code
    while(1)
    {
        xQueueReceive(queueHandles[kQUEUE_CONFIG], &rxMsg, portMAX_DELAY);
        switch( rxMsg.mainEvent )
        {
            case kEVENT_CONFIG_WRITE_NVM:
                nvmWriteQueued = false;
                writeAllConfigs();
                DEBUG_println(CONFIG, "Config written to the SmartEEPROM.\n\r");
                break;
            default:
                break;
        }
    }
}

/*******************************************************************************
* Description: Initialize the config module by reading all of our configuration
* from the SmartEEPROM
*******************************************************************************/
void config_init(void)
{    
    // Read all of our device configs from the Smart EEPROM
    readAllConfigs();
}

/*******************************************************************************
* Description: Set the Firmware Version Major and send an event to ourself
* to initiate a write to the EEPROM.
*******************************************************************************/
void config_setFirmwareVersionMajor(uint8_t value)
{
    device_config.firmwareVersion_Major = value;
    if( false == nvmWriteQueued )
    {
        nvmWriteQueued = true;
        eventQueue_sendMsg(kEVENT_CONFIG_WRITE_NVM,kEVENT_NULL,0x00,0x00,NULL,kQUEUE_NULL,kQUEUE_CONFIG);
    }
}

/*******************************************************************************
* Description: Get the Firmware Version Major from our RAM copy of the config.
*******************************************************************************/
uint8_t config_getFirmwareVersionMajor(void)
{
    return( device_config.firmwareVersion_Major );
}

/*******************************************************************************
* Description: Set the Firmware Version Minor and send an event to ourself
* to initiate a write to the EEPROM.
*******************************************************************************/
void config_setFirmwareVersionMinor(uint8_t value)
{
    device_config.firmwareVersion_Minor = value;
    if( false == nvmWriteQueued )
    {
        nvmWriteQueued = true;
        eventQueue_sendMsg(kEVENT_CONFIG_WRITE_NVM,kEVENT_NULL,0x00,0x00,NULL,kQUEUE_NULL,kQUEUE_CONFIG);
    }
}

/*******************************************************************************
* Description: Get the Firmware Version Mnior from our RAM copy of the config.
*******************************************************************************/
uint8_t config_getFirmwareVersionMinor(void)
{
    return( device_config.firmwareVersion_Minor );
}

/*******************************************************************************
* Description: Set the Firmware Version Build and send an event to ourself
* to initiate a write to the EEPROM.
*******************************************************************************/
void config_setFirmwareVersionBuild(uint8_t value)
{
    device_config.firmwareVersion_Build = value;
    if( false == nvmWriteQueued )
    {
        nvmWriteQueued = true;
        eventQueue_sendMsg(kEVENT_CONFIG_WRITE_NVM,kEVENT_NULL,0x00,0x00,NULL,kQUEUE_NULL,kQUEUE_CONFIG);
    }
}

/*******************************************************************************
* Description: Get the Firmware Version Build from our RAM copy of the config.
*******************************************************************************/
uint8_t config_getFirmwareVersionBuild(void)
{
    return( device_config.firmwareVersion_Build );
}

/*******************************************************************************
* Description: Set the Bluetooth Config Version and send an event to ourself
* to initiate a write to the EEPROM.
*******************************************************************************/
void config_setBluetoothConfigVersion(uint8_t value )
{
    device_config.bluetoothConfigVersion = value;
    if( false == nvmWriteQueued )
    {
        nvmWriteQueued = true;
        eventQueue_sendMsg(kEVENT_CONFIG_WRITE_NVM,kEVENT_NULL,0x00,0x00,NULL,kQUEUE_NULL,kQUEUE_CONFIG);
    }
}

/*******************************************************************************
* Description: Get the Bluetooth Config version from our RAM copy of the config.
*******************************************************************************/
uint8_t config_getBluetoothConfigVersion(void)
{
    return( device_config.bluetoothConfigVersion );
}

/*******************************************************************************
* Description: Read all of our device config from the Smart EEPROM.
*******************************************************************************/
static void readAllConfigs(void)
{
    uint8_t *pCONFIG = (uint8_t *)&device_config;
    
    for(uint16_t x = 0; x < sizeof(device_config); x++)
    {
        *pCONFIG++ = brd_intFlash_readConfigByte(x);
    }
}

/*******************************************************************************
* Description: Write all of our configs in RAM to the Smart EEPROM.
*******************************************************************************/
static void writeAllConfigs(void)
{
    uint8_t *pCONFIG = (uint8_t *)&device_config;
    
    for(uint16_t x = 0; x < sizeof(device_config); x++)
    {
        brd_intFlash_writeConfigByte(x, *pCONFIG + x);
    }
}
