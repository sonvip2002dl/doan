/*
 * encode.h
 *
 *  Created on: Apr 15, 2022
 *      Author: pai3_
 */

#ifndef INC_ENCODE_H_
#define INC_ENCODE_H_

#include "tim.h"
#include "usart.h"
#include "stdio.h"
//void Get_speed();
void PRINTF_FUN();



typedef struct
 {
 float target_val; //目标值
 float actual_val; //实际值

 float err; //定义当前偏差值
 float err_next; //定义下一个偏差值
 float err_last; //定义最后一个偏差值

 volatile float Kp, Ki, Kd; //定义比例、积分、微分系数
 }* _Pid_;


 void PID_param_init(_Pid_ pid);
 float PID_Increment(_Pid_ pid ,float sample_val);

 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_ENCODE_H_ */
