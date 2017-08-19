	#include "includes.h"
	/******************************************************
	* Name： main函数
	* Function：  子模块具体实现
	* Description： 
	* Author：  sun
	******************************************************/	

	int main()
	{
		
  //串口初始化
	Usart1_Init(9600);
	//清除接受结构体信息
	clearStruct();

	while(1)
	{
		//解析数据
		parseGpsBuffer();
		//打印数据
		printGpsBuffer();
	}
	

	}
					 




