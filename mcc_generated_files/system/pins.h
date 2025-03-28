/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
*/

/*
? [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set nRF24_CSN aliases
#define nRF24_CSN_TRIS                 TRISDbits.TRISD1
#define nRF24_CSN_LAT                  LATDbits.LATD1
#define nRF24_CSN_PORT                 PORTDbits.RD1
#define nRF24_CSN_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define nRF24_CSN_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define nRF24_CSN_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define nRF24_CSN_GetValue()           PORTDbits.RD1
#define nRF24_CSN_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define nRF24_CSN_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)

// get/set nRF24_CE aliases
#define nRF24_CE_TRIS                 TRISDbits.TRISD2
#define nRF24_CE_LAT                  LATDbits.LATD2
#define nRF24_CE_PORT                 PORTDbits.RD2
#define nRF24_CE_ANS                  ANSELDbits.ANSD2
#define nRF24_CE_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define nRF24_CE_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define nRF24_CE_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define nRF24_CE_GetValue()           PORTDbits.RD2
#define nRF24_CE_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define nRF24_CE_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define nRF24_CE_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define nRF24_CE_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set RA0 aliases
#define WEI_SEN_TRIS                 TRISAbits.TRISA0
#define WEI_SEN_LAT                  LATAbits.LATA0
#define WEI_SEN_PORT                 PORTAbits.RA0
#define WEI_SEN_WPU                  WPUAbits.WPUA0
#define WEI_SEN_OD                   ODCONAbits.ODCA0
#define WEI_SEN_ANS                  ANSELAbits.ANSELA0
#define WEI_SEN_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define WEI_SEN_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define WEI_SEN_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define WEI_SEN_GetValue()           PORTAbits.RA0
#define WEI_SEN_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define WEI_SEN_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define WEI_SEN_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define WEI_SEN_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define WEI_SEN_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define WEI_SEN_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define WEI_SEN_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define WEI_SEN_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RB4 aliases
#define IO_Debug_TRIS                 TRISBbits.TRISB4
#define IO_Debug_LAT                  LATBbits.LATB4
#define IO_Debug_PORT                 PORTBbits.RB4
#define IO_Debug_WPU                  WPUBbits.WPUB4
#define IO_Debug_OD                   ODCONBbits.ODCB4
#define IO_Debug_ANS                  ANSELBbits.ANSELB4
#define IO_Debug_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_Debug_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_Debug_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_Debug_GetValue()           PORTBbits.RB4
#define IO_Debug_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_Debug_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_Debug_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_Debug_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_Debug_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_Debug_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_Debug_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define IO_Debug_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RC1 aliases
#define PWM_SERVO_TRIS                 TRISCbits.TRISC1
#define PWM_SERVO_LAT                  LATCbits.LATC1
#define PWM_SERVO_PORT                 PORTCbits.RC1
#define PWM_SERVO_WPU                  WPUCbits.WPUC1
#define PWM_SERVO_OD                   ODCONCbits.ODCC1
#define PWM_SERVO_ANS                  ANSELCbits.ANSELC1
#define PWM_SERVO_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define PWM_SERVO_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define PWM_SERVO_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define PWM_SERVO_GetValue()           PORTCbits.RC1
#define PWM_SERVO_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define PWM_SERVO_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define PWM_SERVO_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define PWM_SERVO_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define PWM_SERVO_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define PWM_SERVO_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define PWM_SERVO_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define PWM_SERVO_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC2 aliases
#define PWM_MOTOR_TRIS                 TRISCbits.TRISC2
#define PWM_MOTOR_LAT                  LATCbits.LATC2
#define PWM_MOTOR_PORT                 PORTCbits.RC2
#define PWM_MOTOR_WPU                  WPUCbits.WPUC2
#define PWM_MOTOR_OD                   ODCONCbits.ODCC2
#define PWM_MOTOR_ANS                  ANSELCbits.ANSELC2
#define PWM_MOTOR_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define PWM_MOTOR_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define PWM_MOTOR_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define PWM_MOTOR_GetValue()           PORTCbits.RC2
#define PWM_MOTOR_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define PWM_MOTOR_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define PWM_MOTOR_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define PWM_MOTOR_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define PWM_MOTOR_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define PWM_MOTOR_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define PWM_MOTOR_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define PWM_MOTOR_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODCC3
#define IO_RC3_ANS                  ANSELCbits.ANSELC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_OD                   ODCONCbits.ODCC4
#define IO_RC4_ANS                  ANSELCbits.ANSELC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define IO_RC4_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 aliases
#define IO_RC5_TRIS                 TRISCbits.TRISC5
#define IO_RC5_LAT                  LATCbits.LATC5
#define IO_RC5_PORT                 PORTCbits.RC5
#define IO_RC5_WPU                  WPUCbits.WPUC5
#define IO_RC5_OD                   ODCONCbits.ODCC5
#define IO_RC5_ANS                  ANSELCbits.ANSELC5
#define IO_RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define IO_RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define IO_RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define IO_RC5_GetValue()           PORTCbits.RC5
#define IO_RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define IO_RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define IO_RC5_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define IO_RC5_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define IO_RC5_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define IO_RC5_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define IO_RC5_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define IO_RC5_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RD1 aliases
#define IO_RD1_TRIS                 TRISDbits.TRISD1
#define IO_RD1_LAT                  LATDbits.LATD1
#define IO_RD1_PORT                 PORTDbits.RD1
#define IO_RD1_WPU                  WPUDbits.WPUD1
#define IO_RD1_OD                   ODCONDbits.ODCD1
#define IO_RD1_ANS                  ANSELDbits.ANSELD1
#define IO_RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define IO_RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define IO_RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define IO_RD1_GetValue()           PORTDbits.RD1
#define IO_RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define IO_RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define IO_RD1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define IO_RD1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define IO_RD1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define IO_RD1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define IO_RD1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define IO_RD1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set RD2 aliases
#define IO_RD2_TRIS                 TRISDbits.TRISD2
#define IO_RD2_LAT                  LATDbits.LATD2
#define IO_RD2_PORT                 PORTDbits.RD2
#define IO_RD2_WPU                  WPUDbits.WPUD2
#define IO_RD2_OD                   ODCONDbits.ODCD2
#define IO_RD2_ANS                  ANSELDbits.ANSELD2
#define IO_RD2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define IO_RD2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define IO_RD2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define IO_RD2_GetValue()           PORTDbits.RD2
#define IO_RD2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define IO_RD2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define IO_RD2_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define IO_RD2_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define IO_RD2_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define IO_RD2_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define IO_RD2_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define IO_RD2_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set RD4 aliases
#define IR_SEN_TRIS                 TRISDbits.TRISD4
#define IR_SEN_LAT                  LATDbits.LATD4
#define IR_SEN_PORT                 PORTDbits.RD4
#define IR_SEN_WPU                  WPUDbits.WPUD4
#define IR_SEN_OD                   ODCONDbits.ODCD4
#define IR_SEN_ANS                  ANSELDbits.ANSELD4
#define IR_SEN_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define IR_SEN_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define IR_SEN_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define IR_SEN_GetValue()           PORTDbits.RD4
#define IR_SEN_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define IR_SEN_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define IR_SEN_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define IR_SEN_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define IR_SEN_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define IR_SEN_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define IR_SEN_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define IR_SEN_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set RF0 aliases
#define IO_RF0_TRIS                 TRISFbits.TRISF0
#define IO_RF0_LAT                  LATFbits.LATF0
#define IO_RF0_PORT                 PORTFbits.RF0
#define IO_RF0_WPU                  WPUFbits.WPUF0
#define IO_RF0_OD                   ODCONFbits.ODCF0
#define IO_RF0_ANS                  ANSELFbits.ANSELF0
#define IO_RF0_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define IO_RF0_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define IO_RF0_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define IO_RF0_GetValue()           PORTFbits.RF0
#define IO_RF0_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define IO_RF0_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define IO_RF0_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define IO_RF0_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define IO_RF0_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define IO_RF0_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define IO_RF0_SetAnalogMode()      do { ANSELFbits.ANSELF0 = 1; } while(0)
#define IO_RF0_SetDigitalMode()     do { ANSELFbits.ANSELF0 = 0; } while(0)

// get/set RF1 aliases
#define IO_RF1_TRIS                 TRISFbits.TRISF1
#define IO_RF1_LAT                  LATFbits.LATF1
#define IO_RF1_PORT                 PORTFbits.RF1
#define IO_RF1_WPU                  WPUFbits.WPUF1
#define IO_RF1_OD                   ODCONFbits.ODCF1
#define IO_RF1_ANS                  ANSELFbits.ANSELF1
#define IO_RF1_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define IO_RF1_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define IO_RF1_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define IO_RF1_GetValue()           PORTFbits.RF1
#define IO_RF1_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define IO_RF1_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define IO_RF1_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define IO_RF1_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define IO_RF1_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define IO_RF1_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define IO_RF1_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define IO_RF1_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)

// get/set RF3 aliases
#define IO_LED_TRIS                 TRISFbits.TRISF3
#define IO_LED_LAT                  LATFbits.LATF3
#define IO_LED_PORT                 PORTFbits.RF3
#define IO_LED_WPU                  WPUFbits.WPUF3
#define IO_LED_OD                   ODCONFbits.ODCF3
#define IO_LED_ANS                  ANSELFbits.ANSELF3
#define IO_LED_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define IO_LED_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define IO_LED_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define IO_LED_GetValue()           PORTFbits.RF3
#define IO_LED_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define IO_LED_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define IO_LED_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define IO_LED_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define IO_LED_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define IO_LED_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define IO_LED_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define IO_LED_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/