
#include <xc.h>
#include "adcmod.h"
#include "configpic.h"

void adc_init(void)
{
#if defined (_18F452) || defined(_16F877A)
  ADCON1=0x02; 
  ADCON0=0x41;
#elif defined(_18F47K40)
  ADCON0=0x80;
#else
  ADCON0=0x01;
  ADCON1=0x0B;
  ADCON2=0x01;
#endif
  
 

}

unsigned int adc_amostra(unsigned char canal)
{

#ifdef    _18F47K40
      ADPCH=canal;
#else    
    ADCON0bits.CHS=canal;
#endif
    __delay_us(20);
    
    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}
