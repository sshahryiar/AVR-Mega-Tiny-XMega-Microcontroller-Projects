#define BMP180_Address                                                          0xEE

#define AC1_reg                                                                 0xAA
#define AC2_reg                                                                 0xAC
#define AC3_reg                                                                 0xAE
#define AC4_reg                                                                 0xB0
#define AC5_reg                                                                 0xB2
#define AC6_reg                                                                 0xB4
#define B1_reg                                                                  0xB6
#define B2_reg                                                                  0xB8
#define MB_reg                                                                  0xBA
#define MC_reg                                                                  0xBC
#define MD_reg                                                                  0xBE
#define control_reg                                                             0xF4
#define MSB                                                                     0xF6
#define LSB                                                                     0xF7
#define XLSB                                                                    0xF8
#define OSS_value                                                               0x03
#define temp_conv_cmd                                                           0x2E

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


void BMP180_init();
signed char BMP180_read_byte(unsigned char address);
signed int BMP180_read_word(unsigned char address);
void BMP180_write(unsigned char address, unsigned char value);
void BMP180_Calibration();
unsigned int read_uncompensated_temperature();
unsigned long read_uncompensated_pressure(unsigned char OSS);
float get_temperature(unsigned int UT);
signed long get_pressure(unsigned long UP, unsigned char OSS);