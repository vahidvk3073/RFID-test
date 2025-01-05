/*
 * servo_functions.c
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */


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

void DS04ServoSetPulse(ServoMotor *servo, uint32 pulse)
{
	*(servo->channel) = pulse;
}

uint8 DS04CheckState(ServoMotor *servo, ServoValues *servo_values, uint8 optocounter_number)
{
	const int COUNTER_MAX = 100;

	uint32 counter,
		   wait;
	uint8 pin_status;

	DS04ServoSetPulse(servo, DS04_SPEED_SLOW);

	counter = 0;
	wait = 0;

	while (counter < COUNTER_MAX)
	{
		pin_status = HAL_GPIO_ReadPin(OptoSensor_GPIO_Port, OptoSensor_Pin);

		switch(pin_status)
		{
			case 0:
				counter = 0;
				break;

			case 1:
				counter++;
				break;
		}

		if (wait++ > 2000)
		{
			printf(" << ERROR >>\r\n");
		}

		HAL_Delay(0);
	}

	DS04ServoSetPulse(servo, DS04_STOP);
	return 0;
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
