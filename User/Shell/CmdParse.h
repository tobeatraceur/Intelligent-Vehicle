/*******************************************************Copyright*********************************************************
** 											Beijing Water-Plus Technology
**
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			CmdParse.h
** ����޶�����:		2009-03-19
** ���汾:			1.0
** ����:				��������������ڽ�����λ����ָ�������Ӧ��ִ�к���������Ӧ�����ݡ�
**
**------------------------------------------------------------------------------------------------------------------------
** ������:				����
** ��������:			2009-03-20
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
#ifndef CMDPARSE_H_
#define CMDPARSE_H_


#include "stm32f10x.h"
#include "CfgTypes.h"
#include "Protocol/UpRobot.h"
#include "Wp_Globle.h"
#include "Wp_Motor.h"
#include "Wp_MPU6050.h"

#include <stdio.h>						// printf������
#include "stdlib.h"
#include <string.h>
#include "math.h"


#define		CMDPARSE_GLOBALS


#ifndef   CMDPARSE_GLOBALS
     #define CMDPARSE_EXT
#else 
     #define CMDPARSE_EXT  extern
#endif 


/*************************************************************************************************************************
**														�����ⲿ����
*************************************************************************************************************************/
CMDPARSE_EXT void UpdataMotorCmdPraseSendBuf(u8 localid);
CMDPARSE_EXT void ActionMotorCmdPraseSendBuf(void);
CMDPARSE_EXT void UpMotorNouseCmdPraseSendBuf(u8 localid);
     
CMDPARSE_EXT void Wp_UpdataPcCmdPraseSendBuf(void);
CMDPARSE_EXT void Wp_UpdataPcMotorPraseSendBuf(u8 motornum);
     
CMDPARSE_EXT void Wp_UpdataPcAdcSendBuf(u8 groupnum);
CMDPARSE_EXT void Wp_UpdataPcGpioInputSendBuf(void);
CMDPARSE_EXT void Wp_UpdataPcGpioOutputSendBuf(void);
CMDPARSE_EXT void Wp_UpdataPcAlltiOutputSendBuf(void);
CMDPARSE_EXT void Wp_UpdataPcPowerValueSendBuf(void);
     
     
#endif
/*************************************************************************************************************************
**														�ļ�����
*************************************************************************************************************************/
