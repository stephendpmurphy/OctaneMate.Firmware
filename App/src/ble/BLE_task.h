/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

#ifndef BLE_TASK_H_
#define BLE_TASK_H_

/************ DEFINITIONS ***************/
//#define BLE_USART_BUFFER_SIZE 2000
//#define BLE_USART_Handler FLEXCOM0_Handler
//#define BLE_USART_IRQn	FLEXCOM0_IRQn
/************** TYPEDEFS ****************/

/********* FUNCTION PROTOTYPES **********/
void task_BLE(void *p);
void BLE_initTask(void);

/******* EXTERN / GLOBAL VARIABLE *******/

#endif /* BLE_TASK_H_ */