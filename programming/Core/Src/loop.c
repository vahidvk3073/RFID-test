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
uint8				DS04_is_running				= 1;

float				ANGLE_STEP					= 1;



void Loop(void)
{
	  if (data_received_flag == 1)
	  {
		  BufferProcess(rx_buffer);

		  CalibrateSpeed(&servo_2_values);

		  run_motors_flag = 1;
		  DS04_is_running = 1;

		  data_received_flag = 0;
	  }

	  if (run_motors_flag == 1)
	  {
		  if (DS04_is_running == 1)
		  {
			  DS04_is_running = DS04HandleAngle(&servo_1, &servo_1_values);
		  }
		  else if (DS04_is_running == 0)
		  {
			  run_motors_flag = ServoControl(&servo_2, &servo_2_values);
		  }


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


uint8 ServoControl(ServoMotor *servo, ServoValues *servo_values)
{
	uint8 end_pivot;

	end_pivot = ServoSetSpeed(servo, servo_values);

	if (end_pivot == 0)
	{
		ResetServoValues(servo, servo_values);
//		ServoSetAngle(servo, servo_values->MIN_ANGLE);

		servo_values->previous_angle = servo_values->MIN_ANGLE;

		printf("end_pivot\r\n");



		return 0;
	}

	return 1;
}

uint8 ServoSetSpeed(ServoMotor *servo,ServoValues *servo_values)
{
	  if (HAL_GetTick() - servo_values->previous_millis > (servo_values->speed * 10))
	  {
		  if (servo_values->previous_angle < servo_values->angle)
		  {
			  ServoSetAngle(servo, servo_values->previous_angle);
			  servo_values->previous_angle = servo_values->previous_angle + ANGLE_STEP;
		  }
		  else // end of angle(360")
		  {
//			  servo_values->previous_angle = servo_values->angle;
			  return 0;
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



	//debug
	printf("===============\r\n motor_1_angle = %d, motor_1_speed = %d ***"
			 " motor_2_angle = %d, motor_2_speed = %d \r\n",buffer[0], buffer[1], buffer[2], buffer[3]);

	//send ACK data to PC
	HAL_UART_Transmit(&huart1, (uint8 *)"received\r\n", sizeof("received\r\n"), 0xFFFF);

	ResetRxBuffer();
}

void ResetServoValues(ServoMotor *servo, ServoValues *servo_values)
{
	for(int i = servo_values->angle; i > servo_values->MIN_ANGLE ; i--)
	{
		ServoSetAngle(servo, i);
		HAL_Delay(100);
	}

	servo_values->previous_angle = servo_values->MIN_ANGLE;
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
