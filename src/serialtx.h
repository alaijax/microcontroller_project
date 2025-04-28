
void serial_init();//default 9600
void serial_end();
void serial_tx(unsigned char val);
void serial_tx_str(const char* val);
unsigned char serial_rx(unsigned int timeout);  /*timeout=0 no time out*/ 
