#include <pwm.h>

void Tim1_Pwm_Init(u16 pre,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //定义GPIO初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;	//定时器初始化结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;	//PWM初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	    //使能定时器3 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能 GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//使能 时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;		//IO口 5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//传输速率 50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE);  //改变指定管脚的映射	
	
	TIM_TimeBaseInitStruct.TIM_Period=pre;	//设置定时器周期
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;	//设置定时器预分频器
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;	
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;	// PWM1模式
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;	//输出级性 低电平 有效
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	//输出使能
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable); //使能TIMx在 CCR2 上的预装载寄存器
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);//使能预装载寄存器
	
	
	TIM_Cmd(TIM1,ENABLE);	//使能定时器
	
	
}
