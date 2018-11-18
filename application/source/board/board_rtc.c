//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "driver_init.h"
#include "hal_timer.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
static struct timer_task TIMER_0_task1;
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void TIMER_0_task1_cb(const struct timer_task *const timer_task);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
uint16_t rtc_msec = 0;
uint8_t rtc_sec = 0;
uint8_t rtc_min = 0;
uint8_t rtc_hour = 0;

/*******************************************************************************
* Description: Debug board level init.
*******************************************************************************/
void brd_rtc_init(void)
{
    TIMER_0_task1.interval = 5;
    TIMER_0_task1.cb       = TIMER_0_task1_cb;
    TIMER_0_task1.mode     = TIMER_TASK_REPEAT;

    timer_add_task(&TIMER_0, &TIMER_0_task1);
    timer_start(&TIMER_0);
}

/*******************************************************************************
* Description: Return the current RTC milliseconds count.
*******************************************************************************/
uint16_t brd_rtc_getMsec()
{
    return(rtc_msec);    
}

/*******************************************************************************
* Description: Return the current RTC seconds count.
*******************************************************************************/
uint8_t brd_rtc_getSec()
{
    return(rtc_sec);
}

/*******************************************************************************
* Description: Return the current RTC minute count.
*******************************************************************************/
uint8_t brd_rtc_getMin()
{
    return(rtc_min);
}

/*******************************************************************************
* Description: Return the current RTC hour count.
*******************************************************************************/
uint8_t brd_rtc_getHour()
{
    return(rtc_hour);
}

/*******************************************************************************
* Description: Timer "Tick" callback. This will increment our clock value by
* 5 since our tick rate is every 5ms. This will also handle the overflow, and
* increment the next time units variable.
*******************************************************************************/
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
    // Increment ms count by 5ms.
    rtc_msec += 5;
    
    // If we reach 1000ms increment the second counter.
    if( 1000 == rtc_msec )
    {
        rtc_sec++;
        rtc_msec = 0;
    }
    
    // If we reach 60sec increment the minute counter.
    if( 60 == rtc_sec )
    {
        rtc_min++;
        rtc_sec = 0;
    }
    
    // If we reach 60min increment the hour counter.
    if( 60 == rtc_min )
    {
        rtc_hour++;
        rtc_min = 0;
    }
}