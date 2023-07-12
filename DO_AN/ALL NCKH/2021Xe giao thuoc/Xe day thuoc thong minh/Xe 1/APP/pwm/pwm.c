#include <pwm.h>

void Tim1_Pwm_Init(u16 pre,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO��ʼ���ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;	//��ʱ����ʼ���ṹ��
	TIM_OCInitTypeDef TIM_OCInitStructure;	//PWM��ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);	    //ʹ�ܶ�ʱ��3 ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//ʹ�� GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//ʹ�� ʱ��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;		//IO�� 5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	//�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	//�������� 50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE);  //�ı�ָ���ܽŵ�ӳ��	
	
	TIM_TimeBaseInitStruct.TIM_Period=pre;	//���ö�ʱ������
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;	//���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;	
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;	// PWM1ģʽ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;	//������� �͵�ƽ ��Ч
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	//���ʹ��
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable); //ʹ��TIMx�� CCR2 �ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);//ʹ��Ԥװ�ؼĴ���
	
	
	TIM_Cmd(TIM1,ENABLE);	//ʹ�ܶ�ʱ��
	
	
}
