#define AT24C32_addr                       0xA0
#define AT24C32_WR                         AT24C32_addr
#define AT24C32_RD                         0xA1

#define bytes_per_page                     0x20


unsigned char buffer[bytes_per_page];


unsigned char get_low_byte(signed int address);
unsigned char get_high_byte(signed int address);
unsigned char AT24C32_read(unsigned int address);
void AT24C32_byte_write(unsigned int address, unsigned char value);
void AT24C32_page_write(unsigned int address);