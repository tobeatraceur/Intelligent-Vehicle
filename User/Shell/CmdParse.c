/*******************************************************Copyright*********************************************************
** 											Beijing Water-Plus Technology
**
**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			CmdParse.c
** 最后修订日期:		2010-04-09
** 最后版本:			1.0
** 描述:				UpRobot协议的命令解析器，用于解析从机栈收到的的指令，调用相应的执行函数，返回应答数据。
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:				律晔
** 创建日期:			2010-04-09
** 版本:				1.0
** 描述:				解析上位机的指令，调用相应的执行函数，返回应答数据。
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
#include "Shell/CmdParse.h"


/*************************************************************************************************************************
** 函数名称:			UpdataMotorCmdPraseSendBuf
**
** 函数描述:			主机数据打包发送;
**                      主机发送给驱动器模块数据缓存;
**					   	直接通过串口非中断方式发送;
** 输入变量:			u8 localid;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void UpdataMotorCmdPraseSendBuf(u8 localid)
{   
	long temp = 0;
	u8 sendbuf[4] = {0};    
//    static u8 i = 0;
    
    str_motor_reply.local_id = localid;					                // 设备ID，暂定被动行走ID为0x02
    str_motor_reply.method_code = 0x00;
    str_motor_reply.parameter_length = 0x04;                            // 仅4个速度参数
    
//  motor_data[0].sendspeed = 1000;
/*    i++;
    motor_data[0].sendspeed = 1000 * i;                                 // 测试使用
    if(i >= 6)
    {
        i = 1;
    }
*/  
    temp = motor_data[str_motor_reply.local_id - 1].sendspeed;          // 速度，速度数据在后
    memcpy(sendbuf, &temp, 4);
    str_motor_reply.parameter[0] = sendbuf[3];
    str_motor_reply.parameter[1] = sendbuf[2];
    str_motor_reply.parameter[2] = sendbuf[1];
    str_motor_reply.parameter[3] = sendbuf[0];  
    
	str_motor_reply.p_para = &str_motor_reply.parameter[0];
}


/*************************************************************************************************************************
** 函数名称:			ActionMotorCmdPraseSendBuf
**
** 函数描述:			组织执行指令;
**                      直接通过串口非中断方式发送;
**					   	
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void ActionMotorCmdPraseSendBuf(void)
{   
    str_motor_reply.local_id = 0xFE;             // 设备ID，暂定被动行走ID为0x02
    str_motor_reply.method_code = 0x01;
    str_motor_reply.parameter_length = 0x00;
}


/*************************************************************************************************************************
** 函数名称:			UpMotorNouseCmdPraseSendBuf
**
** 函数描述:			组织无效指令;
**                      直接通过串口非中断方式发送;
**					   	
** 输入变量:			u8 localid;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void UpMotorNouseCmdPraseSendBuf(u8 localid)
{   
    str_motor_reply.local_id = localid;             // 设备ID，暂定被动行走ID为0x02
    str_motor_reply.method_code = 0x00;
    str_motor_reply.parameter_length = 0x00;
}


/*************************************************************************************************************************
** 函数名称:			Wp_UpdataPcCmdPraseSendBuf
**
** 函数描述:			从机数据打包发送;
**                      串口1以中断或者DMA方式发送数据，以此方式组织从机数据;
**					   	控制器组织发给上位机数据;
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcCmdPraseSendBuf(void)
{
	long temp = 0;
	u8 sendbuf[4] = {0};
	u8 i = 0;
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // 设备ID，暂定启智控制器为0x03
    str_reply.method_code = 0x00;                               // 控制字，0x00
	str_reply.parameter_length = 32;	                        // 参数长度，32字节参数
    
/*  str_reply.parameter[0] = 0x55;
    check_sum = str_reply.parameter[0];
    str_reply.parameter[1] = 0xAA;
    check_sum += str_reply.parameter[1];
    str_reply.parameter[2] = 0x03;
    check_sum += str_reply.parameter[2];
    str_reply.parameter[3] = 0x00;
    check_sum += str_reply.parameter[3];    
    str_reply.parameter[4] = 0x20;
    check_sum += str_reply.parameter[4];
*/  
    // 四个电机模块的返回数据
    for (i = 0; i < 4; i++)
    {
        temp = motor_data[i].receivespeed;                              // 速度在前
        memcpy(sendbuf, &temp, 4);
        str_reply.parameter[0 + i*8] = sendbuf[3];
        check_sum += str_reply.parameter[0 + i*8];
        str_reply.parameter[1 + i*8] = sendbuf[2];
        check_sum += str_reply.parameter[1 + i*8];
        str_reply.parameter[2 + i*8] = sendbuf[1];
        check_sum += str_reply.parameter[2 + i*8];
        str_reply.parameter[3 + i*8] = sendbuf[0];
        check_sum += str_reply.parameter[3 + i*8];
        
        temp = motor_data[i].receiveposition;                           // 位置在后
        memcpy(sendbuf, &temp, 4);
        str_reply.parameter[4 + i*8] = sendbuf[3];
        check_sum += str_reply.parameter[4 + i*8];
        str_reply.parameter[5 + i*8] = sendbuf[2];
        check_sum += str_reply.parameter[5 + i*8];
        str_reply.parameter[6 + i*8] = sendbuf[1];
        check_sum += str_reply.parameter[6 + i*8];
        str_reply.parameter[7 + i*8] = sendbuf[0];
        check_sum += str_reply.parameter[7 + i*8];    
    }
    
    str_reply.parameter[32] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // 使用串口中断方式发送数据，使用此条代码，DMA方式发送则不使用此条代码
} 


/*************************************************************************************************************************
** 函数名称:			Wp_UpdataPcMotorPraseSendBuf
**
** 函数描述:			从机数据打包发送;
**                      motornum为电机编号，取值范围：1~4;
**					   	
** 输入变量:			u8 motornum;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcMotorPraseSendBuf(u8 motornum)
{
	long temp = 0;
	u8 sendbuf[4] = {0};
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // 设备ID，暂定启智控制器为0x03
    str_reply.method_code = 0x00;                               // 控制字，0x00
	str_reply.parameter_length = 10;	                        // 参数长度，32字节参数
    
    str_reply.parameter[0] = 0x00;
    str_reply.parameter[1] = motornum;
    
    temp = motor_data[motornum - 1].receivespeed;               // 速度在前
    memcpy(sendbuf, &temp, 4);
    str_reply.parameter[2] = sendbuf[3];
    check_sum += str_reply.parameter[2];
    str_reply.parameter[3] = sendbuf[2];
    check_sum += str_reply.parameter[3];
    str_reply.parameter[4] = sendbuf[1];
    check_sum += str_reply.parameter[4];
    str_reply.parameter[5] = sendbuf[0];
    check_sum += str_reply.parameter[5];
    
    temp = motor_data[motornum - 1].receiveposition;            // 位置在后
    memcpy(sendbuf, &temp, 4);
    str_reply.parameter[6] = sendbuf[3];
    check_sum += str_reply.parameter[6];
    str_reply.parameter[7] = sendbuf[2];
    check_sum += str_reply.parameter[7];
    str_reply.parameter[8] = sendbuf[1];
    check_sum += str_reply.parameter[8];
    str_reply.parameter[9] = sendbuf[0];
    check_sum += str_reply.parameter[9];    
    
    str_reply.parameter[10] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // 使用串口中断方式发送数据，使用此条代码，DMA方式发送则不使用此条代码
} 


/*************************************************************************************************************************
** 函数名称:			Wp_UpdataPcAdcSendBuf
**
** 函数描述:			从机数据打包发送;
**                      控制器组织发给上位机数据;
**					   	groupnum取值：1~3;
** 输入变量:			u8 groupnum;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcAdcSendBuf(u8 groupnum)
{
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // 设备ID，暂定启智控制器为0x03
    str_reply.method_code = 0x00;                               // 控制字，0x00
	str_reply.parameter_length = 12;	                        // 参数长度，32字节参数
    
    str_reply.parameter[0] = 0x00;
    check_sum = str_reply.parameter[0];
    str_reply.parameter[1] = groupnum;
    check_sum += str_reply.parameter[1];
    
    switch (groupnum)
    {
        case 1:
                str_reply.parameter[2] = g_ADValue[1] >> 8;
                check_sum += str_reply.parameter[2];
                str_reply.parameter[3] = g_ADValue[1] & 0xFF;
                check_sum += str_reply.parameter[3];
            
                str_reply.parameter[4] = g_ADValue[2] >> 8;
                check_sum += str_reply.parameter[4];
                str_reply.parameter[5] = g_ADValue[2] & 0xFF;
                check_sum += str_reply.parameter[5];
                
                str_reply.parameter[6] = g_ADValue[3] >> 8;
                check_sum += str_reply.parameter[6];
                str_reply.parameter[7] = g_ADValue[3] & 0xFF;
                check_sum += str_reply.parameter[7];
                
                str_reply.parameter[8] = g_ADValue[4] >> 8;
                check_sum += str_reply.parameter[8];
                str_reply.parameter[9] = g_ADValue[4] & 0xFF;
                check_sum += str_reply.parameter[9];
            
                str_reply.parameter[10] = g_ADValue[5] >> 8;
                check_sum += str_reply.parameter[10];
                str_reply.parameter[11] = g_ADValue[5] & 0xFF;
                check_sum += str_reply.parameter[11];
            break;
        case 2:
                str_reply.parameter[2] = g_ADValue[6] >> 8;
                check_sum += str_reply.parameter[2];
                str_reply.parameter[3] = g_ADValue[6] & 0xFF;
                check_sum += str_reply.parameter[3];
            
                str_reply.parameter[4] = g_ADValue[7] >> 8;
                check_sum += str_reply.parameter[4];
                str_reply.parameter[5] = g_ADValue[7] & 0xFF;
                check_sum += str_reply.parameter[5];
                
                str_reply.parameter[6] = g_ADValue[8] >> 8;
                check_sum += str_reply.parameter[6];
                str_reply.parameter[7] = g_ADValue[8] & 0xFF;
                check_sum += str_reply.parameter[7];
                
                str_reply.parameter[8] = g_ADValue[9] >> 8;
                check_sum += str_reply.parameter[8];
                str_reply.parameter[9] = g_ADValue[9] & 0xFF;
                check_sum += str_reply.parameter[9];
            
                str_reply.parameter[10] = g_ADValue[10] >> 8;
                check_sum += str_reply.parameter[10];
                str_reply.parameter[11] = g_ADValue[10] & 0xFF;
                check_sum += str_reply.parameter[11];
            break;
        case 3:
                str_reply.parameter[2] = g_ADValue[11] >> 8;
                check_sum += str_reply.parameter[2];
                str_reply.parameter[3] = g_ADValue[11] & 0xFF;
                check_sum += str_reply.parameter[3];
            
                str_reply.parameter[4] = g_ADValue[12] >> 8;
                check_sum += str_reply.parameter[4];
                str_reply.parameter[5] = g_ADValue[12] & 0xFF;
                check_sum += str_reply.parameter[5];
                
                str_reply.parameter[6] = g_ADValue[13] >> 8;
                check_sum += str_reply.parameter[6];
                str_reply.parameter[7] = g_ADValue[13] & 0xFF;
                check_sum += str_reply.parameter[7];
                
                str_reply.parameter[8] = g_ADValue[14] >> 8;
                check_sum += str_reply.parameter[8];
                str_reply.parameter[9] = g_ADValue[14] & 0xFF;
                check_sum += str_reply.parameter[9];
            
                str_reply.parameter[10] = g_ADValue[15] >> 8;
                check_sum += str_reply.parameter[10];
                str_reply.parameter[11] = g_ADValue[15] & 0xFF;
                check_sum += str_reply.parameter[11];
            break;
        default:
            break;
    }
    
    str_reply.parameter[12] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // 使用串口中断方式发送数据，使用此条代码，DMA方式发送则不使用此条代码
} 


/*************************************************************************************************************************
** 函数名称:			Wp_UpdataPcGpioInputSendBuf
**
** 函数描述:			从机数据打包发送;
**                      控制器组织发给上位机数据;
**					   	
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcGpioInputSendBuf(void)
{
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // 设备ID，暂定启智控制器为0x03
    str_reply.method_code = 0x00;                               // 控制字，0x00
	str_reply.parameter_length = 2;	                            // 参数长度，32字节参数
    
    str_reply.parameter[0] = 0x00;
    check_sum = str_reply.parameter[0];
    str_reply.parameter[1] = gpioinputvalue;                    // 输入端口的值
    check_sum += str_reply.parameter[1];
    
    str_reply.parameter[2] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // 使用串口中断方式发送数据，使用此条代码，DMA方式发送则不使用此条代码
}


/*************************************************************************************************************************
** 函数名称:			Wp_UpdataPcGpioOutputSendBuf
**
** 函数描述:			从机数据打包发送;
**                      控制器组织发给上位机数据;
**					   	
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcGpioOutputSendBuf(void)
{
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // 设备ID，暂定启智控制器为0x03
    str_reply.method_code = 0x00;                               // 控制字，0x00
	str_reply.parameter_length = 2;	                            // 参数长度，32字节参数
    
    str_reply.parameter[0] = 0x00;
    check_sum = str_reply.parameter[0];
    str_reply.parameter[1] = gpiooutputvalue;                   // 输入端口的值
    check_sum += str_reply.parameter[1];
    
    str_reply.parameter[2] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // 使用串口中断方式发送数据，使用此条代码，DMA方式发送则不使用此条代码
}


/*************************************************************************************************************************
** 函数名称:			Wp_UpdataPcAlltiOutputSendBuf
**
** 函数描述:			从机数据打包发送;
**                      控制器组织发给上位机数据;
**					   	
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcAlltiOutputSendBuf(void)
{
    u8 check_sum = 0;
    long temp = 0;
	u8 sendbuf[4] = {0};
    
    str_reply.local_id = 0x03;					                // 设备ID，暂定启智控制器为0x03
    str_reply.method_code = 0x00;                               // 控制字，0x00
	str_reply.parameter_length = 12;	                        // 参数长度，32字节参数
    
    temp = wp_dmp_data.Pitch;                                   // 俯仰信息
    memcpy(sendbuf, &temp, 4);
    str_reply.parameter[0] = sendbuf[3];
    check_sum += str_reply.parameter[0];
    str_reply.parameter[1] = sendbuf[2];
    check_sum += str_reply.parameter[1];
    str_reply.parameter[2] = sendbuf[1];
    check_sum += str_reply.parameter[2];
    str_reply.parameter[3] = sendbuf[0];
    check_sum += str_reply.parameter[3];
    
    temp = wp_dmp_data.Roll;                                    // 滚转信息
    memcpy(sendbuf, &temp, 4);
    str_reply.parameter[4] = sendbuf[3];
    check_sum += str_reply.parameter[4];
    str_reply.parameter[5] = sendbuf[2];
    check_sum += str_reply.parameter[5];
    str_reply.parameter[6] = sendbuf[1];
    check_sum += str_reply.parameter[6];
    str_reply.parameter[7] = sendbuf[0];
    check_sum += str_reply.parameter[7];
    
    temp = wp_dmp_data.Yaw;                                     // 偏航信息
    memcpy(sendbuf, &temp, 4);
    str_reply.parameter[8] = sendbuf[3];
    check_sum += str_reply.parameter[8];
    str_reply.parameter[9] = sendbuf[2];
    check_sum += str_reply.parameter[9];
    str_reply.parameter[10] = sendbuf[1];
    check_sum += str_reply.parameter[10];
    str_reply.parameter[11] = sendbuf[0];
    check_sum += str_reply.parameter[11];
    
    str_reply.parameter[12] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // 使用串口中断方式发送数据，使用此条代码，DMA方式发送则不使用此条代码
}


/*************************************************************************************************************************
** 函数名称:			Wp_UpdataPcPowerValueSendBuf
**
** 函数描述:			从机数据打包发送;
**                      控制器组织发给上位机数据;
**					   	
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				律晔
** 创建日期:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcPowerValueSendBuf(void)
{
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // 设备ID，暂定启智控制器为0x03
    str_reply.method_code = 0x00;                               // 控制字，0x00
	str_reply.parameter_length = 2;	                            // 参数长度，32字节参数
    
    str_reply.parameter[0] = powervalueint >> 8;
    check_sum = str_reply.parameter[0];
    str_reply.parameter[1] = (powervalueint >> 8) & 0xFF;       // 电源电压值，单位mV
    check_sum += str_reply.parameter[1];
    
    str_reply.parameter[2] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // 使用串口中断方式发送数据，使用此条代码，DMA方式发送则不使用此条代码
}


/*************************************************************************************************************************
**														文件结束
*************************************************************************************************************************/
