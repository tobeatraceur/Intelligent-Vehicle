/*******************************************************Copyright*********************************************************
** 											Beijing Water-Plus Technology
**
**
**-------------------------------------------------------文件信息---------------------------------------------------------
** 文件名称:			CmdParse.h
** 最后修订日期:		2009-03-19
** 最后版本:			1.0
** 描述:				命令解析器，用于解析上位机的指令，调用相应的执行函数，返回应答数据。
**
**------------------------------------------------------------------------------------------------------------------------
** 创建人:				律晔
** 创建日期:			2009-03-20
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
#ifndef CMDPARSE_H_
#define CMDPARSE_H_


#include "stm32f10x.h"
#include "CfgTypes.h"
#include "Protocol/UpRobot.h"
#include "Wp_Globle.h"
#include "Wp_Motor.h"
#include "Wp_MPU6050.h"

#include <stdio.h>						// printf函数用
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
**														函数外部声明
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
**														文件结束
*************************************************************************************************************************/
