/*
 * motor.c
 *
 *  Created on: Apr 7, 2022
 *      Author: pai3_
 *
 * 					pwm通道channel3/4
 *      \\ D轮 D14 D15  T4   Forward_Left      // A轮 E13 E14  T1  Forward_Rihgt
 *
 *
 *      // C轮 B0 B1 T3  Rear_Left             \\ B轮  A2 A3    T2		Rear_Rihgt
 */


#include "motor.h"

void Mecanum_wheel_Init(void)
{
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	    Wheel_Pin_Init();   //上电后占空比置0

}

void Wheel_Pin_Init(void)
{
		  TIM1->CCR4 = 0;
		  TIM2->CCR4 = 0;
		  TIM3->CCR4 = 0;
		  TIM4->CCR4 = 0;

 		  TIM1->CCR3 = 0;
 		  TIM2->CCR3 = 0;
 		  TIM3->CCR3 = 0;
 		  TIM4->CCR3 = 0;

}

void Mecanum_wheel_Stop(void)
{
	Wheel_Pin_Init();
	HAL_TIM_PWM_Stop_IT(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_IT(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_IT(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop_IT(&htim1,TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop_IT(&htim2,TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop_IT(&htim3,TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop_IT(&htim4,TIM_CHANNEL_4);

}



void Forward_Car(int pwmVal)
{
	//Wheel_Pin_Init();
		 		  TIM1->CCR3 = pwmVal;
		 		  TIM2->CCR3 = pwmVal;
		 		  TIM3->CCR3 = pwmVal;
		 		  TIM4->CCR3 = pwmVal;

	 		 	  TIM1->CCR4 = 0;
	 		 	  TIM2->CCR4 = 0;
	 		 	  TIM3->CCR4 = 0;
	 		 	  TIM4->CCR4 = 0;

}

void Back_Car(int pwmVal)
{
	//Wheel_Pin_Init();
				  TIM1->CCR3 = 0;
				  TIM2->CCR3 = 0;
				  TIM3->CCR3 = 0;
				  TIM4->CCR3 = 0;

	 		 	  TIM1->CCR4 = pwmVal;
	 		 	  TIM2->CCR4 = pwmVal;
	 		 	  TIM3->CCR4 = pwmVal;
	 		 	  TIM4->CCR4 = pwmVal;

}

void SingleMotor_Ctrol(int motor , int pwm_Forward , int pwm_Back)
{
	//Wheel_Pin_Init();  //此初始化会影响其他轮子，所以注释掉
	switch(motor)
	{
	case 1 :     	 TIM1->CCR4 = pwm_Back;TIM1->CCR3 = pwm_Forward;
			break;
	case 2 :		 TIM2->CCR4 = pwm_Back;TIM2->CCR3 = pwm_Forward;
			break;
	case 3  :		 TIM3->CCR4 = pwm_Back;TIM3->CCR3 = pwm_Forward;
			break;
	case 4 :		 TIM4->CCR4 = pwm_Back;TIM4->CCR3 = pwm_Forward;
			break;
	}
}

void Car__motion(int pwm_A , int pwm_B,int pwm_C,int pwm_D)
{
	Wheel_Pin_Init();
		  TIM1->CCR3 = pwm_A;
		  TIM2->CCR3 = pwm_B;
		  TIM3->CCR3 = pwm_C;
		  TIM4->CCR3 = pwm_D;
}



/*********************funtion   combation_motion  *********************/
void R_Rotation(int speed)
{
	SingleMotor_Ctrol(1,0000,speed);
	SingleMotor_Ctrol(2,0000,speed);
	SingleMotor_Ctrol(3,speed,0000);
	SingleMotor_Ctrol(4,speed,0000);
}
void L_Rotation(int speed)
{
	SingleMotor_Ctrol(1,speed,0000);
	SingleMotor_Ctrol(2,speed,0000);
	SingleMotor_Ctrol(3,0000,speed);
	SingleMotor_Ctrol(4,0000,speed);
}

void Left_Sidesway(int speed)
{
	SingleMotor_Ctrol(1,speed,000);
	SingleMotor_Ctrol(2,000,speed);
	SingleMotor_Ctrol(3,speed,000);
	SingleMotor_Ctrol(4,000,speed);
}

void Right_Sidesway(int speed)
{
		SingleMotor_Ctrol(1,000,speed);
		SingleMotor_Ctrol(2,speed,000);
		SingleMotor_Ctrol(3,000,speed);
		SingleMotor_Ctrol(4,speed,000);
}

void ZuoQian(int speed)
{
			SingleMotor_Ctrol(1,speed,000);
			SingleMotor_Ctrol(2,000,000);
			SingleMotor_Ctrol(3,speed,000);
			SingleMotor_Ctrol(4,000,000);
}

void YouQian(int speed)
{
			SingleMotor_Ctrol(1,000,000);
			SingleMotor_Ctrol(2,speed,000);
			SingleMotor_Ctrol(3,000,000);
			SingleMotor_Ctrol(4,speed,000);
}

void ZuoHou(int speed)
{
			SingleMotor_Ctrol(1,000,000);
			SingleMotor_Ctrol(2,000,speed);
			SingleMotor_Ctrol(3,000,000);
			SingleMotor_Ctrol(4,000,speed);
}
void YouHou(int speed)
{
			SingleMotor_Ctrol(1,000,speed);
			SingleMotor_Ctrol(2,000,000);
			SingleMotor_Ctrol(3,000,speed);
			SingleMotor_Ctrol(4,000,000);
}



void grass_car(int speed1,int speed2)
{
		SingleMotor_Ctrol(1,speed1,0000);
		SingleMotor_Ctrol(2,speed2,0000);
}

void arm_move(int speed)
{
	SingleMotor_Ctrol(4,000,speed);
}
