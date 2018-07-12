/*******************************************************Copyright*********************************************************
** 											Beijing Water-Plus Technology
**
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			UpRobot.c
** ����޶�����:		2009-04-01
** ���汾:			1.0
** ����:				�����˿���UARTͨѶЭ���Э��ջ;
**
**------------------------------------------------------------------------------------------------------------------------
** ������:				����
** ��������:			2009-04-01
** �汾:				1.0
** ����:				�������ɿ��ƽṹ�岢д���ͻ��壻
**						����UART���ջ����������ݣ�����״̬�ṹ�壻
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
*************************************************************************************************************************/
#include "Protocol/UpRobot.h"


UPROBOT_COMMAND_INFO_STRUCT str_cmd;        // ������λ�����ݰ�����
UPROBOT_DATA_INFO_STRUCT str_reply;         // ������λ�����ݰ�����


/*************************************************************************************************************************
** ��������:			UpRobotSlaveTxPacket
**
** ��������:			UpRobot�ӻ����ݰ������(To String)������
**                      ���ǿ�����������λ��Э��֡���ݷ���;
**
** �������:			UPROBOT_DATA_INFO_STRUCT* p_uprobot_send;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-14
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void UpRobotSlaveTxPacket(UPROBOT_DATA_INFO_STRUCT* p_uprobot_send)
{
	uint8_t count = 0;
	uint8_t check_sum = 0;
	
	Wp_Usart1_SendChar(UPROBOT_START1);														// ��ʼλ1��2
	Wp_Usart1_SendChar(UPROBOT_START2);
	Wp_Usart1_SendChar(p_uprobot_send->local_id);											// �豸ID
	Wp_Usart1_SendChar(p_uprobot_send->method_code);										// ��������    
	Wp_Usart1_SendChar(p_uprobot_send->parameter_length);									// ��������
//	Wp_Usart1_SendChar(p_uprobot_send->functional_unit);									// ���ܵ�Ԫ����
//	Wp_Usart1_SendChar(p_uprobot_send->state_byte);											// ״̬��־
	
	for (count = 0; count < (p_uprobot_send->parameter_length); count++)
	{
		Wp_Usart1_SendChar(p_uprobot_send->p_para[count]);									// д������
	}
	
	check_sum = UPROBOT_START1;
	check_sum += UPROBOT_START2;
	check_sum += p_uprobot_send->local_id;
	check_sum += p_uprobot_send->method_code;    
	check_sum += p_uprobot_send->parameter_length;
//	check_sum += p_uprobot_send->functional_unit;
//	check_sum += p_uprobot_send->state_byte;
    
	for (count = 0; count < (p_uprobot_send->parameter_length); count++)
	{
		check_sum += p_uprobot_send->p_para[count];											// У��ͼ���
	}
    
	Wp_Usart1_SendChar(check_sum);
	
	Uart1Cts;																				// Uart1Ctsȡ��
}


/*************************************************************************************************************************
** ��������:			UpRobotSlaveRxPacket
**
** ��������:			UpRobot�ӻ��ֶν���(Parser)
**                      ������������λ��Э��֡����;
**                        
** �������:			BUFFER_QUEUE* p_usart_data, UPROBOT_COMMAND_INFO_STRUCT* p_uprobot_receive;
** ����ֵ:				uint8_t;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-14
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
uint8_t UpRobotSlaveRxPacket(BUFFER_QUEUE* p_usart_data, UPROBOT_COMMAND_INFO_STRUCT* p_uprobot_receive)
{	
	static uint8_t count = 0;												// ѭ������������
	
	uint8_t temp_buffer = 0;												// ���ݻ���
	uint8_t check_sum = 0;													// У���
	uint8_t check_sum_count = 0;
	
	while (1)
	{	
		if (TestEmptyBufferQueue(p_usart_data))								// ���Խ��������Ƿ�ɹ�
		{
		//	recflag = 0;                                                    // �ɹ�������λ��һ֡���ݱ�־
            
			return 0;
		}
		
		count++;
		
		OutBufferQueue(p_usart_data, &temp_buffer);							// ��ȡ����
		
		switch (count)
		{
			case 1:															// ƥ��������1
			{
				if (UPROBOT_START1 != temp_buffer)
				{
					count = 0;
				}
				break;
			}
			case 2:															// ƥ��������2
			{		
				if (UPROBOT_START2 != temp_buffer)
				{
					count = 0;
				}
				break;
			}
			case 3:															// �豸ID��
			{
				p_uprobot_receive->device_id = temp_buffer;
				break;
			}
			case 4:															// ���ݰ�����
			{
				p_uprobot_receive->parameter_length = temp_buffer ;
				break;
			}
			default:
			{
				if (count < (5 + p_uprobot_receive->parameter_length))		// �������
				{
					p_uprobot_receive->parameter[count - 5] = temp_buffer;
				}
				else														// ����У���
				{
					check_sum = UPROBOT_START1;								// ��������
					check_sum += UPROBOT_START2;
					check_sum += p_uprobot_receive->device_id;			
					check_sum += p_uprobot_receive->parameter_length;
					for(check_sum_count = 0; check_sum_count < (p_uprobot_receive->parameter_length); check_sum_count++)
					{
						check_sum += p_uprobot_receive -> parameter[check_sum_count];
					}
					
					count = 0;												// �������
                    
				//	recflag = 1;                                            // �ɹ�������λ��һ֡���ݱ�־
					
					if (check_sum == temp_buffer)
					{
						return 1;											// �޴���
					}
					else
					{
						return 0;											// У�������
					}
				}
				break;
			}			
		}	 
	}
	
//	return 0;																// ��Ч�����������
}


/*************************************************************************************************************************
**                                                      �ļ�����
*************************************************************************************************************************/
