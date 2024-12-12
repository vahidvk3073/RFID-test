/*
 * loop.c
 *
 *  Created on: Dec 10, 2024
 *      Author: vahid
 */

#include "loop.h"

#define	ANGLE_STEP	1

extern uint8		data_received_flag;
extern ServoMotor	servo_1,
					servo_2;
extern uint8		rx_buffer[RX_BUFFER_SIZE];

ServoValues			servo_1_values;
ServoValues			servo_2_values;

//servo_1_values->previous_angle = 0;
uint8				motor_number;


void Loop(void)
{
	  if (data_received_flag == 1)
	  {
		  BufferProcess(rx_buffer);

		  Calibrate(&servo_1_values);
		  Calibrate(&servo_2_values);

		  data_received_flag = 0;
	  }

	  if (motor_number == 2)
	  {

		  ServoSetSpeed(&servo_1, &servo_1_values);
		  ServoSetSpeed(&servo_2, &servo_2_values);
	  }

}


void ServoSetSpeed(ServoMotor *servo,ServoValues *servo_values)
{
	  if (HAL_GetTick() - servo_values->previous_millis > (servo_values->speed * 30))
	  {
		  if (servo_values->previous_angle < servo_values->angle)
		  {
//			  printf("motor_number %d :: angle = %d, previous_angle = %d \r\n",
//					  servo_values->motor_number,servo_values->angle, servo_values->previous_angle);

			  ServoSetAngle(servo, servo_values->previous_angle);
			  servo_values->previous_angle = servo_values->previous_angle + ANGLE_STEP;
		  }
		  else
		  {
//			  printf("else--------motor_number %d :: angle = %d, previous_angle = %d \r\n",
//					  servo_values->motor_number, servo_values->angle, servo_values->previous_angle);

			  servo_values->previous_angle = servo_values->angle;
		  }

		  servo_values->previous_millis = HAL_GetTick();
	  }
}


void BufferProcess(uint8 *buffer)
{
	motor_number = buffer[0];

	switch (motor_number)
	{
	case 1:
		servo_1_values.motor_number = buffer[0];
		servo_1_values.angle = buffer[1];
		servo_1_values.speed = buffer[2];
		servo_1_values.previous_millis = HAL_GetTick();
		break;

	case 2:
		servo_2_values.motor_number = buffer[0];
		servo_2_values.angle = buffer[1];
		servo_2_values.speed = buffer[2];
		servo_2_values.previous_millis = HAL_GetTick();
		break;
	}

//	 printf("data received succussfully, motor_number : %d, angle = %d, speed = %d \r\n",
//			 buffer[0], buffer[1], buffer[2]);

	 ResetRxBuffer();
}

void Calibrate(ServoValues *servo_values)
{
	CalibrateSpeed(servo_values->speed);
}

void CalibrateSpeed(uint8 speed)
{
	if (speed < MIN_SPEED)
	{
		speed = MIN_SPEED;
	}

	if (speed > MAX_SPEED)
	{
		speed = MAX_SPEED;
	}
}





void TurnOnLED(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}
void TurnOffLED(void)
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}
