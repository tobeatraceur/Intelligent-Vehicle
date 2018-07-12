/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_Key.c
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				������������;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				������������;
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
#include "Wp_Key.h"


/*************************************************************************************************************
** ��������:			key_delay1ms
**
** ��������:			����ר����ʱ���������һ����;
** 						
**					    
** �������:			uint8_t nms;
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
#ifndef  KEY_FIXED_PERIOD
static void key_delay1ms(uint8_t nms)
{
	unsigned int i = 0;
    
	for(; nms > 0; nms--)
    {
		for(i = 400; i > 0; i--);
    }
}
#endif


/*************************************************************************************************************
** ��������:			KeyDown_state
**
** ��������:			��ⰴ�������ƽ״̬;
** 						���°�������͵�ƽ��û�а��°�������ߵ�ƽ;
**					    
** �������:			void;
** ����ֵ:				uint8_t;
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
static u8 KeyUp_state(void)
{
    if (1 == CHECKKEYUP)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static u8 KeyDown_state(void)
{
    if (1 == CHECKKEYDOWN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static u8 KeyBack_state(void)
{
    if (1 == CHECKKEYBACK)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
static u8 KeyOk_state(void)
{
    if (1 == CHECKKEYOK)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/*************************************************************************************************************
** ��������:			Wp_KeyObjectInit
**
** ��������:			��ʼ��һ����������;
** 						key_this��ָ�򰴼������ָ��;
**					    getState��״̬��⺯��ָ��;
**
** �������:			key_inf_type* key_this, uint8_t(*getState)(void);
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
void Wp_KeyObjectInit(key_inf_type* key_this, u8(*getState)(void))
{
	key_this->get_state = getState;     // ����״̬��ȡ��ں���
    
	key_this->state = KEY_DOWN;         // ��ʼ��Ϊ����������Ч
	key_this->times	= 0;                // �������´���
    
	#if (USER_DATA_EN == 1)             // ��ʹ���û�����
        key_this->value	= 0;
	#endif
    
	#if (KEY_USE_SEM == 1)              // ��ʹ�ܰ��������ź���
        key_this->sem = KEY_SEM_FREE;
	#endif
    
	#ifdef  KEY_FIXED_PERIOD
        key_this->time_ms = 0;	        // ���ڹ̶����ڵ���״̬���º����ļ�ʱ
	#endif
}


/*************************************************************************************************************
** ��������:			Key_RefreshState
**
** ��������:			���°���״̬;
** 						����Ƶ�ʣ����㰴���������Ƶ�ʣ�һ��Ҫ�����Ƶ����20HZ����;
**					    
** �������:			key_inf_type* theKey;
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
void Wp_KeyRefreshState(key_inf_type* theKey)
{
	#if KEY_USE_SEM == 1
	if (KEY_SEM_FREE == theKey->sem)
	{
		theKey->sem = KEY_SEM_USING;
	#endif
		switch (theKey->state)
		{
			case KEY_UP:
			{
				if ((*(theKey->get_state))())                // ��ȡ��ƽ״̬
				{
					#ifdef  KEY_FIXED_PERIOD
                        theKey->time_ms = 0;
                        theKey->state = KEY_DOWN_WOBBLE;    // ����������ʱ
					#else
					theKey->state = KEY_DOWN_WOBBLE;
                    
					key_delay1ms(KEY_WOBBLE_TIME);          // ȥ����
                    
					if ((*(theKey->get_state))())
					{
						theKey->state = KEY_DOWN;
					}
					#endif
				}
			}
            break;
			
			#ifdef  KEY_FIXED_PERIOD
			case KEY_DOWN_WOBBLE:
			{
				theKey->time_ms += KEY_FIXED_PERIOD;
				if(theKey->time_ms >=KEY_WOBBLE_TIME)
				{
					if((*(theKey->get_state))())
					{
						theKey->state = KEY_DOWN;
					}
                    else
					{
						theKey->state = KEY_UP;
					}
				}
			}
            break;
			#endif

			case KEY_DOWN:
			{
				if ((*(theKey->get_state))() == 0)
				{
					#ifdef  KEY_FIXED_PERIOD
                        theKey->time_ms = 0;
                        theKey->state = KEY_UP_WOBBLE;      // ����������ʱ
					#else
					key_delay1ms(KEY_WOBBLE_TIME);
                    
					if ((*(theKey->get_state))() == 0)
					{
						theKey->state = KEY_UP;
						theKey->times++;
						if (theKey->times > 250)
                        {
							theKey->times = 1;             // ���������250��û����
                        }
					}
					#endif
				}
			}
            break;

			#ifdef  KEY_FIXED_PERIOD
			case KEY_UP_WOBBLE:
			{
				theKey->time_ms += KEY_FIXED_PERIOD;
				if(theKey->time_ms >= KEY_WOBBLE_TIME)
				{
					if(0 == (*(theKey->get_state))())
					{
						theKey->state = KEY_UP;
						theKey->times++;
						if (theKey->times > 250)
							theKey->times = 250;            // ���������250��û����
					}
                    else
					{
						theKey->state = KEY_DOWN;
					}
				}
			}
            break;
			#endif
		}
    
	#if KEY_USE_SEM == 1
		theKey->sem = KEY_SEM_FREE;
	}
	#endif
}


/*************************************************************************************************************
** ��������:			Key_AccessTimes
**
** ��������:			�԰���ֵ�ķ��ʣ���Ҫ�Ƿ�װ���ź����ķ���;
**                      option��ѡ��;
**                      ���access_type���壬��Ҫ��read��write���಻�ɰ�λ��write��3����������ɰ�λ��;
**					    ���ֻ�Ƕ�ȡ���ö�option��������;
**                      �����write���͵ķ��ʣ���ҪKEY_ACCESS_WRITEλ���ϡ�KEY_ACCESS_CLEAR�������������е�һ��;
** 						����Ƶ�ʣ����㰴���������Ƶ�ʣ�һ��Ҫ�����Ƶ����20HZ����;
**					    ����ֵ��->times��ֵ;
**
** �������:			key_inf_type* theKey, access_type option;
** ����ֵ:				uint8_t;
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
u8 Wp_KeyAccessTimes(key_inf_type* theKey, access_type option)
{
	u8 times_temp = 0;
	
	#if KEY_USE_SEM == 1
	if(KEY_SEM_FREE == theKey->sem)
	{
		theKey->sem = KEY_SEM_USING;
	#endif
	
        if ((option & KEY_ACCESS_WRITE) == KEY_ACCESS_WRITE)
        {
            if ((option & KEY_ACCESS_CLEAR) == KEY_ACCESS_CLEAR)
            {
                theKey->times = 0;			
            }
            if ((option & KEY_ACCESS_DECREASE) == KEY_ACCESS_DECREASE)
            {
                if (0 == theKey->times)
                {
                    theKey->times = theKey->times;
                }
                else
                {
                    (theKey->times)--;
                }
            }
            if ((option & KEY_ACCESS_INCREASE) == KEY_ACCESS_INCREASE)
            {
                if (KEY_TIMES_MAX == theKey->times)
                {
                    theKey->times = theKey->times;
                }
                else
                {
                    (theKey->times)++;
                }
            }
        }
		
        times_temp = theKey->times;
        
	#if KEY_USE_SEM == 1
		theKey->sem = KEY_SEM_FREE;
	}
	#endif
	
	return times_temp;
}


extern key_inf_type key_up;
extern key_inf_type key_down;
extern key_inf_type key_back;
extern key_inf_type key_ok;
/*************************************************************************************************************
** ��������:			Wp_GpioKeyInit
**
** ��������:			Gpio connect Key Init;
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
void Wp_KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    
    /*  PD12, PD13, PD14, PD15Ĭ�ϰ��������	    */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// ��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);					// GPIOD��ʼ��
    
    Wp_KeyObjectInit(&key_up, KeyUp_state);                 // ��ʼ��һ����������
    Wp_KeyObjectInit(&key_down, KeyDown_state);             // ��ʼ��һ����������
    Wp_KeyObjectInit(&key_back, KeyBack_state);             // ��ʼ��һ����������
    Wp_KeyObjectInit(&key_ok, KeyOk_state);                 // ��ʼ��һ����������
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
