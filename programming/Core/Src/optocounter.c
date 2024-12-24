/*
 * optocounter.c
 *
 *  Created on: Dec 24, 2024
 *      Author: vahid
 */
#include "optocounter.h"

uint8	optocounter_number	= 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_9)
    {
    	optocounter_number++;

    	if (optocounter_number > 6)
    	{
    		optocounter_number = 1;
    	}
    }
}

uint8 OptocounterNumber(void)
{
	return optocounter_number;
}
