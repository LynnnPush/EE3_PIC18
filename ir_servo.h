/**
 * @file ir_servo.h
 * @brief Timer-based IR sensor and servo control system header file
 * 
 * This module manages the detection of objects using an IR sensor,
 * weighing them, and sorting items based on weight thresholds.
 */

#ifndef IR_SERVO_H
#define IR_SERVO_H

#include <stdint.h>
#include <stdbool.h>

// State enumeration for the IR servo state machine
typedef enum {
    IR_STATE_IDLE,           // Initial state, waiting for IR detection
    IR_STATE_WEIGHT_READ,    // After IR detection, reading weight
    IR_STATE_REJECT_STEP1,   // Step 1 of rejection process
    IR_STATE_REJECT_STEP2,   // Step 2 of rejection process
    IR_STATE_REJECT_STEP3,   // Step 3 of rejection process
    IR_STATE_COMPLETE        // Process complete
} ir_servo_state_t;

// Weight sensor threshold definitions
#define WEIGHT_MIN 10    // Minimum acceptable weight
#define WEIGHT_MAX 2600  // Maximum acceptable weight

// PWM period and duty cycle ratios
static uint16_t totalPeriod;
#define SERVO_PUSH 0.11
#define SERVO_IDLE 0.023
#define MOTOR_FAST 0.75
#define MOTOR_SLOW 0.25
#define DUTYCYCLE_RATIO_CONVERT(P)  (uint16_t)((double)(P)*totalPeriod)

// Status code of the item
#define REJECTED 0
#define ACCEPTED 1

/**
 * @brief Initialize the IR servo system
 * 
 * Sets up the state machine, registers the TMR0 callback,
 * and configures the IR sensor interrupt.
 */
void ir_servo_initialize(void);

/**
 * @brief Start the IR servo process
 * 
 * Called when an IR sensor detection occurs.
 * Begins the weight measurement and sorting process.
 */
void ir_servo_start(void);

/**
 * @brief Check if the IR servo system is currently processing an item
 * 
 * @return true if the system is busy, false if idle
 */
bool ir_servo_is_busy(void);

/**
 * @brief Get the current count of detected items
 * 
 * @return Number of items detected since initialization
 */
uint8_t ir_servo_get_item_count(void);

/**
 * @brief Get the most recently measured item weight
 * 
 * @return Weight of the last item in ADC units
 */
uint16_t ir_servo_get_last_weight(void);

/**
 * @brief Get the minimum acceptable weight threshold
 * 
 * @return Current minimum weight threshold
 */
uint16_t ir_servo_get_min_weight(void);

/**
 * @brief Get the maximum acceptable weight threshold
 * 
 * @return Current maximum weight threshold
 */
uint16_t ir_servo_get_max_weight(void);

/**
 * @brief Set the minimum acceptable weight threshold
 * 
 * @param min_weight New minimum weight threshold
 */
void ir_servo_set_min_weight(uint16_t min_weight);

/**
 * @brief Set the maximum acceptable weight threshold
 * 
 * @param max_weight New maximum weight threshold
 */
void ir_servo_set_max_weight(uint16_t max_weight);

/**
 * @brief Load new duty cycle values to both PWM slices
 * 
 * This function updates the duty cycle for both the servo and motor PWM outputs.
 * Always sets both slices at the same time to avoid register conflicts.
 * 
 * @param slice1 Duty cycle ratio for slice 1 (servo) as a decimal value (0.0-1.0)
 * @param slice2 Duty cycle ratio for slice 2 (motor) as a decimal value (0.0-1.0)
 */
void reload_PWM1_dutyCycle(double slice1, double slice2);

#endif // IR_SERVO_H