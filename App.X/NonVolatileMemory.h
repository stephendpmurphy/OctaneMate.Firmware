/* 
 * File:   NonVolatileMemory.h
 * Author: smurphy
 *
 * Created on November 2, 2017, 1:38 PM
 */

#ifndef NONVOLATILEMEMORY_H
#define	NONVOLATILEMEMORY_H

//DEFINITIONS
#define MAX_PID_CHANNELS 20
#define PSEUDO_UNUSED_PID_VAL 0xFF

//TYPEDEFS
typedef enum DISPLAY_TYPE_ENUM {
    NONE,
    LOG,
    DISPLAY
}PID_CHANNEL_DISPLAY_t;

typedef struct PID_CHANNEL_CONFIG_STRUCT
{
    uint8_t ID;
    PID_CHANNEL_DISPLAY_t display_type;
    uint8_t PID_val;
    uint8_t raw_result;
    uint8_t conv_result;
    uint8_t poll_rate;
    uint16_t next_poll;
} PID_CHANNEL_CONFIG_t;

typedef struct DEVICE_CONFIG_STRUCT
{
    uint8_t temp;
} DEVICE_CONFIG_t;

//GLOBAL VARIABLES
extern PID_CHANNEL_CONFIG_t PID_CHANNEL_CONFIG[MAX_PID_CHANNELS];
extern DEVICE_CONFIG_t DEVICE_CONFIG;
//FUNCTION PROTOTYPES

#endif	/* NONVOLATILEMEMORY_H */

