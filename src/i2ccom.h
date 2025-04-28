
#include<xc.h>

#define ICLK PORTCbits.RC3
#define IDAT PORTCbits.RC4
#define TICLK TRISCbits.TRISC3
#define TIDAT TRISCbits.TRISC4


void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_wb(unsigned char val);
unsigned char i2c_rb(unsigned char ack);
void i2c_acktst(unsigned char val);
