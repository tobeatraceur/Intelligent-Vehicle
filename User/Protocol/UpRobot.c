/*******************************************************Copyright*********************************************************
** 											Beijing Water-Plus Technology
**
**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			UpRobot.c
** 最后修订日期:		2009-04-01
** 最后版本:			1.0
** 描述:				机器人控制UART通讯协议的协议栈;
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:				律晔
** 创建日期:			2009-04-01
** 版本:				1.0
** 描述:				用于生成控制结构体并写发送缓冲；
**						处理UART接收缓冲区的数据，生成状态结构体；
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
*************************************************************************************************************************/
#include "Protocol/UpRobot.h"


UPROBOT_COMMAND_INFO_STRUCT str_cmd;        // 解析上位机数据包缓存
UPROBOT_DATA_INFO_STRUCT str_reply;         // 返回上位机数据包缓存


/*************************************************************************************************************************
** 函数名称:			UpRobotSlaveTxPacket
**
** 函数描述:			UpRobot从机数据包的组包(To String)、发送
**                      启智控制器返回上位机协议帧数据发送;
**
** 输入变量:			UPROBOT_DATA_INFO_STRUCT* p_uprobot_send;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-14
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void UpRobotSlaveTxPacket(UPROBOT_DATA_INFO_STRUCT* p_uprobot_send)
{
	uint8_t count = 0;
	uint8_t check_sum = 0;
	
	Wp_Usart1_SendChar(UPROBOT_START1);														// 开始位1、2
	Wp_Usart1_SendChar(UPROBOT_START2);
	Wp_Usart1_SendChar(p_uprobot_send->local_id);											// 设备ID
	Wp_Usart1_SendChar(p_uprobot_send->method_code);										// 方法代号    
	Wp_Usart1_SendChar(p_uprobot_send->parameter_length);									// 参数长度
//	Wp_Usart1_SendChar(p_uprobot_send->functional_unit);									// 功能单元代号
//	Wp_Usart1_SendChar(p_uprobot_send->state_byte);											// 状态标志
	
	for (count = 0; count < (p_uprobot_send->parameter_length); count++)
	{
		Wp_Usart1_SendChar(p_uprobot_send->p_para[count]);									// 写数据组
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
		check_sum += p_uprobot_send->p_para[count];											// 校验和计算
	}
    
	Wp_Usart1_SendChar(check_sum);
	
	Uart1Cts;																				// Uart1Cts取反
}


/*************************************************************************************************************************
** 函数名称:			UpRobotSlaveRxPacket
**
** 函数描述:			UpRobot从机字段解析(Parser)
**                      控制器解析上位机协议帧数据;
**                        
** 输入变量:			BUFFER_QUEUE* p_usart_data, UPROBOT_COMMAND_INFO_STRUCT* p_uprobot_receive;
** 返回值:				uint8_t;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-14
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
uint8_t UpRobotSlaveRxPacket(BUFFER_QUEUE* p_usart_data, UPROBOT_COMMAND_INFO_STRUCT* p_uprobot_receive)
{	
	static uint8_t count = 0;												// 循环次数计数器
	
	uint8_t temp_buffer = 0;												// 数据缓存
	uint8_t check_sum = 0;													// 校验和
	uint8_t check_sum_count = 0;
	
	while (1)
	{	
		if (TestEmptyBufferQueue(p_usart_data))								// 测试接收数据是否成功
		{
		//	recflag = 0;                                                    // 成功解析上位机一帧数据标志
            
			return 0;
		}
		
		count++;
		
		OutBufferQueue(p_usart_data, &temp_buffer);							// 获取数据
		
		switch (count)
		{
			case 1:															// 匹配启动字1
			{
				if (UPROBOT_START1 != temp_buffer)
				{
					count = 0;
				}
				break;
			}
			case 2:															// 匹配启动字2
			{		
				if (UPROBOT_START2 != temp_buffer)
				{
					count = 0;
				}
				break;
			}
			case 3:															// 设备ID号
			{
				p_uprobot_receive->device_id = temp_buffer;
				break;
			}
			case 4:															// 数据包长度
			{
				p_uprobot_receive->parameter_length = temp_buffer ;
				break;
			}
			default:
			{
				if (count < (5 + p_uprobot_receive->parameter_length))		// 保存参数
				{
					p_uprobot_receive->parameter[count - 5] = temp_buffer;
				}
				else														// 保存校验和
				{
					check_sum = UPROBOT_START1;								// 计算检验和
					check_sum += UPROBOT_START2;
					check_sum += p_uprobot_receive->device_id;			
					check_sum += p_uprobot_receive->parameter_length;
					for(check_sum_count = 0; check_sum_count < (p_uprobot_receive->parameter_length); check_sum_count++)
					{
						check_sum += p_uprobot_receive -> parameter[check_sum_count];
					}
					
					count = 0;												// 清计数器
                    
				//	recflag = 1;                                            // 成功解析上位机一帧数据标志
					
					if (check_sum == temp_buffer)
					{
						return 1;											// 无错误
					}
					else
					{
						return 0;											// 校验码错误
					}
				}
				break;
			}			
		}	 
	}
	
//	return 0;																// 无效缓冲数据溢出
}


/*************************************************************************************************************************
**                                                      文件结束
*************************************************************************************************************************/
