#include "PCF8574.h"


unsigned char PCF8574_read()
{
    unsigned char port_byte = 0;
    soft_i2c_start();
    soft_i2c_write(PCF8574_read_cmd);
    port_byte = soft_i2c_read(0);
    soft_i2c_stop();
    return port_byte;
}


void PCF8574_write(unsigned char data_byte)
{
    soft_i2c_start();
    soft_i2c_write(PCF8574_write_cmd);
    soft_i2c_write(data_byte);
    soft_i2c_stop();
}