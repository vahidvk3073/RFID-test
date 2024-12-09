/*
 * servo_functions.c
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#include "main.h"
#include "servo_functions.h"

void servo_set_angle_speed(servo_motor *servo, uint8_t angle, uint8_t speed)
{
	uint16_t calibrated_angle = calibrate_angle(angle);

	//map angle to pulse PWM value
	uint32_t pulse = (calibrated_angle - MIN_ANGLE) * (servo->max_pulse - servo->min_pulse) /(MAX_ANGLE - MIN_ANGLE)
					 + servo->min_pulse;

	__HAL_TIM_SetCompare(servo->htim, servo->channel, pulse);
}

uint16_t calibrate_angle(uint8_t angle)
{
	uint16_t c_angle = angle * 10;

	if (c_angle > MAX_ANGLE)
	{
		return MAX_ANGLE;
	}
	else if (c_angle < MIN_ANGLE)
	{
		return MIN_ANGLE;
	}
	else
	{
		return c_angle;
	}
}
