#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "Timeout.h"
#include "NonVolatileMemory.h"

PID_CHANNEL_CONFIG_t PID_CHANNEL_CONFIG[MAX_PID_CHANNELS];
DEVICE_CONFIG_t DEVICE_CONFIG;

static const uint8_t DEFAULT_DEVICE_CONFIG[3] = { 0x00, 0x01, 0x02 };
static const PID_CHANNEL_CONFIG_t DEFAULT_PID_CHANNEL_CONFIG = {0x00, NONE, 0x00, 0x00, 0x00, 0x00, 0x00};

void Config_init(void)
{
    memcpy((uint8_t*)&DEVICE_CONFIG, DEFAULT_DEVICE_CONFIG, sizeof(DEVICE_CONFIG_t));
}

void RESET_ALL_CONFIG()
{
    //Reset Device Config to Default
    memcpy((uint8_t*)&DEVICE_CONFIG, DEFAULT_DEVICE_CONFIG, sizeof(DEVICE_CONFIG_t));
    
    //Reset PID Channel Config to Default
    for(uint8_t x=0;x<MAX_PID_CHANNELS-1;x++)
    {
        memcpy(&PID_CHANNEL_CONFIG[x], DEFAULT_PID_CHANNEL_CONFIG, sizeof(PID_CHANNEL_CONFIG_t));
    }
}