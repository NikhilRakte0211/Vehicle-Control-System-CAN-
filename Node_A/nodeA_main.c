#include"header.h"
int c,c1,rif,lif,hlf,H,L,R,tf,c1;
can2 v1,v2;
#define l (1<<17)
#define h (1<<18)
#define r (1<<19)
int main()
{
	u32 adc_out;
	IODIR0=l|r|h;
	IOSET0=l|r|h;
	can2_init();
	adc_init();
	config_vic();
	uart0_init(9600);
	congig_vic_for_timer1();
	config_timer1(1000);
	config_all_EXNT();
	v1.byteA=v2.byteA=0;
	v1.byteB=v2.byteB=0;
	while(1)
	{
		if(lif)
		{
			lif=0;
			R=0;
			v1.id=0x203;	 
			v1.dlc=1;
			v1.rtr=0;
			L^=1;
			if(L){
				v1.byteA=4;
				IOCLR0=l;
				IOSET0=r;
			}
			else{	    			
				v1.byteA=0; 
				IOCLR0=l;
			}
			can2_tx(v1);
		}
		if(rif)
		{
			rif=0;
			L=0;
			v1.id=0x201;	 
			v1.dlc=1;
			v1.rtr=0;
			R^=1;
			if(R){
				v1.byteA=1;	 
				IOCLR0=r;
				IOSET0=l;
			}
			else{
				v1.byteA=0;  
				IOSET0=r;
			}
			can2_tx(v1);
		}
		if(hlf)
		{
			hlf=0;
			v1.id=0x202;	
			v1.dlc=1;
			v1.rtr=0;
			H^=1;
			if(H){
				v1.byteA=2;
				IOCLR0=h;
				}
			else{
				v1.byteA=0;
				IOSET0=h;
			}
			can2_tx(v1);
		}
		if(tf)
		{
			adc_out=adc_read(1);
	   		v2.id=0x100;	 
			v2.dlc=2;
			v2.rtr=0;
			v2.byteA=adc_out; 
			can2_tx(v2);
			tf=0;
		}
		
//		if(L){
//			IOCLR0=l;
//			IOSET0=r;
//		}
//		else{
//			IOSET0=l;
//			uart0_tx_string("L indi off\r\n");
//		}
//		if(R){
//			IOCLR0=r;
//			IOSET0=l;
//			uart0_tx_string("R indi on\r\n");
//		}
//		else{
//			IOSET0=r;
//			uart0_tx_string("R indi off\r\n");
//		}
//		if(H){
//			IOCLR0=h;
//			uart0_tx_string("HL on\r\n");
//		}
//		else{
//			IOSET0=h;
//			uart0_tx_string("HL off\r\n");
//		}

	}
}



