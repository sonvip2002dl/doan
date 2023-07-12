#include <pid.h>
#include "encoder.h"
#include "motor.h"
#include "systick.h"
#include "usart.h"
#include "motion.h"

char Qianjin2_240()
{
	static s32 encs=0;
	s32  enc=34200;
	
	s16 pwm=5000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-35;

	mot=0;
	
	pwmx=tkp*kxie;
	
	
	if(encs>33000)
	{
		pwm=2000;
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
		Motor_Motion(-2000,-2000); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		return 1;
	}
	return 0;
}


char Qianjin2_180()
{
	static s32 encs=0;
	s32  enc=31000;
	
	s16 pwm=5000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-35;

	mot=0;
	
	if(encs>29000)
	{
		pwm=2000;
	}
	
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



char Houtui2_30()
{
	static s32 encs=0;
	s32  enc=-6000;
	
	
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


char Qianjin2_40_2()
{
	static s32 encsx=0;
	s32  enc=4600;
	
	
	encsx+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	if(encsx<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encsx=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

char Qianjin2_40_3()
{
	static s32 encsx=0;
	s32  enc=4400;
	
	
	encsx+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	if(encsx<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encsx=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

char Qianjin2_40_4()
{
	static s32 encsx=0;
	s32  enc=4450;
	
	
	encsx+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	if(encsx<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encsx=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Qianjin2_40()
{
	static s32 encsx=0;
	s32  enc=4500;
	
	
	encsx+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	if(encsx<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encsx=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Qianjin2_40_12()
{
	static s32 encsx=0;
	s32  enc=4300;
	
	
	encsx+=Encoder_Read(3)+Encoder_Read(4);
	//printf("hh %d\r\n",encs);
	Motor_Motion(3000,3000);
	if(encsx<enc)
	{
		Motor_Motion(3000,3000);
	}
	else
	{
		Motor_Motion(-1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encsx=0;
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Fanhiu2_60()
{
	static s32 encs=0;
	s32  enc=7550;
	
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
		//delay_ms(1000);
		return 1;
	}
	return 0;
}





int Incremental_PI (int Encoder,int Target)
{ 	
	float Kp=-8,Ki=-10;	
	static int Bias,Pwm=0,Last_bias;
	
	Bias=Encoder-Target;                //计算偏差
	Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	Last_bias=Bias;	                   //保存上一次偏差 
	
	return Pwm;                         //增量输出
}


char Jiao90_4()
{
	static s32 encs=0;
	s32  enc=1600;

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
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

char Jiao90_2()
{
	static s32 encs=0;
	s32  enc=1550;

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
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Jiao90_5()
{
	static s32 encs=0;
	s32  enc=1600;

	encs+=-Encoder_Read(3)+Encoder_Read(4);
	//printf("agagagga %d\r\n",encs);
	///1Motor_Motion(-3000,3000);
		
	if(encs<=enc)
	{
		Motor_Motion(-2000,2000);
	}
	else
	{
		Motor_Motion(1500,-1500); 
		delay_ms(70); 
		Motor_Motion(0,0);
		encs=0;
		delay_ms(100);
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

// 逆时针90°
char Jiao90()
{
	static s32 encs=0;
	s32  enc=1550;

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
		//delay_ms(1000);
		return 1;
	}
	return 0;
}

char Jiao90_10()
{
	static s32 encs=0;
	s32  enc=1500;

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
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Jiao90_3()
{
	static s32 encs=0;
	s32  enc=1300;

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
		delay_ms(1000);
		return 1;
	}
	return 0;
}

// 顺时针90°
char Jiao_90()
{
	static s32 encs=0;
	s32  enc=-1500;

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
		//delay_ms(100);
		return 1;
	}
	return 0;
}

char Jiao_90_11()
{
	static s32 encs=0;
	s32  enc=-1470;

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
		//delay_ms(100);
		return 1;
	}
	return 0;
}




// 逆时针90°
char Jiao180()
{
	static s32 encs=0;
	s32  enc=3150;

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
		//delay_ms(1000);
		return 1;
	}
	return 0;
}


char Qianhou40()
{
	static s32 encs=0;
	u32  enc=5700;
	
	
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
	s32  enc=-5700;
	
	
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


// 第一段直线
char Fanhiu75()
{
	static s32 encs=0;
	s32  enc=9000;
	
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

//中端第一段直线
char Qianjin150()
{
	static s32 encs=0;
	s32  enc=21000;
	
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


char Qianjin165()
{
	static s32 encs=0;
	s32  enc=23500;
	
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


char Qianjin15_6()
{
	static s32 encs=0;
	u32  enc=4700;
	
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
		delay_ms(100);
		return 1;
	}
	return 0;
}

//中端第二段
char Qianjin15()
{
	static s32 encs=0;
	u32  enc=4000;
	
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


char Qianjin15_13()
{
	static s32 encs=0;
	u32  enc=4500;
	
	s16 pwm=2000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
//	pwmx=tkp*kxie;
//	pwm1=pwm+pwmx;
//	pwm2=pwm-pwmx;
//	
//	Motor_Limit(&pwm1);
//	Motor_Limit(&pwm2);
//	
	encs+=Encoder_Read(3)+Encoder_Read(4);
//	//printf("hh %d\r\n",encs);
	
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

char Qianjin2_15_3()
{
	static s32 encs=0;
	u32  enc=4300;
	
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
	u32  enc=14000+6000;
	
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
	u32  enc=6400;
	
	
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
	s32  enc=6300;
	
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
	u32  enc=13000;
	
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



//远端直线第四段
char Qianjin15_3()
{
	static s32 encs=0;
	u32  enc=4500;
	
	
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
	u32  enc=4900;
	
	
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


char Qianjin15_99()
{
	static s32 encs=0;
	u32  enc=5100;
	
	
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
	u32  enc=4800;
	
	
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
	u32  enc=35000;
	
	s16 pwm=3000;
	s16 pwmx;
	s16 pwm1,pwm2;
	s16 tkp=-20;

	mot=0;
	
	pwmx=tkp*kxie;
	
	if(encs>37500)
	{
		pwm=0;
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