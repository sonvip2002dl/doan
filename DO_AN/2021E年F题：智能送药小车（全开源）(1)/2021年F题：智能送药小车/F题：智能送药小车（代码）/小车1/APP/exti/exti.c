#include <exti.h>
#include <SysTick.h>
#include "motion.h"

void Exti_Init()	//�������޿���ʱ�ӣ���ΪLED���ѿ���
{
	 NVIC_InitTypeDef NVIC_InitStructure;
	 EXTI_InitTypeDef EXTI_InitStructure;
	 GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO��ʼ���ṹ��
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//���� GPIOE GPIOA ʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//���� AFIO ʱ��SSS
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);	//ѡ��GPIO A0 �ܽ������ⲿ�ж���·
	 
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;		//IO�� 13
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	//���� ����
	 GPIO_Init(GPIOA,&GPIO_InitStructure); 	//GPIOE ��ʼ��
	 
	 NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;	//EXTI0�ж�ͨ��
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//��ռ���ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	//�����ȼ�
	 NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	//IRQͨ��ʹ��
	 NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	 
	 
	 EXTI_InitStructure.EXTI_Line=EXTI_Line8;	//ѡ���ж��� 0	
	 EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	//�ж�ģʽ	
	 EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;	//�����ش���		
	 EXTI_InitStructure.EXTI_LineCmd=ENABLE;	//�ж���ʹ��
	 EXTI_Init(&EXTI_InitStructure);	//����ָ��������ʼ��EXTI
	 
}


void EXTI9_5_IRQHandler()	//�ⲿ�ж�0����
{
	if(EXTI_GetITStatus(EXTI_Line8)==1)	//�ж��ж���0�����жϷ���
	{
		kting=100;
	}
	EXTI_ClearITPendingBit(EXTI_Line8);	//����жϱ�־λ
}

