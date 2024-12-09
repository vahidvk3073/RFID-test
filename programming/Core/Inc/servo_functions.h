/*
 * servo_functions.h
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#ifndef INC_SERVO_FUNCTIONS_H_
#define INC_SERVO_FUNCTIONS_H_

#define MIN_ANGLE 0
#define MAX_ANGLE 360

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
    uint32_t min_pulse;
    uint32_t max_pulse;
} servo_motor;



void servo_set_angle_speed(servo_motor *servo, uint8_t angle, uint8_t speed);
uint16_t calibrate_angle(uint8_t angle);

#endif /* INC_SERVO_FUNCTIONS_H_ */
