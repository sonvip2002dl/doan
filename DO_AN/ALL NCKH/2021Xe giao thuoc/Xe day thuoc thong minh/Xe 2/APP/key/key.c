#include <key.h>
#include <SysTick.h>

u8 key_data=0;

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO��ʼ���ṹ��	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//���� GPIOE GPIOA ʱ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;		//IO�� 5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	//���� ����
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	//GPIOE ��ʼ��
	
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
	return 0;
}

