#include "includes.h"

//���������Ϣ�Ľṹ�����
struct GPS_Data Save_Data;
/*****************************
��������clrStruct
������������

��������ֵ����
�������ܣ�������սṹ����Ϣ
����������
****************************/

void clearStruct()
{
  Save_Data.isGetData= false;
	Save_Data.isParseData= false;
	Save_Data.isUsefull= false;
	//���
	memset(Save_Data.GPS_Buffer,0,200);
	memset(Save_Data.UTCTime, 0, 20);
	memset(Save_Data.latitude, 0, 20);
	memset(Save_Data.N_S, 0, 2);
	memset(Save_Data.longitude, 0, 20);
	memset(Save_Data.E_W, 0, 2);

}

/*****************************
��������parseGpsBuffer
������������

��������ֵ����
�������ܣ��������սṹ����Ϣ
����������
*****************************/
void parseGpsBuffer(void)
{
	char *subString=NULL;
	char *subStringNext=NULL;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;//�����жϽ���һ�Ρ�����һ��
//		printf("**************\r\n");
//		printf(Save_Data.GPS_Buffer);
    //����������Ϣ
		for (i = 0 ; i <= 9 ; i++)
		{
			if (i == 0)
			{
				//������յ���������Ϣ��û��, 
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//��������
			}
			else
			{
				subString++;//��һ��,���ֵ�λ�õ���һ���ַ�����
				if ((subStringNext = strstr(subString, ",")) != NULL)//��һ��,���ߵ�λ��
				{
					char usefullBuffer[2]; 
					switch(i) //��ȡ����,֮����ַ�����
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//��λ��Ϣ�Ƿ���Ч
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//��ȡγ����Ϣ
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//��ȡN/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//��ȡ������Ϣ
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//��ȡE/W
            case 7:break;
						case 8:break;
						case 9:memcpy(Save_Data.UTCDay, subString, subStringNext - subString);break;	//��ȡUTC����
						default:break;
					}

					subString = subStringNext; //ָ����һ��,��������Ϣ
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;
				}
				else
				{
					errorLog(2);	//��������
				}
			}
		}
	}
}
/*****************************
��������printGpsBuffer
������������

��������ֵ����
�������ܣ���ӡ���յ�������Ϣ
����������
*****************************/
void printGpsBuffer(void)
{
	u8 year,month,day,hour,minute,second;
	double latitude,longitude;
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		//���ʱ��
		hour =(Save_Data.UTCTime[0]-'0')*10+(Save_Data.UTCTime[1]-'0')+8;
		minute =(Save_Data.UTCTime[2]-'0')*10 +(Save_Data.UTCTime[3]-'0');
		second =(Save_Data.UTCTime[4]-'0')*10 +(Save_Data.UTCTime[5]-'0');
		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			//���γ��
			latitude= atof( Save_Data.latitude); 
			// ����stdlib.h ���ַ���(s)ת��Ϊ˫���ȵĸ�������
			latitude/=100;
      //��þ���
			longitude= atof( Save_Data.longitude);
			longitude/=100;
			//�������
			year =(Save_Data.UTCDay[4]-'0')*10+(Save_Data.UTCDay[5]-'0');
			month =(Save_Data.UTCDay[2]-'0')*10 +(Save_Data.UTCDay[3]-'0');
			day =(Save_Data.UTCDay[0]-'0')*10 +(Save_Data.UTCDay[1]-'0');
			
			
			printf("��ǰʱ��: 20%d-%d-%d %d:%d:%d\r\n",year,month,day,hour,minute,second);
			printf("��ǰγ�� %s:%f��\r\n",Save_Data.N_S,latitude);
			printf("��ǰ���� %s:%f��\r\n",Save_Data.E_W,longitude);
		 }
		else
		{
			printf("GPS DATA is not usefull!\r\n");
		}
		
	}
}
void errorLog(int num)
{
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}



