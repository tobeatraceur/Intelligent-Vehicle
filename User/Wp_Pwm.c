/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_Pwm.c
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				PWM�����ļ�;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				PWM�����ļ�;
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
#include "Wp_Pwm.h"


u32 g_UP_PWMFrequency[WP_PWM_NUM] = {0};	// PWMƵ��
u16 g_UP_PWMDutyTime[WP_PWM_NUM] = {0};		// PWMռ�ձ�

u8 g_UP_bPWM_L[WP_PWM_NUM] = {0};			// PWMͨ����ǰ�Ƿ��ǵ͵�ƽ

u16 g_UP_PWMCCRVal_H[WP_PWM_NUM] = {0};		// PWM�ߵ�ƽʱ�䣬�ߵ�ƽʱ���ʼ����ʱ���������
u16 g_UP_PWMCCRVal_L[WP_PWM_NUM] = {0};		// PWM�͵�ƽʱ��

u8 g_UP_bPWMMode[WP_PWM_NUM];				// �˿�ģʽ��PWM��IO-OUT���ߵ�ƽΪPWMģʽ���͵�ƽΪIO-OUTģʽ
u8 g_UP_PWMIOVal[WP_PWM_NUM];				// IOģʽ�˿ڵ�ƽ�������ƽֵ���ж�����ߵ�ƽ���ǵ͵�ƽ


/*************************************************************************************************************
** ��������:			Wp_PwmInitParameters
**
** ��������:			PWM������ʼ������;
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
static void Wp_PwmInitParameters(void)
{
	u8 i = 0;
    
	for(i = 0; i < WP_PWM_NUM; i++)
	{
		g_UP_PWMFrequency[i] = 1000;            // Ƶ�����ã�2KHz
        
		g_UP_PWMCCRVal_H[i] = 10;               // PWM�ߵ�ƽ��ʱ��
		g_UP_PWMCCRVal_L[i]	= 1990;             // PWM�͵�ƽ��ʱ��
        
		g_UP_bPWM_L[i] = 0;                     // ��ʼ���趨Ϊ�͵�ƽ�����־��PWM�˿�����͵�ƽ
        
		g_UP_PWMDutyTime[i] = 2048;             // ռ�ձ�����
	}
}


/*************************************************************************************************************
** ��������:			Wp_PwmConfigure
**
** ��������:			PWM��ʼ������;
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
void Wp_PwmConfigure(void)	
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;                  // Timer4��4������Ƚ���4·PWM
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	Wp_PwmInitParameters();                                         // ������ʼ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);           // ʹ�ܶ˿�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);            // ʹ�ܶ�ʱ��ʱ��
	
	WP_PWM0_L;                                                      // GPIO���ã���ʼ��PWM�˿�����͵�ƽ
	WP_PWM1_L;
	WP_PWM2_L;
	WP_PWM3_L;
    
    // PB6��PB7��PB8��PB9����Ϊ����������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			        // ���⸴�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		        // 50Mʱ���ٶ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
	// Timer4��������
	TIM_DeInit(TIM4);
	TIM_TimeBaseStructure.TIM_Prescaler = 36-1;						// 36��Ƶ��2MHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 65535;						// ����ֵ65535
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         // ����Ƶ
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;              // ��Timer1��Timer8�д��������֮
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    
	// �Ƚ����ͨ������
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle; 			// �ȽϷ�תģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	// ����ͨ����Ч
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;// ����ͨ����Ч
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_PWMCCRVal_H[0]; 			// �Ƚϣ��͵�ƽ��ת��ʱ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		// �������
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;     // �����˵ļ���  
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);						// ͨ��1
    
	TIM_OCInitStructure.TIM_Pulse = g_UP_PWMCCRVal_H[1];
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 						// ͨ��2
	TIM_OCInitStructure.TIM_Pulse = g_UP_PWMCCRVal_H[2];
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 						// ͨ��3
	TIM_OCInitStructure.TIM_Pulse = g_UP_PWMCCRVal_H[3];
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 						// ͨ��4
	
	TIM_CtrlPWMOutputs(TIM4, ENABLE);                               // TIM4ʹ��PWM���
	
//	TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);  // �Ƚ��ж�ʹ�ܣ�Ĭ�ϲ�ʹ�ܣ�
	
	TIM_Cmd(TIM4, ENABLE);                                          // TIM4����ʹ��
}


/*************************************************************************************************************
** ��������:			Wp_PwmEnable
**
** ��������:			ʹ��PWMģʽ���;
** 						ʹ��PWM�ж�;
**					    
** �������:			u8 Channel, FunctionalState NewState;
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
void Wp_PwmEnable(u8 Channel, FunctionalState NewState)
{
	if (Channel > WP_PWM_NUM)
		return;
    
	g_UP_bPWMMode[Channel] = (NewState == DISABLE)?0:1;     // ʹ��PWM�ж�
    
	if (g_UP_bPWMMode[Channel])		                        // �������ΪPWMģʽ��ʹ����Ӧ�ж�
		TIM_ITConfig(TIM4, 0x02 << Channel, ENABLE);
	else
		TIM_ITConfig(TIM4, 0x02 << Channel, DISABLE);
}


/*************************************************************************************************************
** ��������:			Wp_PwmTimerPro
**
** ��������:			�жϷ�����;
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
void Wp_Pwm_TimerPro(void)
{
	// �Ƚ�ͨ��1�ж�
	if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
	{
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
        
		TIM4->CCR1 += g_UP_bPWM_L[0]?g_UP_PWMCCRVal_L[0]:g_UP_PWMCCRVal_H[0];
		g_UP_bPWM_L[0] = !g_UP_bPWM_L[0];
	}
    
	// �Ƚ�ͨ��2�ж�
	else if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
	{
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
        
	    TIM4->CCR2 += g_UP_bPWM_L[1]?g_UP_PWMCCRVal_L[1]:g_UP_PWMCCRVal_H[1];
		g_UP_bPWM_L[1] = !g_UP_bPWM_L[1];
	}
    
	// �Ƚ�ͨ��3�ж�
	else if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
	{
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
        
	    TIM4->CCR3 += g_UP_bPWM_L[2]?g_UP_PWMCCRVal_L[2]:g_UP_PWMCCRVal_H[2];
		g_UP_bPWM_L[2] = !g_UP_bPWM_L[2];
	}
    
	// �Ƚ�ͨ��4�ж�
	else if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)
	{
	    TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
        
	    TIM4->CCR4 += g_UP_bPWM_L[3]?g_UP_PWMCCRVal_L[3]:g_UP_PWMCCRVal_H[3];
		g_UP_bPWM_L[3] = !g_UP_bPWM_L[3];
	}
    else
    {
        
    }
}


/*************************************************************************************************************
** ��������:			Wp_Pwm_SetCCR
**
** ��������:			����ռ�ձȶ�Ӧ�ļ�ʱ������ֵ;
** 						
**					    
** �������:			u8 Channel;
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
static void Wp_Pwm_SetCCR(u8 Channel)	
{
	if (Channel > WP_PWM_NUM)
		return;
    
	g_UP_PWMCCRVal_H[Channel] = (2000000/g_UP_PWMFrequency[Channel]*g_UP_PWMDutyTime[Channel])>>12; 	    // �ߵ�ƽʱ��
	g_UP_PWMCCRVal_L[Channel] = (2000000/g_UP_PWMFrequency[Channel]*(4095-g_UP_PWMDutyTime[Channel]))>>12;	// �͵�ƽʱ��
}


/*************************************************************************************************************
** ��������:			Wp_PwmSetDutyTime
**
** ��������:			����ռ��ʱ��0~4095;
** 						
**					    
** �������:			u8 Channel, u16 DutyTime;
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
void Wp_PwmSetDutyTime(u8 Channel, u16 DutyTime)	
{
	if (Channel > WP_PWM_NUM || DutyTime > 4095)
		return;
    
	g_UP_PWMDutyTime[Channel] = DutyTime;
	Wp_Pwm_SetCCR(Channel);
}


/*************************************************************************************************************
** ��������:			Wp_PwmSetFrequency
**
** ��������:			����Ƶ��;
** 						
**					    
** �������:			u8 Channel, u32 Frequency;
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
void Wp_PwmSetFrequency(u8 Channel, u32 Frequency)
{
	if (Channel > WP_PWM_NUM)
		return;
    
	g_UP_PWMFrequency[Channel] = Frequency;
	Wp_Pwm_SetCCR(Channel);
}


/*************************************************************************************************************
** ��������:			Wp_PwmSetIO
**
** ��������:			����IO���;
** 						
**					    
** �������:			u8 Channel, u8 Value;
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
void Wp_PwmSetIO(u8 Channel, u8 Value)
{
	if (Channel > WP_PWM_NUM || Value > 1)
		return;
    
	g_UP_PWMIOVal[Channel] = Value;
    
	if (g_UP_bPWMMode[Channel] == 1)                    // �����PWMģʽ����ʹ�ܶ�ʱ���Ƚ��ж�
		TIM_ITConfig(TIM4, 0x02 << Channel, DISABLE);
    
	g_UP_bPWMMode[Channel] = 0;                         // 0ΪPWM������IO-OUTģʽ
    
	switch(Channel)								        // ����Ӧ�Ķ˿����ó���Ҫ�ĵ�ƽ
	{
		case 0: 
            Value ? WP_PWM0_H : WP_PWM0_L;
        
            break;
		case 1: 
            Value ? WP_PWM1_H : WP_PWM1_L;
        
            break;
		case 2: 
            Value ? WP_PWM2_H : WP_PWM2_L;
        
            break;
		case 3: 
            Value ? WP_PWM3_H : WP_PWM3_L;
        
            break;
		default: 
            break;
	}
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
