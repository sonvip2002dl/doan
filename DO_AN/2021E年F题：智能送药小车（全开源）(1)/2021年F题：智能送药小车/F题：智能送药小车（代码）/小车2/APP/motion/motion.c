#include "motion.h"
#include "motor.h"
#include "usart.h"
#include "SysTick.h"

u8 kting=0;
u16 mot=0;  //1 ת��  99 ֹͣ  70 ��ת���
u16 motx=0;
u8  mot1=0;
u8  mot2=0;
u8  mot3=0;
u8  mot4=0;
u8  mot5=0;


// ǰ�� forw: ��ʮ��·�ںͷ���ֹͣ
// pp: 1 ��ת90��  2 ��ת90��
char Moton_Forward(u16 forw,u8 pp)
{
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;  
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1); //�޷�
	Motor_Limit(&pwm2); //�޷�
	Motor_Motion(pwm1,pwm2);  //���pwm
	
	if(kting==100)
	{
		kting=0;
		switch(forw)
		{	
			case(1):  //��������ǰֹͣ
				Motor_Motion(-1500,-1500);
				delay_ms(70);
				Motor_Motion(0,0);
				mot=99;
				break;
			case(2):  //��ʮ��·��ת��
				delay_ms(500);
				Motor_Motion(-1500,-1500);
				delay_ms(70);
				Motor_Motion(0,0);
				//Motion_Spin(pp);  //��ת90��
				kting=0;
				//printf("liuhaijuci");
				return 1;
				break;
			case(3):  //���ſ�ֹͣ
				delay_ms(1000);
				Motor_Motion(-1500,-1500);
				delay_ms(70);
				Motor_Motion(0,0);
				mot=99;
				motx=2;
		}
	}	
	return 0;
}


// ת�� turn: 1 ��ת   2 ��ת
void Motion_Turn(u8 turn)
{
	mot=1;
	if(turn==1)
	{
		Motor_Motion(1600,3500);
	}
	else
	{
		if(turn==2)
		{
			Motor_Motion(3500,1600);
		}
	}
}


/* ǰ��30cm */
void Motion_Front()
{
	Motor_Motion(3000,3000);
	delay_ms(500);
	Motor_Motion(-1000,-1000);
	delay_ms(80);
	Motor_Motion(0,0);
}


/* ����30cm */
void Motion_After()
{
	Motor_Motion(-3000,-3000);
	delay_ms(1000);
	Motor_Motion(1000,1000);
	delay_ms(80);
	Motor_Motion(0,0);
	
	delay_ms(500);
	
	Motion_Spin(1);
}


void Motion_Spin(u8 spin)
{
	if(spin==1)
	{
		mot=2;
		Motor_Motion(-3000,3000);
	}
	else
	{
		mot=2;
		Motor_Motion(3000,-3000);
	}
	delay_ms(370); 
	Motor_Motion(1000,-1000); 
	delay_ms(70); 
	Motor_Motion(0,0);
	mot=70;
}


void Motion_Jin(u8 jin)
{
	if(jin==1)
	{
		Motion_Front();  //ǰ��30 
		delay_ms(1000);
		Motion_After();  //����30
			
		Motion_Spin(jin);  //��ת90��
			
		delay_ms(350); 
		Motor_Motion(1000,-1000); 
		delay_ms(50); 
		Motor_Motion(0,0); 

		motx=1;
	}
	else
	{
		Motion_Front();  //ǰ��30 
		delay_ms(1000);
		Motion_After();  //����30
			
		Motion_Spin(jin);  //��ת90��
			
		delay_ms(350); 
		Motor_Motion(1000,-1000); 
		delay_ms(50); 
		Motor_Motion(0,0); 

		motx=1;
	}
}

