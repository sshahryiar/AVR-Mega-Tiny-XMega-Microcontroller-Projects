#include "DS1307.h"


void DS1307_init()
{
     Soft_I2C_Init();
     DS1307_write(control_reg, 0x10);
}


unsigned char DS1307_read(unsigned char address)
{
    unsigned char value = 0x00;

    Soft_I2C_Start();
    Soft_I2C_Write(DS1307_WR);
    Soft_I2C_Write(address);
    Soft_I2C_Start();
    Soft_I2C_Write(DS1307_RD);
    value = Soft_I2C_Read(0);
    Soft_I2C_Stop();
    
    return value;
}


void DS1307_write(unsigned char address, unsigned char value)
{
    Soft_I2C_Start();
    Soft_I2C_Write(DS1307_WR);
    Soft_I2C_Write(address);
    Soft_I2C_Write(value);
    Soft_I2C_Stop();
}


unsigned char bcd_to_decimal(unsigned char value)
{
    return ((value & 0x0F) + (((value & 0xF0) >> 0x04) * 0x0A));
}


unsigned char decimal_to_bcd(unsigned char value)
{
    return (((value / 0x0A) << 0x04) & 0xF0) | ((value % 0x0A) & 0x0F);
}


void get_time()
{
     time.s = DS1307_read(sec_reg);
     time.s = bcd_to_decimal(time.s);
     
     time.m = DS1307_read(min_reg);
     time.m = bcd_to_decimal(time.m);
     
     time.h = DS1307_read(hr_reg);
     time.h = bcd_to_decimal(time.h);
     
     time.dy = DS1307_read(day_reg);
     time.dy = bcd_to_decimal(time.dy);

     time.dt = DS1307_read(date_reg);
     time.dt = bcd_to_decimal(time.dt);

     time.mt = DS1307_read(month_reg);
     time.mt = bcd_to_decimal(time.mt);
     
     time.yr = DS1307_read(year_reg);
     time.yr = bcd_to_decimal(time.yr);
}


void set_time()
{
     time.s = decimal_to_bcd(time.s);
     DS1307_write(sec_reg, time.s);
     
     time.m = decimal_to_bcd(time.m);
     DS1307_write(min_reg, time.m);
     
     time.h = decimal_to_bcd(time.h);
     DS1307_write(hr_reg, time.h);

     time.dy = decimal_to_bcd(time.dy);
     DS1307_write(day_reg, time.dy);
     
     time.dt = decimal_to_bcd(time.dt);
     DS1307_write(date_reg, time.dt);

     time.mt = decimal_to_bcd(time.mt);
     DS1307_write(month_reg, time.mt);

     time.yr = decimal_to_bcd(time.yr);
     DS1307_write(year_reg, time.yr);
}