/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_TIMER.h
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				Timer初始化相关;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				Timer初始化相关;
**
**-----------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
**-----------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
** 版本:
** 描述:
**
*************************************************************************************************************/
#ifndef WP_TIMER_H
#define WP_TIMER_H


#include "stm32f10x.h"
#include "Wp_Globle.h"


/************************************************************************************************************
**                            计时器相关宏定义
*************************************************************************************************************/
#define TIMER_CHANNEL0	0
#define TIMER_CHANNEL1	1
#define TIMER_CHANNEL2	2
#define TIMER_CHANNEL3	3


/************************************************************************************************************
**                             函数外部声明
*************************************************************************************************************/
extern void TimerHadler(u32 timerchannel);							// 定时器比较中断服务函数

extern void Wp_UserTimerEnableIT(u32 TimerChannel, u32 Time_us);	// 使能计时器中断
extern void Wp_UserTimerDisableIT(u32 TimerChannel);				// 禁能计时器中断

extern void Wp_UserTimerSetHadler(void (*ApplicationAddress)(u32));	// 设置定时器中断入口函数

extern void Wp_UserTimerConfigure(void);						    // Timer3相关初始化
extern void Wp_Timer2Configure(void);								// Timer2初始化函数


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
