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
	uint8	previous_angle;
	uint8	speed;
	uint32	previous_millis;
}ServoValues;

void	Loop(void);
void	BufferProcess(uint8 *buffer);
void	ServoSetSpeed(ServoMotor *servo, ServoValues *servo_values);
void	CalibrateSpeed(uint8 speed);

void	Calibrate(ServoValues *servo_values);
void	TurnOnLED(void);
void	TurnOffLED(void);

#endif /* INC_LOOP_H_ */
