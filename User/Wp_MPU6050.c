/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_MPU6050.c
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				����MPU6050_DMP���;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				����MPU6050_DMP���;
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
#include "Wp_MPU6050.h"


TYPE_CONV_UNION type_conv;
WP_DMP_DATA_INFO_STRUCT wp_dmp_data;
WP_DMP_DATA_INFO_STRUCT wp_dmp_data = 
{
	0,
	0,
	0,
	0,
	{0},
	{0},
	0,
	0,
	{0}
};

/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static  unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      		// error
    
    return b;
}


unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;

    /* XYZ  010_001_000 	Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010 */
	
    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;
    
    return scalar;
}


void run_self_test(void)
{
    int result = 0;
    long gyro[3], accel[3];
    
    result = mpu_run_self_test(gyro, accel);
    
    if (result == 0x7) 
    {
    /* Test passed. We can trust the gyro data here, so let's push it down
     * to the DMP.
     */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
        
	//	USART1_Puts("setting bias succesfully ......\n");
    }
	else
	{
	//	USART1_Puts("bias has not been modified ......\n");
	}
}

static void Wp_Mpu6050Gpio(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
	/*	FSYNC, Att_AD0��ΪLEDָʾ��				*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 50Mʱ���ٶ�
	GPIO_Init(GPIOC, &GPIO_InitStructure);					// GPIOC��ʼ��
}

void Wp_MPU6050DMP_Init(void)
{
	int result = 0;
	
    Wp_Mpu6050Gpio();
	SimulateI2cInit();							            // IIC���ߵĳ�ʼ��
	result = mpu_init();				                    // MPU-6050��ʼ��
    
	if (!result)
	{  
		// mpu_set_sensor
		if (!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
        {
		//	USART1_Puts("mpu_set_sensor complete ......\n");
        }
		else
        {
		//	USART1_Puts("mpu_set_sensor come across error ......\n");
        }
        
		// mpu_configure_fifo
		if (!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))
        {
		//	USART1_Puts("mpu_configure_fifo complete ......\n");
        }
		else
        {
		//	USART1_Puts("mpu_configure_fifo come across error ......\n");
        }
        
		// mpu_set_sample_rate
		if (!mpu_set_sample_rate(DEFAULT_MPU_HZ))			// ���ò���Ƶ��
        {
		//	USART1_Puts("mpu_set_sample_rate complete ......\n");
        }
		else
        {
		//	USART1_Puts("mpu_set_sample_rate error ......\n");
        }
        
		// dmp_load_motion_driver_firmvare
		if (!dmp_load_motion_driver_firmware())				// �������Ҫ��ʧ�ܵĻ���û������DMP
        {
		//	USART1_Puts("dmp_load_motion_driver_firmware complete ......\n");
        }
		else
        {
		//	USART1_Puts("dmp_load_motion_driver_firmware come across error ......\n");
        }
        
		// dmp_set_orientation
		if (!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
        {
		//	USART1_Puts("dmp_set_orientation complete ......\n");
        }
		else
        {
		//	USART1_Puts("dmp_set_orientation come across error ......\n");
        }
        
		// dmp_enable_feature
		if (!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT 
                               | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL))
        {
		//	USART1_Puts("dmp_enable_feature complete ......\n");
        }
		else
        {
		//	USART1_Puts("dmp_enable_feature come across error ......\n");
        }
        
		// dmp_set_fifo_rate
		if (!dmp_set_fifo_rate(DEFAULT_MPU_HZ))
        {
		//	USART1_Puts("dmp_set_fifo_rate complete ......\n");
        }
		else
        {
		//	USART1_Puts("dmp_set_fifo_rate come across error ......\n");
        }
        
		// �Լ죬��������Ư��
		run_self_test();
		if (!mpu_set_dmp_state(1))
        {
		//	USART1_Puts("mpu_set_dmp_state complete ......\n");
        }
		else
        {
		//	USART1_Puts("mpu_set_dmp_state come across error ......\n");
        }
	}
}


void Wp_GetMpu6050Dmp(void)
{
	float q0 = 1.0f;        // ��Ԫ������
    float q1 = 0.0f;
    float q2 = 0.0f;
    float q3 = 0.0f;
	
	// ��ȡDMP_FIFO�е�����
	dmp_read_fifo(wp_dmp_data.gyro, wp_dmp_data.accel, wp_dmp_data.quat, 
                  &wp_dmp_data.sensor_timestamp, &wp_dmp_data.sensors, &wp_dmp_data.more);
    
	// ��ȡ��Ԫ��������ŷ���ǣ�Ĭ����long����ת����float�����1073741824.0f����ʹ���ˣ�˳����WXYZ
	if (wp_dmp_data.sensors & INV_WXYZ_QUAT)
	{   
		// ��Ԫ��
		q0 = wp_dmp_data.quat[0] / q30;			// W
		q1 = wp_dmp_data.quat[1] / q30;			// X
		q2 = wp_dmp_data.quat[2] / q30;			// Y 
		q3 = wp_dmp_data.quat[3] / q30;			// Z
        
		// ŷ����
		wp_dmp_data.Pitch = asin(-2*q1*q3 + 2*q0*q2) * 57.3; 								// pitch����
		wp_dmp_data.Roll = atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1) * 57.3;			// roll��ת
		wp_dmp_data.Yaw = atan2(2*(q1*q2 + q0*q3), q0*q0 + q1*q1 - q2*q2 - q3*q3) * 57.3; 	// yawƫ��
	}
}


/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
        
    }
}


#endif
/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
