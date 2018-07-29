//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include "extFlash.h"
#include "driver_init.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
static void extFlash_setPowerEn(bool en);
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/*******************************************************************************
* Description: Init needed for the External Flash.
*
*******************************************************************************/
void extFlash_init(void)
{
	extFlash_setPowerEn(true);
}

/*******************************************************************************
* Description: Set the power enable pin of the External Flash. This takes into
* account the fact that the FET enable is active low.
*******************************************************************************/
static void extFlash_setPowerEn(bool en)
{
	//External Flash Power FET is Active Low.. So invert the bool logic
	gpio_set_pin_level(EXT_FLASH_NEN,false);
}
