#include "USART3_init.h"


UsartRxTypeDef3 USARTStructure3;
unsigned char USART3_TX_BUFF[USART3_TX_BUFF_SIZEMAX];   

/****************************************************************************
* ��	�ƣ�void USART3_GPIO_Init(void)
* ��	�ܣ��������ų�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART3_GPIO_Init(void)			//�������ų�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;		//�������Žṹ
	
	//�������ŷ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//���ô��� Tx (PB.10) Ϊ�����������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					//���ڷ�������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				//�����������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//Ƶ��50MHz
  	GPIO_Init(GPIOB, &GPIO_InitStructure);						//��ʼ������
    
	// ���ô��� Rx (PB.11) Ϊ��������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					//���ڽ�������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
  	GPIO_Init(GPIOB, &GPIO_InitStructure);						//��ʼ������
												 
}

/****************************************************************************
* ��	�ƣ�void USART3_Init(void)
* ��	�ܣ����ڳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART3_Init(void)
{		
	USART_InitTypeDef UART_InitStructure;		//���ڽṹ

	//���ڷ���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	//���ڳ�ʼ��
	UART_InitStructure.USART_BaudRate            = USART3BaudRate;	//������
	UART_InitStructure.USART_WordLength          = USART_WordLength_8b;		//����λ8bit
	UART_InitStructure.USART_StopBits            = USART_StopBits_1;		//ֹͣλ����
	UART_InitStructure.USART_Parity              = USART_Parity_No ;		//��������żЧ��
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//RTS��CTSʹ��(None��ʹ��)
	UART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//���ͺͽ���ʹ��
	USART_Init(USART3, &UART_InitStructure);	//��ʼ������
}

/****************************************************************************
* ��	�ƣ�void USART2_NVIC_Init(void)
* ��	�ܣ������ж��������ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART3_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 		//�жϿ���������

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;			//�����ж�ͨ��
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
void USART3_DMATxd_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 		//�жϿ���������
	DMA_InitTypeDef DMA_InitStructure;			//DMA�ṹ

	RCC_AHBPeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);			//ʹ��DMA1ʱ��

	//DMA�ж���������
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;	//����DMA�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//�����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;			//�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//���ж�
	NVIC_Init(&NVIC_InitStructure); 

	//DMA����
	DMA_DeInit(DMA1_Channel2);  		   									//��λDMA1_Channel4ͨ��ΪĬ��ֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART3_BASE + 4;				//DMAͨ���������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART3_TX_BUFF;				//DMAͨ���洢������ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						//DMAĿ�ĵ�	(DMA_DIR_PeripheralSRCԴ)
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//��ǰ����Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//��ǰ�洢�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ��Ϊ�ֽ�(8λ)
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//�洢�����ݿ��Ϊ�ֽ�(8λ)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							//��������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;					//DMAͨ�����ȼ��ǳ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//DMAͨ��δ���ô洢�����洢������
	DMA_Init(DMA1_Channel2, &DMA_InitStructure);							//�����������ó�ʼ��DMA
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);    						//����DMAͨ���ж�
}

/****************************************************************************
* ��	�ƣ�void USART2_Config(void)
* ��	�ܣ���������
* ��ڲ�������
* ���ڲ�������
* ˵	����Ĭ��Ϊ�����ݽ���					 
****************************************************************************/
void USART3_Config(void)
{
	USART3_Init();				//���ڳ�ʼ��
	USART3_GPIO_Init();			//�������ų�ʼ��
	USART3_NVIC_Init();			//�жϳ�ʼ��
	USART3_DMATxd_Init();		//DMA���ͳ�ʼ��
	USART3_RX_Buffer_Clear();	//�����ж�����ջ�������
	TIM4_Config();
	TIM4_NVIC_Init();
		
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);				//����ձ�־
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);				//���������ж�
	
	USART_Cmd(USART3, ENABLE);  								//ʹ��ʧ�ܴ�������	
}


/****************************************************************************
* ��	��:
* ��	�ܣ����ճ�ʱ���
* ��ڲ�������
* ���ڲ�������
* ˵	����	
//TIM_TimeBaseStructure.TIM_Prescaler = 7199;//ʱ��Ԥ��Ƶ��  
//TIM_TimeBaseStructure.TIM_Period = 9999; // �Զ���װ�ؼĴ������ڵ�ֵ(��ʱʱ��) 
//((1+TIM_Prescaler )/72M)*(1+TIM_Period )
//((1+7199)/72M)*(1+9999)=72/72M *10000=1 ��
// Period =9  ,Prescaler = 7199 ��ʱ1ms
// Period =99  ,Prescaler = 7199 ��ʱ10ms
****************************************************************************/
void TIM4_Config(void)
{

	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ�ܶ�ʱ��3
	
    TIM_TimeBaseStructure.TIM_Period =49;          		  //���ö�ʱ������ֵ,����ʱӦ��1
    TIM_TimeBaseStructure.TIM_Prescaler = 7199;       		  //��ʱ��ʱ��Ԥ��Ƶ,����ʱӦ��1  ��ʱ5ms
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    		  //ʱ�ӷָ�����˲���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //ѡ�����ϼ���ģʽ 
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;		  //���ش�����������������0������ж��¼�
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);			  //���ϲ�����ʼ��TIM3

    TIM_ClearFlag(TIM4, TIM_FLAG_Update);					  		//��������¼���־λ(��ֹ�������ж�)
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);				  //�����ظ����ж� 

    TIM_Cmd(TIM4, DISABLE);									  					//ʹ��TIM3	
}

/****************************************************************************
* ��	�ƣ�
* ��	�ܣ�
* ��ڲ�����
* ���ڲ�������
* ˵	������				   
****************************************************************************/
void TIM4_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 		//�жϿ���������

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;			     //ѡ��ʱ��2�ж���
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		 //��ռ���ȼ�Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;			 //��Ӧ���ȼ�Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //ʹ���ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);								 //�����ϲ�����ʼ��10-15�����ж�ͨ��
}

/****************************************************************************
* ��	�ƣ�void USART2_SendByte(u8 Data)
* ��	�ܣ����ַ�����
* ��ڲ�����Data 	���͵��ַ�����
* ���ڲ�������
* ˵	������				   
****************************************************************************/
void USART3_RX_Buffer_Clear(void)	
{

	USARTStructure3.RX_Len = 0;
		
}
/****************************************************************************
* ��	�ƣ�void USART2_SendByte(u8 Data)
* ��	�ܣ����ַ�����
* ��ڲ�����Data 	���͵��ַ�����
* ���ڲ�������
* ˵	������				   
****************************************************************************/
void USART3_SendByte(u8 Data)		   //���ַ��������
{
	USART_SendData(USART3, Data);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

/****************************************************************************
* ��	�ƣ�void USART2_SendString(u8* Data,u32 Len)
* ��	�ܣ����ַ����
* ��ڲ�����Data 	����ĵ��ַ�����
			Len		�ַ�����
* ���ڲ�������
* ˵	������					 
****************************************************************************/
void USART3_SendString(char * Data,u32 Len)		   //���ַ����
{
	u32 i=0;

	for(i=0;i<Len;i++)
  {    
		USART_SendData(USART3, Data[i]);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	}

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
void USART3_DMASendData(char * Data,u32 Len)		   //���ַ����
{
	
	memcpy(USART3_TX_BUFF, Data, Len);			   //�������ݵ����ͻ�����
    DMA1_Channel2->CNDTR = Len;					   //�����ֽ�����
	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE); //����
	DMA_Cmd(DMA1_Channel2, ENABLE);				   //ʼ��DMAͨ��
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
void USART3_IRQHandler(void)
{
	unsigned char i;
	unsigned char USART3_GetChar;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)				// ���ڽ������ݴ����ж�
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);					//��ս����жϱ�־			//���յ����ַ�����

		USART3_GetChar  = USART_ReceiveData(USART3);
		
    TIM_Cmd(TIM4, ENABLE);									  					 		//ʹ��TIM4	
		TIM_SetCounter(TIM4, 0);																//�嵱ǰ�ļ���
	
		if(USART3_GetChar==0xA)                             		//���յ�LF������
		{

		}
		else if(USART3_GetChar==0xD)                        		//���յ�CR������
		{
			USARTStructure3.RX_BUFF[USARTStructure3.RX_Len] = '\0';
			USARTStructure3.RX_Flag = 1;
			TIM_Cmd(TIM4, DISABLE);									  						//�ر� TIM4	
		}
		else
		{
				USARTStructure3.RX_BUFF[USARTStructure3.RX_Len]=USART3_GetChar;
				USARTStructure3.RX_Len++;
				if(USARTStructure3.RX_Len>=60)
				{
						for(i=0;i<60;i++)
						{
							 USARTStructure3.RX_BUFF[i]=0x00;  						//����ַ���
						}
						USARTStructure3.RX_Len=0;
				}
		}
	 }

	else if(USART_GetFlagStatus(USART3, USART_IT_ORE) == SET)	//����Ƿ��н������
	{
		USART_ReceiveData(USART3);															//����������־��ֻ���ö����ݵķ�ʽ���������־
	}

	else if(USART_GetITStatus(USART3, USART_IT_TXE) == SET)		//���ڷ������ݴ����ж�
	{
		
	}
}
/*******************************************************************************
* Function Name  : TIM2_IRQHandler	 ��ʱ5ms
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
  /* ����жϱ�־λ */
//	unsigned int rlen;
		
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	
//	for(rlen = 0 ;rlen<USARTStructure2.RX_TMEP_Len; rlen++ )
//	{
//			USARTStructure2.RX_BUFF[rlen]=USARTStructure2.RX_TEMP_BUFF[rlen];
//	}
//	USARTStructure2.RX_Len = USARTStructure2.RX_TMEP_Len;
//	USARTStructure2.RX_TMEP_Len = 0;
//	USARTStructure3.RX_BUFF[USARTStructure3.RX_Len] = '\0';
//	USARTStructure3.RX_Flag=1; 
	USARTStructure3.RX_Len = 0;
	
	TIM_Cmd(TIM4, DISABLE);									  			//�ر� TIM4	

}

/****************************************************************************
* ��	�ƣ�void DMA1_Channel2_IRQHandler(void)	
* ��	�ܣ�DMA�жϻ���
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC2)) //����������
	{
		USART_DMACmd(USART2, USART_DMAReq_Tx, DISABLE);    //�ر�DMA����
		DMA_Cmd(DMA1_Channel2, DISABLE);	       			//�ر�DMAͨ��  	

	}

	DMA_ClearFlag(DMA1_FLAG_GL2| DMA1_FLAG_TC2 | DMA1_FLAG_HT2 | DMA1_FLAG_TE2);  //���DMA��ر�־
}


