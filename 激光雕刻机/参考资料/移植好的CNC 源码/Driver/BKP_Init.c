#include "BKP_Init.h"


/****************************************************************************
* ��	�ƣ�
* ��	�ܣ�������
* ��ڲ�������
* ���ڲ�������
* ˵	����
//BKP_WriteBackupRegister(BKP_DR1, FirstBackupData);
//BKP_ReadBackupRegister(BKP_DR10);			
****************************************************************************/
void BKP_Config(void) 
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE); 	
	BKP_ClearFlag(); 	
	BKP_TamperPinLevelConfig(BKP_TamperPinLevel_Low); 	
	BKP_ITConfig(ENABLE); 
	BKP_TamperPinCmd(DISABLE); 
}
/*******************************/








