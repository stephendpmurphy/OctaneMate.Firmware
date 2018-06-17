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

#define EXT_FLASH_MOSI GPIO(GPIO_PORTA, 4)
#define EXT_FLASH_SCK GPIO(GPIO_PORTA, 5)
#define EXT_FLASH_MISO GPIO(GPIO_PORTA, 6)
#define EXT_FLASH_CS GPIO(GPIO_PORTA, 7)
#define BT_CONF GPIO(GPIO_PORTA, 14)
#define BT_STATUS1_IND GPIO(GPIO_PORTA, 15)
#define BT_STATUS2_IND GPIO(GPIO_PORTA, 16)
#define BT_PAIRING_KEY GPIO(GPIO_PORTA, 18)
#define BT_RSSI_IND GPIO(GPIO_PORTA, 19)
#define BT_UART_RX GPIO(GPIO_PORTA, 21)
#define BT_LINK_DROP GPIO(GPIO_PORTA, 22)
#define EXT_FLASH_NEN GPIO(GPIO_PORTA, 23)
#define BT_UART_TX GPIO(GPIO_PORTA, 24)
#define BT_NEN GPIO(GPIO_PORTA, 25)
#define MCU_STATUS_LED GPIO(GPIO_PORTA, 27)
#define EXT_FLASH_NRST GPIO(GPIO_PORTB, 9)
#define CAN1_STDBY GPIO(GPIO_PORTB, 11)
#define CAN1_TX GPIO(GPIO_PORTB, 14)
#define CAN1_RX GPIO(GPIO_PORTB, 15)
#define BT_NRST GPIO(GPIO_PORTB, 16)
#define BT_RF_ACTIVE_IND GPIO(GPIO_PORTB, 17)
#define DEBUG_UART_RX GPIO(GPIO_PORTB, 30)
#define DEBUG_UART_TX GPIO(GPIO_PORTB, 31)

#endif // ATMEL_START_PINS_H_INCLUDED
