#include"header.h"

void i2c_st(void)
{
	PINSEL0|=0x50;
	I2CONSET=1<<6;
	I2SCLL=I2SCLH=75;
}

void i2c_tx(u8 sa,u8 mr_addr,u8 data)
{
	I2CONSET=1<<5;
	I2CONCLR=1<<3;
	while(SI==0);
	I2CONCLR=1<<5;

	I2DAT=sa;
	I2CONCLR=1<<3;
	while(SI==0);
	if(I2STAT==0x20)
	{
		uart0_tx_string("ERROR : SA+W\r\n");
		goto exit;
	}

	I2DAT=mr_addr;
	I2CONCLR=1<<3;
	while(SI==0);
	if(I2STAT==0x30)
	{
		uart0_tx_string("ERROR : mr_addr\r\n");
		goto exit;
	}

	I2DAT=data;
	I2CONCLR=1<<3;
	while(SI==0);
	if(I2STAT==0x30)
	{
		uart0_tx_string("ERROR : data\r\n");
		goto exit;
	}

	exit: I2CONSET=1<<4;
		  I2CONCLR=1<<3;
}
u8 i2c_rx(u8 sa,u8 mr_addr)
{
	u8 temp=0;
	I2CONSET=1<<5;
	I2CONCLR=1<<3;
	while(SI==0);
	I2CONCLR=1<<5;

	I2DAT=sa&0xfe;
	I2CONCLR=1<<3;
	while(SI==0);
	if(I2STAT==0x20)
	{
		uart0_tx_string("ERROR : SA+W\r\n");
		goto exit;
	}

	I2DAT=mr_addr;
	I2CONCLR=1<<3;
	while(SI==0);
	if(I2STAT==0x30)
	{
		uart0_tx_string("ERROR : mr_addr\r\n");
		goto exit;
	}
	I2CONSET=1<<5;
	I2CONCLR=1<<3;
	while(SI==0);
	I2CONCLR=1<<5;

	I2DAT=sa;
	I2CONCLR=1<<3;
	while(SI==0);
	if(I2STAT==0x48)
	{
		uart0_tx_string("ERROR : SA+R\r\n");
		goto exit;
	}


	I2CONCLR=1<<3;
	while(SI==0);
	temp=I2DAT;
	

	exit: I2CONSET=1<<4;
		  I2CONCLR=1<<3;
		  return temp;
}
