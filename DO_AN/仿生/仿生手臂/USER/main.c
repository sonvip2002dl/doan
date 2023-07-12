#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "timer.h"

//ALIENTEK ̽����STM32F407������ ʵ��9
//PWM���ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart3_init(9600);//��ʼ�����ڲ�����Ϊ115200
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
	
   while(1) //ʵ�ֱȽ�ֵ��0-300��������300���300-0�ݼ���ѭ��
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
