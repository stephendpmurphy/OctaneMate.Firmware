/**********************************************************
* Copyright 2017, Murphy Technology, All rights reserved. *
***********************************************************/
#include <stdint.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "Timeout.h"
#include "NonVolatileMemory.h"
#include "LED_UI.h"
#include "Logger.h"

/************ DEFINITIONS ***************/
#define RESET_VECTOR 0x76A
#define FLASH_MEM_SIZE 0x20000

/*********** LOCAL VARIABLES ************/
const char NVFlag @ (FLASH_MEM_SIZE - 2) = 0x55;

/********* FUNCTION PROTOTYPES **********/
void enableInterrupts(void);
void Signal_BL_Requested(void);
void EraseResetVector(void);

/****************************************
* Name: main
* Arg: Void
* Return: Void
* Notes: Main loops where all the magic happens
*
*****************************************/
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    InitTimer();
    InitDeviceConfig();

    SetLED_State(MCU_LED, LED_ON);
    SetLED_State(BLUETOOTH_LED, LED_ON);

    while (1)
    {
        ServiceTimers(); //This handles all LED UI as well as the 10hz and 20hz PID logging

    }
}

/****************************************
* Name: enableInterrupts
* Arg: Void
* Return: Void
* Notes: Enable interrupts at MCU startup
*
*****************************************/
void enableInterrupts(void)
{
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
}

void Signal_BL_Requested(void)
{
    NVMADRL  = (uint8_t) (FLASH_MEM_SIZE-2) & 0x00FF;
    NVMADRH  = ((FLASH_MEM_SIZE-2)) >> 8;
    NVMDAT  = 0x00;
    NVMCON1 = 0x14;  // WREN & FREE
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
}

void EraseResetVector(void)
{
    NVMADRL = (uint8_t) (RESET_VECTOR & 0x00FF);
    NVMADRH = (uint8_t) ((RESET_VECTOR & 0xFF00) >> 8);
    NVMDAT  = 0x00;
    NVMCON1 = 0x14;  // WREN & FREE
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
}
/**
 End of File
*/
