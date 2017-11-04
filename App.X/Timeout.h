/*
 * File:   Timeout.h
 * Author: smurphy
 *
 * Created on November 2, 2017, 1:55 PM
 */

#ifndef TIMEOUT_H
#define	TIMEOUT_H

//Definitions
#define MAX_TIMER 4

//Timeout handles

//Typedefs
typedef struct TIMEOUT_STRUCT
{
    uint8_t enabled;
    uint16_t timeout_ms;
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

//Global Variables
extern uint16_t _timer_tick;

//Function Prototypes
void InitTimer(void);
void AddTimer(TIMEOUT_HANDLE_t handle, uint8_t enabled, uint16_t timeout_ms, uint16_t periodic, void(*callback)(void), void *arg);
void SetTimerStatus(TIMEOUT_HANDLE_t handle, uint8_t enabled);
void SetTimerPeriodic(TIMEOUT_HANDLE_t handle, uint16_t periodic);

#endif	/* TIMEOUT_H */
