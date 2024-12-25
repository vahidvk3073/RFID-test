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
#include "optocounter.h"



void	Loop(void);
void	BufferProcess(uint8 *buffer);
uint8	ServoSetSpeed(ServoMotor *servo, ServoValues *servo_values);
void	CalibrateSpeed(ServoValues *servo_values);
void	ResetServoValues(ServoMotor *servo, ServoValues *servo_values);
void	ServoControl(ServoMotor *servo, ServoValues *servo_values);
uint8	DS04HandleAngle(ServoMotor *servo, ServoValues *servo_values);
void	TurnOnLED(void);
void	TurnOffLED(void);

#endif /* INC_LOOP_H_ */
