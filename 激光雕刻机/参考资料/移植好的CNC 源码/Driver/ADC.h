#ifndef _ADC_H_	
#define _ADC_H_

#ifdef __cplusplus									  //�����CPP����C����
extern "C" {
#endif

#include "Config.h"

#define DR_ADDRESS                  ((uint32_t)0x4001244C)



extern uint16_t ADCPrimevalValue[6];

void AD1_Config(void);
u16 GetTemp(u16 advalue);
u16 GetVolt(u16 advalue);	
	
#ifdef __cplusplus		   //�����CPP����C���� //��������
}
#endif

#endif






