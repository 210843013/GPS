	#include "includes.h"
	/******************************************************
	* Name�� main����
	* Function��  ��ģ�����ʵ��
	* Description�� 
	* Author��  sun
	******************************************************/	

	int main()
	{
		
  //���ڳ�ʼ��
	Usart1_Init(9600);
	//������ܽṹ����Ϣ
	clearStruct();

	while(1)
	{
		//��������
		parseGpsBuffer();
		//��ӡ����
		printGpsBuffer();
	}
	

	}
					 




