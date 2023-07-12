#include <time6.h>
#include <system.h>
#include <usart.h>
#include <ano.h>
#include <encoder.h>
#include <pid.h>
#include <motor.h>
#include "motion.h"
#include "systick.h"
#include "key.h"
#include "led.h"



//��ʱ���㹫ʽ��t=per*(psc+1)/72M  ��λ��s
void Tim6_Init(u16 pre,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;  //��ʱ��
	NVIC_InitTypeDef NVIC_InitStructure;  //�ж�
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);	//ʹ�ܶ�ʱ��ʱ��
	
	TIM_TimeBaseInitStruct.TIM_Period=pre;	//���ö�ʱ������
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;	//���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;	//����Ƶ����ʱ��Ƶ�ʵı�ֵ�������벶����ʹ��
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);	//����жϱ�־λ
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);	//������ʱ���ж�(�����ж�)
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_IRQn;	//EXTI3�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	 
	TIM_Cmd(TIM6,ENABLE);
} 


void TIM6_IRQHandler()
{
	
	
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==1)	//�ж������жϷ���
	{
		if(key_data==0)
		{
			if(ce1==2)  //Զ�� ����
			{
				switch(mot1)
				{
					case(0):  if(Qianjin2_240()==1)  mot1=1;  break;
					case(1):  if(Jiao_90()==1)       mot1=2;  break;
					case(2):  if(Qianjin60()==1)     mot1=3;  break;
					case(3):  TIM_SetCompare1(TIM1,1600);  k210_r=0; delay_ms(500);  mot1=4; break;//Զ�� �� ��
					case(4):  if(k210_r==11)  //Զ�� �� �� �ж�
							  {
								  mot1=5;  mot2=1; break;
							  }
							  else if(k210_r==10)
							  {
								  TIM_SetCompare1(TIM1,1300);
								  k210_r=0;  delay_ms(500);
								  mot1=6;  mot2=1;  break;
							  }	break;
					case(5):
						switch(mot2)  // Զ�� �� ��
						{
							case(1):  if(Qianjin15_6()==1)  mot2=2;  break;
							case(2):  if(Jiao90_5()==1)     mot2=3;  break;
							case(3):  if(Qianjin2_40_2()==1)  mot2=4;  break;
							case(4):  led_R=1; while(1);
						}break;
					case(6):  if(k210_r==11)  // Զ�� �� �� �ж�
							  {
								  mot1=7;  mot2=1;  break;
							  }
							  else if(k210_r==10)
							  {
								  mot1=8;  mot2=1;  break;
							  }break;
					case(7):
						switch(mot2)  // Զ�� �� ��
						{
							case(1):  if(Qianjin15_3()==1)    mot2=2;  break;
							case(2):  if(Jiao_90()==1)        mot2=3;  break;
							case(3):  if(Qianjin2_40_3()==1)  mot2=4;  break;
							case(4):  led_R=1; while(1);
						}break;
					case(8):  TIM_SetCompare1(TIM1,1600); if(Jiao180()==1)     mot1=9;   break;
					case(9):  if(Qianjin120()==1)  mot1=10;  break;
					case(10): k210_r=0;  delay_ms(500); mot1=11;  break;
					case(11): if(k210_r==11)  // Զ�� �� �� �ж�
							  {
								  mot1=12;  mot2=1;  break;
							  }
							  else if(k210_r==10)
							  {
								  mot1=13;  mot2=1;  break;
							  }break;
					case(12):
						switch(mot2)
						{
							case(1):  if(Qianjin15_5()==1)   mot2=2;  break;
							case(2):  if(Jiao90_4()==1)        mot2=3;  break;
							case(3):  if(Qianjin2_40_4()==1) mot2=4;  break;
							case(4):  led_R=1;  while(1);
						}break;
					case(13):
						switch(mot2)
						{
							case(1):  if(Qianjin15_5()==1)   mot2=2;  break;
							case(2):  if(Jiao_90()==1)       mot2=3;  break;
							case(3):  if(Qianjin2_40_4()==1) mot2=4;  break;
							case(4):  led_R=1;  while(1);
						}break;
				}
			}
			else if(ce1==1)  //Զ�� �� ��
			{
				switch(mot1)
				{
					case(0):  if(Qianjin2_240()==1)  mot1=1;  break;
					case(1):  if(Jiao90()==1)        mot1=2;  break;
					case(2):  if(Qianjin60()==1)     mot1=3;  break;
					case(3):  TIM_SetCompare1(TIM1,1600);  k210_r=0; delay_ms(500);  mot1=4; break;//Զ�� �� ��
					case(4):  if(k210_r==11)
							  {
								  mot1=5;  mot2=1; break;
							  
							  }
							  else if(k210_r==10)
							  {
								  TIM_SetCompare1(TIM1,1300);
								  k210_r=0;  delay_ms(500);
								  mot1=6;  mot2=1;  break;
							  }	break;
					case(5):
						switch(mot2)  // �� ��
						{
							case(1):  if(Qianjin15_13()==1)  mot2=2;  break;
							case(2):  if(Jiao90_2()==1)     mot2=3;  break;
							case(3):  if(Qianjin2_40_2()==1)  mot2=4;  break;
							case(4):  led_R=1;  while(1);
						}break;
					case(6):  if(k210_r==11)
							  {
								  mot1=7;  mot2=1;  break;
							  }
							  else if(k210_r==10)
							  {
								  mot1=8;  mot2=1;  break;
							  }break;
					case(7):
						switch(mot2)  // �� ��
						{
							case(1):  if(Qianjin15_3()==1)    mot2=2;  break;
							case(2):  if(Jiao_90()==1)        mot2=3;  break;
							case(3):  if(Qianjin2_40_3()==1)  mot2=4;  break;
							case(4):  led_R=1;  while(1);
						}break;
					case(8):  TIM_SetCompare1(TIM1,1600); if(Jiao180()==1)     mot1=9;   break;
					case(9):  if(Qianjin120()==1)  mot1=10;  break;
					case(10): k210_r=0;  delay_ms(500); mot1=11;  break;
					case(11): if(k210_r==11)
							  {
								  mot1=12;  mot2=1;  break;
							  }
							  else if(k210_r==10)
							  {
								  mot1=13;  mot2=1;  break;
							  }break;
					case(12):
						switch(mot2)
						{
							case(1):  if(Qianjin15_4()==1)   mot2=2;  break;
							case(2):  if(Jiao90()==1)        mot2=3;  break;
							case(3):  if(Qianjin2_40_4()==1) mot2=4;  break;
							case(4):  led_R=1;  while(1);
						}break;
					case(13):
						switch(mot2)
						{
							case(1):  if(Qianjin15_99()==1)   mot2=2;  break;
							case(2):  if(Jiao_90()==1)       mot2=3;  break;
							case(3):  if(Qianjin2_40_4()==1) mot2=4;  break;
							case(4):  led_R=1; while(1);
						}break;
				}
			}
		}
		else  
		{
			switch(mot1)
			{
				case(0):  if(Qianjin2_180()==1)  mot1=1;  break;
				case(1):  led_Y=1;               mot1=2;  break;
				case(2):  if(ce1==9)
						  {
							 led_Y=0;  mot1=3;  break;
						  } break;
				case(3):  if(ce1==3)       //��
						  {
							  mot1=4;  mot2=1;    break;  ///////////////////////////////////////////////////
						  }
						  else if(ce1==4)  //��
						  {
							  mot1=5;  mot2=1;    break;   /////////////////////////////////////////////////////
						  }break;
				case(4): 
					switch(mot2)  
					{
						case(1):  if(Jiao180()==1)       mot2=2;  break;
						case(2):  if(Fanhiu2_60()==1)    mot2=3;  break;
						case(3):  if(Jiao_90_11()==1)       mot2=4;  break;
						case(4):  if(Qianjin2_40_12()==1)   mot2=5;  break;
						case(5):  led_R=1; while(1);
					}break;
				case(5):
					switch(mot2)
					{
						case(1):  if(Jiao180()==1)       mot2=2;  break;
						case(2):  if(Fanhiu2_60()==1)    mot2=3;  break;
						case(3):  if(Jiao90_10()==1)        mot2=4;  break;
						case(4):  if(Qianjin2_40()==1)   mot2=5;  break;
						case(5):  led_R=1; while(1);
					}break;
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
//		switch(mot1)  //�ж� ��
//		{
//			case(0):  if(Qianjin2_180()==1)  mot1=1; break;
//			case(1):  led_Y=1;   delay_ms(1000); ce1=3;    mot1=2; break;
//			case(2):  if(ce1==3)     
//					  {
//						  mot1=3;  mot2=1;  led_Y=0;  break;
//					  }
//					  else if(ce1==4)
//					  {
//						  mot1=4;  mot2=1;  led_Y=0;  break;
//					  }break;
//			case(3):
//				switch(mot2)
//				{
//					case(1):  if(Houtui2_30()==1)  mot2=2;  break;
//					case(2):  if(Jiao90()==1)      mot2=3;  break;
//					case(3):  if(Qianjin2_40()==1) mot2=4;  break;
//					case(4):  while(1);
//				}break;
//			case(4):
//				switch(mot2)
//				{
//					case(1):  if(Houtui2_30()==1)  mot2=2;  break;
//					case(2):  if(Jiao_90()==1)     mot2=3;  break;
//					case(3):  if(Qianjin2_40()==1) mot2=4;  break;
//					case(4):  while(1);
//				}
//		}
		
//		switch(mot1)  //�ж� ��
//		{
//			case(0):  if(Qianjin2_180()==1)  mot1=1; break;
//			case(1):  delay_ms(1000);        mot1=2; break;
//			case(2):  if(Houtui2_30()==1)   { mot1=3; delay_ms(1000); }  break;
//			case(3):  if(Jiao_90()==1)       { mot1=4; delay_ms(1000); }  break;
//			case(4):  if(Qianjin2_40()==1)    { mot1=5; delay_ms(1000); }  break;
////			case(2):  if(Qianhou40()==1)  mot1=3; break;
////			case(3):  led_R=1; if(Key_Scam()==0)  { delay_ms(100); led_R=0; mot2=4; }break;
//		}
	
	
	
	
	
	
//		if(k210_mubiao>2)
//		{
//			switch(mot1)  //�ж�
//				{
//					case(0): if(Qianjin150()==1) {mot1=1;  k210_r=0;}  break;
//					case(1): 
//							 if(k210_r==11) 
//							 {
//								 mot1=2; mot2=0; break;
//							 }
//							 else if(k210_r==10)
//							 {
//								 mot1=3; mot2=1; break;
//							 }break;
//					case(2): 
//						switch(mot2)  //�ж� ��
//						{
//							case(0):  if(Qianjin15()==1)  mot2=1; break;
//							case(1):  if(Jiao90()==1)     mot2=2; break;
//							case(2):  if(Qianhou40()==1)  mot2=3; break;
//							case(3):  led_R=1; if(Key_Scam()==0)  { delay_ms(100); led_R=0; mot2=4; }break;
//							case(4):  if(Houtui40()==1)   mot2=5; break;
//							case(5):  if(Jiao90()==1)     mot2=6; break;
//							case(6):  if(Qianjin165()==1) mot2=7; break;
//							case(7):  led_G=1; while(1);
//						} break ;
//						
//					case(3):
//						switch(mot2)
//						{
//							case(1): TIM_SetCompare1(TIM1,1100); k210_r=0; delay_ms(700);   mot2=2; break;  
//							case(2): if(k210_r==11)
//									 {
//										  mot2=3;  mot3=0;
//									 }
//									 else if(k210_r==10)
//									 {
//										  mot2=4;  mot3=0;
//									 }break;
//							case(3): 
//								switch(mot3)  //�ж� ��
//								{
//									case(0):  if(Qianjin15()==1)   mot3=1;  break;
//									case(1):  if(Jiao_90()==1)     mot3=2;  break;
//									case(2):  if(Qianhou40()==1)   mot3=3;  break;
//									case(3):  led_R=1; if(Key_Scam()==0)   {delay_ms(100);led_R=0; mot3=4; } break;
//									case(4):  if(Houtui40()==1)    mot3=5;  break;
//									case(5):  if(Jiao_90()==1)     mot3=6;  break;
//									case(6):  if(Qianjin165()==1)  mot3=7;  break;
//									case(7):  led_G=1; while(1);
//								}break;
//							case(4): TIM_SetCompare1(TIM1,1530);  
//									 if(Qianjin90()==1)         mot2=5; break;

//							case(5): if(Jiao90()==1)       mot2=6; break;
//							case(6): if(Qianjin60()==1)    mot2=7; break;
//							case(7): k210_r=0; delay_ms(700); mot2=8; break;
//							case(8): if(k210_r==11)
//									 {
//										mot2=9;   mot3=1;   break; 
//									 }
//									 else if(k210_r==10)
//									 {
//										mot2=10;   mot3=1;   break;
//									 }break;
//							case(9): 
//								switch(mot3)  //Զ�� �� ��
//								{
//									case(1):  if(Qianjin15_3()==1)  mot3=2;  break;
//									case(2):  if(Jiao90()==1)       mot3=3;  break;
//									case(3):  if(Qianhou40()==1)    mot3=4;  break;
//									case(4):  led_R=1;if(Key_Scam()==0)  {delay_ms(100);led_R=0;   mot3=5; } break;
//									case(5):  if(Houtui40()==1)     mot3=6;  break;
//									case(6):  if(Jiao90()==1)       mot3=7;  break;
//									case(7):  if(Qianjin75()==1)    mot3=8;  break;
//									case(8):  if(Jiao_90()==1)      mot3=9;  break;
//									case(9):  if(Qianjin255()==1)   mot3=10;  break;
//									case(10): led_G=1; while(1);
// 								}break;
//							case(10):   // Զ�� �� ����ʶ��
//								switch(mot3)
//								{
//									case(1):  TIM_SetCompare1(TIM1,1110);   k210_r=0; delay_ms(700); mot3=2; break;
//									case(2):  if(k210_r==11)
//											  {
//												  mot3=3;  mot4=1;  break;
//											  }
//											  else if(k210_r==10)
//											  {
//												  mot3=4;  mot4=1;  break;
//											  }break;
//									case(3):
//										switch(mot4)  //Զ�� �� ��
//										{
//											case(1):  if(Qianjin15_3()==1)  mot4=2;  break;
//											case(2):  if(Jiao_90()==1)      mot4=3;  break;
//											case(3):  if(Qianhou40()==1)    mot4=4;  break;
//											case(4):  led_R=1;if(Key_Scam()==0)  {delay_ms(100);led_R=0;   mot4=5; } break;
//											case(5):  if(Houtui40()==1)     mot4=6;  break;
//											case(6):  if(Jiao_90()==1)      mot4=7;  break;
//											case(7):  if(Qianjin75()==1)    mot4=8;  break;
//											case(8):  if(Jiao_90()==1)      mot4=9;  break;
//											case(9):  if(Qianjin255()==1)   mot4=10;  break;
//											case(10): led_G=1; while(1);
//										}break;
//									case(4):
//										switch(mot4)
//										{
//											case(1):  TIM_SetCompare1(TIM1,1520); mot4=2;  break;
//											case(2):  if(Jiao180()==1)     mot4=3;  break;
//											case(3):  if(Qianjin120()==1)  mot4=4;  break;
//											case(4):  k210_r=0;  delay_ms(500); mot4=5;  break;
//											case(5):  if(k210_r==11)
//													  {
//														  mot4=6;  mot5=1;  break;
//													  }
//													  else
//													  {
//														  mot4=7;  mot5=1;  break;
//													  }break;
//											case(6):
//												switch(mot5)  //Զ�� �� ��
//												{
//													case(1):  if(Qianjin15_3()==1)  mot5=2;  break;
//													case(2):  if(Jiao90()==1)       mot5=3;  break;
//													case(3):  if(Qianhou40()==1)    mot5=4;  break;
//													case(4):  led_R=1; if(Key_Scam()==0)   {delay_ms(100);led_R=0;  mot5=5; } break;
//													case(5):  if(Houtui40()==1)     mot5=6;  break;
//													case(6):  if(Jiao90()==1)       mot5=7;  break;
//													case(7):  if(Qianjin75()==1)    mot5=8;  break;
//													case(8):  if(Jiao90()==1)       mot5=9;  break;
//													case(9):  if(Qianjin255()==1)   mot5=10;  break;
//													case(10): led_G=1; while(1);
//												}break;
//											case(7):
//												switch(mot5)  //Զ�� �� ��
//												{
//													case(1):  if(Qianjin15_3()==1)  mot5=2;  break;
//													case(2):  if(Jiao_90()==1)      mot5=3;  break;
//													case(3):  if(Qianhou40()==1)    mot5=4;  break;
//													case(4):  led_R=1; if(Key_Scam()==0)   {delay_ms(100);led_R=0;  mot5=5;}  break;
//													case(5):  if(Houtui40()==1)     mot5=6;  break;
//													case(6):  if(Jiao_90()==1)      mot5=7;  break;
//													case(7):  if(Qianjin75()==1)    mot5=8;  break;
//													case(8):  if(Jiao90()==1)       mot5=9;  break;
//													case(9):  if(Qianjin255()==1)   mot5=10;  break;
//													case(10): led_G=1; while(1);
//												}break;
//										}
//								}
////						   //case(10): if()
							
							
							
							
							
							
							
							
							
							
							
							
							
							
//								switch(mot3)  //Զ�˵�һ����ת
//								{
////									case(0):  if(Qianjin15_2()==1)  mot3=1;  break;
////									case(1):  if(Jiao90()==1)       mot3=2;  break;
////									case(4):  if(Qianjin60()==1)	mot3=5;  break;  //�ڶ���T��·���ж�
////									
////									
////									
////									case(5): if(Qianjin15_3()==1)	mot3=6;  break;
////									case(6): if(Jiao90()==1)     	mot3=7;  break;
////									case(7): if(Qianhou40()==1)  	mot3=8;  break;  //���յ�
//								}
							//case(5): while(1);
//						}
								
					//if(Qianjin15()==1)  mot1=3; break;
//			
//				}
//		}
//		else
//		{
//			if(k210_mubiao==1)
//			{
//				switch(mot1)
//				{
//					case(0): if(Qianjin75()==1)        mot1=1; break;
//					case(1): if(Jiao90()==1)           mot1=2; break;
//					case(2): if(Qianhou40()==1)        mot1=3; break;
//					case(3): led_R=1; if(Key_Scam()==0)   {delay_ms(100);  led_R=0;    mot1=4; } break;
//					case(4): if(Houtui40()==1)		   mot1=5; break;
//					case(5): if(Jiao90()==1)           mot1=6;kting=0; break;
//					case(6): if(Fanhiu75()==1)        mot1=7;         break;
//					case(7): led_G=1; while(1);
//				}
//			}
//			else if(k210_mubiao==2)
//			{
//				switch(mot1)  //������ת
//				{
//					case(0): if(Qianjin75()==1) mot1=1; break;
//					case(1): if(Jiao_90()==1)   mot1=2; break;
//					case(2): if(Qianhou40()==1) mot1=3; break;
//					case(3): led_R=1; if(Key_Scam()==0) {delay_ms(100);led_R=0; mot1=4;} break;
//					case(4): if(Houtui40()==1)	mot1=5; break;
//					case(5): if(Jiao_90()==1)   mot1=6;kting=0; break;
//					case(6): if(Fanhiu75()==1) mot1=7; break;
//					case(7): led_G=1; while(1);
//				}
//			}
//		}
		
		
		
		
		
		
		
		
	
//			switch(mot1)  //�ж�
//			{
//				case(0): if(Qianjin150()==1) mot1=1;  break;
//				case(1): 
//						 if(k210_r==11) 
//						 {
//							 mot1=2; mot2=0; break;
//						 }
////						 else if(k210_mubiao==10)
////						 {
////							 mot1=3; mot2=1; break;
////						 }
//						break;
//				case(2): 
//					switch(mot2)  //�ж� ��
//					{
//						case(0): if(Qianjin15()==1)  mot2=1; break;
//						case(1): if(Jiao90()==1)     mot2=2; break;
//						case(2): if(Qianhou40()==1)  mot2=3; break;
//						case(3): if(Houtui40()==1)   mot2=4; break;
//						case(4): if(Jiao90()==1)     mot2=5; break;
//						case(5): if(Qianjin150()==1) mot2=6; break;
//						case(6): while(1);
//					} break ;
//	
//			}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//		switch(mot1)  //Զ��
//		{
//			case(0): if(Qianjin150()==1) mot1=1; break;
//			case(1): if(Qianjin90()==1)  mot1=2; break;
//			case(2): if(Qianjin15_2()==1)mot1=3; break;
//			case(3): if(Jiao_90()==1)  	 mot1=4; break;
//			case(4): if(Qianjin60()==1)	 mot1=5; break;
//			case(5): if(Qianjin15_3()==1)mot1=6; break;
//			case(6): if(Jiao90()==1)     mot1=7; break;
//			case(7): if(Qianhou40()==1)  mot1=8; break;
//			case(8): if(Houtui40()==1)   mot1=9; break;
//			case(9): if(Jiao90()==1)     mot1=10;break;
//			case(10): while(1);
//			case(5): if(Jiao90()==1)     mot1=6;kting=0; break;
//			case(6): if(Qianjin150()==1) mot1=7; break;
//			case(7): while(1);
//		}
		
	
//		switch(mot1)  //�ж���ת
//		{
//			case(0): if(Qianjin150()==1) mot1=1; break;
//			case(1): if(Qianjin15()==1)  mot1=2; break;
//			case(2): if(Jiao90()==1)     mot1=3; break;
//			case(3): if(Qianhou40()==1)  mot1=4; break;
//			case(4): if(Houtui40()==1)	 mot1=5; break;
//			case(5): if(Jiao90()==1)     mot1=6;kting=0; break;
//			case(6): if(Qianjin150()==1) mot1=7; break;
//			case(7): while(1);
//		}
		
		
//		switch(mot1)  //�ж���ת
//		{
//			case(0): if(Qianjin150()==1) mot1=1; break;
//			case(1): if(Qianjin15()==1)  mot1=2; break;
//			case(2): if(Jiao_90()==1)     mot1=3; break;
//			case(3): if(Qianhou40()==1)  mot1=4; break;
//			case(4): if(Houtui40()==1)	 mot1=5; break;
//			case(5): if(Jiao_90()==1)     mot1=6;kting=0; break;
//			case(6): if(Qianjin150()==1) mot1=7; break;
//			case(7): while(1);
//		}
		
//		switch(mot1)  //������ת
//		{
//			case(0): if(Moton_Forward(2,0)==1) mot1=1; break;
//			case(1): if(Jiao90()==1)           mot1=2; break;
//			case(2): if(Qianhou40()==1)        mot1=3; break;
//			case(3): if(Houtui40()==1)		   mot1=4; break;
//			case(4): if(Jiao90()==1)           mot1=5;kting=0; break;
//			case(5): if(Moton_Forward(2,0)==1) mot1=6; break;
//			case(6): while(1);
//		}
		
//		switch(mot1)  //������ת
//		{
//			case(0): if(Moton_Forward(2,0)==1) mot1=1; break;
//			case(1): if(Jiao_90()==1)           mot1=2; break;
//			case(2): if(Qianhou40()==1)        mot1=3; break;
//			case(3): if(Houtui40()==1)		   mot1=4; break;
//			case(4): if(Jiao_90()==1)           mot1=5;kting=0; break;
//			case(5): if(Moton_Forward(2,0)==1) mot1=6; break;
//			case(6): while(1);
//		}


//		k210_r=1;
//		if(k210_r==1)
//		{
//		
//			switch(mot1)
//			{
//				case(0): if(Qianjin75()==1)          mot1=1; break;
//				case(1): if(Jiao90()==1)           mot1=2; break;
//				case(2): if(Qianhou40()==1)        mot1=3; break;
//				case(3): if(Houtui40()==1)		   mot1=4; break;
//				case(4): if(Jiao90()==1)           mot1=5;kting=0; break;
//				case(5): if(Qianjin75()==1) mot1=6;                  break;
//				case(6): while(1);
//			}
//		}
//		else if(k210_r==2)
//		{
//			switch(mot1)
//			{
//				case(0): if(Qianjin75()==1) mot1=1;          break;
//				case(1): if(Jiao_90()==1)           mot1=2; break;
//				case(2): if(Qianhou40()==1)        mot1=3; break;
//				case(3): if(Houtui40()==1)		   mot1=4; break;
//				case(4): if(Jiao_90()==1)           mot1=5;kting=0; break;
//				case(5): if(Qianjin75()==1) mot1=6;                  break;
//				case(6): while(1);
//			}
//		}

	}
	
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);	//����жϱ�־λ
}


