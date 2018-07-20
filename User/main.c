/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------文件信息-------------------------------------------------------
** 文件名称:			main.c
** 最后修订日期:  		2012-10-10
** 最后版本:			1.0
** 描述:				移动小底盘控制器系统主函数;
**
**-----------------------------------------------------------------------------------------------------------
** 创建人:				吴康
** 创建日期:			2012-02-09
** 版本:				1.0
** 描述:				移动小底盘控制器系统主函数;
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
#include "Wp_Sys.h"
#include "math.h"


/*************************************************************************************************************
** 函数名称:			main
**
** 函数描述:			系统主函数;
** 						
**					    
** 输入变量:			void;
** 返回值:				int;
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
int main(void)
{
    uint8 i = 0;
    uint8 j = 0;
    uint8 k = 0;
    uint8 h = 0;
    
    u8 n = 0;
    
	float pitch = 0.0;          // 姿态缓存
	float roll = 0.0;
	float yaw = 0.0;
    
//  u16 distance = 0;           // 距离缓存
//  u16 lux = 0;                // Lux缓存
    
    
	/*	计时器(Timer3)及其中断的初始化（必须放在系统初始化函数的前面）	*/
//	Wp_UserTimerEnableIT(TIMER_CHANNEL0, 1000000);	// 使能计时器0，计时时间1s
//	Wp_UserTimerEnableIT(TIMER_CHANNEL2, 1000);	    // 使能计时器2，计时时间1ms
//	Wp_UserTimerSetHadler(TimerHadler);			    // 传递计时器中断入口函数指针
	
    /*	串口1~3中断的初始化（必须放在系统初始化函数的前面）	*/
	Wp_SetUART1Hadler(ReceiveUart1Hadler);		    // UART1中断入口函数
	Wp_SetUART2Hadler(ReceiveUart2Hadler);		    // UART2中断入口函数
	Wp_SetUART3Hadler(ReceiveUart3Hadler);		    // UART3中断入口函数
	
	Wp_UserTimerEnableIT(TIMER_CHANNEL0, 10);	    // 使能计时器0，计时时间10us
	Wp_UserTimerEnableIT(TIMER_CHANNEL1, 500000);	    // 使能计时器2，计时时间500ms
	Wp_UserTimerSetHadler(TimerHadler);			        // 传递计时器中断入口函数指针
	
	Wp_SystemConfigure();						    // 系统初始化
	
	while(1)
	{
     // keyvalue = 5;                                                   // 显示当前界面

		//Wp_SetPortOutputValue(1,1);																			//调用Wp_SetPortOutputValue(u8 port, u8 value)，使Out1输出1
																																			//（注意这里Out端口不是从0开始）
		
		  // 计算红外传感器测量距离值
      for (n = 0; n < 12; n++)
			{
        infrareddistance[n] = Wp_CalculateDistanceChannel(n+1);
      }
			// 计算灰度传感器光通量值
      for (n = 0; n < 6; n++)
      {
          luxvalue[n] = Wp_CalculateLuxChannel(7+n);       // 测试使用，计算Lux    灰度传感器从第7个开始
      }

        switch(keyvalue)
        {
            case 1:                                                     // 显示姿态信息
                    k++;
                    if (k == 1)
                    {
                        Wp_ClearOled();                                 // 清屏
                    }
                    if (k > 100)
                    {
                        k = 2;
                    }
                    j = 0;
                    h = 0;
                    i = 0;
                    
                    pitch = wp_dmp_data.Pitch;				            // 显示俯仰角
                    if (wp_dmp_data.Pitch >= 0)
                    {
                        OLED_P8x16Str(0, 1, "P:+");
                        Wp_Disfloat(3, 1, pitch, 2);
                    }
                    else
                    {
                        OLED_P8x16Str(0, 1, "P:-");
                        pitch = -pitch;
                        Wp_Disfloat(3, 1, pitch, 2);
                    }
                    roll = wp_dmp_data.Roll;				            // 显示滚转角
                    if (roll >= 0)
                    {
                        OLED_P8x16Str(0, 2, "R:+");
                        Wp_Disfloat(3, 2, roll, 2);
                    }
                    else
                    {
                        OLED_P8x16Str(0, 2, "R:-");
                        roll = -roll;
                        Wp_Disfloat(3, 2, roll, 2);
                    }
                    yaw = wp_dmp_data.Yaw;					            // 显示偏航角
                    if (yaw >= 0)
                    {
                        OLED_P8x16Str(0, 3, "Y:+");
                        Wp_Disfloat(3, 3, yaw, 2);
                    }
                    else
                    {
                        OLED_P8x16Str(0, 3, "Y:-");
                        yaw = -yaw;
                        Wp_Disfloat(3, 3, yaw, 2);
                    }
                    
                    OLED_P8x16Char(15, 1, 'V');                         // 显示电源电压
                    Wp_DisfloatIntegerandDecimal(11, 1, powervalue, 2, 1);
                    Wp_DisP16x16DotArray(2, 0, 0);                      // 显示“姿态信息”
                    Wp_DisP16x16DotArray(3, 0, 1);
                    Wp_DisP16x16DotArray(4, 0, 2);
                    Wp_DisP16x16DotArray(5, 0, 3);
                    
                    // 测试光通量值
                //  Wp_DisfloatIntegerandDecimal(11, 2, analogvalue[10]-0.99, 1, 3);
                //  lux = ((analogvalue[10]-0.99) * 10000) / 180;       // 测试使用，计算Lux
                //  Wp_DisfloatIntegerandDecimal(11, 3, lux, 3, 1);
                //  lux = Wp_CalculateLuxChannel(11);                   // 测试使用，计算Lux
                //  Wp_DisIntNum(11, 3, lux, 5);
                    
                    // 测试红外传感器距离值
                //  Wp_DisfloatIntegerandDecimal(11, 3, analogvalue[11], 1, 3);
                //  distance = Wp_CalculateDistanceChannel(12);
                //  Wp_DisIntNum(11, 2, distance, 3);
                    
                /*  Wp_DisfloatIntegerandDecimal(11, 3, analogvalue[0], 1, 3);
                    Wp_DisIntNum(11, 2, infrareddistance[0], 3);
                    // 计算红外传感器测量距离值
                    for (n = 0; n < 12; n++)
                    {
                        infrareddistance[n] = Wp_CalculateDistanceChannel(n+1);
                    }
                */
                    
                break;
                
            case 2:                                                     // 显示输入GPIO值
                    j++;
                    if (j == 1)
                    {
                        Wp_ClearOled();                                 // 清屏
                    }
                    if (j > 100)
                    {
                        j = 2;
                    }
                    k = 0;
                    h = 0;
                    i = 0;
                    
                    printf("  Input Value\n");		                    // 用printf显示一串字符
                //  OLED_P8x16Str(2, 0, "Input Value");
                    OLED_Dis8x16CharNum(0, 1, 1);
                    OLED_Dis8x16CharNum(4, 1, 2);
                    OLED_Dis8x16CharNum(8, 1, 3);
                    OLED_Dis8x16CharNum(12, 1, 4);
                    OLED_Dis8x16CharNum(0, 2, gpioinputvalue & 0x01);
                    OLED_Dis8x16CharNum(4, 2, (gpioinputvalue & 0x02) >> 1);
                    OLED_Dis8x16CharNum(8, 2, (gpioinputvalue & 0x04) >> 2);
                    OLED_Dis8x16CharNum(12, 2, (gpioinputvalue & 0x08) >> 3);
                    
                break;
                
            case 3:                                                     // 显示输出GPIO值
                    i++;
                    if (i == 1)
                    {
                        Wp_ClearOled();                                 // 清屏
                    }
                    if (i > 100)
                    {
                        i = 2;
                    }
                    j = 0;
                    k = 0;
                    h = 0;
                    
                    printf("  Output Value\n");		                    // 用printf显示一串字符
                //  OLED_P8x16Str(2, 0, "Output Value"); 
                    OLED_Dis6x8CharNum(0, 2, 1);
                    OLED_Dis6x8CharNum(5, 2, 2);
                    OLED_Dis6x8CharNum(11, 2, 3);
                    OLED_Dis6x8CharNum(16, 2, 4);
                    OLED_Dis6x8CharNum(0, 3, 5);
                    OLED_Dis6x8CharNum(5, 3, 6);
                    OLED_Dis6x8CharNum(11, 3, 7);
                    OLED_Dis6x8CharNum(16, 3, 8);
                    
                    OLED_Dis8x16CharNum(0, 2, gpiooutputvalue & 0x01);
                    OLED_Dis8x16CharNum(4, 2, (gpiooutputvalue & 0x02) >> 1);
                    OLED_Dis8x16CharNum(8, 2, (gpiooutputvalue & 0x04) >> 2);
                    OLED_Dis8x16CharNum(12, 2, (gpiooutputvalue & 0x08) >> 3);
                    OLED_Dis8x16CharNum(0, 3, (gpiooutputvalue & 0x10) >> 4);
                    OLED_Dis8x16CharNum(4, 3, (gpiooutputvalue & 0x20) >> 5);
                    OLED_Dis8x16CharNum(8, 3, (gpiooutputvalue & 0x40) >> 6);
                    OLED_Dis8x16CharNum(12, 3, (gpiooutputvalue & 0x80) >> 7);
                    
                break;
                    
            case 4:                                                     // 显示各模拟通道电压值
                    h++;
                    if (h == 1)
                    {
                        Wp_ClearOled();                                 // 清屏
                    }
                    if (h > 100)
                    {
                        h = 2;           
                    }
                    j = 0;
                    k = 0;
                    i = 0;
                    
                    Wp_DisfloatIntegerandDecimal(0, 0, powervalue, 2, 1);               // 电源电压
                    Wp_DisfloatIntegerandDecimal(4, 0, analogvalue[0], 1, 1);           // 模拟1~15通道电压
                    Wp_DisfloatIntegerandDecimal(8, 0, analogvalue[1], 1, 1);
                    Wp_DisfloatIntegerandDecimal(12, 0, analogvalue[2], 1, 1);
                    
                    Wp_DisfloatIntegerandDecimal(0, 1, analogvalue[3], 1, 1);
                    Wp_DisfloatIntegerandDecimal(4, 1, analogvalue[4], 1, 1);
                    Wp_DisfloatIntegerandDecimal(8, 1, analogvalue[5], 1, 1);
                    Wp_DisfloatIntegerandDecimal(12, 1, analogvalue[6], 1, 1);
                    
                    Wp_DisfloatIntegerandDecimal(0, 2, analogvalue[7], 1, 1);
                    Wp_DisfloatIntegerandDecimal(4, 2, analogvalue[8], 1, 1);
                    Wp_DisfloatIntegerandDecimal(8, 2, analogvalue[9], 1, 1);
                    Wp_DisfloatIntegerandDecimal(12, 2, analogvalue[10], 1, 1);
                    
                    Wp_DisfloatIntegerandDecimal(0, 3, analogvalue[11], 1, 1);
                    Wp_DisfloatIntegerandDecimal(4, 3, analogvalue[12], 1, 1);
                    Wp_DisfloatIntegerandDecimal(8, 3, analogvalue[13], 1, 1);
                    Wp_DisfloatIntegerandDecimal(12, 3, analogvalue[14], 1, 1);
                    
                break;
                    
            case 5:
                    Wp_DisIntNum(0, 2, infrareddistance[0], 3);
                    Wp_DisIntNum(4, 2, infrareddistance[1], 3);
                    Wp_DisIntNum(8, 2, infrareddistance[2], 3);
                    Wp_DisIntNum(12, 2, infrareddistance[3], 3);
                    Wp_DisIntNum(0, 3, infrareddistance[4], 3);
                    Wp_DisIntNum(4, 3, infrareddistance[5], 3);
                    Wp_DisIntNum(8, 3, infrareddistance[6], 3);
                    Wp_DisIntNum(12, 3, infrareddistance[7], 3);
                    
                    printf("InfraredDistancs\n");
                    OLED_P8x16Str(4, 1, "Unit:mm");
                    
                break;
                    
            case 6:
                    Wp_DisIntNum(1, 2, luxvalue[0], 4);
                    Wp_DisIntNum(6, 2, luxvalue[1], 4);
                    Wp_DisIntNum(11, 2, luxvalue[2], 4);
                    Wp_DisIntNum(1, 3, luxvalue[3], 4);
                    Wp_DisIntNum(6, 3, luxvalue[4], 4);
                    Wp_DisIntNum(11, 3, luxvalue[5], 4);
                    
                    printf("  GrayscaleLux\n");
                    OLED_P8x16Str(2, 1, "Unit:10mLux");
                    
                break;
                   
						case 7:                                                     // ???????
										j++;
                    if (j == 1)
                    {
                        Wp_ClearOled();                                 // ??
                    }
                    if (j == 2)
                    {
                        j = 1;
                    }
                    k = 0;
                    h = 0;
                    i = 0;
                   
                    
//                  Wp_DisfloatIntegerandDecimal(0, 0, powervalue, 2, 1);               // ????
//                  Wp_DisfloatIntegerandDecimal(4, 0, analogvalue[0], 1, 1);           // ??1~15????
//                  Wp_DisfloatIntegerandDecimal(8, 0, analogvalue[1], 1, 1);
//                  Wp_DisfloatIntegerandDecimal(12, 0, analogvalue[2], 1, 1);
//                    
//                  Wp_DisfloatIntegerandDecimal(0, 1, analogvalue[3], 1, 1);
//                  Wp_DisfloatIntegerandDecimal(4, 1, analogvalue[4], 1, 1);
//                  Wp_DisfloatIntegerandDecimal(8, 1, analogvalue[5], 1, 1);
//                  Wp_DisfloatIntegerandDecimal(12, 1, analogvalue[6], 1, 1);
//                    
//                  Wp_DisfloatIntegerandDecimal(0, 2, analogvalue[7], 1, 1);
//                  Wp_DisfloatIntegerandDecimal(4, 2, analogvalue[8], 1, 1);
//                  Wp_DisfloatIntegerandDecimal(8, 2, analogvalue[9], 1, 1);
										
                    
										//Wp_DisfloatIntegerandDecimal(0, 0, analogvalue[10], 1, 4);            
										//Wp_DisfloatIntegerandDecimal(0, 1, analogvalue[11], 1, 4);
										//Wp_DisfloatIntegerandDecimal(0, 2, analogvalue[12], 1, 4);
										//Wp_DisfloatIntegerandDecimal(0, 3, analogvalue[13], 1, 4);
										
										Wp_DisfloatIntegerandDecimal(7, 0, distance, 5, 1);
                    //Wp_DisfloatIntegerandDecimal(7, 0, location_x, 5, 1);
										//Wp_DisfloatIntegerandDecimal(7, 1, location_y, 5, 1);
										//Wp_DisfloatIntegerandDecimal(7, 2, angle, 5, 1);
										//Wp_DisfloatIntegerandDecimal(7, 3, speed, 5, 1);
                break;
										
            default:
                break;
        }
        
		Wp_DelayMs(10);                                                 // 延时函数
	}
}


/*************************************************************************************************************
** 函数名称:			Wp_Sev_TimerPro
**
** 函数描述:			50ms伺服中断函数;
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
void Wp_Sev_TimerPro(void)
{
		static int leftturnstate = 0;									// 用于灭火程序，标记车是否在左转或右转状态，1代表在该状态
		static int rightturnstate = 0;
		static int normalstate = 1;										// 用于灭火程序，标记车是否在检测到异常状态，0代表在异常状态
		static int leftreassure = 0;										// 用于灭火程序，记录是否在左边/右边确认火源阶段，1代表在该状态
		static int rightreassure = 0;
		static int leftonwork = 0;											// 用于灭火程序，记录是否在左边/右边工作状态，1代表在该状态
		static int rightonwork = 0;
		static int backtonormal = 0;										// 用于灭火程序，记录是否在工作完回到normal的状态中，1代表在该状态
		static int preinfrareddistance[4] = {0};					// 记录前一状态的红外距离，用在目标追踪里，在遇到墙等极端情况停下时可以判断移动物体的方位	
		static int counttime = 0;											// 服务于目标追踪功能，用于记录时间，从而实现定时
		static int preState = 0;												// 轨道循迹时使用，用来记录前一时刻轨道信息，preState = 0代表左边有轨道
		static double dx = 0;														// 用于导航程序，记录与目标之间x，y方向的距离
		static double dy = 0;
		static double dtheta = 0;												// 用于导航程序，记录车头与目标方向的角度差，和为此转动的时间差
		static double dtime = 0;
		static double destx = 0;												// 用于导航程序，记录目标的坐标
		static double desty = 0;
		static int navistate = 0;												// 用于导航程序，记录工作状态，总共3状态，状态0代表寻找方向，状态1代表往目标走，状态2-6代表5种避障状态
		static int cruisestate = 0;											// 用于建图程序，记录工作状态，0代表向右，1代表向左，2代表向右部分的避障，3代表向左部分的避障
		static int leftforwardstate = 0;												// 用于灭火程序，用于记录是否在左边开始灭火状态，1代表在该状态
		static int rightforwardstate = 0;												// 用于灭火程序，用于记录是否在右边开始灭火阶段，1代表在该状态
		static int leftbackstate = 0;												// 用于灭火程序，用于记录是否在左边回调状态，1代表在该状态
		static int rightbackstate = 0;												// 用于灭火程序，用于记录是否在右边回调状态，1代表在该状态
		static int firedis = 0;														// // 用于灭火程序，用于记录火源距离对应的行走时间

	static u8 i = 0;                    // LED1闪烁
    static u16 j = 0;                   // LED2闪烁
    static u8 k = 0;                    // 刷新按键使用
	static u8 h = 0;                    // 读取姿态信息使用
    static u8 n = 0;
//  static u16 m = 0;
    
    //static u8 runflag = 0;              // 运行标志
    
    static u8 floatleddismode = 0;      // 流水灯显示模式
    u8 result = 0;
//  static u8 receiveresult = 0;        // 成功解析一帧上位机协议标志，在发送完执行指令后清零
    
    u16 temph = 0;                      // 临时转换变量
    u16 templ = 0;
    
    long firstspeedtemp = 0;            // 四个电机模块的速度缓存
    long secondspeedtemp = 0;
    long thirdspeedtemp = 0;
    long fourthspeedtemp = 0;
		static long operation_speed = gospeed;  //手动操作时的速度，默认为gospeed
		static u8 direction_command = 0x00;         //手动操作时的方向，默认前进
    
    u8 firstsendok = 0;                 // 成功发送标志
    u8 secondsendok = 0;    
    u8 thirdsendok = 0;    
    u8 fourthsendok = 0;

    static u16 runtimes = 0;            // 运行时间计数器，调试DEMO使用
		static int ReceivingData = 0;       // 蓝牙接收收据标志位，为1时只接收数据，不进行操作
		static u8 DataFromBle[10] = {0};    // 从蓝牙接收的数据,最多10个数据
 		static int DataCount = 0;             // 蓝牙数据个数
		
		static int AlarmFlag = 0;             //报警标志位
		static int ModeFlag = 0;            //0:手动或导航，1:跟踪标志位,2:红外避障标志位,3:灭火标志位
		
		static int SendPositionCount = 0;    //计数，用于回传坐标，循环20次刷新一次，即1s
		//u8 SendStr[3] = {0};                 // 用于回传手机通信
		
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		if(UART2_data >= 0x00 && UART2_data <= 0x06 && ReceivingData == 0)//设置手动操作的方向
		{
		  direction_command = UART2_data;
			UART2_data = 0xff; 
			ModeFlag = 0;                                //跳出其他功能模式
		}
		
		if(UART2_data == 0x07 && operation_speed < 2400 && ReceivingData == 0)//加速
		{
			operation_speed = operation_speed + 100;
			Wp_Usart2_SendChar(0xff);
			Wp_Usart2_SendChar(operation_speed / 100 *16 + (operation_speed /10) % 10 );

			UART2_data = 0xff;                            //0xff为闲置态
			ModeFlag = 0;
		}
		
		if(UART2_data == 0x08 && operation_speed > 80 && ReceivingData == 0)//减速
		{
			operation_speed = operation_speed - 100;

			Wp_Usart2_SendChar(0xff);
			Wp_Usart2_SendChar(operation_speed / 100 *16 + (operation_speed /10) % 10 );

			UART2_data = 0xff;
			ModeFlag = 0;
		}
    
		if(UART2_data == 0x09 && ReceivingData == 0)//红外避障
		{
			
			UART2_data = 0xff;
			ModeFlag = 2;
		}
		
		if(UART2_data == 0x10 && ReceivingData == 0)//巡线灭火
		{
			
			UART2_data = 0xff;
			ModeFlag = 3;
		}
		
		if(UART2_data == 0x11 && ReceivingData == 0)//跟踪
		{
			
			UART2_data = 0xff;
			ModeFlag = 1;
		}
		if(UART2_data == 0x12 && ReceivingData == 0)//开始喷水,使用倒数第二个outport
		{
			Wp_SetPortOutputValue(7,1);
			UART2_data = 0xff;
			ModeFlag = 0;
		}
		if(UART2_data == 0x13 && ReceivingData == 0)//结束喷水
		{
			Wp_SetPortOutputValue(7,0);
			UART2_data = 0xff;
			ModeFlag = 0;
		}
		
		if(UART2_data == 0xfe)                          //0xfe时进入接收数据状态，数据范围为0x00-0xfa
		{
			ReceivingData = 1;
			DataCount = 0;
			DataFromBle[0] = '\0';
			Wp_Usart2_SendChar(0xfe);
			UART2_data = 0xff;
			ModeFlag = 0;
		}
		else if(UART2_data == 0xfd)                          //0xfd时结束接收
		{
			ReceivingData = 0;
			DataFromBle[DataCount ++] = '\0';                       // 结尾符
			Wp_Usart2_SendStr((char*)DataFromBle);               //回显字符串
			UART2_data = 0xff;
		}
		else if(ReceivingData == 1 && UART2_data != 0xff)         //0xff防止不断赋值
		{
			DataFromBle[DataCount ++] = UART2_data;                 //接收蓝牙数据
			UART2_data = 0xff;
		}
		
		
		if (++i >= 10)										        // 板载LED频闪
		{
			i = 0;
            
            LED2_TOGGLE;
            
        //  Wp_FlowLights(floatleddismode);                         // 流水灯函数
		}
        if (++j >= 2)                                               // 接口面板LED频闪
        {
            j = 0;
            
            LED1_TOGGLE;
        }
        
        if (++k >= 1)                                               // 检测按键是否按下
        {
            k = 0;
            
            /*  刷新按键状态，用户切换屏幕使用      */
            Wp_KeyRefreshState(&key_up);                            // 刷新按键状态
            if (Wp_KeyAccessTimes(&key_up, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_up, KEY_ACCESS_REFRESH);             
							
							  Wp_Usart2_SendStr("CC");								//测试发送字符串
                
							  keyvalue++;                                         // 切换屏幕状态
                if (keyvalue >= 8)
                {
                    keyvalue = 1;
                }
            }
            /*  刷新按键状态，用户切换屏幕使用      */
            Wp_KeyRefreshState(&key_down);                          // 刷新按键状态
            if (Wp_KeyAccessTimes(&key_down, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_down, KEY_ACCESS_REFRESH);
                
							Wp_Usart2_SendChar(0x55);								//测试发送Char
                keyvalue--;                                         // 切换屏幕状态
                if (keyvalue <= 0)
                {
                    keyvalue = 7;
                }
            }
            /*  刷新按键状态，用户切换屏幕使用      */
            Wp_KeyRefreshState(&key_back);                          // 刷新按键状态
            if (Wp_KeyAccessTimes(&key_back, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_back, KEY_ACCESS_REFRESH);
                
                keyvalue = 1;                                       // 切换屏幕状态
                
                runflag = 0;                                        // 按下BACK按键运动结束
                runtimes = 0;                                       // 清时间计数器
            }
            /*  刷新按键状态，用户切换屏幕使用      */
            Wp_KeyRefreshState(&key_ok);                            // 刷新按键状态
            if (Wp_KeyAccessTimes(&key_ok, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_ok, KEY_ACCESS_REFRESH);
                
            //  keyvalue = 1;                                       // 切换屏幕状态
                
                floatleddismode++;                                  // 流水灯模式切换
                if (floatleddismode >= 3)
                    floatleddismode = 0;
                
                runflag = 1;                                        // 按下OK按键运动开始
            }
        }
        
				//刷新坐标
				GetLocation();
				
				//温度过高报警，用最后一个ADC
				if(analogvalue[14] > 0.40 && AlarmFlag == 0)      //阈值40摄氏度
				{
					Wp_Usart2_SendChar(0x01);     //0x01为报警
					AlarmFlag = 1;
				}
				
				if(analogvalue[14] < 0.35 && AlarmFlag == 1)      //阈值35摄氏度
				{
					Wp_Usart2_SendChar(0x02);     //0x02为解除报警
					AlarmFlag = 0;
				}
				
        /*
        // 测试使用，按键按下前进，后退，左转，右转
        if (key_up())                   // 前进
        {
            firstspeedtemp = -3000;
            secondspeedtemp = 3000;
            thirdspeedtemp = 3000;
            fourthspeedtemp = -3000;
        }
        else if (key_down())            // 后退
        {
            firstspeedtemp = 3000;
            secondspeedtemp = -3000;
            thirdspeedtemp = -3000;
            fourthspeedtemp = 3000;            
        }
        else if (key_back())            // 左转
        {
            firstspeedtemp = 2000;
            secondspeedtemp = 2000;
            thirdspeedtemp = 2000;
            fourthspeedtemp = 2000;                
        }
        else if (key_ok())              // 右转
        {
            firstspeedtemp = -2000;
            secondspeedtemp = -2000;
            thirdspeedtemp = -2000;
            fourthspeedtemp = -2000;          
        }
        */
				
				
				// 测试使用，蓝牙控制
				if (runflag)
        {				
            if (direction_command == 0x01)
            {
                speed = operation_speed;
								direction = 1;
							  
            }
            else if(direction_command == 0x02)
            {
                speed = operation_speed;         
							  direction = 2;
            }
            else if(direction_command == 0x03)
            {
                speed = operation_speed;
							  direction = 3;
            }
            else if(direction_command == 0x04)
            {
                speed = operation_speed;
							  direction = 4;
            }
						else if(direction_command == 0x00)
            {
                speed = operation_speed;
							  direction = 0;
            }
						else if(direction_command == 0x05)
            {
                speed = operation_speed - 40;    //旋转的默认速度为turnspeed，即gospeed-40
							  direction = 5;
            }
						else if(direction_command == 0x06)
            {
                speed = operation_speed - 40;
								direction = 6;
            }
				}
				
				
				//{0xfc,0x10,0x10}
				//if (UART2_DATA == 0xff)				代码之后的思路
						
				//if (DataFromBle[0] == 0xfc)
				//DataFromBle[1] = 0x15;
				//DataFromBle[2] = 0x10;
				if (!runflag)													// 停止运动后回到状态0
				{
						navistate = 0;
				}
				if (DataFromBle[0] == 0xfc)
				{
						if (runflag)
						{
							  //回传坐标，1s1次
								if(SendPositionCount == 20)
								{
									
									Wp_Usart2_SendChar(0xfe);
									Wp_Usart2_SendChar(((int)location_x) / 10 * 16 + ((int)location_x)  % 10 );
									Wp_Usart2_SendChar(((int)location_y) / 10 * 16 + ((int)location_y)  % 10 );
									
									SendPositionCount = 0;
								}
							  SendPositionCount ++;
							
								destx = (int)DataFromBle[1]%16 + (int)DataFromBle[1]/16*10;						// 将收到的蓝牙目标地址信息转换为double类型，用到BCD码的转换
								desty = (int)DataFromBle[2]%16 + (int)DataFromBle[2]/16*10;
								dx = destx - location_x;																		// 计算小车与目标位置的差值
								dy = desty - location_y;
								if (navistate == 0)
								{
										if (dx == 0 && dy == 0)																				// 如果没有差值
										{
												dtheta = 0;
												DataFromBle[0] = 0xfb;																	// 角度差为0，第一位给0xfb，意味着到达位置，退出导航
												direction = 0;
												Wp_Usart2_SendChar(0xfb);																// 调试用，给上位机发一个到达的信息
										}
										else if (dx == 0)																					// dx = 0的情况
										{
												if (dy > 0)
												{
													dtheta = angle - 90;
												}
												else if (dy < 0)
												{
													dtheta = angle - 270;
												}
										}
										else if (dx > 0 && dy >= 0)												// 第一象限如果dx,dy大于零，atan计算出的就是目标方位，角度差就是angle-atan(dy/dx)
										{
												dtheta = angle - atan(dy/dx)*180/PI;
										}
										else if (dx < 0)																	// 第二三象限，atan计算值加180才是真正的目标方位
										{
												dtheta = angle - atan(dy/dx)*180/PI - 180;
										}
										else if (dx > 0 && dy < 0)													// 第四象限，atan需要加360才是真正的目标方位
										{
												dtheta = angle - atan(dy/dx)*180/PI - 360; 			
										}
										if (dtheta > 1 || dtheta < -1)																	// 如果有角度差，就旋转，左旋还是右旋看差值正负（只是一个小优化）
										{
												if (dtheta >= 180 || (dtheta <= 0 && dtheta > -180))					// dtheta在180~360以及-180~0度时，左转能更快找到目标方向	
												{
														direction = 5;
														speed = turnspeed;
												}
												else																// 其他情况，右转更快
												{
														direction = 6;
														speed = turnspeed;
												}
										}
										else
										{
												direction = 0;
												navistate = 1;
										}
								}
								else if (navistate == 1)									// 前进状态
								{
										direction = 1;
										speed = gospeed;
										if (dx <= 4 && dx >= -4 && dy <= 4 && dy >= -4)										// 到达目标位置内的一个范围
										{	
												DataFromBle[0] = 0xfb;																				// 该导航寄存器的值，退出导航
												direction = 0;
												Wp_Usart2_SendChar(0xfb);
												navistate = 0;
										}
										if (!(infrareddistance[1] >= 200 && infrareddistance[2] >= 200 			// 如果遇到障碍物，开始执行避障过程
											&& infrareddistance[0] >= 200 && infrareddistance[3] >= 200))
										{
												direction = 0;
												Wp_Usart2_SendChar(0xf9);
												//Wp_Usart2_SendChar(0xfa);
												//Wp_Usart2_SendChar(((int)location_x) / 10 * 16 + ((int)location_x)  % 10 );
												//Wp_Usart2_SendChar(((int)location_y) / 10 * 16 + ((int)location_y)  % 10 );
											
												if (infrareddistance[0] < 200 && infrareddistance[1] >= 200 &&				// 多种避障状态，障碍物在左边
													infrareddistance[2] >= 200 && infrareddistance[3] >= 200)
														navistate = 2;
												else if (infrareddistance[3] < 200 && infrareddistance[1] >= 200 &&			// 右边
													infrareddistance[2] >= 200 && infrareddistance[0] >= 200)
														navistate = 3;
												else if (infrareddistance[0] < 200 && infrareddistance[1] < 200 &&			// 左前
													infrareddistance[2] >= 200 && infrareddistance[3] >= 200)
														navistate = 4;
												else if (infrareddistance[2] < 200 && infrareddistance[3] < 200 &&			// 右前	
													infrareddistance[1] >= 200 && infrareddistance[0] >= 200)
														navistate = 5;
												else																																	// 其余（主要是前方）
														navistate = 6;
												runtimes = 0;
										}
								}
								else if (navistate == 2)															// 避障状态2
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 25)													// 左侧，稍向右转，约50度
										{
												direction = 6;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 25 && runtimes <= 75)															// 前进，绕过障碍物
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes > 75)
										{
												navistate = 0;															// 完成后回到状态0
												runtimes = 0;
										}
								}
								else if (navistate == 3)															// 避障状态3
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 25)													// 右侧，稍向左转，约50度
										{
												direction = 5;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 25 && runtimes <= 75)															// 前进，绕过障碍物
										{
												direction = 1;
												speed = gospeed;
										}
										if (runtimes > 75)															
										{
												navistate = 0;															// 完成后回到状态0
												runtimes = 0;
										}
								}
								else if (navistate == 4)															// 避障状态4
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 35)													// 左前，稍向右转，约70度
										{
												direction = 6;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 35 && runtimes <= 85)															// 前进，绕过障碍物
										{
												direction = 1;
												speed = gospeed;
										}
										if (runtimes > 85)														
										{
												navistate = 0;															// 完成后回到状态0
												runtimes = 0;
										}
								}
								else if (navistate == 5)															// 避障状态5
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 35)												// 右前，稍向左转，约70度
										{
												direction = 5;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 35 && runtimes <= 85)															// 前进，绕过障碍物
										{
												direction = 1;
												speed = gospeed;
										}
										if (runtimes > 85)															
										{
												navistate = 0;															// 完成后回到状态0
												runtimes = 0;
										}
								}
								else if (navistate == 6)
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 45)												// 前方，向左转90度
										{
												direction = 5;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 45 && runtimes <= 95)															// 前进，绕过障碍物
										{
												direction = 1;
												speed = gospeed;
										}
										if (runtimes > 95)														
										{
												navistate = 0;															// 完成后回到状态0
												runtimes = 0;
										}
								}
						}	
				}				
					
				
				// 建图程序
				if (!runflag)													// 停止运动后回到状态0
				{
						cruisestate = 0;
				}
				if (DataFromBle[0] == 0xec &&  runflag == 1)
				{
					 //回传坐标，1s1次
								if(SendPositionCount == 20)
								{
									
									Wp_Usart2_SendChar(0xfe);
									Wp_Usart2_SendChar(((int)location_x) / 10 * 16 + ((int)location_x)  % 10 );
									Wp_Usart2_SendChar(((int)location_y) / 10 * 16 + ((int)location_y)  % 10 );
									
									SendPositionCount = 0;
								}
							  SendPositionCount ++;
								
								destx = (int)DataFromBle[1]%16 + (int)DataFromBle[1]/16*10;						// 将收到的蓝牙目标地址信息转换为double类型，用到BCD码的转换
								desty = (int)DataFromBle[2]%16 + (int)DataFromBle[2]/16*10;
			
						if (location_y <= desty)													// y边界值，自己定（接口）
						{
								if (cruisestate == 0)  															// x轴正方向行走
								{
										if (location_x <= destx)
										{
												if (infrareddistance[0] >= 200 && infrareddistance[1] >= 200 
													&& infrareddistance[4] >= 200 && infrareddistance[5] >= 200)						// 遇到障碍物，进入躲避状态
												{
														direction = 1;
														speed = gospeed;
												}
												else 
												{
														// 遇到障碍，写接口，红色
														Wp_Usart2_SendChar(0xf9);
														cruisestate = 2;
														runtimes = 0;
												}
										}
										else																						// 到达坐标极限，进入掉头状态
										{
												cruisestate = 4;
												runtimes = 0;
										}
								}
								else if (cruisestate == 1)													// x轴负方向行走	
								{
										if (location_x >= 0)
										{
												if (infrareddistance[0] >= 200 && infrareddistance[1] >= 200 
													&& infrareddistance[4] >= 200 && infrareddistance[5] >= 200)						// 遇到障碍物，进入躲避状态
												{
														direction = 1;
														speed = gospeed;
												}
												else 
												{
														// 遇到障碍，写接口，红色
														Wp_Usart2_SendChar(0xf9);
														cruisestate = 3;
														runtimes = 0;
												}
										}
										else																								// 到达坐标极限，进入掉头状态
										{
												cruisestate = 5;
												runtimes = 0;
										}
								}
								else if (cruisestate == 2)										// 正方向行走躲避程序
								{
										runtimes++;
										if (runtimes >= 0 && runtimes < 45)											// 左转
										{
												direction = 5;
												speed = turnspeed;
												if (runtimes == 25)
												{
														// 发消息，变回黑色
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes >= 45 && runtimes < 95)									// 前进
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 95 && runtimes < 140)						// 右转
										{
												direction = 6;
												speed = turnspeed;
										}
										else if (runtimes >= 140 && runtimes < 190)								// 前进
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 190 && runtimes < 235)													// 右转
										{
												direction = 6;
												speed = turnspeed;
										}
										else if (runtimes >= 235 && runtimes < 285)								// 前进
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 285 && runtimes < 330)								// 左转
										{
												direction = 5;
												speed = turnspeed;
										}
										else if (runtimes > 330)												// 回到x正方向行走状态
										{
												runtimes = 0;
												cruisestate = 0;
										}
								}
								else if (cruisestate == 3)											// 与状态2完全相反
								{
										runtimes++;
										if (runtimes >= 0 && runtimes < 45)									
										{
												direction = 6;
												speed = turnspeed;
												if (runtimes == 25)
												{
														// 发消息，变回黑色
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes >= 45 && runtimes < 95)									// 前进
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 95 && runtimes < 140)					
										{
												direction = 5;
												speed = turnspeed;
										}
										else if (runtimes >= 140 && runtimes < 190)								// 前进
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 190 && runtimes < 235)												
										{
												direction = 5;
												speed = turnspeed;
										}
										else if (runtimes >= 235 && runtimes < 285)								
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 285 && runtimes < 330)							
										{
												direction = 6;
												speed = turnspeed;
										}
										else if (runtimes > 330)												// 回到x正方向行走状态
										{
												runtimes = 0;
												cruisestate = 1;
										}
								}
								else if (cruisestate == 4)											// 正方向掉头状态
								{
										runtimes++;
										if (runtimes >= 0 && runtimes < 45)
										{
												direction = 5;
												speed = turnspeed;
										}
										else if (runtimes >= 45 && runtimes < 145)
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 145 && runtimes < 190)
										{
												direction = 5;
												speed = turnspeed;
										}
										else if (runtimes > 190)
										{
												runtimes = 0;
												cruisestate = 1;
										}
								}
								else if (cruisestate == 5)																			// 负方向掉头状态
								{
										runtimes++;
										if (runtimes >= 0 && runtimes < 45)
										{
												direction = 6;
												speed = turnspeed;
										}
										else if (runtimes >= 45 && runtimes < 145)
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 145 && runtimes < 190)
										{
												direction = 6;
												speed = turnspeed;
										}
										else if (runtimes > 190)
										{
												runtimes = 0;
												cruisestate = 0;
										}
								}
						}
				}	
				
				
				/*
				// 测试使用，转90度，缓慢前进固定距离
				if (runflag)
				{
						runtimes++;
						if (runtimes > 0 && runtimes < 50)
						{
								firstspeedtemp = 500;							 // 左转90度
								secondspeedtemp = 500;
								thirdspeedtemp = 500;
								fourthspeedtemp = 500; 
						}
						if (runtimes >= 50 && runtimes < 100)
						{
								firstspeedtemp = -500;							 // 右转90度
								secondspeedtemp = -500;
								thirdspeedtemp = -500;
								fourthspeedtemp = -500; 
						}
						if (runtimes >= 100 && runtimes < 150)
						{
								firstspeedtemp = -200;							 // 前进
								secondspeedtemp = 200;
								thirdspeedtemp = 200;
								fourthspeedtemp = -200; 
						}
						if (runtimes >= 150 && runtimes < 200)
						{
								firstspeedtemp = 150;							 // 前进
								secondspeedtemp = -150;
								thirdspeedtemp = -150;
								fourthspeedtemp = 150; 
						}
						if (runtimes >= 200)
						{
								runtimes = 0;
						}
				}
				*/
				
					// 灭火程序。前进，寻找高温，确认找到后转向，执行，转回
				if (runflag == 1 && ModeFlag == 3)
				//if (runflag)
        {
						if (normalstate == 1)
						{
								if (analogvalue[10] > 1.5 && analogvalue[11] > 1.5)			// 侧方两个探头都没有探到火焰，则前进（之后会改成循迹）
								{
										runtimes = 0;														// 时间清零 
										//direction = 1;
										//speed = 200;
										
										if (luxvalue[1] <= 500 && luxvalue[2] <= 500)
										{
												direction = 1;							// 前进
												speed = 200;
												if (luxvalue[0] <= 500 && luxvalue[3] >= 450)		//标记急转弯前一时刻状态，a = 0代表左边有道轨道
												{
														preState = 0;
												}
												if (luxvalue[0] >= 500 && luxvalue[2] <= 500)
												{
														preState = 1;
												}
										}
										else        // 脱离轨道
										{
												direction = 0;
											
												if (luxvalue[1] <= 450 && luxvalue[2] >= 500) 		//向右微偏出，需要向左微调
												{
														direction = 5;
														speed = 200;
												}
												else if (luxvalue[2] <= 450 && luxvalue[1] >= 500) 		//向左微偏出，需要向右微调
												{
														direction = 6;
														speed = 200;
												}
												else if (luxvalue[0] <= 450) 		//向右偏出，需要向左调
												{
														direction = 5;         // 原地旋转
														speed = 250;
												}
												else if (luxvalue[3] <= 450) 		//向左偏出，需要向右调
												{
														direction = 6;        // 原地旋转
														speed = 250;
												}
												//出现无法探测到轨道的情况，需要利用前一时刻的信息，进行旋转
												else if (preState == 0)								//左边有轨道，向左旋转
												{
														direction = 5;         // 原地旋转
														speed = 250;
												}
												else 							//右边有轨道，向右旋转
												{
														direction = 6;        // 原地旋转
														speed = 250;
												}
										}

								}
						
								else if (analogvalue[10] <= 1.5)
								{
										normalstate = 0;
										leftonwork = 1;											// 进入左边工作状态
										leftforwardstate = 1;									// 开始完成左转
										runtimes = 0;
									  Wp_Usart2_SendChar(0x03);
								}
								else if (analogvalue[11] <= 1.5)
								{
										normalstate = 0;
										rightonwork = 1;										// 进入右边工作状态
										rightforwardstate = 1;									// 开始完成右转
										runtimes = 0;
										Wp_Usart2_SendChar(0x03);
								}
						}
						else if (leftonwork == 1 || rightonwork == 1)				// 左边/右边工作状态
						{
								if (leftforwardstate == 0 && rightforwardstate == 0)		// 是否完成左转/右转？完成后进入下面部分
								{		
										runtimes++;
										if (runtimes > 0 && runtimes <= 3)						// 调整工作时间
										{
												// 驱动执行机构
												Wp_SetPortOutputValue(7,1);
										}
										else if (runtimes > 3 && runtimes <= 30)
										{
										}
										else if (runtimes > 30 && runtimes <= 50)
										{
												direction = 2;
												speed = 200;
										}
										else if (runtimes > 50 && runtimes <= 60)
										{
												direction = 1;
												speed = 200;
										}
										else if (runtimes > 60 && runtimes <= 70)
										{
												direction = 5;
												speed = 200;
										}
										else if (runtimes > 70 && runtimes <= 90)
										{
												direction = 6;
												speed = 200;
										}
										else if (runtimes > 90 && runtimes <= 100)
										{
												direction = 5;
												speed = 200;
										}
										else if (runtimes > 100 && runtimes <= 110)
										{
												direction = 1;
												speed = 200;
												Wp_SetPortOutputValue(7,0);
										}
										else if (runtimes > 110)
										{
												direction = 0;
										}
										if (runtimes > 130)														// 确认传感器的值低于阈值,进行相应左右转，并回到正常状态
										{
												if (analogvalue[12] > 3)				// 一段时间后检测确认传感器的值是否高于阈值
												{
														if (leftonwork == 1)						// 在左边工作
														{
																leftonwork = 0;
																leftbackstate = 1;					// 触发后退及右转
														}
														else if (rightonwork == 1)			// 在右边工作
														{
																rightonwork = 0;
																rightbackstate = 1;					// 触发后退及左转
														}
														runtimes = 0;
												}
												else															// 灭火没有成功，重新灭火
												{
														runtimes = 0;
												}
										}		
								}
						}
						
						if (leftforwardstate == 1)										// 左边开始灭火状态
						{
								runtimes ++;
								if (runtimes <= 50)											// 在既定时间内以既定速度左转，左转了既定角度
								{
										direction = 5;							 // 左转
										speed = 390;
								}
								else if (!(distance > 5 && distance < 10))
								{
										direction = 1;
										speed = 250;
								}
								else
								{
										firedis = runtimes;
										leftforwardstate = 0;
										direction = 0;
										runtimes = 0;
								}
						}
						else if (rightforwardstate == 1)									// 右转状态
						{
								runtimes ++;
								if (runtimes <= 50)												// 在既定时间内以既定速度右转，右转了既定角度
								{
										direction = 6;						 // 右转
										speed = 390;
								}
								/*else if (runtimes == 50)
								{
										firedis = 2* (distance - 10);					// 计算为了接近目标而需要走的时间，截距待调
								}
								else if (runtimes > 50 && runtimes < firedis + 50)
								{
										direction = 1;
										speed = 290;
								}
								*/
								else if (!(distance > 5 && distance < 10))
								{
										direction = 1;
										speed = 250;
								}
								//else if (runtimes > firedis + 50)
								else
								{
										firedis = runtimes;
										rightforwardstate = 0;
										direction = 0;
										runtimes = 0;
								}
						}			
						if (leftbackstate == 1)																	// 左边回归状态
						{
								runtimes++;
								if (runtimes >= 0 && runtimes <= firedis - 50)
								{
										direction = 2;
										speed = 290;
								}
								else if (runtimes <= firedis)
								{
										direction = 6;
										speed = 390;
								}
								else if (runtimes > firedis)
								{
										runtimes = 0;
										leftbackstate = 0;
										normalstate = 1;
								}
						}
						else if (rightbackstate == 1)																	// 右边回归状态
						{
								runtimes++;
								if (runtimes >= 0 && runtimes <= firedis - 50)
								{
										direction = 2;
										speed = 290;
								}
								else if (runtimes <= firedis)
								{
										direction = 5;
										speed = 390;
								}
								else if (runtimes > firedis)
								{
										runtimes = 0;
										rightbackstate = 0;
										normalstate = 1;
								}
						}
				}
				
				
				
				
				//测试使用，目标追踪，麦克纳姆轮
				if (ModeFlag == 1 && runflag == 1)
        {
							if (infrareddistance[0] <= 200	||			// 目标较近
											infrareddistance[1] <= 200 || infrareddistance[2] <= 150
											|| infrareddistance[3] <= 150)		
							{
									direction = 0;
							     speed = 0;
//									firstspeedtemp = 0;											// 停止
//									secondspeedtemp = 0;
//									thirdspeedtemp = 0;
//									fourthspeedtemp = 0; 
									
	//								if (counttime < 50)
	//								{
	//										counttime++;
	//								}
	//								else
	//							{
	//									if (infrareddistance[0] > preinfrareddistance[0] + 50)				//物体在左方移动
	//										{
	//												firstspeedtemp = 800;							 // 左转
	//												secondspeedtemp = 800;
	//												thirdspeedtemp = 800;
	//												fourthspeedtemp = 800;  
	//										}
	//										else if (infrareddistance[3] > preinfrareddistance[3] + 50)				//物体在右方移动
	//										{
	//												firstspeedtemp = -800;							 // 右转
	//												secondspeedtemp = -800;
	//												thirdspeedtemp = -800;
	//												fourthspeedtemp = -800;  
	//										}
	//										preinfrareddistance[0] = infrareddistance[0];
	//										preinfrareddistance[1] = infrareddistance[1];
	//										preinfrareddistance[2] = infrareddistance[2];
	//										preinfrareddistance[3] = infrareddistance[3];
	//										counttime = 0;
	//								}
									
								}
							else
							{
									if (infrareddistance[1] >= 400 && infrareddistance[2] >= 400 				// 目标在前方较远
											&& infrareddistance[0] >= infrareddistance[1] 
											&& infrareddistance[3] >= infrareddistance[2]
											&& infrareddistance[2] >= infrareddistance[1] - 200 
											&& infrareddistance[1] >= infrareddistance[2] - 200)		// 两边更远
									{
//											firstspeedtemp = -2000;									// 较快前进
//											secondspeedtemp = 2000;
//											thirdspeedtemp = 2000;
//											fourthspeedtemp = -2000;
											direction = 1;
							        speed = 800;
									}
									else if (infrareddistance[1] >= 200 && infrareddistance[2] >= 200 				// 目标在前方较近
													&& infrareddistance[0] >= infrareddistance[1] 
											&& infrareddistance[3] >= infrareddistance[2]
											&& infrareddistance[2] >= infrareddistance[1] - 200 
											&& infrareddistance[1] >= infrareddistance[2] - 200)		// 两边更远
									{
//											firstspeedtemp = -800;									// 较慢前进
//											secondspeedtemp = 800;
//											thirdspeedtemp = 800;
//											fourthspeedtemp = -800;
											direction = 1;
											speed = 400;
									}
									else if (infrareddistance[0] < infrareddistance[1] 
													|| infrareddistance[1] < infrareddistance[2] - 200 
													|| infrareddistance[4] < infrareddistance[1] - 50)												// 目标在左边
									{
//											firstspeedtemp = 1000;							 // 左转
//											secondspeedtemp = 1000;
//											thirdspeedtemp = 1000;
//											fourthspeedtemp = 1000;  
											direction = 5;
											speed = 750;
									}
									else if (infrareddistance[3] < infrareddistance[2] 
													|| infrareddistance[2] < infrareddistance[1] - 200
													|| infrareddistance[5] < infrareddistance[2] - 50)												// 目标在右边
									{
//											firstspeedtemp = -1000;							 // 右转
//											secondspeedtemp = -1000;
//											thirdspeedtemp = -1000;
//											fourthspeedtemp = -1000;  
											direction = 6;
							        speed = 750;
									}			
							}
					if (distance > 70 && distance < 120)
					{
							direction = 1;
							speed = 800;
					}
					if (distance < 30)
					{
							direction = 0;
					}
			}
				
        
        // 避障测试程序，仅使用前4个红外测距传感器，适用于麦克纳姆轮和普通论
        if (runflag == 1 && ModeFlag == 2)
        {
            if (infrareddistance[1] >= 250 && infrareddistance[2] >= 250 
                && infrareddistance[0] >= 200 && infrareddistance[3] >= 200)
            {
								direction = 1;
							  speed = 600;
							  /*
                firstspeedtemp = -1000;                 // 前进
                secondspeedtemp = 1000;
                thirdspeedtemp = 1000;
                fourthspeedtemp = -1000;
							*/
            }
            else if (infrareddistance[1] <= 250)        // 2号红外传感器
            {
//                firstspeedtemp = 0;
//                secondspeedtemp = 0;
//                thirdspeedtemp = 0;
//                fourthspeedtemp = 0;
								direction = 0;
							  speed = 0;
                if (infrareddistance[2] >= 200)         // 右转
                {
//                    firstspeedtemp = -1000;
//                    secondspeedtemp = -1000;
//                    thirdspeedtemp = -1000;
//                    fourthspeedtemp = -1000;
										direction = 6;
							      speed = 600;
                }
								//firstspeedtemp = -1300;         // 原地旋转
                //secondspeedtemp = -700;
               //thirdspeedtemp = -1200;
                //fourthspeedtemp = 500;
//								firstspeedtemp = -1000;						// 右转
//                secondspeedtemp = -1000;
//                thirdspeedtemp = -1000;
//                fourthspeedtemp = -1000; 
								direction = 6;
							  speed = 600;
            }
            else if (infrareddistance[2] <= 250)        // 3号红外传感器
            {
//                firstspeedtemp = 0;
//                secondspeedtemp = 0;
//                thirdspeedtemp = 0;
//                fourthspeedtemp = 0;	
								direction = 0;
							  speed = 0;
                if (infrareddistance[1] >= 200)         // 左转
                {
//                    firstspeedtemp = 1000;
//                    secondspeedtemp = 1000;
//                    thirdspeedtemp = 1000;
//                    fourthspeedtemp = 1000;    
										direction = 5;
							      speed = 600;									
                }
								//firstspeedtemp = 700;         // 原地旋转
                //secondspeedtemp = 1300;
                //thirdspeedtemp = -500;
                //fourthspeedtemp = 1200;
//								firstspeedtemp = 1000;					// 左转
//                secondspeedtemp = 1000;
//                thirdspeedtemp = 1000;
//                fourthspeedtemp = 1000;
								   direction = 5;
							      speed = 600;
            }
            else if (infrareddistance[0] <= 250)        // 右转
            {
//                firstspeedtemp = -1000;
//                secondspeedtemp = -1000;
//                thirdspeedtemp = -1000;
//                fourthspeedtemp = -1000;
							      direction = 6;
							      speed = 600;
            }
            else if (infrareddistance[3] <= 250)        // 左转
            {
//                firstspeedtemp = 1000;
//                secondspeedtemp = 1000;
//                thirdspeedtemp = 1000;
//                fourthspeedtemp = 1000;
							      direction = 5;
							      speed = 600;
            }
        }
        
				
				/*
				 // 测试使用，循迹程序，仅使用中间4个灰度传感器，适用于麦克纳姆轮和普通轮
        if (runflag)
        {
            if (luxvalue[1] <= 500 && luxvalue[2] <= 500)
            {
                direction = 1;							// 前进
                speed = 500;
								if (luxvalue[0] <= 500 && luxvalue[3] >= 450)		//标记急转弯前一时刻状态，a = 0代表左边有道轨道
								{
										preState = 0;
								}
								if (luxvalue[0] >= 500 && luxvalue[2] <= 500)
								{
										preState = 1;
								}
            }
            else        // 脱离轨道
            {
                direction = 0;
							
								if (luxvalue[1] <= 450 && luxvalue[2] >= 500) 		//向右微偏出，需要向左微调
								{
										direction = 5;
										speed = 300;
								}
								else if (luxvalue[2] <= 450 && luxvalue[1] >= 500) 		//向左微偏出，需要向右微调
								{
										direction = 6;
										speed = 300;
								}
								else if (luxvalue[0] <= 450) 		//向右偏出，需要向左调
								{
										direction = 5;         // 原地旋转
										speed = 350;
								}
								else if (luxvalue[3] <= 450) 		//向左偏出，需要向右调
								{
										direction = 6;        // 原地旋转
										speed = 350;
								}
								//出现无法探测到轨道的情况，需要利用前一时刻的信息，进行旋转
								else if (preState == 0)								//左边有轨道，向左旋转
								{
										direction = 5;         // 原地旋转
										speed = 350;
								}
								else 							//右边有轨道，向右旋转
								{
										direction = 6;        // 原地旋转
										speed = 350;
								}
						}
				}
				*/
				
				/*
				//测试使用，模拟输入对于前进的控制
				if (runflag)
				{
						if (analogvalue[14] >= 3)
						{
								firstspeedtemp = -1000;                 // 前进
								secondspeedtemp = 1000;
								thirdspeedtemp = 1000;
								fourthspeedtemp = -1000;
						}
				}
				*/
				
				/*
				 // 循迹程序，仅使用中间4个灰度传感器，适用于麦克纳姆轮和普通轮
        if (runflag)
        {
            if (luxvalue[1] <= 250 && luxvalue[2] <= 250)
            {
                firstspeedtemp = -500;                 // 前进
                secondspeedtemp = 500;
                thirdspeedtemp = 500;
                fourthspeedtemp = -500;
								if (luxvalue[0] <= 250 && luxvalue[3] >= 200)		//标记急转弯前一时刻状态，a = 0代表左边有道轨道
								{
										preState = 0;
								}
								if (luxvalue[0] >= 200 && luxvalue[2] <= 250)
								{
										preState = 1;
								}
            }
            else        // 脱离轨道
            {
                firstspeedtemp = 0;
                secondspeedtemp = 0;
                thirdspeedtemp = 0;
                fourthspeedtemp = 0;
							
								if (luxvalue[1] <= 200 && luxvalue[2] >= 250) 		//向右微偏出，需要向左微调
								{
										firstspeedtemp = 300;
										secondspeedtemp = 300;
										thirdspeedtemp = 300;
										fourthspeedtemp = 300;
								}
								else if (luxvalue[2] <= 200 && luxvalue[1] >= 250) 		//向左微偏出，需要向右微调
								{
										firstspeedtemp = -300;
										secondspeedtemp = -300;
										thirdspeedtemp = -300;
										fourthspeedtemp = -300;
								}
								else if (luxvalue[0] <= 200) 		//向右偏出，需要向左调
								{
										firstspeedtemp = 350;         // 原地旋转
										secondspeedtemp = 350;
										thirdspeedtemp = 350;
										fourthspeedtemp = 350;
								}
								else if (luxvalue[3] <= 200) 		//向左偏出，需要向右调
								{
										firstspeedtemp = -350;         // 原地旋转
										secondspeedtemp = -350;
										thirdspeedtemp = -350;
										fourthspeedtemp = -350;
								}
								//出现无法探测到轨道的情况，需要利用前一时刻的信息，进行旋转
								else if (preState == 0)								//左边有轨道，向左旋转
								{
										firstspeedtemp = 350;         // 原地旋转
										secondspeedtemp = 350;
										thirdspeedtemp = 350;
										fourthspeedtemp = 350;
								}
								else 							//右边有轨道，向右旋转
								{
										firstspeedtemp = -350;         // 原地旋转
										secondspeedtemp = -350;
										thirdspeedtemp = -350;
										fourthspeedtemp = -350;
								}
						}
				}
				*/
				
        /*
        // 测试使用，原地运动，前进，后退，左平移，右平移
        if (runflag)
        {
            runtimes++;
            
            // 四轮平台麦克纳姆轮
					
            if (runtimes > 0 && runtimes <= 50)
            {
                firstspeedtemp = -1000;         // 前进
                secondspeedtemp = 1000;
                thirdspeedtemp = 1000;
                fourthspeedtemp = -1000;
            }
            else if(runtimes > 50 && runtimes <= 100)
            {
                firstspeedtemp = 1000;          // 后退
                secondspeedtemp = -1000;
                thirdspeedtemp = -1000;
                fourthspeedtemp = 1000;          
            }
            else if(runtimes > 100 && runtimes <= 150)
            {
                firstspeedtemp = 1000;          // 左平移
                secondspeedtemp = 1000;
                thirdspeedtemp = -1000;
                fourthspeedtemp = -1000;
            }
            else if(runtimes > 150 && runtimes <= 200)
            {
                firstspeedtemp = -1000;         // 右平移
                secondspeedtemp = -1000;
                thirdspeedtemp = 1000;
                fourthspeedtemp = 1000;
            }
						
						
						else if(runtimes > 200 && runtimes <= 250)
            {
                firstspeedtemp = 2000;         // 
                secondspeedtemp = 0;
                thirdspeedtemp = 500;
                fourthspeedtemp = 0;
            }
						else if(runtimes > 250 && runtimes <= 300)
            {
                firstspeedtemp = -1300;         // 
                secondspeedtemp = -150;
                thirdspeedtemp = 0;
                fourthspeedtemp = 1000;
            }
						
						//测试原地旋转
						
						if(runtimes > 0 && runtimes <= 200)
            {
                firstspeedtemp = -300;         // 
                secondspeedtemp = -1500;
                thirdspeedtemp = 300;
                fourthspeedtemp = -1500;
            }
						else if(runtimes > 200 && runtimes <= 400)
            {
                firstspeedtemp = 700;         // 
                secondspeedtemp = 1300;
                thirdspeedtemp = -700;
                fourthspeedtemp = 1300;
            }
							else if(runtimes > 400 && runtimes <= 600)
            {
                firstspeedtemp = 700;         // 最终成功原地旋转
                secondspeedtemp = 1300;
                thirdspeedtemp = -500;
                fourthspeedtemp = 1200;
            }
						
						
            if(runtimes > 200)
            {
                runtimes = 0;
            }
            
						
            // 三轮全向平台
            
            if (runtimes > 0 && runtimes <= 50)
            {
                firstspeedtemp = -1000;         // 前进
                secondspeedtemp = 1000;
                thirdspeedtemp = 0;             
            }
            else if (runtimes > 50 && runtimes <= 100)
            {
                firstspeedtemp = 1000;          // 后退
                secondspeedtemp = -1000;
                thirdspeedtemp = 0;             
            }
            else if (runtimes > 100 && runtimes <= 150)
            {
                firstspeedtemp = 1000;          // 原地左旋转
                secondspeedtemp = 1000;
                thirdspeedtemp = 1000;  
            }
            else if (runtimes > 150 && runtimes <= 200)
            {
                firstspeedtemp = -1000;         // 原地右旋转
                secondspeedtemp = -1000;
                thirdspeedtemp = -1000;  
            }
            else if (runtimes > 200 && runtimes <= 300)
            {
                VectorMove(90, 2000, 0);       // 90度左平移
                firstspeedtemp = motorspeedbuffer[0];
                secondspeedtemp = motorspeedbuffer[1];
                thirdspeedtemp = motorspeedbuffer[2];
            }
            else if (runtimes > 300 && runtimes <= 400)
            {
                VectorMove(-90, 2000, 0);      // -90度右平移
                firstspeedtemp = motorspeedbuffer[0];
                secondspeedtemp = motorspeedbuffer[1];
                thirdspeedtemp = motorspeedbuffer[2];
            }
            else if (runtimes > 400)
            {
                runtimes = 0;
            }
            
        }
        */
				if(speed > 1000)                     //超速保护
					speed = 1000;
				if (runflag)                         // 用direction、speed给电机轮子速度赋值
        {				
					if((direction == 0)||(direction >6))
					{
						firstspeedtemp = 0; 
						secondspeedtemp = 0;
						thirdspeedtemp = 0;
						fourthspeedtemp = 0;
					}
					else if(direction == 1)
					{
						firstspeedtemp = -speed;         // 前进
            secondspeedtemp = speed;
            thirdspeedtemp = speed;
            fourthspeedtemp = -speed;
					}
            
					else if(direction == 2)
					{
							firstspeedtemp = speed;          // 后退
							secondspeedtemp = -speed;
							thirdspeedtemp = -speed;
							fourthspeedtemp = speed;          
						
					}
					else if(direction == 3)
					{
							firstspeedtemp = -speed;          // 向左
							secondspeedtemp = -speed;
							thirdspeedtemp = speed;
							fourthspeedtemp = speed;
							
					}
					else if(direction == 4)
					{
							firstspeedtemp = speed;         // 向右
							secondspeedtemp = speed;
							thirdspeedtemp = -speed;
							fourthspeedtemp = -speed;
						 
					}
					else if(direction == 5)
					{
							firstspeedtemp = speed;         	 // 左转
							secondspeedtemp = speed;
							thirdspeedtemp = speed;
							fourthspeedtemp = speed;

					}
					else if(direction == 6)
					{
							firstspeedtemp = -speed;         	 // 右转
							secondspeedtemp = -speed;
							thirdspeedtemp = -speed;
							fourthspeedtemp = -speed;
					}
				}
        
					
        if (++n >= 1)
        {
            n = 0;
            
            //  解析上位机指令，并回复上位机各关节状态
            //result = UpRobotSlaveRxPacket(&str_rx_buffer, &str_cmd);	        // 解析上位机发送数据帧
            if (result)
            {
                result = 0;
                
                /*  保存参数    */
                for (h = 0; h < 4; h++)                                         // 保存速度参数，4个电机模块，三轮结构，第四个模块无效
                {
                    In16(temph, str_cmd.parameter[1 + 8*h], str_cmd.parameter[0 + 8*h]);
                    In16(templ, str_cmd.parameter[3 + 8*h], str_cmd.parameter[2 + 8*h]);
                    In32(motor_data[0].sendspeed, templ, temph);
                }
                
            //  receiveresult = 1;                                              // 成功解析一帧上位机协议包标志
            }
            
            /*
            // 发送第一个电机模块
            if (receiveresult)
                UpdataMotorCmdPraseSendBuf(0x01);                               // 非中断发送方式组织数据
            else
                UpMotorNouseCmdPraseSendBuf(0x01);
            UART3TXEN;
            Wp_DelayUs(2);
            UpMotorSlaveTxPacket(&str_motor_reply);                             // 发送数据
            Wp_DelayUs(1);
            UART3RXEN;
            Wp_DelayUs(3000);                                                   // 延时2.5ms左右
            // 解析各关节返回的数据帧，并发送各模块PDO协议包
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // 解析驱动器返回数据帧
            if (result)
            {
                result = 0;
                
                In16(temph, str_motor_cmd.parameter[1], str_motor_cmd.parameter[0]);
                In16(templ, str_motor_cmd.parameter[3], str_motor_cmd.parameter[2]);
                In32(motor_data[0].receivespeed, templ, temph);
                
                In16(temph, str_motor_cmd.parameter[5], str_motor_cmd.parameter[4]);
                In16(templ, str_motor_cmd.parameter[7], str_motor_cmd.parameter[6]);
                In32(motor_data[0].receiveposition, templ, temph);
            }
            
            // 发送第二个电机模块
            if (receiveresult)
                UpdataMotorCmdPraseSendBuf(0x02);                               // 非中断发送方式组织数据
            else
                UpMotorNouseCmdPraseSendBuf(0x02);
            UART3TXEN;
            Wp_DelayUs(2);
            UpMotorSlaveTxPacket(&str_motor_reply);                             // 发送数据
            Wp_DelayUs(1);
            UART3RXEN;
            Wp_DelayUs(3000);                                                   // 延时2.5ms左右
            // 解析各关节返回的数据帧，并发送各模块PDO协议包
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // 解析驱动器返回数据帧
            if (result)
            {
                result = 0;
                
                In16(temph, str_motor_cmd.parameter[1], str_motor_cmd.parameter[0]);
                In16(templ, str_motor_cmd.parameter[3], str_motor_cmd.parameter[2]);
                In32(motor_data[1].receivespeed, templ, temph);
                
                In16(temph, str_motor_cmd.parameter[5], str_motor_cmd.parameter[4]);
                In16(templ, str_motor_cmd.parameter[7], str_motor_cmd.parameter[6]);
                In32(motor_data[1].receiveposition, templ, temph);
            }
            
            // 发送第三个电机模块
            if (receiveresult)
                UpdataMotorCmdPraseSendBuf(0x03);                               // 非中断发送方式组织数据
            else
                UpMotorNouseCmdPraseSendBuf(0x03);
            UART3TXEN;
            Wp_DelayUs(2);
            UpMotorSlaveTxPacket(&str_motor_reply);                             // 发送数据
            Wp_DelayUs(1);
            UART3RXEN;
            Wp_DelayUs(3000);                                                   // 延时2.5ms左右
            // 解析各关节返回的数据帧，并发送各模块PDO协议包
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // 解析驱动器返回数据帧
            if (result)
            {
                result = 0;
                
                In16(temph, str_motor_cmd.parameter[1], str_motor_cmd.parameter[0]);
                In16(templ, str_motor_cmd.parameter[3], str_motor_cmd.parameter[2]);
                In32(motor_data[2].receivespeed, templ, temph);

                In16(temph, str_motor_cmd.parameter[5], str_motor_cmd.parameter[4]);
                In16(templ, str_motor_cmd.parameter[7], str_motor_cmd.parameter[6]);
                In32(motor_data[2].receiveposition, templ, temph);
            }
            
            // 发送第四个电机模块
            if (receiveresult)
                UpdataMotorCmdPraseSendBuf(0x04);                               // 非中断发送方式组织数据
            else
                UpMotorNouseCmdPraseSendBuf(0x04);
            UART3TXEN;
            Wp_DelayUs(2);
            UpMotorSlaveTxPacket(&str_motor_reply);                             // 发送数据
            Wp_DelayUs(1);
            UART3RXEN;
            Wp_DelayUs(3000);                                                   // 延时2.5ms左右
            // 解析各关节返回的数据帧，并发送各模块PDO协议包
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // 解析驱动器返回数据帧
            if (result)
            {
                result = 0;
                
                In16(temph, str_motor_cmd.parameter[1], str_motor_cmd.parameter[0]);
                In16(templ, str_motor_cmd.parameter[3], str_motor_cmd.parameter[2]);
                In32(motor_data[3].receivespeed, templ, temph);
                
                In16(temph, str_motor_cmd.parameter[5], str_motor_cmd.parameter[4]);
                In16(templ, str_motor_cmd.parameter[7], str_motor_cmd.parameter[6]);
                In32(motor_data[3].receiveposition, templ, temph);
            }
            
            if (receiveresult)
            {
                // 发送执行指令
                ActionMotorCmdPraseSendBuf();                                   // 非中断发送方式组织执行指令
                UART3TXEN;
                Wp_DelayUs(2);
                UpMotorSlaveTxPacket(&str_motor_reply);                         // 发送数据
                Wp_DelayUs(1);
                UART3RXEN;
                
                receiveresult = 0;
            }
            */
            
            Wp_SetMotorSpeed(0x01, firstspeedtemp);
            Wp_DelayUs(3000);                                                   // 延时2.5ms左右
            // 解析各关节返回的数据帧，并发送各模块PDO协议包
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // 解析驱动器返回数据帧
            if (result)
            {
                result = 0;
                
                In16(temph, str_motor_cmd.parameter[1], str_motor_cmd.parameter[0]);
                In16(templ, str_motor_cmd.parameter[3], str_motor_cmd.parameter[2]);
                In32(motor_data[0].receivespeed, templ, temph);
                
                In16(temph, str_motor_cmd.parameter[5], str_motor_cmd.parameter[4]);
                In16(templ, str_motor_cmd.parameter[7], str_motor_cmd.parameter[6]);
                In32(motor_data[0].receiveposition, templ, temph);
                
                firstsendok = 1;
            }
            else
                firstsendok = 0;
            
            Wp_SetMotorSpeed(0x02, secondspeedtemp);
            Wp_DelayUs(3000);                                                   // 延时2.5ms左右
            // 解析各关节返回的数据帧，并发送各模块PDO协议包
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // 解析驱动器返回数据帧
            if (result)
            {
                result = 0;
                
                In16(temph, str_motor_cmd.parameter[1], str_motor_cmd.parameter[0]);
                In16(templ, str_motor_cmd.parameter[3], str_motor_cmd.parameter[2]);
                In32(motor_data[1].receivespeed, templ, temph);
                
                In16(temph, str_motor_cmd.parameter[5], str_motor_cmd.parameter[4]);
                In16(templ, str_motor_cmd.parameter[7], str_motor_cmd.parameter[6]);
                In32(motor_data[1].receiveposition, templ, temph);
                
                secondsendok = 1;
            }
            else
                secondsendok = 0;
            
            Wp_SetMotorSpeed(0x03, thirdspeedtemp);
            Wp_DelayUs(3000);                                                   // 延时2.5ms左右
            // 解析各关节返回的数据帧，并发送各模块PDO协议包
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // 解析驱动器返回数据帧
            if (result)
            {
                result = 0;
                
                In16(temph, str_motor_cmd.parameter[1], str_motor_cmd.parameter[0]);
                In16(templ, str_motor_cmd.parameter[3], str_motor_cmd.parameter[2]);
                In32(motor_data[2].receivespeed, templ, temph);
                
                In16(temph, str_motor_cmd.parameter[5], str_motor_cmd.parameter[4]);
                In16(templ, str_motor_cmd.parameter[7], str_motor_cmd.parameter[6]);
                In32(motor_data[2].receiveposition, templ, temph);
                
                thirdsendok = 1;    
            }
            else
                thirdsendok = 0;
            
            Wp_SetMotorSpeed(0x04, fourthspeedtemp);
            Wp_DelayUs(3000);                                                   // 延时2.5ms左右
            // 解析各关节返回的数据帧，并发送各模块PDO协议包
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // 解析驱动器返回数据帧
            if (result)
            {
                result = 0;
                
                In16(temph, str_motor_cmd.parameter[1], str_motor_cmd.parameter[0]);
                In16(templ, str_motor_cmd.parameter[3], str_motor_cmd.parameter[2]);
                In32(motor_data[3].receivespeed, templ, temph);
                
                In16(temph, str_motor_cmd.parameter[5], str_motor_cmd.parameter[4]);
                In16(templ, str_motor_cmd.parameter[7], str_motor_cmd.parameter[6]);
                In32(motor_data[3].receiveposition, templ, temph);
                
                fourthsendok = 1;
            }
            else
                fourthsendok = 0;
            
            // 当所有的电机发送都成功，再发送执行命令
            if (fourthsendok & thirdsendok & secondsendok & firstsendok)
            {
                fourthsendok = 0;
                thirdsendok = 0;
                secondsendok = 0;
                firstsendok = 0;
                
                Wp_ActiomMotorMode();                               // 执行指令
            }
        }
        
        
        /*  测试阶段，50ms伺服周期    */
		if (++h >= 1)
        {	
            h = 0;
            
            gpioinputvalue = Wp_GetInputValue();                    // 读输入IO口的值
            gpiooutputvalue = Wp_GetOutputValue();                  // 读输出IO口的值
            Wp_GetAdcVoltageValue();                                // 计算各通道电压
            powervalue = Wp_FilterPower();					        // 计算电池电压并滤波
            powervalueint = powervalue * 1000;
            Wp_GetMpu6050Dmp();								        // 获取姿态信息
            /*
            // 返回上位机信息
            Wp_UpdataPcAlltiOutputSendBuf();                        // 姿态信息
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcGpioInputSendBuf();                          // 输入端口
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcGpioOutputSendBuf();                         // 输出端口
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcPowerValueSendBuf();                         // 电源电压
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcAdcSendBuf(1);                               // ADC第一组
            UpRobotSlaveTxPacket(&str_reply);
            Wp_UpdataPcAdcSendBuf(2);                               // ADC第二组
            UpRobotSlaveTxPacket(&str_reply);            
            Wp_UpdataPcAdcSendBuf(3);                               // ADC第三组
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcMotorPraseSendBuf(1);                        // 第一个电机模块
            UpRobotSlaveTxPacket(&str_reply);
            Wp_UpdataPcMotorPraseSendBuf(2);                        // 第二个电机模块
            UpRobotSlaveTxPacket(&str_reply);
            Wp_UpdataPcMotorPraseSendBuf(3);                        // 第三个电机模块
            UpRobotSlaveTxPacket(&str_reply);
            Wp_UpdataPcMotorPraseSendBuf(4);                        // 第四个电机模块
            UpRobotSlaveTxPacket(&str_reply);
        //  Wp_UpdataPcCmdPraseSendBuf();                           // 数据打包，所有电机模块返回数据
        //  UpRobotSlaveTxPacket(&str_reply);                       // 发送数据给上位机            
            */
		}
	}
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
