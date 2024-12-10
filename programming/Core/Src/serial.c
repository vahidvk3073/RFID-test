/*
 * serial.c
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#include "serial.h"



uint8				data_received_flag				= 0;
uint8				rx_index						= 0;
int 				servo_1_angle;

uint8				rx_buffer[RX_BUFFER_SIZE];

extern uint8 		rx_temp;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		if(rx_temp == '\n') //  '\n' character means end of received data
		{
			rx_buffer[rx_index] = '\0';

			servo_1_angle = atoi((char *)rx_buffer);

			data_received_flag = 1;
		}
		else
		{
			rx_buffer[rx_index] = rx_temp;
			rx_index++;

			if (rx_index > RX_BUFFER_SIZE)
			{
				rx_index = 0;
			}
		}
	}
}

void reset_rx_buffer(void)
{
	memset(rx_buffer , 0 ,RX_BUFFER_SIZE);
	rx_index = 0;
}


/*function for define printf*/
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1, (uint8 *)&ch, 1, 0xFFFF);

  return ch;
}

