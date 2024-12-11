/*
 * loop.c
 *
 *  Created on: Dec 10, 2024
 *      Author: vahid
 */

#include "loop.h"

extern uint8		data_received_flag;
extern int			servo_1_angle;
extern servo_motor	servo_1;
extern uint8		rx_buffer[RX_BUFFER_SIZE];

uint8				motor_number;
uint8				angle;
uint8				speed;

void loop(void)
{
	  if (data_received_flag == 1)
	  {
		  buffer_process(rx_buffer);

		  servo_set_angle_speed(&servo_1, servo_1_angle, 50);

		  data_received_flag = 0;

		  reset_rx_buffer();
	  }
}

void	buffer_process(uint8 *buffer)
{
	motor_number = buffer[0];
	angle = buffer[1];
	speed = buffer[2];

	 printf(" servo number : %d, angle = %d, speed = %d \r\n", buffer[0], buffer[1], buffer[2]);
}
