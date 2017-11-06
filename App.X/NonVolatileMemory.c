/**********************************************************
* Copyright 2017, Murphy Technology, All rights reserved. *
***********************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "Timeout.h"
#include "NonVolatileMemory.h"
#include "LED_UI.h"
#include "Logger.h"

/*********** LOCAL VARIABLES ************/
PID_CHANNEL_CONFIG_t PID_CHANNEL_CONFIG[MAX_PID_CHANNELS];
DEVICE_CONFIG_t DEVICE_CONFIG;

static const uint8_t DEFAULT_DEVICE_CONFIG[3] = { 0x00, 0x01, 0x02 };
static const PID_CHANNEL_CONFIG_t DEFAULT_PID_CHANNEL_CONFIG = {0x00, NONE, 0x00, 0x00, 0x00, 0x00, 0x00};

/****************************************
* Name: InitDeviceConfig
* Arg: Void
* Return: Void
* Notes: Init Device Config struct and then
* copy Device and PID config from EEPROM to RAM
*****************************************/
void InitDeviceConfig(void)
{
    memcpy((uint8_t*)&DEVICE_CONFIG, DEFAULT_DEVICE_CONFIG, sizeof(DEVICE_CONFIG_t));

    //TO-DO - COPY ALL CONFIG FROM EEPROM INTO DEVICE_CONFIG VAR
    //TO-DO - COPY ALL PID CONFIG FROM EEPROM INTO PID_CHANNEL_CONFIG VAR
}

/****************************************
* Name: ResetAllConfig
* Arg: Void
* Return: Void
* Notes: Set all Device and PID config back
* to default
*****************************************/
void ResetAllConfig(void)
{
    //Reset Device Config to Default
    memcpy((uint8_t*)&DEVICE_CONFIG, DEFAULT_DEVICE_CONFIG, sizeof(DEVICE_CONFIG_t));

    //Reset PID Channel Config to Default
    for(uint8_t x=0;x<MAX_PID_CHANNELS-1;x++)
    {
        memcpy(&PID_CHANNEL_CONFIG[x], &DEFAULT_PID_CHANNEL_CONFIG, sizeof(PID_CHANNEL_CONFIG_t));
    }
}
