/**********************************************************
* Copyright 2018, Murphy Technology, All rights reserved. *
***********************************************************/

#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMG has 4 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3

#define MCU_STATUS_LED GPIO(GPIO_PORTA, 6)
#define PA9 GPIO(GPIO_PORTA, 9)
#define PA10 GPIO(GPIO_PORTA, 10)
#define BLE_STATUS_LED GPIO(GPIO_PORTA, 11)
#define STN_STATUS_LED GPIO(GPIO_PORTA, 12)
#define PB0 GPIO(GPIO_PORTB, 0)
#define PB1 GPIO(GPIO_PORTB, 1)
#define PB2 GPIO(GPIO_PORTB, 2)
#define PB3 GPIO(GPIO_PORTB, 3)

#endif // ATMEL_START_PINS_H_INCLUDED
