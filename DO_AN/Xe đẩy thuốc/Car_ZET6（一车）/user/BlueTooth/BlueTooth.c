/*��Ƶ�̳����� https://www.bilibili.com/video/BV1UL411V7XK?p=2&share_source=copy_web*/

#include "BlueTooth.h"
#include "bsp_GraySensor.h"
#include "bsp_led.h"
#include "openmv.h"
#include "bsp_debug.h"
#include "usart.h"


u8 BlueToothSendBuf[5] = {0x52, 0x21, 0x00, 0x00, 0xf2};

void BlueToothTransmitData()
{
   	u8 i;
	
	  BlueToothSendBuf[2] = TargetRoom;
	  BlueToothSendBuf[3] = Load_flag;
	  //BlueToothSendBuf[4] = TASK;
	
		for(i = 0; i <= 5; i++)   //�����ַ�����λ������ͨ��HEX���������Ƿ���ȷ
		{
			Usart_SendByte(BlueToothSendBuf[i]);      
		}
	
//  	for(i = 0; i <= 5; i++)   //�����ַ���
//		{
//			sprintf((char *)BlueToothSendBuf, "2%d%d%d8", TASK, TargetNum, Load_flag);
//				HAL_UART_Transmit(&huart1, BlueToothSendBuf, sizeof(BlueToothSendBuf), 1000);
//		}
	 
	      
}


