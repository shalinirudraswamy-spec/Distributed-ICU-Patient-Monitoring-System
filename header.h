/* header.h */

#include <lpc21xx.h>

typedef unsigned int u32;
typedef unsigned char u8;

typedef struct can1_msg{
		u32 id;
		u32 bytea;
		u32 byteb;
		u8 rtr;
		u8 ff;
		u8 dlc;
		 
}CAN1;
void can1_init();
extern void can1_tx(CAN1 );
extern void can1_rx(CAN1 *);

void delay_ms(u32 );
void delay_sec(u32 );

void lcd_init(void);
void lcd_data(u8 );
void lcd_cmnd(u8 );
void lcd_string(char *);
void lcd_int(int );

void uart0_init(u32 );
void uart0_tx(u8 );
u8 uart0_rx();
void uart0_tx_string(char * );
void uart0_int(int );
void uart0_float(float );

void adc_init();
u32 adc_read(u32 );

