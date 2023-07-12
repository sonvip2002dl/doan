#include <ano.h>
#include <usart.h>

u8 DataToSen[20]={0};


//�Զ����ʽ����
void Ano_SenF1(s16 a,u8 b,u8 c)	
{
	u8 cnt=0;	//λ��
	u8 sc=0;	//��У��
	u8 ac=0;	//����У��
	u8 i=0;
	
	DataToSen[cnt++]=0xAA;	//֡ͷ
	DataToSen[cnt++]=0xFF;	//��ַ
	DataToSen[cnt++]=0xF1;	//����
	DataToSen[cnt++]=2;		//���ݳ���
	
	//���ݲ��	���ֽ���ǰ
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
	
	//У�����
	for(i=0;i<DataToSen[3]+4;i++)
	{
		sc+=DataToSen[i];
		ac+=sc;
	}
	
	//У��λ
	DataToSen[cnt++]=sc;	//��У��
	DataToSen[cnt++]=ac;	//����У��
	
	Usart1_Send(DataToSen,cnt);	//�������� DataToSend
}

void Usart1_Send(unsigned char *DataToSend,u8 data_num)	//����1�����ַ�������
{
	u8 i;
	for(i=0;i<data_num;i++)
	{	
		USART_SendData(UART4, DataToSend[i]);  
		while(USART_GetFlagStatus(UART4, USART_FLAG_TC) != SET);     
	}
}
