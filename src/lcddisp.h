
#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE2
#define LPORT PORTD


#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_CR	0x0F		
#define L_NCR	0x0C	
#define L_HOM   0x02
#define L_CFG   0x38
#define L_LEF   0x04
#define L_RIT   0x06
#define L_DIR   0x05
#define L_DIL   0x07
#define L_OFC   0x0A
#define L_OFN   0x0C
#define L_OCR   0x0E
#define L_CLE   0x10
#define L_CRI   0x14
#define L_DLE   0x18
#define L_DRI   0x1C
  

void lcd_init(void);
void lcd_cmd(unsigned char val); 
void lcd_dat(unsigned char val);
void lcd_str(const char* str);

