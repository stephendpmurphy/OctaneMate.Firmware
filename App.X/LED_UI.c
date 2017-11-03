#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "Timeout.h"
#include "NonVolatileMemory.h"
#include "LED_UI.h"

STATUS_LED_t MCU_LED = {.LED_NAME = MCU_STATUS_LED, .LED_STATE = LED_STATE_OFF, .TIMEOUT_HANDLE = MCU_LED_TIMEOUT};
STATUS_LED_t BLUETOOTH_LED = {.LED_NAME = BLUETOOTH_STATUS_LED. .LED_STATE = LED_STATE_OFF, .TIMEOUT_HANDLE = BLUETOOTH_LED_TIMEOUT};

void InitLED_UI(void)
{
    void(*ptrFunc1)(void) = UpdateMCU_LED;
    void(*ptrFunc2)(void) = UpdateBluetooth_LED;
    AddTimer(MCU_LED_TIMEOUT, FALSE, 0, 0, ptrFunc1, NULL);
    AddTimer(BLUETOOTH_LED_TIMEOUT, FALSE, 0, 0, ptrFunc2, NULL);
}

static void UpdateMCU_LED(void)
{
    switch(MCU_LED.LED_STATE)
    {
        case LED_STATE_OFF:
            MCU_STATUS_LED_SetLow();
            break;

        case LED_STATE_ON:
            MCU_STATUS_LED_SetHigh();
            break;

        case LED_STATE_BLINK_SLOW:
        case LED_STATE_BLINK_FAST:
            MCU_STATUS_LED_Toggle();
            break;

        default:
            MCU_STATUS_LED_SetLow();
            break;
    }
}

static void UpdateBluetooth_LED(void)
{
    switch(BLUETOOTH_LED.LED_STATE)
    {
        case LED_STATE_OFF:
            break;
        case LED_STATE_ON:
            break;
        case LED_STATE_BLINK_SLOW:
        case LED_STATE_BLINK_FAST:
            break;
        default:
            break;
    }
}

void SetLED_State(STATUS_LED_t LED, LED_STATE_t state)
{
    LED.LED_STATE = state;
    SetTimerPeriodic(LED.TIMEOUT_HANDLE, state);
}
