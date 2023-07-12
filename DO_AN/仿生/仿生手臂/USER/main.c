#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "timer.h"

//ALIENTEK 探索者STM32F407开发板 实验9
//PWM输出实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart3_init(9600);//初始化串口波特率为115200
	uart1_init(9600);
 	TIM3_3_PWM_Init(20000-1,84-1);
	TIM3_4_PWM_Init(20000-1,84-1);
	TIM2_3_PWM_Init(20000-1,84-1);
	TIM2_4_PWM_Init(20000-1,84-1);
//	TIM2_Int_Init(5000-1,84-1);
	TIM_SetCompare3(TIM2,1500);
	TIM_SetCompare4(TIM2,500);
	TIM_SetCompare3(TIM3,1500);
	TIM_SetCompare4(TIM3,1500);
	
   while(1) //实现比较值从0-300递增，到300后从300-0递减，循环
	{
//		TIM_SetCompare3(TIM3,800);
//		TIM_SetCompare4(TIM3,1500);
//		delay_ms(1000);
//		
//		TIM_SetCompare3(TIM3,500);
//		TIM_SetCompare4(TIM3,1500);
//		delay_ms(1000);
//		
////		TIM_SetCompare3(TIM3,2500);
//		TIM_SetCompare4(TIM3,1000);
//		delay_ms(1000);
	}
}
