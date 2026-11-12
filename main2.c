#include"header.h"

can1 v;
int main()
{
	float ldr=0,temp=0;
	int i;
	i2c_init();
	can1_st();
	adc_st();	
	uart0_st(9600);
	while(3)
	{  	
		  temp=tempu(0);
		//  ldr=tempu(0);
		  ldr=adc_read(2);
		 // ldr=(ldr/1023)*100;
		//  uart0_integer(ldr);
		 // uart0_tx_string("\r\n");
		//  uart0_integer(temp);


		  v.id=21;
		  v.byteA=temp;
		  v.byteB=ldr;
		  v.rtr=0;
		  v.dlc=8;
		  v.ff=0;
		  can1_tx(v);
		 // uart0_tx_string("nice");
		 delay_ms(300);

	}



}