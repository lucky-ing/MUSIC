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
//ALIENTEK战舰STM32开发板实验45
//录音机 实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 
 		    
	
 int main(void)
 {	 
	 u8 num=0,w=0,res=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	//LED_Init();			     //LED端口初始化
	//TPAD_Init();		//初始化触摸按键
	//LCD_Init();				//LCD初始化
	//KEY_Init();	 			//按键初始化
	Audiosel_Init();	//初始化音源选择
	//usmart_dev.init(72);//usmart初始化
 	mem_init(SRAMIN);	//初始化内部内存池	
 	VS_Init();	  

 	exfuns_init();					//为fatfs相关变量申请内存  
  f_mount(0,fs[0]); 		 		//挂载SD卡 
 	f_mount(1,fs[1]); 				//挂载FLASH.
	POINT_COLOR=RED;      
	while(1)
	{
		Audiosel_Set(0);	//MP3通道
 		//LED1=0; 	  
		//Show_Str(60,210,200,16,"存储器测试...",16,0);
		printf("存储器测试...\n");
		VS_Ram_Test();	    
		//Show_Str(60,210,200,16,"正弦波测试...",16,0);
		printf("正弦波测试...\n");		
 		VS_Sine_Test();	   
		//Show_Str(60,210,200,16,"<<WAV录音机>>",16,0); 		
    printf("<<WAV录音机>>\n");			
		//LED1=1;
		printf("输入a以进入音乐播放，输入b进入录音机\n");
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
				printf("a:音乐\nb:录音机\nl:删除\n ");
			}
}
		
		
		//RecoderPlay();
		
		
		printf("竟然出错了。。。\n");
		while(1);
	}    					  
}


