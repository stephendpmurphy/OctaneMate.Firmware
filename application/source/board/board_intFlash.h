//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------

#include <stdint.h>

#define DEVICE_SN_WORD0_ADDR		0x008061FC
#define DEVICE_SN_WORD1_ADDR		0x00806010
#define DEVICE_SN_WORD2_ADDR		0x00806014
#define DEVICE_SN_WORD3_ADDR		0x00806018

void intFlash_test(void);
void brd_intFlash_init(void);
void brd_intFlash_writeConfigByte(uint8_t offset, uint8_t value);
uint8_t brd_intFlash_readConfigByte(uint8_t offset);
