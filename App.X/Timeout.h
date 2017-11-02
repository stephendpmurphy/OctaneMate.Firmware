/* 
 * File:   Timeout.h
 * Author: smurphy
 *
 * Created on November 2, 2017, 1:55 PM
 */

#ifndef TIMEOUT_H
#define	TIMEOUT_H

//Definitions
#define MAX_TIMER 10

//Typedefs
typedef struct TIMEOUT_STRUCT
{
    uint16_t expiry;
    uint16_t periodic;
    void (*callback)(void *);
    void *arg;
} TIMEOUT_t;

//Global Variables
extern TIMEOUT_t DEVICE_TIMEOUTS[MAX_TIMER];
extern uint16_t _timer_tick = 0;

//Function Prototypes

#endif	/* TIMEOUT_H */

