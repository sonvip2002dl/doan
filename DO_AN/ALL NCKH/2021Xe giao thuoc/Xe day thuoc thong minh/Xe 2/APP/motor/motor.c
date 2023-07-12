#include "motor.h"


/* 电机初始化（全部的） */
void Motor_Init(u32 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	
	/* 初始化方向引脚 */
	/* 左轮 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/* 右轮 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	/* 静止 */
	AIN1=AIN2=0;
	BIN1=BIN2=0;
	
	
	/*  配置 PWM GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;  //PWM1 小于有效
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;  //有效值为 1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	
	/* 左轮 */
	TIM_OC1Init(TIM2,&TIM_OCInitStructure); //输出比较通道1初始化
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable); //使能TIMx在 CCR1 上的预装载寄存器
	
	/* 右轮 */
	TIM_OC2Init(TIM2,&TIM_OCInitStructure); //输出比较通道2初始化
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); //使能TIMx在 CCR2 上的预装载寄存器
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);  //使能预装载寄存器
	TIM_Cmd(TIM2,ENABLE); //使能定时器	
	
	/* 电机初始化（停止转动） */
	TIM_SetCompare1(TIM2,0);
	TIM_SetCompare2(TIM2,0);
}


/* 小车运动 */
void Motor_Motion(int pwm1,int pwm2)
{
	if(pwm1>=0)	//左轮
	{
		AIN1=0;
		AIN2=1;
	}
	else
	{
		AIN1=1;
		AIN2=0;
		pwm1=-pwm1;
	}
	
	if(pwm2>=0)  //右轮
	{
		BIN1=0;
		BIN2=1;
	}
	else
	{
		BIN1=1;
		BIN2=0;
		pwm2=-pwm2;
	}
	
	TIM_SetCompare1(TIM2,pwm2);  //左轮
	TIM_SetCompare2(TIM2,pwm1);  //右轮
}


void Motor_Limit(s16 *pwm)
{
	if(*pwm>6000)
	{
		*pwm=6000;
	}
	else
	{
		if(*pwm<-6000)
		{
			*pwm=-6000;
		}
	}
}

