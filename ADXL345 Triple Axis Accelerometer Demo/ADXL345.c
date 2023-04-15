#include "ADXL345.h"


void ADXL345_init()
{
    TWI_Init(100000);
    delay_ms(100);
    power_sequence();
    set_sensitivity(_2g);
    set_bandwidth(ADXL345_BW_100);
}


void ADXL345_write_byte(unsigned char address, unsigned char value)
{
     TWI_Start();
     TWI_Write(ADXL345_Write);
     TWI_Write(address);
     TWI_Write(value);
     TWI_Stop();
}


void ADXL345_write_word(unsigned char address, unsigned int value)
{
     unsigned int temp = 0x0000;
     
     temp = value & 0xFF00;
     temp >>= 8;
     
     TWI_Start();
     TWI_Write(ADXL345_Write);
     TWI_Write(address);
     TWI_Write(value & 0x00FF);
     TWI_Write(temp);
     TWI_Stop();
}


unsigned char ADXL345_read_byte(unsigned char address)
{
     unsigned char value = 0x00;
     
     TWI_Start();
     TWI_Write(ADXL345_Write);
     TWI_Write(address);
     TWI_Start();
     TWI_Write(ADXL345_Read);
     value = TWI_Read(0);
     TWI_Stop();
     
     return value;
}


unsigned int ADXL345_read_word(unsigned char address)
{
     unsigned char hb = 0x00;
     unsigned char lb = 0x00;
     
     unsigned int temp = 0x0000;
     
     TWI_Start();
     TWI_Write(ADXL345_Write);
     TWI_Write(address);
     TWI_Start();
     TWI_Write(ADXL345_Read);
     lb = TWI_Read(1);
     hb = TWI_Read(0);
     TWI_Stop();
     
     temp = hb;
     temp <<= 0x08;
     temp |= lb;
     
     return temp;
}


void power_sequence()
{
     ADXL345_write_byte(ADXL345_POWER_CTL, 0x00);
     ADXL345_write_byte(ADXL345_POWER_CTL, 0x10);
     ADXL345_write_byte(ADXL345_POWER_CTL, 0x08);
}


void set_sensitivity(unsigned char value)
{
     ADXL345_write_byte(ADXL345_DATA_FORMAT, value);
}


void set_bandwidth(unsigned char value)
{
    ADXL345_write_byte(ADXL345_BW_RATE, value);
}


void get_values(signed int *x_val, signed int *y_val, signed int *z_val, float scale)
{
     signed int val_x = 0x0000;
     signed int val_y = 0x0000;
     signed int val_z = 0x0000;
     unsigned char samples = 0x04;
     
     while(samples > 0)
     {
         val_x += ADXL345_read_word(ADXL345_DATAX0);
         val_y += ADXL345_read_word(ADXL345_DATAY0);
         val_z += ADXL345_read_word(ADXL345_DATAZ0);
         samples--;
     }
     
     val_x >>= 0x02;
     val_y >>= 0x02;
     val_z >>= 0x02;
     
     *x_val = (val_x * scale);
     *y_val = (val_y * scale);
     *z_val = (val_z * scale);
}