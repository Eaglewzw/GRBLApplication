#ifndef _USART1_INIT_H_	
#define _USART1_INIT_H_

#ifdef __cplusplus									  //�����CPP����C����
extern "C" {
#endif

#include "Config.h"

#define USART1BaudRate		115200		   			  //���崮��1�Ĳ�����
//#define USART1RxRank    	4						  //����1���ն������	������8�� 

//#define USART1RXMAXRANK    (0x01<<(USART1RxRank-1))	  //������εĽ������ȼ�

	
/*************************************///Grbl_serial
#ifndef RX_BUFFER_SIZE
  #define RX_BUFFER_SIZE 128
#endif
#ifndef TX_BUFFER_SIZE
  #define TX_BUFFER_SIZE 64
#endif

#define SERIAL_NO_DATA 0xff
	
extern uint8_t rx_buffer[RX_BUFFER_SIZE];
extern uint8_t rx_buffer_head;
extern volatile uint8_t rx_buffer_tail;

extern uint8_t tx_buffer[TX_BUFFER_SIZE];
extern uint8_t tx_buffer_head;
extern volatile uint8_t tx_buffer_tail;

void serial_write(uint8_t data);
/****************************************/

//typedef struct                                                          //�ṹ��
//{
// unsigned char RX_Flag;                                                 //����״̬		01248
// unsigned char RX_Len;                                                  //���յ��ó���	(������ģʽʹ��)�ַ�ģʽʹ��\0����
//          char RX_Buffer[60];                                           //���յ������ݻ���
//}UsartRxTypeDef;

//extern UsartRxTypeDef USARTStructure1;	   //���ڽṹ��

char Transchar(char r);

void USART1_Config(void);		  								//��������
//void USART1_RX_Buffer_Clear(void); 						//��ս��ջ�����

void USART1_SendByte(u8 Data);								//���ַ����ݷ���
void USART1_SendString(u8* Data,u32 Len);			//���ַ�����
void USART1_DMASendString(u8* Data,u32 Len);	//DMA���ַ�����


void U1ProtocolAnalysis(void);

uint8_t serial_read(void);
void serial_reset_read_buffer(void);

#ifdef __cplusplus		   //�����CPP����C���� //��������
}
#endif

#endif
