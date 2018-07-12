/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_GPIO.h
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				GPIO��ʼ���ļ�;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				GPIO��ʼ���ļ�;
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
#ifndef WP_GPIO_H
#define WP_GPIO_H


#include "stm32f10x.h"


/************************************************************************************************************
**                             �궨�����
*************************************************************************************************************/
// LED1Ϊ�ӿ�����û�ָʾ��
#define LED1_ON				GPIO_ResetBits(GPIOC, GPIO_Pin_11)  // ����LED1
#define LED1_OFF			GPIO_SetBits(GPIOC, GPIO_Pin_11)    // Ϩ��LED1
#define LED1_TOGGLE         GPIOC->ODR ^= GPIO_Pin_11           // LED1��˸

// LED2Ϊ�������ָʾ��
#define LED2_ON				GPIO_ResetBits(GPIOB, GPIO_Pin_12)  // ����LED2
#define LED2_OFF			GPIO_SetBits(GPIOB, GPIO_Pin_12)    // Ϩ��LED2
#define LED2_TOGGLE         GPIOC->ODR ^= GPIO_Pin_12           // LED2��˸

#define PWM_1_L			    GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define PWM_1_H			    GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define PWM_2_L			    GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define PWM_2_H			    GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define PWM_3_L			    GPIO_ResetBits(GPIOB, GPIO_Pin_8)
#define PWM_3_H			    GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define PWM_4_L			    GPIO_ResetBits(GPIOB, GPIO_Pin_9)
#define PWM_4_H			    GPIO_SetBits(GPIOB, GPIO_Pin_9)

#define OUTPUT_1_L			GPIO_ResetBits(GPIOE, GPIO_Pin_0)
#define OUTPUT_1_H			GPIO_SetBits(GPIOE, GPIO_Pin_0)
#define OUTPUT_2_L			GPIO_ResetBits(GPIOE, GPIO_Pin_1)
#define OUTPUT_2_H			GPIO_SetBits(GPIOE, GPIO_Pin_1)
#define OUTPUT_3_L			GPIO_ResetBits(GPIOE, GPIO_Pin_2)
#define OUTPUT_3_H			GPIO_SetBits(GPIOE, GPIO_Pin_2)
#define OUTPUT_4_L			GPIO_ResetBits(GPIOE, GPIO_Pin_3)
#define OUTPUT_4_H			GPIO_SetBits(GPIOE, GPIO_Pin_3)


/************************************************************************************************************
**                             �����ⲿ����
*************************************************************************************************************/
extern void Wp_FlowLights(u8 dismode);

extern u8 Wp_GetInputValue(void);
extern u8 Wp_GetPortInputValue(u8 port);

extern u8 Wp_GetOutputValue(void);
extern u8 Wp_GetPortOutputValue(u8 port);

extern void Wp_SetOutputValue(u8 value);
extern void Wp_SetPortOutputValue(u8 port, u8 value);

extern void Wp_GpioConfigure(void);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
