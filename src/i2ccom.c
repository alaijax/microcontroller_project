
#if !defined(_18F4550) && !defined(_18F45K50)
#include "i2ccom.h"
#include "configpic.h"

void delay(void) {
    __delay_us(20);
}

void i2c_init(void) {
    TICLK = 0;
    TIDAT = 0;
    ICLK = 1;
    IDAT = 1;
}

void i2c_start(void) {
    delay();
    IDAT = 1;
    ICLK = 1;
    delay();
    IDAT = 0;
    delay();
}

void i2c_stop(void) {
    delay();
    IDAT = 0;
    ICLK = 1;
    delay();
    IDAT = 1;
    delay();
}

void i2c_wb(unsigned char val) {
    unsigned char i;
    ICLK = 0;
    delay();
    for (i = 0; i < 8; i++) {
        IDAT = ((val >> (7 - i))& 0x01);
        ICLK = 1;
        delay();
        ICLK = 0;
        delay();
    }
    TIDAT = 1;
    delay();
    ICLK = 1;
    //ACK
    delay();
    ICLK = 0;
    TIDAT = 0;
    IDAT = 1;
    delay();
}

unsigned char i2c_rb(unsigned char ack) {
    char i;
    unsigned char ret = 0;

    ICLK = 0;
    delay();
    TIDAT = 1;
    IDAT = 1;
    for (i = 0; i < 8; i++) {
        ICLK = 1;
        delay();
        ret |= (IDAT << (7 - i));
        ICLK = 0;
        delay();
    }
    TIDAT = 0;
    if (ack)
        IDAT = 0;
    else
        IDAT = 1;
    delay();
    ICLK = 1;
    delay();
    ICLK = 0;
    delay();
    return ret;
}



#endif


