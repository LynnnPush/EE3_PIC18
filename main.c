
/*This main project lets PIC18 adjust the PWM duty cycle according to the
 * potential meter value, and print the ADC value on the terminal of Data Visualizer
 * at the same time
 * 
 * NOTE: The following pin notes may not be the latest. 
 * Check MCC Pin Grid View for confirmation
 * D4: IR_SEN (IR sensor)
 * PWM1OUT1: C1, PWM_SERVO
 * PWM1OUT2: C2, PWM_MOTOR
 * Analog Input: A0, WEI_SEN (Weight sensor)
*/
#include "mcc_generated_files/system/system.h"
#include "nrf24_lib.h"
#include <string.h>

// Counter of detected object
uint8_t itemNbr;
// Weight sensor value
adc_result_t itemWeight;
#define WEIGHT_MIN 10   //Random nbr now. Replace after testing
#define WEIGHT_MAX 2600  //Random nbr now. Replace after testing


// Load the PWM period to the variable
uint16_t totalPeriod;
// Duty Cycle ratio:
#define SERVO_PUSH 0.023
#define SERVO_IDLE 0.08
#define MOTOR_FAST 0.75
#define MOTOR_SLOW 0.25
#define DUTYCYCLE_RATIO_CONVERT(P)  (uint16_t)((double)(P)*totalPeriod)


// Define the NRF24-related buffer and variables:
NRF24_INIT_STATUS ret;
//unsigned char i;
char buffer1[20];
unsigned char bufferTX[32];
unsigned char bufferRX[32];
#define NRF24L01_TX_EX  1
#define NRF24L01_RX_EX  !NRF24L01_TX_EX

/**
 * Load the new duty cycle to both slices
 * For some unkonwn reasons, u have to execute PWM1_16BIT_LoadBufferRegisters();
 * after setting the new duty cycle, otherwise it will not load to the register.
 * But if u just set one of the slices,the other slices' duty cycle will first set back
 * to initial value, then rolls back to the last assigned value.
 * Thus ALWAYS set 2 slices at the same time, eventhough u only need 1 to change.
 * 
 * The value of slice1 and slice2 should be decimal(percentage)
 */
void reload_PWM1_dutyCycle(double slice1, double slice2)
{
    PWM1_16BIT_LoadBufferRegisters();
    PWM1_16BIT_SetSlice1Output1DutyCycleRegister(DUTYCYCLE_RATIO_CONVERT(slice1));
    PWM1_16BIT_SetSlice1Output2DutyCycleRegister(DUTYCYCLE_RATIO_CONVERT(slice2));
}

/*
 * Main operation mode.
 * ISR of INT1, triggered by falling edge (object detected) of IR_SEN (RD4)
 */ 
void ir_servo()
{
    EXT_INT1_InterruptDisable();
    __delay_ms(1000);
     
    itemNbr++;
    (void) printf("itemNumber: %d\r\n", itemNbr);
    __delay_ms(1000);    //wait to let object reach detected zone

    // Read the weight sensor value
    ADC_SampleCapacitorDischarge();
    itemWeight = ADC_ChannelSelectAndConvert(ADC_CHANNEL_ANA0);
    (void) printf("itemWeight %d\r\n", itemWeight);
    
    // Enter different state based on itemWeight
    if (itemWeight>=WEIGHT_MIN && itemWeight<=WEIGHT_MAX)
    {
        // TODO: Send records to ESP32, e.g. itemNbr, itemWeight, itemStatus etc.
        sprintf((char*)bufferTX, "%d", itemNbr);
        nrf24_send_rf_data(bufferTX);
        
        sprintf((char*)bufferTX, "%d", itemWeight);
        nrf24_send_rf_data(bufferTX);
        
        sprintf((char*)bufferTX, " ACC");
        nrf24_send_rf_data(bufferTX);
        
        (void) printf("itemWeight is ACCEPTED\n");
        (void) printf("\n");
        return; 
    }
               
    else
    {
        (void) printf("itemWeight is REJECTED\n");
        // TODO: Send records to ESP32, e.g. itemNbr, itemWeight, itemStatus etc.
        
        memset(bufferTX, 0, sizeof(bufferTX));
        bufferTX[0] = '1';  // Packet type identifier
        // Store integer values directly as bytes
//        bufferTX[1] = itemNbr & 0xFF;
//        bufferTX[2] = itemWeight & 0xFF;
        bufferTX[1] = '2';
        bufferTX[2] = '3';
        bufferTX[3] = 'R';
        bufferTX[4] = 'E';
        bufferTX[5] = 'J';
        nrf24_send_rf_data(bufferTX);
        printf("[Send] Data: %d,%d,%s\n", itemNbr, itemWeight, "REJ");
        
//        sprintf((char*)bufferTX, "%d ", itemNbr);
//        nrf24_send_rf_data(bufferTX);
//        printf("[Send]itemNbr: %d\n", itemNbr);
//         __delay_ms(10);
//        
//        sprintf((char*)bufferTX, "%d", itemWeight);
//        nrf24_send_rf_data(bufferTX);
//        printf("[Send]itemWeight: %d\n", itemWeight);
//        __delay_ms(10);
//        
//        sprintf((char*)bufferTX, "REJ ");
//        printf("[Send]itemStatus: REJ\n");
//        nrf24_send_rf_data(bufferTX);
//        __delay_ms(10);
        
        // STEP1:
        // Servo:IDLE  Motor:FAST -> STOP
        reload_PWM1_dutyCycle(SERVO_IDLE, 0);
        __delay_ms(500);
        
        // STEP2:
        // Servo:IDLE -> PUSH  Motor:STOP
        reload_PWM1_dutyCycle(SERVO_PUSH, 0);
        __delay_ms(2000);
        
        // STEP3:
        // Servo:PUSH -> IDLE  Motor:STOP -> FAST
        reload_PWM1_dutyCycle(SERVO_IDLE, MOTOR_FAST);
    }
    
    (void) printf("\n");
}

int main(void)
{
    //Initialize the device
    SYSTEM_Initialize();
    totalPeriod = ((uint16_t)PWM1PRH << 8) | PWM1PRL;
    
    // Enable interrupts
    INTERRUPT_GlobalInterruptEnable();
    INT1_SetInterruptHandler(ir_servo);
//    TMR0_PeriodMatchCallbackRegister();
    
    itemNbr=0;
    
    //Open SPI1:
    SPI1_Open(0);
    
    // Set and examine status of NRF24
    #if NRF24L01_TX_EX
        ret = nrf24_rf_init(TX_MODE, 97); // Tx mode with 2400+97 Ghz RF frq
    #elif NRF24L01_RX_EX
        ret = nrf24_rf_init(RX_MODE, 90); // Rx mode with 2400+97 Ghz RF frq
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
    // Actuators in working mode:
         
        while(1)
        {
//            if (ret == NRF24_INIT_OK) {
//
//                printf("###############################################################\r\n");
//                printf("NRF24L01 Initialize successful\r\n");
//                nrf24_printf_rf_config();
//                __delay_ms(1000);
//                printf("###############################################################\r\n");
//            } else {
//                printf("###############################################################\r\n");
//                printf("Failed Initialize NRF24L01\r\n");
//                printf("###############################################################\r\n");
//                __delay_ms(1000);
//            }
            
//            printf("Hello World\n");
//            __delay_ms(500);
            
            
            if (!PIE6bits.INT1IE)
            {
                EXT_INT1_InterruptFlagClear();
                __delay_ms(1000);
                EXT_INT1_InterruptEnable();
            }
             reload_PWM1_dutyCycle(SERVO_IDLE, MOTOR_FAST);      
            
        }
        
}