#include "USART1_init.h"
#include <stdio.h>
#include <ctype.h>
#include "motion_control.h"



//UsartRxTypeDef USARTStructure1;
 uint8_t rx_buffer[RX_BUFFER_SIZE];
 uint8_t rx_buffer_head = 0;
 volatile uint8_t rx_buffer_tail = 0;

 uint8_t tx_buffer[TX_BUFFER_SIZE];
 uint8_t tx_buffer_head = 0;
 volatile uint8_t tx_buffer_tail = 0;

static unsigned char USART1_TxBuffer[60];		//����1DMA���ͻ���
/****************************************************************************
* ��	�ƣ�void USART1_GPIO_Init(void)
* ��	�ܣ��������ų�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART1_GPIO_Init(void)						//�������ų�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;		//�������Žṹ
	
	//�������ŷ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//���ô��� Tx (PA.09) Ϊ�����������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;					//���ڷ�������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				//�����������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//Ƶ��50MHz
  	GPIO_Init(GPIOA, &GPIO_InitStructure);						//��ʼ������
    
	// ���ô��� Rx (PA.10) Ϊ��������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					//���ڽ�������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);						//��ʼ������
}

/****************************************************************************
* ��	�ƣ�void USART1_Init(void)
* ��	�ܣ����ڳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART1_Init(void)
{		
	USART_InitTypeDef UART_InitStructure;		//���ڽṹ

	//���ڷ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//���ڳ�ʼ��
	UART_InitStructure.USART_BaudRate            = USART1BaudRate;					//������
	UART_InitStructure.USART_WordLength          = USART_WordLength_8b;				//����λ8bit
	UART_InitStructure.USART_StopBits            = USART_StopBits_1;				//ֹͣλ����
	UART_InitStructure.USART_Parity              = USART_Parity_No ;				//��������żЧ��
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//RTS��CTSʹ��(None��ʹ��)
	UART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//���ͺͽ���ʹ��
	USART_Init(USART1, &UART_InitStructure);										//��ʼ������
}

/****************************************************************************
* ��	�ƣ�void USART1_NVIC_Init(void)
* ��	�ܣ������ж��������ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART1_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 						//�жϿ���������

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//�����ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//�����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//�򿪴����ж�
	NVIC_Init(&NVIC_InitStructure);								//��ʼ���ж�������
}

/****************************************************************************
* ��	�ƣ�void USART1_DMATxd_Init(void)
* ��	�ܣ�����DMA��ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART1_DMATxd_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 						//�жϿ���������
	DMA_InitTypeDef DMA_InitStructure;							//DMA�ṹ

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);			//ʹ��DMA1ʱ��

	//DMA�ж���������
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;	//����DMA�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//�����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			//�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//���ж�
	NVIC_Init(&NVIC_InitStructure); 

	//DMA����
	DMA_DeInit(DMA1_Channel4);  		   									//��λDMA1_Channel4ͨ��ΪĬ��ֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_BASE + 4;				//DMAͨ���������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)USART1_TxBuffer;			//DMAͨ���洢������ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						//DMAĿ�ĵ�	(DMA_DIR_PeripheralSRCԴ)
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//��ǰ����Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//��ǰ�洢�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ��Ϊ�ֽ�(8λ)
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;			//�洢�����ݿ��Ϊ�ֽ�(8λ)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							//��������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;					//DMAͨ�����ȼ��ǳ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;							//DMAͨ��δ���ô洢�����洢������
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);							//�����������ó�ʼ��DMA
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);    						//����DMAͨ���ж�
}

/****************************************************************************
* ��	�ƣ�void USART1_RX_Buffer_init(void)
* ��	�ܣ����ڽ��ճ�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	�������ջ�������ʼ��
****************************************************************************/
void USART1_RX_Buffer_init(void)
{
//	unsigned char i;

//		USARTStructure1.RX_Flag = 0;
//		USARTStructure1.RX_Len = 0;
//		for(i=0; i<60; i++)
//		{
//			USARTStructure1.RX_Buffer[i] = 0x00;
//		}
}

/****************************************************************************
* ��	�ƣ�void USART1_Config(void)
* ��	�ܣ���������
* ��ڲ�������
* ���ڲ�������
* ˵	����Ĭ��Ϊ�����ݽ���					 
****************************************************************************/
void USART1_Config(void)
{
	USART1_Init();				//���ڳ�ʼ��
	USART1_GPIO_Init();			//�������ų�ʼ��
	USART1_NVIC_Init();			//�жϳ�ʼ��
//	USART1_DMATxd_Init();		//DMA���ͳ�ʼ��
//	USART1_RX_Buffer_init();	//�����ж�����ջ�������

	USART_ClearITPendingBit(USART1, USART_IT_RXNE);				//����ձ�־
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);				//���������ж�
	
	USART_Cmd(USART1, ENABLE);  								//ʹ��ʧ�ܴ�������	

//	USART1_DMASendString("USART 1 Send ok",20);		   			//���ַ�DMA���
}


/****************************************************************************
* ��	�ƣ�void USART1_SendByte(u8 Data)
* ��	�ܣ����ַ�����
* ��ڲ�����Data 	���͵��ַ�����
* ���ڲ�������
* ˵	������				   
****************************************************************************/
void USART1_SendByte(u8 Data)		   //���ַ��������
{
	USART_SendData(USART1, Data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/****************************************************************************
* ��	�ƣ�void USART1_SendString(u8* Data,u32 Len)
* ��	�ܣ����ַ����
* ��ڲ�����Data 	����ĵ��ַ�����
			Len		�ַ�����
* ���ڲ�������
* ˵	������					 
****************************************************************************/
void USART1_SendString(u8* Data,u32 Len)		   //���ַ����
{
	u32 i=0;
	for(i=0;i<Len;i++)
    {    
		USART_SendData(USART1, Data[i]);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
}

/****************************************************************************
* ��	�ƣ�void USART1_DMASendString(u8* Data,u32 Len)
* ��	�ܣ�DMA��ʽ���ַ����
* ��ڲ�����Data 	����ĵ��ַ�����
			Len		�ַ�����
* ���ڲ�������
* ˵	����������USART1_DMATxd_Init��ʼ��֮�����ʹ��
			DMA����CPU���� �� ��CPU���� ���з��ͳ�ͻ	 
****************************************************************************/
void USART1_DMASendString(u8* Data,u32 Len)		   //���ַ����
{
	memcpy(USART1_TxBuffer, Data, Len);			   //�������ݵ����ͻ�����
    DMA1_Channel4->CNDTR = Len;					   //�����ֽ�����
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE); //����
	DMA_Cmd(DMA1_Channel4, ENABLE);				   //ʼ��DMAͨ��
}

/****************************************************************************
* ��	�ƣ�void USART1_IRQHandler(void)	
* ��	�ܣ��жϻ���
* ��ڲ�������
* ���ڲ�������
* ˵	�������յ������ݴ�����ջ�����
	 USART_GetITStatus		���ָ����USART�жϷ������
	 USART_GetFlagStatus	���ָ����USART��־λ�������
****************************************************************************/
void USART1_IRQHandler(void)
{
	unsigned char USART1_GetChar;
  uint8_t next_head;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)				// ���ڽ������ݴ����ж�
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);				//��ս����жϱ�־
		USART1_GetChar = USART_ReceiveData(USART1);					//���յ����ַ�����
		
	  switch (USART1_GetChar) 
	  {
			case 0x0a:
				
			break;
			case CMD_STATUS_REPORT: 
				sys.execute |= EXEC_STATUS_REPORT; 
			break; // Set as true
			case CMD_CYCLE_START:   
				sys.execute |= EXEC_CYCLE_START; 
			break; // Set as true
			case CMD_FEED_HOLD:     
				sys.execute |= EXEC_FEED_HOLD; 
			break; // Set as true
			case CMD_RESET:         
				//mc_reset(); 
				PWR_OFF; 											//�˿ڹر�
				OutputControl(0x0000);				//�ر����ж˿�
				Delay_MS(100);
				__set_FAULTMASK(1);   
				NVIC_SystemReset();
			
			break; // Call motion control reset routine.
			default: // Write character to buffer    	
		
			next_head = rx_buffer_head + 1;
			if (next_head == RX_BUFFER_SIZE) { next_head = 0; }
		
			// Write data to buffer unless it is full.
			if (next_head != rx_buffer_tail) 
			{
				rx_buffer[rx_buffer_head] = USART1_GetChar;
				rx_buffer_head = next_head;    
						
	//			#ifdef ENABLE_XONXOFF
	//				if ((get_rx_buffer_count() >= RX_BUFFER_FULL) && flow_ctrl == XON_SENT) {
	//					flow_ctrl = SEND_XOFF;
	//					UCSR0B |=  (1 << UDRIE0); // Force TX
	//				} 
	//			#endif			
			}		
			break;
		}
		
//		protocol_process();		//Э�����ִ��
	}

	else if(USART_GetFlagStatus(USART1, USART_IT_ORE) == SET)		//����Ƿ��н������
    {
	    USART_ReceiveData(USART1);									//����������־��ֻ���ö����ݵķ�ʽ���������־
    }

	else if(USART_GetITStatus(USART1, USART_IT_TXE) == SET)				//���ڷ������ݴ����ж�
	{
		;
	}
}

/****************************************************************************
* ��	�ƣ�void DMA1_Channel4_IRQHandler(void)	
* ��	�ܣ�DMA�жϻ���
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC4)) //����������
	{
		USART_DMACmd(USART1, USART_DMAReq_Tx, DISABLE);    //�ر�DMA����
		DMA_Cmd(DMA1_Channel4, DISABLE);	       			//�ر�DMAͨ��  
	}

	DMA_ClearFlag(DMA1_FLAG_GL4| DMA1_FLAG_TC4 | DMA1_FLAG_HT4 | DMA1_FLAG_TE4);  //���DMA��ر�־
}




///*******************************************************************************
//* Function Name  : ??1???????
//* Description    : 
//* Parameter		 
//* Return		
//********************************************************************************/

//void U1ProtocolAnalysis(void)
//{
//	unsigned char i;
//	unsigned char rlen;
//	char Rx1_String[60];
//	
//		if(USARTStructure1.RX_Flag == 1)		  										//????????
//		{
//			USARTStructure1.RX_Flag = 0;														//????		
//		
//			rlen = USARTStructure1.RX_Len;												
//			for(i=0; i< rlen; i++)
//			{
//				Rx1_String[i] = Transchar(USARTStructure1.RX_Buffer[i]); 	
//			}
//			Rx1_String[i] = '\0';		
//				
//				switch(Rx1_String[0])									
//				{
//					case 'I':
//							if(StringCompare2("INFO",&Rx1_String[0]) == 0)
//							{
//								printf("CNC STM32 Control sysytem v1.0\r\n");
//							}
//							break;
//					case 'K':						
//							if(StringCompare3("KEY_",&Rx1_String[0],4) == 0)
//							{
////								key_value= ChrToInt(Rx1_String[4])+1;		//��ֵ	
////								printf("\r\n*** key_%x ***\r\n",key_value-1);
//							}
//							break;
//					default:break;
//					
//				}
//		}
//}


char Transchar(char r)
{
	if(('a'<=r)&&(r<='z'))
	{
		return r-32;
	}
	else if(('A'<=r)&&(r<='Z'))
	{
		return r+32;
	}
	else
	{
		return r;
	}
}



uint8_t serial_read()
{
  uint8_t tail = rx_buffer_tail; // Temporary rx_buffer_tail (to optimize for volatile)
  if (rx_buffer_head == tail) {
    return SERIAL_NO_DATA;
  } else {
    uint8_t data = rx_buffer[tail];
    tail++;
    if (tail == RX_BUFFER_SIZE) { tail = 0; }
    rx_buffer_tail = tail;
    
//    #ifdef ENABLE_XONXOFF
//      if ((get_rx_buffer_count() < RX_BUFFER_LOW) && flow_ctrl == XOFF_SENT) { 
//        flow_ctrl = SEND_XON;
//        UCSR0B |=  (1 << UDRIE0); // Force TX
//      }
//    #endif
    
    return data;
  }
}

void serial_reset_read_buffer() 
{
  rx_buffer_tail = rx_buffer_head;

//  #ifdef ENABLE_XONXOFF
//    flow_ctrl = XON_SENT;
//  #endif
}
