#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/6/16
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

void TIM3_4_PWM_Init(u32 arr,u32 psc);
void TIM3_3_PWM_Init(u32 arr3,u32 psc3);
void TIM2_3_PWM_Init(u32 arr3,u32 psc3);
void TIM2_4_PWM_Init(u32 arr4,u32 psc4);
#endif
