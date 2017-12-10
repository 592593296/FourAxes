/*
 * IIC.c
 *
 *  Created on: 2017��12��10��
 *      Author: Administrator
 */


#include "iic.h"
#include "stdio.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)

#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48


#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08


#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		  0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)


//****************************

#define	GYRO_ADDRESS   0xD0	  //���ݵ�ַ
#define MAG_ADDRESS    0x18   //�ų���ַ
#define ACCEL_ADDRESS  0xD0

#define WRITE_DEVICEADD 11010000
#define READ_DEVICEADD 11010001
uint8_t ACCELBUFF[6];
uint8_t GYROBUFF[6];

extern I2C_HandleTypeDef hi2c1;

void MPU9255Init(void)
{
	HAL_I2C_Mem_Write(&hi2c1, WRITE_DEVICEADD, PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, (uint8_t *)0, 1, 100 );
	HAL_I2C_Mem_Write(&hi2c1, WRITE_DEVICEADD, SMPLRT_DIV, I2C_MEMADD_SIZE_8BIT, (uint8_t *)6, 1, 100 );
	HAL_I2C_Mem_Write(&hi2c1, WRITE_DEVICEADD, CONFIG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)7, 1, 100 );
	HAL_I2C_Mem_Write(&hi2c1, WRITE_DEVICEADD, GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)0x18, 1, 100 );
	HAL_I2C_Mem_Write(&hi2c1, WRITE_DEVICEADD, ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, (uint8_t *)1, 1, 100 );
//	HAL_I2C_Mem_Write(&hi2c1, WRITE_DEVICEADD, PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, 1, 100 );


}

void ReadAccelGyro(void)
{
	uint16_t value;
	while(1)
	{
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,ACCEL_XOUT_H,I2C_MEMADD_SIZE_8BIT,&ACCELBUFF[0],1,100);
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,ACCEL_XOUT_L,I2C_MEMADD_SIZE_8BIT,&ACCELBUFF[1],1,100);
		value= (ACCELBUFF[0]<<8) + ACCELBUFF[1];
		printf("ACCEL = %d\r\n",value);
	}

















}








