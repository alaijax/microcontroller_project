/*
 * File:   newmain.c
 * Author: Arhaan Ali
 * Student ID: 20378035
 * Module Code: 4ELEN007W
 * 
 * 
 * Created on 23 April 2025, 22:51
 */
    

    #include <xc.h>
    #include <stdio.h>  // Add this for sprintf()    
    #include "configpic.h"
    #include "lcddisp.h"
    #include "atrasotime.h"
    #include "adcmod.h"
    #include "itoaval.h" 
    #include "i2ccom.h"
    #include "serialtx.h"
    #include <math.h>   //Add this for log()   
    #define print_msg(x)  lcd_str(x);serial_tx_str(x);serial_tx_str("\r\n");
    // CONFIG
    #pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
    #pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
    #pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
    #pragma config BOREN = OFF       // Brown-out Reset Enable bit (BOR enabled)
    #pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
    #pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
    #pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
    #pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

    // #pragma config statements should precede project file includes.
    // Use project enums instead of #define for ON and OFF.
 
    /// Thermistor parameters (10k NTC)
    #define SERIES_RESISTOR  10000  // 10k ohm series resistor
    #define NOMINAL_RESISTANCE 10000
    #define NOMINAL_TEMP     25     // 25°C
    #define B_COEFFICIENT    3950   // B value

    void read_and_display(unsigned char channel);
    float read_temperature(unsigned int adc_value);

    void main(void) {
        TRISA = 0xD3;
        TRISB = 0x3F; // Set RB0-RB5 as inputs
        TRISD = 0x00; // PORTD as output (LCD data)
        TRISE = 0x00; // PORTE as output (LCD control)
               
        lcd_init();
        lcd_cmd(L_NCR);
      
        i2c_init();
        adc_init();
        PORTA = 0xFF;
        serial_init();
        LPORT = 0;
        
        ADCON1 = 0;

        while(1) {
            unsigned char portb_val = PORTB;

            // Check if any of RB2-RB5 are pressed (active-low)
            if ((portb_val & 0x3C) != 0x3C || (PORTAbits.RA5 == 0)){
                lcd_cmd(L_CLR);
                lcd_str("ERROR");
                serial_tx_str("ERROR\r\n");
            } 
            else {
                if (PORTBbits.RB0 == 0) { // Select channel 0 (sensor1)
                    lcd_cmd(L_CLR);
                    lcd_cmd(L_L1);
                    print_msg("SENSOR 1:")                    
                    read_and_display(0);
                } 
                else if (PORTBbits.RB1 == 0) { // Select channel 1 (sensor2)
                    lcd_cmd(L_CLR);
                    lcd_cmd(L_L1);
                    print_msg("SENSOR 2:")                    
                    read_and_display(1);
                } 
            }
            atraso_ms(100); // Debounce and update delay
        }
    }
    
     float read_temperature(unsigned int adc_value) {
        float voltage = (adc_value * 5.0) / 1023.0;
        float resistance = SERIES_RESISTOR * (5.0 / voltage - 1.0);

        // Steinhart-Hart equation
        float steinhart;
        steinhart = resistance / NOMINAL_RESISTANCE;    // (R/Ro)
        steinhart = log(steinhart);                     // ln(R/Ro)
        steinhart /= B_COEFFICIENT;                     // 1/B * ln(R/Ro)
        steinhart += 1.0 / (NOMINAL_TEMP + 273.15);     // + (1/To)
        steinhart = 1.0 / steinhart;                    // Invert
        steinhart -= 273.15;                            // Convert to Celsius

        return steinhart;
    }

    void read_and_display(unsigned char channel) {
        unsigned int adc_value = adc_amostra(channel);
        float temperature = read_temperature(adc_value);
        float voltage = (adc_value * 5.0) / 1023.0;

        char buffer[17];
        sprintf(buffer, "V:%.2fV T:%.1fC", voltage, temperature);
        
        lcd_cmd(L_L2);
        print_msg(buffer);
    }   
      