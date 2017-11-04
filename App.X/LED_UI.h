/*
 * File:   LED_UI.h
 * Author: Steve
 *
 * Created on November 3, 2017, 10:53 AM
 */

#ifndef LED_UI_H
#define	LED_UI_H

#define BLUETOOTH_STATUS_LED 0x00
#define MCU_STATUS_LED = 0x01

#define LED_OFF_DUR 0x0000 //Periodic of Zero - Essentially a one shot. Turns the LED OFF and then disables the timer
#define LED_ON_DUR 0x0000 //Periodic of Zero - Essentially a one shot. Turns the LED ON and then disables the timer
#define LED_FAST_DUR 0x00FA
#define LED_SLOW_DUR 0x01FA

typedef struct STATUS_LED {
    LED_STATE_t LED_STATE;
    TIMEOUT_HANDLE_t TIMEOUT_HANDLE;
} STATUS_LED_t;

typedef enum LED_STATE
{
    LED_STATE_OFF = LED_OFF_DUR,
    LED_STATE_ON = LED_ON_DUR,
    LED_STATE_BLINK_SLOW = LED_SLOW_DUR,
    LED_STATE_BLINK_FAST = LED_FAST_DUR
} LED_STATE_t;

//Function Prototypes
static void UpdateMCU_LED(void);
static void UpdateBluetooth_LED(void);

#endif	/* LED_UI_H */
