//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#ifndef CONFIGAPI_H_
#define CONFIGAPI_H_

#include <stdint.h>

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
typedef struct {
    // Byte 0
    uint8_t firmwareVersion_Major;
    // Byte 1
    uint8_t firmwareVersion_Minor;
    // Byte 2
    uint8_t firmwareVersion_Build;
    // Byte 3
    uint8_t bluetoothConfigVersion;
    
} nvm_device_config_t;

/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
void task_config(void* params);
void config_init(void);
void config_setFirmwareVersionMajor(uint8_t value);
uint8_t config_getFirmwareVersionMajor(void);
void config_setFirmwareVersionMinor(uint8_t value);
uint8_t config_getFirmwareVersionMinor(void);
void config_setFirmwareVersionBuild(uint8_t value);
uint8_t config_getFirmwareVersionBuild(void);
void config_setBluetoothConfigVersion(uint8_t value);
uint8_t config_getBluetoothConfigVersion(void);

/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

#endif //CONFIGAPI_H_
