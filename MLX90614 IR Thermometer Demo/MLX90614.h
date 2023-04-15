#define MLX90614_I2C_ADDR                             0xB4

#define MLX90614_RAWIR1                               0x04
#define MLX90614_RAWIR2                               0x05
#define MLX90614_TA                                   0x06
#define MLX90614_TOBJ1                                0x07
#define MLX90614_TOBJ2                                0x08

#define MLX90614_TOMAX                                0x20
#define MLX90614_TOMIN                                0x21
#define MLX90614_PWMCTRL                              0x22
#define MLX90614_TARANGE                              0x23
#define MLX90614_EMISS                                0x24
#define MLX90614_CONFIG                               0x25
#define MLX90614_ADDR                                 0x0E
#define MLX90614_ID1                                  0x3C
#define MLX90614_ID2                                  0x3D
#define MLX90614_ID3                                  0x3E
#define MLX90614_ID4                                  0x3F

#define MLX90614_PEC_for_ROM_erase                    0x6F
#define MLX90614_PEC_for_ROM_write                    0xE1
#define MLX90614_PEC_for_sleep_mode                   0xF3

#define slope                                         0.02
#define _0C_in_K                                      273.0
#define Temp_count_Max                                32650

#define unit_Kelvin                                   0
#define unit_Celcius                                  1
#define unit_Fahrenheit                               2

#define C_to_F(value)                                 ((value * 1.8) + 32)


sbit Soft_I2C_Scl_Output    at PORTC1_bit;
sbit Soft_I2C_Sda_Output    at PORTC0_bit;

sbit Soft_I2C_Scl_Input     at PINC1_bit;
sbit Soft_I2C_Sda_Input     at PINC0_bit;

sbit Soft_I2C_Scl_Direction at DDC1_bit;
sbit Soft_I2C_Sda_Direction at DDC0_bit;


void MLX90614_init();
void MLX90614_enter_sleep_mode(unsigned char device_address);
unsigned int MLX90614_read(unsigned char device_address, unsigned char location);
void MLX90614_write_ROM(unsigned char device_address, unsigned char location, unsigned int value, unsigned char PEC);
void MLX90614_erase_ROM(unsigned char device_address, unsigned char location, unsigned int value);
float MLX90614_get_temperature(unsigned int value, unsigned char unit);