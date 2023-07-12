#include <pid.h>
#include "encoder.h"
#include "motor.h"
#include "systick.h"
#include "usart.h"
#include "motion.h"


int Incremental_PI (int Encoder,int Target)
{ 	
	float Kp=-8,Ki=-10;	
	static int Bias,Pwm=0,Last_bias;
	
	Bias=Encoder-Target;                //计算偏差
	Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	Last_bias=Bias;	                   //保存上一次偏差 
	
	return Pwm;                         //增量输出
}

char Jiao90_2()
{
	static s32 encs=0;
	s32  enc=2150;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	///1Motor_Motion(-3000,3000);
		
	if(encs<=enc)
	{
		Motor_Motion(-3000,3000);
	}
	else
	{
		Motor_Motion(1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


// 逆时针90°
char Jiao90()
{
	static s32 encs=0;
	s32  enc=1800;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	///1Motor_Motion(-3000,3000);
		
	if(encs<=enc)
	{
		Motor_Motion(-3000,3000);
	}
	else
	{
		Motor_Motion(1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Jiao90x(s32  enc)
{
	static s32 encs=0;
	

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	///1Motor_Motion(-3000,3000);
		
	if(encs<=enc)
	{
		Motor_Motion(-3000,3000);
	}
	else
	{
		Motor_Motion(1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}



char Jiao90_3()
{
	static s32 encs=0;
	s32  enc=1900;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	///1Motor_Motion(-3000,3000);
		
	if(encs<=enc)
	{
		Motor_Motion(-3000,3000);
	}
	else
	{
		Motor_Motion(1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Jiao90_23()
{
	static s32 encs=0;
	s32  enc=2050;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	///1Motor_Motion(-3000,3000);
		
	if(encs<=enc)
	{
		Motor_Motion(-3000,3000);
	}
	else
	{
		Motor_Motion(1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}

char Jiao90_18()
{
	static s32 encs=0;
	s32  enc=2000;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	///1Motor_Motion(-3000,3000);
		
	if(encs<=enc)
	{
		Motor_Motion(-3000,3000);
	}
	else
	{
		Motor_Motion(1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}

char Jiao_90_2()
{
	static s32 encs=0;
	s32  enc=-1750;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	//Motor_Motion(-3000,3000);
		
	if(encs>enc)
	{
		Motor_Motion(3000,-3000);
	}
	else
	{
		Motor_Motion(-1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}

// 顺时针90°
char Jiao_90()
{
	static s32 encs=0;
	s32  enc=-1900;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	//Motor_Motion(-3000,3000);
		
	if(encs>enc)
	{
		Motor_Motion(3000,-3000);
	}
	else
	{
		Motor_Motion(-1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Jiao_90_31()
{
	static s32 encs=0;
	s32  enc=-1800;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	//Motor_Motion(-3000,3000);
		
	if(encs>enc)
	{
		Motor_Motion(3000,-3000);
	}
	else
	{
		Motor_Motion(-1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Jiao_90_19()
{
	static s32 encs=0;
	s32  enc=-1800;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	//Motor_Motion(-3000,3000);
		
	if(encs>enc)
	{
		Motor_Motion(3000,-3000);
	}
	else
	{
		Motor_Motion(-1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


// 逆时针90°
char Jiao180()
{
	static s32 encs=0;
	s32  enc=3900;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	///1Motor_Motion(-3000,3000);
		
	if(encs<=enc)
	{
		Motor_Motion(-3000,3000);
	}
	else
	{
		Motor_Motion(1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Qianhou40()
{
	static s32 encs=0;
	s32  enc=5700;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}


char Qianhou40x(s32 enc)
{
	static s32 encs=0;
	//s32  enc=5700;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}


char Qianhou40_30()
{
	static s32 encs=0;
	s32  enc=4700;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}


char Qianhou40_27()
{
	static s32 encs=0;
	s32  enc=5150;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}


char Qianhou40_20()
{
	static s32 encs=0;
	s32  enc=4900;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}

char Qianhou40_15()
{
	static s32 encs=0;
	s32  enc=5500;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}


char Qianhou40_11()
{
	static s32 encs=0;
	s32  enc=5000;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1800,-1800); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}


char Qianhou40_10()
{
	static s32 encs=0;
	s32  enc=5400;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}


char Qianhou40_4()
{
	static s32 encs=0;
	s32  enc=5900;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(1000);
		return 1;
	}
	return 0;
}


char Qianhou40_2()
{
	static s32 encs=0;
	s32  enc=5400;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		return 1;
	}
	return 0;
}

char Qianhou40_3()
{
	static s32 encs=0;
	s32  enc=5500;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(1000);
		return 1;
	}
	return 0;
}

char Houtui40()
{
	static s32 encs=0;
	s32  enc=-5500;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(-3000,-3000);
	
	if(encs>enc)
	{
		Motor_Motion(-3000,-3000);
	}
	else
	{
		Motor_Motion(1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(200);
		return 1;
	}
	return 0;
}


char Houtui40_29()
{
	static s32 encs=0;
	s32  enc=-5200;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(-3000,-3000);
	
	if(encs>enc)
	{
		Motor_Motion(-3000,-3000);
	}
	else
	{
		Motor_Motion(1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(200);
		return 1;
	}
	return 0;
}


char Houtui40_26()
{
	static s32 encs=0;
	s32  enc=-5600;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(-3000,-3000);
	
	if(encs>enc)
	{
		Motor_Motion(-3000,-3000);
	}
	else
	{
		Motor_Motion(1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(200);
		return 1;
	}
	return 0;
}


char Houtui40_22()
{
	static s32 encs=0;
	s32  enc=-5300;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(-3000,-3000);
	
	if(encs>enc)
	{
		Motor_Motion(-3000,-3000);
	}
	else
	{
		Motor_Motion(1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(200);
		return 1;
	}
	return 0;
}

char Houtui40_13()
{
	static s32 encs=0;
	s32  enc=-5500;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(-3000,-3000);
	
	if(encs>enc)
	{
		Motor_Motion(-3000,-3000);
	}
	else
	{
		Motor_Motion(1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(200);
		return 1;
	}
	return 0;
}


char HoutuiX(s32 enc)
{
	static s32 encs=0;
	//s32  enc=-5500;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(-3000,-3000);
	
	if(encs>enc)
	{
		Motor_Motion(-2700,-3000);
	}
	else
	{
		Motor_Motion(1500,1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(200);
		return 1;
	}
	return 0;
}


// 第一段直线
char Fanhiu75()
{
	static s32 encs=0;
	s32  enc=8500;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;
	
	
	if(encs>7000)
	{
		pwm1=pwm2=0;
	}

	mot=0;
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1900,-2500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}



char Fanhiu75_2()
{
	static s32 encs=0;
	s32  enc=7500;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;
	
	
	if(encs>8000)
	{
		pwm1=pwm2=0;
	}

	mot=0;
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}

// 第一段直线
char Qianjin75()
{
	static s32 encs=0;
	s32  enc=13000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	//printf("aa");
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
		//printf("bb");
	}
	else
	{
		//printf("cc");
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Qianjin75_28()
{
	static s32 encs=0;
	s32  enc=12000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	//printf("aa");
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
		//printf("bb");
	}
	else
	{
		//printf("cc");
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Qianjin75_25()
{
	static s32 encs=0;
	s32  enc=14000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	//printf("aa");
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
		//printf("bb");
	}
	else
	{
		//printf("cc");
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Qianjin75_14()
{
	static s32 encs=0;
	s32  enc=12000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	//printf("aa");
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
		//printf("bb");
	}
	else
	{
		//printf("cc");
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}

char Qianjin75_12()
{
	static s32 encs=0;
	s32  enc=12000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	//printf("aa");
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
		//printf("bb");
	}
	else
	{
		//printf("cc");
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Qianjin75_2()
{
	static s32 encs=0;
	s32  enc=14000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	//printf("aa");
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
		//printf("bb");
	}
	else
	{
		//printf("cc");
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


//中端第一段直线
char Qianjin150()
{
	static s32 encs=0;
	s32  enc=21700;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		//while(1);
		return 1;
	}
	return 0;
}


char Qianjin165()
{
	static s32 encs=0;
	s32  enc=21700;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	
	if(encs>19700)
	{
		pwmx=0;
	}
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1800,-1800); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Qianjin165x(s32 enc)
{
	static s32 encs=0;
	//s32  enc=21700;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	
	if(encs>19700)
	{
		pwmx=0;
	}
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1800,-1800); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Qianjin165_21()
{
	static s32 encs=0;
	s32  enc=23000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	
	if(encs>21000)
	{
		pwmx=0;
	}
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1800,-1800); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

char Qianjin165_2()
{
	static s32 encs=0;
	s32  enc=23000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

//中端第二段
char Qianjin15()
{
	static s32 encs=0;
	s32  enc=4500;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

char Qianjin15_16()
{
	static s32 encs=0;
	s32  enc=4800;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

//远端第二段
char Qianjin90()
{
	static s32 encs=0;
	s32  enc=14000+5000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

// 远端第三段，无循迹
char Qianjin15_2()
{
	static s32 encs=0;
	s32  enc=6400;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

//远端直线第三段
char Qianjin60()
{
	static s32 encs=0;
	s32  enc=7700;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1700,-1700); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


//远端到另一边
char Qianjin120()
{
	static s32 encs=0;
	s32  enc=17000;
	
	s16 pwm=5000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	
	if(encs>enc-2000)
	{
		pwm=3000;
		pwmx=0;
	}
	
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1900,-1900); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}



//远端直线第四段
char Qianjin15_3()
{
	static s32 encs=0;
	s32  enc=5100;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Qianjin15_24()
{
	static s32 encs=0;
	s32  enc=5200;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

char Qianjin15_6()
{
	static s32 encs=0;
	s32  enc=5300;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

char Qianjin15_4()
{
	static s32 encs=0;
	s32  enc=4800;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Qianjin15_5()
{
	static s32 encs=0;
	s32  enc=5300;
	
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	if(encs<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


//远端直线返回
char Qianjin255()
{
	static s32 encs=0;
	s32  enc=37500;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	
	if(encs>35000)
	{
		pwmx=0;
	}
	
	pwm1=pwm+pwmx;
	pwm2=pwm-pwmx;
	
	Motor_Limit(&pwm1);
	Motor_Limit(&pwm2);
	
	encs+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	
	if(encs<enc)
	{
		Motor_Motion(pwm1,pwm2);
	}
	else
	{
		Motor_Motion(-1700,-1700); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

