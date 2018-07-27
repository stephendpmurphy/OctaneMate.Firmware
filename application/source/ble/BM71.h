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
#define MAX_DATA_LENGTH 127
#define MAX_COMMAND_LENGTH 132

/************** TYPEDEFS ****************/
/********* FUNCTION PROTOTYPES **********/
void BM71_init(void);
void BM71_readLocalInfo(void);
void BM71_PulseRSTPin(void);
void BM71_Reset(void);
void BM71_ResetToTestMode(void);
void BM71_ResetToAppMode(void);
void BM71_enterAppMode(void);
void BM71_sendAppCommand(uint8_t sendSize);
void BM71_calculateCRC(uint8_t *buffer, uint8_t len);
void BM71_setResetPin(bool en);
void BM71_setPowerEn(bool en);
void BM71_setConfigPin(bool en);
void BM71_clearWriteBuffer(void);
void BM71_clearReadBuffer(void);
void BM71_loadSendBuffer( const uint8_t *command, uint8_t bytes);

/******* EXTERN / GLOBAL VARIABLE *******/
extern uint8_t BM71_writeBuffer[147];
extern uint8_t BM71_readBuffer[147];

#endif /* BM71_H_ */
