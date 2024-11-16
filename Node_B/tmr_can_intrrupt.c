#include "header.h"
extern can2 v1;
extern u8 rxf,tf,c1;

void can2_ISR(void)__irq
{
	 v1.id=C2RID;
	 v1.dlc=((C2RFS>>16)&0xf);
	 v1.rtr=((C2RFS>>30)&1);
	 if(v1.rtr==0)
	 	v1.byteA=C2RDA;
	 C2CMR=1<<2;
	 rxf=1;
	 VICVectAddr=0;
}

void congig_vic_for_can2(void)
{
	VICIntSelect=0;
	VICVectCntl0=27|(1<<5);		  
	VICVectAddr0=(u32)can2_ISR;	
	VICIntEnable=(1<<27);
	C2IER=1;
}

void timer1_ISR(void)__irq
{
	//tf++;
	tf=1;
	c1=1;
	T0IR=1;
	VICVectAddr=0;
}

void congig_vic_for_timer1(void)
{
	VICIntSelect=0;
	VICVectCntl1=4|(1<<5);		  
	VICVectAddr1=(u32)timer1_ISR;	
	VICIntEnable=(1<<4);
}

void config_timer1(u32 ms)
{
	u32 a[]={15,60,30,15,15};
	T0PC=0;
	T0PR=a[VPBDIV]*1000-1;
	T0TC=0;
	T0TCR=1;
	T0MR0=ms;
	T0MCR=3;
}




