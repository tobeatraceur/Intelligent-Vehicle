/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_Key.h
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				������������;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				������������;
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
#ifndef WP_KEY_H
#define WP_KEY_H


#include "stm32f10x.h"
#include "Wp_GPIO.h"


/************************************************************************************************************
**                            	�궨�����
*************************************************************************************************************/
// ����
/*
#define CHECKKEYUP          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)           // ��������ֵ
#define CHECKKEYDOWN        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)           // ��������ֵ
#define CHECKKEYBACK        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)           // ��������ֵ
#define CHECKKEYOK          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)           // ��������ֵ

#define key_up()            (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15))
#define key_down()          (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14))
#define key_back()          (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13))
#define key_ok()            (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12))
*/

// �ڶ��棬�������пƴ�İ汾
#define CHECKKEYUP          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12)           // ��������ֵ
#define CHECKKEYDOWN        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)           // ��������ֵ
#define CHECKKEYBACK        GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)           // ��������ֵ
#define CHECKKEYOK          GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)           // ��������ֵ

#define key_up()            (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12))
#define key_down()          (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13))
#define key_back()          (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14))
#define key_ok()            (!GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15))


#define USER_DATA_EN		(0)             // ʹ���û����ݣ�ÿһ��������һ���������û�ʹ��
#define KEY_USE_SEM			(0)	            // 1��ʹ�ð��������ź�����0����ʹ�ð��������ź���
#define KEY_WOBBLE_TIME		(5)             // ��������ʱ�䣬Ҳ��������ʱ�䣬��λms
//#define KEY_FIXED_PERIOD	(10)            // �̶�Ƶ�ʵ��ð���״̬���º�����������Ϊ�������ڣ����ڵ�λΪms
#define KEY_TIMES_MAX       (0xFF)          // �������������ֵ


typedef enum                                // ���ö��������ʹ�û����ź���ʱ���԰���״̬���ʵ�ѡ��
{
	KEY_ACCESS_READ 	= 0x08,
	KEY_ACCESS_WRITE	= 0x80,
	KEY_ACCESS_CLEAR	= 0x40,
	KEY_ACCESS_DECREASE = 0x20,
	KEY_ACCESS_INCREASE = 0x10,
    KEY_ACCESS_REFRESH  = 0xc0              // ������ˢ���а������±�־��KEY_ACCESS_REFRESH = (KEY_ACCESS_WRITE | KEY_ACCESS_CLEAR)
}access_type;


typedef enum                                // ����״̬��
{
	KEY_DOWN 		    = 1,                // ����
	KEY_UP	 		    = 2,                // ̧��
	KEY_UP_WOBBLE 	    = 3,                // ȷ�ϵ�������״̬
	KEY_DOWN_WOBBLE     = 4                 // ȷ�ϰ�������״̬
}key_state_type;


typedef enum                                // ������¼�ź���״̬
{
	KEY_SEM_USING       = 0,
	KEY_SEM_FREE        = 1
}key_sem_type;


typedef struct
{
	u8 (*get_state)(void);	                // ���ڻ�ȡ����״̬�ĺ���
    
	#if (KEY_USE_SEM == 1)
        key_sem_type sem;				    // ���������ź���
	#endif
    
	#ifdef  KEY_FIXED_PERIOD
        uint8_t time_ms;			        // ���ڹ̶����ڵ��ð���״̬���º����ļ�ʱ
	#endif
    
	key_state_type state;                   // ����״̬��
	uint8_t times;				            // ���������´��������²��������1��ʹ�ú���Ӧ�ó����1
    
	#if (USER_DATA_EN == 1)
        uint8_t value;				        // �û������������û�����ʹ��
	#endif
}key_inf_type;


/************************************************************************************************************
**                            	�����ⲿ����
*************************************************************************************************************/
void Wp_KeyObjectInit(key_inf_type* key_this, u8(*getState)(void));
void Wp_KeyRefreshState(key_inf_type* theKey);
u8 Wp_KeyAccessTimes(key_inf_type* theKey, access_type option);
void Wp_KeyInit(void);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
