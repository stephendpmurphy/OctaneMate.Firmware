//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include <stdbool.h>
#include "board_extFlash.h"
#include "driver_init.h"
#include "hal_gpio.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/*******************************************************************************
* Description: Set the power enable pin of the External Flash. This takes into
* account the fact that the FET enable is active low.
*******************************************************************************/
void BRD_extFlash_setPowerEn(bool en)
{
	//External Flash Power FET is Active Low.. So invert the bool logic
	gpio_set_pin_level(EXT_FLASH_NEN,false);
}
