/**********************************************************
* Copyright 2017, Murphy Technology, All rights reserved. *
***********************************************************/
#ifndef TIMEOUT_H
#define	TIMEOUT_H

/************ DEFINITIONS ***************/
#define MAX_TIMER 4
#define TIME_ROLLOVER 60000 //ms or 1 minute

/************** TYPEDEFS ****************/
typedef struct TIMEOUT_STRUCT
{
    uint8_t enabled;
    uint16_t timeout_ref;
    uint16_t periodic;
    void(*callback)(void);
    void *arg;
} TIMEOUT_t;

typedef enum TIMEOUT_HANDLE
{
    MCU_LED_TIMEOUT = 0x00,
    BLUETOOTH_LED_TIMEOUT,
    TEN_HZ_LOG_TIMEOUT,
    TWENTY_HZ_LOG_TIMEOUT
} TIMEOUT_HANDLE_t;

/********* FUNCTION PROTOTYPES **********/
void InitTimer(void);
void AddTimer(TIMEOUT_HANDLE_t handle, uint8_t enabled, uint16_t periodic, void(*callback)(void), void *arg);
void SetTimerStatus(TIMEOUT_HANDLE_t handle, uint8_t enabled);
void SetTimerPeriodic(TIMEOUT_HANDLE_t handle, uint16_t periodic);
void ServiceTimers(void);

/******* EXTERN / GLOBAL VARIABLE *******/
extern uint16_t _timer_tick;

#endif	/* TIMEOUT_H */
