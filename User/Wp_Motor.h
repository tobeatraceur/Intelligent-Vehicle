/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_Motor.h
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				��������ļ�;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				��������ļ�;
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
#ifndef WP_MOTOR_H
#define WP_MOTOR_H


#include "stm32f10x.h"

#include "Wp_Globle.h"
#include "Wp_UART.h"
#include "Queue.h"

#include <string.h>
#include "math.h"


#define		UPROBOT_GLOBALS

#ifndef   UPROBOT_GLOBALS
     #define UPROBOT_EXT
#else 
     #define UPROBOT_EXT  extern
#endif 
     
     
/************************************************************************************************************
**                            	�궨��
*************************************************************************************************************/
#define UPMOTOR_COMMAND_INFO_MAX_LENGTH			0x20			// ���������
#define UPMOTOR_DATA_INFO_MAX_LENGTH			0x20            // ��������ģ����ƣ����4�������֣��������Ҫ16�ֽڻ���
     
     
// Usart3���ͽ���ʹ�ܶ˿ں궨��
//#define UART3TXEN   GPIO_SetBits(GPIOD, GPIO_Pin_7)           // �øߵ�ƽ
//#define UART3RXEN   GPIO_ResetBits(GPIOD, GPIO_Pin_7)	        // �õ͵�ƽ

//#define UART3TXEN   GPIOD->BSRR = GPIO_Pin_7                  // �øߵ�ƽ��ʹ�ܷ���
//#define UART3RXEN   GPIOD->BRR = GPIO_Pin_7                   // �õ͵�ƽ��ʹ�ܽ���

#define UART3TXEN      (GPIOD->ODR |= GPIO_Pin_7)				// �øߵ�ƽ
#define UART3RXEN      (GPIOD->ODR &= ~GPIO_Pin_7)			    // �õ͵�ƽ


/*************************************************************************************************************************
**                                                     �ṹ�嶨��
*************************************************************************************************************************/
typedef struct SUpMotorDataInfo                                 // ���͸�����ģ���Э��֡
{
	u8 local_id;												// ����ID
	u8 device_id;												// �豸ID
	u8 method_code;												// �������ţ�������
    
	u8 parameter_length;										// ��������
    
	u8* p_para;													// ��������ָ�룬���ڷ���
	u8 parameter[UPMOTOR_DATA_INFO_MAX_LENGTH];					// �������飬���ڽ���
}UPMOTOR_DATA_INFO_STRUCT;										// UpRobot�������մӻ����ͽṹ��


typedef struct SUpMotorCommandInfo                              // ��������ģ�鷢��Э��֡
{
	u8 local_id;												// ����ID
	u8 device_id;												// �豸ID
	u8 method_code;												// ��������
	
	u8 parameter_length;										// ��������
    
	u8* p_para;													// ��������ָ�룬���ڷ���
	u8 parameter[UPMOTOR_COMMAND_INFO_MAX_LENGTH];				// �������飬���ڽ���
}UPMOTOR_COMMAND_INFO_STRUCT;									// UpRobot�������ʹӻ����սṹ��


typedef struct WpMotorDataInfo                                  // ���͹ؽ�ģ����ٶȺ�λ�ýṹ��
{
	long sendspeed;								                // ���͸�����ģ����ٶȻ��棬Ҳ���ǽ�����λ�����ٶȻ���
	long receivespeed;							                // ���ո���ģ����ٶȻ��棬Ҳ����Ҫ������λ�����ٶȻ���
    long receiveposition;                                       // ���ո���ģ���λ�û��棬Ҳ����Ҫ������λ����λ�û���
}WP_MOTOR_DATA_INFO_STRUCT;


/*************************************************************************************************************************
**                                                     �ṹ�嶨��
*************************************************************************************************************************/
UPROBOT_EXT UPMOTOR_COMMAND_INFO_STRUCT str_motor_cmd;
UPROBOT_EXT UPMOTOR_DATA_INFO_STRUCT str_motor_reply;
UPROBOT_EXT WP_MOTOR_DATA_INFO_STRUCT motor_data[4];


/************************************************************************************************************
**                            	�ⲿ��������
*************************************************************************************************************/
UPROBOT_EXT void Wp_Usart3_SendChar(unsigned char c);
UPROBOT_EXT void Wp_Usart3_SendStr(char *str);
UPROBOT_EXT void Wp_Usart3Configure(u32 baud);
UPROBOT_EXT void ReceiveUart3Hadler(u8 val);
UPROBOT_EXT void Wp_SetUART3Hadler(void (*ApplicationAddress)(u8));

UPROBOT_EXT void Wp_SetMotorSpeed(u8 motorid, long speed);
UPROBOT_EXT void Wp_ActiomMotorMode(void);

UPROBOT_EXT void UpMotorSlaveTxPacket(UPMOTOR_DATA_INFO_STRUCT* p_uprobot_send);
UPROBOT_EXT uint8_t UpMotorSlaveRxPacket(BUFFER_QUEUE* p_usart_data, UPMOTOR_COMMAND_INFO_STRUCT* p_uprobot_receive);

UPROBOT_EXT void VectorMove(int inAngle, int inV, int inRotSpeed);


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
