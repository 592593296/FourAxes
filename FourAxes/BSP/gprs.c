/*
 * gprs.c
 *
 *  Created on: 2017Äê12ÔÂ17ÈÕ
 *      Author: Administrator
 */

#include "gprs.h"
#include "stdio.h"
#include "string.h"
uint8_t atb[]="AT+IPR=115200;&W\r";
uint8_t at[]="AT+CGSN\r";
uint8_t rx[100];
uint8_t num;
extern UART_HandleTypeDef huart2;

void GPRS_Init()
{

}
void AT_Transmit(void)
{
//	if(HAL_OK == HAL_UART_Transmit(&huart2, at, sizeof(atb)/sizeof(uint8_t), 1000))
//	{
//		printf("at cheng gong\r\n");
//	}
	while(1)
	{

		if(HAL_OK == HAL_UART_Transmit(&huart2, atb, sizeof(at)/sizeof(uint8_t)-1, 0xffffff));
		{
			printf("rx cheng gong\r\n");

		}
//		huart2.Instance->DR = 0x00000000;
		HAL_UART_Receive_IT(&huart2,rx,1);
//		while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE));

//		osDelay(10);
		printf("IMEI=%s\r\n",rx);
//		printf("hello\r\n");
//		printf("rx1 is %s\r\n",rx);
		memset(rx,0,sizeof(rx)/sizeof(uint8_t));
				num = 0;

//		printf("rx2 is %s\r\n",rx);
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
