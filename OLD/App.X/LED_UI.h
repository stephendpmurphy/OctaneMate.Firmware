/**********************************************************
* Copyright 2017, Murphy Technology, All rights reserved. *
***********************************************************/
#ifndef LED_UI_H
#define	LED_UI_H

/************** TYPEDEFS ****************/
typedef struct STATUS_LED {
    uint16_t LED_STATE;
    TIMEOUT_HANDLE_t TIMEOUT_HANDLE;
} STATUS_LED_t;

enum LED_STATE_enum {
    LED_ON = 0x00,
    LED_OFF = 0x01,
    LED_FAST_FLASH = 0x00FA,
    LED_SLOW_FLASH = 0x01FA
};

/********* FUNCTION PROTOTYPES **********/
void InitLED_UI(void);
static void UpdateMCU_LED(void);
static void UpdateBluetooth_LED(void);
void SetLED_State(STATUS_LED_t, uint16_t);

/******* EXTERN / GLOBAL VARIABLE *******/
extern STATUS_LED_t MCU_LED;
extern STATUS_LED_t BLUETOOTH_LED;

#endif	/* LED_UI_H */
