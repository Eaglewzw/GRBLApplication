

#ifndef _HMIGT02_H_	
#define _HMIGT02_H_

#ifdef __cplusplus		   				//�����CPP����C���� //��ʼ����
extern "C" {
#endif


#include "Config.h"
	

	
	
enum status		 //ö��
{
	TIMEOUT=0, //��ʱ//У����� //����

	AUTO=1,	   //�Զ�ģʽ10
	MANU=2,	   //�ֶ�ģʽ20
	SETT=4,	   //����ģʽ40
	REST=5,		 //ϵͳ��λ80
	M000=16,		 // 0 λ��
	M180=32,		 // 180λ��
	JUP=64,	   //΢����
	JDW=128,	   //΢����
	SAVE_Q=256,	   //����ѯ��
	SAVE_Y=512,	   //������
	SAVE_N=1024,	   //�����
};
extern enum status TOUCH_KEY;


unsigned long Get_Key(void);
unsigned long HexStringToInt(unsigned char *Command,unsigned char len);
	

#ifdef __cplusplus		   				//�����CPP����C���� //��������
}




#endif

#endif


