/*
 * servo_functions.h
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#ifndef INC_SERVO_FUNCTIONS_H_
#define INC_SERVO_FUNCTIONS_H_

#include "Types.h"
#include "main.h"
#include "optocounter.h"

#define SERVO_1_MIN_ANGLE	0
#define SERVO_1_MAX_ANGLE	360

#define SERVO_2_MIN_ANGLE	0
#define SERVO_2_MAX_ANGLE	360

#define MIN_SPEED			0
#define MAX_SPEED			100

#define SERVO_1_MIN_PULSE	17500
#define SERVO_1_MAX_PULSE	19500

#define SERVO_2_MIN_PULSE	17500
#define SERVO_2_MAX_PULSE	19500

#define DS04_STOP			18500
#define DS04_SPEED_SLOW		18455

#define MOTOR_NUMBER		2

#define	ANGLE_0				0
#define	ANGLE_60			6
#define	ANGLE_120			12
#define	ANGLE_180			18
#define	ANGLE_240			24
#define	ANGLE_300			30

#define	COUNTER_NUMBER_0	1
#define	COUNTER_NUMBER_60	2
#define	COUNTER_NUMBER_120	3
#define	COUNTER_NUMBER_180	4
#define	COUNTER_NUMBER_240	5
#define	COUNTER_NUMBER_300	6

typedef struct
{
    uint32	*channel;
    uint32	min_pulse;
    uint32	max_pulse;
} ServoMotor;

typedef struct
{
	uint8	motor_number;
	uint8	angle;
	float	previous_angle;
	uint8	speed;
	uint8	MIN_ANGLE;
	uint16	MAX_ANGLE;
	uint32	previous_millis;
}ServoValues;

void	ServoSetAngle(ServoMotor *servo, float angle);
void	DS04ServoSetPulse(ServoMotor *servo, uint32 pulse);
uint8	DS04CheckState(ServoMotor *servo, ServoValues *servo_values, uint8 optocounter_number);
uint16	CalibrateAngle(float angle);

#endif /* INC_SERVO_FUNCTIONS_H_ */
