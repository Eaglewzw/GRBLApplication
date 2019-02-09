/***************************************************************/
#include "stm32f10x_it.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
/***************************************************************/
extern u8 USART_RX[60];
extern u8 USART_mark;
extern int USART_control;
extern u16 USART_RX_STA;       //����״̬���	
extern uint8_t serial_rx_buffer[];
/***************************************************************/
//void USART1_IRQHandler(void)
//{
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)     //Check whether receiving interrupt
//	{
//		USART_RX[USART_mark++] = USART_ReceiveData(USART1);   // Read one byte from the receive data register
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//		if(USART_mark ==60){USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);}			
//	}
//}


//void USART1_IRQHandler(void)
//{
//	u8 Res;

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������

//		if((USART_RX_STA&0x8000)==0)//����δ���
//		{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//			{
//					if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//					else USART_RX_STA|=0x8000;	//��������� 
//			}
//			else //��û�յ�0X0D
//			{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//				{
//					serial_rx_buffer[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(200-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//				}		 
//			}
//		}   		 
//	} 
//}

/***************************************************************/
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)     //Check whether receiving interrupt
	{
		USART_RX[USART_mark++] = USART_ReceiveData(USART2);     // Read one byte from the receive data register
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		if(USART_mark ==60){USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);}			
	}
}

/***************************************************************/
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)     //Check whether receiving interrupt
	{
		USART_RX[USART_mark++] = USART_ReceiveData(USART3);     // Read one byte from the receive data register
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		if(USART_mark ==60){USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);}			
	}
}
/***************************************************************/


