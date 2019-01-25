#include "ADC.h"   

uint16_t ADCPrimevalValue[6];
/****************************************************************************
* ��	�ƣ�void AD1_GPIO_Init(void)
* ��	�ܣ��������ų�ʼ��
* ��ڲ�������
* ���ڲ�������
* ˵	������
****************************************************************************/
void AD1_GPIO_Init(void)						//�������ų�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;		//�������Žṹ
	
	//�������ŷ���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

/*����PC0 1 2 3 4 5 Ϊģ������(ADC Channel 10 11 12 13 14 15 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5; 	 //ADC��������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	       			//�˿�ģʽΪģ�����뷽ʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   			//��ת�ٶ�Ϊ50M
  GPIO_Init(GPIOC, &GPIO_InitStructure);			   			//�����ϼ���������ʼ��PC��
}
/*******************************************************************************
* Function Name  : ADC_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Configuration(void)
{
  ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);  				 //72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;				 //������ת��ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;		  				 //����ɨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   				 //��������ת��ģʽ
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ADC�ⲿ���أ��ر�״̬
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   			 //���뷽ʽ,ADCΪ12λ�У��Ҷ��뷽ʽ
  ADC_InitStructure.ADC_NbrOfChannel = 6;	 						 //����ͨ������6��
  ADC_Init(ADC1, &ADC_InitStructure);
 //ADC�����¶ȴ�����ʹ�ܣ�Ҫʹ��Ƭ���¶ȴ��������м�Ҫ��������    
	ADC_TempSensorVrefintCmd(ENABLE);   

  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);	//ADCͨ���飬 ��10��ͨ�� ����˳��1��ת��ʱ�� 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_55Cycles5);	//ADCͨ���飬 ��11��ͨ�� ����˳��2��ת��ʱ�� 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_55Cycles5);	//ADCͨ���飬 ��12��ͨ�� ����˳��3��ת��ʱ�� 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 5, ADC_SampleTime_55Cycles5);	//ADCͨ���飬 ��13��ͨ�� ����˳��4��ת��ʱ��                           											
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 6, ADC_SampleTime_55Cycles5);	//ADCͨ���飬 ��14��ͨ�� ����˳��5��ת��ʱ��                           											
 // ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 6, ADC_SampleTime_55Cycles5);	//ADCͨ���飬 ��15��ͨ�� ����˳��6��ת��ʱ��                           											

 //����ת������2��ͨ��16���ڲ��¶ȴ�������������ʱ��>2.2us,(239cycles)    
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 4, ADC_SampleTime_55Cycles5);  
	
  ADC_DMACmd(ADC1, ENABLE);											 //ʹ��ADC1 DMA 
  ADC_Cmd(ADC1, ENABLE);                                 			 //ʹ��ADC1
  ADC_ResetCalibration(ADC1);							 			 //����ADC1У׼�Ĵ���
  while(ADC_GetResetCalibrationStatus(ADC1));			 			 //�õ�����У׼�Ĵ���״̬
  ADC_StartCalibration(ADC1);							 			 //��ʼУ׼ADC1
  while(ADC_GetCalibrationStatus(ADC1));				 			 //�õ�У׼�Ĵ���״̬
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 			 //ʹ��ADC1��������ƿ�ʼת��ADC,ͨ��DMA��ʽ���ϵĸ���RAM����
}

/*******************************************************************************
* Function Name  : DMA_Configuration(void)
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;        								//DMA��ʼ���ṹ������
 	
  DMA_DeInit(DMA1_Channel1);		  										//����DMA1�ĵ�һͨ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = DR_ADDRESS;		  			//DMA��Ӧ������ADC����ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCPrimevalValue;   	//�ڴ�洢����ַ�û�����
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//DMA��ת��ģʽΪSRCģʽ����������Ƶ��ڴ�
  DMA_InitStructure.DMA_BufferSize = 6;		   								//DMA�����С��5��
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//����һ�����ݺ��豸��ַ��ֹ����
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					//�رս���һ�����ݺ�Ŀ���ڴ��ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //�����������ݿ��Ϊ16λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  		//DMA�������ݳߴ磬HalfWord����Ϊ16λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   						//ת��ģʽ��ѭ������ģʽ��
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;						//DMA���ȼ���
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  					    //M2Mģʽ����
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);          
 		 /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
}

/****************************************************************************
* ��	�ƣ�void AD1_Config(void)
* ��	�ܣ�AD����
* ��ڲ�������
* ���ڲ�������
* ˵	����Ĭ��Ϊ�����ݽ���					 
****************************************************************************/
void AD1_Config(void)
{
	ADC_Configuration();				//AD��ʼ��
	AD1_GPIO_Init();			//AD���ų�ʼ��
	DMA_Configuration();
}

//����������ʵ�ʵ�ѹ/�¶�ת����
//u16 GetTemp(u16 advalue)   
//{   
//    u32 Vtemp_sensor;   
//    s32 Current_Temp;   
//      
////    ADCת�������Ժ󣬶�ȡADC_DR�Ĵ����еĽ����ת���¶�ֵ���㹫ʽ���£�    
////          V25 - VSENSE    
////  T(��) = ------------  + 25    
////           Avg_Slope    
////   V25��  �¶ȴ�������25��ʱ �������ѹ������ֵ1.43 V��    
////  VSENSE���¶ȴ������ĵ�ǰ�����ѹ����ADC_DR �Ĵ����еĽ��ADC_ConvertedValue֮���ת����ϵΪ��    
////            ADC_ConvertedValue * Vdd    
////  VSENSE = --------------------------    
////            Vdd_convert_value(0xFFF)    
////  Avg_Slope���¶ȴ����������ѹ���¶ȵĹ�������������ֵ4.3 mV/�档    
//   
//    Vtemp_sensor = advalue * 330 / 4096;   
//    Current_Temp = (s32)(143 - Vtemp_sensor)*10000/43 + 2500;   
//    return (s16)Current_Temp; 
//}    
 
/*******************************************************************************
* Function Name  : GetTemp
* Description    : ����ADC��������¶�
* Input          : u16 advalue
* Output         : 
* Return         : u16 temp
*******************************************************************************/
u16 GetTemp(u16 advalue)
{
    vu16 Current_Temp;
    
//    ADCת�������Ժ󣬶�ȡADC_DR�Ĵ����еĽ����ת���¶�ֵ���㹫ʽ���£�
//          V25 - VSENSE
//  T(��) = ------------  + 25
//           Avg_Slope
//   V25��  �¶ȴ�������25��ʱ �������ѹ������ֵ1.43 V��
//  VSENSE���¶ȴ������ĵ�ǰ�����ѹ����ADC_DR �Ĵ����еĽ��ADC_ConvertedValue֮���ת����ϵΪ�� 
//            ADC_ConvertedValue * Vdd
//  VSENSE = --------------------------
//            Vdd_convert_value(0xFFF)
//  Avg_Slope���¶ȴ����������ѹ���¶ȵĹ�������������ֵ4.3 mV/�档

    Current_Temp = (1.42 - advalue*3.288/4096)*1000/4.35 + 25; 
    return (s16)Current_Temp;
}

u16 GetVolt(u16 advalue)   
{
   
    return (u16)(advalue * 3288 / 4096);   
} 
