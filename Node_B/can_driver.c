#include "header.h"
extern can2 v1;
extern u8 rxf,tf,c1;
void can2_init(void)
{
	u32 *ptr=(u32 *)0xE0038000;
	PINSEL1|=0x14000;
	VPBDIV=1;
	C2MOD=1;
	C2BTR=0x001c001d;
	AFMR=1;
	//msg Acceptance setting
	ptr[0]=0x21002201;
	ptr[1]=0x22022203;
	SFF_sa=0;
	SFF_GRP_sa=0x8;
	EFF_sa=0x8;
	EFF_GRP_sa=0x8;
	ENDofTable=0x8;
	AFMR=0;
	C2MOD=0;
}
#define TCS	((C2GSR>>3)&1)
#define RBS	(C2GSR&1)
void can2_tx(can2 t)
{
	C2TID1=t.id;
	C2TFI1=(t.dlc)<<16;
	if(t.rtr==0)
	{
		C2TDA1=t.byteA;
		C2TDB1=t.byteB;
	}
	else
		C2TFI1|=(t.rtr)<<30;
	C2CMR=1|(1<<5);
	while(TCS==0);
}
void can2_rx(can2 *t)
{
	while(RBS==0);
	t->id=C2RID;
	t->dlc=(C2RFS>>16)&0xf;
	t->rtr=(C2RFS>>30)&1;
	if((t->rtr)==0)
	{
		t->byteA=C2RDA;
		t->byteB=C2RDB;
	}
	C2CMR=(1<<2);
}








//void can2_ISR(void)__irq
//{
//	 v1.id=C2RID;
//	 v1.dlc=((C2RFS>>16)&0xf);
//	 v1.rtr=((C2RFS>>30)&1);
//	 if(v1.rtr==0)
//	 	v1.byteA=C2RDA;
//	 C2CMR=1<<2;
//	 rxf=1;
//	 VICVectAddr=0;
//}
//
//void congig_vic_for_can2(void)
//{
//	VICIntSelect=0;
//	VICVectCntl0=27|(1<<5);		  
//	VICVectAddr0=(u32)can2_ISR;	
//	VICIntEnable=(1<<27);
//	C2IER=1;
//}
//
//void timer1_ISR(void)__irq
//{
//	//tf++;
//	tf=1;
//	c1=1;
//	T0IR=1;
//	VICVectAddr=0;
//}
//
//void congig_vic_for_timer1(void)
//{
//	VICIntSelect=0;
//	VICVectCntl1=4|(1<<5);		  
//	VICVectAddr1=(u32)timer1_ISR;	
//	VICIntEnable=(1<<4);
//}
//
//void config_timer1(u32 ms)
//{
//	u32 a[]={15,60,30,15,15};
//	T0PC=0;
//	T0PR=a[VPBDIV]*1000-1;
//	T0TC=0;
//	T0TCR=1;
//	T0MR0=ms;
//	T0MCR=3;
//}


