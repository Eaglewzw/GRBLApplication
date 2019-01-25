#ifndef __IAICONTROL_H
#define __IAICONTROL_H


#include "Config.h"

//extern const uchar Ascill_16[];
//extern uchar Rx4_String[40];	  				//���ܵ����ַ��� ȥ��lrcУ�鼰�س�����	extern
//extern uchar Rx4_Flag;

unsigned int IAI_Set_OrderEnable(unsigned char AdressNum);						//��������ģʽ��Чָ��
unsigned int IAI_Set_ServoON(unsigned char AdressNum);							//�����ŷ�ONָ��
unsigned int IAI_Set_ServoOFF(unsigned char AdressNum);							//�����ŷ�OFFָ��
unsigned int IAI_Set_Speed(unsigned char AdressNum,unsigned char CSpeed ); 		//���õ�ǰ�ٶ�ָ��						
unsigned int IAI_Set_Pause(unsigned char AdressNum);                                    //������ָͣ��
unsigned int IAI_Set_ClearPause(unsigned char AdressNum);
unsigned int IAI_Set_ClearArm(unsigned char AdressNum);							//�����������ָ��
unsigned int IAI_Go_Origin(unsigned char AdressNum);				  			//��ԭ��ָ��
unsigned int IAI_Go_Zero(unsigned char AdressNum);							//�����ָ��
unsigned int IAI_Go_AssignPoint(unsigned char AdressNum,int Point);		//��ָ��λ��ָ��

unsigned int Read_CurrentStatus(unsigned char AdressNum);						//��ȡ��ǰ״ָ̬��
unsigned int Read_ErrorCode(unsigned char AdressNum);							//��ȡ�������ָ��
unsigned int Read_CurrentPoint(unsigned char AdressNum);						     //��ȡ��ǰλ��ָ��

unsigned int IAI_Send_WData(unsigned char AdressNum,unsigned char *WData);		 //����д���ݺ�ķ���ֵ
unsigned int IAI_Send_Flag(unsigned char AdressNum,unsigned char *Command);		  //���Ͷ�ȡ���ݺ�ķ���ֵ
unsigned int IAI_Send_Command(unsigned char AdressNum,unsigned char *Command);	  //���Ϳ��������ķ���ֵ

unsigned char LRC_DATA(unsigned char *str);                                      // LRC X���ݴ���
//unsigned char ChrToInt(unsigned char chr);					 														 //ʮ�������ַ���תʮ����
unsigned char StringCompare(unsigned char *Command);                            //�ַ����Ƚ�
void Clear_Rx4_String(void);                                                    //������ջ�������ȫ���ַ�����־λ
//unsigned char Get_Strlen(unsigned char *Command);                                //�����ַ����ĳ���

#endif /* __END_*/



