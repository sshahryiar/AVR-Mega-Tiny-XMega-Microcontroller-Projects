#include "AT24C32.h"


unsigned char get_low_byte(signed int address)
{
    return (address & 0x00FF);
}


unsigned char get_high_byte(signed int address)
{
    unsigned int temp = 0x0000;

    temp = (address & 0x0F00);
    temp >>= 0x08;

    return temp;
}


unsigned char AT24C32_read(unsigned int address)
{
     unsigned char value = 0x00;

     Soft_I2C_Start();
     Soft_I2C_Write(AT24C32_WR);
     Soft_I2C_Write(get_high_byte(address));
     Soft_I2C_Write(get_low_byte(address));
     Soft_I2C_Start();
     Soft_I2C_Write(AT24C32_RD);
     value = Soft_I2C_Read(0);
     Soft_I2C_Stop();
     delay_ms(16);
     
     return value;
}


void AT24C32_byte_write(unsigned int address, unsigned char value)
{
     Soft_I2C_Start();
     Soft_I2C_Write(AT24C32_WR);
     Soft_I2C_Write(get_high_byte(address));
     Soft_I2C_Write(get_low_byte(address));
     Soft_I2C_Write(value);
     Soft_I2C_Stop();
     delay_ms(16);
}


void AT24C32_page_write(unsigned int address)
{
     unsigned char ee = 0x00;

     Soft_I2C_Start();
     Soft_I2C_Write(AT24C32_WR);
     Soft_I2C_Write(get_high_byte(address));
     Soft_I2C_Write(get_low_byte(address));
     
     for(ee = 0; ee < bytes_per_page; ee++)
     {
         Soft_I2C_Write(buffer[ee]);
     }
     
     Soft_I2C_Stop();
     delay_ms(16);
}