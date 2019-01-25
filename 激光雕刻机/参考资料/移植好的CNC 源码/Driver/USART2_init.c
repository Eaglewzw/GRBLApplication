#include "USART2_init.h"


UsartRxTypeDef1 USARTStructure2;
unsigned char USART2_TX_BUFF[USART2_TX_BUFF_SIZEMAX];   

/****************************************************************************
* ��	�ƣ�void USART2_GPIO_Init(void)
* ��	�ܣ��������ų�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART2_GPIO_Init(void)			//�������ų�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;		//�������Žṹ
	
	//�������ŷ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);

	//���ô��� Tx (PA.02) Ϊ�����������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;					//���ڷ�������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				//�����������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//Ƶ��50MHz
  	GPIO_Init(GPIOA, &GPIO_InitStructure);						//��ʼ������
    
	// ���ô��� Rx (PA.03) Ϊ��������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;					//���ڽ�������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);						//��ʼ������
												 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;											//PD3 485 ת��
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//ʱ���ٶ�Ϊ50M
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�˿�ģʽΪ���������ʽ	
		GPIO_Init(GPIOD, &GPIO_InitStructure);		
		
}

/****************************************************************************
* ��	�ƣ�void USART2_Init(void)
* ��	�ܣ����ڳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART2_Init(void)
{		
	USART_InitTypeDef UART_InitStructure;		//���ڽṹ

	//���ڷ���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	//���ڳ�ʼ��
	UART_InitStructure.USART_BaudRate            = USART2BaudRate;	//������
	UART_InitStructure.USART_WordLength          = USART_WordLength_8b;		//����λ8bit
	UART_InitStructure.USART_StopBits            = USART_StopBits_1;		//ֹͣλ����
	UART_InitStructure.USART_Parity              = USART_Parity_No ;		//��������żЧ��
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//RTS��CTSʹ��(None��ʹ��)
	UART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//���ͺͽ���ʹ��
	USART_Init(USART2, &UART_InitStructure);	//��ʼ������
}

/****************************************************************************
* ��	�ƣ�void USART2_NVIC_Init(void)
* ��	�ܣ������ж��������ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART2_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 		//�жϿ���������

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			//�����ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//�����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//�򿪴����ж�
	NVIC_Init(&NVIC_InitStructure);								//��ʼ���ж�������
}

/****************************************************************************
* ��	�ƣ�void USART2_DMATxd_Init(void)
* ��	�ܣ�����DMA��ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART2_DMATxd_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 		//�жϿ���������
	DMA_InitTypeDef DMA_InitStructure;			//DMA�ṹ

	RCC_AHBPeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			//ʹ��DMA1ʱ��

	//DMA�ж���������
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;	//����DMA�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//�����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//���ж�
	NVIC_Init(&NVIC_InitStructure); 

	//DMA����
	DMA_DeInit(DMA1_Channel7);  		   									//��λDMA1_Channel4ͨ��ΪĬ��ֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_BASE + 4;				//DMAͨ���������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART2_TX_BUFF;				//DMAͨ���洢������ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						//DMAĿ�ĵ�	(DMA_DIR_PeripheralSRCԴ)
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//��ǰ����Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//��ǰ�洢�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ��Ϊ�ֽ�(8λ)
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//�洢�����ݿ��Ϊ�ֽ�(8λ)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							//��������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;					//DMAͨ�����ȼ��ǳ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//DMAͨ��δ���ô洢�����洢������
	DMA_Init(DMA1_Channel7, &DMA_InitStructure);							//�����������ó�ʼ��DMA
	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);    						//����DMAͨ���ж�
}

/****************************************************************************
* ��	�ƣ�void USART2_Config(void)
* ��	�ܣ���������
* ��ڲ�������
* ���ڲ�������
* ˵	����Ĭ��Ϊ�����ݽ���					 
****************************************************************************/
void USART2_Config(void)
{
	USART2_Init();				//���ڳ�ʼ��
	USART2_GPIO_Init();			//�������ų�ʼ��
	USART2_NVIC_Init();			//�жϳ�ʼ��
	USART2_DMATxd_Init();		//DMA���ͳ�ʼ��
	USART2_RX_Buffer_Clear();	//�����ж�����ջ�������

	USART_ClearITPendingBit(USART2, USART_IT_RXNE);				//����ձ�־
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);				//���������ж�
	
	USART_Cmd(USART2, ENABLE);  								//ʹ��ʧ�ܴ�������	
}

/****************************************************************************
* ��	�ƣ�void USART2_SendByte(u8 Data)
* ��	�ܣ����ַ�����
* ��ڲ�����Data 	���͵��ַ�����
* ���ڲ�������
* ˵	������				   
****************************************************************************/
void USART2_RX_Buffer_Clear(void)	
{

	USARTStructure2.RX_TMEP_Len = 0;
		
}
/****************************************************************************
* ��	�ƣ�void USART2_SendByte(u8 Data)
* ��	�ܣ����ַ�����
* ��ڲ�����Data 	���͵��ַ�����
* ���ڲ�������
* ˵	������				   
****************************************************************************/
void USART2_SendByte(u8 Data)		   //���ַ��������
{
	USART_SendData(USART2, Data);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

/****************************************************************************
* ��	�ƣ�void USART2_SendString(u8* Data,u32 Len)
* ��	�ܣ����ַ����
* ��ڲ�����Data 	����ĵ��ַ�����
			Len		�ַ�����
* ���ڲ�������
* ˵	������					 
****************************************************************************/
void USART2_SendString(u8* Data,u32 Len)		   //���ַ����
{
	u32 i=0;
	GPIO_SetBits(GPIOD, GPIO_Pin_3 );  
	Delay_MS(5);
	for(i=0;i<Len;i++)
  {    
		USART_SendData(USART2, Data[i]);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	}
	GPIO_ResetBits(GPIOD, GPIO_Pin_3 ); 
}

/****************************************************************************
* ��	�ƣ�void USART2_DMASendString(u8* Data,u32 Len)
* ��	�ܣ�DMA��ʽ���ַ����
* ��ڲ�����Data 	����ĵ��ַ�����
			Len		�ַ�����
* ���ڲ�������
* ˵	����������USART2_DMATxd_Init��ʼ��֮�����ʹ��
			DMA����CPU���� �� ��CPU���� ���з��ͳ�ͻ	 
****************************************************************************/
void USART2_DMASendData(u8* Data,u32 Len)		   //���ַ����
{
	GPIO_SetBits(GPIOD, GPIO_Pin_3 );  
	Delay_MS(5);
	
	memcpy(USART2_TX_BUFF, Data, Len);			   //�������ݵ����ͻ�����
    DMA1_Channel7->CNDTR = Len;					   //�����ֽ�����
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE); //����
	DMA_Cmd(DMA1_Channel7, ENABLE);				   //ʼ��DMAͨ��
}

/****************************************************************************
* ��	�ƣ�void USART2_IRQHandler(void)	
* ��	�ܣ��жϻ���
* ��ڲ�������
* ���ڲ�������
* ˵	�������յ������ݴ�����ջ�����
	USART_GetITStatus		���ָ����USART�жϷ������
	USART_GetFlagStatus	���ָ����USART��־λ�������
****************************************************************************/
void USART2_IRQHandler(void)
{

	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)				// ���ڽ������ݴ����ж�
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);					//��ս����жϱ�־									//���յ����ַ�����

		USARTStructure2.RX_TEMP_BUFF[USARTStructure2.RX_TMEP_Len]=USART_ReceiveData(USART2);
		USARTStructure2.RX_TMEP_Len++;
	}

	else if(USART_GetFlagStatus(USART2, USART_IT_ORE) == SET)	//����Ƿ��н������
	{
		USART_ReceiveData(USART2);															//����������־��ֻ���ö����ݵķ�ʽ���������־
	}

	else if(USART_GetITStatus(USART2, USART_IT_TXE) == SET)		//���ڷ������ݴ����ж�
	{
		
	}
}

/****************************************************************************
* ��	�ƣ�void DMA1_Channel7_IRQHandler(void)	
* ��	�ܣ�DMA�жϻ���
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void DMA1_Channel7_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC7)) //����������
	{
		USART_DMACmd(USART2, USART_DMAReq_Tx, DISABLE);    //�ر�DMA����
		DMA_Cmd(DMA1_Channel7, DISABLE);	       			//�ر�DMAͨ��  	
		Delay_MS(5);
		GPIO_ResetBits(GPIOD, GPIO_Pin_3 );  
	}

	DMA_ClearFlag(DMA1_FLAG_GL7| DMA1_FLAG_TC7 | DMA1_FLAG_HT7 | DMA1_FLAG_TE7);  //���DMA��ر�־
}


