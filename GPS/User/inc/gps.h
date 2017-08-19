#ifndef GPS_H
#define GPS_H

#include "stm32f4xx.h"

#define false 0
#define true 1
	
//����GPS�Ľ���֡�����ݸ�ʽ�ṹ��

struct GPS_Data
{
	//��������ݳ���
 char GPS_Buffer[200];
	//
 char isGetData;
	//�Ƿ�������
 char isParseData;
	//UTCʱ��
	char UTCTime[20];
	//γ��
	char latitude[20];
	//N_S
	char N_S[2];
	//����
	char longitude[20];
	//E_W
	char E_W[2];
	//��λ��Ϣ�Ƿ�����
	char isUsefull;
	//UTC����
	char UTCDay[20];
	
};
extern struct GPS_Data Save_Data;

void clearStruct(void);
void errorLog(int num);
void parseGpsBuffer(void);
void printGpsBuffer(void);


#endif


