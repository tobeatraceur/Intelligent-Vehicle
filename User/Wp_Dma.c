/********************************************Copyright******************************************************
**                                                                                                      
**
**-------------------------------------------�ļ���Ϣ-------------------------------------------------------
** �ļ�����:			Wp_Dma.c
** ����޶�����:  		2012-10-10
** ���汾:			1.0
** ����:				DMA��ʼ���ļ�;
**
**-----------------------------------------------------------------------------------------------------------
** ������:				�⿵
** ��������:			2012-02-09
** �汾:				1.0
** ����:				DMA��ʼ���ļ�;
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
#include "Wp_Dma.h"


/*************************************************************************************************************
** ��������:			Wp_Uart1RxDmaInit
**
** ��������:			UART1��������DMA��ʼ��;
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
void Wp_Uart1RxDmaInit(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
	DMA_DeInit(DMA1_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);				// ԴͷBUF
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)(&receivebuf[0]);				// Ŀ��BUF
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							// ������Դͷ
	DMA_InitStructure.DMA_BufferSize = 62;										// BUF��С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// �������ģʽ��ֹ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						// �ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		// �����ֽ�Ϊ��λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			    // �ڴ��ֽ�Ϊ��λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								// ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;							// 4���ȼ�֮һ��(������)
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								// ���ڴ浽�ڴ�
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);
	
    DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);								// DMA5��������ж�  
    
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);                              // ����DMA��ʽ����  
	
	DMA_Cmd(DMA1_Channel5, ENABLE);												// ʹ��DMA����ʽ����DMA    
}


/*************************************************************************************************************
** ��������:			Wp_Uart1TxDmaInit
**
** ��������:			UART1��������DMA��ʼ��;
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
void Wp_Uart1TxDmaInit(void)  
{   
    DMA_InitTypeDef DMA_InitStructure;  
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    /* DMA channel4 Configuration */
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);          // �����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)(&sendtemp[0]);             // ���ڷ��ͻ���
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      // ������ΪĿ�ĵ�ַ
    DMA_InitStructure.DMA_BufferSize = 62;                                  // BufferSize�������С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        // �������ģʽ��ֹ
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 // �ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // ���䷽ʽ���ֽ�
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // �ڴ�洢��ʽ���ֽ� 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         // DMA����ģʽ��ֻ����һ��
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                     // 4���ȼ�֮һ��(������)
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            // ���ڴ浽�ڴ�
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);  
    
    /* Enable DMA Channel4Transfer Complete interrupt */  
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);                         // ʹ�ܷ�������ж�
    
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);                          // ����DMA��ʽ����
    
//  USART_Cmd(USART1, ENABLE);                                              // ��������
    
    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);                         // ������������DMA�ж�
}


/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
