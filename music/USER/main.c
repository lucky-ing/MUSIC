#include "led.h"
#include "delay.h"
//#include "key.h"
//#include "tpad.h"
#include "sys.h"
//#include "lcd.h"
#include "usart.h"	 
#include "flash.h"
#include "sram.h"
#include "malloc.h"
//#include "string.h"
#include "mmc_sd.h"
#include "ff.h"
#include "exfuns.h"
//#include "fontupd.h"
//#include "text.h"
#include "piclib.h"
//#include "string.h"
//#include "usmart.h"
#include "fattester.h"
#include "piclib.h"
#include "vs10xx.h"
#include "mp3player.h"
#include "audiosel.h"
#include "recorder.h"
//ALIENTEKս��STM32������ʵ��45
//¼���� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
 		    
	
 int main(void)
 {	 
	 u8 num=0,w=0,res=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	//LED_Init();			     //LED�˿ڳ�ʼ��
	//TPAD_Init();		//��ʼ����������
	//LCD_Init();				//LCD��ʼ��
	//KEY_Init();	 			//������ʼ��
	Audiosel_Init();	//��ʼ����Դѡ��
	//usmart_dev.init(72);//usmart��ʼ��
 	mem_init(SRAMIN);	//��ʼ���ڲ��ڴ��	
 	VS_Init();	  

 	exfuns_init();					//Ϊfatfs��ر��������ڴ�  
  f_mount(0,fs[0]); 		 		//����SD�� 
 	f_mount(1,fs[1]); 				//����FLASH.
	POINT_COLOR=RED;      
	while(1)
	{
		Audiosel_Set(0);	//MP3ͨ��
 		//LED1=0; 	  
		//Show_Str(60,210,200,16,"�洢������...",16,0);
		printf("�洢������...\n");
		VS_Ram_Test();	    
		//Show_Str(60,210,200,16,"���Ҳ�����...",16,0);
		printf("���Ҳ�����...\n");		
 		VS_Sine_Test();	   
		//Show_Str(60,210,200,16,"<<WAV¼����>>",16,0); 		
    printf("<<WAV¼����>>\n");			
		//LED1=1;
		printf("����a�Խ������ֲ��ţ�����b����¼����\n");
		while(1)
		{
			if(USART_RX_STA&0x8000)
			{	
				num=USART_RX_STA&0x3fff;
				
				for(w=0;w<num;w++)
				{
					res=USART_RX_BUF[w];
				}
				USART_RX_STA=0;
				switch(res)
				{
					case MUSIC:Mp3Play();break;
					case RECODER:RecoderPlay();break;
					case DELETE:DeleteRecorder();break;
					default:             break;
				}
				printf("a:����\nb:¼����\nl:ɾ��\n ");
			}
}
		
		
		//RecoderPlay();
		
		
		printf("��Ȼ�����ˡ�����\n");
		while(1);
	}    					  
}


