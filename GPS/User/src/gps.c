#include "includes.h"

//定义接收信息的结构体变量
struct GPS_Data Save_Data;
/*****************************
函数名：clrStruct
函数参数：无

函数返回值：无
函数功能：清除接收结构体信息
函数描述：
****************************/

void clearStruct()
{
  Save_Data.isGetData= false;
	Save_Data.isParseData= false;
	Save_Data.isUsefull= false;
	//清空
	memset(Save_Data.GPS_Buffer,0,200);
	memset(Save_Data.UTCTime, 0, 20);
	memset(Save_Data.latitude, 0, 20);
	memset(Save_Data.N_S, 0, 2);
	memset(Save_Data.longitude, 0, 20);
	memset(Save_Data.E_W, 0, 2);

}

/*****************************
函数名：parseGpsBuffer
函数参数：无

函数返回值：无
函数功能：解析接收结构体信息
函数描述：
*****************************/
void parseGpsBuffer(void)
{
	char *subString=NULL;
	char *subStringNext=NULL;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;//串口中断接收一次。解析一次
//		printf("**************\r\n");
//		printf(Save_Data.GPS_Buffer);
    //解析数据信息
		for (i = 0 ; i <= 9 ; i++)
		{
			if (i == 0)
			{
				//如果接收到的数据信息中没有, 
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//解析错误
			}
			else
			{
				subString++;//第一个,出现的位置的下一个字符数据
				if ((subStringNext = strstr(subString, ",")) != NULL)//下一个,出线的位置
				{
					char usefullBuffer[2]; 
					switch(i) //提取两个,之间的字符数据
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//获取UTC时间
						case 2:memcpy(usefullBuffer, subString, subStringNext - subString);break;	//定位信息是否有效
						case 3:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//获取纬度信息
						case 4:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//获取N/S
						case 5:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//获取经度信息
						case 6:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//获取E/W
            case 7:break;
						case 8:break;
						case 9:memcpy(Save_Data.UTCDay, subString, subStringNext - subString);break;	//获取UTC日期
						default:break;
					}

					subString = subStringNext; //指向下一个,后数据信息
					Save_Data.isParseData = true;
					if(usefullBuffer[0] == 'A')
						Save_Data.isUsefull = true;
					else if(usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;
				}
				else
				{
					errorLog(2);	//解析错误
				}
			}
		}
	}
}
/*****************************
函数名：printGpsBuffer
函数参数：无

函数返回值：无
函数功能：打印接收的数据信息
函数描述：
*****************************/
void printGpsBuffer(void)
{
	u8 year,month,day,hour,minute,second;
	double latitude,longitude;
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		//获得时间
		hour =(Save_Data.UTCTime[0]-'0')*10+(Save_Data.UTCTime[1]-'0')+8;
		minute =(Save_Data.UTCTime[2]-'0')*10 +(Save_Data.UTCTime[3]-'0');
		second =(Save_Data.UTCTime[4]-'0')*10 +(Save_Data.UTCTime[5]-'0');
		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			//获得纬度
			latitude= atof( Save_Data.latitude); 
			// 包含stdlib.h 将字符串(s)转换为双精度的浮点数据
			latitude/=100;
      //获得经度
			longitude= atof( Save_Data.longitude);
			longitude/=100;
			//获得日期
			year =(Save_Data.UTCDay[4]-'0')*10+(Save_Data.UTCDay[5]-'0');
			month =(Save_Data.UTCDay[2]-'0')*10 +(Save_Data.UTCDay[3]-'0');
			day =(Save_Data.UTCDay[0]-'0')*10 +(Save_Data.UTCDay[1]-'0');
			
			
			printf("当前时间: 20%d-%d-%d %d:%d:%d\r\n",year,month,day,hour,minute,second);
			printf("当前纬度 %s:%f°\r\n",Save_Data.N_S,latitude);
			printf("当前经度 %s:%f°\r\n",Save_Data.E_W,longitude);
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



