#include "L3G4200.h"


void L3G4200_init()
{
    TWI_Init(100000);
    delay_ms(10);
    
    L3G4200_write_byte(CTRL_REG1, 0xCF);
    delay_ms(1);
    L3G4200_write_byte(CTRL_REG2, 0x01);
    delay_ms(1);
    L3G4200_write_byte(CTRL_REG3, 0x00);
    delay_ms(1);
    L3G4200_write_byte(CTRL_REG4, 0x00);
    delay_ms(1);
    L3G4200_write_byte(CTRL_REG5, 0x02);
    delay_ms(1);
}


void L3G4200_write_byte(unsigned char address, unsigned char value)
{
     TWI_Start();
     TWI_Write(L3G4200_write_cmd);
     TWI_Write(address);
     TWI_Write(value);
     TWI_Stop();
}


void L3G4200_write_word(unsigned char address, unsigned int value)
{
     unsigned int temp = 0x0000;

     temp = (value & 0xFF00);
     temp >>= 0x08;

     TWI_Start();
     TWI_Write(L3G4200_write_cmd);
     TWI_Write(address);
     TWI_Write(temp);
     TWI_Write(value & 0x00FF);
     TWI_Stop();
}


unsigned char L3G4200_read_byte(unsigned char address)
{
     unsigned char value = 0x00;

     TWI_Start();
     TWI_Write(L3G4200_write_cmd);
     TWI_Write(address);
     TWI_Start();
     TWI_Write(L3G4200_read_cmd);
     value = TWI_Read(0);
     TWI_Stop();

     return value;
}


unsigned int L3G4200_read_word(unsigned char address)
{
     unsigned int hb = 0x00;
     unsigned char lb = 0x00;

     lb = L3G4200_read_byte(address);
     hb = L3G4200_read_byte(address + 1);

     hb <<= 0x08;
     hb |= lb;

     return hb;
}


signed char L3G4200_get_raw_temperature()
{
    signed char ts = 0x00;

    ts = L3G4200_read_byte(OUT_TEMP);
    
    return ts;
}


signed char L3G4200_get_temperature()
{
    signed char ts = 0x00;
    
    ts = L3G4200_get_raw_temperature();
    ts = (51 - (ts * 1.33));
    
    return ts;
}


void L3G4200_get_raw_data(signed int *x_val, signed int *y_val, signed int *z_val)
{
     *x_val = L3G4200_read_word(OUT_X_L);
     *y_val = L3G4200_read_word(OUT_Y_L);
     *z_val = L3G4200_read_word(OUT_Z_L);
}


void L3G4200_degrees_per_second(signed int *x_val, signed int *y_val, signed int *z_val, float scale)
{
     signed int val_x = 0x0000;
     signed int val_y = 0x0000;
     signed int val_z = 0x0000;

     val_x = *x_val;
     val_y = *y_val;
     val_z = *z_val;

     *x_val = (val_x * scale);
     *y_val = (val_y * scale);
     *z_val = (val_z * scale);
}