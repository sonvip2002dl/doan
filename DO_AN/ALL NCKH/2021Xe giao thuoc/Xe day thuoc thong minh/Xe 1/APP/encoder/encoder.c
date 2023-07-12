#include <encoder.h>


void Encoder_Init()
{
	Encoder_Init_Tim3();
	Encoder_Init_Tim4();
}

void Encoder_Init_Tim3()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //定时器3时钟
	
	/* GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;   //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//PA6 | PA7
	
	/* 定时器 */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  //缺省定时器接结构体
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //预分频
	TIM_TimeBaseStructure.TIM_Period=65535; //自动重转载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	/* 编码器 */
	/* 第3、4参数可决定加减方向 */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //使用编码器模式3
	
	/* 滤波 */
	TIM_ICStructInit(&TIM_ICInitStructure);  //缺省定时器接结构体
	TIM_ICInitStructure.TIM_ICFilter=10;  //滤波器 低通滤波
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_SetCounter(TIM3,0);  //设置定时器值
	TIM_Cmd(TIM3, ENABLE);   //使能定时器
}


void Encoder_Init_Tim4()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //定时器4时钟
	
	/* GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;   //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//PA6 | PA7
	
	/* 定时器 */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);  //缺省定时器接结构体
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //预分频
	TIM_TimeBaseStructure.TIM_Period=65535; //自动重转载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	/* 编码器 */
	/* 第3、4参数可决定加减方向 */
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);  //使用编码器模式3
	
	/* 滤波 */
	TIM_ICStructInit(&TIM_ICInitStructure);  //缺省定时器接结构体
	TIM_ICInitStructure.TIM_ICFilter=10;  //滤波器 低通滤波
	TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
	TIM_SetCounter(TIM4,0);  //设置定时器值
	TIM_Cmd(TIM4, ENABLE);   //使能定时器
}


/* 读取编码器的值 */
short Encoder_Read(int TIMX)
{
	short encoder;
	switch(TIMX)
	{                           /* 读取定时器值 */     /* 定时器值置零 */
		case 3:  encoder=(short)TIM_GetCounter(TIM3);  TIM_SetCounter(TIM3,0);  break;	
		case 4:  encoder=(short)TIM_GetCounter(TIM4);  TIM_SetCounter(TIM4,0);  break;	
		default: encoder=0;
	}
	return encoder;
}

