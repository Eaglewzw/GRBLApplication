

#ifndef _MODBUS_H_
#define _MODBUS_H_

#ifdef __cplusplus		   //�����CPP����C���� //��ʼ����
extern "C" {
#endif
 
#include "stm32f10x.h"

	
#define SlaveID 0x01				// �ӻ�ID��
	
//����ȫ��16λ
	
#define 	MBPARTADRESS 			1000	
#define 	MBPUBLICADRESS 		2000
	
extern unsigned int Modbus_Port[16];						// ��ַ��1000 
extern unsigned int Modbus_Public_Var[128];			// ��ַ��2000

unsigned int crc16(unsigned char* puchMsg,unsigned char usDataLen);
void ParseRecieve(void);  //������	
	
	
	
void Nvic_init(void);	   //�жϹ����ʼ��

#ifdef __cplusplus		   //�����CPP����C���� //��������
}
#endif

#endif

