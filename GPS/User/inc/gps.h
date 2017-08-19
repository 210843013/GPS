#ifndef GPS_H
#define GPS_H

#include "stm32f4xx.h"

#define false 0
#define true 1
	
//定义GPS的接受帧的数据格式结构体

struct GPS_Data
{
	//整体的数据长度
 char GPS_Buffer[200];
	//
 char isGetData;
	//是否解析完成
 char isParseData;
	//UTC时间
	char UTCTime[20];
	//纬度
	char latitude[20];
	//N_S
	char N_S[2];
	//经度
	char longitude[20];
	//E_W
	char E_W[2];
	//定位信息是否有用
	char isUsefull;
	//UTC日期
	char UTCDay[20];
	
};
extern struct GPS_Data Save_Data;

void clearStruct(void);
void errorLog(int num);
void parseGpsBuffer(void);
void printGpsBuffer(void);


#endif


