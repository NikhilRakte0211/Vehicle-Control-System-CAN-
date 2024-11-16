#include "header.h"
void adc_init(void)
{
	PINSEL1|=0x15400000;		 //p0.27 to p0.31 setting  as analog pins
	ADCR=0x00200400;		//no channel selected ,then 4 is to set frequency as 3 mhz,16th bit to burst off,
							//10 bits for resolution, 2 for channel power down mode,then adc stop
}
#define DONE ((ADDR>>31)&1)
u32 adc_read(u8 channel_num)
{
	u32 result;
	ADCR|=(1<<channel_num);	// to set the channel num
	ADCR|=1<<24;			//to start the acd conversion
	while(DONE==0);		// to monitor the flag
	ADCR^=1<<24;     	//to stop adc conversion
	ADCR^=(1<<channel_num);  //To deselect channel
	result=(ADDR>>6)&0x3ff;  //extract 10 bits result
	return result;
}



