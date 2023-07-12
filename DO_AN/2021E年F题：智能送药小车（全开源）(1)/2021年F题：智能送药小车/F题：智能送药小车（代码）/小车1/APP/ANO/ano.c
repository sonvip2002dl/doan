#include <ano.h>
#include <usart.h>

u8 DataToSen[20]={0};


//自定义格式发送
void Ano_SenF1(s16 a,u8 b,u8 c)	
{
	u8 cnt=0;	//位置
	u8 sc=0;	//和校验
	u8 ac=0;	//附加校验
	u8 i=0;
	
	DataToSen[cnt++]=0xAA;	//帧头
	DataToSen[cnt++]=0xFF;	//地址
	DataToSen[cnt++]=0xF1;	//功能
	DataToSen[cnt++]=2;		//数据长度
	
	//数据拆分	低字节在前
	DataToSen[cnt++]=BYET0(a);
	DataToSen[cnt++]=BYET1(a);
//	DataToSen[cnt++]=BYET2(a);
//	DataToSen[cnt++]=BYET3(a);
	
//	DataToSen[cnt++]=BYET0(b);
//	DataToSen[cnt++]=BYET1(b);
//	DataToSen[cnt++]=BYET2(b);
//	DataToSen[cnt++]=BYET3(b);
	
//	DataToSen[cnt++]=BYET0(c);
//	DataToSen[cnt++]=BYET1(c);
//	DataToSen[cnt++]=BYET2(c);
//	DataToSen[cnt++]=BYET3(c);
	
	//校验计算
	for(i=0;i<DataToSen[3]+4;i++)
	{
		sc+=DataToSen[i];
		ac+=sc;
	}
	
	//校验位
	DataToSen[cnt++]=sc;	//和校验
	DataToSen[cnt++]=ac;	//附加校验
	
	Usart1_Send(DataToSen,cnt);	//发送数组 DataToSend
}

void Usart1_Send(unsigned char *DataToSend,u8 data_num)	//串口1发送字符串函数
{
	u8 i;
	for(i=0;i<data_num;i++)
	{	
		USART_SendData(UART4, DataToSend[i]);  
		while(USART_GetFlagStatus(UART4, USART_FLAG_TC) != SET);     
	}
}
