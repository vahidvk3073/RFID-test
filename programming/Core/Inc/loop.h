/*
 * loop.h
 *
 *  Created on: Dec 10, 2024
 *      Author: vahid
 */

#ifndef INC_LOOP_H_
#define INC_LOOP_H_

#include "main.h"
#include "Types.h"
#include "servo_functions.h"
#include "serial.h"

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

void	Loop(void);
void	BufferProcess(uint8 *buffer);
uint8	ServoSetSpeed(ServoMotor *servo, ServoValues *servo_values);
void	CalibrateSpeed(ServoValues *servo_values);
void	ResetServoValues(ServoMotor *servo, ServoValues *servo_values);
void	Servo1Control(ServoMotor *servo, ServoValues *servo_values);
void	Servo2Control(ServoMotor *servo, ServoValues *servo_values);

void	TurnOnLED(void);
void	TurnOffLED(void);

#endif /* INC_LOOP_H_ */
