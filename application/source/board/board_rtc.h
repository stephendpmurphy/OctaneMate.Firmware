//------------------------------------------------------------------------------
// Copyright(c)2018 Murphy Technology as an unpublished work.
//
// The information contained herein is confidential property of Murphy Technology.
// All rights reserved. Reproduction, adaptation, or translation without the
// express written consent of Murphy Technology is prohibited, except as allowed
// under the copyright laws.
//------------------------------------------------------------------------------
#ifndef BOARD_RTC_H_
#define BOARD_RTC_H_

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
void brd_rtc_init(void);
uint16_t brd_rtc_getMsec();
uint8_t brd_rtc_getSec();
uint8_t brd_rtc_getMin();
uint8_t brd_rtc_getHour();

/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

#endif /* BOARD_RTC_H_ */