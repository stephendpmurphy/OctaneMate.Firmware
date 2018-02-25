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
#include "ErrorLog.h"

/************ DEFINITIONS ***************/

/********* FUNCTION PROTOTYPES **********/

/*********** LOCAL VARIABLES ************/
ERRORLOG_t ErrorLog[MAX_ERROR_LOG] = {0,NULL_ERROR};

/****************************************
* Name: Function Headers
* Arg: Void
* Return: Void
* Notes: Null
*
*****************************************/
void LogError(uint8_t error)
{
    for(uint8_t x=(MAX_ERROR_LOG-1); x > 0; x--)
    {
        if((ErrorLog[x].errorcode != NULL_ERROR) && (x != MAX_ERROR_LOG-1))
        {
            ErrorLog[x+1].timestamp = _timer_tick;
            ErrorLog[x+1].errorcode = error;
            break;
        }
    }
}

void ClearErrorCodes(void)
{
    memcpy(ErrorLog, 0, sizeof(ERRORLOG_t)*MAX_ERROR_LOG);
}
