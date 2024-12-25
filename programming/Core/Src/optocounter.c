/*
 * optocounter.c
 *
 *  Created on: Dec 24, 2024
 *      Author: vahid
 */
#include "optocounter.h"

#define DEBOUNCE_OPTOCOUNTER	50

uint8	optocounter_number	= 0;
uint8	debounce_flag		= 0;
uint32	signal_counter		= 0;

extern	TIM_HandleTypeDef htim3;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_9)
    {
    	if (debounce_flag == 0)
    	{
    		debounce_flag = 1;
    		signal_counter = 0;
        	HAL_TIM_Base_Start_IT(&htim3);
    	}
    }
}

void	HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
    	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET)
    	{
    		signal_counter++;

    		if (signal_counter > DEBOUNCE_OPTOCOUNTER)
    		{
    			optocounter_number++;

    			if (optocounter_number > 6)
    			{
    				optocounter_number = 1;
    			}

    			debounce_flag = 0;

    			HAL_TIM_Base_Stop_IT(htim);
    		}
    	}
    }
}
uint8 OptocounterNumber(void)
{
	return optocounter_number;
}
