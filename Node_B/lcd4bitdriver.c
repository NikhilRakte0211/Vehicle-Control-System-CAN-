#include"header.h"
void lcd_data(u8 data)
{
	u32 temp;
	IOCLR1=0xFE<<16;
	temp=(data&0xF0)<<16;
	IOSET1=temp;
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(10);
	IOCLR1=1<<19;

	IOCLR1=0xFE<<16;
	temp=(data&0x0F)<<20;
	IOSET1=temp;
	IOSET1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(10);
	IOCLR1=1<<19;
}
void lcd_cmd(u8 cmd)
{
	u32 temp;
	IOCLR1=0xFE<<16;
	temp=(cmd&0xF0)<<16;
	IOSET1=temp;
	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(10);
	IOCLR1=1<<19;

	IOCLR1=0xFE<<16;
	temp=(cmd&0x0F)<<20;
	IOSET1=temp;
	IOCLR1=1<<17;
	IOCLR1=1<<18;
	IOSET1=1<<19;
	delay_ms(10);
	IOCLR1=1<<19;
}
void lcd_init(void)
{
	IODIR1=0xFE<<16;
	IOCLR1=1<<19;
	PINSEL2=0x0;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
}
void lcd_string(s8 *p)
{
	while(*p)
	{
		lcd_data(*p);
		p++;
	}
}


void lcd_atoi(int n)
{
	int a[10],i;
	if(n==0)
		lcd_data('0');
	if(n<0)
	{
		lcd_data('-');
		n=-n;
	}
	i=0;
	while(n)
	{
		a[i]=n%10+48;
		n=n/10;
		i++;
	}
	for(i=i-1;i>=0;i--)
	lcd_data(a[i]);
}


void lcd_binary(u8 num)
{
	int pos;
	lcd_cmd(0x01);
	for(pos=7;pos>=0;pos--)
	{
		if((num>>pos)&1)
			lcd_data('1');
		else
			lcd_data('0');
	}
}

void lcd_float(float f)
{
int i;
	if(f==0)
	{
		lcd_string("0.000000");
		return;
	}
	if(f<0)
	{
		lcd_data('-');
		f=-f;
	}
	i=f;
	lcd_atoi(i);
	i=(f-i)*100;
	lcd_data('.');
	lcd_atoi(i);


}



void cgram(void)
{
	unsigned char a[10]={0x10,0x18,0x1c,0x1e,0x1c,0x18,0x10,0x0}; //   >
	unsigned char b[10]={0x0,0x0,0x1f,0x1f,0x1f,0x0,0x0,0x0};	  //   -
	unsigned char c[10]={0x01,0x03,0x7,0xf,0x7,0x3,0x01,0x0};	  //   <
	//unsigned char H_ON[10]={0x15,0x00,0x04,0x0A,0x11,0x1f,0x00,0x1f};
	//unsigned char H_OFF[10]={0x00,0x00,0x04,0x0e,0x1f,0x1f,0x00,0x1f};
	unsigned char H_ON[10]={0x01,0x03,0x0f,0x0f,0xf,0x03,0x01,0x00};
	unsigned char H_OFF[10]={0x01,0x03,0x0d,0x09,0xd,0x03,0x01,0x00};
	unsigned char H_DASH[10]={0x1c,0x0,0x1c,0x0,0x1c,0x0,0x1c,0x0};
		  
	int i=0;
	lcd_cmd(0x40);
	for(i=0;i<8;i++)
		lcd_data(a[i]);  //   >	 pg 0
	lcd_cmd(0x48);
	for(i=0;i<8;i++)
		lcd_data(b[i]);	//   -	pg 1
	lcd_cmd(0x50);
	for(i=0;i<8;i++)
		lcd_data(c[i]);	//   <  pg 2
	lcd_cmd(0x58);
	for(i=0;i<8;i++)	  
		lcd_data(H_ON[i]);	//  ON pg 3
	lcd_cmd(0x60);
	for(i=0;i<8;i++)	  
		lcd_data(H_OFF[i]);	//  OFF pg 4
	lcd_cmd(0x68);
	for(i=0;i<8;i++)	  
		lcd_data(H_DASH[i]);	 //  __ pg 5
}












