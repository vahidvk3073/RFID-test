/*
 * servo_functions.h
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#ifndef INC_SERVO_FUNCTIONS_H_
#define INC_SERVO_FUNCTIONS_H_

#include "Types.h"

#define MIN_ANGLE			0
#define MAX_ANGLE			360

#define SERVO_1_MIN_PULSE	17500
#define SERVO_1_MAX_PULSE	19500

#define SERVO_2_MIN_PULSE	17500
#define SERVO_2_MAX_PULSE	19500

typedef struct
{
    uint32	*channel;
    uint32	min_pulse;
    uint32	max_pulse;
} servo_motor;



void	servo_set_angle_speed(servo_motor *servo, uint8 angle, uint8 speed);
uint16	calibrate_angle(uint8 angle);

#endif /* INC_SERVO_FUNCTIONS_H_ */
