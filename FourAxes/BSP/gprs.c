/*
 * gprs.c
 *
 *  Created on: 2017Äê12ÔÂ17ÈÕ
 *      Author: Administrator
 */

#include "gprs.h"
#include "stdio.h"
uint8_t at[]="AT+CGSN\r";
uint8_t rx[100];
uint8_t num;
extern UART_HandleTypeDef huart2;

void GPRS_Init()
{

}
void AT_Transmit(void)
{
	while(1)
	{
//		osDelay(10000);
		HAL_UART_Transmit(&huart2, at, sizeof(at), 1000);
//		printf("tx AT+CGSN");
		HAL_UART_Receive_IT(&huart2,rx,100);


		osDelay(10);
//		printf("IMEI=%s\r\n",rx);
		printf("hello\r\n");
		memset(rx,0,100*sizeof(uint8_t));
		num = 0;
//		HAL_UART_Receive_IT(&huart2,rx,100);


//		printf("%s\r\n",rx);
		osDelay(1000);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart == &huart2)
	{
		HAL_UART_Receive_IT(&huart2,&rx[num],1);
		num++;
	}


}
