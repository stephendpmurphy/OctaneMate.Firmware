#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "Timeout.h"
#include "NonVolatileMemory.h"

TIMEOUT_t DEVICE_TIMEOUTS[MAX_TIMER];
uint16_t _timer_tick = 0;



void timer_init(void)
{
    memset(DEVICE_TIMEOUTS, 0, sizeof(TIMEOUT_t));
}
