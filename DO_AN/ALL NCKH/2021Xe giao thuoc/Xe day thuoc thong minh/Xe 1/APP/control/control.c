#include <control.h>
#include <motor.h>


void Control(int data)
{
	static s16 x=0;
	static int y=0;
	
	switch(data)
	{
		case(3):  x+=500;  y=0;  break;  //Ç°
		case(4):  y+=500;        break;  //×ó
		case(5):  x-=500;  y=0;  break;  //ºó
		case(6):  y-=500;        break;  //ÓÒ
		case(7):  x=y=0;         break;  //Í£
	}
	Motor_Limit(&x);
	Motor_Motion(x,x+y);
}

