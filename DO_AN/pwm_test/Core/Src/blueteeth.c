/*
 * blueteeth.c
 *
 *  Created on: Apr 17, 2022
 *      Author: pai3_
 *
 *     串口3  蓝牙 中断接受  注意波特率  9600
 */
#include "blueteeth.h"
#include "openmv.h"
#include "usart.h"
#include "motor.h"
unsigned char RX_dat=0;//接收变量
#define speed 2400


		void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  // 蓝牙控制小车运动
		{
		  if(huart->Instance == USART3)
		   {
			  switch(RX_dat)
			  {
			  case 'A' :		Forward_Car(speed);BEEP_ON();
				  break;
			  case 'B' :   		Left_Sidesway(speed);BEEP_ON();
				  break;
			  case 'C' :   		L_Rotation(speed);BEEP_ON();
				  break;
			  case 'D' :		Right_Sidesway(speed);BEEP_ON();
				  break;
			  case 'E' :   		Back_Car(speed);BEEP_ON();
				  break;

			  case 'F' :		ZuoQian(speed);BEEP_ON();
				  break;
			  case 'G' :		YouQian(speed);BEEP_ON();
				  break;
			  case 'H' :		ZuoHou(speed);BEEP_ON();
				  break;
			  case 'I' :		YouHou(speed);BEEP_ON();
				  break;

		//	  case 'J' :		model_change = !model_change;
		//		  break;

			  case 'S' :   		Wheel_Pin_Init();
				  break;
			  }
			  HAL_UART_Receive_IT(&huart3,&RX_dat,1);//启动接收函数
		  }
		}






/**************************************************************************/

//	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//			{
//			  if(huart->Instance == USART3)
//				   {
//				  Openmv_Receive_Data(RX_dat);
//				  Openmv_Data();
//				  //printf("%x",RX_dat);
//				   }
//				  HAL_UART_Receive_IT(&huart3,&RX_dat,1);//启动接收函数
//			}
/**************************************************************************/
//UART.c
/**
  * @brief 串口中断回调函数
  * @param 调用回调函数的串口
  * @note  串口每次收到数据以后都会关闭中断，如需重复使用，必须再次开启
  * @retval None
  */




//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance == USART3)
//			   {
//				  switch(RX_dat)
//				  {
//				  case 'A' :		Back_Car(speed);
//					  break;
//				  case 'B' :   		Back_Car(speed);
//					  break;
//				  case 'C' :   		Back_Car(speed);
//					  break;
//				  case 'D' :		L_Rotation(speed);
//					  break;
//				  case 'E' :   		Wheel_Pin_Init();
//					  break;
//				  case 'F' :		R_Rotation(speed);
//					  break;
//				  case 'G' :		Forward_Car(speed);
//					  break;
//				  case 'H' :		Forward_Car(speed);
//					  break;
//				  case 'I' :		Forward_Car(speed);
//					  break;
//				  case 'S' :   		Wheel_Pin_Init();
//					  break;
//				  }
//				  HAL_UART_Receive_IT(&huart3,&RX_dat,1);//启动接收函数
//			  }
//}

