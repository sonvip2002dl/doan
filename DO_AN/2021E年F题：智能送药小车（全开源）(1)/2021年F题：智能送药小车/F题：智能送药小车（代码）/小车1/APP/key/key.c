#include <key.h>
#include <SysTick.h>

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO��ʼ���ṹ��	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//���� GPIOE GPIOA ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//���� GPIOE GPIOA ʱ��
	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;		//IO�� 5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	//���� ����
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	//GPIOE ��ʼ��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;		//IO�� 5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//���� ����
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	//GPIOE ��ʼ��
}


u8 Key_Scam()
{
	if(k0==1)
	{
		delay_ms(10);
		if(k0==1)
		{
			return 1;
		}
	}
	
	if(k1==0)
	{
		delay_ms(10);
		if(k1==0)
		{
			while(k1==0);
			return 2;
		}
	}
	return 0;
}

