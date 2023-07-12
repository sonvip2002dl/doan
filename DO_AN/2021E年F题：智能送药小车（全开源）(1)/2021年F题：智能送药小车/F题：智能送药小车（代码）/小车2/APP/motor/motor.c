#include "motor.h"


/* �����ʼ����ȫ���ģ� */
void Motor_Init(u32 per,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	
	/* ��ʼ���������� */
	/* ���� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //�������
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //�������
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	/* ���� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //�������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;  //�������
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	/* ��ֹ */
	AIN1=AIN2=0;
	BIN1=BIN2=0;
	
	
	/*  ���� PWM GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  //�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  //�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //�Զ�װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�������ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;  //PWM1 С����Ч
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;  //��ЧֵΪ 1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	
	/* ���� */
	TIM_OC1Init(TIM2,&TIM_OCInitStructure); //����Ƚ�ͨ��1��ʼ��
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable); //ʹ��TIMx�� CCR1 �ϵ�Ԥװ�ؼĴ���
	
	/* ���� */
	TIM_OC2Init(TIM2,&TIM_OCInitStructure); //����Ƚ�ͨ��2��ʼ��
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); //ʹ��TIMx�� CCR2 �ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM2,ENABLE);  //ʹ��Ԥװ�ؼĴ���
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��	
	
	/* �����ʼ����ֹͣת���� */
	TIM_SetCompare1(TIM2,0);
	TIM_SetCompare2(TIM2,0);
}


/* С���˶� */
void Motor_Motion(int pwm1,int pwm2)
{
	if(pwm1>=0)	//����
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
	
	if(pwm2>=0)  //����
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
	
	TIM_SetCompare1(TIM2,pwm2);  //����
	TIM_SetCompare2(TIM2,pwm1);  //����
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

