/*
 * IIC.c
 *
 *  Created on: 2017年12月10日
 *      Author: Administrator
 */


#include "iic.h"
#include "stdio.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

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


#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		  0x75	//IIC地址寄存器(默认数值0x68，只读)


//****************************

#define	GYRO_ADDRESS   0xD0	  //陀螺地址
#define MAG_ADDRESS    0x18   //磁场地址
#define ACCEL_ADDRESS  0xD0

#define WRITE_DEVICEADD 11010000
#define READ_DEVICEADD 11010001
uint16_t ACCELBUFF[6];
uint16_t GYROBUFF[6];
uint16_t MAGBUFF[6];

uint8_t value = 0x02;
uint8_t cntl1 = 0x01;
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
	int16_t AccelX;
	int16_t AccelY;
	int16_t AccelZ;
	int16_t GyroX;
	int16_t GyroY;
	int16_t GyroZ;
	int16_t MAGX;
	int16_t MAGY;
	int16_t MAGZ;
	uint16_t id;

	while(1)
	{
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,ACCEL_XOUT_H,I2C_MEMADD_SIZE_8BIT,&ACCELBUFF[0],1,100);
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,ACCEL_XOUT_L,I2C_MEMADD_SIZE_8BIT,&ACCELBUFF[1],1,100);
		AccelX= (ACCELBUFF[0]<<8) + ACCELBUFF[1];
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,ACCEL_YOUT_H,I2C_MEMADD_SIZE_8BIT,&ACCELBUFF[2],1,100);
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,ACCEL_YOUT_L,I2C_MEMADD_SIZE_8BIT,&ACCELBUFF[3],1,100);
		AccelY= (ACCELBUFF[2]<<8) + ACCELBUFF[3];
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,ACCEL_ZOUT_H,I2C_MEMADD_SIZE_8BIT,&ACCELBUFF[4],1,100);
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,ACCEL_ZOUT_L,I2C_MEMADD_SIZE_8BIT,&ACCELBUFF[5],1,100);
		AccelZ= (ACCELBUFF[4]<<8) + ACCELBUFF[5];

		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,GYRO_XOUT_H,I2C_MEMADD_SIZE_8BIT,&GYROBUFF[0],1,100);
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,GYRO_XOUT_L,I2C_MEMADD_SIZE_8BIT,&GYROBUFF[1],1,100);
		GyroX= (GYROBUFF[0]<<8) + GYROBUFF[1];
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,GYRO_YOUT_H,I2C_MEMADD_SIZE_8BIT,&GYROBUFF[2],1,100);
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,GYRO_YOUT_L,I2C_MEMADD_SIZE_8BIT,&GYROBUFF[3],1,100);
		GyroY= (GYROBUFF[2]<<8) + GYROBUFF[3];
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,GYRO_ZOUT_H,I2C_MEMADD_SIZE_8BIT,&GYROBUFF[4],1,100);
		HAL_I2C_Mem_Read(&hi2c1,READ_DEVICEADD,GYRO_ZOUT_L,I2C_MEMADD_SIZE_8BIT,&GYROBUFF[5],1,100);
		GyroZ= (GYROBUFF[4]<<8) + GYROBUFF[5];

		HAL_I2C_Mem_Write(&hi2c1, WRITE_DEVICEADD, 0x37, I2C_MEMADD_SIZE_8BIT, &value, 1, 100 );
		HAL_I2C_Mem_Write(&hi2c1, 0x18, 0x0a, I2C_MEMADD_SIZE_8BIT, &cntl1, 1, 100 );
//		osDelay(10);
//		value = 0x11;

		osDelay(10);
		HAL_I2C_Mem_Read(&hi2c1,0x19,MAG_XOUT_L,I2C_MEMADD_SIZE_8BIT,&MAGBUFF[0],1,100);
		HAL_I2C_Mem_Read(&hi2c1,0x19,MAG_XOUT_H,I2C_MEMADD_SIZE_8BIT,&MAGBUFF[1],1,100);
		MAGX = (MAGBUFF[1]<<8) + MAGBUFF[0];
		HAL_I2C_Mem_Read(&hi2c1,0x19,MAG_YOUT_L,I2C_MEMADD_SIZE_8BIT,&MAGBUFF[2],1,100);
		HAL_I2C_Mem_Read(&hi2c1,0x19,MAG_YOUT_H,I2C_MEMADD_SIZE_8BIT,&MAGBUFF[3],1,100);
		MAGY = (MAGBUFF[3]<<8) + MAGBUFF[2];
		HAL_I2C_Mem_Read(&hi2c1,0x19,MAG_ZOUT_L,I2C_MEMADD_SIZE_8BIT,&MAGBUFF[4],1,100);
		HAL_I2C_Mem_Read(&hi2c1,0x19,MAG_ZOUT_H,I2C_MEMADD_SIZE_8BIT,&MAGBUFF[5],1,100);
		MAGZ = (MAGBUFF[5]<<8) + MAGBUFF[4];

		HAL_I2C_Mem_Read(&hi2c1,0x19,0,I2C_MEMADD_SIZE_8BIT,&id,1,100);

		printf("ACCEL x,y,z\t%d\t%d\t%d\t\r\n",AccelX,AccelY,AccelZ);
		printf("GYRO x,y,z\t%d\t%d\t%d\t\r\n",GyroX,GyroY,GyroZ);
		printf("MAG x,y,z\t%d\t%d\t%d\t\r\n",MAGX,MAGY,MAGZ);
		printf("id=%d\r\n",id);

		osDelay(1000);

	}

















}








