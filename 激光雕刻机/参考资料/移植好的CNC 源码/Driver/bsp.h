#ifndef _BSP_H_	
#define _BSP_H_

#ifdef __cplusplus		   //�����CPP����C���� //��ʼ����
extern "C" {
#endif

#include "stm32f10x.h"				//STM32�⺯��
#include "nvic_init.h"	   			//�жϹ���
#include "USART1_init.h"			//����1
#include "USART2_init.h"			//����2
#include "printf_init.h"			//��ӡ�˿�
#include "Grbl_config.h"	
//ErrorStatus HSEStartUpStatus;

#define OS_TICKS_PER_SEC 100		//�δ�Ƶ��(ucosϵͳƵ��)��100��֮1�룬10ms

#define SYSTEM_VERSION 0   			//ϵͳ�汾

void BSP_Init(void);				//Ӳ����Դ��ʼ��
void beep(int i);
	
#ifdef __cplusplus		   			//�����CPP����C���� //��������
}
#endif

#endif
