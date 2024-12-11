/*
 * serial.c
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#include "serial.h"

#define START_BYTE	0xFF
#define STOP_BYTE	0x0A

uint8			receiving					= 0;
uint8			buffer_index				= 0;
int				servo_1_angle;
uint8			data_received_flag;

uint8			rx_buffer[RX_BUFFER_SIZE];

extern uint8	rx_temp;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		if (rx_temp == START_BYTE && receiving == 0)//check START BYTE,if valid start receiving
		{
			receiving = 1;
			buffer_index = 0;
		}
		else if (receiving == 1) //start receiving
		{
			if (rx_temp == STOP_BYTE)
			{
				data_received_flag = 1;
				receiving = 0;
			}

			if (buffer_index < RX_BUFFER_SIZE)
			{
				rx_buffer[buffer_index] = rx_temp;
				buffer_index++;
			}

		}
	}
}

void reset_rx_buffer(void)
{
	memset(rx_buffer , 0 ,RX_BUFFER_SIZE);
	buffer_index = 0;
}


/*function for define printf*/
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1, (uint8 *)&ch, 1, 0xFFFF);

  return ch;
}

