//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include "bleAPI.h"
#include "FreeRTOS_API.h"
#include "debugAPI.h"
#include "BM71.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/*******************************************************************************
* Description: All module init needed for the BLE
*
*******************************************************************************/
bool ble_init(void)
{
    return true;
}

/*******************************************************************************
* Description: FreeRTOS task for BLE
*
*******************************************************************************/
void task_ble(void* params)
{
    eventMsg_t rxMsg = {0};
    DEBUG_println(BLE, "BLE Task Started\n\r");
    eventQueue_sendMsg(kEVENT_INIT,kEVENT_NULL,0x00,0x00,NULL,kQUEUE_NULL,kQUEUE_BLE);
    
    //BLE Task Code
    while(1)
    {
        xQueueReceive(queueHandles[kQUEUE_BLE], &rxMsg, portMAX_DELAY);
        
        switch( rxMsg.mainEvent )
        {
            case kEVENT_INIT:
                BM71_init();
                break;
            default:
                break;
        }
    }
}
