/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			main.c
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				�ƶ�С���̿�����ϵͳ������;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				�ƶ�С���̿�����ϵͳ������;
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
#include "Wp_Sys.h"
#include "math.h"


/*************************************************************************************************************
** ��������:			main
**
** ��������:			ϵͳ������;
** 						
**					    
** �������:			void;
** ����ֵ:				int;
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
int main(void)
{
    uint8 i = 0;
    uint8 j = 0;
    uint8 k = 0;
    uint8 h = 0;
    
    u8 n = 0;
    
	float pitch = 0.0;          // ��̬����
	float roll = 0.0;
	float yaw = 0.0;
    
//  u16 distance = 0;           // ���뻺��
//  u16 lux = 0;                // Lux����
    
    
	/*	��ʱ��(Timer3)�����жϵĳ�ʼ�����������ϵͳ��ʼ��������ǰ�棩	*/
//	Wp_UserTimerEnableIT(TIMER_CHANNEL0, 1000000);	// ʹ�ܼ�ʱ��0����ʱʱ��1s
//	Wp_UserTimerEnableIT(TIMER_CHANNEL2, 1000);	    // ʹ�ܼ�ʱ��2����ʱʱ��1ms
//	Wp_UserTimerSetHadler(TimerHadler);			    // ���ݼ�ʱ���ж���ں���ָ��
	
    /*	����1~3�жϵĳ�ʼ�����������ϵͳ��ʼ��������ǰ�棩	*/
	Wp_SetUART1Hadler(ReceiveUart1Hadler);		    // UART1�ж���ں���
	Wp_SetUART2Hadler(ReceiveUart2Hadler);		    // UART2�ж���ں���
	Wp_SetUART3Hadler(ReceiveUart3Hadler);		    // UART3�ж���ں���
	
	Wp_UserTimerEnableIT(TIMER_CHANNEL0, 10);	    // ʹ�ܼ�ʱ��0����ʱʱ��10us
	Wp_UserTimerEnableIT(TIMER_CHANNEL1, 500000);	    // ʹ�ܼ�ʱ��2����ʱʱ��500ms
	Wp_UserTimerSetHadler(TimerHadler);			        // ���ݼ�ʱ���ж���ں���ָ��
	
	Wp_SystemConfigure();						    // ϵͳ��ʼ��
	
	while(1)
	{
     // keyvalue = 5;                                                   // ��ʾ��ǰ����

		//Wp_SetPortOutputValue(1,1);																			//����Wp_SetPortOutputValue(u8 port, u8 value)��ʹOut1���1
																																			//��ע������Out�˿ڲ��Ǵ�0��ʼ��
		
		  // ������⴫������������ֵ
      for (n = 0; n < 12; n++)
			{
        infrareddistance[n] = Wp_CalculateDistanceChannel(n+1);
      }
			// ����Ҷȴ�������ͨ��ֵ
      for (n = 0; n < 6; n++)
      {
          luxvalue[n] = Wp_CalculateLuxChannel(7+n);       // ����ʹ�ã�����Lux    �Ҷȴ������ӵ�7����ʼ
      }

        switch(keyvalue)
        {
            case 1:                                                     // ��ʾ��̬��Ϣ
                    k++;
                    if (k == 1)
                    {
                        Wp_ClearOled();                                 // ����
                    }
                    if (k > 100)
                    {
                        k = 2;
                    }
                    j = 0;
                    h = 0;
                    i = 0;
                    
                    pitch = wp_dmp_data.Pitch;				            // ��ʾ������
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
                    roll = wp_dmp_data.Roll;				            // ��ʾ��ת��
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
                    yaw = wp_dmp_data.Yaw;					            // ��ʾƫ����
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
                    
                    OLED_P8x16Char(15, 1, 'V');                         // ��ʾ��Դ��ѹ
                    Wp_DisfloatIntegerandDecimal(11, 1, powervalue, 2, 1);
                    Wp_DisP16x16DotArray(2, 0, 0);                      // ��ʾ����̬��Ϣ��
                    Wp_DisP16x16DotArray(3, 0, 1);
                    Wp_DisP16x16DotArray(4, 0, 2);
                    Wp_DisP16x16DotArray(5, 0, 3);
                    
                    // ���Թ�ͨ��ֵ
                //  Wp_DisfloatIntegerandDecimal(11, 2, analogvalue[10]-0.99, 1, 3);
                //  lux = ((analogvalue[10]-0.99) * 10000) / 180;       // ����ʹ�ã�����Lux
                //  Wp_DisfloatIntegerandDecimal(11, 3, lux, 3, 1);
                //  lux = Wp_CalculateLuxChannel(11);                   // ����ʹ�ã�����Lux
                //  Wp_DisIntNum(11, 3, lux, 5);
                    
                    // ���Ժ��⴫��������ֵ
                //  Wp_DisfloatIntegerandDecimal(11, 3, analogvalue[11], 1, 3);
                //  distance = Wp_CalculateDistanceChannel(12);
                //  Wp_DisIntNum(11, 2, distance, 3);
                    
                /*  Wp_DisfloatIntegerandDecimal(11, 3, analogvalue[0], 1, 3);
                    Wp_DisIntNum(11, 2, infrareddistance[0], 3);
                    // ������⴫������������ֵ
                    for (n = 0; n < 12; n++)
                    {
                        infrareddistance[n] = Wp_CalculateDistanceChannel(n+1);
                    }
                */
                    
                break;
                
            case 2:                                                     // ��ʾ����GPIOֵ
                    j++;
                    if (j == 1)
                    {
                        Wp_ClearOled();                                 // ����
                    }
                    if (j > 100)
                    {
                        j = 2;
                    }
                    k = 0;
                    h = 0;
                    i = 0;
                    
                    printf("  Input Value\n");		                    // ��printf��ʾһ���ַ�
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
                
            case 3:                                                     // ��ʾ���GPIOֵ
                    i++;
                    if (i == 1)
                    {
                        Wp_ClearOled();                                 // ����
                    }
                    if (i > 100)
                    {
                        i = 2;
                    }
                    j = 0;
                    k = 0;
                    h = 0;
                    
                    printf("  Output Value\n");		                    // ��printf��ʾһ���ַ�
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
                    
            case 4:                                                     // ��ʾ��ģ��ͨ����ѹֵ
                    h++;
                    if (h == 1)
                    {
                        Wp_ClearOled();                                 // ����
                    }
                    if (h > 100)
                    {
                        h = 2;           
                    }
                    j = 0;
                    k = 0;
                    i = 0;
                    
                    Wp_DisfloatIntegerandDecimal(0, 0, powervalue, 2, 1);               // ��Դ��ѹ
                    Wp_DisfloatIntegerandDecimal(4, 0, analogvalue[0], 1, 1);           // ģ��1~15ͨ����ѹ
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
        
		Wp_DelayMs(10);                                                 // ��ʱ����
	}
}


/*************************************************************************************************************
** ��������:			Wp_Sev_TimerPro
**
** ��������:			50ms�ŷ��жϺ���;
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
void Wp_Sev_TimerPro(void)
{
		static int leftturnstate = 0;									// ���������򣬱�ǳ��Ƿ�����ת����ת״̬��1�����ڸ�״̬
		static int rightturnstate = 0;
		static int normalstate = 1;										// ���������򣬱�ǳ��Ƿ��ڼ�⵽�쳣״̬��0�������쳣״̬
		static int leftreassure = 0;										// ���������򣬼�¼�Ƿ������/�ұ�ȷ�ϻ�Դ�׶Σ�1�����ڸ�״̬
		static int rightreassure = 0;
		static int leftonwork = 0;											// ���������򣬼�¼�Ƿ������/�ұ߹���״̬��1�����ڸ�״̬
		static int rightonwork = 0;
		static int backtonormal = 0;										// ���������򣬼�¼�Ƿ��ڹ�����ص�normal��״̬�У�1�����ڸ�״̬
		static int preinfrareddistance[4] = {0};					// ��¼ǰһ״̬�ĺ�����룬����Ŀ��׷���������ǽ�ȼ������ͣ��ʱ�����ж��ƶ�����ķ�λ	
		static int counttime = 0;											// ������Ŀ��׷�ٹ��ܣ����ڼ�¼ʱ�䣬�Ӷ�ʵ�ֶ�ʱ
		static int preState = 0;												// ���ѭ��ʱʹ�ã�������¼ǰһʱ�̹����Ϣ��preState = 0��������й��
		static double dx = 0;														// ���ڵ������򣬼�¼��Ŀ��֮��x��y����ľ���
		static double dy = 0;
		static double dtheta = 0;												// ���ڵ������򣬼�¼��ͷ��Ŀ�귽��ĽǶȲ��Ϊ��ת����ʱ���
		static double dtime = 0;
		static double destx = 0;												// ���ڵ������򣬼�¼Ŀ�������
		static double desty = 0;
		static int navistate = 0;												// ���ڵ������򣬼�¼����״̬���ܹ�3״̬��״̬0����Ѱ�ҷ���״̬1������Ŀ���ߣ�״̬2-6����5�ֱ���״̬
		static int cruisestate = 0;											// ���ڽ�ͼ���򣬼�¼����״̬��0�������ң�1��������2�������Ҳ��ֵı��ϣ�3�������󲿷ֵı���
		static int leftforwardstate = 0;												// �������������ڼ�¼�Ƿ�����߿�ʼ���״̬��1�����ڸ�״̬
		static int rightforwardstate = 0;												// �������������ڼ�¼�Ƿ����ұ߿�ʼ���׶Σ�1�����ڸ�״̬
		static int leftbackstate = 0;												// �������������ڼ�¼�Ƿ�����߻ص�״̬��1�����ڸ�״̬
		static int rightbackstate = 0;												// �������������ڼ�¼�Ƿ����ұ߻ص�״̬��1�����ڸ�״̬
		static int firedis = 0;														// // �������������ڼ�¼��Դ�����Ӧ������ʱ��

	static u8 i = 0;                    // LED1��˸
    static u16 j = 0;                   // LED2��˸
    static u8 k = 0;                    // ˢ�°���ʹ��
	static u8 h = 0;                    // ��ȡ��̬��Ϣʹ��
    static u8 n = 0;
//  static u16 m = 0;
    
    //static u8 runflag = 0;              // ���б�־
    
    static u8 floatleddismode = 0;      // ��ˮ����ʾģʽ
    u8 result = 0;
//  static u8 receiveresult = 0;        // �ɹ�����һ֡��λ��Э���־���ڷ�����ִ��ָ�������
    
    u16 temph = 0;                      // ��ʱת������
    u16 templ = 0;
    
    long firstspeedtemp = 0;            // �ĸ����ģ����ٶȻ���
    long secondspeedtemp = 0;
    long thirdspeedtemp = 0;
    long fourthspeedtemp = 0;
		static long operation_speed = gospeed;  //�ֶ�����ʱ���ٶȣ�Ĭ��Ϊgospeed
		static u8 direction_command = 0x00;         //�ֶ�����ʱ�ķ���Ĭ��ǰ��
    
    u8 firstsendok = 0;                 // �ɹ����ͱ�־
    u8 secondsendok = 0;    
    u8 thirdsendok = 0;    
    u8 fourthsendok = 0;

    static u16 runtimes = 0;            // ����ʱ�������������DEMOʹ��
		static int ReceivingData = 0;       // ���������վݱ�־λ��Ϊ1ʱֻ�������ݣ������в���
		static u8 DataFromBle[10] = {0};    // ���������յ�����,���10������
 		static int DataCount = 0;             // �������ݸ���
		
		static int AlarmFlag = 0;             //������־λ
		static int ModeFlag = 0;            //0:�ֶ��򵼺���1:���ٱ�־λ,2:������ϱ�־λ,3:����־λ
		
		static int SendPositionCount = 0;    //���������ڻش����꣬ѭ��20��ˢ��һ�Σ���1s
		//u8 SendStr[3] = {0};                 // ���ڻش��ֻ�ͨ��
		
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		if(UART2_data >= 0x00 && UART2_data <= 0x06 && ReceivingData == 0)//�����ֶ������ķ���
		{
		  direction_command = UART2_data;
			UART2_data = 0xff; 
			ModeFlag = 0;                                //������������ģʽ
		}
		
		if(UART2_data == 0x07 && operation_speed < 2400 && ReceivingData == 0)//����
		{
			operation_speed = operation_speed + 100;
			Wp_Usart2_SendChar(0xff);
			Wp_Usart2_SendChar(operation_speed / 100 *16 + (operation_speed /10) % 10 );

			UART2_data = 0xff;                            //0xffΪ����̬
			ModeFlag = 0;
		}
		
		if(UART2_data == 0x08 && operation_speed > 80 && ReceivingData == 0)//����
		{
			operation_speed = operation_speed - 100;

			Wp_Usart2_SendChar(0xff);
			Wp_Usart2_SendChar(operation_speed / 100 *16 + (operation_speed /10) % 10 );

			UART2_data = 0xff;
			ModeFlag = 0;
		}
    
		if(UART2_data == 0x09 && ReceivingData == 0)//�������
		{
			
			UART2_data = 0xff;
			ModeFlag = 2;
		}
		
		if(UART2_data == 0x10 && ReceivingData == 0)//Ѳ�����
		{
			
			UART2_data = 0xff;
			ModeFlag = 3;
		}
		
		if(UART2_data == 0x11 && ReceivingData == 0)//����
		{
			
			UART2_data = 0xff;
			ModeFlag = 1;
		}
		if(UART2_data == 0x12 && ReceivingData == 0)//��ʼ��ˮ,ʹ�õ����ڶ���outport
		{
			Wp_SetPortOutputValue(7,1);
			UART2_data = 0xff;
			ModeFlag = 0;
		}
		if(UART2_data == 0x13 && ReceivingData == 0)//������ˮ
		{
			Wp_SetPortOutputValue(7,0);
			UART2_data = 0xff;
			ModeFlag = 0;
		}
		
		if(UART2_data == 0xfe)                          //0xfeʱ�����������״̬�����ݷ�ΧΪ0x00-0xfa
		{
			ReceivingData = 1;
			DataCount = 0;
			DataFromBle[0] = '\0';
			Wp_Usart2_SendChar(0xfe);
			UART2_data = 0xff;
			ModeFlag = 0;
		}
		else if(UART2_data == 0xfd)                          //0xfdʱ��������
		{
			ReceivingData = 0;
			DataFromBle[DataCount ++] = '\0';                       // ��β��
			Wp_Usart2_SendStr((char*)DataFromBle);               //�����ַ���
			UART2_data = 0xff;
		}
		else if(ReceivingData == 1 && UART2_data != 0xff)         //0xff��ֹ���ϸ�ֵ
		{
			DataFromBle[DataCount ++] = UART2_data;                 //������������
			UART2_data = 0xff;
		}
		
		
		if (++i >= 10)										        // ����LEDƵ��
		{
			i = 0;
            
            LED2_TOGGLE;
            
        //  Wp_FlowLights(floatleddismode);                         // ��ˮ�ƺ���
		}
        if (++j >= 2)                                               // �ӿ����LEDƵ��
        {
            j = 0;
            
            LED1_TOGGLE;
        }
        
        if (++k >= 1)                                               // ��ⰴ���Ƿ���
        {
            k = 0;
            
            /*  ˢ�°���״̬���û��л���Ļʹ��      */
            Wp_KeyRefreshState(&key_up);                            // ˢ�°���״̬
            if (Wp_KeyAccessTimes(&key_up, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_up, KEY_ACCESS_REFRESH);             
							
							  Wp_Usart2_SendStr("CC");								//���Է����ַ���
                
							  keyvalue++;                                         // �л���Ļ״̬
                if (keyvalue >= 8)
                {
                    keyvalue = 1;
                }
            }
            /*  ˢ�°���״̬���û��л���Ļʹ��      */
            Wp_KeyRefreshState(&key_down);                          // ˢ�°���״̬
            if (Wp_KeyAccessTimes(&key_down, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_down, KEY_ACCESS_REFRESH);
                
							Wp_Usart2_SendChar(0x55);								//���Է���Char
                keyvalue--;                                         // �л���Ļ״̬
                if (keyvalue <= 0)
                {
                    keyvalue = 7;
                }
            }
            /*  ˢ�°���״̬���û��л���Ļʹ��      */
            Wp_KeyRefreshState(&key_back);                          // ˢ�°���״̬
            if (Wp_KeyAccessTimes(&key_back, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_back, KEY_ACCESS_REFRESH);
                
                keyvalue = 1;                                       // �л���Ļ״̬
                
                runflag = 0;                                        // ����BACK�����˶�����
                runtimes = 0;                                       // ��ʱ�������
            }
            /*  ˢ�°���״̬���û��л���Ļʹ��      */
            Wp_KeyRefreshState(&key_ok);                            // ˢ�°���״̬
            if (Wp_KeyAccessTimes(&key_ok, KEY_ACCESS_READ) != 0)
            {
                Wp_KeyAccessTimes(&key_ok, KEY_ACCESS_REFRESH);
                
            //  keyvalue = 1;                                       // �л���Ļ״̬
                
                floatleddismode++;                                  // ��ˮ��ģʽ�л�
                if (floatleddismode >= 3)
                    floatleddismode = 0;
                
                runflag = 1;                                        // ����OK�����˶���ʼ
            }
        }
        
				//ˢ������
				GetLocation();
				
				//�¶ȹ��߱����������һ��ADC
				if(analogvalue[14] > 0.40 && AlarmFlag == 0)      //��ֵ40���϶�
				{
					Wp_Usart2_SendChar(0x01);     //0x01Ϊ����
					AlarmFlag = 1;
				}
				
				if(analogvalue[14] < 0.35 && AlarmFlag == 1)      //��ֵ35���϶�
				{
					Wp_Usart2_SendChar(0x02);     //0x02Ϊ�������
					AlarmFlag = 0;
				}
				
        /*
        // ����ʹ�ã���������ǰ�������ˣ���ת����ת
        if (key_up())                   // ǰ��
        {
            firstspeedtemp = -3000;
            secondspeedtemp = 3000;
            thirdspeedtemp = 3000;
            fourthspeedtemp = -3000;
        }
        else if (key_down())            // ����
        {
            firstspeedtemp = 3000;
            secondspeedtemp = -3000;
            thirdspeedtemp = -3000;
            fourthspeedtemp = 3000;            
        }
        else if (key_back())            // ��ת
        {
            firstspeedtemp = 2000;
            secondspeedtemp = 2000;
            thirdspeedtemp = 2000;
            fourthspeedtemp = 2000;                
        }
        else if (key_ok())              // ��ת
        {
            firstspeedtemp = -2000;
            secondspeedtemp = -2000;
            thirdspeedtemp = -2000;
            fourthspeedtemp = -2000;          
        }
        */
				
				
				// ����ʹ�ã���������
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
                speed = operation_speed - 40;    //��ת��Ĭ���ٶ�Ϊturnspeed����gospeed-40
							  direction = 5;
            }
						else if(direction_command == 0x06)
            {
                speed = operation_speed - 40;
								direction = 6;
            }
				}
				
				
				//{0xfc,0x10,0x10}
				//if (UART2_DATA == 0xff)				����֮���˼·
						
				//if (DataFromBle[0] == 0xfc)
				//DataFromBle[1] = 0x15;
				//DataFromBle[2] = 0x10;
				if (!runflag)													// ֹͣ�˶���ص�״̬0
				{
						navistate = 0;
				}
				if (DataFromBle[0] == 0xfc)
				{
						if (runflag)
						{
							  //�ش����꣬1s1��
								if(SendPositionCount == 20)
								{
									
									Wp_Usart2_SendChar(0xfe);
									Wp_Usart2_SendChar(((int)location_x) / 10 * 16 + ((int)location_x)  % 10 );
									Wp_Usart2_SendChar(((int)location_y) / 10 * 16 + ((int)location_y)  % 10 );
									
									SendPositionCount = 0;
								}
							  SendPositionCount ++;
							
								destx = (int)DataFromBle[1]%16 + (int)DataFromBle[1]/16*10;						// ���յ�������Ŀ���ַ��Ϣת��Ϊdouble���ͣ��õ�BCD���ת��
								desty = (int)DataFromBle[2]%16 + (int)DataFromBle[2]/16*10;
								dx = destx - location_x;																		// ����С����Ŀ��λ�õĲ�ֵ
								dy = desty - location_y;
								if (navistate == 0)
								{
										if (dx == 0 && dy == 0)																				// ���û�в�ֵ
										{
												dtheta = 0;
												DataFromBle[0] = 0xfb;																	// �ǶȲ�Ϊ0����һλ��0xfb����ζ�ŵ���λ�ã��˳�����
												direction = 0;
												Wp_Usart2_SendChar(0xfb);																// �����ã�����λ����һ���������Ϣ
										}
										else if (dx == 0)																					// dx = 0�����
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
										else if (dx > 0 && dy >= 0)												// ��һ�������dx,dy�����㣬atan������ľ���Ŀ�귽λ���ǶȲ����angle-atan(dy/dx)
										{
												dtheta = angle - atan(dy/dx)*180/PI;
										}
										else if (dx < 0)																	// �ڶ������ޣ�atan����ֵ��180����������Ŀ�귽λ
										{
												dtheta = angle - atan(dy/dx)*180/PI - 180;
										}
										else if (dx > 0 && dy < 0)													// �������ޣ�atan��Ҫ��360����������Ŀ�귽λ
										{
												dtheta = angle - atan(dy/dx)*180/PI - 360; 			
										}
										if (dtheta > 1 || dtheta < -1)																	// ����нǶȲ����ת������������������ֵ������ֻ��һ��С�Ż���
										{
												if (dtheta >= 180 || (dtheta <= 0 && dtheta > -180))					// dtheta��180~360�Լ�-180~0��ʱ����ת�ܸ����ҵ�Ŀ�귽��	
												{
														direction = 5;
														speed = turnspeed;
												}
												else																// �����������ת����
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
								else if (navistate == 1)									// ǰ��״̬
								{
										direction = 1;
										speed = gospeed;
										if (dx <= 4 && dx >= -4 && dy <= 4 && dy >= -4)										// ����Ŀ��λ���ڵ�һ����Χ
										{	
												DataFromBle[0] = 0xfb;																				// �õ����Ĵ�����ֵ���˳�����
												direction = 0;
												Wp_Usart2_SendChar(0xfb);
												navistate = 0;
										}
										if (!(infrareddistance[1] >= 200 && infrareddistance[2] >= 200 			// ��������ϰ����ʼִ�б��Ϲ���
											&& infrareddistance[0] >= 200 && infrareddistance[3] >= 200))
										{
												direction = 0;
												Wp_Usart2_SendChar(0xf9);
												//Wp_Usart2_SendChar(0xfa);
												//Wp_Usart2_SendChar(((int)location_x) / 10 * 16 + ((int)location_x)  % 10 );
												//Wp_Usart2_SendChar(((int)location_y) / 10 * 16 + ((int)location_y)  % 10 );
											
												if (infrareddistance[0] < 200 && infrareddistance[1] >= 200 &&				// ���ֱ���״̬���ϰ��������
													infrareddistance[2] >= 200 && infrareddistance[3] >= 200)
														navistate = 2;
												else if (infrareddistance[3] < 200 && infrareddistance[1] >= 200 &&			// �ұ�
													infrareddistance[2] >= 200 && infrareddistance[0] >= 200)
														navistate = 3;
												else if (infrareddistance[0] < 200 && infrareddistance[1] < 200 &&			// ��ǰ
													infrareddistance[2] >= 200 && infrareddistance[3] >= 200)
														navistate = 4;
												else if (infrareddistance[2] < 200 && infrareddistance[3] < 200 &&			// ��ǰ	
													infrareddistance[1] >= 200 && infrareddistance[0] >= 200)
														navistate = 5;
												else																																	// ���ࣨ��Ҫ��ǰ����
														navistate = 6;
												runtimes = 0;
										}
								}
								else if (navistate == 2)															// ����״̬2
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 25)													// ��࣬������ת��Լ50��
										{
												direction = 6;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 25 && runtimes <= 75)															// ǰ�����ƹ��ϰ���
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes > 75)
										{
												navistate = 0;															// ��ɺ�ص�״̬0
												runtimes = 0;
										}
								}
								else if (navistate == 3)															// ����״̬3
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 25)													// �Ҳ࣬������ת��Լ50��
										{
												direction = 5;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 25 && runtimes <= 75)															// ǰ�����ƹ��ϰ���
										{
												direction = 1;
												speed = gospeed;
										}
										if (runtimes > 75)															
										{
												navistate = 0;															// ��ɺ�ص�״̬0
												runtimes = 0;
										}
								}
								else if (navistate == 4)															// ����״̬4
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 35)													// ��ǰ��������ת��Լ70��
										{
												direction = 6;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 35 && runtimes <= 85)															// ǰ�����ƹ��ϰ���
										{
												direction = 1;
												speed = gospeed;
										}
										if (runtimes > 85)														
										{
												navistate = 0;															// ��ɺ�ص�״̬0
												runtimes = 0;
										}
								}
								else if (navistate == 5)															// ����״̬5
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 35)												// ��ǰ��������ת��Լ70��
										{
												direction = 5;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 35 && runtimes <= 85)															// ǰ�����ƹ��ϰ���
										{
												direction = 1;
												speed = gospeed;
										}
										if (runtimes > 85)															
										{
												navistate = 0;															// ��ɺ�ص�״̬0
												runtimes = 0;
										}
								}
								else if (navistate == 6)
								{
										runtimes++;
										if (runtimes > 0 && runtimes <= 45)												// ǰ��������ת90��
										{
												direction = 5;
												speed = turnspeed;
												if (runtimes == 25)
												{
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes > 45 && runtimes <= 95)															// ǰ�����ƹ��ϰ���
										{
												direction = 1;
												speed = gospeed;
										}
										if (runtimes > 95)														
										{
												navistate = 0;															// ��ɺ�ص�״̬0
												runtimes = 0;
										}
								}
						}	
				}				
					
				
				// ��ͼ����
				if (!runflag)													// ֹͣ�˶���ص�״̬0
				{
						cruisestate = 0;
				}
				if (DataFromBle[0] == 0xec &&  runflag == 1)
				{
					 //�ش����꣬1s1��
								if(SendPositionCount == 20)
								{
									
									Wp_Usart2_SendChar(0xfe);
									Wp_Usart2_SendChar(((int)location_x) / 10 * 16 + ((int)location_x)  % 10 );
									Wp_Usart2_SendChar(((int)location_y) / 10 * 16 + ((int)location_y)  % 10 );
									
									SendPositionCount = 0;
								}
							  SendPositionCount ++;
								
								destx = (int)DataFromBle[1]%16 + (int)DataFromBle[1]/16*10;						// ���յ�������Ŀ���ַ��Ϣת��Ϊdouble���ͣ��õ�BCD���ת��
								desty = (int)DataFromBle[2]%16 + (int)DataFromBle[2]/16*10;
			
						if (location_y <= desty)													// y�߽�ֵ���Լ������ӿڣ�
						{
								if (cruisestate == 0)  															// x������������
								{
										if (location_x <= destx)
										{
												if (infrareddistance[0] >= 200 && infrareddistance[1] >= 200 
													&& infrareddistance[4] >= 200 && infrareddistance[5] >= 200)						// �����ϰ��������״̬
												{
														direction = 1;
														speed = gospeed;
												}
												else 
												{
														// �����ϰ���д�ӿڣ���ɫ
														Wp_Usart2_SendChar(0xf9);
														cruisestate = 2;
														runtimes = 0;
												}
										}
										else																						// �������꼫�ޣ������ͷ״̬
										{
												cruisestate = 4;
												runtimes = 0;
										}
								}
								else if (cruisestate == 1)													// x�Ḻ��������	
								{
										if (location_x >= 0)
										{
												if (infrareddistance[0] >= 200 && infrareddistance[1] >= 200 
													&& infrareddistance[4] >= 200 && infrareddistance[5] >= 200)						// �����ϰ��������״̬
												{
														direction = 1;
														speed = gospeed;
												}
												else 
												{
														// �����ϰ���д�ӿڣ���ɫ
														Wp_Usart2_SendChar(0xf9);
														cruisestate = 3;
														runtimes = 0;
												}
										}
										else																								// �������꼫�ޣ������ͷ״̬
										{
												cruisestate = 5;
												runtimes = 0;
										}
								}
								else if (cruisestate == 2)										// ���������߶�ܳ���
								{
										runtimes++;
										if (runtimes >= 0 && runtimes < 45)											// ��ת
										{
												direction = 5;
												speed = turnspeed;
												if (runtimes == 25)
												{
														// ����Ϣ����غ�ɫ
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes >= 45 && runtimes < 95)									// ǰ��
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 95 && runtimes < 140)						// ��ת
										{
												direction = 6;
												speed = turnspeed;
										}
										else if (runtimes >= 140 && runtimes < 190)								// ǰ��
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 190 && runtimes < 235)													// ��ת
										{
												direction = 6;
												speed = turnspeed;
										}
										else if (runtimes >= 235 && runtimes < 285)								// ǰ��
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 285 && runtimes < 330)								// ��ת
										{
												direction = 5;
												speed = turnspeed;
										}
										else if (runtimes > 330)												// �ص�x����������״̬
										{
												runtimes = 0;
												cruisestate = 0;
										}
								}
								else if (cruisestate == 3)											// ��״̬2��ȫ�෴
								{
										runtimes++;
										if (runtimes >= 0 && runtimes < 45)									
										{
												direction = 6;
												speed = turnspeed;
												if (runtimes == 25)
												{
														// ����Ϣ����غ�ɫ
														Wp_Usart2_SendChar(0xf8);
												}
										}
										else if (runtimes >= 45 && runtimes < 95)									// ǰ��
										{
												direction = 1;
												speed = gospeed;
										}
										else if (runtimes >= 95 && runtimes < 140)					
										{
												direction = 5;
												speed = turnspeed;
										}
										else if (runtimes >= 140 && runtimes < 190)								// ǰ��
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
										else if (runtimes > 330)												// �ص�x����������״̬
										{
												runtimes = 0;
												cruisestate = 1;
										}
								}
								else if (cruisestate == 4)											// �������ͷ״̬
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
								else if (cruisestate == 5)																			// �������ͷ״̬
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
				// ����ʹ�ã�ת90�ȣ�����ǰ���̶�����
				if (runflag)
				{
						runtimes++;
						if (runtimes > 0 && runtimes < 50)
						{
								firstspeedtemp = 500;							 // ��ת90��
								secondspeedtemp = 500;
								thirdspeedtemp = 500;
								fourthspeedtemp = 500; 
						}
						if (runtimes >= 50 && runtimes < 100)
						{
								firstspeedtemp = -500;							 // ��ת90��
								secondspeedtemp = -500;
								thirdspeedtemp = -500;
								fourthspeedtemp = -500; 
						}
						if (runtimes >= 100 && runtimes < 150)
						{
								firstspeedtemp = -200;							 // ǰ��
								secondspeedtemp = 200;
								thirdspeedtemp = 200;
								fourthspeedtemp = -200; 
						}
						if (runtimes >= 150 && runtimes < 200)
						{
								firstspeedtemp = 150;							 // ǰ��
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
				
					// ������ǰ����Ѱ�Ҹ��£�ȷ���ҵ���ת��ִ�У�ת��
				if (runflag == 1 && ModeFlag == 3)
				//if (runflag)
        {
						if (normalstate == 1)
						{
								if (analogvalue[10] > 1.5 && analogvalue[11] > 1.5)			// �෽����̽ͷ��û��̽�����棬��ǰ����֮���ĳ�ѭ����
								{
										runtimes = 0;														// ʱ������ 
										//direction = 1;
										//speed = 200;
										
										if (luxvalue[1] <= 500 && luxvalue[2] <= 500)
										{
												direction = 1;							// ǰ��
												speed = 200;
												if (luxvalue[0] <= 500 && luxvalue[3] >= 450)		//��Ǽ�ת��ǰһʱ��״̬��a = 0��������е����
												{
														preState = 0;
												}
												if (luxvalue[0] >= 500 && luxvalue[2] <= 500)
												{
														preState = 1;
												}
										}
										else        // ������
										{
												direction = 0;
											
												if (luxvalue[1] <= 450 && luxvalue[2] >= 500) 		//����΢ƫ������Ҫ����΢��
												{
														direction = 5;
														speed = 200;
												}
												else if (luxvalue[2] <= 450 && luxvalue[1] >= 500) 		//����΢ƫ������Ҫ����΢��
												{
														direction = 6;
														speed = 200;
												}
												else if (luxvalue[0] <= 450) 		//����ƫ������Ҫ�����
												{
														direction = 5;         // ԭ����ת
														speed = 250;
												}
												else if (luxvalue[3] <= 450) 		//����ƫ������Ҫ���ҵ�
												{
														direction = 6;        // ԭ����ת
														speed = 250;
												}
												//�����޷�̽�⵽������������Ҫ����ǰһʱ�̵���Ϣ��������ת
												else if (preState == 0)								//����й����������ת
												{
														direction = 5;         // ԭ����ת
														speed = 250;
												}
												else 							//�ұ��й����������ת
												{
														direction = 6;        // ԭ����ת
														speed = 250;
												}
										}

								}
						
								else if (analogvalue[10] <= 1.5)
								{
										normalstate = 0;
										leftonwork = 1;											// ������߹���״̬
										leftforwardstate = 1;									// ��ʼ�����ת
										runtimes = 0;
									  Wp_Usart2_SendChar(0x03);
								}
								else if (analogvalue[11] <= 1.5)
								{
										normalstate = 0;
										rightonwork = 1;										// �����ұ߹���״̬
										rightforwardstate = 1;									// ��ʼ�����ת
										runtimes = 0;
										Wp_Usart2_SendChar(0x03);
								}
						}
						else if (leftonwork == 1 || rightonwork == 1)				// ���/�ұ߹���״̬
						{
								if (leftforwardstate == 0 && rightforwardstate == 0)		// �Ƿ������ת/��ת����ɺ�������沿��
								{		
										runtimes++;
										if (runtimes > 0 && runtimes <= 3)						// ��������ʱ��
										{
												// ����ִ�л���
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
										if (runtimes > 130)														// ȷ�ϴ�������ֵ������ֵ,������Ӧ����ת�����ص�����״̬
										{
												if (analogvalue[12] > 3)				// һ��ʱ�����ȷ�ϴ�������ֵ�Ƿ������ֵ
												{
														if (leftonwork == 1)						// ����߹���
														{
																leftonwork = 0;
																leftbackstate = 1;					// �������˼���ת
														}
														else if (rightonwork == 1)			// ���ұ߹���
														{
																rightonwork = 0;
																rightbackstate = 1;					// �������˼���ת
														}
														runtimes = 0;
												}
												else															// ���û�гɹ����������
												{
														runtimes = 0;
												}
										}		
								}
						}
						
						if (leftforwardstate == 1)										// ��߿�ʼ���״̬
						{
								runtimes ++;
								if (runtimes <= 50)											// �ڼȶ�ʱ�����Լȶ��ٶ���ת����ת�˼ȶ��Ƕ�
								{
										direction = 5;							 // ��ת
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
						else if (rightforwardstate == 1)									// ��ת״̬
						{
								runtimes ++;
								if (runtimes <= 50)												// �ڼȶ�ʱ�����Լȶ��ٶ���ת����ת�˼ȶ��Ƕ�
								{
										direction = 6;						 // ��ת
										speed = 390;
								}
								/*else if (runtimes == 50)
								{
										firedis = 2* (distance - 10);					// ����Ϊ�˽ӽ�Ŀ�����Ҫ�ߵ�ʱ�䣬�ؾ����
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
						if (leftbackstate == 1)																	// ��߻ع�״̬
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
						else if (rightbackstate == 1)																	// �ұ߻ع�״̬
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
				
				
				
				
				//����ʹ�ã�Ŀ��׷�٣������ķ��
				if (ModeFlag == 1 && runflag == 1)
        {
							if (infrareddistance[0] <= 200	||			// Ŀ��Ͻ�
											infrareddistance[1] <= 200 || infrareddistance[2] <= 150
											|| infrareddistance[3] <= 150)		
							{
									direction = 0;
							     speed = 0;
//									firstspeedtemp = 0;											// ֹͣ
//									secondspeedtemp = 0;
//									thirdspeedtemp = 0;
//									fourthspeedtemp = 0; 
									
	//								if (counttime < 50)
	//								{
	//										counttime++;
	//								}
	//								else
	//							{
	//									if (infrareddistance[0] > preinfrareddistance[0] + 50)				//���������ƶ�
	//										{
	//												firstspeedtemp = 800;							 // ��ת
	//												secondspeedtemp = 800;
	//												thirdspeedtemp = 800;
	//												fourthspeedtemp = 800;  
	//										}
	//										else if (infrareddistance[3] > preinfrareddistance[3] + 50)				//�������ҷ��ƶ�
	//										{
	//												firstspeedtemp = -800;							 // ��ת
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
									if (infrareddistance[1] >= 400 && infrareddistance[2] >= 400 				// Ŀ����ǰ����Զ
											&& infrareddistance[0] >= infrareddistance[1] 
											&& infrareddistance[3] >= infrareddistance[2]
											&& infrareddistance[2] >= infrareddistance[1] - 200 
											&& infrareddistance[1] >= infrareddistance[2] - 200)		// ���߸�Զ
									{
//											firstspeedtemp = -2000;									// �Ͽ�ǰ��
//											secondspeedtemp = 2000;
//											thirdspeedtemp = 2000;
//											fourthspeedtemp = -2000;
											direction = 1;
							        speed = 800;
									}
									else if (infrareddistance[1] >= 200 && infrareddistance[2] >= 200 				// Ŀ����ǰ���Ͻ�
													&& infrareddistance[0] >= infrareddistance[1] 
											&& infrareddistance[3] >= infrareddistance[2]
											&& infrareddistance[2] >= infrareddistance[1] - 200 
											&& infrareddistance[1] >= infrareddistance[2] - 200)		// ���߸�Զ
									{
//											firstspeedtemp = -800;									// ����ǰ��
//											secondspeedtemp = 800;
//											thirdspeedtemp = 800;
//											fourthspeedtemp = -800;
											direction = 1;
											speed = 400;
									}
									else if (infrareddistance[0] < infrareddistance[1] 
													|| infrareddistance[1] < infrareddistance[2] - 200 
													|| infrareddistance[4] < infrareddistance[1] - 50)												// Ŀ�������
									{
//											firstspeedtemp = 1000;							 // ��ת
//											secondspeedtemp = 1000;
//											thirdspeedtemp = 1000;
//											fourthspeedtemp = 1000;  
											direction = 5;
											speed = 750;
									}
									else if (infrareddistance[3] < infrareddistance[2] 
													|| infrareddistance[2] < infrareddistance[1] - 200
													|| infrareddistance[5] < infrareddistance[2] - 50)												// Ŀ�����ұ�
									{
//											firstspeedtemp = -1000;							 // ��ת
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
				
        
        // ���ϲ��Գ��򣬽�ʹ��ǰ4�������ഫ�����������������ķ�ֺ���ͨ��
        if (runflag == 1 && ModeFlag == 2)
        {
            if (infrareddistance[1] >= 250 && infrareddistance[2] >= 250 
                && infrareddistance[0] >= 200 && infrareddistance[3] >= 200)
            {
								direction = 1;
							  speed = 600;
							  /*
                firstspeedtemp = -1000;                 // ǰ��
                secondspeedtemp = 1000;
                thirdspeedtemp = 1000;
                fourthspeedtemp = -1000;
							*/
            }
            else if (infrareddistance[1] <= 250)        // 2�ź��⴫����
            {
//                firstspeedtemp = 0;
//                secondspeedtemp = 0;
//                thirdspeedtemp = 0;
//                fourthspeedtemp = 0;
								direction = 0;
							  speed = 0;
                if (infrareddistance[2] >= 200)         // ��ת
                {
//                    firstspeedtemp = -1000;
//                    secondspeedtemp = -1000;
//                    thirdspeedtemp = -1000;
//                    fourthspeedtemp = -1000;
										direction = 6;
							      speed = 600;
                }
								//firstspeedtemp = -1300;         // ԭ����ת
                //secondspeedtemp = -700;
               //thirdspeedtemp = -1200;
                //fourthspeedtemp = 500;
//								firstspeedtemp = -1000;						// ��ת
//                secondspeedtemp = -1000;
//                thirdspeedtemp = -1000;
//                fourthspeedtemp = -1000; 
								direction = 6;
							  speed = 600;
            }
            else if (infrareddistance[2] <= 250)        // 3�ź��⴫����
            {
//                firstspeedtemp = 0;
//                secondspeedtemp = 0;
//                thirdspeedtemp = 0;
//                fourthspeedtemp = 0;	
								direction = 0;
							  speed = 0;
                if (infrareddistance[1] >= 200)         // ��ת
                {
//                    firstspeedtemp = 1000;
//                    secondspeedtemp = 1000;
//                    thirdspeedtemp = 1000;
//                    fourthspeedtemp = 1000;    
										direction = 5;
							      speed = 600;									
                }
								//firstspeedtemp = 700;         // ԭ����ת
                //secondspeedtemp = 1300;
                //thirdspeedtemp = -500;
                //fourthspeedtemp = 1200;
//								firstspeedtemp = 1000;					// ��ת
//                secondspeedtemp = 1000;
//                thirdspeedtemp = 1000;
//                fourthspeedtemp = 1000;
								   direction = 5;
							      speed = 600;
            }
            else if (infrareddistance[0] <= 250)        // ��ת
            {
//                firstspeedtemp = -1000;
//                secondspeedtemp = -1000;
//                thirdspeedtemp = -1000;
//                fourthspeedtemp = -1000;
							      direction = 6;
							      speed = 600;
            }
            else if (infrareddistance[3] <= 250)        // ��ת
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
				 // ����ʹ�ã�ѭ�����򣬽�ʹ���м�4���Ҷȴ������������������ķ�ֺ���ͨ��
        if (runflag)
        {
            if (luxvalue[1] <= 500 && luxvalue[2] <= 500)
            {
                direction = 1;							// ǰ��
                speed = 500;
								if (luxvalue[0] <= 500 && luxvalue[3] >= 450)		//��Ǽ�ת��ǰһʱ��״̬��a = 0��������е����
								{
										preState = 0;
								}
								if (luxvalue[0] >= 500 && luxvalue[2] <= 500)
								{
										preState = 1;
								}
            }
            else        // ������
            {
                direction = 0;
							
								if (luxvalue[1] <= 450 && luxvalue[2] >= 500) 		//����΢ƫ������Ҫ����΢��
								{
										direction = 5;
										speed = 300;
								}
								else if (luxvalue[2] <= 450 && luxvalue[1] >= 500) 		//����΢ƫ������Ҫ����΢��
								{
										direction = 6;
										speed = 300;
								}
								else if (luxvalue[0] <= 450) 		//����ƫ������Ҫ�����
								{
										direction = 5;         // ԭ����ת
										speed = 350;
								}
								else if (luxvalue[3] <= 450) 		//����ƫ������Ҫ���ҵ�
								{
										direction = 6;        // ԭ����ת
										speed = 350;
								}
								//�����޷�̽�⵽������������Ҫ����ǰһʱ�̵���Ϣ��������ת
								else if (preState == 0)								//����й����������ת
								{
										direction = 5;         // ԭ����ת
										speed = 350;
								}
								else 							//�ұ��й����������ת
								{
										direction = 6;        // ԭ����ת
										speed = 350;
								}
						}
				}
				*/
				
				/*
				//����ʹ�ã�ģ���������ǰ���Ŀ���
				if (runflag)
				{
						if (analogvalue[14] >= 3)
						{
								firstspeedtemp = -1000;                 // ǰ��
								secondspeedtemp = 1000;
								thirdspeedtemp = 1000;
								fourthspeedtemp = -1000;
						}
				}
				*/
				
				/*
				 // ѭ�����򣬽�ʹ���м�4���Ҷȴ������������������ķ�ֺ���ͨ��
        if (runflag)
        {
            if (luxvalue[1] <= 250 && luxvalue[2] <= 250)
            {
                firstspeedtemp = -500;                 // ǰ��
                secondspeedtemp = 500;
                thirdspeedtemp = 500;
                fourthspeedtemp = -500;
								if (luxvalue[0] <= 250 && luxvalue[3] >= 200)		//��Ǽ�ת��ǰһʱ��״̬��a = 0��������е����
								{
										preState = 0;
								}
								if (luxvalue[0] >= 200 && luxvalue[2] <= 250)
								{
										preState = 1;
								}
            }
            else        // ������
            {
                firstspeedtemp = 0;
                secondspeedtemp = 0;
                thirdspeedtemp = 0;
                fourthspeedtemp = 0;
							
								if (luxvalue[1] <= 200 && luxvalue[2] >= 250) 		//����΢ƫ������Ҫ����΢��
								{
										firstspeedtemp = 300;
										secondspeedtemp = 300;
										thirdspeedtemp = 300;
										fourthspeedtemp = 300;
								}
								else if (luxvalue[2] <= 200 && luxvalue[1] >= 250) 		//����΢ƫ������Ҫ����΢��
								{
										firstspeedtemp = -300;
										secondspeedtemp = -300;
										thirdspeedtemp = -300;
										fourthspeedtemp = -300;
								}
								else if (luxvalue[0] <= 200) 		//����ƫ������Ҫ�����
								{
										firstspeedtemp = 350;         // ԭ����ת
										secondspeedtemp = 350;
										thirdspeedtemp = 350;
										fourthspeedtemp = 350;
								}
								else if (luxvalue[3] <= 200) 		//����ƫ������Ҫ���ҵ�
								{
										firstspeedtemp = -350;         // ԭ����ת
										secondspeedtemp = -350;
										thirdspeedtemp = -350;
										fourthspeedtemp = -350;
								}
								//�����޷�̽�⵽������������Ҫ����ǰһʱ�̵���Ϣ��������ת
								else if (preState == 0)								//����й����������ת
								{
										firstspeedtemp = 350;         // ԭ����ת
										secondspeedtemp = 350;
										thirdspeedtemp = 350;
										fourthspeedtemp = 350;
								}
								else 							//�ұ��й����������ת
								{
										firstspeedtemp = -350;         // ԭ����ת
										secondspeedtemp = -350;
										thirdspeedtemp = -350;
										fourthspeedtemp = -350;
								}
						}
				}
				*/
				
        /*
        // ����ʹ�ã�ԭ���˶���ǰ�������ˣ���ƽ�ƣ���ƽ��
        if (runflag)
        {
            runtimes++;
            
            // ����ƽ̨�����ķ��
					
            if (runtimes > 0 && runtimes <= 50)
            {
                firstspeedtemp = -1000;         // ǰ��
                secondspeedtemp = 1000;
                thirdspeedtemp = 1000;
                fourthspeedtemp = -1000;
            }
            else if(runtimes > 50 && runtimes <= 100)
            {
                firstspeedtemp = 1000;          // ����
                secondspeedtemp = -1000;
                thirdspeedtemp = -1000;
                fourthspeedtemp = 1000;          
            }
            else if(runtimes > 100 && runtimes <= 150)
            {
                firstspeedtemp = 1000;          // ��ƽ��
                secondspeedtemp = 1000;
                thirdspeedtemp = -1000;
                fourthspeedtemp = -1000;
            }
            else if(runtimes > 150 && runtimes <= 200)
            {
                firstspeedtemp = -1000;         // ��ƽ��
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
						
						//����ԭ����ת
						
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
                firstspeedtemp = 700;         // ���ճɹ�ԭ����ת
                secondspeedtemp = 1300;
                thirdspeedtemp = -500;
                fourthspeedtemp = 1200;
            }
						
						
            if(runtimes > 200)
            {
                runtimes = 0;
            }
            
						
            // ����ȫ��ƽ̨
            
            if (runtimes > 0 && runtimes <= 50)
            {
                firstspeedtemp = -1000;         // ǰ��
                secondspeedtemp = 1000;
                thirdspeedtemp = 0;             
            }
            else if (runtimes > 50 && runtimes <= 100)
            {
                firstspeedtemp = 1000;          // ����
                secondspeedtemp = -1000;
                thirdspeedtemp = 0;             
            }
            else if (runtimes > 100 && runtimes <= 150)
            {
                firstspeedtemp = 1000;          // ԭ������ת
                secondspeedtemp = 1000;
                thirdspeedtemp = 1000;  
            }
            else if (runtimes > 150 && runtimes <= 200)
            {
                firstspeedtemp = -1000;         // ԭ������ת
                secondspeedtemp = -1000;
                thirdspeedtemp = -1000;  
            }
            else if (runtimes > 200 && runtimes <= 300)
            {
                VectorMove(90, 2000, 0);       // 90����ƽ��
                firstspeedtemp = motorspeedbuffer[0];
                secondspeedtemp = motorspeedbuffer[1];
                thirdspeedtemp = motorspeedbuffer[2];
            }
            else if (runtimes > 300 && runtimes <= 400)
            {
                VectorMove(-90, 2000, 0);      // -90����ƽ��
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
				if(speed > 1000)                     //���ٱ���
					speed = 1000;
				if (runflag)                         // ��direction��speed����������ٶȸ�ֵ
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
						firstspeedtemp = -speed;         // ǰ��
            secondspeedtemp = speed;
            thirdspeedtemp = speed;
            fourthspeedtemp = -speed;
					}
            
					else if(direction == 2)
					{
							firstspeedtemp = speed;          // ����
							secondspeedtemp = -speed;
							thirdspeedtemp = -speed;
							fourthspeedtemp = speed;          
						
					}
					else if(direction == 3)
					{
							firstspeedtemp = -speed;          // ����
							secondspeedtemp = -speed;
							thirdspeedtemp = speed;
							fourthspeedtemp = speed;
							
					}
					else if(direction == 4)
					{
							firstspeedtemp = speed;         // ����
							secondspeedtemp = speed;
							thirdspeedtemp = -speed;
							fourthspeedtemp = -speed;
						 
					}
					else if(direction == 5)
					{
							firstspeedtemp = speed;         	 // ��ת
							secondspeedtemp = speed;
							thirdspeedtemp = speed;
							fourthspeedtemp = speed;

					}
					else if(direction == 6)
					{
							firstspeedtemp = -speed;         	 // ��ת
							secondspeedtemp = -speed;
							thirdspeedtemp = -speed;
							fourthspeedtemp = -speed;
					}
				}
        
					
        if (++n >= 1)
        {
            n = 0;
            
            //  ������λ��ָ����ظ���λ�����ؽ�״̬
            //result = UpRobotSlaveRxPacket(&str_rx_buffer, &str_cmd);	        // ������λ����������֡
            if (result)
            {
                result = 0;
                
                /*  �������    */
                for (h = 0; h < 4; h++)                                         // �����ٶȲ�����4�����ģ�飬���ֽṹ�����ĸ�ģ����Ч
                {
                    In16(temph, str_cmd.parameter[1 + 8*h], str_cmd.parameter[0 + 8*h]);
                    In16(templ, str_cmd.parameter[3 + 8*h], str_cmd.parameter[2 + 8*h]);
                    In32(motor_data[0].sendspeed, templ, temph);
                }
                
            //  receiveresult = 1;                                              // �ɹ�����һ֡��λ��Э�����־
            }
            
            /*
            // ���͵�һ�����ģ��
            if (receiveresult)
                UpdataMotorCmdPraseSendBuf(0x01);                               // ���жϷ��ͷ�ʽ��֯����
            else
                UpMotorNouseCmdPraseSendBuf(0x01);
            UART3TXEN;
            Wp_DelayUs(2);
            UpMotorSlaveTxPacket(&str_motor_reply);                             // ��������
            Wp_DelayUs(1);
            UART3RXEN;
            Wp_DelayUs(3000);                                                   // ��ʱ2.5ms����
            // �������ؽڷ��ص�����֡�������͸�ģ��PDOЭ���
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // ������������������֡
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
            
            // ���͵ڶ������ģ��
            if (receiveresult)
                UpdataMotorCmdPraseSendBuf(0x02);                               // ���жϷ��ͷ�ʽ��֯����
            else
                UpMotorNouseCmdPraseSendBuf(0x02);
            UART3TXEN;
            Wp_DelayUs(2);
            UpMotorSlaveTxPacket(&str_motor_reply);                             // ��������
            Wp_DelayUs(1);
            UART3RXEN;
            Wp_DelayUs(3000);                                                   // ��ʱ2.5ms����
            // �������ؽڷ��ص�����֡�������͸�ģ��PDOЭ���
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // ������������������֡
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
            
            // ���͵��������ģ��
            if (receiveresult)
                UpdataMotorCmdPraseSendBuf(0x03);                               // ���жϷ��ͷ�ʽ��֯����
            else
                UpMotorNouseCmdPraseSendBuf(0x03);
            UART3TXEN;
            Wp_DelayUs(2);
            UpMotorSlaveTxPacket(&str_motor_reply);                             // ��������
            Wp_DelayUs(1);
            UART3RXEN;
            Wp_DelayUs(3000);                                                   // ��ʱ2.5ms����
            // �������ؽڷ��ص�����֡�������͸�ģ��PDOЭ���
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // ������������������֡
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
            
            // ���͵��ĸ����ģ��
            if (receiveresult)
                UpdataMotorCmdPraseSendBuf(0x04);                               // ���жϷ��ͷ�ʽ��֯����
            else
                UpMotorNouseCmdPraseSendBuf(0x04);
            UART3TXEN;
            Wp_DelayUs(2);
            UpMotorSlaveTxPacket(&str_motor_reply);                             // ��������
            Wp_DelayUs(1);
            UART3RXEN;
            Wp_DelayUs(3000);                                                   // ��ʱ2.5ms����
            // �������ؽڷ��ص�����֡�������͸�ģ��PDOЭ���
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // ������������������֡
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
                // ����ִ��ָ��
                ActionMotorCmdPraseSendBuf();                                   // ���жϷ��ͷ�ʽ��ִ֯��ָ��
                UART3TXEN;
                Wp_DelayUs(2);
                UpMotorSlaveTxPacket(&str_motor_reply);                         // ��������
                Wp_DelayUs(1);
                UART3RXEN;
                
                receiveresult = 0;
            }
            */
            
            Wp_SetMotorSpeed(0x01, firstspeedtemp);
            Wp_DelayUs(3000);                                                   // ��ʱ2.5ms����
            // �������ؽڷ��ص�����֡�������͸�ģ��PDOЭ���
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // ������������������֡
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
            Wp_DelayUs(3000);                                                   // ��ʱ2.5ms����
            // �������ؽڷ��ص�����֡�������͸�ģ��PDOЭ���
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // ������������������֡
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
            Wp_DelayUs(3000);                                                   // ��ʱ2.5ms����
            // �������ؽڷ��ص�����֡�������͸�ģ��PDOЭ���
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // ������������������֡
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
            Wp_DelayUs(3000);                                                   // ��ʱ2.5ms����
            // �������ؽڷ��ص�����֡�������͸�ģ��PDOЭ���
            result = UpMotorSlaveRxPacket(&motor_rx_buffer, &str_motor_cmd);    // ������������������֡
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
            
            // �����еĵ�����Ͷ��ɹ����ٷ���ִ������
            if (fourthsendok & thirdsendok & secondsendok & firstsendok)
            {
                fourthsendok = 0;
                thirdsendok = 0;
                secondsendok = 0;
                firstsendok = 0;
                
                Wp_ActiomMotorMode();                               // ִ��ָ��
            }
        }
        
        
        /*  ���Խ׶Σ�50ms�ŷ�����    */
		if (++h >= 1)
        {	
            h = 0;
            
            gpioinputvalue = Wp_GetInputValue();                    // ������IO�ڵ�ֵ
            gpiooutputvalue = Wp_GetOutputValue();                  // �����IO�ڵ�ֵ
            Wp_GetAdcVoltageValue();                                // �����ͨ����ѹ
            powervalue = Wp_FilterPower();					        // �����ص�ѹ���˲�
            powervalueint = powervalue * 1000;
            Wp_GetMpu6050Dmp();								        // ��ȡ��̬��Ϣ
            /*
            // ������λ����Ϣ
            Wp_UpdataPcAlltiOutputSendBuf();                        // ��̬��Ϣ
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcGpioInputSendBuf();                          // ����˿�
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcGpioOutputSendBuf();                         // ����˿�
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcPowerValueSendBuf();                         // ��Դ��ѹ
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcAdcSendBuf(1);                               // ADC��һ��
            UpRobotSlaveTxPacket(&str_reply);
            Wp_UpdataPcAdcSendBuf(2);                               // ADC�ڶ���
            UpRobotSlaveTxPacket(&str_reply);            
            Wp_UpdataPcAdcSendBuf(3);                               // ADC������
            UpRobotSlaveTxPacket(&str_reply);
            
            Wp_UpdataPcMotorPraseSendBuf(1);                        // ��һ�����ģ��
            UpRobotSlaveTxPacket(&str_reply);
            Wp_UpdataPcMotorPraseSendBuf(2);                        // �ڶ������ģ��
            UpRobotSlaveTxPacket(&str_reply);
            Wp_UpdataPcMotorPraseSendBuf(3);                        // ���������ģ��
            UpRobotSlaveTxPacket(&str_reply);
            Wp_UpdataPcMotorPraseSendBuf(4);                        // ���ĸ����ģ��
            UpRobotSlaveTxPacket(&str_reply);
        //  Wp_UpdataPcCmdPraseSendBuf();                           // ���ݴ�������е��ģ�鷵������
        //  UpRobotSlaveTxPacket(&str_reply);                       // �������ݸ���λ��            
            */
		}
	}
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
