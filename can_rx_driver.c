#include <LPC21xx.H>

#include "head.h"


void can1_st(void){

	VPBDIV=1;//pclk=60MHz

	PINSEL1|=0x00040000;//P0.25--> RD1

	C1MOD=1;//select reset mode

	AFMR=2;//accept all receiving msgs

	C1BTR=0x001C001D;//baudrate=125Kbps

	C1MOD=0;//release reset mode

}


#define RBS (C1GSR&1)

void can1_rx(CAN1 *ptr){

	while(RBS==0);//waiting for msg to receive

	ptr->id=C1RID;//store id

	ptr->dlc=(C1RFS>>16)&0xF;//extract & stotr dlc

	ptr->rtr=(C1RFS>>30)&1;//extract & store rtr

	ptr->ff=(C1RFS>>31)&1;//extract & store ide/ff

	if(ptr->rtr==0){//if data-frame

		ptr->byteA=C1RDA;

		ptr->byteB=C1RDB;

	}

	

	C1CMR=0x4;//release rxbuf*

}




#define TCS ((C1GSR>>3)&1)

void can1_tx(CAN1 v){

	C1TID1=v.id;

	C1TFI1=(v.dlc<<16);//set dlc, rtr=0, ff=0

	if(v.rtr==0){//if data-frame

		C1TDA1=v.byteA;

		C1TDB1=v.byteB;

	}

	else //if remote-frame

		C1TFI1|=(1<<30);//rtr=1

	

	C1CMR=0x21;//select txbuf1 & start xmission

	while(TCS==0);

}
