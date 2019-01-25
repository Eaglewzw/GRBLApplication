/******************** (C) COPYRIGHT 2013 STMicroelectronics ********************
* File Name          : main.c
* Author             : 
* Version            : V2.0.1
* Date               : 01/09/2014
* Description        : 
*******************************************************************************/
#include "Config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

char buffer1[4096];   	/* file copy buffer */
char writefbuff[1024];

uint16 pc_port_commun=8000;		/*����һ������˿ڲ���ʼ��	ͨ��ʹ��*/	
#define  SOCK_COMMUN	 1	
	
unsigned int Host_order;
uint8 buffer[2048];		/*����һ��2KB�Ļ���*///���绺��
	
void SocketHandle(void);	
void WorkingFromSDfile(void);	
void TimerSetup4(void);
	
FATFS fatfs;
FRESULT fres;
	
int main(void)
{
	static unsigned char run_cycle_count = 0;
//	int i,val = 1;
    BSP_Init();										//Board Init
	OutputControl(0x0000);				//�ر����ж˿�
	
	settings_init();
//	settings_reset(true);				//ʹ��Ĭ�ϲ���
	st_init(); 
	
	memset(&sys, 0, sizeof(sys));
	sys.abort = true;   // Set abort to complete initialization
  sys.state = STATE_INIT;  // Set alarm state to indicate unknown initial position 
	init_grbl();
//	TimerSetup4();
	PWR_ON; 
	Delay_MS(100);
	if (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == SUCCESS)
	{
	//	DebugPf("*** CNC Control system boot ok***\r\n");
	}
	else
	{
		//DebugPf("*** Boot Fail [ HSE ]");
	}
	
	fres = f_mount(0, &fatfs);	//����SD��
	if (fres != FR_OK)
	{
		//DebugPf("Mount SD error [0x%x]\n", fres);
	}
	else
	{
		DWORD fre_clust;
		FATFS *fs1;
		fres = f_getfree("", &fre_clust, &fs1);
	//	DebugPf("FreeSpace:%ld MB\n",(fre_clust /2048));
	}
	
//	for(i=0;i<16;i++)
//	{		
//		OutputControl(val);
//		val<<=1;
//		Delay_MS(100);
//	}
	beep(500);	
	FAN_ON;
	
	if(ReadTestboardID() == 1)
	{
		WorkingFromSDfile();	//��ȡSD���ļ���ִ��
	}

	while(1)
	{
		protocol_process();
//		SocketHandle();	
	
		/********************************/ //MCU����ָʾ��
		Delay_MS(1);	
		run_cycle_count++;
				
		if(run_cycle_count == 100)
		{
			LED_LED1_ON();
		}	
		else if(run_cycle_count >= 200)
		{
			LED_LED1_OFF();
			run_cycle_count = 0;
		}
		/********************************/
	} 
}

///*******************************************************************************
//* Function Name  : ���ڴ���
//* Description    : 
//********************************************************************************/
//void SocketHandle(void)
//{
//	static uint8 status = 0;
//	uint16 len=0;

//		status = getSn_SR(SOCK_COMMUN);		//8000�˿�
//    switch(status)			/*��ȡsocket0��״̬*/
//    {
//       case SOCK_INIT: 	/*socket��ʼ�����*/
//			 
//         //connect(0, pc_ip ,pc_port);							/*��TCP Clientģʽ���������������������*/ 
//				 listen(SOCK_COMMUN);												/*��TCP Serverģʽ���������������������*/
//				 DebugPf("1 W5500 connecting \r\n");
//         break;
//			 
//       case SOCK_ESTABLISHED:									/*socket���ӽ���*/ 
//				 
//         if(getSn_IR(SOCK_COMMUN) & Sn_IR_CON)
//         {
//            setSn_IR(SOCK_COMMUN, Sn_IR_CON);	/*Sn_IR�ĵ�0λ��1*/
//         }      
//         len=getSn_RX_RSR(SOCK_COMMUN);				/*lenΪ�ѽ������ݵĴ�С*/
//         if(len>0)
//         {
//            recv(SOCK_COMMUN,buffer,len);			/*W5500��������Sever������*/
//         }
//         break;
//       case SOCK_CLOSE_WAIT:									/*socket�ȴ��ر�״̬*/
//					DebugPf("1 W5500 wait close \r\n");
//					close(SOCK_COMMUN);
//					break;
//       case SOCK_CLOSED:											/*socket�ر�*/
//					DebugPf("1 W5500 closed \r\n");
//         	socket(SOCK_COMMUN,Sn_MR_TCP,pc_port_commun,Sn_MR_ND);/*��socket0��һ���˿�*/
//					break;
//    }	
//}


void WorkingFromSDfile()
{

uint32_t len = 0;
FRESULT res;
FIL file;
	
		sys.abort = 0;
		sys.auto_start = true;//true
	
		res = f_open(&file,"0:/test/data.nc", FA_OPEN_EXISTING | FA_READ);
		if (res == FR_OK) 
		{
				char riadok[100];

				while (f_gets(riadok, sizeof (riadok), &file) != NULL)  
				{
					len++;
					gc_execute_line(riadok);			//�����ļ��в��ɴ��\\r
					DebugPf("[Gcode %d] %s",len,riadok);
					protocol_execute_runtime();	//	CNC
					
//					while(sys.state == STATE_CYCLE)	//�ȴ�����ִ�����
//					{
//						if(sys.state == STATE_HOLD) break;
//						if(sys.state == STATE_IDLE) break;
//						if(sys.execute == EXEC_CYCLE_STOP) break;
//					}			

					if(sys.abort) break;
				}
				DebugPf("Work finish\r\n");
		}	
		sys.abort = 0;
		f_close (&file); 
}


//void TimerSetup4(void) 
//{
//	  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;                     // enable clock for TIM4

////		TIM4->PSC = 1124;                          // set prescaler
////		TIM4->PSC = 28;                          // set prescaler	1/40sekundy
//		TIM4->PSC = 10;                          // set prescaler	1/40sekundy
//		TIM4->ARR = 63999;  											// set auto-reload
//		TIM4->CR1 = 0;                            // reset command register 1
//		TIM4->CR2 = 0;                            // reset command register 2
//		TIM4->DIER = (1<<0);                      // Update interrupt enabled
//		TIM4->CR1 |= (1<<0);                      // Enable Timer
//		NVIC_EnableIRQ (TIM4_IRQn);               // Enable TIM4 interrupt
//		NVIC_SetPriority(TIM4_IRQn, 3);
//} 

//void TIM4_IRQHandler(void)
//{
//	static char Timer4Ticks = 0;
//	
//  if ((TIM4->SR & 0x0001) != 0)                  // check interrupt source
//	{
//    TIM4->SR &= ~(1<<0);                          // clear UIF flag
//		if(ShowPos)
//		{
//				lcd_x = 50 + (sys.position[X_AXIS] / (settings.steps_per_mm[X_AXIS] / 6));
//				lcd_y = 50 + (sys.position[Y_AXIS] / (settings.steps_per_mm[Y_AXIS] / 6));

//				Timer4Ticks++;
//				if(Timer4Ticks >= 60)
//				{
//					printpos_grbl(0,480);
//					Timer4Ticks = 0;
//				}
//		}
//	}
//}

