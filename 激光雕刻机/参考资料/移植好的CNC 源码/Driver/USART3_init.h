#ifndef _USART3_INIT_H_	
#define _USART3_INIT_H_

#ifdef __cplusplus			//�����CPP����C����
extern "C" {
#endif

#include "stm32f10x.h"
#include "static_init.h"	//���ڽṹ��

#define USART3BaudRate		115200		   			  //���崮��1�Ĳ�����	
//���ջ���������
#define USART3_RX_BUFF_SIZEMAX 100
#define USART3_TX_BUFF_SIZEMAX 100



typedef struct                                                          //
{
 unsigned char RX_Flag;                                                 // 
 unsigned char RX_Len;                                                  //  
 unsigned char RX_BUFF[USART3_RX_BUFF_SIZEMAX];                     		//�ڶ�����
}
UsartRxTypeDef3;

extern UsartRxTypeDef3 USARTStructure3;
extern unsigned char USART3_TX_BUFF[USART3_TX_BUFF_SIZEMAX];   

void USART3_Config(void);		  						//��������
void USART3_RX_Buffer_Clear(void); 				//��ս��ջ�����
void TIM4_Config(void);
void TIM4_NVIC_Init(void);
void USART3_SendByte(u8 Data);							//���ַ����ݷ���
void USART3_SendString(char * Data,u32 Len);		//���ַ�����
void USART3_DMASendData( char * Data,u32 Len);	//DMA���ֽڷ���

	
	

#ifdef __cplusplus		   //�����CPP����C���� //��������
}
#endif

#endif



