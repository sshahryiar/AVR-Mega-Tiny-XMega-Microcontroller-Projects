#define L3G4200_Addr                                                                     0xD2

#define L3G4200_write_cmd                                                                0xD2
#define L3G4200_read_cmd                                                                 0xD3

#define CTRL_REG1                                                                        0x20
#define CTRL_REG2                                                                        0x21
#define CTRL_REG3                                                                        0x22
#define CTRL_REG4                                                                        0x23
#define CTRL_REG5                                                                        0x24
#define REFERENCE                                                                        0x25
#define OUT_TEMP                                                                         0x26
#define STATUS_REG                                                                       0x27
#define OUT_X_L                                                                          0xA8
#define OUT_X_H                                                                          0x29
#define OUT_Y_L                                                                          0x2A
#define OUT_Y_H                                                                          0x2B
#define OUT_Z_L                                                                          0x2C
#define OUT_Z_H                                                                          0x2D
#define FIFO_CTRL_REG                                                                    0x2E
#define FIFO_SRC_REG                                                                     0x2F
#define INT1_CFG                                                                         0x30
#define INT1_SRC                                                                         0x31
#define INT1_TSH_XH                                                                      0x32
#define INT1_TSH_XL                                                                      0x33
#define INT1_TSH_YH                                                                      0x34
#define INT1_TSH_YL                                                                      0x35
#define INT1_TSH_ZH                                                                      0x36
#define INT1_TSH_ZL                                                                      0x37
#define INT1_DURATION                                                                    0x38

#define FS250                                                                            0.00875
#define FS500                                                                            0.0175
#define FS2000                                                                           0.07


void L3G4200_init();
void L3G4200_write_byte(unsigned char address, unsigned char value);
void L3G4200_write_word(unsigned char address, unsigned int value);
unsigned char L3G4200_read_byte(unsigned char address);
unsigned int L3G4200_read_word(unsigned char address);
signed char L3G4200_get_raw_temperature();
signed char L3G4200_get_temperature();
void L3G4200_get_raw_data(signed int *x_val, signed int *y_val, signed int *z_val);
void L3G4200_degrees_per_second(signed int *x_val, signed int *y_val, signed int *z_val, float scale);