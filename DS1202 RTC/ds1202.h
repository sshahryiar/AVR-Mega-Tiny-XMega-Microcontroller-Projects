#define bit_set(reg, bit_val)                           reg |= (1 << bit_val)
#define bit_clr(reg, bit_val)                           reg &= (~(1 << bit_val))
#define bit_tgl(reg, bit_val)                           reg ^= (1 << bit_val)
#define get_bit(reg, bit_val)                           (reg & (1 << bit_val))
#define get_reg(reg, msk)                               (reg & msk)

#define RST_pin                                         0
#define SCK_pin                                         1
#define IO_pin                                          2

#define RST_dir_in                                      bit_clr(DDRB, RST_pin)
#define SCK_dir_in                                      bit_clr(DDRB, SCK_pin)
#define IO_dir_in                                       bit_clr(DDRB, IO_pin)

#define RST_dir_out                                     bit_set(DDRB, RST_pin)
#define SCK_dir_out                                     bit_set(DDRB, SCK_pin)
#define IO_dir_out                                      bit_set(DDRB, IO_pin)

#define RST_out_high                                    bit_set(PORTB, RST_pin)
#define SCK_out_high                                    bit_set(PORTB, SCK_pin)
#define IO_out_high                                     bit_set(PORTB, IO_pin)

#define RST_out_low                                     bit_clr(PORTB, RST_pin)
#define SCK_out_low                                     bit_clr(PORTB, SCK_pin)
#define IO_out_low                                      bit_clr(PORTB, IO_pin)

#define IO_in                                           get_bit(PINB, IO_pin)

#define sec_wreg                                        0x80
#define sec_rreg                                        0x81
#define min_wreg                                        0x82
#define min_rreg                                        0x83
#define hr_wreg                                         0x84
#define hr_rreg                                         0x85
#define date_wreg                                       0x86
#define date_rreg                                       0x87
#define month_wreg                                      0x88
#define month_rreg                                      0x89
#define dow_wreg                                        0x8A
#define dow_rreg                                        0x8B
#define year_wreg                                       0x8C
#define year_rreg                                       0x8D
#define control_wreg                                    0x8E
#define control_rreg                                    0x8F
#define clk_burst_wreg                                  0xBE
#define clk_burst_rreg                                  0xBF
                         
#define ramlocstartr                                    0xC1
#define ramlocendr                                      0xEF

#define ramlocstartw                                    0xC0
#define ramlocendw                                      0xEE
                                 
           
unsigned char bcd_to_decimal(unsigned char value);
unsigned char decimal_to_bcd(unsigned char value);
void DS1202_GPIO_init(void);
void DS1202_init(void); 
void DS1202_serial_write(unsigned char value);
unsigned char DS1202_serial_read(void);
void DS1202_write(unsigned char addr, unsigned char value);                     
unsigned char DS1202_read(unsigned char addr);   
unsigned char DS1202_read_RAM(unsigned char addr);
void DS1202_write_RAM(unsigned char addr, unsigned char value);
void DS1202_get_time(void);
void DS1202_get_date(void);
void DS1202_get_time_and_date(void);
void DS1202_set_time(unsigned char p1, unsigned char p2, unsigned char p3);
void DS1202_set_date(unsigned char p1, unsigned char p2, unsigned char p3, unsigned char p4);