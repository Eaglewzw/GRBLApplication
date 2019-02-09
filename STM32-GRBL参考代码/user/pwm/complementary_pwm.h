/***************************************************************/
#include "stm32f10x.h"
/***************************************************************/
#ifndef __COMPLEMENTARY_PWM_H
#define __COMPLEMENTARY_PWM_H 
/***************************************************************/



/*
	TIM1
	    B13    A8
		B14    A9
		B15    A10
		Break  B12	  ɲ������
	TIM8	
		C6     A7
		C7     B0
		C8     B1
		Break  A6	  ɲ������

	  TIM1_Init(1,10000,1,0,0,100,0);		 1->��һ�η�Ƶ  10000->���س�ֵ  1->OC1 ��  0->OC2 ��	 0->OC3 ��  100->����ʱ�� 0-> ɲ�����ƹر�
	  TIM1_OC1_Pulse(1,1,k);   	B13 A8   1-> + ռ�ձ�  1-> - ռ�ձ�
	  TIM1_OC2_Pulse(1,1,k);   	B14 A9   1-> + ռ�ձ�  1-> - ռ�ձ� 
	  TIM1_OC3_Pulse(1,1,k);   	B15 A10  1-> + ռ�ձ�  1-> - ռ�ձ� 

 */



void TIM1_Configuration(u16 Prescaler,u16 Period,u8 OC1,u8 OC2,u8 OC3,u8 DeadTime,u8 Open);
void TIM1_OC1_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);
void TIM1_OC2_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);
void TIM1_OC3_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);


void TIM8_Configuration(u16 Prescaler,u16 Period,u8 OC1,u8 OC2,u8 OC3,u8 DeadTime,u8 Open);
void TIM8_OC1_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);
void TIM8_OC2_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);
void TIM8_OC3_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);













#endif


