#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include <motor.h>
#include <time6.h>  
#include <encoder.h>
#include "motion.h"
#include "exti.h"
#include "pwm.h"
#include "key.h"


int main()
{
	u16 i=0;
	u8 key=0;
	
	SysTick_Init(72);
	LED_Init();
	Key_Init();
	
	
	
	Motor_Init(7200-1,10);
	Tim1_Pwm_Init(20000-1,72-1);
	
	TIM_SetCompare1(TIM1,1400);  //中端 左
	//TIM_SetCompare1(TIM1,1040);
	////////////////////////////TIM_SetCompare1(TIM1,1040);  //中端 右
	//TIM_SetCompare1(TIM1,1100);  //中端 右
	//TIM_SetCompare1(TIM1,1500);    //远端1  左1
	//TIM_SetCompare1(TIM1,1350);    //远端1  左1
	//TIM_SetCompare1(TIM1,1490);
	
	//TIM_SetCompare1(TIM1,1520);
	//TIM_SetCompare1(TIM1,1480);
	
	////////////////////////////////TIM_SetCompare1(TIM1,1525);  
	  
	 //TIM_SetCompare1(TIM1,1090);

	
	Usart3_Init(115200);
	Uart4_Init(115200);
	
	Encoder_Init();

	while(k210_mubiao==0);
	
	Usart1_Init(115200);
	LED2=!LED2;
	while(key!=1)
	{
		key=Key_Scam();
		if(key==2)
		{
			ditu=1;
			LED2=!LED2;
		}
	}
	Usart4_Ditu(10);
	
	delay_ms(100);

	Tim6_Init(1000-1,720-1);  //10ms 进一次中断

	
	while(1)
	{		
		i++;
		if(i%50==0)
		{
			i=0;
			LED2=!LED2;
			//printf("LLLLLLL");
		}
		//USART_SendData(USART2,123);	//向串口1发送数据
		//while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);	//等待数据发送结束

		delay_ms(10);
		
	}
}
