#include"header.h"
#define l (1<<17)
#define h (1<<18)
#define r (1<<19)
#define BUZZER (1<<21)
can2 v1,v2;
u32 rxf,rf,lf,hf,ef,t1,c1,c,t2,tf=0,adc_out;
float v_out,temp;
int main()
{
	
	can2_init();
	lcd_init();
	cgram();
	congig_vic_for_can2();
	congig_vic_for_timer1();
	config_timer1(500);
	IODIR0=l|h|r|BUZZER;
	IOSET0=l|h|r;
	IOCLR0=BUZZER;
	lcd_cmd(0x01);
	while(1)
	{
		if(tf)
		{
			if(rf){
				lcd_cmd(0x80);
				lcd_data(' ');
				lcd_data(' ');
				lcd_cmd(0x8e);
				IOSET0=l;
				t1^=1;
				if(t1){
					lcd_data(1);  //   -	pg 1
					lcd_data(0);  //   >	 pg 0
					IOCLR0=r;
				}
				else{
					lcd_data(' ');
					lcd_data(' ');
					IOSET0=r;
				}
			}
			else{
				lcd_cmd(0x8e);
				lcd_data(' ');
				lcd_data(' ');
				IOSET0=r;
			}
			if(lf){
				lcd_cmd(0x8e);
				lcd_data(' ');
				lcd_data(' ');
				lcd_cmd(0x80);
				IOSET0=r;
				t2^=1;
				if(t2){
					lcd_data(2);  //   <    pg 2
					lcd_data(1);  //   -    pg 1
					IOCLR0=l;
				}
				else{
					lcd_data(' ');
					lcd_data(' ');
					IOSET0=l;
				}
			}
			else{
				lcd_cmd(0x80);
				lcd_data(' ');
				lcd_data(' ');
				IOSET0=l;
			}
			tf=0;
		}


		if(hf){
			IOCLR0=h;
			lcd_cmd(0x87);
			lcd_data(3);   //HL on
			lcd_data(5);
		}
		else{
			IOSET0=h;
			lcd_cmd(0x87);
			lcd_data(4);  //HL off
			lcd_data(' ');
		}
			
				 
		
		if(ef){
			adc_out=v1.byteA;
			v_out=(adc_out*3.3)/1023;
			temp=(v_out-0.5)/0.01;
			lcd_cmd(0xc0);
			if(temp>31)
			{
				lcd_string("Engine Temp Err.");
				IOSET0=BUZZER;
			}
			else{
				IOCLR0=BUZZER;
				lcd_string("Eng Temp:");
				lcd_float(temp);
				lcd_cmd(0xce);
				lcd_string("dC");
			   }
			ef=0;
		}




		if(rxf)
		{
			
			rxf=0;
			if(v1.id==0x201){
				if(v1.byteA&1){
					rf=1;
					lf=0;
				}
				else
					rf=0;
			}
			if(v1.id==0x202){
				if((v1.byteA>>1)&1)
					hf=1;
				else
					hf=0;
			}			   
			if(v1.id==0x203){
			   if((v1.byteA>>2)&1){
			   		rf=0;
					lf=1;
				}
				else
					lf=0;
			}
			if(v1.id==0x100)
				  ef=1;	
		}		
	}		
}


