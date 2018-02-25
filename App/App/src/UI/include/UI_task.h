#ifndef UI_TASK_H_
#define UI_TASK_H_


/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

/************ DEFINITIONS ***************/

/************** TYPEDEFS ****************/
typedef enum
{
	UI_OFF = 0x00,
	UI_SOLID,
	UI_FAST_FLASH,
	UI_SLOW_FLASH
} UI_LED_STATE_t;

/********* FUNCTION PROTOTYPES **********/
void task_UI(void);
/******* EXTERN / GLOBAL VARIABLE *******/

#endif /* UI_TASK_H_ */