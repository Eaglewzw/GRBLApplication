/***************************************************************/
#include "stm32f10x.h"
#include "complementary_pwm.h"
/***************************************************************/
#ifndef __PWM_H
#define __PWM_H 
/***************************************************************/
//Ƶ�ʼ���  �� 72M / Prescaler / Period 		  
//													   TIM8_PWM_init(36,40000,1,1,1,0); Ƶ��= 72M /36 /40000 =50 Hz  ��ʼ����ǰ����ͨ��
//													   TIM8_PWM_init(1,3600,0,0,0,1); Ƶ��= 72M /1 /3600 =20 KHz    ��ʼ���˺�һ��ͨ��
//���ռ�ձȼ��㹫ʽ��TIM_Pulse / Period
/***************************************************************/

void TIM1_PWM_Configuration(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
void TIM1_Change_Period(u16 NoteSet);
void Change_TIM1_OC1_Pulse(u16 Pulse);
void Change_TIM1_OC2_Pulse(u16 Pulse);
void Change_TIM1_OC3_Pulse(u16 Pulse);
void Change_TIM1_OC4_Pulse(u16 Pulse);
void Change_TIM1_OC1_Polarity(u8 i);
void Change_TIM1_OC2_Polarity(u8 i);
void Change_TIM1_OC3_Polarity(u8 i);
void Change_TIM1_OC4_Polarity(u8 i);


void TIM2_PWM_Configuration(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
void TIM2_Change_Period(u16 NoteSet);
void Change_TIM2_OC1_Pulse(u16 Pulse);
void Change_TIM2_OC2_Pulse(u16 Pulse);
void Change_TIM2_OC3_Pulse(u16 Pulse);
void Change_TIM2_OC4_Pulse(u16 Pulse);
void Change_TIM2_OC1_Polarity(u8 i);
void Change_TIM2_OC2_Polarity(u8 i);
void Change_TIM2_OC3_Polarity(u8 i);
void Change_TIM2_OC4_Polarity(u8 i);


void TIM3_PWM_Configuration(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
void TIM3_Change_Period(u16 NoteSet);
void Change_TIM3_OC1_Pulse(u16 Pulse);
void Change_TIM3_OC2_Pulse(u16 Pulse);
void Change_TIM3_OC3_Pulse(u16 Pulse);
void Change_TIM3_OC4_Pulse(u16 Pulse);
void Change_TIM3_OC1_Polarity(u8 i);
void Change_TIM3_OC2_Polarity(u8 i);
void Change_TIM3_OC3_Polarity(u8 i);
void Change_TIM3_OC4_Polarity(u8 i);


void TIM4_PWM_Configuration(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
void TIM4_Change_Period(u16 NoteSet);
void Change_TIM4_OC1_Pulse(u16 Pulse);
void Change_TIM4_OC2_Pulse(u16 Pulse);
void Change_TIM4_OC3_Pulse(u16 Pulse);
void Change_TIM4_OC4_Pulse(u16 Pulse);
void Change_TIM4_OC1_Polarity(u8 i);
void Change_TIM4_OC2_Polarity(u8 i);
void Change_TIM4_OC3_Polarity(u8 i);
void Change_TIM4_OC4_Polarity(u8 i);


void TIM5_PWM_Configuration(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
void TIM5_Change_Period(u16 NoteSet);
void Change_TIM5_OC1_Pulse(u16 Pulse);
void Change_TIM5_OC2_Pulse(u16 Pulse);
void Change_TIM5_OC3_Pulse(u16 Pulse);
void Change_TIM5_OC4_Pulse(u16 Pulse);
void Change_TIM5_OC1_Polarity(u8 i);
void Change_TIM5_OC2_Polarity(u8 i);
void Change_TIM5_OC3_Polarity(u8 i);
void Change_TIM5_OC4_Polarity(u8 i);

void TIM8_PWM_Configuration(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
void TIM8_Change_Period(u16 NoteSet);
void Change_TIM8_OC1_Pulse(u16 Pulse);					   //	  TIM5_Change_Period(999);
void Change_TIM8_OC2_Pulse(u16 Pulse);					   //	  Change_TIM5_OC1_Pulse(800);	 ռ�ձ�Ϊ80%   Ƶ��Ϊ 72  KHz
void Change_TIM8_OC3_Pulse(u16 Pulse);					   //	  TIM5_Change_Period(9999);
void Change_TIM8_OC4_Pulse(u16 Pulse);					   //	  Change_TIM5_OC1_Pulse(8000);	 ռ�ձ�Ϊ80%   Ƶ��Ϊ 7.2 KHz
void Change_TIM8_OC1_Polarity(u8 i);
void Change_TIM8_OC2_Polarity(u8 i);
void Change_TIM8_OC3_Polarity(u8 i);
void Change_TIM8_OC4_Polarity(u8 i);

#endif
