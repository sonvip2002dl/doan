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






//TIM_SetCompare1(TIM1,1730);  //远端 左 左
//TIM_SetCompare1(TIM1,1400);  //远端 左 右
//TIM_SetCompare1(TIM1,1650);  //远端 右 左
//TIM_SetCompare1(TIM1,1300);  //中端 右 右



int main()
{
	u16 i=0;
	
	
	SysTick_Init(72);
	LED_Init();
	Key_Init();
	
	
	Motor_Init(7200-1,10);
	Tim1_Pwm_Init(20000-1,72-1);
	//TIM_SetCompare1(TIM1,1500);  //中端 左
	
	TIM_SetCompare1(TIM1,1600);  //中端 左
	//TIM_SetCompare1(TIM1,1100);  //中端 右
	//TIM_SetCompare1(TIM1,1500);    //远端1  左1
	//TIM_SetCompare1(TIM1,1350);    //远端1  左1
	//TIM_SetCompare1(TIM1,1490);
  

	Usart1_Init(115200);
	Usart3_Init(115200);
	Uart4_Init(115200);
	Encoder_Init();
	
//	while(1)
//	{
//		Motor_Motion(3000,3000);
//		delay_ms(10);
//		printf("%d  %d\r\n",Encoder_Read(3),Encoder_Read(4));
//	}
	mot1=0;
//	while(1)
//	{
//		//printf("AA");
//		printf("%d    %d\r\n",Encoder_Read(3),Encoder_Read(4));
//		delay_ms(1000);
//		Motor_Motion(2000,2000);
//	}
//

	k210_r=7;
	delay_ms(1500);
	delay_ms(1500);
	
	while(k210_mubiao==0);
	LED2=!LED2;  
//	delay_ms(1000);
//	

	while(Key_Scam()==0 && ce1==0);
	if(Key_Scam()==1)
	{
		key_data=1;
	}
	else
	{
		key_data=0;
	}
	
	//k210_mubiao=4;
	Tim6_Init(1000-1,720-1);  //10ms 进一次中断
	
	
	while(1)
	{		
		//printf("AAAA\r\n");
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
