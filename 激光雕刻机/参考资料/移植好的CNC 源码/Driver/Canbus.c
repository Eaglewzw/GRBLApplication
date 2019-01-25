
#include "Config.h"
#include "Canbus.h"

CanRxMsg RxMessage;							//Ҫ������Ϣ�ṹ��
u8 can_var=0;
volatile u8 g_CanRecvFlag=0;	  //can�Ƿ��յ����ݱ�־
__IO uint32_t ret = 0;          /* for return of the interrupt handling */
volatile TestStatus TestRx;		  //can���ͳɹ���־

//---------------------------------------------------------------------------
//�������� 		   void CAN_NVIC_Configuration(void)
//��������������   CAN�жϳ�ʼ��
//���������� 	  
//��������ֵ�� 	  
//���ߣ� 		 wenzer
//�޸��ˣ�		   �޸����ڣ�
//�޸�ԭ�� 
//---------------------------------------------------------------------------

void CAN_NVIC_Configuration(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	
	  /* Enable CAN1 RX0 interrupt IRQ channel */

	  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

	  /* Enable CAN1 RX0 interrupt IRQ channel */
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


//---------------------------------------------------------------------------
//�������� 		  void CAN_GPIO_Init(void)
//��������������  can���IO��ʼ�� 
//���������� 	  
//��������ֵ�� 	  
//���ߣ� 		 wenzer
//�޸��ˣ�		   �޸����ڣ�
//�޸�ԭ�� 
//---------------------------------------------------------------------------
void CAN_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//��AFIOʱ��
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);	 		/* CAN1 Periph clock enable */	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_CAN, ENABLE);	   /* GPIO clock enable */
	

	  /* Configure CAN pin: RX */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CAN_RX;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	  GPIO_Init(GPIO_CAN, &GPIO_InitStructure);
	
	  /* Configure CAN pin: TX */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_CAN_TX;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIO_CAN, &GPIO_InitStructure);
	
	
	  //STM32FVBT6 �е� can �������Ž�λ�������ó����֣�Ĭ��ģʽ���ض����ַ1ģʽ���ض����ַ2ģʽ�� 
	//CANRX,CANTX �ֱ��ض��嵽 PB8,PB9 �������档 �����������е�һ��Ҫ�����ض���Ĳ�����
	  GPIO_PinRemapConfig(GPIO_Remap_CAN , ENABLE);	   	//��ӳ��

}

//---------------------------------------------------------------------------
//�������� 		  	 void CAN_BUS1_configure(void)
//��������������   	 can�ٶ�����
//���������� 	  
//��������ֵ�� 	  
//���ߣ� 		 wenzer
//�޸��ˣ�		   �޸����ڣ�
//�޸�ԭ�� 
//---------------------------------------------------------------------------
void CAN_BUS1_configure(void)
{
//	u8 slave_id = 0x11;
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;

  /* CAN register init */
  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */ 
  CAN_InitStructure.CAN_TTCM=DISABLE;	 //��ֹʱ�䴥��ͨ��ģʽ
  CAN_InitStructure.CAN_ABOM=DISABLE;	 //Ӳ���Զ���0 MCR�Ĵ���
  CAN_InitStructure.CAN_AWUM=DISABLE;	//˯��ģʽ��� MCR sleep��־
  CAN_InitStructure.CAN_NART=ENABLE;  //����ʧ�ܲ��ط�
  CAN_InitStructure.CAN_RFLM=DISABLE;	//FIFO������´α��Ľ�����
  CAN_InitStructure.CAN_TXFP=DISABLE;	//�������ȼ��ɱ�ʶ������
  CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;				//����ģʽ
	
// CAN_InitStructure.CAN_Mode=CAN_Mode_LoopBack;	  //----loop back

  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
  CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
  CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
  CAN_InitStructure.CAN_Prescaler=9;								//250K
  CAN_Init(CAN1, &CAN_InitStructure);

//(8,7,1)500k
//(8,7,9)250k
//(9,8,200)10k
//72M/2/200/(1+9+8) = 10K

  /* CAN filter init */
	//�������ù����� ȫͨ��
  CAN_FilterInitStructure.CAN_FilterNumber=1; 
  CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;
//  CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)slave_id<<21)&0xffff0000)>>16;
//	
//  CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)slave_id<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
//	
//  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xFFFF;
//  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xFFFF;
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;				//���ù��˱�־��
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;		//�������ù������α�ʶ��
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FIFO0;	  //fifo 0
  CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;					//ʹ�ܹ���
  CAN_FilterInit(&CAN_FilterInitStructure); 

   /* CAN FIFO0 message pending interrupt enable */
//  CAN_ITConfig(CAN1, CAN_IT_TME, DISABLE);                	 //�ط����ж�
  CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE); 
	
}

//---------------------------------------------------------------------------
//�������� 		  void CAN_BUS_init(void)
//��������������   ��ʼ��can������Դ
//���������� 	  
//��������ֵ�� 	  
//���ߣ� 		 wenzer
//�޸��ˣ�		   �޸����ڣ�
//�޸�ԭ�� 
//---------------------------------------------------------------------------
void CAN_BUS_init(void)
{
	
	CAN_GPIO_Init();	           /* CAN����IO��ʱ������ ��ʹ��CAN1*/
	CAN_NVIC_Configuration();	  /* CAN �����ж����� */
	CAN_BUS1_configure();	      //
	
	CAN_WakeUp(CAN1);

}


//---------------------------------------------------------------------------
//�������� 		
//��������������   
//���������� 	  
//��������ֵ�� 	  
//���ߣ� 
//�޸��ˣ�		   �޸����ڣ�
//�޸�ԭ�� 
//---------------------------------------------------------------------------
unsigned char CanbusSendData(u8 reader_addr,u8 *pdata,u8 len)
{
 
	  CanTxMsg TxMessage;
	  uint8_t TransmitMailbox = 0;
		unsigned int i;
		u8 message_tx_status = 0;
	
	  TxMessage.StdId=reader_addr;		//ID
//	  TxMessage.ExtId=0x1234;
	
		TxMessage.IDE=CAN_ID_STD;			 	//��׼��ʽ
//		TxMessage.IDE=CAN_ID_EXT;			//��չ��ʽ
	
	  TxMessage.RTR=CAN_RTR_DATA;	   	//����֡
	  TxMessage.DLC=len;							//���ݳ���
	
	  for(i=0;i<len;i++)
	  {
	  	 TxMessage.Data[i]=pdata[i];
	  }
  
		TransmitMailbox=CAN_Transmit(CAN1, &TxMessage);   //����
		i=0;
	  while(( message_tx_status  != CANTXOK) && (i != 0x1FF))
	  {
			message_tx_status  = CAN_TransmitStatus(CAN1, TransmitMailbox);
			
			if(message_tx_status == CANTXOK)
			{
					DebugPf("message send ok\r\n");
				break;
			}
			else if(message_tx_status == CANTXPENDING)   
			{
				if(i ==0)
				{
					DebugPf("message send pending\r\n");
				}
			}
			else if(message_tx_status == CANTXFAILE)   
			{
					DebugPf("message send failed\r\n");
				break;
			}
			
			__NOP();
			__NOP();
			__NOP();
	    i++;
	  }
	
	  if(i==0x1FF) 
	  {
				CAN_CancelTransmit(CAN1,message_tx_status); //ȡ������
				return 0;  //fail
			
	  }
		else
	  {
	  		return 1;
	  }
		
}

///*******************************************************************************
//* Function Name  : USB_HP_CAN_TX_IRQHandler
//* Description    : This function handles USB High Priority or CAN TX interrupts 
//*                  requests.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void USB_HP_CAN1_TX_IRQHandler(void)
//{
//	  CTR_HP();	 //USB����
//}

///*******************************************************************************
//* Function Name  : USB_LP_CAN_RX0_IRQHandler
//* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
//*                  requests.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void USB_LP_CAN1_RX0_IRQHandler(void)
//{   
//	  USB_Istr();	 //USB����
	
//	u8 tmp=0;
//	u8 i =0;
//	
//			RxMessage.StdId=0x00;
//			RxMessage.ExtId=0x00;
//			RxMessage.IDE=0;
//			RxMessage.DLC=0;
//			RxMessage.FMI=0;
//			RxMessage.Data[0]=0x00;
//			RxMessage.Data[1]=0x00;
//			RxMessage.Data[2]=0x00;
//			RxMessage.Data[3]=0x00;
//			RxMessage.Data[4]=0x00;
//			RxMessage.Data[5]=0x00;
//			RxMessage.Data[6]=0x00;
//			RxMessage.Data[7]=0x00;
//	
//   if(SET == CAN_GetITStatus(CAN1,CAN_IT_FF0))
//   {
//        CAN_ClearITPendingBit(CAN1,CAN_IT_FF0);
//   }
//   else if(SET == CAN_GetITStatus(CAN1,CAN_IT_FOV0))
//   {
//        CAN_ClearITPendingBit(CAN1,CAN_IT_FOV0);
//   }
//   else
//   {
//		 tmp=CAN_MessagePending(CAN1,CAN_FIFO0);							//�жϽ����Ƿ�������
//		 if(tmp)
//		 {	 
//			 CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);		  		//����	

//			 for(i =0;i<RxMessage.DLC;i++)
//			 {
//				 DebugPf("%c",RxMessage.Data[i]);			 
//			 }		 
////		 ret = CanbusSendData(0x88,RxMessage.Data,RxMessage.DLC);
//			 CAN_FIFORelease(CAN1,CAN_FIFO0);//��fifo
//		 }		
//   } 
//}



