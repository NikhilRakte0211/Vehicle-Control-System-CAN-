#include "header.h"
extern int c,rif,lif,hlf,tf,c1;
void EXNT0_ISR_HL(void) __irq
{
	c++;
	hlf=1;
	EXTINT=0x1;
	VICVectAddr=0;
}

void EXNT1_ISR_LI(void) __irq
{
	c++;
	lif=1;
	rif=0;
	EXTINT=0x2;
	VICVectAddr=0;
}

void EXNT2_ISR_RI(void) __irq
{
	c++;
	rif=1;
	lif=0;	
	EXTINT=0x4;
	VICVectAddr=0;
}

void config_vic(void)
{
	VICIntSelect=0;

	VICVectCntl1=14|(1<<5);		   //sw16  HL
	VICVectAddr1=(u32)EXNT0_ISR_HL;

	VICVectCntl2=15|(1<<5);		   //sw14  LI
	VICVectAddr2=(u32)EXNT1_ISR_LI;

	VICVectCntl3=16|(1<<5);		   //sw15  RI
	VICVectAddr3=(u32)EXNT2_ISR_RI;	

	VICIntEnable=1<<14|1<<15|1<<16;
}

void config_all_EXNT(void)
{
	PINSEL0|=0xA0000000;
	PINSEL1|=1;
	EXTMODE=0x7;
	EXTPOLAR=0;
}

void timer1_ISR(void)__irq
{
	//tf++;
	c1++;
	tf=1;
	T0IR=1;
	VICVectAddr=0;
}

void congig_vic_for_timer1(void)
{
	VICIntSelect=0;
	VICVectCntl0=4|(1<<5);		  
	VICVectAddr0=(u32)timer1_ISR;	
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









