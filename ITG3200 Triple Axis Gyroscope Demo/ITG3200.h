/*       Device Addressing      */

#define ITG3200_Write                                                                    0xD0
#define ITG3200_Read                                                                     0xD1

/*                Registers                  */

#define ID_REG                                                                           0x00
#define SMPLRT_DIV_REG                                                                   0x15
#define DLPF_FS_REG                                                                      0x16
#define INT_CFG_REG                                                                      0x17
#define INT_STATUS_REG                                                                   0x1A
#define TEMP_OUT_H_REG                                                                   0x1B
#define TEMP_OUT_L_REG                                                                   0x1C
#define GYRO_XOUT_H_REG                                                                  0x1D
#define GYRO_XOUT_L_REG                                                                  0x1E
#define GYRO_YOUT_H_REG                                                                  0x1F
#define GYRO_YOUT_L_REG                                                                  0x20
#define GYRO_ZOUT_H_REG                                                                  0x21
#define GYRO_ZOUT_L_REG                                                                  0x22
#define PWR_MGM_REG                                                                      0x3E

/*               Bits                        */

//DLPF Bits

#define FS_SEL                                                                           0x18

#define LPF_256HZ                                                                        0x00
#define LPF_188Hz                                                                        0x01
#define LPF_98HZ                                                                         0x02
#define LPF_42Hz                                                                         0x03
#define LPF_20HZ                                                                         0x04
#define LPF_10Hz                                                                         0x05
#define LPF_5Hz                                                                          0x06

//Interrupt Configuration Bits

#define ACTL                                                                             0x80
#define OPEN                                                                             0x40
#define LATCH_INT_EN                                                                     0x20
#define INT_ANYRD_2CLEAR                                                                 0x10
#define ITG_RDY_EN                                                                       0x04
#define RAW_RDY_EN                                                                       0x01

//Interrupt Status Bits

#define ITG_RDY                                                                          0x04
#define RAW_DATA_RDY                                                                     0x01

//Power Management Bits

#define H_RESET                                                                          0x80
#define SLEEP                                                                            0x40
#define STBY_XG                                                                          0x20
#define STBY_YG                                                                          0x10
#define STBY_ZG                                                                          0x08

#define INTERNAL_OSCILLATOR                                                              0x00
#define PLL_WITH_X_GYRO_REFERENCE                                                        0x01
#define PLL_WITH_Y_GYRO_REFERENCE                                                        0x02
#define PLL_WITH_Z_GYRO_REFERENCE                                                        0x03
#define PLL_WITH__REFERENCE_LOW                                                          0x04
#define PLL_WITH__REFERENCE_HIGH                                                         0x05

#define degrees_per_second_sensitivity                                                   14.375


void ITG3200_init();
void ITG3200_write_byte(unsigned char address, unsigned char value);
void ITG3200_write_word(unsigned char address, unsigned int value);
unsigned char ITG3200_read_byte(unsigned char address);
unsigned int ITG3200_read_word(unsigned char address);
void get_raw_values(signed int *x_val, signed int *y_val, signed int *z_val);
void get_corrected_raw_values(signed int *x_val, signed int *y_val, signed int *z_val, signed int *x_off, signed int *y_off, signed int *z_off);
void get_deg_per_second(signed int *x_val, signed int *y_val, signed int *z_val, float scale);
signed int ITG3200_get_temperature();