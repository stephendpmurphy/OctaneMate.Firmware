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
LOGGER_t TEN_HZ_LOG = {FALSE, TEN_HZ_LOG_TIMEOUT};
LOGGER_t TWENTY_HZ_LOG = {FALSE, TWENTY_HZ_LOG_TIMEOUT};

/****************************************
* Name: InitLogger
* Arg: Void
* Return: Void
* Notes: Set pointers for logging functions
* and add timeouts for 10hz and 20hz logging
*****************************************/
void InitLogger(void)
{
    void(*ptrFunc1)(void) = LogTenHz;
    void(*ptrFunc2)(void) = LogTwentyHz;
    AddTimer(TEN_HZ_LOG.TIMEOUT_HANDLE, FALSE, 0, TEN_HZ_INTERVAL, ptrFunc1, NULL);
    AddTimer(TWENTY_HZ_LOG.TIMEOUT_HANDLE, FALSE, 0, TWENTY_HZ_INTERVAL, ptrFunc2, NULL);
}

/****************************************
* Name: LogTenHz
* Arg: Void
* Return: Void
* Notes: Function to be called at 10hz which
* will retrieve data for all PID's at 10hz
*****************************************/
static void LogTenHz(void)
{
    //GRAB PIDs THAT ARE ONLY IN A 10HZ ARRAY
}

/****************************************
* Name: LogTwentyHz
* Arg: Void
* Return: Void
* Notes: Function to be called at 10hz which
* will retrieve data for all PID's at 10hz
*****************************************/
static void LogTwentyHz(void)
{
    //GRAB PIDs THAT ARE ONLY IN A 20HZ ARRAY
}

/****************************************
* Name: EnableLogger
* Arg: uint8_t
* Return: Void
* Notes: Enable 10hz and 20hz logging
*
*****************************************/
void EnableLogger(uint8_t enable)
{
    SetTimerStatus(TEN_HZ_LOG.TIMEOUT_HANDLE, enable);
    SetTimerStatus(TWENTY_HZ_LOG.TIMEOUT_HANDLE, enable);
}
