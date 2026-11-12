#include "head.h"
#include<stdio.h>

CAN1 r1;

int main()
{

	u32 adcout0,adcout1;
	u8 oxygen;
	float temp,vout,v2,t2;
	char s[50];
	can1_st();

	uart0_st(9600);

	uart0_tx_string("nodeB\r\n");

	while(1)
	{
		can1_rx(&r1);   //receive data/remote frame
		if(r1.rtr==0)
			{
			adcout0 = (r1.byteA&0x3ff);
			adcout1 = ((r1.byteA>>10)&0x3ff);
			 oxygen = ((r1.byteA>>20)&0xff);
			 uart0_tx_string("\r\n----------------------\r\n");
			 uart0_tx_string("ICU PATIENT DATA MONITOR\r\n");
			// sprintf(s,"value=%d %d %d\r\n",adcout0,adcout1,oxygen);
			 uart0_tx_string("\-----------------------\r\n");
			 uart0_tx_string("***** PATIENT DATA ******\r\n");

			  vout =(adcout0*3.3)/1023;
			  temp =-((vout-0.5)/0.01);
			  sprintf(s,"TEMPERATURE LEVEL : %.2f ^C \r\n",temp);
			  uart0_tx_string(s);

			  v2=(adcout0*3.3)/1023*100;
			  //t2=(v2-0.05)/0.1;
			  //sprintf(s,"LIGHT LEVEL : %.2f vout=%.2f\r\n",t2,v2);
			  sprintf(s,"LIGHT LEVEL : %.2f %%\r\n",v2);
			  uart0_tx_string(s);

			 sprintf(s,"OXYGEN LEVEL : %d %%\r\n",oxygen);
			 uart0_tx_string(s);
		
			}

		else 
			uart0_tx_string("remote-frame received\r\n");

	}

}