//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdbool.h>
#include "driver_init.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"
#include "version.h"
#include "BM71.h"
#include "extFlash.h"
#include "configAPI.h"
#include "board_BM71.h"
#include "board_debug.h"
#include "board_intFlash.h"
#include "board_rtc.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void FreeRTOS_init(void);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/*******************************************************************************
* Description: Main entry point for the App.
*
*******************************************************************************/
int main(void)
{
    system_init();
    
    brd_rtc_init();
    //Debug init
    brd_debug_init();
    debug_init();
    DEBUG_println(MAIN, "MurphyTechnology OctaneMate v%d.%d.%d - %s %s\n\n\r", PRODUCT_VERSION, HW_VERSION, FW_VERSION, __DATE__, __TIME__);
    
    //Board init
    brd_BM71_init();
    brd_intFlash_init();
    //BRD_extFlash_init();

    //Module init
    config_init();
    extFlash_init();

    //Initialize FreeRTOS and start the scheduler.. Should not return from this function call.
    FreeRTOS_init();

    //Something went wrong.. Stop here.
    DEBUG_halt();
}

/*******************************************************************************
* Description: Hook for ARM Cortex hard faults.
*
*******************************************************************************/
void HardFault_Handler()
{
    DEBUG_println(MAIN, "!!! Hard fault !!!");
    DEBUG_halt();
}

/*******************************************************************************
* Description: Hook for stack overflows.
*
*******************************************************************************/
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
    DEBUG_println(MAIN, "%s overflowed its stack!", pcTaskName);
    DEBUG_halt();
}

void vApplicationIdleHook( void )
{
    //DEBUG_println("!!! IDLE !!!\n\r"); 
}

void vApplicationTickHook(void)
{
    //DEBUG_println("!!! TICK !!!\n\r");
}

/*******************************************************************************
* Description: This handles all of the FreeRTOS init for queues and tasks. Once
* finished it also starts the scheduler.
*******************************************************************************/
static void FreeRTOS_init(void)
{
    //Init all of the Module Tasks
    if( !tasks_CreateTasks() )
    {
        DEBUG_println(MAIN, "Failed to create task(s)");
        DEBUG_halt();
    }

    //Init all of the Module Queues
    if( !eventQueue_CreateQueues() )
    {
        DEBUG_println(MAIN, "Failed to create queue(s)");
        DEBUG_halt();
    }

    //Start the FreeRTOS scheduler..
    vTaskStartScheduler();

    //Should never have returned from the above call..
    DEBUG_println(MAIN, "!!! ERROR !!! Scheduler returned...");
}
