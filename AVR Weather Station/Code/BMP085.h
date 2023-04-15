#define BMP085_Address                                                                   0xEE

#define AC1_reg                                                                          0xAA
#define AC2_reg                                                                          0xAC
#define AC3_reg                                                                          0xAE
#define AC4_reg                                                                          0xB0
#define AC5_reg                                                                          0xB2
#define AC6_reg                                                                          0xB4
#define B1_reg                                                                           0xB6
#define B2_reg                                                                           0xB8
#define MB_reg                                                                           0xBA
#define MC_reg                                                                           0xBC
#define MD_reg                                                                           0xBE
#define control_reg                                                                      0xF4
#define MSB                                                                              0xF6
#define LSB                                                                              0xF7
#define XLSB                                                                             0xF8
#define temp_conv_cmd                                                                    0x2E

#define std_atm_pressure_at_sea_lvl                                                      101325.0
#define const1                                                                           5.255
#define const2                                                                           44330.0
#define const3                                                                           0.19029

#define EOC_pin                                                                          PINB0_bit
#define XCLR_pin                                                                         PORTB1_bit

enum {clear = 1, cloudy, rain};


signed int _b1 = 0;
signed int _b2 = 0;
signed int mb = 0;
signed int mc = 0;
signed int md = 0;
signed int ac1 = 0;
signed int ac2 = 0;
signed int ac3 = 0;

unsigned int ac4 = 0;
unsigned int ac5 = 0;
unsigned int ac6 = 0;

signed long _b5 = 0;


void BMP085_init();
signed char BMP085_read_byte(unsigned char address);
signed int BMP085_read_word(unsigned char address);
void BMP085_write(unsigned char address, unsigned char value);
void BMP085_Calibration();
unsigned int BMP085_read_uncompensated_temperature();
unsigned long BMP085_read_uncompensated_pressure(unsigned char OSS);
float  BMP085_get_temperature(unsigned int UT);
signed long BMP085_get_pressure(unsigned long UP, unsigned char OSS);
float BMP085_get_pressure_in_kPa();
float BMP085_get_temp();