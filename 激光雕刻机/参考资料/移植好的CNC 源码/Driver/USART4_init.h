#ifndef _USART4_INIT_H_	
#define _USART4_INIT_H_

#ifdef __cplusplus			//�����CPP����C����
extern "C" {
#endif

#include "Config.h"
#include "stm32f10x.h"
#include "static_init.h"	//���ڽṹ��

#define USART4BaudRate		19200		   			  //���崮��1�Ĳ�����	
//���ջ���������
#define USART4_RX_BUFF_SIZEMAX 100
#define USART4_TX_BUFF_SIZEMAX 100

typedef struct                                                          //�ṹ��
{
 unsigned char RX_Flag;                                                 //����״̬		01248
 unsigned char RX_Len;                                                  //���յ��ó���	(������ģʽʹ��)�ַ�ģʽʹ��\0����
          char RX_BUFF[USART4_RX_BUFF_SIZEMAX];                                           //���յ������ݻ���
}UsartRxTypeDef4;

extern UsartRxTypeDef4 USARTStructure4;
extern unsigned char USART4_TX_BUFF[USART4_TX_BUFF_SIZEMAX];   


extern unsigned char Rx4_String[60];	  			  //??????? ??lrc???????
extern unsigned char Rx4_Flag;  

void USART4_Config(void);		  						//��������
void USART4_RX_Buffer_Clear(void); 				//��ս��ջ�����

void USART4_SendByte(u8 Data);							//���ַ����ݷ���
void USART4_SendString(char * Data,u32 Len);		//���ַ�����
void Send_Command(unsigned char *str);
void Get_Command(void);

#ifdef __cplusplus		   //�����CPP����C���� //��������
}
#endif

#endif



