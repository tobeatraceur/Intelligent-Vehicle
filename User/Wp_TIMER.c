/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_TIMER.c
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				Timer��ʼ�����;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				Timer��ʼ�����;
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
#include "Wp_TIMER.h"


u32 g_UP_iTimerTime[4] = {0};			// ��ʱʱ�䣬usΪ��λ

u16 g_UP_TimerCCRVal_L16[4] = {0};		// Timer�Ƚ�ͨ���Ƚ�ֵ��16λ
u16 g_UP_TimerCCRVal_H16[4] = {0};		// Timer�Ƚ�ͨ���Ƚ�ֵ��16λ

u16 g_UP_TempCCRVal_L16[4] = {0};		// Timer�Ƚ�ͨ���Ƚ�ֵ��16λ
u16 g_UP_TempCCRVal_H16[4] = {0};		// Timer�Ƚ�ͨ���Ƚ�ֵ��16λ


/*************************************************************************************************************
** ��������:			Wp_Timer_InitParameters
**
** ��������:		    ��ʼ����ز���;
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
static void Wp_Timer_InitParameters(void)
{

}


/*************************************************************************************************************
** ��������:			Wp_UserTimerConfigure
**
** ��������:			Timer3��ʼ������;
** 						Timer3��Ϊ�û���ʱ��ʹ��;
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
void Wp_UserTimerConfigure(void)
{
	// Timer3��4������Ƚ���4·��ʱ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	Wp_Timer_InitParameters();                                      // ������ʼ��

	if (!g_UP_bTimerIT[0] && !g_UP_bTimerIT[1] && !g_UP_bTimerIT[2] && !g_UP_bTimerIT[3])
		return;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	        // ʹ�ܶ�ʱ��ʱ��

	// Timer3��������
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;						// 72��Ƶ��1us
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 65535;						// ����ֵ65535
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         // ����Ƶ
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;              // ���������Timer1��Timer8���ڣ�������֮
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	// �Ƚ�ͨ������
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;       	// ����ȽϷ�����ģʽ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// ����Ϊ�����ߵ�ƽ��Ч
	
	TIM_OCInitStructure.TIM_Pulse = g_UP_iTimerTime[0]>65535?65535:g_UP_iTimerTime[0]; 	//�Ƚ�ʱ��
	if (g_UP_bTimerIT[0])                                           // �ж��Ƿ����ö�ʱ��
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);					// ͨ��1
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_iTimerTime[1]>65535?65535:g_UP_iTimerTime[1]; 	//�Ƚ�ʱ��
	if (g_UP_bTimerIT[1])                                           // �ж��Ƿ����ö�ʱ��
		TIM_OC2Init(TIM3, &TIM_OCInitStructure); 					// ͨ��2
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_iTimerTime[2]>65535?65535:g_UP_iTimerTime[2]; 	//�Ƚ�ʱ��
	if (g_UP_bTimerIT[2])                                           // �ж��Ƿ����ö�ʱ��
		TIM_OC3Init(TIM3, &TIM_OCInitStructure); 					// ͨ��3
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_iTimerTime[3]>65535?65535:g_UP_iTimerTime[3]; 	//�Ƚ�ʱ��
	if (g_UP_bTimerIT[3])                                           // �ж��Ƿ����ö�ʱ��
		TIM_OC4Init(TIM3, &TIM_OCInitStructure); 					// ͨ��4

	// Ԥ����������ж�λ
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4);

	// �Ƚ��ж�ʹ��
	if (g_UP_bTimerIT[0]) 
		TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);                     // �Ƚ��ж�ʹ��
	if (g_UP_bTimerIT[1]) 
		TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);                     // �Ƚ��ж�ʹ��
	if (g_UP_bTimerIT[2]) 
		TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);                     // �Ƚ��ж�ʹ��
	if (g_UP_bTimerIT[3]) 
		TIM_ITConfig(TIM3, TIM_IT_CC4, ENABLE);                     // �Ƚ��ж�ʹ��

	TIM_Cmd(TIM3, ENABLE);	                                        // TIM3����ʹ��
}


/*************************************************************************************************************
** ��������:			TimerHadler
**
** ��������:		    ����Timer�ж���ں���;
** 						
**					    
** �������:			u32 timerchannel;
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
void TimerHadler(u32 timerchannel)
{
	if (timerchannel == TIMER_CHANNEL0)	 		    // �ж�����һ·��ʱ���ж�
	{
		// �жϺ���
	}
	else if (timerchannel == TIMER_CHANNEL1)
	{   
		// �жϺ���
	}
	else if (timerchannel == TIMER_CHANNEL2)
	{
		// �жϺ���
	}
	else if (timerchannel == TIMER_CHANNEL3)
	{
		// �жϺ���
	}
}


/*************************************************************************************************************
** ��������:			Wp_User_TimerPro
**
** ��������:			�û���ʱ�����жϷ�����;
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
void Wp_User_TimerPro(void)
{
	// �Ƚ�ͨ��1�ж�
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
	{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
		
		if (g_UP_TempCCRVal_H16[0] == 0 && g_UP_TempCCRVal_L16[0] == 0)
		{
			g_UP_TempCCRVal_L16[0] = g_UP_TimerCCRVal_L16[0];
			g_UP_TempCCRVal_H16[0] = g_UP_TimerCCRVal_H16[0];
            
			if (g_UP_TimerITAddress)
				(*((void(*)(u8))g_UP_TimerITAddress))(TIMER_CHANNEL0);
		}
		if (g_UP_TempCCRVal_H16[0] != 0)
		{
			TIM3->CCR1 += 65535;
			g_UP_TempCCRVal_H16[0]--;
		}
		else if (g_UP_TempCCRVal_L16[0] != 0)
		{
			TIM3->CCR1 += g_UP_TempCCRVal_L16[0];
			g_UP_TempCCRVal_L16[0] = 0;
		}
	}
	// �Ƚ�ͨ��2�ж�
	else if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
	{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
		
		if (g_UP_TempCCRVal_H16[1] == 0 && g_UP_TempCCRVal_L16[1] == 0)
		{
			g_UP_TempCCRVal_L16[1] = g_UP_TimerCCRVal_L16[1];
			g_UP_TempCCRVal_H16[1] = g_UP_TimerCCRVal_H16[1];
			if (g_UP_TimerITAddress)
				(*((void(*)(u8))g_UP_TimerITAddress))(TIMER_CHANNEL1);
		}
		if (g_UP_TempCCRVal_H16[1] != 0)
		{
			TIM3->CCR2 += 65535;
			g_UP_TempCCRVal_H16[1]--;
		}
		else if (g_UP_TempCCRVal_L16[1] != 0)
		{
			TIM3->CCR2 += g_UP_TempCCRVal_L16[1];
			g_UP_TempCCRVal_L16[1] = 0;
		}
	}
	// �Ƚ�ͨ��3�ж�
	else if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
	{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
		if (g_UP_TempCCRVal_H16[2] == 0 && g_UP_TempCCRVal_L16[2] == 0)
		{
			g_UP_TempCCRVal_L16[2] = g_UP_TimerCCRVal_L16[2];
			g_UP_TempCCRVal_H16[2] = g_UP_TimerCCRVal_H16[2];
			if (g_UP_TimerITAddress)
				(*((void(*)(u8))g_UP_TimerITAddress))(TIMER_CHANNEL2);
		}
		if (g_UP_TempCCRVal_H16[2] != 0)
		{
			TIM3->CCR3 += 65535;
			g_UP_TempCCRVal_H16[2]--;
		}
		else if (g_UP_TempCCRVal_L16[2] != 0)
		{
			TIM3->CCR3 += g_UP_TempCCRVal_L16[2];
			g_UP_TempCCRVal_L16[2] = 0;
		}
	}
	// �Ƚ�ͨ��4�ж�
	else if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
	{
	    TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);
		if (g_UP_TempCCRVal_H16[3] == 0 && g_UP_TempCCRVal_L16[3] == 0)
		{
			g_UP_TempCCRVal_L16[3] = g_UP_TimerCCRVal_L16[3];
			g_UP_TempCCRVal_H16[3] = g_UP_TimerCCRVal_H16[3];
			if (g_UP_TimerITAddress)
				(*((void(*)(u8))g_UP_TimerITAddress))(TIMER_CHANNEL3);
		}
		if (g_UP_TempCCRVal_H16[3] != 0)
		{
			TIM3->CCR4 += 65535;
			g_UP_TempCCRVal_H16[3]--;
		}
		else if (g_UP_TempCCRVal_L16[3] != 0)
		{
			TIM3->CCR4 += g_UP_TempCCRVal_L16[3];
			g_UP_TempCCRVal_L16[3] = 0;
		}
	}
}


/*************************************************************************************************************
** ��������:			Wp_UserTimerEnableIT
**
** ��������:			ʹ�ܼ�ʱ���ж�;
** 						
**					    
** �������:			u32 TimerChannel, u32 Time_us;
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
void Wp_UserTimerEnableIT(u32 TimerChannel, u32 Time_us)
{
	if (TimerChannel > 3 || Time_us == 0)
		return;
    
	g_UP_bTimerIT[TimerChannel] = TRUE;															// ������ʱ����־��λ
	g_UP_iTimerTime[TimerChannel] = Time_us;													// ��ʼ���Ƚϼ����Ĵ�����ֵ
	g_UP_TempCCRVal_L16[TimerChannel] = g_UP_TimerCCRVal_L16[TimerChannel] = Time_us;			// ��ʼ���ȽϼĴ���
	g_UP_TempCCRVal_H16[TimerChannel] = g_UP_TimerCCRVal_H16[TimerChannel] = Time_us >> 16;		// ��ʼ���ȽϼĴ���
}


/*************************************************************************************************************
** ��������:			Wp_UserTimerDisableIT
**
** ��������:			���ܼ�ʱ���ж�;
** 						
**					    
** �������:			u32 TimerChannel;
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
void Wp_UserTimerDisableIT(u32 TimerChannel)
{
	if (TimerChannel > 3)                       // 0~3ͨ���Ƚ�ʹ���ж�
		return;
    
	g_UP_bTimerIT[TimerChannel] = FALSE;
    
	// �Ƚ��жϽ���
	if (!g_UP_bTimerIT[0]) 
		TIM_ITConfig(TIM3, TIM_IT_CC1, DISABLE);
	if (!g_UP_bTimerIT[1]) 
		TIM_ITConfig(TIM3, TIM_IT_CC2, DISABLE);
	if (!g_UP_bTimerIT[2]) 
		TIM_ITConfig(TIM3, TIM_IT_CC3, DISABLE);
	if (!g_UP_bTimerIT[3]) 
		TIM_ITConfig(TIM3, TIM_IT_CC4, DISABLE);	
}


/*************************************************************************************************************
** ��������:			Wp_UserTimerSetHadler
**
** ��������:			���ö�ʱ���ж���ں���;
** 						
**					    
** �������:			void (*ApplicationAddress)(u32);
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
void Wp_UserTimerSetHadler(void (*ApplicationAddress)(u32))
{
	if (ApplicationAddress != 0)
		g_UP_TimerITAddress = (u32)ApplicationAddress;
}


/*************************************************************************************************************
** ��������:			Wp_Timer2Configure
**
** ��������:			Timer2��ʼ������;
** 						50ms�ŷ�����;
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
void Wp_Timer2Configure(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	u16 CCR1_Val = 5000;                                            // ��ʼ���Ƚ�ͨ��1�Ƚ�ֵ
	
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);            // TIMER2 clock enable
	
	// Timer2��������
	TIM_TimeBaseStructure.TIM_Period = 50000;						// ����ֵ��50ms�ŷ�����
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;    					// Ԥ��Ƶ,��ֵ+1Ϊ��Ƶ�ĳ���
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;  				// ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 	// ���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// �Ƚ�ͨ��1����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;      		// ����ȽϷ�����ģʽ
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// ����Ϊ��
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);				// ��ֹOC1��װ��,��ʵ����ʡ�����,��ΪĬ����4·������װ��
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);                             // ʹ��Ԥװ��
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1 | TIM_IT_Update);        // Ԥ����������ж�λ
	
	TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_Update, ENABLE);         // 1��ͨ��������������ж�
	
	TIM_Cmd(TIM2, ENABLE);                                          // ����TIMER2��ʼ����
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
