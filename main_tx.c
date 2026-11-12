#include <LPC21xx.h>	

#include "header.h"
#include "max30102.h"
#include "spo2.h"

MAX30102_Data sensor;
s16 ir_filtered;
CAN1 v1;

int main(void)
{
	
	u32 temp,ldr;
	u8 oxygen;
    u8 count = 0;
	char s[50];
	float t1,l2;
	can1_st();
	adc_st();

    uart0_st(9600);

    i2c_st();

    delay_ms(100);

    uart0_tx_string("\r\n");

    uart0_tx_string("MAX30102 BPM & SpO2 TEST\r\n");

    MAX30102_st();

    SpO2_st();

 	v1.id=0x234;

	v1.rtr=0;//data-frame

	v1.dlc=4;

	v1.byteA=0;

	v1.byteB=0;

    while(1)
    {
        /* Read one sample */

        MAX30102_ReadFIFO(&sensor);
        SpO2_Process(sensor.red, sensor.ir);

        /* Print every 50 samples (~500ms at 100Hz) */
        count++;
       if(count >= 50)
        {

            count = 0;

            uart0_tx_string("----------------------\r\n");


            uart0_tx_string("RED=");

            uart0_integer(sensor.red);


            uart0_tx_string("\r\nIR=");

            uart0_integer(sensor.ir);


            uart0_tx_string("\r\nSpO2=");

            uart0_integer(Get_SpO2());


            uart0_tx_string("\r\n");

			
		temp = adc_read(0);     //read Ain0 temp
		    ldr  = adc_read(1);     //read Ain0 ldr
			
			temp = temp&0x3ff;
			ldr  = ldr&0x3ff;
			oxygen = Get_SpO2();
				

	v1.byteA=(temp|(ldr<<10)|(oxygen<<20));
	/*

		sprintf(s,"temp =%d ldr=%d \r\n",temp,ldr);

		uart0_tx_string(s);
		t1=(((float)temp*3.3)/1023)*100;
		sprintf(s,"temp=%.2f ",t1);
		uart0_tx_string(s);

		l2=((ldr*3.3)/1023);
		l2=(l2/3.3)*100;
		sprintf(s,"LDR=%.2f %%",l2);
		uart0_tx_string(s);
		uart0_tx_string("\r\n");
			*/
		can1_tx(v1);           //send data-frame
	  
        }
        /* Keep sampling at ~100Hz */
		delay_ms(100);
    }
}