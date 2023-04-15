#define TSL256x_address                                                              0x52

#define TSL256x_write_mode                                                TSL256x_address
#define TSL256x_read_mode                                                            0x53

#define control_reg                                                                  0x00
#define timing_reg                                                                   0x01
#define thresh_low_low_reg                                                           0x02
#define thresh_low_high_reg                                                          0x03
#define thresh_high_low_reg                                                          0x04
#define thresh_high_high_reg                                                         0x05
#define interrupt_reg                                                                0x06
#define CRC_reg                                                                      0x08
#define ID_reg                                                                       0x0A
#define data_0_low_reg                                                               0x0C
#define data_0_high_reg                                                              0x0D
#define data_1_low_reg                                                               0x0E
#define data_1_high_reg                                                              0x0F

#define TSL256x_CMD                                                                  0x80


sbit Soft_I2C_Scl_Output    at                                                PORTC5_bit;
sbit Soft_I2C_Sda_Output    at                                                PORTC4_bit;
sbit Soft_I2C_Scl_Input     at                                                 PINC5_bit;
sbit Soft_I2C_Sda_Input     at                                                 PINC4_bit;
sbit Soft_I2C_Scl_Direction at                                                  DDC5_bit;
sbit Soft_I2C_Sda_Direction at                                                  DDC4_bit;


void TSL256x_init();
unsigned char TSL256x_read_byte(unsigned char reg);
unsigned int TSL256x_read_word(unsigned char reg);
void TSL256x_write(unsigned char reg, unsigned char value);
unsigned long calculate_lux(unsigned int iGain, unsigned int tInt);