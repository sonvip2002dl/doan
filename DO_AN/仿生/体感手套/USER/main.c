#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "pwm.h"
#include "adc.h"

float pitch,roll,yaw; 		//ŷ����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
short temp;					//�¶�
float ek_pitch,ek_roll,ek_yaw;
float ek1_pitch,ek1_roll,ek1_yaw;
float Kp=10;//PID����
int balance_pitch,balance_roll,balance_yaw;
u8 Res;
u8 flag=0;
u8 adcx;
//����1����1���ַ� 
//c:Ҫ���͵��ַ�
void usart1_send_char(u8 c)
{

	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,c);   

} 
//�������ݸ�����������λ�����(V2.6�汾)
//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//���28�ֽ����� 
	send_buf[len+3]=0;	//У��������
	send_buf[0]=0X88;	//֡ͷ
	send_buf[1]=fun;	//������
	send_buf[2]=len;	//���ݳ���
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//��������
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//����У���	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//�������ݵ�����1 
}
//���ͼ��ٶȴ��������ݺ�����������
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)
{
	u8 tbuf[12]; 
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;
	usart1_niming_report(0XA1,tbuf,12);//�Զ���֡,0XA1
}	
//ͨ������1�ϱ���������̬���ݸ�����
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
//roll:�����.��λ0.01�ȡ� -18000 -> 18000 ��Ӧ -180.00  ->  180.00��
//pitch:������.��λ 0.01�ȡ�-9000 - 9000 ��Ӧ -90.00 -> 90.00 ��
//yaw:�����.��λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//��0
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;	
	tbuf[18]=(roll>>8)&0XFF;
	tbuf[19]=roll&0XFF;
	tbuf[20]=(pitch>>8)&0XFF;
	tbuf[21]=pitch&0XFF;
	tbuf[22]=(yaw>>8)&0XFF;
	tbuf[23]=yaw&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//�ɿ���ʾ֡,0XAF
} 
 
void Xianfu_Pwm(void)
{	
	  int Amplitude=2500;    //===PWM������7200 ������7100
		int Amplitude1=500;	
		if(balance_pitch>Amplitude)  balance_pitch=Amplitude;	
		if(balance_roll>Amplitude)  balance_roll=Amplitude;
	  if(balance_yaw>Amplitude)  balance_yaw=Amplitude;
		if(balance_pitch<Amplitude1)  balance_pitch=Amplitude1;	
		if(balance_roll<Amplitude1)  balance_roll=Amplitude1;
	  if(balance_yaw<Amplitude1)  balance_yaw=Amplitude1;
}

void PD(void)
{
		ek_roll=ek1_roll-roll;
		balance_roll=Kp*(ek_roll*11.11+500);   //===����ƽ����Ƶĵ��PWM  PD����   kp��Pϵ�� kd��Dϵ�� ;
	  
		ek_pitch=ek1_pitch-pitch;
	  balance_pitch=Kp*(pitch*11.11+500);
	  	
	  ek_yaw=ek1_yaw-yaw;
	  balance_yaw=Kp*(yaw*11.11+500);
	  Xianfu_Pwm();
}

void send_bluetooth()
{
	balance_pitch=pitch;
	balance_roll=roll;
	balance_yaw=yaw;
	USART_SendData(USART3,adcx);
	/*USART_SendData(USART3,balance_pitch);
	USART_SendData(USART3,balance_roll);
	USART_SendData(USART3,balance_yaw);*/
	USART_SendData(USART3,balance_pitch);
	USART_SendData(USART3,balance_roll);
	USART_SendData(USART3,balance_yaw);
}

int main(void)
{ 
	u8 t=0,report=1;			//Ĭ�Ͽ����ϱ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(500000);		//��ʼ�����ڲ�����Ϊ500000
	uart3_init(9600);//��ʼ�����ڲ�����Ϊ115200����ͷ����
	LED_Init();					//��ʼ��LED 
	KEY_Init();					//��ʼ������
 	OLED_Init();
	MPU_Init();					//��ʼ��MPU6050
	Adc2_PA4_Init();
	while(mpu_dmp_init())
	{
		OLED_ShowString(12,24,"MPU6050 Error",16);
		OLED_Refresh_Gram();
		delay_ms(200);
	}	
	OLED_Clear();
	OLED_ShowString(0,0, " ADC :       ",12);
	OLED_ShowString(0,12," Temp:    . C",12);  
	OLED_ShowString(0,24,"Pitch:    . C",12);  
 	OLED_ShowString(0,36," Roll:    . C",12);  
 	OLED_ShowString(0,48," Yaw :    . C",12);
	OLED_Refresh_Gram();
	
	
 	while(1)
	{
		adcx=Get_Adc(ADC_Channel_4);		
		OLED_ShowNum(36+6,0,adcx,4,12);
		
		
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
			if((t%1)==0)
			{ 
				delay_us(620);
				USART_SendData(USART3,0xAA);
				
				delay_us(620);		
				if(temp<0)
				{
					OLED_ShowChar(36,12,'-',12,1);		//��ʾ����
					temp=-temp;		//תΪ����
				}else OLED_ShowChar(36,12,' ',12,1);		//ȥ������ 
				OLED_ShowNum(36+6,12,temp/100,3,12);
				OLED_ShowNum(36+30,12,temp%10,1,12);
				USART_SendData(USART3,adcx);
				
				delay_us(620);
				temp=pitch*10;
				if(temp<0)
				{
					OLED_ShowChar(36,24,'-',12,1);		//��ʾ����
					temp=-temp;		//תΪ����
				}else OLED_ShowChar(36,24,' ',12,1);		//ȥ������ 
				OLED_ShowNum(36+6,24,temp/10,3,12);
				OLED_ShowNum(36+30,24,temp%10,1,12);
				balance_pitch=pitch;
				USART_SendData(USART3,balance_pitch);
				
				delay_us(620);
				temp=roll*10;
				if(temp<0)
				{
					OLED_ShowChar(36,36,'-',12,1);		//��ʾ����
					temp=-temp;		//תΪ����
				}else OLED_ShowChar(36,36,' ',12,1);		//ȥ������ 
				OLED_ShowNum(36+6,36,temp/10,3,12);
				OLED_ShowNum(36+30,36,temp%10,1,12);
				balance_roll=roll;
				USART_SendData(USART3,balance_roll);
				
				delay_us(620);
				temp=yaw*10;
				if(temp<0)
				{
					OLED_ShowChar(36,48,'-',12,1);  	//��ʾ����
					temp=-temp;		//תΪ����
				}else OLED_ShowChar(36,48,' ',12,1);		//ȥ������ 
				OLED_ShowNum(36+6,48,temp/10,3,12);
				OLED_ShowNum(36+30,48,temp%10,1,12);
				balance_yaw=yaw;
				USART_SendData(USART3,balance_yaw);
				
				OLED_Refresh_Gram();
				t=0;
				LED0=!LED0;//LED��˸
				
				delay_us(620);
				USART_SendData(USART3,0xEE);
				
				//delay_ms(1);
				
				//PD();
				//send_bluetooth();
			}
		}
		t++; 
	} 	
}
