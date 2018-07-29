//------------------------------------------------------------------------------
//  Copyright(c)2018 Murphy Technology as an unpublished work.
//
//  The information contained herein is confidential property of Murphy Technology.
//  All rights reserved.  Reproduction, adaptation, or translation without the
//  express written consent of Murphy Technology is prohibited, except as allowed
//  under the copyright laws.
//------------------------------------------------------------------------------


#ifndef BM71_H_
#define BM71_H_

/*-------------- DEFINITIONS -------------------------------------------------*/
/*-------------- TYPEDEFS ----------------------------------------------------*/
/*-------------- FUNCTION PROTOTYPES -----------------------------------------*/
/*-------------- VARIABLE DEFINITIONS ----------------------------------------*/

/************ DEFINITIONS ***************/
#define BM71_DEFAULT_BAUD_RATE	115200
#define BM71_MAX_COMMAND_LENGTH 147

/************** TYPEDEFS ****************/
/********* FUNCTION PROTOTYPES **********/
void BM71_init(void);
void BM71_readLocalInfo(void);
uint8_t BM71_readStatus(void);
void BM71_readDeviceName(void);
void BM71_writeDeviceName(void);
void BM71_setAdvertisingEnable(uint8_t val);

void BM71_PulseRSTPin(void);
void BM71_Reset(void);
void BM71_ResetToTestMode(void);
void BM71_ResetToAppMode(void);
void BM71_enterAppMode(void);
uint16_t BM71_sendAppCommand(uint8_t sendSize);
void BM71_calculateCRC(uint8_t *buffer, uint8_t len);
void BM71_clearWriteBuffer(void);
void BM71_clearReadBuffer(void);
void BM71_loadWriteBuffer( const uint8_t *command, uint8_t bytes);

/******* EXTERN / GLOBAL VARIABLE *******/
extern uint8_t BM71_writeBuffer[BM71_MAX_COMMAND_LENGTH];
extern uint8_t BM71_readBuffer[BM71_MAX_COMMAND_LENGTH];

#endif /* BM71_H_ */
