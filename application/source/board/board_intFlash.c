//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include "driver_init.h"
#include "board_intFlash.h"
#include "debugAPI.h"

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/
static uint32_t page_size;

void brd_intFlash_init(void)
{
    uint8_t SBLK = hri_nvmctrl_read_SEESTAT_SBLK_bf(NVMCTRL);
    uint8_t PSZ = hri_nvmctrl_read_SEESTAT_PSZ_bf(NVMCTRL);
    DEBUG_println(DEBUG_SRC, "SBLK = %02X      PSZ = %02X\n\r", SBLK, PSZ);
 
    page_size = flash_get_page_size(&FLASH_0);
}

void brd_intFlash_writeConfigByte(uint8_t offset, uint8_t value)
{
    // Initialize our pointer to the Smart EEPROM
    uint8_t *pEEPROM = (uint8_t *) SEEPROM_ADDR + offset;
    
    // Wait until the module is no longer busy
    while(NVMCTRL->SEESTAT.bit.BUSY);
    
    // Write the config byte to our EEPROM
    *pEEPROM = value;
}

uint8_t brd_intFlash_readConfigByte(uint8_t offset)
{
    // Initialize our pointer to the Smart EEPROM
    uint8_t *pEEPROM = (uint8_t *) SEEPROM_ADDR + offset;
    
    // Wait until the module is no longer busy
    while(NVMCTRL->SEESTAT.bit.BUSY);
    
    // Return the value of the requested config byte
    return(*pEEPROM);
}