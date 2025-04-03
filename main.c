/**
 * @file main.c
 * @brief Main application entry point using the modular IR servo library
 * @Reference Original and adjusted by Shanghong Lin @BUILD1, reorganized by Claude Sonnet 3.7
 * 
 * This main project handles object detection, weight sensing, and sorting
 * using IR sensors, servo motors, and wireless communication.
 * 
 * Pin assignments:
 * D4: IR_SEN (IR sensor)
 * PWM1OUT1: C1, PWM_SERVO
 * PWM1OUT2: C2, PWM_MOTOR
 * Analog Input: A0, WEI_SEN (Weight sensor)
 */
#include "mcc_generated_files/system/system.h"
#include "nrf24_lib.h"
#include "ir_servo.h"
#include <string.h>
#include <stdbool.h>

// NRF24-related variables
NRF24_INIT_STATUS ret;
unsigned char bufferRX[32];
#define NRF24L01_TX_EX  1
#define NRF24L01_RX_EX  !NRF24L01_TX_EX

int main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    // Enable global interrupts
    INTERRUPT_GlobalInterruptEnable();
    
    // Initialize the IR servo system
    ir_servo_initialize();
    
    // Initialize NRF24L01 module
    SPI1_Open(0);
    
    #if NRF24L01_TX_EX
        ret = nrf24_rf_init(TX_MODE, 103); // Tx mode with 2400+97 Ghz RF frq
    #elif NRF24L01_RX_EX
        ret = nrf24_rf_init(RX_MODE, 103); // Rx mode with 2400+97 Ghz RF frq
    #endif
    
    if (ret == NRF24_INIT_OK) {
        printf("###############################################################\r\n");
        printf("NRF24L01 Initialize successful\r\n");
        nrf24_printf_rf_config();
        __delay_ms(10);
        printf("###############################################################\r\n");
    } else {
        printf("###############################################################\r\n");
        printf("Failed Initialize NRF24L01\r\n");
        printf("###############################################################\r\n");
    }
    
    // Main loop
    while(1)
    {
        // Set default motor and servo position when idle
        if (!ir_servo_is_busy())
            reload_PWM1_dutyCycle(SERVO_IDLE, MOTOR_FAST);
        
        // Additional background tasks could be implemented here
        
        // Optional: Process any received NRF24 data
        // if (nrf24_is_data_available()) {
        //     nrf24_receive_rf_data(bufferRX);
        //     printf("Received: %s\n", bufferRX);
        // }
    }
}