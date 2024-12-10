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

void loop(void)
{
	  if (data_received_flag == 1)
	  {
		  printf(" servo_1_angle = %d \r\n", servo_1_angle);

		  servo_set_angle_speed(&servo_1, servo_1_angle, 50);

		  data_received_flag = 0;

		  reset_rx_buffer();
	  }
}
