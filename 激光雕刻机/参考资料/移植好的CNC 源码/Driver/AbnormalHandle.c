 /***********************************************************************************************
 Ŀ��壺ControlBoard V1.0������
 �����ܣ�MODUBUS ��λ����ģ�� �����ط�����
 Э�飺 Modbusͨ��Э��  19200 n.8.1
 ���̽������ڣ�2013.12.9
 ��д�ˣ�����
 �޸�1��
 �޸�2��
*************************************************************************************************/

#include "AbnormalHandle.h"

unsigned int Error_Code;

unsigned char ServoBusyBit[MAX_ADRESS];				//????
unsigned char ServoPauseBit[MAX_ADRESS];			//????
unsigned char ServoOriginBit[MAX_ADRESS];			//????
unsigned char ServoErrorBit[MAX_ADRESS];			//????
unsigned char ServoPwrOnBit[MAX_ADRESS];			//??ON
int ServoCurrentPoint[MAX_ADRESS];            //?????? XYZ

/*******************************************************************************
* Function Name  :
* Description    : ����ʱ ��ȡ��ǰλ��,��������,PCIO״̬
********************************************************************************/
void Read_Status_Handle(unsigned char adress)
{
    unsigned int RET;
    unsigned char adres,i;
    unsigned char max_adres;

    switch (adress)
    {
        case 0:
            adres=1;                        //XYZ��
            max_adres=MAX_ADRESS;
            break;
        case 1:
            adres=1;                        //��X��
            max_adres=2;
            break;
        case 2:
            adres=2;                        //��Y��
            max_adres=3;
            break;
        case 3:
            adres=3;                        //��Z��
            max_adres=4;
            break;
        default:                            //��ַ����
            adres=4;
            max_adres=4; 
            break;
    }
    for(i=adres;i<max_adres;i++)
    {
				RET=Read_CurrentStatus(i);
				if(RET != 0xffff)
				{
					if(RET & 0x0008) 	ServoBusyBit[i]=1;                      //�ŷ�æµ  BIT(3)
					else			ServoBusyBit[i]=0;

					if(RET & 0x0020) 	ServoPauseBit[i]=1;			//�ŷ���ͣ	BIT(5)
					else			ServoPauseBit[i]=0;

					if(RET & 0x0010) 	ServoOriginBit[i]=1;                    //�ŷ�ԭ��	BIT(4)
					else			ServoOriginBit[i]=0;

					if(RET & 0x0400) 	ServoErrorBit[i]=1;			//�ŷ�����	BIT(10)
					else			ServoErrorBit[i]=0;

					if(RET & 0x1000) 	ServoPwrOnBit[i]=1;			//�ŷ�ON 	BIT(12)
					else			ServoPwrOnBit[i]=0;
				}

        Delay_MS(10);      
        RET=Read_ErrorCode(i);                                                   //��������
        if(RET != 0xffff)
        {
            switch (i)
            {
            case 1:
                Error_Code = RET|0x1000;                                         //����ı�������
                break;
            case 2:
                Error_Code = RET|0x2000;
                break;
            case 3:
                Error_Code = RET|0x4000;
                break;
            default:break;
            }
        }

				Delay_MS(10);
        RET=Read_CurrentPoint(i);                                               //��ȡ�ŷ���ǰλ�ã����ԣ�
        if(RET != 0xffff)
        {
             ServoCurrentPoint[i]= RET;
        }
    }

}
/*******************************************************************************
* Function Name  :
* Description    : �ŷ���ʼ��
* Parameter		 : 1 or 2 or 3
* Return		 :
********************************************************************************/
unsigned int ServoInitialize(unsigned char AdressNum)
{
    unsigned char i=1;

    ServoBusyBit[AdressNum]=0;			//�ŷ�æµ
    ServoPauseBit[AdressNum]=0;			//�ŷ���ͣ
    ServoOriginBit[AdressNum]=0;                //�ŷ�ԭ��
    ServoErrorBit[AdressNum]=0;			//�ŷ�����
    ServoPwrOnBit[AdressNum]=0;			//�ŷ�ON
 
   i=0;
   while(i<REPEAT_TIMES)			  			//����ģʽ����
   {
        if(IAI_Set_OrderEnable(AdressNum) == 0x8000)		  	//ʧ���ط�
        {
                break;                                                  //�ɹ�����
        }
        Delay_MS(10);
        i++;
   }

   i=0;
   while(i<REPEAT_TIMES)			  			 //�������
   {
   		if(IAI_Set_ClearArm(AdressNum) == 0x8000)		 //ʧ���ط�
		{
			break;                                           //�ɹ�����
		}
		Delay_MS(10);
		i++;
   }
   IAI_Set_ClearPause(AdressNum);                                       //�����ͣ����

   i=0;
   while(i<REPEAT_TIMES)			  			 //�ŷ�ON
   {
   		if(IAI_Set_ServoON(AdressNum) == 0x8000)		 //ʧ���ط�
		{
			break;						 //�ɹ�����
		}
		Delay_MS(10);
		i++;
   }

   Read_Status_Handle(AdressNum);

   return 0x0000;
}

/*******************************************************************************
* Function Name  :
* Description    : �ŷ��ٶ�����
* Parameter		 : 1 or 2 or 3
* Return		 :
********************************************************************************/
unsigned int ServoSetSpeed(unsigned char AdressNum,unsigned int CSpeed)
{
unsigned char i=0;

   while( i<REPEAT_TIMES )						//�����ٶ�����
   {
   		if(IAI_Set_Speed(AdressNum,CSpeed) == 0x8000)		//ʧ���ط�
		{
			break;                                          //�ɹ�����
		}
		Delay_MS(10);
		i++;
   }
   if( i >= REPEAT_TIMES )	   return 0xA010+AdressNum*3;
   return 0;
}

/*******************************************************************************
* Function Name  :
* Description    : �ŷ���ԭ��
* Parameter		 : 1 or 2 or 3
* Return		 :
********************************************************************************/
unsigned int ServoGoOrigin(unsigned char AdressNum)
{
unsigned char i=0;

   while( i<REPEAT_TIMES )						//��ԭ������
   {
   		if(IAI_Go_Origin(AdressNum) == 0x8000)		  		//ʧ���ط�
		{
			break;									    //�ɹ�����
		}
		Delay_MS(10);
		i++;
   }
   if( i >= REPEAT_TIMES )	   return 1;
   return 0;
}

/*******************************************************************************
* Function Name  :
* Description    : �ŷ��ƶ�ָ��λ��
* Parameter		 :  ��ַ λ��
* Return		 :
********************************************************************************/
unsigned int ServoGoAssignPoint(unsigned char AdressNum,unsigned int Point)
{
unsigned char i=0;
   while( i<REPEAT_TIMES )		  				//ȥָ��λ��
   {
   		if(IAI_Go_AssignPoint(AdressNum, Point) == 0x8000)	//ʧ���ط�
		{
			break;								    	//�ɹ�����
		}
		Delay_MS(10);
		i++;
   }
   if( i >= REPEAT_TIMES )	   return 1;
   return 0;
}


