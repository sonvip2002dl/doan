/**************************************
��Ŀ���ƣ�����С˵�Ķ���
���ߣ�������
ʱ�䣺2020��12��8��09:36:05
�汾��v1.0
���䣺2809786963@qq.com
���ͽ̳̣�������
����������������my
**************************************/


#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "sram.h"   
#include "malloc.h" 
#include "usmart.h"  
#include "sdio_sdcard.h"    
#include "malloc.h" 
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	 
#include "piclib.h"	
#include "string.h"	
#include "math.h"	
#include "touch.h"

u8 menu_num;//��ǰ���˵�ҳ��
u32 page;//��ǰҳ��
//char chapter_name[50];//��ǰ�½���
u32 page_offset[1000];//����ҳ��ƫ��
//u32 page_off_mult;//ҳ��ƫ�Ʊ���
u8 txt_num;//��ǰ���ͼ������
u8 txt_path_name[30][60];//����ͼ��·��
u32 bookmark[30];				//�����Ӧ��ǩ Ҳ����ҳ�� �´ν���ֱ��ƫ��ҳ��
char txt_name[4][30]={"","","",""};//��ʾ4��ͼ������
u8 pname[60];			//���ڴ򿪵��ļ���·��
int SIZE=24;			//��ʼ������
char buff[2500];//һҳ���� �����ĵ�
int page_mul_cnt=0;//��ȡ���� һ��1000ҳ
int now_page_mul;//��ǰ1000ҳ�ı���
u32 data_offset;//��ȡƫ��  ��дflash��


//��ʾ������
void menu(void);
//��ȡ������ֵ
u16 get_ts_val(int key);
//��ȡ�ļ����ݵ�LCD
int read_to_lcd(void);
//����С˵��
u8 lcd_dis_files(u8 * path);
//�Ķ�ģʽ
void read_mode(void);
//���������ʽ
int setting(void);
//���ý���
void show_setting(void);
//Ŀ¼����
u32 txt_dir_scan(void);
//�ļ�ϵͳ���� ����С˵
void fatfs_choose(void);
//��ȡ���ݵ�flash
void file_data_to_w25q(void);
//����ҳ��õ�ҳ��
u32 ident_get_page(u32 page_offset);
//�����ļ� ��ʾ����Ļ
u8 mf_scan_file(u8 * path);
//ˢ����ʾ�������
void re_dis_txtname(int i);
//��·�����ļ��� ת ����·���ļ���
char* path_change(char *oldpath);
//����ҳ���õ�ҳ��
u32 ident_get_offset(u32 page);
//�����ڴ�1000ҳҳ��
void update_page_offset(void);
//������ǩ����
void read_bookmark(void);
//������ǩ���ݵ�flash
void save_bookmark(void);
//�����������ݵ�flash
void save_bookinfo(void);
//ɾ��С˵
void del_txt(u8 *path);
//ɾ��С˵���ƽ���
void del_txt_ctrl(void);
	



int main(void)
{        
 	//DIR picdir;	 		//ͼƬĿ¼
	u32 recode=0;
	
	u8 key;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED  
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ�� 
	tp_dev.init();			//������ʼ��	
	W25QXX_Init();				//��ʼ��W25Q128
	usmart_dev.init(168);		//��ʼ��USMART
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
  f_mount(fs[0],"0:",1); 		//����SD�� 
 	f_mount(fs[1],"1:",1); 		//����FLASH.
	
	
	/******************��ֹ��������****************************/
	W25QXX_Read((u8 *)&recode,1024*1024*4-4,4);//�������ڴ�
	if(recode != 0xffaaffaa)
	{
		recode = 0xffaaffaa;
		W25QXX_Write((u8 *)&recode,1024*1024*4-4,4);//д��flash
		//W25QXX_Erase_Chip();//������Ƭ
		txt_num=0;//��ʼ��С˵����0 ��Ȼ�����޷����� 
		save_bookinfo();//���浽flash
	}
	/******************��ֹ��������****************************/
	
	
	while(font_init()) 			//����ֿ�
	{  
		LCD_Clear(WHITE);		   	//����
 		POINT_COLOR=RED;			//��������Ϊ��ɫ	   	   	  
		LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");
		while(SD_Init())			//���SD��
		{
			LCD_ShowString(30,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,70,200+30,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(30,70,200,16,16,"SD Card OK");
		LCD_ShowString(30,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,"0:");//�����ֿ�
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(30,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(30,110,200,16,16,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����	       
	}     

	//f_opendir(&picdir,"0:/SYSTEM/PICTURE"); //��Ŀ¼
	delay_ms(150);
	piclib_init();										//��ʼ����ͼ	  
	delay_ms(150);
	LCD_Clear(GBLUE);//����
	ai_load_picfile("0:/SYSTEM/PICTURE/logo.gif",0,0,lcddev.width,lcddev.height,1);//��ʾͼ
	read_bookmark();//����ͼ�� ��ǩ����
	
	memset(page_offset,0,1000*4);//���ҳ������
	menu_num=1;//��ʾ��һҳ
	//lcd_dis_files("0:/TXT");//����ϵͳ����
	menu();//��ʾ������
	while(1)
	{
		key = get_ts_val(1);
		if(key!=0)
		{
			printf("key=%d\n",key);
			switch(key)//ѡ��Ҫ�򿪵�ͼ��
			{
				case 1: if(txt_num-4*(menu_num-1)>=1){
									strcpy((char *)pname,(char *)txt_path_name[0+(menu_num-1)*4]);//��Ҫ�򿪵��鼮���Ƹ�ֵ
					
									page = bookmark[0+(menu_num-1)*4];//����flash�������ǩ��ʼ�������ҳ��
									if(page >= 0xffff)page=0;
										read_mode();//�����Ķ�ģʽ
									bookmark[0+(menu_num-1)*4] = page;//�˳�������ǩ
									save_bookmark();
									}break;
				
				case 2:	if(txt_num-4*(menu_num-1)>=2){
									strcpy((char *)pname,(char *)txt_path_name[1+(menu_num-1)*4]);
					
									page = bookmark[1+(menu_num-1)*4];
									if(page >= 0xffff)page=0;
									read_mode();//�����Ķ�ģʽ
									bookmark[1+(menu_num-1)*4] = page;
									save_bookmark();
									}break;
									
									
				case 3: if(txt_num-4*(menu_num-1)>=3){
									strcpy((char *)pname,(char *)txt_path_name[2+(menu_num-1)*4]);
					
									page = bookmark[2+(menu_num-1)*4];
									if(page >= 0xffff)page=0;
									read_mode();//�����Ķ�ģʽ
									bookmark[2+(menu_num-1)*4] = page;
									save_bookmark();
									}break;
									
				case 4: if(txt_num-4*(menu_num-1)>=4){
									strcpy((char *)pname,(char *)txt_path_name[3+(menu_num-1)*4]);
					
									page = bookmark[3+(menu_num-1)*4];
									if(page >= 0xffff)page=0;
									read_mode();//�����Ķ�ģʽ
									bookmark[3+(menu_num-1)*4] = page;
									save_bookmark();
									}break;

				case 5:		//����ͼ��
									fatfs_choose();//�ļ�ϵͳѡ���ļ�����
									save_bookinfo();//�����鼮���ݵ�flash
									printf("��ǰͼ��������%d\r",txt_num);
									break;
				
				case 6:		del_txt_ctrl();//ɾ��ͼ��
									break;
				
				case 111: if((txt_num-1)/4+1>menu_num)menu_num++;
										printf("menu_num = %d\n",menu_num);//��һҳ
									break;
				
				case 222: if(1<menu_num)menu_num--;
										printf("menu_num = %d\n",menu_num);//��һҳ
									break;	
			}
			
			menu();//��ʾ������
			data_offset=0;//ƫ������
			page_mul_cnt=0;//1000ҳ��������
		}
		delay_ms(10);
	}
}

//�Ķ�ģʽ �����Ķ�
void read_mode(void)
{
	int key;
	u8 res,n;
	char spr_name[30];

	sprintf((char *)spr_name,"%s",pname);
	res=mf_open((char *)spr_name,FA_READ);//ֻ����
	if(res==FR_OK)printf("�򿪣�%s\n",(char *)spr_name);
	else return;//��ʧ��
	
	LCD_Clear(WHITE);//����
	n=page/1000+1;//����Ҫ���¼���
	while(n--)
	{
		LCD_ShowNum(200,376,page/1000+1-n,2,24);//��ʾ������
		LCD_ShowChar(234,376,'/',24,0);
		LCD_ShowNum(250,376,page/1000+1,2,24);
		file_data_to_w25q();	//����ҳ�� һ��1000ҳ
	}
	mf_lseek(page_offset[page%1000]);//�õ���ʼƫ��
	
	read_to_lcd();//��ȡ�ĵ����ݵ���Ļ
	
	Show_Str(420,770,200,24,"����",24,0);
	Show_Str(5,770,50,24,"����",24,0);
	Show_Str(218,770,50,24,"Ŀ¼",24,0);
	LCD_ShowNum(400,0,page,5,16);

	
	while(1)
	{
			key = get_ts_val(2);
			if(key != 0)
			{
//				printf("key == %d\n",key);
				switch(key)//����ѡ��
				{
					case 101:
										page++;
										if(page%1000==0 && page>0)
										{
											//���»���ҳ������
											file_data_to_w25q();//��д��ҳ�뵽flash
											update_page_offset();//�����ڴ�1000ҳҳ��
										}
										res=mf_lseek(page_offset[page%100]);
										if(res==0)read_to_lcd();
										break;//��һҳ
					case 202:	
										
										if(page==0)
										{
											Show_Str(180,730,200,24,(u8*)"�Ѿ��ǵ�һҳ",24,0);
											break;
										}
										page--;
										if(page%999==0 && page>0)
										{
											update_page_offset();//�����ڴ�1000ҳҳ��
										}
										res=mf_lseek(page_offset[page%1000]);
										if(res==0)read_to_lcd();
										break;//��һҳ
					case 303:
					case 404:break;
					case 5: 
									return;//�������ݵ�flash//���� 
					case 6:
								res=setting();
								if(res)  //�޸������˳�
								{
										res=0;
										LCD_Clear(BACK_COLOR);//�����껹ԭ����
										Show_Str(50,50,400,700,(u8 *)buff,SIZE,0); 
								}else //�����˳� 
								{
									LCD_Fill(0,570,480,800,BACK_COLOR);
									Show_Str(50,50,400,700,(u8 *)buff,SIZE,0); 
								}
								break;
					case 7:page=txt_dir_scan();//Ŀ¼ɨ�� ����ҳ��
								
								update_page_offset();//�����ڴ�1000ҳҳ��
								res=mf_lseek(page_offset[page%1000]);//ƫ�Ƶ�ҳ��
								if(res==0)read_to_lcd();
								break;
				}
				Show_Str(420,770,200,24,"����",24,0);
				Show_Str(5,770,50,24,"����",24,0);
				Show_Str(218,770,50,24,"Ŀ¼",24,0);
				LCD_ShowNum(400,0,page,5,16);
				//printf("lseek=%ld\n",offset);
			}
	}
}

//���ý���
void show_setting()
{
	int i;
	u16 clor[7] = {WHITE,BLACK,BLUE,BRED,GRED,GBLUE,RED};
	LCD_Fill(0,570,480,800,GRAY);
	LCD_Fill(45,580,75,604,BLACK);
	LCD_Fill(190,580,220,604,WHITE);
	LCD_Fill(335,580,365,604,GBLUE);
	
	Show_Str(34+45,580,64,24,"ҹ��",24,1);
	Show_Str(34+190,580,64,24,"����",24,1);
	Show_Str(34+335,580,64,24,"����",24,1);
	
	Show_Str(10,630,50,24,"����",24,1);
	Show_Str(10,690,50,24,"����",24,1);
	Show_Str(10,750,50,24,"�ֺ�",24,1);
	for(i=0; i<7; i++)
	{
		LCD_Fill(80+i*50,630,120+i*50,654,clor[i]);
		LCD_Fill(80+i*50,690,120+i*50,714,clor[i]);
	}
	Show_Str(80,750,400,24,"12��     16��     24��    32��",24,1);
	//Show_Str(420,770,200,24,"����",24,0);
}
//����
int setting(void)
{	
	int key;
	show_setting();//��ʾ����
	while(1)
	{
		key = get_ts_val(3);
		if(key)
		{
//			printf("key3=%d\n",key);
//			printf("%d,%d\n",tp_dev.x[0],tp_dev.y[0]);
			switch(key)//����ѡ��
			{
				//case 5:key=0;goto exit;break;//����
				//����
				case 10:BACK_COLOR=WHITE;return 1;
				case 11:BACK_COLOR=BLACK;return 1;
				case 12:BACK_COLOR=BLUE;return 1;
				case 13:BACK_COLOR=BRED;return 1;
				case 14:BACK_COLOR=GRED;return 1;
				case 15:BACK_COLOR=GBLUE;return 1;
				case 16:BACK_COLOR=RED;return 1;
				//������ɫ
				case 17:POINT_COLOR = WHITE;return 1;
				case 18:POINT_COLOR = BLACK;return 1;
				case 19:POINT_COLOR = BLUE;return 1;
				case 20:POINT_COLOR = BRED;return 1;
				case 21:POINT_COLOR = GRED;return 1;
				case 22:POINT_COLOR = GBLUE;return 1;
				case 23:POINT_COLOR = RED;return 1;
				case 30:POINT_COLOR = WHITE;BACK_COLOR=BLACK;return 1;
				case 31:POINT_COLOR = BLACK;BACK_COLOR=WHITE;return 1;
				case 32:POINT_COLOR = BLACK;BACK_COLOR=GBLUE;return 1;
				//�ֺ�
				case 24:SIZE=12;return 1;
				case 25:SIZE=16;return 1;
				case 26:SIZE=24;return 1;
				case 28:SIZE=32;return 1;
				case 27:goto exit;
			}
			
		}
	}
exit:
	return 0;
}
//��ʾ������
void menu(void)
{
	char spr_buf[60];//ƴ������
	
	int len1,len2,len3,len4;

	BACK_COLOR = BROWN;//����
	POINT_COLOR = BLACK;//������ɫ
	LCD_Clear(WHITE);
	//ai_load_picfile((u8 *)"0:/PICTURE/menu.jpg",0,0,lcddev.width,lcddev.height,1);//��ʾͼƬ
	LCD_Fill(0,0,480,50,BROWN);
	Show_Str(220,10,200,24,"���",24,0);
	Show_Str(380,770,100,24,"����ͼ��",24,1);
	Show_Str(0,770,100,24,"ɾ��ͼ��",24,1);
	
	//printf("txt_num = %d\n",txt_num);//��ӡ��ǰ�������
	//txt_num=0;
	if(txt_num != 0)
	{
		BACK_COLOR = WHITE;//����
		POINT_COLOR = BLACK;//������ɫ
		
		LCD_Fill(0,350,480,380,WHITE);
		LCD_Fill(0,700,480,730,WHITE);
		
		if(txt_num-4*(menu_num-1)>=1)
		{
			strcpy((char *)txt_name[0],path_change((char *)txt_path_name[0+(menu_num-1)*4]));//��ȡ�ļ�·��
			len1 = strlen(txt_name[0]);//��ȡ�ļ�����
			
			sprintf(spr_buf,"0:/SYSTEM/PICTURE/%s.jpg",txt_name[0]);//�鿴ϵͳ�Ƿ���ƥ��ͼƬ
			if(mf_open(spr_buf,FA_OPEN_EXISTING)==FR_OK)
				ai_load_picfile(spr_buf,60,100,150,250,1);	//��ʾͼƬ1
			else 
				ai_load_picfile("0:/SYSTEM/PICTURE/txt.jpg",60,100,150,250,1);	//��ʾͼƬ1
			
			Show_Str(60+75-len1*4,350,200,16,(u8 *)txt_name[0],16,0);//��ʾ����
		}
		
		if(txt_num-4*(menu_num-1)>=2)
		{
			strcpy((char *)txt_name[1],path_change((char *)txt_path_name[1+(menu_num-1)*4]));//��ȡ�ļ�·��
			len2 = strlen(txt_name[1]);//��ȡ�ļ�����
			
			sprintf(spr_buf,"0:/SYSTEM/PICTURE/%s.jpg",txt_name[1]);//�鿴ϵͳ�Ƿ���ƥ��ͼƬ
			if(mf_open(spr_buf,FA_OPEN_EXISTING)==FR_OK)
				ai_load_picfile(spr_buf,280,100,150,250,1);
			
			else 
				ai_load_picfile("0:/SYSTEM/PICTURE/txt.jpg",280,100,150,250,1);//��ʾͼƬ2
			
			Show_Str(280+75-len2*4,350,200,16,(u8 *)txt_name[1],16,0);//��ʾ����
		}
		
		
		if(txt_num-4*(menu_num-1)>=3)
		{
			strcpy((char *)txt_name[2],path_change((char *)txt_path_name[2+(menu_num-1)*4]));//��ȡ�ļ�·��
			len3 = strlen(txt_name[2]);//��ȡ�ļ�����
			
			sprintf(spr_buf,"0:/SYSTEM/PICTURE/%s.jpg",txt_name[2]);//�鿴ϵͳ�Ƿ���ƥ��ͼƬ
			if(mf_open(spr_buf,FA_OPEN_EXISTING)==FR_OK)
				ai_load_picfile(spr_buf,60,450,150,250,1);//��ʾͼƬ3
			else 
				ai_load_picfile("0:/SYSTEM/PICTURE/txt.jpg",60,450,150,250,1);//��ʾͼƬ3
			
			Show_Str(60+75-len3*4,700,200,16,(u8 *)txt_name[2],16,0);//��ʾ����
		}
		
		
		if(txt_num-4*(menu_num-1)>=4)
		{
			strcpy((char *)txt_name[3],path_change((char *)txt_path_name[3+(menu_num-1)*4]));//��ȡ�ļ�·��
			len4 = strlen(txt_name[3]);//��ȡ�ļ�����
			
			sprintf(spr_buf,"0:/SYSTEM/PICTURE/%s.jpg",txt_name[3]);//�鿴ϵͳ�Ƿ���ƥ��ͼƬ
			if(mf_open(spr_buf,FA_OPEN_EXISTING)==FR_OK)
				ai_load_picfile(spr_buf,280,450,150,250,1);//��ʾͼƬ4
			else 
				ai_load_picfile("0:/SYSTEM/PICTURE/txt.jpg",280,450,150,250,1);//��ʾͼƬ4
			
			Show_Str(280+75-len4*4,700,200,16,(u8 *)txt_name[3],16,0);//��ʾ����
		}
	}
	
}



//��ȡ�ļ��ı����ݵ�lcd
int read_to_lcd(void)
{
	int len;
	u8 res=0,hc_cnt=0;
	u16 tlen=0;
	
	LCD_Clear(BACK_COLOR);
	
	
	if(SIZE==12)len=2400;
	else if(SIZE==16)len=1200;
	else if(SIZE==24)len=700;
	else if(SIZE==32)len=400;
	while(1)
	{
		res=f_read(file,buff+tlen,1,&br);
		
		if(!res)	//������
		{
			tlen+=br;
			
			if(*(buff+tlen-1)=='\n')hc_cnt++;
			
			if(tlen+hc_cnt*SIZE>len && strncmp(buff+tlen-2,"��",2)==0)//�˳�����
				break;
			
			else if(tlen+hc_cnt*SIZE>len && strncmp(buff+tlen-2,"��",2)==0)//�˳�����
				break;
			
			else if(tlen+hc_cnt*SIZE>len && buff[tlen-1]=='\n')
				break;
		}	
	}
	buff[tlen]='\0';//��β��
	
	res=Show_Str(50,50,400,700,(u8 *)buff,SIZE,0); //��ʾ����Ļ
	//printf("next_page: tlen=%d ,  offset=%ld,  hc_cnt=%d\n",(int)tlen,offset,hc_cnt);
	
	return tlen;
}


//��ȡ������ֵ
int x_last,y_last,x_last2,y_last2,flag=0,time=0;
u16 get_ts_val(int key)
{
	int i=10;
	int val = 0;
	//if(flag==1)time++;
	if((tp_dev.scan(0))==1 && flag==0)
	{
//		printf("����\n");
//		printf("[%d,%d]%d\r\n",x_last,y_last,flag);
		flag=1;
		x_last=tp_dev.x[0];
		y_last=tp_dev.y[0];
	}
	if(flag==1)
	{
		flag=0;
		while(1)
		{
			tp_dev.scan(0);
			delay_ms(1);
			if(tp_dev.x[0]>480)
			{
//				printf("�ɿ�\n");
//  			printf("[%d,%d]\n",x_last2,y_last2);
				if(x_last2-x_last<-50)val=101;//<-
				else if(x_last2-x_last>50)val=202;//->
				else if(y_last2-y_last<-50)val=111;//��
				else if(y_last2-y_last>50)val=222;//��
				tp_dev.x[0]=0;tp_dev.y[0]=0;
				break;
			}
				x_last2=tp_dev.x[0];
				y_last2=tp_dev.y[0];
		}
	}
	if(val != 0)
	{
		x_last2=0;y_last2=0;
		return val;
	}
	
	if(key == 1)//����1  ѡ��ͼ��
	{
		if(x_last2>60 && x_last2<210)
		{
			if(y_last2>100 && y_last2<100+250)val=1;
			if(y_last2>450 && y_last2<700)val=3;
		}else if(x_last2>280 && x_last2<430)
		{
			if(y_last2>100 && y_last2<100+250)val=2;
			if(y_last2>450 && y_last2<700)val=4;
		}		
		if(x_last2>400 && y_last2>750 && x_last2<479 && y_last2<799)val=5;//����ͼ��
		if(x_last2>0 && y_last2>750 && x_last2<100 && y_last2<799)val=6;//ɾ��ͼ��
	}
	else if(key == 2)//�Ķ�ģʽ
	{
		if(x_last2<100 && y_last2>750)val=6;//����
		else if(x_last2>400 && y_last2>750 && x_last2<479 && y_last2<799)val=5;//����
		else if(x_last2>215 && y_last2>750 && x_last2<265 && y_last2<799)val=7;//Ŀ¼
		else if(x_last2>230 && y_last2>10 && x_last2<479 && y_last2<700)val=101;//��һҳ
		else if(x_last2>0 && y_last2>10 && x_last2<220 && y_last2<700)val=202;//��һҳ
	}
	else if(key == 3)//����3 ����
	{
		for(i=0; i<7; i++)
		{
			if(x_last2>80+i*50 && x_last2<80+(i+1)*50)
			{
				if(y_last2>630 && y_last2<654)val=10+i;//10-16
				if(y_last2>690 && y_last2<714)val=17+i;//17-23
			}
		}
		if(y_last2>745 && y_last2<790)
		{
			if(x_last2>80 && x_last2<150)val=24;
			if(x_last2>180 && x_last2<230)val=25;
			if(x_last2>250 && x_last2<320)val=26;
			if(x_last2>330 && x_last2<450)val=28;
		}
		else if(y_last2>540 && y_last2<600)
		{
			if(x_last2>45 && x_last2<145)val=30;
			else if(x_last2>190 && x_last2<290)val=31;
			else if(x_last2>335 && x_last2<435)val=32;
		}
		else if(x_last2>100 && y_last2>100 && x_last2<380 && y_last2<540)val=27;//ȡ������
	}
	else if(key == 4)//Ŀ¼
	{
		for(i=0; i<20; i++)
		{
			if(x_last2>10 && x_last2<400+50)
			{
				if(y_last2>40*i && y_last2<40*(i+1))val=i+1;//1-20
			}
		}
		if(x_last2>400 && x_last2<480 && y_last2>10 && y_last2<760)val=21;
	}
	else if(key == 5)//����5 �ļ�ϵͳ
	{
		for(i=0; i<15; i++)
		{
			if(x_last2>10 && x_last2<450)
			{
				if(y_last2>90+45*i && y_last2<90+45*(i+1))val=i+1;//1-15
			}else if(x_last2>400 && y_last2>750 && x_last2<479 && y_last2<799)val=17;//����
			
		}
	}
	else if(key==6)//�Ƿ�ѡ�� 
	{
		if(x_last2>180 && y_last2>420 && x_last2<230 && y_last2<480)val=1;//��
		else if(x_last2>250 && y_last2>420 && x_last2<320 && y_last2<480)val=2;//��
	}
	else if(key==7)//ɾ��ͼ��
	{
		if(x_last2>200 && y_last2>85 && x_last2<245 && y_last2<125)val=1;
		else if(x_last2>425 && y_last2>80 && x_last2<470 && y_last2<125)val=2;
		else if(x_last2>200 && y_last2>430 && x_last2<245 && y_last2<475)val=3;
		else if(x_last2>200 && y_last2>430 && x_last2<245 && y_last2<475)val=4;
		else if(x_last2>400 && y_last2>750 && x_last2<479 && y_last2<799)val=5;//����
	}
	
	x_last2=0;y_last2=0;
	return val;
}



//����ϵͳС˵��
u8 lcd_dis_files(u8 * path)
{
	FRESULT res;	  
  char *fn;   /* This function is assuming non-Unicode cfg. */
 	fileinfo.lfsize = _MAX_LFN * 2 + 1;
	fileinfo.lfname = mymalloc(SRAMIN,fileinfo.lfsize);
  res = f_opendir(&dir,(const TCHAR*)path); //��һ��Ŀ¼
  if (res == FR_OK) 
	{	
		while(1)
		{
			res = f_readdir(&dir, &fileinfo);                   //��ȡĿ¼�µ�һ���ļ�
			if (res != FR_OK || fileinfo.fname[0] == 0) break;  //������/��ĩβ��,�˳�
			//if (fileinfo.fname[0] == '.') continue;             //�����ϼ�Ŀ¼
			fn = *fileinfo.lfname ? fileinfo.lfname : fileinfo.fname;
			if(strncmp(fn-4+strlen(fn),".txt",4)==0)//���ж��ǲ���С˵
				sprintf((char *)txt_path_name[txt_num],"%s/%s",path,fn);//ƴ��·��
			txt_num++;
		} 
  }	  
	myfree(SRAMIN,fileinfo.lfname);
}


//Ŀ¼����
u32 txt_dir_scan()
{
	int key;
	u32 dir_offset[20];
	int i;
	int cnt;
	int res,flag,flag2;
	int tlen;
	u32 tlen_sum=0;
	
	mf_lseek(0);
	
txt_dir_choose:
	res=0;flag=0;flag2=0;tlen=2;cnt=0;
	
	for(i=0; i<20; i++)
	{
		if(i%2)LCD_Fill(0,i*40,400,(i+1)*40,0xCDF7);
		else LCD_Fill(0,i*40,400,(i+1)*40,GRAY);
	}
	
	while(1)
	{
		res=f_read(file,buff+tlen,1,&br);
		if(!res && br==1)	//������
		{
			tlen+=br;
			tlen_sum+=1;//ƫ���ۼ�
			if(flag==0 && strncmp(buff+tlen-2,"��",2)==0)flag=1;
			if(flag>=1)
			{
				if(flag2==0 && strncmp(buff+tlen-2,"��",2)==0)//��ʼ�����
				{
					flag2=1;
				}else if(*(buff+tlen-1)=='\n')tlen-=1;//��ȥ�����\n
				else if(*(buff+tlen-1)>'A' && *(buff+tlen-1)<'z')tlen-=1;//��ȥ
				
				flag++;	
				if(flag>50){
					flag=0;flag2=0;
				}
			}
			if(flag2 >= 1)
			{
				if(*(buff+tlen-1)=='\n' || *(buff+tlen-1)=='\r'
					|| (*(buff+tlen-1)>'A' && *(buff+tlen-1)<'z'))//����������
				{
					if(flag<50)//������ʾ
						*(buff+tlen-1)='\0';
					else 
						*(buff+tlen-9)='\0';
					
					printf("%s\n",buff+tlen-flag);//buff+tlen-flag-2���ǵ��� ƫ��tlen_sum+tlen-flag-2
					dir_offset[cnt] = tlen_sum-flag;//��¼ƫ��λ�� ����Ŀ¼�½���ƫ��
					
					Show_Str(0,16+cnt*40,400,16+(cnt+1)*40,(u8*)buff+tlen-flag,16,1);//��ʾ�½ڵ�LCD
					cnt++;//��һ��
					
					flag=0;//��������һ��λ��
					flag2=0;
					
					tlen=2;//�����ؼ��
					
					if(cnt==20)break;//20�½ڼ�����
				}
			}
			if(tlen>1100)tlen=0;
		}	
		else 
		{
			printf("��ȡ���\n");
			break;
		}
	}
	while(1)//��������
	{
		key = get_ts_val(4);
		
		if(key>0 && key<=20)
		{
			
			printf("��תҳ����%d\n",ident_get_page(dir_offset[key-1]));
			return ident_get_page(dir_offset[key-1]);//����ҳ��
			
		}
		else if(key==21)
		{
			return 0;
		}
		else if(key==111)goto txt_dir_choose;//����
		
	}
	
}







//��ȡҳ�����ݵ�flash
void file_data_to_w25q()
{
	int len,page_cnt=0;
	u8 res=0,hc_cnt=0;
	u16 tlen=0;
	
	
	LCD_ShowChar(256,400,'%',24,0);
	
	if(SIZE==12)len=2400;				//��������
	else if(SIZE==16)len=1200;
	else if(SIZE==24)len=700;
	else if(SIZE==32)len=400;
	
	res=mf_lseek(data_offset);//ƫ�Ƹ���
	
	if(res==0)
		printf("��ʼд��ҳ�뵽flash\n");
	else 
		return ;
	
	while(1)
	{
			while(1)//��ʼʶ��ҳ��
			{
					while(1)
					{
						res=f_read(file,buff+tlen,1,&br);
						if(!res && br==1)	//������
						{
							tlen+=br;
							if(*(buff+tlen-1)=='\n')hc_cnt++;
							
							if(tlen+hc_cnt*SIZE>len && strncmp(buff+tlen-2,"��",2)==0)//�˳�����
								break;
							
							else if(tlen+hc_cnt*SIZE>len && strncmp(buff+tlen-2,"��",2)==0)//�˳�����
								break;
							
							else if(tlen+hc_cnt*SIZE>len && buff[tlen-1]=='\n')
								break;
						}	
						else 
						{
							data_offset += tlen;
							W25QXX_Write((u8*)page_offset,1024*1024*5+4*1000*page_mul_cnt+4*(page_cnt%1000),4*(page_cnt%1000));//д��flash
							return ;
						}
					}
					
					//if(page_cnt<5)printf("flash :tlen=%d ,  offset=%ld,  hc_cnt=%d\r\n",(int)tlen,offset,hc_cnt);
					page_offset[page_cnt] = data_offset;//����ҳ��
					data_offset+=(tlen);//�ļ�ƫ�Ƹ���
					
					page_cnt++;//ҳ���
					if(page_cnt==1000)
					{	page_cnt=0;
						break;//һ�ζ�1000��ҳ��
					}
					
					hc_cnt=0;tlen=0;
					
					if(page_cnt%10==0)
						LCD_ShowNum(220,400,page_cnt/10,2,24);//��ʾ���ذٷֱ�
			}
			W25QXX_Write((u8*)page_offset,1024*1024*5+4*1000*page_mul_cnt,4*1000);//д��flash
			page_mul_cnt++;//�����Լ�
			
			break;//ʶ��ҳ����� ����
//			if(page_mul_cnt==1)//��ȡ1�� 1000*1=1000ҳ
//			{	
			
//			}
	}
	
}





//����ҳ��(ƫ��)�õ�ҳ��
u32 ident_get_page(u32 page_off)
{
	u32 n=0,pg_offset1,pg_offset2;
	u32 cnt=100;
	while(cnt--)
	{
		if(page_off > page_offset[999])//����ȱ�ƪ�����Ҫ��͸���1000ҳҳ��
		{
			file_data_to_w25q();//д��ҳ�뵽flash
			page+=1000;//����ҳ��
			update_page_offset();//�����ڴ�1000ҳҳ��
		}
		else if(page_off < page_offset[0])//����ȱ�ƪ����С��ҪС�͸��µ���һ��ҳ��
		{
			page-=1000;//����ҳ��
			update_page_offset();//�����ڴ�1000ҳҳ��
		}
		else break;
	}
	cnt =1000*100;
	while(cnt)
	{
		W25QXX_Read((u8 *)&pg_offset1,1024*1024*5+4*n,4);//����ҳ������
		W25QXX_Read((u8 *)&pg_offset2,1024*1024*5+4*(n+1),4);//����ҳ������
		
		if(page_off>=pg_offset1 && page_off<pg_offset2)break;
		
		if(page_off>pg_offset1+500*20)n+=20;
		else if(page_off>pg_offset1)n+=1;
		else if(page_off<pg_offset1)n-=1;
		else if(page_off<pg_offset1-500*20)n-=20;
	}
	printf("%ld->%ld \r\n",page_offset,n);
	return n;
}


//����ҳ���õ�ҳ��
u32 ident_get_offset(u32 page)
{
	u32 pg_offset;
	W25QXX_Read((u8 *)&pg_offset,1024*1024*5+4*page,4);//����ҳ������
	
	printf("%ld->%ld  \r\n",page,pg_offset);
	return pg_offset;
}

//�����ڴ�1000ҳҳ��
void update_page_offset(void)
{
		now_page_mul = page/1000;
		memset(page_offset,0,1000*4);
		W25QXX_Read((u8 *)&page_offset,1024*1024*5+(page/1000)*4*1000,4*1000);//�������ڴ�
}
			


//�ļ�ϵͳ���� ����С˵
char txt_pathname[15][60];//��·�����ļ���
void fatfs_choose(void)
{
	int i;
	int key,key2;
	mf_scan_file("0:/");
	while(1)
	{
		key = get_ts_val(5);
		if(key>0 && key<16)
		{
			if(strncmp(txt_pathname[key-1]-4+strlen(txt_pathname[key-1]),".txt",4)==0)
			{
				LCD_Fill(140,300,340,340,BROWN);//
				LCD_Fill(140,340,340,480,GRAY);//
				Show_Str(192,304,200,24,"����ͼ��",24,1);
				Show_Str(150,360,200,16,"�Ƿ����鼮����ܣ�",16,1);
				Show_Str(145,400,200,16,(u8*)txt_pathname[key-1],16,1);
				LCD_Fill(180,440,220,470,WHITE);//��
				LCD_Fill(260,440,300,470,WHITE);//��
				Show_Str(190,445,200,24,"��     ��",24,1);
				while(1)
				{
					key2 = get_ts_val(6);
					if(key2==1){
						strcpy((char*)txt_path_name[txt_num],(char*)txt_pathname[key-1]);//����·��
						txt_num++;
						printf("�����鼮��%s\r\n",txt_path_name[txt_num-1]);
						for(i=0; i<txt_num; i++)
						{
							printf("%s\r\n",txt_path_name[i]);
						}
//						mf_scan_file("0:/");
						return ;
//						break;
					}
					else if(key2==2){mf_scan_file("0:/");
					break;}
				}
			}
			else mf_scan_file((u8*)txt_pathname[key-1]);
		}else if(key==17)
		{
			break;
		}
	}
	
}
	
	
	
	

//ɾ��С˵
void del_txt(u8 *path)
{
	u8 i,j;
	for(i=0; i<txt_num; i++)
	{
		if(strcmp(path,txt_path_name[i])==0)
		{
			for(j=i; j<txt_num; j++)
			{
				strcpy(txt_path_name[j],txt_path_name[j+1]);
			}
			txt_num--;
			break;
		}
	}save_bookinfo();//�������ݵ�flash
}

//ɾ��С˵���ƽ���
void del_txt_ctrl(void)
{
	int key,key2;
	Show_Str(380,770,100,24,"    ȡ��",24,0);
	Show_Str(0 , 770,100,24,"        ",24,0);
	if(txt_num-4*(menu_num-1)>=1)
	{
		ai_load_picfile("0:/SYSTEM/PICTURE/del.jpg",210,85,30,30,1);	//��ʾͼƬdel
	}
	
	if(txt_num-4*(menu_num-1)>=2)
	{
		ai_load_picfile("0:/SYSTEM/PICTURE/del.jpg",430,85,30,30,1);	//��ʾͼƬdel
	}
	
	if(txt_num-4*(menu_num-1)>=3)
	{
		ai_load_picfile("0:/SYSTEM/PICTURE/del.jpg",210,435,30,30,1);	//��ʾͼƬdel
	}
	
	if(txt_num-4*(menu_num-1)>=4)
	{
		ai_load_picfile("0:/SYSTEM/PICTURE/del.jpg",430,435,30,30,1);	//��ʾͼƬdel
	}
	
	while(1)
	{
		key = get_ts_val(7);
		if(key!=0 && txt_num-4*(menu_num-1)>=key)
		{
				LCD_Fill(140,300,340,340,BROWN);//
				LCD_Fill(140,340,340,480,GRAY);//
				Show_Str(192,304,200,24,"ɾ��ͼ��",24,1);
				Show_Str(150,360,200,16,"�Ƿ��鼮�Ƴ���ܣ�",16,1);
				Show_Str(145,400,200,16,(u8*)txt_path_name[key-1+(menu_num-1)*4],16,1);
				LCD_Fill(180,440,220,470,WHITE);//��
				LCD_Fill(260,440,300,470,WHITE);//��
				Show_Str(190,445,200,24,"��     ��",24,1);
				while(1)
				{
					key2 = get_ts_val(6);
					if(key2==1){    //��
						del_txt(txt_path_name[key-1+(menu_num-1)*4]);
						return ;
					}
					else if(key2==2) //��
						return ;
				}
		}else if(key==5)return ;//�˳�
	}
	
}

//�����ļ� ��ʾ����Ļ
u8 mf_scan_file(u8 * path)
{
	u8 txt_cnt=0;
	int i;
	FRESULT res;	  
  char *fn;   /* This function is assuming non-Unicode cfg. */

 	fileinfo.lfsize = _MAX_LFN * 2 + 1;
	fileinfo.lfname = mymalloc(SRAMIN,fileinfo.lfsize);
	  
	
	res = f_opendir(&dir,(const TCHAR*)path); //��һ��Ŀ¼
	if (res == FR_OK) 
	{	
		LCD_Clear(WHITE);//��ʾ����
		LCD_Fill(0,0,480,50,BROWN);//
		Show_Str(208,7,200,32,"�ļ�",32,1);
		while(1)
		{
			res = f_readdir(&dir, &fileinfo);                   //��ȡĿ¼�µ�һ���ļ�
			if (res != FR_OK || fileinfo.fname[0] == 0) break;  //������/��ĩβ��,�˳�
			fn = *fileinfo.lfname ? fileinfo.lfname : fileinfo.fname;
			sprintf(txt_pathname[txt_cnt],"%s/%s",path,fn);//ƴ��·����
			//printf("%s\n",txt_pathname[txt_cnt]);
			//��ʾ����Ļ
			LCD_Fill(50,90+txt_cnt*45,75,90+(txt_cnt+1)*45,BROWN);
			LCD_DrawLine(75,90+(txt_cnt+1)*45,400,90+(txt_cnt+1)*45);
			Show_Str(80,100+txt_cnt*45,300,24,(u8*)fn,24,0);
			
			txt_cnt++;
			if(txt_cnt>=15)break;
		}
		for(i=0; i<15-txt_cnt; i++)
			memset(txt_pathname[15-1-i],0,60);//�����һ�ε�·��
	
		Show_Str(420,770,200,24,"����",24,0);
		
		
  }	  
	myfree(SRAMIN,fileinfo.lfname);
    return res;	  
}
	
	




//��·�����ļ��� ת ����·���ļ���
char* path_change(char *oldpath)
{
	//   0:TXT/���޴�½.txt  -> ���޴�½
	int i;
	static char path_buf[30];//��������
	char old_path[60];
	
	strcpy(old_path,oldpath);//��ֹ�޸ı�Դ
	
	
	old_path[strlen(old_path)-4]='\0';  //   0:TXT/���޴�½
	
	for(i=strlen(old_path); i>0; i--)  
	{
		if(old_path[i]=='/')
			break;
	}
	strcpy(path_buf,old_path+i+1);    //     ���޴�½
	
	
	return path_buf;
}






//������ǩ���ݵ�flash
void save_bookmark(void)
{
	u8 i;

	for(i=0; i<txt_num; i++)
	{
		W25QXX_Write((u8*)&bookmark[i],1024*1024*4+i*64+60,4);//д��flash
		printf("������ǩ %d��%ld\r\n",i,bookmark[i]);
	}
}
//�����������ݵ�flash
void save_bookinfo(void)
{
	u8 i;

	for(i=0; i<txt_num; i++)
	{
		W25QXX_Write((u8*)txt_path_name[i],1024*1024*4+i*64,60);//д��flash
		printf("%s	",txt_path_name[i]);
	}W25QXX_Write((u8*)&txt_num,1024*1024*4+30*64,1);//д��flash
	printf("д����������%d\r\n",txt_num);
}



//������ǩ����
void read_bookmark(void)
{
	u8 i;
	for(i=0; i<30; i++)
	{
		W25QXX_Read((u8 *)txt_path_name[i],1024*1024*4+i*64,60);//�������ڴ�
		W25QXX_Read((u8 *)&bookmark[i],1024*1024*4+i*64+60,4);//�������ڴ�
		printf("������ǩ %d��%ld\r\n",i,bookmark[i]);
	}W25QXX_Read((u8 *)&txt_num,1024*1024*4+30*64,1);//�������ڴ�
	printf("������������%d\r\n",txt_num);
}






