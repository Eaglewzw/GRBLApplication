#ifndef _CONFIG_H_	
#define _CONFIG_H_

#ifdef __cplusplus		   //�����CPP����C���� //��ʼ����
extern "C" {
#endif

#include <math.h>
#include <string.h>			//�ַ����Ƚ�
#include <ctype.h>			//��дת��
#include <stdlib.h>

 #include "stm32f10x.h"		//STM32�̼���
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
	
#include "bsp.h"			//�弶��ʼ��
#include "static_init.h"	//DebugPf
#include "GPIO_Init.h"
#include "BKP_Init.h"

#include "socket.h"
#include "w5500.h"

#include "SPI1_Init.h"
#include "SPI2_Init.h"
#include "spi_flash.h"
#include "I2CEEPROM.h"
#include "ADC.h"   
//USB
#include "USB_config.h"
#include "usb_istr.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "platform_config.h"
//File
#include "ff.h"
#include "diskio.h"
#include "fatfs_app.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "gcode.h"
#include "protocol.h"
#include "settings.h"
#include "stepper.h"
#include "limits.h"

#include "cnc.h"

#define LED_LED1_OFF()   GPIO_SetBits(GPIOA, GPIO_Pin_1 );  	   //LED1 
#define LED_LED1_ON()  GPIO_ResetBits(GPIOA, GPIO_Pin_1 ); 	  


extern uint8 buffer[2048];/*����һ��2KB�Ļ���*/
extern const unsigned char Ascill_16[];


#ifdef __cplusplus		   //�����CPP����C���� //��������
}

#endif

#endif
