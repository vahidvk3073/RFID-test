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

ServoValues			servo_1_values 				= {0,0,0,0, SERVO_1_MIN_ANGLE, SERVO_1_MAX_ANGLE};
ServoValues			servo_2_values 				= {0,0,0,0, SERVO_2_MIN_ANGLE, SERVO_2_MAX_ANGLE};

uint8				run_motors_flag 			= 0;
//uint8				DS04_is_running				= 1;

float				ANGLE_STEP					= 1;



void Loop(void)
{
	  if (data_received_flag == 1)
	  {
		  BufferProcess(rx_buffer);

		  ValidateSpeed(&servo_1_values);
		  ValidateSpeed(&servo_2_values);

		  run_motors_flag = 1;

		  data_received_flag = 0;
	  }

	  if (run_motors_flag == 1)
	  {
		  switch(motor_number)
		  {
		  	  case 1:
		  		DS04HandleAngle(&servo_1, &servo_1_values);
		  		run_motors_flag = 0;
		  		break;

		  	  case 2:
		  		ServoControl(&servo_2, &servo_2_values);
		  		run_motors_flag = 0;
		  		break;
		  }
	  }
}

void DS04HandleAngle(ServoMotor *servo, ServoValues *servo_values)
{
	uint8 return_value;

	return_value = DS04CheckState(servo, servo_values);

	if(return_value == 1)
	{
		HAL_UART_Transmit(&huart1, (uint8 *)"OK1\r\n", sizeof("OK1\r\n"), 0xFFFF);
	}
	else
	{
		HAL_UART_Transmit(&huart1, (uint8 *)"ERROR1\r\n", sizeof("ERROR1\r\n"), 0xFFFF);
	}
}


void ServoControl(ServoMotor *servo, ServoValues *servo_values)
{
	uint8 end_pivot;

	end_pivot = ServoSetSpeed(servo, servo_values);

	if (end_pivot == 1)
	{
		ResetServoValues(servo, servo_values);

		servo_values->previous_angle = servo_values->MIN_ANGLE;

		printf("end_pivot\r\n");
	}
}

uint8 ServoSetSpeed(ServoMotor *servo,ServoValues *servo_values)
{
	for(uint32 i = servo_values->MIN_ANGLE ; i < servo_values->angle ; i = i + ANGLE_STEP)
	{
		ServoSetAngle(servo, i);
		HAL_Delay(servo_values->speed);
	}

	return 1;
}

void BufferProcess(uint8 *buffer)
{
	motor_number = buffer[0];

	switch(motor_number)
	{
		case 1:
			servo_1_values.motor_number = buffer[0];
			servo_1_values.angle = buffer[1];
			servo_1_values.speed = buffer[2];

			//debug
			printf("===============\r\n motor_number = %d :: motor_angle = %d, motor_speed = %d \r\n",
					servo_1_values.motor_number, servo_1_values.angle, servo_1_values.speed);
			break;

		case 2:
			servo_2_values.motor_number = buffer[0];
			servo_2_values.angle = buffer[1];
			servo_2_values.speed = buffer[2];

			//send ACK data to PC
			HAL_UART_Transmit(&huart1, (uint8 *)"OK2\r\n", sizeof("OK2\r\n"), 0xFFFF);

			//debug
			printf("===============\r\n motor_number = %d :: motor_angle = %d, motor_speed = %d \r\n",
					servo_2_values.motor_number, servo_2_values.angle, servo_2_values.speed);
			break;
	}

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

void ValidateSpeed(ServoValues *servo_values)
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
