#include "USART4_init.h"


unsigned char Rx4_String[60];	  			  //??????? ??lrc???????
unsigned char Rx4_Flag;  
UsartRxTypeDef4 USARTStructure4;
/****************************************************************************
* ��	�ƣ�void USART4_GPIO_Init(void)
* ��	�ܣ��������ų�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART4_GPIO_Init(void)			//�������ų�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;		//�������Žṹ
	
	//�������ŷ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	//���ô��� Tx (PC.10) Ϊ�����������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					//���ڷ�������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				//�����������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			//Ƶ��50MHz
  	GPIO_Init(GPIOC, &GPIO_InitStructure);						//��ʼ������
    
	// ���ô��� Rx (PC.11) Ϊ��������
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;					//���ڽ�������
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		//��������
  	GPIO_Init(GPIOC, &GPIO_InitStructure);						//��ʼ������
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;						//PD4 485 ת��
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//ʱ���ٶ�Ϊ50M
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//�˿�ģʽΪ���������ʽ	
		GPIO_Init(GPIOD, &GPIO_InitStructure);			
}

/****************************************************************************
* ��	�ƣ�void USART3_Init(void)
* ��	�ܣ����ڳ�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART4_Init(void)
{		
	USART_InitTypeDef UART_InitStructure;		//���ڽṹ

	//���ڷ���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	//���ڳ�ʼ��
	UART_InitStructure.USART_BaudRate            = USART4BaudRate;	//������
	UART_InitStructure.USART_WordLength          = USART_WordLength_8b;		//����λ8bit
	UART_InitStructure.USART_StopBits            = USART_StopBits_1;		//ֹͣλ����
	UART_InitStructure.USART_Parity              = USART_Parity_No ;		//��������żЧ��
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//RTS��CTSʹ��(None��ʹ��)
	UART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;		//���ͺͽ���ʹ��
	USART_Init(UART4, &UART_InitStructure);			//��ʼ������
}

/****************************************************************************
* ��	�ƣ�void USART4_NVIC_Init(void)
* ��	�ܣ������ж��������ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void USART4_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 		//�жϿ���������

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;			//�����ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//�����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			//�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//�򿪴����ж�
	NVIC_Init(&NVIC_InitStructure);								//��ʼ���ж�������
}


/****************************************************************************
* ��	�ƣ�void USART2_Config(void)
* ��	�ܣ���������
* ��ڲ�������
* ���ڲ�������
* ˵	����Ĭ��Ϊ�����ݽ���					 
****************************************************************************/
void USART4_Config(void)
{
	USART4_Init();					//���ڳ�ʼ��
	USART4_GPIO_Init();			//�������ų�ʼ��
	USART4_NVIC_Init();			//�жϳ�ʼ��
	USART4_RX_Buffer_Clear();	//�����ж�����ջ�������

		
	USART_ClearITPendingBit(UART4, USART_IT_RXNE);			//����ձ�־
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);				//���������ж�
	
	USART_Cmd(UART4, ENABLE);  								//ʹ��ʧ�ܴ�������	
}

/****************************************************************************
* ��	�ƣ�void USART2_SendByte(u8 Data)
* ��	�ܣ����ַ�����
* ��ڲ�����Data 	���͵��ַ�����
* ���ڲ�������
* ˵	������				   
****************************************************************************/
void USART4_RX_Buffer_Clear(void)	
{
	USARTStructure4.RX_Len = 0;
}
/****************************************************************************
* ��	�ƣ�void USART2_SendByte(u8 Data)
* ��	�ܣ����ַ�����
* ��ڲ�����Data 	���͵��ַ�����
* ���ڲ�������
* ˵	������				   
****************************************************************************/
void UART4_SendByte(u8 Data)		   //���ַ��������
{
	USART_SendData(UART4, Data);
    while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
}

/*******************************************************************************
* Function Name  :
* Description    : ???????(????lrc??,0D0A)   ??':' ??'\0'
*******************************************************************************/
void Send_Command(unsigned char *str)
{
 unsigned char Lrc=0;
 unsigned char Temp=0,Temp_h=0,Temp_l=0;
 unsigned char i=0;
 unsigned char StrCmp[40];

	while( (*str) != '\0')
	{
		StrCmp[i]= (*str);                                              //?????':'???
		str++;
		if(StrCmp[0] == 0x3a)                                           // ??????':'
                {
			if(i%2==0){	Temp_h=ChrToInt(*str);	Temp=0;}
			else{	    Temp_l=ChrToInt(*str);  Temp=Temp_h*16+Temp_l;}
			Lrc += Temp;
			i++;
		}
	}
	Lrc = (~Lrc)+1;                                       //LRC??????
	StrCmp[i]=Ascill_16[Lrc/16];
	StrCmp[++i]=Ascill_16[Lrc%16];
	StrCmp[++i]='\0';

	GPIO_SetBits(GPIOD, GPIO_Pin_4 ); 
                                                        //485????
  Delay_MS(5);
	i=0;
	while(StrCmp[i] != '\0')
	{
      UART4_SendByte(StrCmp[i]); i++;
	}
	UART4_SendByte(0x0d);
  UART4_SendByte(0x0a);
	Delay_MS(5);
	GPIO_ResetBits(GPIOD, GPIO_Pin_4 );                     //485????

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
void UART4_IRQHandler(void)
{
	unsigned char i;

	unsigned char temp;
	static unsigned char  num=0;
	
	if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET)				// ���ڽ������ݴ����ж�
	{
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);					//��ս����жϱ�־			//���յ����ַ�����

		temp  = USART_ReceiveData(UART4);
    if (temp==0x3a)
    {
       num=0;
       USARTStructure4.RX_BUFF[num]=temp;
       num++;
    }
    else if(temp==0xA)                                                          //???LF???
    {
        USARTStructure4.RX_Flag=1;
        USARTStructure4.RX_Len=num;                                             //?ODOA
				num=0;
        Get_Command();
    }
    else if(temp==0xD)                                                          //???CR???
    {}
    else
    {
        USARTStructure4.RX_BUFF[num]=temp;
        num++;
				if(num>=40)
				{
						for(i=0;i<40;i++)
								USARTStructure4.RX_BUFF[i]=0x20;                                //?????
						num=0;
				}
    }
	}
	else if(USART_GetFlagStatus(UART4, USART_IT_ORE) == SET)	//����Ƿ��н������
	{
		USART_ReceiveData(UART4);																//����������־��ֻ���ö����ݵķ�ʽ���������־
	}

	else if(USART_GetITStatus(UART4, USART_IT_TXE) == SET)		//���ڷ������ݴ����ж�
	{
		
	}
}


/*******************************************************************************
* Function Name  :
* Description    : 485?? ????????lrc?????
*******************************************************************************/
void Get_Command(void)
{
unsigned char Lrc=0;
unsigned char Temp=0,Temp_h=0,Temp_l=0;
unsigned char i;

  if(USARTStructure4.RX_Flag==1)
	{
		if(USARTStructure4.RX_BUFF[0]==':')
		{
			for(i=1;i<USARTStructure4.RX_Len+1;i++)		   	//???????? 0D0A	 ?????
			{
				if(i%2 != 0){	Temp_h=ChrToInt(USARTStructure4.RX_BUFF[i]);	Temp=0;}
				else	    { 	Temp_l=ChrToInt(USARTStructure4.RX_BUFF[i]); Temp=Temp_h*16+Temp_l;}
				Lrc += Temp;
			}
		}
		Lrc=((~Lrc)+1);

		if(((~Lrc)+1) == 0)				  										//LRC????????0
		{
		  for(i=0;i<USARTStructure4.RX_Len-2;i++)		   	//???????? ??? 0D0A
				Rx4_String[i] = USARTStructure4.RX_BUFF[i];
			Rx4_String[i]='\0';
			Rx4_Flag=1;
		}

		for(i=0;i<40;i++)                                               //Clear
		{
			USARTStructure4.RX_BUFF[i]=0x20;			//?????
		}
		USARTStructure4.RX_Len=0;
		USARTStructure4.RX_Flag=0;
	}
}



