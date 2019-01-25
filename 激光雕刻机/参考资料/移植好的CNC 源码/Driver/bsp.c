#include "Config.h"

/****************************************************************************
* ��	�ƣ�void  SysTickInit(void)
* ��	�ܣ�ϵͳʱ�� ucos��ʱ
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void SysTickInit(void)
{
	u32 cnts = 0;
  RCC_ClocksTypeDef rcc_clocks;

	RCC_GetClocksFreq(&rcc_clocks);									//��ȡϵͳƵ��	72M = 72,000,000
  cnts = (u32)rcc_clocks.HCLK_Frequency / OS_TICKS_PER_SEC;		//�δ�Ƶ�� 1/100��	��10ms
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_Config(cnts);   										//720000
}

///*******************************************************************************
//* Function Name  : RCC_Configuration
//* Description    : Configures the different system clocks.
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void RCC_Configuration(void)
//{
//  ErrorStatus HSEStartUpStatus;

//  RCC_DeInit();												//ʱ�ӿ��ƼĴ���ȫ���ָ�Ĭ��ֵ
//  RCC_HSEConfig(RCC_HSE_ON);								//�ⲿ����ʱ��Դ������8M����
//  HSEStartUpStatus = RCC_WaitForHSEStartUp();				//�ȴ��ⲿʱ�Ӿ���
//  if(HSEStartUpStatus == SUCCESS)							//���ʱ�������ɹ�
//  {
//    RCC_HCLKConfig(RCC_SYSCLK_Div1);						//����AHB�豸ʱ��Ϊϵͳʱ��1��Ƶ
//    RCC_PCLK2Config(RCC_HCLK_Div1);							//����APB2�豸ʱ��ΪHCLKʱ��1��Ƶ
//    RCC_PCLK1Config(RCC_HCLK_Div2);							//����APB1�豸ʱ��ΪHCLKʱ��2��Ƶ
//		RCC_ADCCLKConfig(RCC_PCLK2_Div6);						//����ADCCLKʱ��ΪPCLK2ʱ��6��Ƶ�����ܴ���14M
//		RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
//    FLASH_SetLatency(FLASH_Latency_2);						//�趨�ڲ�FLASH�ĵ���ʱ����Ϊ2����
//    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	//ʹ��FLASHԤ��ȡ������
//    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	//����PLLʱ��Ϊ�ⲿ����ʱ�ӵ�9��Ƶ��8MHz * 9 = 72 MHz
//    RCC_PLLCmd(ENABLE);										//ʹ��PLLʱ��
//    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)		//�ȴ�PLLʱ���������׼������
//    {
//    }
//    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);				//ʹ��PLLʱ����Ϊϵͳʱ��Դ
//    while(RCC_GetSYSCLKSource() != 0x08)					//����ϵͳ����ʱ��Դȷ��Ϊ�ⲿ���پ���8M����
//    {   }
//  }

//  /* �豸ʱ�ӿ��� */
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1   |			//ʹ����APB2ʱ�ӿ��Ƶ�����	
//   					 RCC_APB2Periph_AFIO   |	
// 						 RCC_APB2Periph_USART1 | 
//						 RCC_APB2Periph_GPIOA  |
//						 RCC_APB2Periph_GPIOB  |
//						 RCC_APB2Periph_GPIOC  |
//						 RCC_APB2Periph_GPIOD  |
//						 RCC_APB2Periph_GPIOE  |
//						 RCC_APB2Periph_GPIOF	 |
//						 RCC_APB2Periph_GPIOG, ENABLE);	   


//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC    |	//ʹ����APB1ʱ�ӿ��Ƶ�����
//  						 RCC_APB1Periph_TIM2   |			
//						   RCC_APB1Periph_USB    |
//						   RCC_APB1Periph_USART2 |
//						   RCC_APB1Periph_USB, ENABLE);	
//						 	
//  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		//ʹ��DMAʱ��
//	
//	

//}

/****************************************************************************
* ��	�ƣ�void  BSP_Init(void)
* ��	�ܣ�������ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void BSP_Init(void)		//Ӳ����Դ��ʼ��
{
unsigned int PowerON_Count;


	SystemInit(); 			//STM32ϵͳ��ʼ��
//	RCC_Configuration();
	Nvic_init();			//�жϹ����ʼ��
 							//�ڸ����ײ�������ʼ�����֮���ٽ������ģ����������Ĺ��罨���л����γ�HardFault_Handler
	/************************************/
	//UART ��ʼ��
	USART1_Config();		//����1��ʼ��		//PA9 PA10
//	USART2_Config();		//����2��ʼ��		//PA2 PA3
	
	Set_PrintfPort(1);	//����printf��ӡ����ö˿�
		
	/************************************/ 
	//GPIO ��ʼ��
	GPIO_Config();			//LED ָʾ��
				//
	BKP_Config();				//�󱸼Ĵ���
	I2C_EE_Init();
	
	/************************************/ 
	//W5500 ��ʼ��
//	W5500_Config();
	
	/************************************/
	//AD ��ʼ��
//	AD1_Config();
//	SPI_FLASH_SPI_Init();

/****************************************/
/**********USB Config********************/
/****************************************/
  USB_System();
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
	
	PowerON_Count = BKP_ReadBackupRegister(BKP_DR1);	 //�鿴�������Ƿ�ʧ
//	DebugPf("PowerON_Count = %d \r\n",PowerON_Count);

	PowerON_Count ++;
  BKP_WriteBackupRegister(BKP_DR1,PowerON_Count);

	SysTickInit();			//uCOSʱ��1ms; //��ʼ�� uC/OS-IIʱ�ӽ���
				
	
}



void beep(int i)
{
	BEEP_ON;
	Delay_MS(i);	
	BEEP_OFF;	
}


