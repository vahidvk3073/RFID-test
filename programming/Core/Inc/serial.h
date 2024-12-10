/*
 * serial.h
 *
 *  Created on: Dec 9, 2024
 *      Author: vahid
 */

#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

#include "stm32f1xx_hal.h"
#include "Types.h"
#include "stdio.h"

#define		RX_BUFFER_SIZE		4

extern UART_HandleTypeDef huart1;

/*macro define for printf*/
#ifdef __GNUC__
	/* With GCC, small printf (option LD Linker->Libraries->Small printf
		 set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
	#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */


/*define function prototype*/
void			HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void			HAL_DMA_RX_CpltCallback(DMA_HandleTypeDef *hdma);
void			reset_rx_buffer(void);


#endif /* INC_SERIAL_H_ */
