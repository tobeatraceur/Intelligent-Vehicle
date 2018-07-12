/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_Motor.c
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
#include "Wp_Motor.h"


UPMOTOR_COMMAND_INFO_STRUCT str_motor_cmd;
UPMOTOR_DATA_INFO_STRUCT str_motor_reply;
WP_MOTOR_DATA_INFO_STRUCT motor_data[4];


// ʸ������Ǽ��㺯��
static int CalAngle(int angle1, int angle2)
{
	int ret;
    
	ret = angle2 - angle1;
	if (ret>180)
		ret = -360 + ret;
	if (ret < -180)
		ret = 360 + ret;
    
	return ret;
}

// ����ʸ���ٶȵ��������
//inAngleʸ���Ƕ�;  inVʸ������; inRotSpeed��ת�ٶ�
void VectorMove(int inAngle, int inV, int inRotSpeed)
{
	int nTmpV = -inV;
	int nRotSp = inRotSpeed;
    
//    int temp;
//    int tempinangle;            // ʸ���ǶȻ���
//    double tempbuffer;
    
//	nTmpV /= 4;                 // ����4��
//	nRotSp /= 4;
    nTmpV >>= 2;
    nRotSp >>= 2;
    
//  int motor[3];	            
    // ������������Ϊ���֣���ǰ�֣���ǰ��
	motorspeedbuffer[2] = -((int)(sin(((double)(CalAngle((int)(-inAngle), +180)))*3.14 / 180)*nTmpV) + nRotSp);
	motorspeedbuffer[0] = -((int)(sin(((double)(CalAngle((int)(-inAngle), 60)))*3.14 / 180)*nTmpV) + nRotSp);
	motorspeedbuffer[1] = -((int)(sin(((double)(CalAngle((int)(-inAngle), -60)))*3.14 / 180)*nTmpV) + nRotSp);
//	SendMotorValAgain();        // ���õ���ٶ�
    
/*  // �ҽ����޸İ汾
    tempinangle = -inAngle;
    temp = CalAngle(tempinangle, 180);
    tempbuffer = (double)(temp*3.14 / 180);
    motorspeedbuffer[2] = -((int)sin(tempbuffer * nTmpV) + nRotSp);
    
    tempinangle = -inAngle;
    temp = CalAngle(tempinangle, 60);
    tempbuffer = (double)(temp*3.14 / 180);
    motorspeedbuffer[0] = -((int)sin(tempbuffer * nTmpV) + nRotSp);
    
    tempinangle = -inAngle;
    temp = CalAngle(tempinangle, -60);
    tempbuffer = (double)(temp*3.14 / 180);
    motorspeedbuffer[1] = -((int)sin(tempbuffer * nTmpV) + nRotSp);
*/

//	motorspeedbuffer[2] = -((int)(sin(((double)(CalAngle(int(-inAngle), +180)))*3.14 / 180)*nTmpV) + nRotSp);
//	motorspeedbuffer[0] = -((int)(sin((double(CalAngle(int(-inAngle), 60)))*3.14 / 180)*nTmpV) + nRotSp);
//	motorspeedbuffer[1] = -((int)(sin((double(CalAngle(int(-inAngle), -60)))*3.14 / 180)*nTmpV) + nRotSp);
}


/*************************************************************************************************************
** ��������:			Wp_SetMotorSpeed
**
** ��������:			����ĳһ������ٶ�;
** 						motoridȡֵ��Χ��1~4;
**					    
** �������:			u8 motorid, long speed;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_SetMotorSpeed(u8 motorid, long speed)
{
	long temp = 0;
	u8 sendbuf[4] = {0};
    
    str_motor_reply.local_id = motorid;					                // �豸ID���ݶ���������IDΪ0x02
    str_motor_reply.method_code = 0x00;
    str_motor_reply.parameter_length = 0x04;                            // ��4���ٶȲ���
    
    temp = speed;                                                       // �ٶȣ��ٶ������ں�
    memcpy(sendbuf, &temp, 4);
    str_motor_reply.parameter[0] = sendbuf[3];
    str_motor_reply.parameter[1] = sendbuf[2];
    str_motor_reply.parameter[2] = sendbuf[1];
    str_motor_reply.parameter[3] = sendbuf[0];
    
	str_motor_reply.p_para = &str_motor_reply.parameter[0];
    
    UART3TXEN;
    Wp_DelayUs(2);
    UpMotorSlaveTxPacket(&str_motor_reply);                             // ��������
    Wp_DelayUs(1);
    UART3RXEN;
}


/*************************************************************************************************************
** ��������:			Wp_ActiomMotorMode
**
** ��������:			ִ��ָ��;
** 						
**					    
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_ActiomMotorMode(void)
{
    str_motor_reply.local_id = 0xFE;                                    // �豸ID���ݶ���������IDΪ0x02
    str_motor_reply.method_code = 0x01;
    str_motor_reply.parameter_length = 0x00;
    
	str_motor_reply.p_para = &str_motor_reply.parameter[0];
    
    UART3TXEN;
    Wp_DelayUs(2);
    UpMotorSlaveTxPacket(&str_motor_reply);                             // ��������
    Wp_DelayUs(1);
    UART3RXEN;
}


/*************************************************************************************************************************
** ��������:			UpMotorSlaveTxPacket
**
** ��������:			UpRobot�ӻ����ݰ������(To String)������;
**                      ������λ��Э��֡;
**
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
void UpMotorSlaveTxPacket(UPMOTOR_DATA_INFO_STRUCT* p_uprobot_send)
{
	uint8_t count = 0;
	uint8_t check_sum = 0;
	
	Wp_Usart3_SendChar(0x55);													                // ��ʼλ1��2
	Wp_Usart3_SendChar(0xAA);
	Wp_Usart3_SendChar(p_uprobot_send->local_id);												// �豸ID
    Wp_Usart3_SendChar(p_uprobot_send->method_code);	                                        // ������
	Wp_Usart3_SendChar(p_uprobot_send->parameter_length);										// ��������
	
	for(count = 0; count < (p_uprobot_send->parameter_length); count++)
	{
		Wp_Usart3_SendChar(p_uprobot_send->p_para[count]);										// д������
	}
	
	check_sum = 0x55;
	check_sum += 0xAA;
	check_sum += p_uprobot_send->local_id;
	check_sum += p_uprobot_send->method_code;
	check_sum += p_uprobot_send->parameter_length;
    
	for(count = 0; count < (p_uprobot_send->parameter_length); count++)
	{
		check_sum += p_uprobot_send->p_para[count];											    // У��ͼ���
	}
    
	Wp_Usart3_SendChar(check_sum);                                                              // ��������
    Wp_Usart3_SendChar(check_sum);                                                              // ��Ҫ��������У��ͣ�ʹ��SN65HVD75���״γ��ִ�����
}


/*************************************************************************************************************************
** ��������:			UpMotorSlaveRxPacket
**
** ��������:			UpMotor�ӻ��ֶν���(Parser);
**                      ������λ������Э��֡;
**                      
**					    
** �������:			BUFFER_QUEUE* p_usart_data, UPMOTOR_COMMAND_INFO_STRUCT* p_uprobot_receive;
** ����ֵ:				uint8;
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
uint8_t UpMotorSlaveRxPacket(BUFFER_QUEUE* p_usart_data, UPMOTOR_COMMAND_INFO_STRUCT* p_uprobot_receive)
{	
	static uint8_t count = 0;												// ѭ������������
	
	uint8_t temp_buffer = 0;												// ���ݻ���
	uint8_t check_sum = 0;													// У���
	uint8_t check_sum_count = 0;
	
	while (1)
	{	
		if (TestEmptyBufferQueue(p_usart_data))								// ���Խ��������Ƿ�ɹ�
		{
		//	recMotorpackflag = 0;
            
			return 0;
		}
		
		count++;
		
		OutBufferQueue(p_usart_data, &temp_buffer);							// ��ȡ����
		
		switch (count)
		{
			case 1:															// ƥ��������1
			{
				if (0x55 != temp_buffer)
				{
					count = 0;
				}
				break;
			}
			case 2:															// ƥ��������2
			{	
				if (0xAA != temp_buffer)
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
            case 4:															// ������
			{
				p_uprobot_receive->method_code = temp_buffer;
				break;
			}
			case 5:															// ���ݰ�����
			{
				p_uprobot_receive->parameter_length = temp_buffer ;
				break;
			}
			default:
			{
				if (count < (6 + p_uprobot_receive->parameter_length))		// �������
				{
					p_uprobot_receive->parameter[count - 6] = temp_buffer;
				}
				else														// ����У���
				{
					check_sum = 0x55;								        // ��������
					check_sum += 0xAA;
					check_sum += p_uprobot_receive->device_id;			
                    check_sum += p_uprobot_receive->method_code;
					check_sum += p_uprobot_receive->parameter_length;
					for(check_sum_count = 0; check_sum_count < (p_uprobot_receive->parameter_length); check_sum_count++)
					{
						check_sum += p_uprobot_receive->parameter[check_sum_count];
					}
                    
					count = 0;												// �������
                    
					if (check_sum == temp_buffer)
					{
                    //  recMotorpackflag = 1;
                        
						return 1;											// �޴���
					}
					else
					{
                    //  recMotorpackflag = 0;
                        
						return 0;											// У�������
					}
				}
				break;
			}
		}
	}
    
//    return 0;																// ��Ч�����������            
}


/*************************************************************************************************************
** ��������:			Wp_Usart3_SendChar
**
** ��������:			�ַ����ͺ���;
** 						
**					    
** �������:			unsigned char c;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_Usart3_SendChar(unsigned char c)
{
    USART_SendData(USART3, c);
    
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}


/*************************************************************************************************************
** ��������:			Wp_Usart3_SendStr
**
** ��������:			�ַ������ͺ���;
** 						
**					    
** �������:			char *str;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_Usart3_SendStr(char *str)
{
    while(*str)
    {
        USART_SendData(USART3, *str++);
		
        /* Loop until the end of transmission */
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    }
}			


/*************************************************************************************************************
** ��������:			Wp_Usart3Configure
**
** ��������:			Uart3��ʼ������;
** 						���ģ��ͨѶ�ӿ�;
**					    
** �������:			u32 baud;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_Usart3Configure(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	
	// ʹ�ܴ���3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	InitBufferQueue(&motor_rx_buffer, 255);						// �������ջ���
	
    // PB10-USART3_Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   			// ���츴�����
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
    // PB11-USART3_Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       // ��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
 	UART3RXEN;													// ʹ�ܽ���
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   		// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// 50Mʱ���ٶ�
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = baud;				    // ������115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART3, &USART_ClockInitStructure);
    USART_Init(USART3, &USART_InitStructure);
    
    USART_Cmd(USART3, ENABLE);                                  // ʹ�ܴ���3
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	            // ����3ʹ�ý����ж�
}


/*************************************************************************************************************
** ��������:			ReceiveUart3Hadler
**
** ��������:			�Զ����Uart3�����жϷ�����;
** 
**					          
** �������:			u8 val;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void ReceiveUart3Hadler(u8 val)
{
    AddBufferQueue(&motor_rx_buffer, val);
}


/*************************************************************************************************************
** ��������:			UP_SetUART3Hadler
**
** ��������:			����UART3���ݽ����ж���ں���;
** 						
**					    
** �������:			void (*ApplicationAddress)(u8);
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				
** ��������:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_SetUART3Hadler(void (*ApplicationAddress)(u8))
{
	if (ApplicationAddress != 0)
		g_UP_Uart3ITAddress = (u32)ApplicationAddress;	
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
