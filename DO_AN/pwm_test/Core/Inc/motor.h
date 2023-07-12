/*
 * motor.h
 *
 *  Created on: Apr 7, 2022
 *      Author: pai3_
 *
 *
 *
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_
/*****************************************/



#include "main.h"
#include "tim.h"

#define ARR_Value 6400   //自动重装载
#define DUTY_50P (ARR_Value/2)
#define DUTY_(X) 		( ARR_Value * ( (X)/100 ) )


void Mecanum_wheel_Init(void);  //m麦克纳姆轮初始化
void Wheel_Pin_Init(void);
void Mecanum_wheel_Stop(void);

void Forward_Car(int pwmVal);		//前进
void Back_Car(int pwmVal);			//后退

void SingleMotor_Ctrol(int motor , int pwm_Forward , int pwm_Back); //单机控制函数
void Car__motion(int pwm_A , int pwm_B,int pwm_C,int pwm_D);


void R_Rotation(int speed);
void L_Rotation(int speed);
void Left_Sidesway(int speed);
void Right_Sidesway(int speed);
void ZuoQian(int speed);
void YouQian(int speed);
void ZuoHou(int speed);
void YouHou(int speed);


void grass_car(int speed1,int speed2);
void arm_move(int speed);














#endif /* INC_MOTOR_H_ */
