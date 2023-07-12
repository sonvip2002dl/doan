#include <control.h>
#include <motor.h>


void Control(int data)
{
	static s16 x=0;
	static int y=0;
	
	switch(data)
	{
		case(3):  x+=500;  y=0;  break;  //ǰ
		case(4):  y+=500;        break;  //��
		case(5):  x-=500;  y=0;  break;  //��
		case(6):  y-=500;        break;  //��
		case(7):  x=y=0;         break;  //ͣ
	}
	Motor_Limit(&x);
	Motor_Motion(x,x+y);
}

