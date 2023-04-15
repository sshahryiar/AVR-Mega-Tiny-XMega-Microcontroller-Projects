/*       Device Addressing      */

#define ADXL345_Write                                                                    0xA6
#define ADXL345_Read                                                                     0xA7


/*      Register names      */

#define ADXL345_DEVID                                                                    0x00
#define ADXL345_RESERVED1                                                                0x01
#define ADXL345_THRESH_TAP                                                               0x1D
#define ADXL345_OFSX                                                                     0x1E
#define ADXL345_OFSY                                                                     0x1F
#define ADXL345_OFSZ                                                                     0x20
#define ADXL345_DUR                                                                      0x21
#define ADXL345_LATENT                                                                   0x22
#define ADXL345_WINDOW                                                                   0x23
#define ADXL345_THRESH_ACT                                                               0x24
#define ADXL345_THRESH_INACT                                                             0x25
#define ADXL345_TIME_INACT                                                               0x26
#define ADXL345_ACT_INACT_CTL                                                            0x27
#define ADXL345_THRESH_FF                                                                0x28
#define ADXL345_TIME_FF                                                                  0x29
#define ADXL345_TAP_AXES                                                                 0x2A
#define ADXL345_ACT_TAP_STATUS                                                           0x2B
#define ADXL345_BW_RATE                                                                  0x2C
#define ADXL345_POWER_CTL                                                                0x2D
#define ADXL345_INT_ENABLE                                                               0x2E
#define ADXL345_INT_MAP                                                                  0x2F
#define ADXL345_INT_SOURCE                                                               0x30
#define ADXL345_DATA_FORMAT                                                              0x31
#define ADXL345_DATAX0                                                                   0x32
#define ADXL345_DATAX1                                                                   0x33
#define ADXL345_DATAY0                                                                   0x34
#define ADXL345_DATAY1                                                                   0x35
#define ADXL345_DATAZ0                                                                   0x36
#define ADXL345_DATAZ1                                                                   0x37
#define ADXL345_FIFO_CTL                                                                 0x38
#define ADXL345_FIFO_STATUS                                                              0x39

#define ADXL345_BW_1600                                                                  0x0F
#define ADXL345_BW_800                                                                   0x0E
#define ADXL345_BW_400                                                                   0x0D
#define ADXL345_BW_200                                                                   0x0C
#define ADXL345_BW_100                                                                   0x0B
#define ADXL345_BW_50                                                                    0x0A
#define ADXL345_BW_25                                                                    0x09
#define ADXL345_BW_12_5                                                                  0x08
#define ADXL345_BW_6_25                                                                  0x07
#define ADXL345_BW_3_13                                                                  0x06
#define ADXL345_BW_1_56                                                                  0x05
#define ADXL345_BW_0_78                                                                  0x04
#define ADXL345_BW_0_39                                                                  0x03
#define ADXL345_BW_0_20                                                                  0x02
#define ADXL345_BW_0_10                                                                  0x01
#define ADXL345_BW_0_05                                                                  0x00

/*      Interrupt pins      */
//             INT1: 0
//             INT2: 1

#define ADXL345_INT1_PIN                                                                 0x00
#define ADXL345_INT2_PIN                                                                 0x01

/*       Interrupt bit position       */

#define ADXL345_INT_DATA_READY_BIT                                                       0x07
#define ADXL345_INT_SINGLE_TAP_BIT                                                       0x06
#define ADXL345_INT_DOUBLE_TAP_BIT                                                       0x05
#define ADXL345_INT_ACTIVITY_BIT                                                         0x04
#define ADXL345_INT_INACTIVITY_BIT                                                       0x03
#define ADXL345_INT_FREE_FALL_BIT                                                        0x02
#define ADXL345_INT_WATERMARK_BIT                                                        0x01
#define ADXL345_INT_OVERRUNY_BIT                                                         0x00

#define ADXL345_DATA_READY                                                               0x07
#define ADXL345_SINGLE_TAP                                                               0x06
#define ADXL345_DOUBLE_TAP                                                               0x05
#define ADXL345_ACTIVITY                                                                 0x04
#define ADXL345_INACTIVITY                                                               0x03
#define ADXL345_FREE_FALL                                                                0x02
#define ADXL345_WATERMARK                                                                0x01
#define ADXL345_OVERRUN                                                                  0x00

/*      G Sensitivity      */

#define _2g                                                                              0x00
#define _4g                                                                              0x01
#define _8g                                                                              0x02
#define _16g                                                                             0x03

#define FULL_RESOLUTION                                                                  0x08
#define JUSTIFY                                                                          0x04


void ADXL345_init();
void ADXL345_write_byte(unsigned char address, unsigned char value);
void ADXL345_write_word(unsigned char address, unsigned int value);
unsigned char ADXL345_read_byte(unsigned char address);
unsigned int ADXL345_read_word(unsigned char address);
void power_sequence();
void set_sensitivity(unsigned char value);
void set_bandwidth(unsigned char value);
void get_values(signed int *x_val, signed int *y_val, signed int *z_val, float scale);
void get_offsets(signed int *x_val, signed int *y_val, signed int *z_val);
void set_offsets(signed int *x_val, signed int *y_val, signed int *z_val);