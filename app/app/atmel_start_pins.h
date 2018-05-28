/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAME51 has 14 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8
#define GPIO_PIN_FUNCTION_J 9
#define GPIO_PIN_FUNCTION_K 10
#define GPIO_PIN_FUNCTION_L 11
#define GPIO_PIN_FUNCTION_M 12
#define GPIO_PIN_FUNCTION_N 13

#define PA00 GPIO(GPIO_PORTA, 0)
#define PA01 GPIO(GPIO_PORTA, 1)
#define PA04 GPIO(GPIO_PORTA, 4)
#define PA05 GPIO(GPIO_PORTA, 5)
#define PA06 GPIO(GPIO_PORTA, 6)
#define SERIAL_FLASH_CS GPIO(GPIO_PORTA, 7)
#define PA09 GPIO(GPIO_PORTA, 9)
#define PA10 GPIO(GPIO_PORTA, 10)
#define CAN_INTF_EN GPIO(GPIO_PORTA, 12)
#define BT_EN GPIO(GPIO_PORTA, 13)
#define SERIAL_FLASH_EN GPIO(GPIO_PORTA, 14)
#define SERIAL_FLASH_RST GPIO(GPIO_PORTA, 16)
#define PA22 GPIO(GPIO_PORTA, 22)
#define PA23 GPIO(GPIO_PORTA, 23)
#define CAN0_STDBY GPIO(GPIO_PORTA, 24)
#define BT_CONF GPIO(GPIO_PORTB, 0)
#define BT_STATUS1_IND GPIO(GPIO_PORTB, 1)
#define BT_STATUS2_IND GPIO(GPIO_PORTB, 2)
#define BT_RSSI_IND GPIO(GPIO_PORTB, 3)
#define BT_PAIRING_KEY GPIO(GPIO_PORTB, 4)
#define BT_LINK_DROP GPIO(GPIO_PORTB, 5)
#define BT_RESET GPIO(GPIO_PORTB, 6)
#define BT_RF_ACTIVE_IND GPIO(GPIO_PORTB, 7)
#define MCU_STATUS_LED GPIO(GPIO_PORTB, 10)

#endif // ATMEL_START_PINS_H_INCLUDED
