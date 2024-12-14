/*
 * loop.c
 *
 *  Created on: Dec 10, 2024
 *      Author: vahid
 */

#include "loop.h"

//#define	ANGLE_STEP	1

extern uint8		data_received_flag;

extern ServoMotor	servo_1,
					servo_2;

extern uint8		rx_buffer[RX_BUFFER_SIZE];

uint8				motor_number;

ServoValues			servo_1_values 				= {0,0,0,0, SERVO_1_MIN_ANGLE, SERVO_1_MAX_ANGLE,0};
ServoValues			servo_2_values 				= {0,0,0,0, SERVO_2_MIN_ANGLE, SERVO_2_MAX_ANGLE,0};

uint8				set_motors_flag 			= 0;

float				ANGLE_STEP					= 0.25;



void Loop(void)
{
	  if (data_received_flag == 1)
	  {
		  BufferProcess(rx_buffer);

		  CalibrateSpeed(&servo_1_values);
		  CalibrateSpeed(&servo_2_values);

		  if (motor_number == MOTOR_NUMBER)
		  {
			  set_motors_flag = 1;
		  }

		  data_received_flag = 0;
	  }

	  if (set_motors_flag == 1)
	  {
		  Servo1Control(&servo_1, &servo_1_values);
		  Servo2Control(&servo_2, &servo_2_values);
	  }

}


uint8 ServoSetSpeed(ServoMotor *servo,ServoValues *servo_values)
{
	  if (HAL_GetTick() - servo_values->previous_millis > (servo_values->speed * 10))
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
//			  printf("End Angle-------->motor_number %d :: angle = %d, previous_angle = %d \r\n",
//					  servo_values->motor_number, servo_values->angle, servo_values->previous_angle);

			  if (servo_values->angle == (servo_values->MAX_ANGLE)/10) // end of angle(360")
			  {
				  return 0;
			  }
			  else
			  {
				  servo_values->previous_angle = servo_values->angle;
			  }
		  }

		  servo_values->previous_millis = HAL_GetTick();
	  }

	  return 1;
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

void Servo1Control(ServoMotor *servo, ServoValues *servo_values)
{
	uint8 end_pivot;

	end_pivot = ServoSetSpeed(servo, servo_values);

	if (end_pivot == 0)
	{
		  servo_values->previous_angle = servo_values->MIN_ANGLE;
		  ServoSetAngle(servo, servo_values->previous_angle);
		  set_motors_flag = 0;
	}
}

void Servo2Control(ServoMotor *servo, ServoValues *servo_values)
{
	uint8 end_pivot;

	end_pivot = ServoSetSpeed(servo, servo_values);

	if (end_pivot == 0)
	{
		  servo_values->previous_angle = servo_values->MIN_ANGLE;
		  ServoSetAngle(servo, servo_values->previous_angle);
		  set_motors_flag = 0;
	}
}

void ResetServoValues(ServoMotor *servo, ServoValues *servo_values)
{
	for(int i = servo_values->MAX_ANGLE; i > servo_values->MIN_ANGLE ; i--)
	{
		ServoSetAngle(servo, i);
		HAL_Delay(100);
	}

	servo_values->previous_angle = servo_values->MIN_ANGLE;
	set_motors_flag = 0;
}

void CalibrateSpeed(ServoValues *servo_values)
{
	if (servo_values->speed < MIN_SPEED)
	{
		servo_values->speed = MIN_SPEED;
	}

	if (servo_values->speed > MAX_SPEED)
	{
		servo_values->speed = MAX_SPEED;
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
