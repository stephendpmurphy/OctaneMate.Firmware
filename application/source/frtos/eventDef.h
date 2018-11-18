//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------
#ifndef EVENTDEF_H_
#define EVENTDEF_H_

typedef enum{
    // General Events
    kEVENT_INIT = 0x00,
    
    // Bluetooth Events
    kEVENT_BLUETOOTH_DEVICE_CONNECTED = 0x20,
    kEVENT_BLUETOOTH_DEVICE_DISCONNECTED,
    // Device Control
    kEVENT_DEVICE_START_LOGGING = 0x40,
    kEVENT_DEVICE_STOP_LOGGING,
    // Config Module
    kEVENT_CONFIG_WRITE_NVM = 0x60,
    kEVENT_CONFIG_READ_NVM,
    
    kEVENT_MAX,
    kEVENT_NULL
}event_t;

#endif /* EVENTDEF_H_ */
