#include <exti.h>
#include <SysTick.h>
#include "motion.h"

void Exti_Init()	//本程序无开启时钟，因为LED中已开启
{
	 NVIC_InitTypeDef NVIC_InitStructure;
	 EXTI_InitTypeDef EXTI_InitStructure;
	 GPIO_InitTypeDef GPIO_InitStructure;  //定义GPIO初始化结构体
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//开启 GPIOE GPIOA 时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//开启 AFIO 时钟SSS
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);	//选择GPIO A0 管脚用作外部中断线路
	 
	 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;		//IO口 13
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;	//上拉 输入
	 GPIO_Init(GPIOA,&GPIO_InitStructure); 	//GPIOE 初始化
	 
	 NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;	//EXTI0中断通道
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//抢占优先级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	//子优先级
	 NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	//IRQ通道使能
	 NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	 
	 
	 EXTI_InitStructure.EXTI_Line=EXTI_Line8;	//选择中断线 0	
	 EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	//中断模式	
	 EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;	//上升沿触发		
	 EXTI_InitStructure.EXTI_LineCmd=ENABLE;	//中断线使能
	 EXTI_Init(&EXTI_InitStructure);	//根据指定参数初始化EXTI
	 
}


void EXTI9_5_IRQHandler()	//外部中断0函数
{
	if(EXTI_GetITStatus(EXTI_Line8)==1)	//判断中断线0有无中断发生
	{
		kting=100;
	}
	EXTI_ClearITPendingBit(EXTI_Line8);	//清除中断标志位
}

