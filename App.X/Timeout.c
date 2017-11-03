#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "Timeout.h"
#include "NonVolatileMemory.h"
#include "LED_UI.h"

TIMEOUT_t DEVICE_TIMEOUTS[MAX_TIMER];
uint16_t _timer_tick = 0;



void InitTimer(void)
{
	memset(DEVICE_TIMEOUTS, 0, sizeof(TIMEOUT_t));
}

void AddTimer(TIMEOUT_HANDLE_t handle, uint8_t enabled, uint16_t timeout_ms, uint16_t periodic, void(*callback)(void), void *arg)
{
	DEVICE_TIMEOUTS[handle].enabled = enabled;
	DEVICE_TIMEOUTS[handle].timeout_ms = timeout_ms;
	DEVICE_TIMEOUTS[handle].periodic = periodic;
	DEVICE_TIMEOUTS[handle].callback = callback;
	(void)arg;
}

void SetTimerStatus(TIMEOUT_HANDLE_t handle, uint8_t enabled)
{
	DEVICE_TIMEOUTS[handle].enabled = enabled;
}

void SetTimerPeriodic(TIMEOUT_HANDLE_t handle, uint16_t periodic)
{
	DEVICE_TIMEOUTS[handle].periodic = periodic;
}

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
