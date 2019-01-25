#ifndef _USART2_INIT_H_	
#define _USART2_INIT_H_

#ifdef __cplusplus			//�����CPP����C����
extern "C" {
#endif

#include "stm32f10x.h"
#include "static_init.h"	//���ڽṹ��

#define USART2BaudRate		115200		   			  //���崮��1�Ĳ�����	
//���ջ���������
#define USART2_RX_BUFF_SIZEMAX 100
#define USART2_TX_BUFF_SIZEMAX 100



typedef struct                                                          //
{
 unsigned char RX_Flag;                                                 // 
 unsigned char RX_TMEP_Len;  
 unsigned char RX_Len;                                                  //  
 unsigned char RX_TEMP_BUFF[USART2_RX_BUFF_SIZEMAX];                    //��ʱ����
 unsigned char RX_BUFF[USART2_RX_BUFF_SIZEMAX];                     		//�ڶ�����
}
UsartRxTypeDef1;

extern UsartRxTypeDef1 USARTStructure2;
extern unsigned char USART2_TX_BUFF[USART2_TX_BUFF_SIZEMAX];   

void USART2_Config(void);		  						//��������
void USART2_RX_Buffer_Clear(void); 				//��ս��ջ�����

void USART2_SendByte(u8 Data);							//���ַ����ݷ���
void USART2_SendString(u8* Data,u32 Len);		//���ַ�����
void USART2_DMASendData(u8* Data,u32 Len);	//DMA���ֽڷ���

	
	

#ifdef __cplusplus		   //�����CPP����C���� //��������
}
#endif

#endif



