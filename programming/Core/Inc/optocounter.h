/*
 * optocounter.h
 *
 *  Created on: Dec 24, 2024
 *      Author: vahid
 */

#ifndef INC_OPTOCOUNTER_H_
#define INC_OPTOCOUNTER_H_

#include "stm32f1xx_hal.h"
#include "Types.h"
#include "serial.h"

void	HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void	HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
uint8	OptocounterNumber(void);

#endif /* INC_OPTOCOUNTER_H_ */
