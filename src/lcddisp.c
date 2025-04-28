
#include <xc.h>
#include "configpic.h"
#include "lcddisp.h"
#include "atrasotime.h"

void lcd_init(void)
{
	LENA=0;
	LDAT=0;
	atraso_ms(15); //Reduced form 20 ms
	LENA=1;
	
	lcd_cmd(L_CFG);
	atraso_ms(1); //Reduced form 5 ms
	lcd_cmd(L_CFG);
        __delay_us(500); //Reduced form 1 ms
	lcd_cmd(L_CFG); //configura
	lcd_cmd(L_OFF);
	lcd_cmd(L_ON); //liga
	lcd_cmd(L_CLR); //limpa
	lcd_cmd(L_CFG); //configura
    lcd_cmd(L_L1);
}

void lcd_wr(unsigned char val)
{
    //WRITE TO THE LCD; LOW LEVEL INTERACTION
  LPORT=val;
}

void lcd_cmd(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=0;
        __delay_us(100); //Reduced form 3 ms
        LENA=0;
        __delay_us(100);
	LENA=1;
    LPORT = 0x00; // Reset PORTD to 0
}
 
void lcd_dat(unsigned char val)
{
	LENA=1; //Enables LCD or sets it to a state ready to receive data
        lcd_wr(val);
        LDAT=1; //DATA READY FOR PROCESSING
        __delay_us(100);
        LENA=0; //Trigger a "latch" or "commit" action on the LCD, signalling the 
                //end of the data transfer.
        __delay_us(100);
	LENA=1;
    LPORT = 0x00; // Reset PORTD to 0
}



void lcd_str(const char* str)
{
 unsigned char i=0;
  
 while(str[i] != 0 )
 {
   lcd_dat(str[i]);
   i++;
 }  
}

/*void shift_out(unsigned char data) {
    for (int i = 0; i < 8; i++) {
        PORTEbits.RE0 = (data >> i) & 1; // Data pin
        LENA = 1; // Clock pulse
        LENA = 0;
    }
    LDAT = 1; // Latch data
    LDAT = 0;
}*/






 
