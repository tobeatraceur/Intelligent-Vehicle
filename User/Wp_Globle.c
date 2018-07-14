/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			Wp_Globle.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				系统全局变量和函数;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				系统全局变量和函数;
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
#include "Wp_Globle.h"


/*************************************************************************************************************************
**										变量定义
*************************************************************************************************************************/
volatile u32 g_SysTickTimer = 0;		// 1ms精确系统时钟计时器计数器（直接在中断函数里被改变值的变量需要加volatile声明）

u32 g_UP_Uart1ITAddress = 0;			// Uart1中断入口函数地址
u32 g_UP_Uart2ITAddress = 0;			// Uart2中断入口函数地址
u32 g_UP_Uart3ITAddress = 0;			// Uart3中断入口函数地址

u32 g_UP_ExtiFlag = 0;					// 外部中断使能的通道
u32 g_UP_ExtiITAddress = 0;				// 外部中断入口函数

bool g_UP_bTimerIT[4] = {FALSE, FALSE, FALSE, FALSE};		// 是否启用定时器中断，默认不启用
u32 g_UP_TimerITAddress = 0;								// 定时器3比较中断入口函数地址

u16 g_ADValue[16] = {0};			    // 当前ADC采样值寄存器，DMA直接传输ADC转换值到此缓存
float analogvalue[15] = {0.0};          // 各个通道电压值，数组0~14对应模拟量采集通道1~15

u16 powertemp[32] = {0};				// AD采集值缓存，滤波使用
float powervalue = 0.0;					// 滤波计算得到的电池电压值，单位V
u16 powervalueint = 0;                  // 滤波计算得到的电池电压值，单位mV

u16 positionvalue[3] = {0};				// 霍尔传感器值，双足机器人使用数字电位计使用

u8 sendtemp[8] = {0};					// UART1发送缓存，DMA使用
u8 receivebuf[20] = {0};                // UART1接收缓存，DMA使用

//u8 transparent_sign = 0;				// 透明传输标志
//u8 recflag = 0;                       // 正确解析一帧上位机数据包标志

u8 keyvalue = 0;                        // 按键值，不同按键值OLED显示界面不同
u8 UART2_data = 0;
key_inf_type key_up;
key_inf_type key_down;
key_inf_type key_back;
key_inf_type key_ok;

u8 gpioinputvalue = 0;                  // 输入IO口的值
u8 gpiooutputvalue = 0;                 // 输出IO口的值

char *blename = "wukangel";             // 蓝牙模块名称

u8 oled_x = 0;                          // OLED光标位置
u8 oled_y = 0;

u16 exflashid = 0;                      // 片外FLASH SST25F16 DEVICE ID

u16 luxvalue[6] = {0};                  // 灰度传感器测量光通量值
float grayscaleSensor[6] = {0.0};       // 灰度传感器测量电压值
u16 infrareddistance[8] = {0};          // 红外传感器测距值，单位cm，测量范围10~80cm

int motorspeedbuffer[4] = {0};          // 四个电机模块的速度缓存

int direction = 0;                      //小车运动状态：0-停止，1-前进，2-后退，3-向左，4-向右，5-左转，6-右转
long speed = 0;                         //小车车轮速度绝对值
double location_x = 0;                      
double location_y = 0;
double angle = 0;
u8 runflag = 0;

/*************************************************************************************************************
** 函数名称:			get_ms
**
** 函数描述:			MPU6050使用;
** 						
**					    
** 输入变量:			unsigned long *time;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void get_ms(unsigned long *time)
{
	
}


/*************************************************************************************************************
** 函数名称:			delay_us
**
** 函数描述:			us延时函数;
** 						
**					    
** 输入变量:			u32 us;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void delay_us(u32 us)
{
	u8 i = 0;
    
	while(us--)
    {
        for(i = 0; i < 8; i++)
        {
            __nop();
        }
    }
}


/*************************************************************************************************************
** 函数名称:			delay_ms
**
** 函数描述:			ms延时函数;
** 						
**					    
** 输入变量:			void;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void delay_ms(u32 n)
{
	while(n--)
    {
        delay_us(1000);
    }
}


/*************************************************************************************************************
** 函数名称:			Wp_DelayUs
**
** 函数描述:			us延时函数;
** 						
**					    
** 输入变量:			u32 us;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_DelayUs(u32 us)
{
	u8 i = 0;
    
	while(us)
	{
		us--;
        
		for(i = 0; i < 8; i++)
        {
            __nop();
        }
	}
}


/*************************************************************************************************************
** 函数名称:			Wp_Delay_ms
**
** 函数描述:			ms延时函数;
** 						
**					    
** 输入变量:			u32 ms;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_Delay_ms(u32 ms)
{
	u16 i = 0;
    
	while(ms)
	{
		ms--;
        
		for(i = 0; i < 8000; i++)
        {
            __nop();
        }
	}
}


/*************************************************************************************************************
** 函数名称:			Wp_DelayMs
**
** 函数描述:			ms延时函数;
** 						
**					    
** 输入变量:			u32 ms;
** 返回值:				void;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
void Wp_DelayMs(u32 ms)
{
	g_SysTickTimer = ms;
	while(g_SysTickTimer);
}


/*************************************************************************************************************
** 函数名称:			abs
**
** 函数描述:			
** 						
**					    
** 输入变量:			u32 i;
** 返回值:				u32;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
u32 abs(s32 i)
{
	return i >= 0 ? i : -i;
}


/*************************************************************************************************************
** 函数名称:			fabs
**
** 函数描述:			
** 						
**					    
** 输入变量:			double i;
** 返回值:				double;
**
** 使用宏或常量:		None;
** 使用全局变量:		None;
**
** 调用函数:			None;
**
** 创建人:				
** 创建日期:			2011-11-1
**-------------------------------------------------------------------------------------------------------------
** 修订人:
** 修订日期:
**-------------------------------------------------------------------------------------------------------------
***************************************************************************************************************/
double fabs(double i)
{
	return i >= 0 ? i : -i;
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
