sbit Soft_I2C_Scl_Output    at                        PORTC5_bit;
sbit Soft_I2C_Sda_Output    at                        PORTC4_bit;
sbit Soft_I2C_Scl_Input     at                        PINC5_bit;
sbit Soft_I2C_Sda_Input     at                        PINC4_bit;
sbit Soft_I2C_Scl_Direction at                        DDC5_bit;
sbit Soft_I2C_Sda_Direction at                        DDC4_bit;

#define AM2320_address                            0xB8
#define I2C_write_cmd                             0x00
#define I2C_read_cmd                              0x01

#define AM2320_read_sensor_data                   0x03
#define AM2320_write_multiple_registers           0x10

#define AM2320_RH_hb                              0x00
#define AM2320_RH_lb                              0x01
#define AM2320_T_hb                               0x02
#define AM2320_T_lb                               0x03


unsigned char data_buffer[8];


void AM2320_init();
void AM2320_write(unsigned char *value, unsigned char length);
void AM2320_read(unsigned char *value, unsigned char length);
unsigned int CRC16(unsigned char *ptr, unsigned char length);
void get_sensor_data(unsigned char start_address, unsigned char input_length, unsigned char output_length);
void get_RH_and_temperature(unsigned int *data1, signed int *data2);
void get_CRC(unsigned int *CRC_data);