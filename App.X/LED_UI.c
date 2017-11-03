#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "Timeout.h"
#include "NonVolatileMemory.h"
#include "LED_UI.h"

void InitLED_UI(void)
{
    void(*ptrFunc1)(void) = UpdateMCU_LED;
    void(*ptrFunc2)(void) = UpdateBluetooth_LED;
    AddTimer(MCU_LED_TIMEOUT, TRUE, 0, 500, ptrFunc1, NULL);
    AddTimer(BLUETOOTH_LED_TIMEOUT, TRUE, 0, 250, ptrFunc2, NULL);
}

static void UpdateMCU_LED(void)
{
    //DO SOMETHING
}

static void UpdateBluetooth_LED(void)
{

}
