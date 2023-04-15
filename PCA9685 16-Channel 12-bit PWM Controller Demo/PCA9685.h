#define PCA9685_address                                                                  0x80

#define PCA9685_write_cmd                                                                PCA9685_address
#define PCA9685_read_cmd                                                                 (PCA9685_address + 1)

#define PCA9685_software_reset                                                           0x06

#define PCA9685_MODE1_reg                                                                0x00
#define PCA9685_MODE2_reg                                                                0x01
#define PCA9685_SUBADR1_reg                                                              0x02
#define PCA9685_SUBADR2_reg                                                              0x03
#define PCA9685_SUBADR3_reg                                                              0x04
#define PCA9685_ALLCALLADR_reg                                                           0x05
#define PCA9685_PRE_SCALE_reg                                                            0xFE
#define PCA9685_TEST_MODE_reg                                                            0xFF

#define PCA9685_CH0_ON_L_reg                                                             0x06
#define PCA9685_CH0_ON_H_reg                                                             0x07
#define PCA9685_CH0_OFF_L_reg                                                            0x08
#define PCA9685_CH0_OFF_H_reg                                                            0x09

#define PCA9685_CH1_ON_L_reg                                                             0x0A
#define PCA9685_CH1_ON_H_reg                                                             0x0B
#define PCA9685_CH1_OFF_L_reg                                                            0x0C
#define PCA9685_CH1_OFF_H_reg                                                            0x0D

#define PCA9685_CH2_ON_L_reg                                                             0x0E
#define PCA9685_CH2_ON_H_reg                                                             0x0F
#define PCA9685_CH2_OFF_L_reg                                                            0x10
#define PCA9685_CH2_OFF_H_reg                                                            0x11

#define PCA9685_CH3_ON_L_reg                                                             0x12
#define PCA9685_CH3_ON_H_reg                                                             0x13
#define PCA9685_CH3_OFF_L_reg                                                            0x14
#define PCA9685_CH3_OFF_H_reg                                                            0x15

#define PCA9685_CH4_ON_L_reg                                                             0x16
#define PCA9685_CH4_ON_H_reg                                                             0x17
#define PCA9685_CH4_OFF_L_reg                                                            0x18
#define PCA9685_CH4_OFF_H_reg                                                            0x19

#define PCA9685_CH5_ON_L_reg                                                             0x1A
#define PCA9685_CH5_ON_H_reg                                                             0x1B
#define PCA9685_CH5_OFF_L_reg                                                            0x1C
#define PCA9685_CH5_OFF_H_reg                                                            0x1D

#define PCA9685_CH6_ON_L_reg                                                             0x1E
#define PCA9685_CH6_ON_H_reg                                                             0x1F
#define PCA9685_CH6_OFF_L_reg                                                            0x20
#define PCA9685_CH6_OFF_H_reg                                                            0x21

#define PCA9685_CH7_ON_L_reg                                                             0x22
#define PCA9685_CH7_ON_H_reg                                                             0x23
#define PCA9685_CH7_OFF_L_reg                                                            0x24
#define PCA9685_CH7_OFF_H_reg                                                            0x25

#define PCA9685_CH8_ON_L_reg                                                             0x26
#define PCA9685_CH8_ON_H_reg                                                             0x27
#define PCA9685_CH8_OFF_L_reg                                                            0x28
#define PCA9685_CH8_OFF_H_reg                                                            0x29

#define PCA9685_CH9_ON_L_reg                                                             0x2A
#define PCA9685_CH9_ON_H_reg                                                             0x2B
#define PCA9685_CH9_OFF_L_reg                                                            0x2C
#define PCA9685_CH9_OFF_H_reg                                                            0x2D

#define PCA9685_CH10_ON_L_reg                                                            0x2E
#define PCA9685_CH10_ON_H_reg                                                            0x2F
#define PCA9685_CH10_OFF_L_reg                                                           0x30
#define PCA9685_CH10_OFF_H_reg                                                           0x31

#define PCA9685_CH11_ON_L_reg                                                            0x32
#define PCA9685_CH11_ON_H_reg                                                            0x33
#define PCA9685_CH11_OFF_L_reg                                                           0x34
#define PCA9685_CH11_OFF_H_reg                                                           0x35

#define PCA9685_CH12_ON_L_reg                                                            0x36
#define PCA9685_CH12_ON_H_reg                                                            0x37
#define PCA9685_CH12_OFF_L_reg                                                           0x38
#define PCA9685_CH12_OFF_H_reg                                                           0x39

#define PCA9685_CH13_ON_L_reg                                                            0x3A
#define PCA9685_CH13_ON_H_reg                                                            0x3B
#define PCA9685_CH13_OFF_L_reg                                                           0x3C
#define PCA9685_CH13_OFF_H_reg                                                           0x3D

#define PCA9685_CH14_ON_L_reg                                                            0x3E
#define PCA9685_CH14_ON_H_reg                                                            0x3F
#define PCA9685_CH14_OFF_L_reg                                                           0x40
#define PCA9685_CH14_OFF_H_reg                                                           0x41

#define PCA9685_CH15_ON_L_reg                                                            0x42
#define PCA9685_CH15_ON_H_reg                                                            0x43
#define PCA9685_CH15_OFF_L_reg                                                           0x44
#define PCA9685_CH15_OFF_H_reg                                                           0x45

#define PCA9685_ALL_CH_ON_L_reg                                                          0xFA
#define PCA9685_ALL_CH_ON_H_reg                                                          0xFB
#define PCA9685_ALL_CH_OFF_L_reg                                                         0xFC
#define PCA9685_ALL_CH_OFF_H_reg                                                         0xFD

#define MAX_count                                                                        4096


void PCA9685_init();
void PCA9685_soft_reset();
unsigned char PCA9685_read_byte(unsigned char address);
void PCA9685_write_byte(unsigned char address, unsigned char value);
void PCA9685_write_word(unsigned char address, unsigned int word_value);
void PCA9685_set_PWM_duty(unsigned char ch, unsigned int duty, unsigned int dead_time);