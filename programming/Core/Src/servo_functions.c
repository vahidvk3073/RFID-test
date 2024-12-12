/*
 * servo_functions.c
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#include "main.h"
#include "servo_functions.h"

void ServoSetAngle(ServoMotor *servo, uint8 angle)
{
	uint16 calibrated_angle;
	calibrated_angle = CalibrateAngle(angle);
	//map angle to pulse PWM value
	uint32 pulse;
	pulse = (angle - MIN_ANGLE) * (servo->max_pulse - servo->min_pulse) /(MAX_ANGLE - MIN_ANGLE)
			+ servo->min_pulse;

	*(servo->channel) = pulse;
}

uint16 CalibrateAngle(uint8 angle)
{
	uint16 c_angle;
	c_angle = angle * 10;

	if (c_angle < MIN_ANGLE)
	{
		return MIN_ANGLE;
	}

	if (c_angle > MAX_ANGLE)
	{
		return MAX_ANGLE;
	}

	return c_angle;
}
