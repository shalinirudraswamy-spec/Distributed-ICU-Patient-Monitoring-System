#include<lpc21xx.h>
#include"header.h"

void adc_st(void)
{
	PINSEL1|=0x15400000;
	ADCR=0x00201300;
}
u32 adc_read(u8 ch_num)
{
	u32 temp;
	ADCR|=1<<ch_num;
	ADCR|=1<<24;
	while(uart0_tx(' '),DONE==0);
	ADCR^=1<<ch_num;
	ADCR^=1<<24;
	temp=(ADDR>>6)&0x3ff;
	return temp;
}

