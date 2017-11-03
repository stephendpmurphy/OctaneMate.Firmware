/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.26
        Device            :  PIC18F27K40
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set MCU_STATUS_LED aliases
#define MCU_STATUS_LED_TRIS               TRISAbits.TRISA0
#define MCU_STATUS_LED_LAT                LATAbits.LATA0
#define MCU_STATUS_LED_PORT               PORTAbits.RA0
#define MCU_STATUS_LED_WPU                WPUAbits.WPUA0
#define MCU_STATUS_LED_OD                ODCONAbits.ODCA0
#define MCU_STATUS_LED_ANS                ANSELAbits.ANSELA0
#define MCU_STATUS_LED_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define MCU_STATUS_LED_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define MCU_STATUS_LED_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define MCU_STATUS_LED_GetValue()           PORTAbits.RA0
#define MCU_STATUS_LED_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define MCU_STATUS_LED_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define MCU_STATUS_LED_SetPullup()      do { WPUAbits.WPUA0 = 1; } while(0)
#define MCU_STATUS_LED_ResetPullup()    do { WPUAbits.WPUA0 = 0; } while(0)
#define MCU_STATUS_LED_SetPushPull()    do { ODCONAbits.ODCA0 = 1; } while(0)
#define MCU_STATUS_LED_SetOpenDrain()   do { ODCONAbits.ODCA0 = 0; } while(0)
#define MCU_STATUS_LED_SetAnalogMode()  do { ANSELAbits.ANSELA0 = 1; } while(0)
#define MCU_STATUS_LED_SetDigitalMode() do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set BLUETOOTH_STATUS_LED aliases
#define BLUETOOTH_STATUS_LED_TRIS               TRISAbits.TRISA1
#define BLUETOOTH_STATUS_LED_LAT                LATAbits.LATA1
#define BLUETOOTH_STATUS_LED_PORT               PORTAbits.RA1
#define BLUETOOTH_STATUS_LED_WPU                WPUAbits.WPUA1
#define BLUETOOTH_STATUS_LED_OD                ODCONAbits.ODCA1
#define BLUETOOTH_STATUS_LED_ANS                ANSELAbits.ANSELA1
#define BLUETOOTH_STATUS_LED_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define BLUETOOTH_STATUS_LED_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define BLUETOOTH_STATUS_LED_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define BLUETOOTH_STATUS_LED_GetValue()           PORTAbits.RA1
#define BLUETOOTH_STATUS_LED_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define BLUETOOTH_STATUS_LED_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define BLUETOOTH_STATUS_LED_SetPullup()      do { WPUAbits.WPUA1 = 1; } while(0)
#define BLUETOOTH_STATUS_LED_ResetPullup()    do { WPUAbits.WPUA1 = 0; } while(0)
#define BLUETOOTH_STATUS_LED_SetPushPull()    do { ODCONAbits.ODCA1 = 1; } while(0)
#define BLUETOOTH_STATUS_LED_SetOpenDrain()   do { ODCONAbits.ODCA1 = 0; } while(0)
#define BLUETOOTH_STATUS_LED_SetAnalogMode()  do { ANSELAbits.ANSELA1 = 1; } while(0)
#define BLUETOOTH_STATUS_LED_SetDigitalMode() do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set IO_RA2 aliases
#define IO_RA2_TRIS               TRISAbits.TRISA2
#define IO_RA2_LAT                LATAbits.LATA2
#define IO_RA2_PORT               PORTAbits.RA2
#define IO_RA2_WPU                WPUAbits.WPUA2
#define IO_RA2_OD                ODCONAbits.ODCA2
#define IO_RA2_ANS                ANSELAbits.ANSELA2
#define IO_RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IO_RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IO_RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define IO_RA2_GetValue()           PORTAbits.RA2
#define IO_RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define IO_RA2_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define IO_RA2_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define IO_RA2_SetPushPull()    do { ODCONAbits.ODCA2 = 1; } while(0)
#define IO_RA2_SetOpenDrain()   do { ODCONAbits.ODCA2 = 0; } while(0)
#define IO_RA2_SetAnalogMode()  do { ANSELAbits.ANSELA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode() do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set IO_RA3 aliases
#define IO_RA3_TRIS               TRISAbits.TRISA3
#define IO_RA3_LAT                LATAbits.LATA3
#define IO_RA3_PORT               PORTAbits.RA3
#define IO_RA3_WPU                WPUAbits.WPUA3
#define IO_RA3_OD                ODCONAbits.ODCA3
#define IO_RA3_ANS                ANSELAbits.ANSELA3
#define IO_RA3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define IO_RA3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define IO_RA3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define IO_RA3_GetValue()           PORTAbits.RA3
#define IO_RA3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define IO_RA3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define IO_RA3_SetPullup()      do { WPUAbits.WPUA3 = 1; } while(0)
#define IO_RA3_ResetPullup()    do { WPUAbits.WPUA3 = 0; } while(0)
#define IO_RA3_SetPushPull()    do { ODCONAbits.ODCA3 = 1; } while(0)
#define IO_RA3_SetOpenDrain()   do { ODCONAbits.ODCA3 = 0; } while(0)
#define IO_RA3_SetAnalogMode()  do { ANSELAbits.ANSELA3 = 1; } while(0)
#define IO_RA3_SetDigitalMode() do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set AUX1_CS aliases
#define AUX1_CS_TRIS               TRISCbits.TRISC3
#define AUX1_CS_LAT                LATCbits.LATC3
#define AUX1_CS_PORT               PORTCbits.RC3
#define AUX1_CS_WPU                WPUCbits.WPUC3
#define AUX1_CS_OD                ODCONCbits.ODCC3
#define AUX1_CS_ANS                ANSELCbits.ANSELC3
#define AUX1_CS_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define AUX1_CS_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define AUX1_CS_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define AUX1_CS_GetValue()           PORTCbits.RC3
#define AUX1_CS_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define AUX1_CS_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define AUX1_CS_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define AUX1_CS_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define AUX1_CS_SetPushPull()    do { ODCONCbits.ODCC3 = 1; } while(0)
#define AUX1_CS_SetOpenDrain()   do { ODCONCbits.ODCC3 = 0; } while(0)
#define AUX1_CS_SetAnalogMode()  do { ANSELCbits.ANSELC3 = 1; } while(0)
#define AUX1_CS_SetDigitalMode() do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set AUX2_CS aliases
#define AUX2_CS_TRIS               TRISCbits.TRISC4
#define AUX2_CS_LAT                LATCbits.LATC4
#define AUX2_CS_PORT               PORTCbits.RC4
#define AUX2_CS_WPU                WPUCbits.WPUC4
#define AUX2_CS_OD                ODCONCbits.ODCC4
#define AUX2_CS_ANS                ANSELCbits.ANSELC4
#define AUX2_CS_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define AUX2_CS_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define AUX2_CS_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define AUX2_CS_GetValue()           PORTCbits.RC4
#define AUX2_CS_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define AUX2_CS_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define AUX2_CS_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define AUX2_CS_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define AUX2_CS_SetPushPull()    do { ODCONCbits.ODCC4 = 1; } while(0)
#define AUX2_CS_SetOpenDrain()   do { ODCONCbits.ODCC4 = 0; } while(0)
#define AUX2_CS_SetAnalogMode()  do { ANSELCbits.ANSELC4 = 1; } while(0)
#define AUX2_CS_SetDigitalMode() do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set AUX3_CS aliases
#define AUX3_CS_TRIS               TRISCbits.TRISC5
#define AUX3_CS_LAT                LATCbits.LATC5
#define AUX3_CS_PORT               PORTCbits.RC5
#define AUX3_CS_WPU                WPUCbits.WPUC5
#define AUX3_CS_OD                ODCONCbits.ODCC5
#define AUX3_CS_ANS                ANSELCbits.ANSELC5
#define AUX3_CS_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define AUX3_CS_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define AUX3_CS_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define AUX3_CS_GetValue()           PORTCbits.RC5
#define AUX3_CS_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define AUX3_CS_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define AUX3_CS_SetPullup()      do { WPUCbits.WPUC5 = 1; } while(0)
#define AUX3_CS_ResetPullup()    do { WPUCbits.WPUC5 = 0; } while(0)
#define AUX3_CS_SetPushPull()    do { ODCONCbits.ODCC5 = 1; } while(0)
#define AUX3_CS_SetOpenDrain()   do { ODCONCbits.ODCC5 = 0; } while(0)
#define AUX3_CS_SetAnalogMode()  do { ANSELCbits.ANSELC5 = 1; } while(0)
#define AUX3_CS_SetDigitalMode() do { ANSELCbits.ANSELC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
