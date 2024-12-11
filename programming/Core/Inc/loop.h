/*
 * loop.h
 *
 *  Created on: Dec 10, 2024
 *      Author: vahid
 */

#ifndef INC_LOOP_H_
#define INC_LOOP_H_

#include "stm32f1xx_hal.h"
#include "Types.h"
#include "servo_functions.h"
#include "serial.h"



void	loop(void);
void	buffer_process(uint8 *buffer);

#endif /* INC_LOOP_H_ */
