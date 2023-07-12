#include <key.h>
#include <SysTick.h>

void Key_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;  //定义GPIO初始化结构体	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//开启 GPIOE GPIOA 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//开启 GPIOE GPIOA 时钟
	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;		//IO口 5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	//下拉 输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); 	//GPIOE 初始化
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;		//IO口 5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//上拉 输入
	GPIO_Init(GPIOB,&GPIO_InitStructure); 	//GPIOE 初始化
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

