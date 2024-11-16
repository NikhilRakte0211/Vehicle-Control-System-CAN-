#include"header.h"
void delay_sec(u32 sec)
{
	s32 a[]={15,60,30,15,15};
	T1PC=0;
	T1PR=a[VPBDIV]*1000000-1;
	T1TC=0;
	T1TCR=1;
	while(T1TC<sec);
	T1TCR=0;
}

void delay_ms(u32 ms)
{
	s32 a[]={15,60,30,15,15};
	T1PC=0;
	T1PR=a[VPBDIV]*1000-1;
	T1TC=0;
	T1TCR=1;
	while(T1TC<ms);							 
	T1TCR=0;
}
