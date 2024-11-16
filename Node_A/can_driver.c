#include "header.h"

void can2_init(void)
{
	PINSEL1|=0x14000;
	VPBDIV=1;
	C2MOD=1;
	C2BTR=0x001c001d;
	AFMR=2;

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




