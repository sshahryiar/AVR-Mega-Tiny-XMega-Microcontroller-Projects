#define SDA_Direction                           DDC4_bit
#define SCL_Direction                           DDC3_bit
#define SDA_In_Pin                              PINC4_bit
#define SDA_Out_Pin                             PORTC4_bit
#define SCL_Pin                                 PORTC3_bit

#define HIGH                                    1
#define LOW                                     0

#define OUTPUT                                  1
#define INPUT                                   0

#define SHT1x_address                           0x00

#define measure_T_cmd                           0x03
#define measure_RH_cmd                          0x05
#define write_status_reg_cmd                    0x06
#define read_status_reg_cmd                     0x07
#define soft_reset_cmd                          0x1E

#define no_LVD                                  0x00
#define LVD                                     0x40
#define LVD_status                              0x40

#define heater_on                               0x04
#define heater_off                              0x00
#define heater_status                           0x04

#define OPT_reload                              0x02
#define no_OPT_reload                           0x00

#define low_resolution                          0x01
#define high_resolution                         0x00

#define T1                                      0.01              // for 14 Bit
#define T2                                   0.00008              // for 14 Bit
#define C1                                      -4.0              // for 12 Bit
#define C2                                    0.0405              // for 12 Bit
#define C3                                -0.0000028              // for 12 Bit
#define NACK                                       0
#define ACK                                        1


unsigned char SHT1x_Error = 0x00;

unsigned int SHT1x_T = 0x0000;
unsigned int SHT1x_H = 0x0000;


void SHT1x_init(void);
void SHT1x_start(void);
unsigned char SHT1x_read_byte(unsigned char acknowledgement);
unsigned char SHT1x_write_byte(unsigned char value);
unsigned char SHT1x_measure(unsigned int *p_value, unsigned char mode);
float SHT1x_calc_temperature(unsigned int t);
float SHT1x_calc_humidity(unsigned int h, unsigned int t);
float SHT1x_get_dew_point(float s_t, float s_rh);
void Read_SHT1x(float *fT, float *fRH);
signed char SHT1x_read_status_reg(unsigned char *p_value);
signed char SHT1x_write_status_reg(unsigned char value);
void SHT1x_connection_reset(void);
unsigned char SHT1x_soft_reset(void);