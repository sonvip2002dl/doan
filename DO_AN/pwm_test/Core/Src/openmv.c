/*
 * openmv.c
 *
 *  Created on: May 3, 2022
 *      Author: pai3_
 */


#include "openmv.h"
#include "motor.h"

int openmv[6];            //stm32接收数据数组
int OpenMV_RX;          /*OPENMV OpenMV_RX 轴反馈坐标*/
int OpenMV_RY;          /*OPENMV OpenMV_RX 轴反馈坐标*/
char OpenMV_L;
int i=0;

void Openmv_Receive_Data(unsigned char data)    //接收Openmv传过来的数据
{
	static unsigned char state = 0;
	if(state==0&&data==0xb3)
	{
		state=1;
		openmv[0]=data;
	}
	else if(state==1&&data==0xb3)
	{
		state=2;
		openmv[1]=data;
	}
	else if(state==2)
	{
		state=3;
		openmv[2]=data;
	}
	else if(state==3)		 //data = bytearray([0xb3,0xb3,OpenMV_RX,OpenMV_RY,length,0x5b])
	{
		state = 4;
		openmv[3]=data;
	}
	else if(state==4)
	{
		state = 5;
		openmv[4]=data;
	}
		else if(state==5)
	{
			if(data == 0x5B)
			        {
			            state = 0;
			            openmv[5]=data;
						data=0;
			        }
			        else if(data != 0x5B)
			        {
			            state = 0;
			            for(i=0;i<8;i++)
			            {
			                openmv[i]=0x00;
			            }
			        }
	}
	else
		{
			state = 0;
            data=0;
			for(i=0;i<8;i++)
            {
                openmv[i]=0x00;
            }
		}

}

void Openmv_Data(void)
{
    OpenMV_RX=openmv[2];
    OpenMV_RY=openmv[3];
	OpenMV_L=openmv[4];
}

		int x_0 = 0;
		int x_1 = 120/2;
		int x_2 = 200/2;
		int x_3 = 320/2;

		int y_0 = 0;
		int y_1 = 80;
		int y_2 = 160;
		int y_3 = 240;
		int flag = 0;
void Openmv_Flag()
{
			if (OpenMV_RX>=x_0 && OpenMV_RX<=x_1 && OpenMV_RY>=y_0 && OpenMV_RY<=y_1 ) flag = 1;
            if (OpenMV_RX>=x_1 && OpenMV_RX<=x_2 && OpenMV_RY>=y_0 && OpenMV_RY<=y_1 ) flag = 2;
            if (OpenMV_RX>=x_2 && OpenMV_RX<=x_3 && OpenMV_RY>=y_0 && OpenMV_RY<=y_1 ) flag = 3;
            if (OpenMV_RX>=x_0 && OpenMV_RX<=x_1 && OpenMV_RY>=y_1 && OpenMV_RY<=y_2 ) flag = 4;
            if (OpenMV_RX>=x_2 && OpenMV_RX<=x_3 && OpenMV_RY>=y_1 && OpenMV_RY<=y_2 ) flag = 6;
            if (OpenMV_RX>=x_0 && OpenMV_RX<=x_1 && OpenMV_RY>=y_2 && OpenMV_RY<=y_3 ) flag = 7;
            if (OpenMV_RX>=x_1 && OpenMV_RX<=x_2 && OpenMV_RY>=y_2 && OpenMV_RY<=y_3 ) flag = 8;
            if (OpenMV_RX>=x_2 && OpenMV_RX<=x_3 && OpenMV_RY>=y_2 && OpenMV_RY<=y_3 ) flag = 9;
            else 									   								   flag = 0;
}


int velocity = 1600;
void Car_mode_control(void)
{

		//车位状态判断
		if(x_0 < OpenMV_RX && OpenMV_RX < x_1 && OpenMV_L>10)
		{
			//Right_Sidesway(velocity);//finding_R = 4
			R_Rotation(velocity);
		}
		else if(OpenMV_RX < x_3  && OpenMV_RX >x_2 && OpenMV_L>10)
		{

			//Left_Sidesway(velocity);//finding_L = 3
			L_Rotation(velocity);
		}
		else if(OpenMV_RX>x_1 && OpenMV_RX<x_2 && OpenMV_L>10)
		{
			Forward_Car(velocity);//run=2
		}
		else if(OpenMV_L<=10 && OpenMV_L>=5)
		{
			Wheel_Pin_Init();//stop = 1
		}
//		else if(0 < OpenMV_L <=5)
//		{
//				Back_Car(velocity);//stop = 1
//		}
		else if(OpenMV_RX == 0 || OpenMV_L == 0 || OpenMV_RY == 0)
		{
			Wheel_Pin_Init();//stop = 1
		}
}
