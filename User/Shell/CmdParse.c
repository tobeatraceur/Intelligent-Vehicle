/*******************************************************Copyright*********************************************************
** 											Beijing Water-Plus Technology
**
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			CmdParse.c
** ����޶�����:		2010-04-09
** ���汾:			1.0
** ����:				UpRobotЭ�����������������ڽ����ӻ�ջ�յ��ĵ�ָ�������Ӧ��ִ�к���������Ӧ�����ݡ�
**
**------------------------------------------------------------------------------------------------------------------------
** ������:				����
** ��������:			2010-04-09
** �汾:				1.0
** ����:				������λ����ָ�������Ӧ��ִ�к���������Ӧ�����ݡ�
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
#include "Shell/CmdParse.h"


/*************************************************************************************************************************
** ��������:			UpdataMotorCmdPraseSendBuf
**
** ��������:			�������ݴ������;
**                      �������͸�������ģ�����ݻ���;
**					   	ֱ��ͨ�����ڷ��жϷ�ʽ����;
** �������:			u8 localid;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void UpdataMotorCmdPraseSendBuf(u8 localid)
{   
	long temp = 0;
	u8 sendbuf[4] = {0};    
//    static u8 i = 0;
    
    str_motor_reply.local_id = localid;					                // �豸ID���ݶ���������IDΪ0x02
    str_motor_reply.method_code = 0x00;
    str_motor_reply.parameter_length = 0x04;                            // ��4���ٶȲ���
    
//  motor_data[0].sendspeed = 1000;
/*    i++;
    motor_data[0].sendspeed = 1000 * i;                                 // ����ʹ��
    if(i >= 6)
    {
        i = 1;
    }
*/  
    temp = motor_data[str_motor_reply.local_id - 1].sendspeed;          // �ٶȣ��ٶ������ں�
    memcpy(sendbuf, &temp, 4);
    str_motor_reply.parameter[0] = sendbuf[3];
    str_motor_reply.parameter[1] = sendbuf[2];
    str_motor_reply.parameter[2] = sendbuf[1];
    str_motor_reply.parameter[3] = sendbuf[0];  
    
	str_motor_reply.p_para = &str_motor_reply.parameter[0];
}


/*************************************************************************************************************************
** ��������:			ActionMotorCmdPraseSendBuf
**
** ��������:			��ִ֯��ָ��;
**                      ֱ��ͨ�����ڷ��жϷ�ʽ����;
**					   	
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void ActionMotorCmdPraseSendBuf(void)
{   
    str_motor_reply.local_id = 0xFE;             // �豸ID���ݶ���������IDΪ0x02
    str_motor_reply.method_code = 0x01;
    str_motor_reply.parameter_length = 0x00;
}


/*************************************************************************************************************************
** ��������:			UpMotorNouseCmdPraseSendBuf
**
** ��������:			��֯��Чָ��;
**                      ֱ��ͨ�����ڷ��жϷ�ʽ����;
**					   	
** �������:			u8 localid;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void UpMotorNouseCmdPraseSendBuf(u8 localid)
{   
    str_motor_reply.local_id = localid;             // �豸ID���ݶ���������IDΪ0x02
    str_motor_reply.method_code = 0x00;
    str_motor_reply.parameter_length = 0x00;
}


/*************************************************************************************************************************
** ��������:			Wp_UpdataPcCmdPraseSendBuf
**
** ��������:			�ӻ����ݴ������;
**                      ����1���жϻ���DMA��ʽ�������ݣ��Դ˷�ʽ��֯�ӻ�����;
**					   	��������֯������λ������;
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcCmdPraseSendBuf(void)
{
	long temp = 0;
	u8 sendbuf[4] = {0};
	u8 i = 0;
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // �豸ID���ݶ����ǿ�����Ϊ0x03
    str_reply.method_code = 0x00;                               // �����֣�0x00
	str_reply.parameter_length = 32;	                        // �������ȣ�32�ֽڲ���
    
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
    // �ĸ����ģ��ķ�������
    for (i = 0; i < 4; i++)
    {
        temp = motor_data[i].receivespeed;                              // �ٶ���ǰ
        memcpy(sendbuf, &temp, 4);
        str_reply.parameter[0 + i*8] = sendbuf[3];
        check_sum += str_reply.parameter[0 + i*8];
        str_reply.parameter[1 + i*8] = sendbuf[2];
        check_sum += str_reply.parameter[1 + i*8];
        str_reply.parameter[2 + i*8] = sendbuf[1];
        check_sum += str_reply.parameter[2 + i*8];
        str_reply.parameter[3 + i*8] = sendbuf[0];
        check_sum += str_reply.parameter[3 + i*8];
        
        temp = motor_data[i].receiveposition;                           // λ���ں�
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
    
	str_reply.p_para = &str_reply.parameter[0];     // ʹ�ô����жϷ�ʽ�������ݣ�ʹ�ô������룬DMA��ʽ������ʹ�ô�������
} 


/*************************************************************************************************************************
** ��������:			Wp_UpdataPcMotorPraseSendBuf
**
** ��������:			�ӻ����ݴ������;
**                      motornumΪ�����ţ�ȡֵ��Χ��1~4;
**					   	
** �������:			u8 motornum;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcMotorPraseSendBuf(u8 motornum)
{
	long temp = 0;
	u8 sendbuf[4] = {0};
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // �豸ID���ݶ����ǿ�����Ϊ0x03
    str_reply.method_code = 0x00;                               // �����֣�0x00
	str_reply.parameter_length = 10;	                        // �������ȣ�32�ֽڲ���
    
    str_reply.parameter[0] = 0x00;
    str_reply.parameter[1] = motornum;
    
    temp = motor_data[motornum - 1].receivespeed;               // �ٶ���ǰ
    memcpy(sendbuf, &temp, 4);
    str_reply.parameter[2] = sendbuf[3];
    check_sum += str_reply.parameter[2];
    str_reply.parameter[3] = sendbuf[2];
    check_sum += str_reply.parameter[3];
    str_reply.parameter[4] = sendbuf[1];
    check_sum += str_reply.parameter[4];
    str_reply.parameter[5] = sendbuf[0];
    check_sum += str_reply.parameter[5];
    
    temp = motor_data[motornum - 1].receiveposition;            // λ���ں�
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
    
	str_reply.p_para = &str_reply.parameter[0];     // ʹ�ô����жϷ�ʽ�������ݣ�ʹ�ô������룬DMA��ʽ������ʹ�ô�������
} 


/*************************************************************************************************************************
** ��������:			Wp_UpdataPcAdcSendBuf
**
** ��������:			�ӻ����ݴ������;
**                      ��������֯������λ������;
**					   	groupnumȡֵ��1~3;
** �������:			u8 groupnum;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcAdcSendBuf(u8 groupnum)
{
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // �豸ID���ݶ����ǿ�����Ϊ0x03
    str_reply.method_code = 0x00;                               // �����֣�0x00
	str_reply.parameter_length = 12;	                        // �������ȣ�32�ֽڲ���
    
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
    
	str_reply.p_para = &str_reply.parameter[0];     // ʹ�ô����жϷ�ʽ�������ݣ�ʹ�ô������룬DMA��ʽ������ʹ�ô�������
} 


/*************************************************************************************************************************
** ��������:			Wp_UpdataPcGpioInputSendBuf
**
** ��������:			�ӻ����ݴ������;
**                      ��������֯������λ������;
**					   	
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcGpioInputSendBuf(void)
{
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // �豸ID���ݶ����ǿ�����Ϊ0x03
    str_reply.method_code = 0x00;                               // �����֣�0x00
	str_reply.parameter_length = 2;	                            // �������ȣ�32�ֽڲ���
    
    str_reply.parameter[0] = 0x00;
    check_sum = str_reply.parameter[0];
    str_reply.parameter[1] = gpioinputvalue;                    // ����˿ڵ�ֵ
    check_sum += str_reply.parameter[1];
    
    str_reply.parameter[2] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // ʹ�ô����жϷ�ʽ�������ݣ�ʹ�ô������룬DMA��ʽ������ʹ�ô�������
}


/*************************************************************************************************************************
** ��������:			Wp_UpdataPcGpioOutputSendBuf
**
** ��������:			�ӻ����ݴ������;
**                      ��������֯������λ������;
**					   	
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcGpioOutputSendBuf(void)
{
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // �豸ID���ݶ����ǿ�����Ϊ0x03
    str_reply.method_code = 0x00;                               // �����֣�0x00
	str_reply.parameter_length = 2;	                            // �������ȣ�32�ֽڲ���
    
    str_reply.parameter[0] = 0x00;
    check_sum = str_reply.parameter[0];
    str_reply.parameter[1] = gpiooutputvalue;                   // ����˿ڵ�ֵ
    check_sum += str_reply.parameter[1];
    
    str_reply.parameter[2] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // ʹ�ô����жϷ�ʽ�������ݣ�ʹ�ô������룬DMA��ʽ������ʹ�ô�������
}


/*************************************************************************************************************************
** ��������:			Wp_UpdataPcAlltiOutputSendBuf
**
** ��������:			�ӻ����ݴ������;
**                      ��������֯������λ������;
**					   	
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcAlltiOutputSendBuf(void)
{
    u8 check_sum = 0;
    long temp = 0;
	u8 sendbuf[4] = {0};
    
    str_reply.local_id = 0x03;					                // �豸ID���ݶ����ǿ�����Ϊ0x03
    str_reply.method_code = 0x00;                               // �����֣�0x00
	str_reply.parameter_length = 12;	                        // �������ȣ�32�ֽڲ���
    
    temp = wp_dmp_data.Pitch;                                   // ������Ϣ
    memcpy(sendbuf, &temp, 4);
    str_reply.parameter[0] = sendbuf[3];
    check_sum += str_reply.parameter[0];
    str_reply.parameter[1] = sendbuf[2];
    check_sum += str_reply.parameter[1];
    str_reply.parameter[2] = sendbuf[1];
    check_sum += str_reply.parameter[2];
    str_reply.parameter[3] = sendbuf[0];
    check_sum += str_reply.parameter[3];
    
    temp = wp_dmp_data.Roll;                                    // ��ת��Ϣ
    memcpy(sendbuf, &temp, 4);
    str_reply.parameter[4] = sendbuf[3];
    check_sum += str_reply.parameter[4];
    str_reply.parameter[5] = sendbuf[2];
    check_sum += str_reply.parameter[5];
    str_reply.parameter[6] = sendbuf[1];
    check_sum += str_reply.parameter[6];
    str_reply.parameter[7] = sendbuf[0];
    check_sum += str_reply.parameter[7];
    
    temp = wp_dmp_data.Yaw;                                     // ƫ����Ϣ
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
    
	str_reply.p_para = &str_reply.parameter[0];     // ʹ�ô����жϷ�ʽ�������ݣ�ʹ�ô������룬DMA��ʽ������ʹ�ô�������
}


/*************************************************************************************************************************
** ��������:			Wp_UpdataPcPowerValueSendBuf
**
** ��������:			�ӻ����ݴ������;
**                      ��������֯������λ������;
**					   	
** �������:			void;
** ����ֵ:				void;
**
** ʹ�ú����:		None;
** ʹ��ȫ�ֱ���:		None;
**
** ���ú���:			None;
**
** ������:				����
** ��������:			2009-03-22
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
**------------------------------------------------------------------------------------------------------------------------
*************************************************************************************************************************/
void Wp_UpdataPcPowerValueSendBuf(void)
{
    u8 check_sum = 0;
    
    str_reply.local_id = 0x03;					                // �豸ID���ݶ����ǿ�����Ϊ0x03
    str_reply.method_code = 0x00;                               // �����֣�0x00
	str_reply.parameter_length = 2;	                            // �������ȣ�32�ֽڲ���
    
    str_reply.parameter[0] = powervalueint >> 8;
    check_sum = str_reply.parameter[0];
    str_reply.parameter[1] = (powervalueint >> 8) & 0xFF;       // ��Դ��ѹֵ����λmV
    check_sum += str_reply.parameter[1];
    
    str_reply.parameter[2] = check_sum;
    
	str_reply.p_para = &str_reply.parameter[0];     // ʹ�ô����жϷ�ʽ�������ݣ�ʹ�ô������룬DMA��ʽ������ʹ�ô�������
}


/*************************************************************************************************************************
**														�ļ�����
*************************************************************************************************************************/
