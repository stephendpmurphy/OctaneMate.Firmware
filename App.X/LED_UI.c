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
STATUS_LED_t MCU_LED = {LED_OFF, MCU_LED_TIMEOUT};
STATUS_LED_t BLUETOOTH_LED = {LED_OFF, BLUETOOTH_LED_TIMEOUT};

/****************************************
* Name: InitLED_UI
* Arg: Void
* Return: Void
* Notes: Set pointers to function calls and
* add timers for the MCU and Bluetooth LED
*****************************************/
void InitLED_UI(void)
{
    void(*ptrFunc1)(void) = UpdateMCU_LED;
    void(*ptrFunc2)(void) = UpdateBluetooth_LED;
    AddTimer(MCU_LED.TIMEOUT_HANDLE, FALSE, 0, 0, ptrFunc1, NULL);
    AddTimer(BLUETOOTH_LED.TIMEOUT_HANDLE, FALSE, 0, 0, ptrFunc2, NULL);
}

/****************************************
* Name: UpdateMCU_LED
* Arg: Void
* Return: Void
* Notes: Main state machine used to drive
* the MCU status LED. This is called from the MCU_LED timer
*****************************************/
static void UpdateMCU_LED(void)
{
    switch(MCU_LED.LED_STATE)
    {
        case LED_OFF:
            SetTimerStatus(MCU_LED_TIMEOUT, FALSE);
            MCU_STATUS_LED_SetLow();
            break;

        case LED_ON:
            SetTimerStatus(MCU_LED_TIMEOUT, FALSE);
            MCU_STATUS_LED_SetHigh();
            break;

        case LED_FAST_FLASH:
        case LED_SLOW_FLASH:
            MCU_STATUS_LED_Toggle();
            break;

        default:
            MCU_STATUS_LED_SetLow();
            break;
    }
}

/****************************************
* Name: UpdateBluetooth_LED
* Arg: Void
* Return: Void
* Notes: Main state machine used to drive
* the Bluetooth status LED. This is called from the MCU_LED timer
*****************************************/
static void UpdateBluetooth_LED(void)
{
    switch(BLUETOOTH_LED.LED_STATE)
    {
        case LED_OFF:
            SetTimerStatus(BLUETOOTH_LED_TIMEOUT, FALSE);
            BLUETOOTH_STATUS_LED_SetLow();
            break;

        case LED_ON:
            SetTimerStatus(BLUETOOTH_LED_TIMEOUT, FALSE);
            BLUETOOTH_STATUS_LED_SetHigh();
            break;

        case LED_FAST_FLASH:
        case LED_SLOW_FLASH:
            BLUETOOTH_STATUS_LED_Toggle();
            break;

        default:
            BLUETOOTH_STATUS_LED_SetLow();
            break;
    }
}

/****************************************
* Name: SetLED_State
* Arg: STATUS_LED_t, uint16_t
* Return: Void
* Notes: Disable or Enable status LED
*
*****************************************/
void SetLED_State(STATUS_LED_t LED, uint16_t state)
{
    LED.LED_STATE = state;
    SetTimerPeriodic(LED.TIMEOUT_HANDLE, state);
    SetTimerStatus(LED.TIMEOUT_HANDLE, TRUE);
}
