/* 
 * File:   AbnormalHandle.h
 * Author: Administrator
 *
 * Created on 2013��12��31��, ����1:27
 */

#ifndef ABNORMALHANDLE_H
#define	ABNORMALHANDLE_H


#include "Config.h"

#define MAX_ADRESS 2		// ������ ����0��modbus 0��ַȺ��
#define REPEAT_TIMES  2							 	//??????
#define MISTAKE_RNGE  5                                                         // ???? (*/100) mm
#define TIME_OUT 10								//???? 100ms (??)2ms

#ifdef	__cplusplus
extern "C" {
#endif

extern unsigned char ServoBusyBit[MAX_ADRESS];				//????
extern unsigned char ServoPauseBit[MAX_ADRESS];				//????
extern unsigned char ServoOriginBit[MAX_ADRESS];			//????
extern unsigned char ServoErrorBit[MAX_ADRESS];				//????
extern unsigned char ServoPwrOnBit[MAX_ADRESS];                         //??ON
extern int ServoCurrentPoint[MAX_ADRESS];                             //?????? ???
	

void Read_Status_Handle(unsigned char adress);								  					//��ʱ�������

unsigned int ServoInitialize(unsigned char AdressNum);			  	//�ŷ���ʼ������
unsigned int ServoGoOrigin(unsigned char AdressNum);			  	//�ŷ���ԭ�㺯��
unsigned int ServoGoAssignPoint(unsigned char AdressNum,unsigned int Point);  //�ŷ�ȥָ��λ��
unsigned int ServoSetSpeed(unsigned char AdressNum,unsigned int CSpeed);       //�ŷ�ȫ���ٶ�����


#ifdef	__cplusplus
}
#endif

#endif	/* ABNORMALHANDLE_H */

