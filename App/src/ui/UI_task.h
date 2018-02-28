/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

#ifndef UI_TASK_H_
#define UI_TASK_H_

/************ DEFINITIONS ***************/

/************** TYPEDEFS ****************/
typedef enum
{
	MCU_LED = 0x00,
	BLE_LED		
} UI_LED_t;

typedef enum
{
	UI_OFF = 0x0000,
	UI_SOLID = 0xFFFF,
	UI_FAST_FLASH = 0x00FA,
	UI_SLOW_FLASH = 0x03E8
} UI_LED_DUR_t;

typedef struct
{
	UI_LED_t led;
	UI_LED_DUR_t dur;
} UI_Task_Msg;

/********* FUNCTION PROTOTYPES **********/
void task_UI(void *p);

/******* EXTERN / GLOBAL VARIABLE *******/

#endif /* UI_TASK_H_ */