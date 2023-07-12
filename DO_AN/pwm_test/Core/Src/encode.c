/*
 * encode.c
 *
 *  Created on: Apr 15, 2022
 *      Author: pai3_
 *      定时器8 通道1 2   编码器模式
 */

#include "encode.h"

int Direction,CaptureNumber;
int speed_sample;

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	//10ms采样周期  50ms 打印显示周期0.5s
//			 static unsigned char TIM_State = 0;
//			if (htim->Instance == TIM7)
//			{
//				TIM_State++;
//				Direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim8);   //读取电机转动方向
//			    CaptureNumber =	(short)__HAL_TIM_GET_COUNTER(&htim8);//读取编码器数脉冲
//			    speed_sample = (int)(CaptureNumber/4.2);     //单圈脉冲�? 420
//			    __HAL_TIM_GET_COUNTER(&htim8) = 0;	 //计数脉冲重新�?0
//
//				//printf("TIM_state is %d \r\n", TIM_State);
//
//				if(TIM_State >= 50)  // 50*10ms = 500ms   T = 0.5s
//						{
//							TIM_State = 0;
//					 printf("  Direction is %d  ---  speed is  %d   (r/sec) \r\n ",Direction,speed_sample);
//						}
//			}
//}

void PRINTF_FUN()
{
	printf("this is a printfing in another .c file\r\n");
}


 /**
 * @brief PID 参数初始化
 * @note 无
 * @retval 无
 */
 void PID_param_init(_Pid_ pid)
 {
 /* 初始化参数 */
 printf("PID_init begin \n");
 pid->target_val=0.0;
 pid->actual_val=0.0;

 pid->err = 0.0;
 pid->err_last = 0.0;
 pid->err_next = 0.0;

  // pid.Kp = 0.21;
  // pid.Ki = 0.070;
  // pid.Kd = 0.32;
  pid->Kp = 0.21;
  pid->Ki = 0.80;
  pid->Kd = 0.01;
  printf("PID_init end \n");

  }


 float PID_Increment(_Pid_ pid ,float sample_val)
  {
  /* 计算目标值与实际值的误差 */
  pid->err=pid->target_val-sample_val;
  /*PID 算法实现 */
  float increment_val = pid->Kp*(pid->err - pid->err_next) +\
		  	  	  	  	pid->Ki*pid->err +\
						pid->Kd*(pid->err - 2 * pid->err_next\
						+ pid->err_last);

  /* 传递误差 */
   pid->err_last = pid->err_next;
   pid->err_next = pid->err;

   /* 累加 */
    pid->actual_val += increment_val;
   /* 返回当前实际值 */
   return pid->actual_val;
   }
