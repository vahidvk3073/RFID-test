/*
 * servo_functions.c
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#include "main.h"
#include "servo_functions.h"

void ServoSetAngle(ServoMotor *servo, float angle)//add SERVO_1_MIN_ANGLE and 2 and.. with ServoValues pointer
{
	uint16 calibrated_angle;
	calibrated_angle = CalibrateAngle(angle);

	//map angle to pulse PWM value
	uint32 pulse;
	pulse = (calibrated_angle - SERVO_1_MIN_ANGLE) * (servo->max_pulse - servo->min_pulse) /(SERVO_1_MAX_ANGLE - SERVO_1_MIN_ANGLE)
			+ servo->min_pulse;

	*(servo->channel) = pulse;
}

uint16 CalibrateAngle(float angle)
{
	uint16 c_angle;
	c_angle = angle * 10;

	if (c_angle < SERVO_1_MIN_ANGLE)
	{
		return SERVO_1_MIN_ANGLE;
	}

	if (c_angle > SERVO_1_MAX_ANGLE)
	{
		return SERVO_1_MAX_ANGLE;
	}

	return c_angle;
}
