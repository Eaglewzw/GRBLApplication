#include "HMIGT02.h"


enum status TOUCH_KEY;

//------------------------------------------------------------------------
//�������ܣ���ü�ֵ	
//?01WRR0000**	
//------------------------------------------------------------------------
unsigned long Get_Key(void)
{
	unsigned char i=0;
	unsigned long Keynum;
	
	USART3_RX_Buffer_Clear();	
	USARTStructure3.RX_Flag=0; 
	
	USART3_DMASendData("?01WRR00100001**\r",21);
	Delay_MS(10);

	while((USARTStructure3.RX_Flag != 1) && (i<50))
	{			
		i++;
		Delay_MS(1);	
		if(i>49)  return 0;					  		  	//ͨ�ų�ʱ���˳�
	}

	if(USARTStructure3.RX_Len == 12)							//�жϽ��ճ���
	{
		if((USARTStructure3.RX_BUFF[2]=='1')&&(USARTStructure3.RX_BUFF[5]=='R'))	  //վ�ź�״̬����
		{
			
			Keynum = HexStringToInt(&USARTStructure3.RX_BUFF[6],4);
//			DebugPf("%ld",Keynum);
//			if (USARTStructure3.RX_BUFF[8] == '6')
//			{
//				
//			}
//			switch(USARTStructure3.RX_BUFF[8])
//			{
//				case '0':			//ģʽ
//							if(USARTStructure3.RX_BUFF[9]=='1')	  	
//							{
//								TOUCH_KEY=AUTO;   //�Զ�ģʽ10
//							}
//							else if(USARTStructure3.RX_BUFF[9]=='2')
//							{
//								TOUCH_KEY=MANU;   //�ֶ�ģʽ20
//							}
//							else if(USARTStructure3.RX_BUFF[9]=='4')
//							{
//								TOUCH_KEY=SETT;		//����ģʽ40
//							}
//							else if(USARTStructure3.RX_BUFF[9]=='8')
//							{
//								TOUCH_KEY=REST;	
//							}
//							else
//							{								
//								TOUCH_KEY=LDLE;
//							}
//	
//							break;
//				case '1':
//								TOUCH_KEY=M000;	
//							break;
//				case '2':	
//								TOUCH_KEY=M180;
//							break;
//				case '4':	
//								TOUCH_KEY=JUP;	
//							break;
//				case '8':	
//								TOUCH_KEY=JDW;	
//							break;
//				default:	break;
//			}	
//			
		}		
		else
		{
			return 0;			
		}
	}
	else
	{
		return 0;
	}
	
	return Keynum;
}



//*******************************************************************************
//* Function Name  :
//* Description    :
//*******************************************************************************/
unsigned long HexStringToInt(unsigned char *Command,unsigned char len)
{
    char i=0;
    unsigned long num=0;
    unsigned char byt=0;
    unsigned char tempstr;
				
			for(i = len; i>0 ;i--)
			{
					tempstr=(*Command);
					byt=ChrToInt(tempstr);
					num=num+byt*pow(16,i-1);
					Command++;
			}
			
    return num;
}



