#include <main.h>

#define delayLED		40

//unsigned char  LED7segAnotdp[] =    {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
//unsigned char  LED7segAnot[] =      {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

unsigned char  LED7segAnot[] =      {0x09,0xaf,0x98,0x8c,0x2e,0x4c,0x48,0x8f,0x08,0x0c};

void LED7seg_Display(unsigned char pos, unsigned char number);

void delay_ms(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<123;j++);
	}
}

void main()
{
	int i,j;
	//Khoi tao ngat ngoai
	IT0 = 0;
	EX0 = 1;
	EA = 1;
	
	while(1)
	{
		Green1=0;					//Bat den xanh 1
		Red1=1;						//Tat den do 1
		Green2=1;					//Tat den xanh 2
		Red2=0;						//Bat den do 2
		Yellow1=Yellow2=1;	//Tat den vang 1 va 2
		for(i=30;i>=0;i--)
		{
			if(i<=4)
			{
				Green1=1;		//Tat den xanh 1
				Yellow1=0;		//Bat den vang 1
				
				for(j=0;j<delayLED;j++)
				{
					LED7seg_Display(2,i/10);
					LED7seg_Display(3,i%10);
					LED7segPIN1 = 1;
					LED7segPIN2 = 1;
				}
					LED7segPIN3 = 1;
					LED7segPIN4 = 1;
					delay_ms(500);
			}
			else
			{
				for(j=0;j<delayLED;j++)
				{
					LED7seg_Display(2,i/10);
					LED7seg_Display(3,i%10);
					LED7seg_Display(0,(i-5)/10);
					LED7seg_Display(1,(i-5)%10);
				}
			}			
		}
			
		Green1=1;					//Tat den xanh 1
		Red1=0;						//Bat den do 1
		Green2=0;					//Bat den xanh 2
		Red2=1;						//Tat den do 2
		Yellow1=Yellow2=1;	//Tat den vang 1 va 2
		for(i=30;i>=0;i--)
		{
			if(i<=4)
			{
				Green2=1;		//Tat den xanh 2
				Yellow2=0;		//Bat den vang 2
				
				for(j=0;j<delayLED;j++)
				{
					LED7seg_Display(0,i/10);
					LED7seg_Display(1,i%10);
					LED7segPIN3 = 1;
					LED7segPIN4 = 1;
				}
					LED7segPIN1 = 1;
					LED7segPIN2 = 1;
					delay_ms(500);
			}
			else
			{
				for(j=0;j<delayLED;j++)
				{
					LED7seg_Display(0,i/10);
					LED7seg_Display(1,i%10);
					LED7seg_Display(2,(i-5)/10);
					LED7seg_Display(3,(i-5)%10);
				}
			}			
		}
	}	
}
void INT0_ISR() interrupt 0
{
	LED7segPIN1 = 1;					
	LED7segPIN2 = 1;
	LED7segPIN3 = 1;
	LED7segPIN4 = 1;
	Green1=Green2=Red1=Red2=1;
	while(1)
	{
		Yellow1=Yellow2=1;
		delay_ms(1000);
		Yellow1=Yellow2=0;
		delay_ms(1000);
	}
}

void LED7seg_Display(unsigned char pos, unsigned char number)
{
    switch(pos)
    {
        case 0: LED7seg = LED7segAnot[number];
                LED7segPIN1 = 0;
                delay_ms(5);
                LED7segPIN1 = 1;
                break; 
        case 1: LED7seg = LED7segAnot[number];
                LED7segPIN2 = 0;
                delay_ms(5);
                LED7segPIN2 = 1;
                break;
        case 2: LED7seg = LED7segAnot[number];
                LED7segPIN3 = 0;
                delay_ms(5);
                LED7segPIN3 = 1;
                break;
        case 3: LED7seg = LED7segAnot[number];
                LED7segPIN4 = 0;
                delay_ms(5);
                LED7segPIN4 = 1;
                break;
    }
}