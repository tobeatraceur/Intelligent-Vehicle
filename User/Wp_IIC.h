/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_IIC.h
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				IIC��ʼ������;
**						ģ��IICͨѶ��ʽ����MPU6050;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				IIC��ʼ������;
**						ģ��IICͨѶ��ʽ����MPU6050;
**
**-----------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
**-----------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
*************************************************************************************************************/
#ifndef WP_IIC_H
#define WP_IIC_H


#include "stm32f10x.h"


/************************************************************************************************************
**                             �궨�����
*************************************************************************************************************/
#define CLI()                       __set_PRIMASK(1)  
#define SEI()                       __set_PRIMASK(0)

#define BYTE0(dwTemp)               (*(char *)(&dwTemp))
#define BYTE1(dwTemp)               (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)               (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)               (*((char *)(&dwTemp) + 3))

#define true                        1
#define false                       0
#define bool                        uint8_t

#define TRUE                        0
#define FALSE                       -1

/*
#define MPU6050_READRATE			1000	// 6050��ȡƵ��
#define MPU6050_READTIME			0.001	// 6050��ȡʱ����
#define EE_6050_ACC_X_OFFSET_ADDR	0
#define EE_6050_ACC_Y_OFFSET_ADDR	1
#define EE_6050_ACC_Z_OFFSET_ADDR	2
#define EE_6050_GYRO_X_OFFSET_ADDR	3
#define EE_6050_GYRO_Y_OFFSET_ADDR	4
#define EE_6050_GYRO_Z_OFFSET_ADDR	5
*/

#define	I2C_Direction_Transmitter   0       // 0��ʾд
#define	I2C_Direction_Receiver      1       // 1��ʾ��


#define SCL_H         GPIOC->BSRR = GPIO_Pin_9 			/* GPIO_SetBits(GPIOC, GPIO_Pin_9)   			*/
#define SCL_L         GPIOC->BRR = GPIO_Pin_9 			/* GPIO_ResetBits(GPIOC, GPIO_Pin_9) 			*/

#define SDA_H         GPIOC->BSRR = GPIO_Pin_8 			/* GPIO_SetBits(GPIOC, GPIO_Pin_8)  	 		*/
#define SDA_L         GPIOC->BRR = GPIO_Pin_8 			/* GPIO_ResetBits(GPIOC, GPIO_Pin_8) 			*/

#define SCL_read      GPIOC->IDR & GPIO_Pin_9	 		/* GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9) 	*/
#define SDA_read      GPIOC->IDR & GPIO_Pin_8 			/* GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) 	*/


/************************************************************************************************************
**                             �����ⲿ����
*************************************************************************************************************/
bool i2cWrite(uint8_t addr_, uint8_t reg, uint8_t data);
uint8_t i2cGetErrorCounter(void);

int8_t i2cwrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
int8_t i2cread(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);

void SimulateI2cInit(void);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
