/*
 * loop.c
 *
 *  Created on: Dec 10, 2024
 *      Author: vahid
 */

#include "loop.h"


extern uint8		data_received_flag;

extern uint8		rx_buffer[RX_BUFFER_SIZE];

ServoMotor			servo_1						= {&TIM2->CCR1, SERVO_1_MIN_PULSE, SERVO_1_MAX_PULSE};
ServoMotor			servo_2						= {&TIM2->CCR2, SERVO_2_MIN_PULSE, SERVO_2_MAX_PULSE};

uint8				motor_number;

ServoValues			servo_1_values 				= {0,0,0,0, SERVO_1_MIN_ANGLE, SERVO_1_MAX_ANGLE,0};
ServoValues			servo_2_values 				= {0,0,0,0, SERVO_2_MIN_ANGLE, SERVO_2_MAX_ANGLE,0};

uint8				run_motors_flag 			= 0;

float				ANGLE_STEP					= 1;



void Loop(void)
{
	  if (data_received_flag == 1)
	  {
		  BufferProcess(rx_buffer);

		  run_motors_flag = 1;

		  data_received_flag = 0;
	  }

	  if (run_motors_flag == 1)
	  {
		  run_motors_flag = DS04HandleAngle(&servo_1, &servo_1_values);
	  }
}

uint8 DS04HandleAngle(ServoMotor *servo, ServoValues *servo_values)
{
	uint8 return_value;

	uint8 angle;
	angle = servo_values->angle;

	switch(angle)
	{
	case ANGLE_0:
		return_value = DS04CheckState(servo, servo_values, COUNTER_NUMBER_0);
		break;

	case ANGLE_60:
		return_value = DS04CheckState(servo, servo_values, COUNTER_NUMBER_60);
		break;

	case ANGLE_120:
		return_value = DS04CheckState(servo, servo_values, COUNTER_NUMBER_120);
		break;

	case ANGLE_180:
		return_value = DS04CheckState(servo, servo_values, COUNTER_NUMBER_180);
		break;

	case ANGLE_240:
		return_value = DS04CheckState(servo, servo_values, COUNTER_NUMBER_240);
		break;

	case ANGLE_300:
		return_value = DS04CheckState(servo, servo_values, COUNTER_NUMBER_300);
		break;
	}

	return return_value;
}


void ServoControl(ServoMotor *servo, ServoValues *servo_values)
{
	uint8 end_pivot;

	end_pivot = ServoSetSpeed(servo, servo_values);

	if (end_pivot == 0)
	{
		  servo_values->previous_angle = servo_values->MIN_ANGLE;
		  ServoSetAngle(servo, servo_values->previous_angle);
		  run_motors_flag = 0;
	}
}

uint8 ServoSetSpeed(ServoMotor *servo,ServoValues *servo_values)
{
	  if (HAL_GetTick() - servo_values->previous_millis > (servo_values->speed * 10))
	  {
		  if (servo_values->previous_angle < servo_values->angle)
		  {
//			  printf("motor_number %d :: angle = %d, previous_angle = %0.2f \r\n",
//					  servo_values->motor_number,servo_values->angle, servo_values->previous_angle);

			  ServoSetAngle(servo, servo_values->previous_angle);
			  servo_values->previous_angle = servo_values->previous_angle + ANGLE_STEP;
		  }
		  else
		  {
//			  printf("End Angle-------->motor_number %d :: angle = %d, previous_angle = %0.2f \r\n",
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
	servo_1_values.motor_number = 1;
	servo_1_values.angle = buffer[0];
	servo_1_values.speed = buffer[1];
	servo_1_values.previous_millis = HAL_GetTick();

	servo_2_values.motor_number = 2;
	servo_2_values.angle = buffer[2];
	servo_2_values.speed = buffer[3];
	servo_2_values.previous_millis = HAL_GetTick();


	 printf("data received succussfully motor_1_angle = %d, motor_1_speed = %d,"
			 " motor_2_angle = %d, motor_2_speed = %d \r\n",buffer[0], buffer[1], buffer[2], buffer[3]);

	ResetRxBuffer();
}

void ResetServoValues(ServoMotor *servo, ServoValues *servo_values)
{
	for(int i = servo_values->MAX_ANGLE; i > servo_values->MIN_ANGLE ; i--)
	{
		ServoSetAngle(servo, i);
		HAL_Delay(100);
	}

	servo_values->previous_angle = servo_values->MIN_ANGLE;
	run_motors_flag = 0;
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
