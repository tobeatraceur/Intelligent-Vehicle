/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_Globle.h
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				ϵͳȫ�ֱ����ͺ���;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				ϵͳȫ�ֱ����ͺ���;
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
#ifndef WP_GLOBLE_H
#define WP_GLOBLE_H


#include "stm32f10x.h"
#include "Wp_Key.h"


/************************************************************************************************************
**                            	�ⲿ��������
*************************************************************************************************************/
extern volatile u32 g_SysTickTimer;			// 1ms��ȷϵͳʱ�Ӽ�ʱ�����������û������޸ģ�

extern u32 g_UP_Uart1ITAddress;				// Uart1�ж���ں���
extern u32 g_UP_Uart2ITAddress;				// Uart2�ж���ں���
extern u32 g_UP_Uart3ITAddress;				// Uart3�ж���ں���

extern u32 g_UP_ExtiFlag;					// �ⲿ�ж�ʹ�ܵ�ͨ��
extern u32 g_UP_ExtiITAddress;				// �ⲿ�ж���ں���

extern bool g_UP_bTimerIT[4];				// �Ƿ����ô������ݽ����ж�
extern u32 g_UP_iTimerTime[4];				// ��ʱ����
extern u32 g_UP_TimerITAddress;				// ��ʱ���ж���ں���

extern u16 g_ADValue[16]; 					// ��ǰADCֵ�Ĵ���
extern float analogvalue[15];               // ����ͨ����ѹֵ

extern u16 powertemp[32];					// AD�ɼ�ֵ���棬�˲���
extern float powervalue;					// ����õ��ĵ�ص�ѹֵ
extern u16 powervalueint;                   // �˲�����õ��ĵ�ص�ѹֵ����λmV

extern u16 positionvalue[3];				// ����������ֵ

extern u8 sendtemp[8];						// UART1���ͻ��棬DMAʹ��
extern u8 receivebuf[20];                   // UART1���ջ��棬DMAʹ��

//extern u8 transparent_sign;		        // ͸�������־
//extern u8 recflag;

extern u8 keyvalue;                         // ����ֵ����ͬ����ֵOLED��ʾ���治ͬ
extern u8 UART2_data;
extern key_inf_type key_up;
extern key_inf_type key_down;
extern key_inf_type key_back;
extern key_inf_type key_ok;

extern u8 gpioinputvalue;                   // ����IO�ڵ�ֵ
extern u8 gpiooutputvalue;                  // ���IO�ڵ�ֵ

extern char *blename;                       // ����ģ������

extern u8 oled_x;                           // OLED���λ��
extern u8 oled_y;

extern u16 exflashid;                       // Ƭ��FLASH ID

extern u16 luxvalue[6];                     // �Ҷȴ�����������ͨ��ֵ
extern float grayscaleSensor[6];            // �Ҷȴ�����������ѹֵ
extern u16 infrareddistance[8];             // ���⴫�������ֵ����λcm��������Χ10~80cm

extern int motorspeedbuffer[4];             // �ĸ����ģ����ٶȻ���


/************************************************************************************************************
**                            	�ⲿ��������
*************************************************************************************************************/
void get_ms(unsigned long *time);

void delay_us(u32 n);
void delay_ms(u32 n);

void Wp_DelayUs(u32 us);
void Wp_Delay_ms(u32 ms);
void Wp_DelayMs(u32 us);        // �δ�ʱ��


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
