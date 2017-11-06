/**********************************************************
* Copyright 2017, Murphy Technology, All rights reserved. *
***********************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "Timeout.h"
#include "NonVolatileMemory.h"
#include "LED_UI.h"

/*********** LOCAL VARIABLES ************/
TIMEOUT_t DEVICE_TIMEOUTS[MAX_TIMER];
uint16_t _timer_tick = 0;


/****************************************
* Name: InitTimer
* Arg: Void
* Return: Void
* Notes: Initialize all timers to zero
*
*****************************************/
void InitTimer(void)
{
	memset(DEVICE_TIMEOUTS, 0, sizeof(TIMEOUT_t));
	//TO-DO - FIX THIS. THIS DOES NOT PROPERLY INITIALIZE ANYTHING
}

/****************************************
* Name: AddTimer
* Arg: Handle, Enabled, Timeout_ms, periodic, callback, null
* Return: Void
* Notes: Adds a new timer to the existing timer array
*
*****************************************/
void AddTimer(TIMEOUT_HANDLE_t handle, uint8_t enabled, uint16_t timeout_ms, uint16_t periodic, void(*callback)(void), void *arg)
{
	DEVICE_TIMEOUTS[handle].enabled = enabled;
	DEVICE_TIMEOUTS[handle].timeout_ms = timeout_ms;
	DEVICE_TIMEOUTS[handle].periodic = periodic;
	DEVICE_TIMEOUTS[handle].callback = callback;
	(void)arg;
}

/****************************************
* Name: SetTimerStatus
* Arg: Void
* Return: Void
* Notes: Enable or Disable a timer with the
* specified handle
*****************************************/
void SetTimerStatus(TIMEOUT_HANDLE_t handle, uint8_t enabled)
{
	DEVICE_TIMEOUTS[handle].enabled = enabled;
}

/****************************************
* Name: SetTimerPeriodic
* Arg: Void
* Return: Void
* Notes: Change the frequency of the specified timer
*
*****************************************/
void SetTimerPeriodic(TIMEOUT_HANDLE_t handle, uint16_t periodic)
{
	DEVICE_TIMEOUTS[handle].periodic = periodic;
}

/****************************************
* Name: ServiceTimers
* Arg: Void
* Return: Void
* Notes: Check if any timers are expired and
* if so, run the callback function associated with it
*****************************************/
void ServiceTimers(void)
{
	TIMEOUT_HANDLE_t handle = 0;

	for(handle=0;handle<MAX_TIMER;handle++)
	{
		if((TRUE == DEVICE_TIMEOUTS[handle].enabled) && (DEVICE_TIMEOUTS[handle].timeout_ms < _timer_tick))
		{
			DEVICE_TIMEOUTS[handle].callback();
		}

		if(DEVICE_TIMEOUTS[handle].periodic > 0)
		{
			DEVICE_TIMEOUTS[handle].timeout_ms += DEVICE_TIMEOUTS[handle].periodic;
		}
		else
		{
			SetTimerStatus(handle, FALSE);
		}
	}
}
